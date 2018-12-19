#pragma once

#include "thread/thread.h"

namespace r
{
class RenderPool;
using RenderPoolPtr = std::shared_ptr<RenderPool>;

class UpdateLoop : public Thread
{
public:
	UpdateLoop();
	virtual ~UpdateLoop();

	void SetRenderPool(RenderPoolPtr renderPool) { m_renderPool = renderPool; }
	RenderPoolPtr GetRenderPool() const { return m_renderPool; }
	uint32_t GetCurrentFrame() const { return m_currentFrame; }

	virtual bool Update() = 0;
	virtual void ShouldStop() = 0;

protected:
	void run() override;

private:
	RenderPoolPtr m_renderPool;
	uint32_t m_currentFrame;
};
}  // namespace r
