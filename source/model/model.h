#pragma once

#include "transformations/transformation.h"

#include <memory>

namespace r
{
class GeometryBase;
using GeometryBasePtr = std::shared_ptr<GeometryBase>;
class ShaderProgram;
using ShaderProgramPtr = std::shared_ptr<ShaderProgram>;

class Model
{
public:
	Model(GeometryBasePtr geometry, ShaderProgramPtr shader);

	Transformation& GetTransformation() { return m_transformation; }
	const Transformation& GetTransformation() const { return m_transformation; }

	GeometryBasePtr GetGeometry() const { return m_geometry; }
	ShaderProgramPtr GetShaderProgram() const { return m_shaderProgram; }

private:
	GeometryBasePtr m_geometry;
	ShaderProgramPtr m_shaderProgram;
	Transformation m_transformation;
};

using ModelPtr = std::shared_ptr<Model>;
}  // namespace r
