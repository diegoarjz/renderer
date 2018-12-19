#pragma once

#include "vertex_description.h"

#include <glm/glm.hpp>

namespace r
{
/**
 * Default Vertex.
 *
 * A vertex is made of several semantic channels.
 *
 * The  VertexDescription describes the elements of this vertex, its semantics,
 * number of components, size per component and wether each component is a
 * floating point value.
 * It can be used to create VertexDataSources, one for each semantic channel.
 * Channels can be made of several components, e.g., a Vector3 channel has
 * 3 components.
 */
class Vertex
{
public:
	static const VertexDescription description;  ///< Describes the vertex semantics

	glm::vec3 mPosition;  ///< The vertex position
	glm::vec3 mNormal;    ///< The vertex normal
};

bool operator==(const Vertex &v1, const Vertex &v2);
bool operator!=(const Vertex &v1, const Vertex &v2);
}  // namespace r
