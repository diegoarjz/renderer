#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace r
{
class Transformation
{
public:
	Transformation();
	Transformation(const glm::quat &rotation, const glm::vec3 &position, const glm::vec3 &scale);
	Transformation(const glm::vec3 &rotEulerAngles, const glm::vec3 &position, const glm::vec3 &scale);
	Transformation(const Transformation &transform);

	const glm::mat4 &GetTransformationMatrix();

	void SetPosition(const float &x, const float &y, const float &z);
	void SetPosition(const glm::vec3 &pos);
	void Translate(const float &x, const float &y, const float &z);
	void Translate(const glm::vec3 &translation);

	void SetScale(const float &scale);
	void SetScale(const float &x, const float &y, const float &z);
	void SetScale(const glm::vec3 &s);

	// Rotation around Z axis
	void Yaw(const float &angle);
	// Rotation around Y axis
	void Pitch(const float &angle);
	// Rotation around X axis
	void Roll(const float &angle);

private:
	glm::quat m_rotation;
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::mat4 m_transformMatrix;
	bool m_transformMatrixIsDirty;
};
}  // namespace r
