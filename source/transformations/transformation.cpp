#include "transformation.h"

#include "common/logger.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>

namespace r
{
Transformation::Transformation()
    : m_rotation(glm::vec3(0, 0, 0)), m_position(0, 0, 0), m_scale(1, 1, 1), m_transformMatrixIsDirty(true)
{
}

Transformation::Transformation(const glm::quat &rotation, const glm::vec3 &position, const glm::vec3 &scale)
    : m_rotation(rotation), m_position(position), m_scale(scale), m_transformMatrixIsDirty(true)
{
}

Transformation::Transformation(const glm::vec3 &rotEulerAngles, const glm::vec3 &position, const glm::vec3 &scale)
    : m_rotation(rotEulerAngles), m_position(position), m_scale(scale), m_transformMatrixIsDirty(true)
{
}

Transformation::Transformation(const Transformation &transform)
    : m_rotation(transform.m_rotation),
      m_position(transform.m_position),
      m_scale(transform.m_scale),
      m_transformMatrix(transform.m_transformMatrix),
      m_transformMatrixIsDirty(transform.m_transformMatrixIsDirty)
{
}

const glm::mat4 &Transformation::GetTransformationMatrix()
{
	if (m_transformMatrixIsDirty)
	{
		m_transformMatrix =
		    glm::translate(glm::mat4(1), m_position) * glm::toMat4(m_rotation) * glm::scale(glm::mat4(1), m_scale);
		m_transformMatrixIsDirty = false;
	}

	return m_transformMatrix;
}

void Transformation::SetPosition(const float &x, const float &y, const float &z) { SetPosition(glm::vec3(x, y, z)); }

void Transformation::SetPosition(const glm::vec3 &pos)
{
	m_position = pos;
	m_transformMatrixIsDirty = true;
}

void Transformation::Translate(const float &x, const float &y, const float &z) { Translate(glm::vec3(x, y, z)); }

void Transformation::Translate(const glm::vec3 &translation)
{
	m_position += translation;
	m_transformMatrixIsDirty = true;
}

void Transformation::SetScale(const float &scale) { SetScale(glm::vec3(scale, scale, scale)); }

void Transformation::SetScale(const float &x, const float &y, const float &z) { SetScale(glm::vec3(x, y, z)); }

void Transformation::SetScale(const glm::vec3 &s)
{
	m_scale = s;
	m_transformMatrixIsDirty = true;
}

void Transformation::Yaw(const float &angle)
{
	m_rotation = glm::quat(glm::vec3(0, 0, angle)) * m_rotation;
	m_transformMatrixIsDirty = true;
}
void Transformation::Pitch(const float &angle)
{
	m_rotation = glm::quat(glm::vec3(angle, 0, 0)) * m_rotation;
	m_transformMatrixIsDirty = true;
}
void Transformation::Roll(const float &angle)
{
	m_rotation = glm::quat(glm::vec3(0, angle, 0)) * m_rotation;
	m_transformMatrixIsDirty = true;
}

}  // namespace r
