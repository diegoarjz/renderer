#include "render_pool.h"

#include "command_list.h"

#include "common/logger.h"

namespace r
{
RenderPool::RenderPool()
    : mCurrentFrame(0), m_frames{std::make_shared<CommandList>(nullptr), std::make_shared<CommandList>(nullptr)}
{
}

RenderPool::~RenderPool() {}

void RenderPool::AddCommandList(CommandListPtr commandList) { m_frames[NextFrame()] = commandList; }

void RenderPool::SwapRenderQueues()
{
	m_frames[mCurrentFrame] = nullptr;
	mCurrentFrame = (mCurrentFrame + 1) % 2;
}

void RenderPool::NotifyUpdateReady()
{
	LOG_TRACE(Rendering, "Notify Update Ready");
	mUpdateReadyEvent.Notify();
}

void RenderPool::WaitForUpdateReady()
{
	LOG_TRACE(Rendering, "Wait for Update Ready");
	mUpdateReadyEvent.Wait();
}

void RenderPool::WaitForRenderReady()
{
	LOG_TRACE(Rendering, "Wait for Render Ready");
	mRenderReadyEvent.Wait();
}

void RenderPool::NotifyRenderReady()
{
	LOG_TRACE(Rendering, "Notify Render Ready");
	mRenderReadyEvent.Notify();
}

void RenderPool::NotifyRenderDone()
{
	LOG_TRACE(Rendering, "Notify Render Done");
	mRenderDoneEvent.Notify();
}

void RenderPool::WaitForRenderDone()
{
	LOG_TRACE(Rendering, "Wait for Render Done");
	mRenderDoneEvent.Wait();
}

void RenderPool::NotifySwapDone()
{
	LOG_TRACE(Rendering, "Notify Update Ready");
	mSwapDoneEvent.Notify();
}

void RenderPool::WaitForSwapDone()
{
	LOG_TRACE(Rendering, "Notify Update Ready");
	mSwapDoneEvent.Wait();
}

uint32_t RenderPool::CurrentFrame() const { return mCurrentFrame; }

uint32_t RenderPool::NextFrame() const { return (CurrentFrame() + 1) % 2; }

CommandListPtr RenderPool::GetCurrentCommandList() const { return m_frames[CurrentFrame()]; }
}  // namespace r
