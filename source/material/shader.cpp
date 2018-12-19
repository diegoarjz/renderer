#include "shader.h"

namespace r
{
Shader::Shader(ShaderType type) : m_bindable(Bindable::BindableType::Shader), m_shaderType(type) {}

}  // namespace r
