#include "basic_test_application.h"

#include <common/logger.h>

#include <image/image.h>
#include <image/png_writer.h>

#include <rendering/render_pool.h>
#include <rendering/renderer.h>
#include <update_loop.h>

#include <window.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

namespace r
{
BasicTestApplication::BasicTestApplication() : m_quitAfterFrame(-1) {}

std::string get_value_from_command_line_option(uint32_t *index, char *argv[])
{
	std::string argument = argv[*index];
	std::size_t pos = argument.find_first_of('=');
	std::string value;
	if (pos != std::string::npos)
	{
		value = argument.substr(pos + 1);
	}
	else
	{
		value = argv[*index];
		*index += 1;
	}
	return value;
}

std::list<uint32_t> parse_frames(const std::string &frames)
{
	std::list<uint32_t> parsedFrames;
	std::size_t current = 0;
	std::size_t previous = 0;
	current = frames.find(',');
	while (current != std::string::npos)
	{
		parsedFrames.push_back(std::atoi(frames.substr(previous, current - previous).c_str()));
		previous = current + 1;
		current = frames.find(",", previous);
	}
	parsedFrames.push_back(std::atoi(frames.substr(previous, current - previous).c_str()));
	return parsedFrames;
}

bool BasicTestApplication::ParseCommandLine(int argc, char *argv[])
{
	for (uint32_t i = 1; i < argc; ++i)
	{
		std::string argument = argv[i];

		if (argument.find("--qaf") == 0)
		{
			m_quitAfterFrame = std::atoi(get_value_from_command_line_option(&i, argv).c_str());
			continue;
		}

		if (argument.find("--grab-frames") == 0)
		{
			std::string frames = get_value_from_command_line_option(&i, argv);
			m_framesToGrab = parse_frames(frames);
			continue;
		}
	}

	return true;
}

void BasicTestApplication::Start()
{
	m_window = std::make_shared<Window>();
	Window::CreationStatus status = m_window->Create(m_windowCreationParams);
	m_renderer = std::make_shared<Renderer>();
	m_renderPool = std::make_shared<RenderPool>();

	uint32_t windowWidth, windowHeight;
	m_window->GetSize(&windowWidth, &windowHeight);
	ImageCreationParams imageCreationParams(windowWidth, windowHeight);

	m_updateLoop->SetRenderPool(m_renderPool);

	m_renderer->SetRenderPool(m_renderPool);
	m_window->SetRenderer(m_renderer);

	m_updateLoop->Start();
	m_renderer->Start();

	while (!m_window->GetWindowShouldClose())
	{
		m_window->MakeContextCurrent();

		uint32_t frame = m_renderer->GetCurrentFrame();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_window->Update();

		glfwPollEvents();

		if (m_framesToGrab.size() > 0)
		{
			if (frame == m_framesToGrab.front())
			{
				// Take screen shot
				auto image = std::make_shared<r::Image>(imageCreationParams);
				r::PngWriter writer(image);

				std::stringstream file_name;
				file_name << "frame" << frame << ".png";

				glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, image->GetImageData());
				writer.WriteToFile(file_name.str().c_str());

				m_framesToGrab.pop_front();
			}
		}

		if (frame == m_quitAfterFrame)
		{
			break;
		}
	}

	m_updateLoop->ShouldStop();
	m_window->Destroy();
	m_updateLoop->Join();

	glfwTerminate();
}

}  // namespace r
