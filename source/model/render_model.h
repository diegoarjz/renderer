#pragma once

#include "rendering/command.h"

#include <memory>

namespace r
{
class Model;
using ModelPtr = std::shared_ptr<Model>;

class RenderModel : public Command
{
public:
	void SetModel(ModelPtr model) { m_model = model; }
	ModelPtr GetModel() const { return m_model; }

	void Execute(Renderer *) override;

private:
	ModelPtr m_model;
};
}  // namespace r
