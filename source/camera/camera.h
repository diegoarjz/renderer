#pragma once

#include <glm/glm.hpp>

#include <memory>

namespace r
{
class Lens;
using LensPtr = std::shared_ptr<Lens>;

class Camera
{
public:
	Camera();
	Camera(const glm::vec3 &position, const glm::vec3 &viewDirection);

	void SetPosition(const glm::vec3 &position);
	const glm::vec3 &GetPosition() const;
	void SetViewDirection(const glm::vec3 &viewDirection);
	const glm::vec3 &GetViewDirection() const;

	const glm::mat4 &GetViewMatrix();
	const glm::mat4 &GetProjectionMatrix();

	void SetLens(LensPtr lens) { m_lens = lens; }
	LensPtr GetLens() const { return m_lens; }

private:
	LensPtr m_lens;

	glm::vec3 m_position;
	glm::vec3 m_viewDirection;
	glm::mat4 m_viewMatrix;
	bool m_viewMatrixDirty;
};

using CameraPtr = std::shared_ptr<Camera>;
}  // namespace r
