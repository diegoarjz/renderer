#include "model.h"

namespace r
{
Model::Model(GeometryBasePtr geometry, ShaderProgramPtr shaderProgram)
    : m_geometry(geometry), m_shaderProgram(shaderProgram), m_transformation()
{
}
}  // namespace r
