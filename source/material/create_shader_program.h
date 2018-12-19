#pragma once

#include "rendering/command.h"

#include <memory>

namespace r
{
class ShaderProgram;
using ShaderProgramPtr = std::shared_ptr<ShaderProgram>;

class CreateShaderProgram : public Command
{
public:
	void SetShaderProgram(ShaderProgramPtr shaderProgram) { m_shaderProgram = shaderProgram; }
	ShaderProgramPtr GetShaderProgram() const { return m_shaderProgram; }

	void Execute(Renderer *) override;

private:
	ShaderProgramPtr m_shaderProgram;
};
}  // namespace r
