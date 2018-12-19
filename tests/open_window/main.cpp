#include "window.h"

#include <GLFW/glfw3.h>

#include <iostream>

int main(int argc, char *argv[])
{
	r::WindowPtr window = std::make_shared<r::Window>();

	r::WindowCreationParams params;

	r::Window::CreationStatus status = window->Create(params);

	if (status != r::Window::CreationStatus::Success)
	{
		return 1;
	}

	uint32_t windowWidth = 0;
	uint32_t windowHeight = 0;
	uint32_t frameBufferWidth = 0;
	uint32_t frameBufferHeight = 0;

	window->GetSize(&windowWidth, &windowHeight);
	window->GetFrameBufferSize(&frameBufferWidth, &frameBufferHeight);

	std::cout << "Successfully created window" << std::endl;
	std::cout << " Size: " << windowWidth << "x" << windowHeight << std::endl;
	std::cout << " Frame Buffer Size: " << frameBufferWidth << "x" << frameBufferHeight << std::endl;

	while (!window->GetWindowShouldClose())
	{
		glfwPollEvents();
	}

	window->Destroy();

	glfwTerminate();

	return 0;
}
