#include "render_model.h"

#include "common/logger.h"
#include "geometry/render_geometry.h"
#include "material/set_shader_program.h"
#include "model.h"
#include "rendering/renderer.h"

namespace r
{
void RenderModel::Execute(Renderer *renderer)
{
	renderer->SetModelMatrix(m_model->GetTransformation().GetTransformationMatrix());

	SetShaderProgram setShaderProgram;
	setShaderProgram.SetProgram(m_model->GetShaderProgram());
	setShaderProgram.Execute(renderer);

	RenderGeometry renderGeometry;
	renderGeometry.SetGeometry(m_model->GetGeometry());
	renderGeometry.Execute(renderer);
}
}  // namespace r
