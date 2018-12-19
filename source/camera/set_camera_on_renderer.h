#pragma once

#include "rendering/command.h"

#include <memory>

namespace r
{
class Camera;
using CameraPtr = std::shared_ptr<Camera>;

class SetCameraOnRenderer : public Command
{
public:
	void Execute(Renderer *r) override;

	void SetCamera(CameraPtr camera) { m_camera = camera; }
	CameraPtr GetCamera() const { return m_camera; }

private:
	CameraPtr m_camera;
};
}  // namespace r
