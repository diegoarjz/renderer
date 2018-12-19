#pragma once

#include "rendering/command.h"

#include <memory>

namespace r
{
class Shader;
using ShaderPtr = std::shared_ptr<Shader>;

class CompileShader : public Command
{
public:
	CompileShader() {}

	void SetShader(ShaderPtr shader) { m_shader = shader; }
	ShaderPtr GetShader() const { return m_shader; }

	void Execute(Renderer *) override;

private:
	ShaderPtr m_shader;
};
}  // namespace r
