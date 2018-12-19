#pragma once

#include "window_creation_params.h"

#include <cstdint>
#include <memory>

namespace r
{
class CommandList;
using CommandListPtr = std::shared_ptr<CommandList>;
class Renderer;
using RendererPtr = std::shared_ptr<Renderer>;

class Window
{
public:
	Window();
	~Window();

	bool GetSize(uint32_t* outWidth, uint32_t* outHeight);
	bool GetFrameBufferSize(uint32_t* outWidth, uint32_t* outHeight);
	void SetTitle(const std::string& title);

	enum class CreationStatus
	{
		Success,
		Failure
	};

	CreationStatus Create(const WindowCreationParams& parameters);
	bool GetWindowShouldClose() const;
	void MakeContextCurrent();
	void Destroy();
	void SwapBuffers();
	void SetRenderer(RendererPtr renderer);

	void Update();

private:
	struct Impl;
	std::unique_ptr<Impl> m_implementation;
};  // class Window

using WindowPtr = std::shared_ptr<Window>;
}  // namespace r
