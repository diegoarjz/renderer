#include "update_loop.h"

#include "rendering/render_pool.h"

namespace r
{
UpdateLoop::UpdateLoop() : m_renderPool(nullptr), m_currentFrame(0) {}
UpdateLoop::~UpdateLoop() {}

void UpdateLoop::run()
{
	m_renderPool->NotifyUpdateReady();
	m_renderPool->WaitForRenderReady();

	while (true)
	{
		bool shouldStop = Update();
		if (shouldStop)
		{
			break;
		}

		m_renderPool->WaitForRenderDone();
		m_renderPool->SwapRenderQueues();
		m_renderPool->NotifySwapDone();

		m_currentFrame++;
	}
}
}  // namespace r
