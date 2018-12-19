#include "set_camera_on_renderer.h"

#include "rendering/renderer.h"

#include "camera.h"

namespace r
{
void SetCameraOnRenderer::Execute(Renderer *renderer)
{
	renderer->SetViewMatrix(m_camera->GetViewMatrix());
	renderer->SetProjectionMatrix(m_camera->GetProjectionMatrix());
}
}  // namespace r
