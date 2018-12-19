#pragma once

#include "rendering/command.h"

#include <memory>

namespace r
{
class GeometryBase;
using GeometryBasePtr = std::shared_ptr<GeometryBase>;

class RenderGeometry : public Command
{
public:
	RenderGeometry() : Command(/*CommandType::RenderGeometry*/) {}

	void SetGeometry(GeometryBasePtr geometry) { m_geometry = geometry; }
	GeometryBasePtr GetGeometry() const { return m_geometry; }

	void Execute(Renderer *) override;

private:
	GeometryBasePtr m_geometry;
};
}  // namespace r
