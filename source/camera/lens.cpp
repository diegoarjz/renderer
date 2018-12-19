#include "lens.h"

#include <glm/gtc/matrix_transform.hpp>

namespace r
{
Lens::Lens() : m_projectionMatrix(1) {}

void Lens::SetPerspective(float fovY, float aspect, float near, float far)
{
	m_projectionMatrix = glm::perspective(glm::radians(fovY), aspect, near, far);
}

void Lens::SetOrthogonal(float left, float right, float top, float bottom)
{
	m_projectionMatrix = glm::ortho(left, right, top, bottom);
}
}  // namespace r
