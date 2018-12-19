#pragma once

#include "shader.h"
#include "uniform.h"

#include <vector>

namespace r
{
class ShaderProgram
{
public:
	ShaderProgram();

	bool SetShader(ShaderPtr shader);
	ShaderPtr GetShader(Shader::ShaderType type);

	UniformPtr CreateUniform(const std::string& name, const Uniform::Type type, const Uniform::Semantics semantics);
	const std::vector<UniformPtr> GetUniforms() const { return m_uniforms; }

	Bindable& GetBindable() { return m_bindable; }

private:
	Bindable m_bindable;
	ShaderPtr m_shaders[static_cast<uint32_t>(Shader::ShaderType::MAX)];
	std::vector<UniformPtr> m_uniforms;
};
}  // namespace r
