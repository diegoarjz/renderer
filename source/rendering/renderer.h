#pragma once

#include <glm/glm.hpp>

#include <memory>

namespace r
{
class RenderPool;
using RenderPoolPtr = std::shared_ptr<RenderPool>;

class Renderer
{
public:
	Renderer();
	~Renderer();

	RenderPoolPtr GetRenderPool() const;
	void SetRenderPool(RenderPoolPtr renderPool);
	void SetModelMatrix(const glm::mat4& mat);
	const glm::mat4& GetModelMatrix() const;
	void SetViewMatrix(const glm::mat4& mat);
	const glm::mat4& GetViewMatrix() const;
	void SetProjectionMatrix(const glm::mat4& mat);
	const glm::mat4& GetProjectionMatrix() const;

	void Start();
	void RenderFrame();
	void WaitForUpdateLoop();
	void Stop();

	uint32_t GetCurrentFrame() const { return m_currentFrame; }

private:
	RenderPoolPtr mRenderPool;
	uint32_t m_currentFrame;
	glm::mat4 mModelMatrix;
	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;
};  // class Renderer

using RendererPtr = std::shared_ptr<Renderer>;
}  // namespace r
