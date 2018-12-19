#pragma once

#include "thread/auto_reset_event.h"

namespace r
{
class CommandList;
using CommandListPtr = std::shared_ptr<CommandList>;

/**
 * The update thread queues render tasks in one frame, while
 * the render thread dequeues them from another frame.
 *
 * Has some methods that allows the proper synchronisation between threads.
 * Upon intialization, the update thread sends the UpdateReady event and waits for the
 * RenderReady event. Similarily, the render thread sends the ReaderReady event and waits for
 * the UpdateReady event. This way, neither the update thread starts pushing render
 * tasks ahead of time, nor the render thread begins reading tasks before.
 *
 * Each frame, the update thread submits render tasks to the next frame (n+1). When
 * finished, it waits for the RenderDone event. In the mean time, the render thread is
 * busy performing the render tasks from the current frame (n) and, when complete, it sends the
 * RenderDone event, and waits for the SwapDone event.
 *
 * The RenderDone event is received by the update thread which, afterwards triggers the
 * buffer swap and sends the SwapDone event.
 *
 * This mechanism allows the proper synchronisation between threads and allows the
 * creation of the next frame to execute while the current is being rendered.
 */
class RenderPool
{
public:
	RenderPool();
	~RenderPool();

	void NotifyUpdateReady();
	void WaitForUpdateReady();

	void NotifyRenderReady();
	void WaitForRenderReady();

	void NotifyRenderDone();
	void WaitForRenderDone();

	void NotifySwapDone();
	void WaitForSwapDone();

	void AddCommandList(CommandListPtr commandList);
	void SwapRenderQueues();
	uint32_t CurrentFrame() const;
	uint32_t NextFrame() const;
	CommandListPtr GetCurrentCommandList() const;

private:
	CommandListPtr m_frames[2];
	uint32_t mCurrentFrame;
	AutoResetEvent mRenderReadyEvent;
	AutoResetEvent mRenderDoneEvent;
	AutoResetEvent mUpdateReadyEvent;
	AutoResetEvent mSwapDoneEvent;

};  // class RenderPool
}  // namespace r
