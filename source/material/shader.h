#pragma once

#include "rendering/bindable.h"

#include <string>

namespace r
{
class Shader
{
public:
	enum class ShaderType
	{
		Vertex,
		Fragment,
		MAX
	};

	Shader(ShaderType type);

	void SetShaderSource(const std::string& source) { m_shaderSource = source; }
	const std::string& GetShaderSource() { return m_shaderSource; }
	ShaderType GetType() const { return m_shaderType; }

	Bindable& GetBindable() { return m_bindable; }

private:
	std::string m_shaderSource;
	Bindable m_bindable;
	ShaderType m_shaderType;
};

using ShaderPtr = std::shared_ptr<Shader>;
}  // namespace r
