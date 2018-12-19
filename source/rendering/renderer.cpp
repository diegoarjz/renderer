#include "renderer.h"

#include "common/logger.h"

#include "command.h"
#include "command_list.h"
#include "render_pool.h"

#include <typeinfo>

namespace r
{
Renderer::Renderer() : m_currentFrame(0) {}

Renderer::~Renderer() {}

RenderPoolPtr Renderer::GetRenderPool() const { return mRenderPool; }

void Renderer::SetRenderPool(RenderPoolPtr renderPool) { mRenderPool = renderPool; }

void Renderer::SetModelMatrix(const glm::mat4& mat) { mModelMatrix = mat; }

const glm::mat4& Renderer::GetModelMatrix() const { return mModelMatrix; }

void Renderer::SetViewMatrix(const glm::mat4& mat) { mViewMatrix = mat; }

const glm::mat4& Renderer::GetViewMatrix() const { return mViewMatrix; }

void Renderer::SetProjectionMatrix(const glm::mat4& mat) { mProjectionMatrix = mat; }

const glm::mat4& Renderer::GetProjectionMatrix() const { return mProjectionMatrix; }

void Renderer::Start()
{
	// notify that the renderer is ready
	mRenderPool->NotifyRenderReady();
	// and wait for the update cycle to be ready
	mRenderPool->WaitForUpdateReady();
}

void Renderer::RenderFrame()
{
	CommandListPtr commandList = mRenderPool->GetCurrentCommandList();

	Command* currentCmd = commandList->GetHead();

	while (currentCmd != nullptr)
	{
		currentCmd->Execute(this);
		currentCmd = currentCmd->GetNext();
	}

	m_currentFrame++;
}

void Renderer::WaitForUpdateLoop()
{
	mRenderPool->NotifyRenderDone();
	mRenderPool->WaitForSwapDone();
}

void Renderer::Stop() {}

}  // namespace r
