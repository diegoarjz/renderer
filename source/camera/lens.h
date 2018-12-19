#pragma once

#include <glm/glm.hpp>

#include <memory>

namespace r
{
class Lens
{
public:
	Lens();

	void SetPerspective(float fovY, float aspect, float near, float far);
	void SetOrthogonal(float left, float right, float top, float bottom);

	const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }

protected:
	glm::mat4 m_projectionMatrix;
};
}  // namespace r
