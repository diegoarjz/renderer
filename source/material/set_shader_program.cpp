#include "set_shader_program.h"

#include "shader_program.h"

#include "rendering/bindable.h"
#include "rendering/gl_debug.h"
#include "rendering/renderer.h"

#include "common/logger.h"

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <iostream>

namespace r
{
void SetShaderProgram::Execute(Renderer *renderer)
{
	Bindable &bindable = m_shaderProgram->GetBindable();
	glUseProgram(bindable.GetBindingData());
	CHECK_GL_ERROR;

	for (auto uniform : m_shaderProgram->GetUniforms())
	{
		Bindable &bindable = uniform->GetBindable();
		GLuint uniformId = bindable.GetBindingData();

		switch (uniform->GetSemantics())
		{
			case Uniform::Semantics::ModelMatrix:
				uniform->SetMatrix4(renderer->GetModelMatrix());
				break;
			case Uniform::Semantics::ViewMatrix:
				uniform->SetMatrix4(renderer->GetViewMatrix());
				break;
			case Uniform::Semantics::ProjectionMatrix:
				uniform->SetMatrix4(renderer->GetProjectionMatrix());
				break;
			default:
				break;
		};

		if (!uniform->IsDirty())
		{
			continue;
		}

		switch (uniform->GetType())
		{
			case Uniform::Type::Float:
				break;
			case Uniform::Type::Vec2:
				break;
			case Uniform::Type::Vec3:
				break;
			case Uniform::Type::Vec4:
				break;
			case Uniform::Type::Integer:
				break;
			case Uniform::Type::Unsigned:
				break;
			case Uniform::Type::Matrix2:
				break;
			case Uniform::Type::Matrix3:
				break;
			case Uniform::Type::Matrix4:
			{
				glUniformMatrix4fv(uniformId, 1, GL_FALSE, &(uniform->GetMatrix4()[0][0]));
				break;
			}
		};
		CHECK_GL_ERROR;

		uniform->NotDirty();
	}
}
}  // namespace r
