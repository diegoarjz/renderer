#pragma once

#include <window_creation_params.h>

#include <list>
#include <memory>

namespace r
{
class UpdateLoop;
using UpdateLoopPtr = std::shared_ptr<UpdateLoop>;
class Window;
using WindowPtr = std::shared_ptr<Window>;
class Renderer;
using RendererPtr = std::shared_ptr<Renderer>;
class RenderPool;
using RenderPoolPtr = std::shared_ptr<RenderPool>;

class BasicTestApplication
{
public:
	BasicTestApplication();

	virtual bool ParseCommandLine(int argc, char *argv[]);

	void SetUpdateLoop(UpdateLoopPtr updateLoop) { m_updateLoop = updateLoop; }

	void Start();

protected:
	WindowPtr m_window;
	WindowCreationParams m_windowCreationParams;
	UpdateLoopPtr m_updateLoop;
	RendererPtr m_renderer;
	RenderPoolPtr m_renderPool;

	int32_t m_quitAfterFrame;
	std::list<uint32_t> m_framesToGrab;
};
}  // namespace r
