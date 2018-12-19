#include "compile_shader.h"

#include "shader.h"

#include "common/logger.h"
#include "rendering/gl_debug.h"

#include <GL/glew.h>

#include <vector>

namespace r
{
GLenum convert_shader_type(Shader::ShaderType type)
{
	switch (type)
	{
		case Shader::ShaderType::Vertex:
			return GL_VERTEX_SHADER;
		case Shader::ShaderType::Fragment:
			return GL_FRAGMENT_SHADER;
		default:
			return GL_VERTEX_SHADER;
	}
}

void CompileShader::Execute(Renderer*)
{
	Shader::ShaderType shaderType = m_shader->GetType();
	const char* shaderSource = m_shader->GetShaderSource().c_str();

	GLuint shaderId = glCreateShader(convert_shader_type(shaderType));
	CHECK_GL_ERROR;
	glShaderSource(shaderId, 1, &shaderSource, NULL);
	CHECK_GL_ERROR;
	glCompileShader(shaderId);
	CHECK_GL_ERROR;

	GLint compileStatus;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		GLint logLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> compilationLog(logLength + 1);
		glGetShaderInfoLog(shaderId, logLength, NULL, &compilationLog[0]);
		LOG_ERROR("Shader (0x%X) compilation failed:", m_shader.get());
		LOG_ERROR("%s", &compilationLog[0]);
	}

	m_shader->GetBindable().SetBindingData(shaderId);
	m_shader->GetBindable().SetBindState(Bindable::BindState::Bound);
}
}  // namespace r
