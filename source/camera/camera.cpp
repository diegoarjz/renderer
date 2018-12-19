#include "camera.h"

#include "lens.h"

#include <glm/gtc/matrix_transform.hpp>

namespace r
{
Camera::Camera()
    : m_position(0, 0, 0),
      m_viewDirection(0, 0, 1),
      m_viewMatrix(1),
      m_viewMatrixDirty(true),
      m_lens(std::make_shared<Lens>())
{
}

Camera::Camera(const glm::vec3 &position, const glm::vec3 &viewDirection)
    : m_position(position),
      m_viewDirection(viewDirection),
      m_viewMatrix(1),
      m_viewMatrixDirty(true),
      m_lens(std::make_shared<Lens>())
{
}

void Camera::SetPosition(const glm::vec3 &position)
{
	m_position = position;
	m_viewMatrixDirty = true;
}

const glm::vec3 &Camera::GetPosition() const { return m_position; }

void Camera::SetViewDirection(const glm::vec3 &viewDirection)
{
	m_viewDirection = viewDirection;
	m_viewMatrixDirty = true;
}

const glm::vec3 &Camera::GetViewDirection() const { return m_viewDirection; }

const glm::mat4 &Camera::GetViewMatrix()
{
	if (m_viewMatrixDirty)
	{
		m_viewMatrix = glm::lookAt(m_position, m_position + m_viewDirection, glm::vec3(0, 1, 0));
		m_viewMatrixDirty = false;
	}
	return m_viewMatrix;
}

const glm::mat4 &Camera::GetProjectionMatrix() { return m_lens->GetProjectionMatrix(); }

}  // namespace r
