#include "create_shader_program.h"

#include "compile_shader.h"
#include "shader.h"
#include "shader_program.h"

#include "common/logger.h"
#include "rendering/gl_debug.h"

#include <GL/glew.h>

#include <vector>

namespace r
{
void CreateShaderProgram::Execute(Renderer* renderer)
{
	GLuint programId = glCreateProgram();
	CHECK_GL_ERROR;

	CompileShader compileShader;
	for (uint32_t i = 0; i < static_cast<uint32_t>(Shader::ShaderType::MAX); ++i)
	{
		ShaderPtr shader = m_shaderProgram->GetShader(static_cast<Shader::ShaderType>(i));
		if (shader != nullptr)
		{
			Bindable& bindData = shader->GetBindable();
			if (bindData.GetBindState() == Bindable::BindState::NotBound)
			{
				compileShader.SetShader(shader);
				compileShader.Execute(renderer);
			}
			glAttachShader(programId, bindData.GetBindingData());
			CHECK_GL_ERROR;
		}
	}

	glLinkProgram(programId);
	CHECK_GL_ERROR;

	GLint linkStatus;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		GLint logLength;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			std::vector<char> errorMessage(logLength + 1);
			glGetProgramInfoLog(programId, logLength, NULL, &errorMessage[0]);
			LOG_ERROR("Unable to link program");
			LOG_ERROR("\t%s", &errorMessage[0]);
		}
	}

	for (uint32_t i = 0; i < static_cast<uint32_t>(Shader::ShaderType::MAX); ++i)
	{
		ShaderPtr shader = m_shaderProgram->GetShader(static_cast<Shader::ShaderType>(i));
		if (shader != nullptr)
		{
			Bindable& bindData = shader->GetBindable();
			glDetachShader(programId, bindData.GetBindingData());
			CHECK_GL_ERROR;
			glDeleteShader(bindData.GetBindingData());
			CHECK_GL_ERROR;
			bindData.SetBindState(Bindable::BindState::NotBound);
		}
	}

	for (auto uniform : m_shaderProgram->GetUniforms())
	{
		const std::string& name = uniform->GetName();
		GLuint uniformId = glGetUniformLocation(programId, name.c_str());
		CHECK_GL_ERROR;
		uniform->GetBindable().SetBindingData(uniformId);
		uniform->GetBindable().SetBindState(Bindable::BindState::Bound);
	}

	m_shaderProgram->GetBindable().SetBindingData(programId);
	m_shaderProgram->GetBindable().SetBindState(Bindable::BindState::Bound);
}
}  // namespace r
