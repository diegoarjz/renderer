#include "window.h"

#include "common/logger.h"

#include "rendering/command_list.h"
#include "rendering/renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace r
{
void errorCallback(int errorCode, const char* errorDescription)
{
	LOG_FATAL("GLFW raised an error");
	LOG_FATAL("\tError Code: 0x%X", errorCode);
	LOG_FATAL("\tError Description: %s", errorDescription);
}

struct Window::Impl
{
	Impl() : m_window(nullptr) {}
	~Impl() { Destroy(); }

	bool GetSize(uint32_t* outWidth, uint32_t* outHeight)
	{
		if (!m_window)
		{
			return false;
		}

		int32_t width;
		int32_t height;

		glfwGetWindowSize(m_window, &width, &height);

		*outWidth = width;
		*outHeight = height;

		return true;
	}

	bool GetFrameBufferSize(uint32_t* outWidth, uint32_t* outHeight)
	{
		if (!m_window)
		{
			return false;
		}

		int32_t width;
		int32_t height;

		glfwGetFramebufferSize(m_window, &width, &height);

		*outWidth = width;
		*outHeight = height;

		return true;
	}

	void SetTitle(const std::string& title)
	{
		if (m_window)
		{
			glfwSetWindowTitle(m_window, title.c_str());
		}
	}

	CreationStatus Create(const WindowCreationParams& params)
	{
		auto pixelFormat = params.GetPixelFormat();
		auto contextVersion = params.GetContextVersion();

		LOG_TRACE(Window, "Creating Window");
		LOG_TRACE(Window, "\tSize: %dx%d Position: (%d, %d)", params.GetWidth(), params.GetHeight(), params.GetXPos(),
		          params.GetYPos());
		LOG_TRACE(Window, "\tOpenGL Context Version %d.%d", contextVersion[0], contextVersion[1]);
		LOG_TRACE(Window, "\tPixel Format: Red: %d Green: %d Blue: %d Alpha: %d", pixelFormat[0], pixelFormat[1],
		          pixelFormat[2], pixelFormat[3]);
		LOG_TRACE(Window, "\tDepth Bits: %d StencilBits: %d", params.GetDepthBits(), params.GetStencilBits());
		LOG_TRACE(Window, "\tAntialias Samples: %d", params.GetAntialiasSamples());
		LOG_TRACE(Window, "\tGetDoubleBuffer: %d", params.GetDoubleBuffer());
		LOG_TRACE(Window, "\tOpenGL DebugContext: %d", params.GetDebugContext());

		if (m_window)
		{
			LOG_FATAL("Window creation requested but window already created.");
			return CreationStatus::Failure;
		}

		glfwSetErrorCallback(errorCallback);

		if (!glfwInit())
		{
			LOG_FATAL("Failed to initialize GLFW");
			// TODO: doesn't really belong here...
			return CreationStatus::Failure;
		}

		// TODO: Full screen

		for (uint32_t i = 0; i < 4; ++i)
		{
			glfwWindowHint(GLFW_RED_BITS + i, pixelFormat[i]);
		}
		glfwWindowHint(GLFW_DEPTH_BITS, params.GetDepthBits());
		glfwWindowHint(GLFW_STENCIL_BITS, params.GetStencilBits());
		glfwWindowHint(GLFW_SAMPLES, params.GetAntialiasSamples());
		glfwWindowHint(GLFW_DOUBLEBUFFER, params.GetDoubleBuffer());
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextVersion[0]);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextVersion[0]);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, params.GetDebugContext());
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		m_window = glfwCreateWindow(params.GetWidth(), params.GetHeight(), params.GetTitle().c_str(), NULL, NULL);

		if (!m_window)
		{
			LOG_FATAL("Failed to create window");
			glfwTerminate();
			return CreationStatus::Failure;
		}

		MakeContextCurrent();

		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
			LOG_FATAL("Failed to initialize GLEW");
			glfwTerminate();
			return CreationStatus::Failure;
		}

		glfwSetWindowPos(m_window, params.GetXPos(), params.GetYPos());

		return CreationStatus::Success;
	}

	void MakeContextCurrent()
	{
		if (!m_window)
		{
			return;
		}
		glfwMakeContextCurrent(m_window);
	}

	bool GetWindowShouldClose() const { return m_window && glfwWindowShouldClose(m_window); }

	void Destroy()
	{
		if (m_window)
		{
			glfwDestroyWindow(m_window);
			m_window = nullptr;
		}
		if (m_renderer)
		{
			m_renderer->Stop();
			m_renderer = nullptr;
		}
	}

	void SwapBuffers()
	{
		if (m_window)
		{
			glfwSwapBuffers(m_window);
		}
	}

	void SetRenderer(RendererPtr renderer) { m_renderer = renderer; }

	void Update()
	{
		m_renderer->RenderFrame();
		SwapBuffers();
		m_renderer->WaitForUpdateLoop();
	}

private:
	GLFWwindow* m_window;
	RendererPtr m_renderer;
};  // struct Window::Impl

Window::Window() : m_implementation(std::make_unique<Window::Impl>()) {}

Window::~Window() {}

bool Window::GetSize(uint32_t* outWidth, uint32_t* outHeight) { return m_implementation->GetSize(outWidth, outHeight); }
bool Window::GetFrameBufferSize(uint32_t* outWidth, uint32_t* outHeight)
{
	return m_implementation->GetFrameBufferSize(outWidth, outHeight);
}
void Window::SetTitle(const std::string& title) { m_implementation->SetTitle(title); }

Window::CreationStatus Window::Create(const WindowCreationParams& params) { return m_implementation->Create(params); }
void Window::MakeContextCurrent() { return m_implementation->MakeContextCurrent(); }
bool Window::GetWindowShouldClose() const { return m_implementation->GetWindowShouldClose(); }
void Window::Destroy() { m_implementation->Destroy(); }
void Window::SwapBuffers() { m_implementation->SwapBuffers(); }
void Window::SetRenderer(RendererPtr renderer) { m_implementation->SetRenderer(renderer); }

void Window::Update() { m_implementation->Update(); }

}  // namespace r
