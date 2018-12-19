#include "shader_program.h"

namespace r
{
ShaderProgram::ShaderProgram() : m_bindable(Bindable::BindableType::ShaderProgram)
{
	for (uint32_t i = 0; i < static_cast<uint32_t>(Shader::ShaderType::MAX); ++i)
	{
		m_shaders[i] = nullptr;
	}
}

bool ShaderProgram::SetShader(ShaderPtr shader)
{
	if (m_shaders[static_cast<uint32_t>(shader->GetType())] != nullptr)
	{
		return false;
	}

	m_shaders[static_cast<uint32_t>(shader->GetType())] = shader;

	return true;
}

ShaderPtr ShaderProgram::GetShader(Shader::ShaderType type) { return m_shaders[static_cast<uint32_t>(type)]; }

UniformPtr ShaderProgram::CreateUniform(const std::string& name, const Uniform::Type type,
                                        const Uniform::Semantics semantics)
{
	auto uniform = std::make_shared<Uniform>(name, type, semantics);
	m_uniforms.push_back(uniform);
	return uniform;
}
}  // namespace r
