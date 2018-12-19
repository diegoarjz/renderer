#include "vertex.h"

namespace r
{
// clang-format off
const VertexDescription Vertex::description = {
    //                           Semantics, float, #comps,        bytes
    { VertexDataSourceSemantics::Position ,  true,      3,sizeof(float) },  // Position
    { VertexDataSourceSemantics::Normal   ,  true,      3,sizeof(float) }   // Normal
};
// clang-format on

bool operator==(const Vertex &v1, const Vertex &v2)
{
	return (v1.mPosition == v2.mPosition) && (v1.mNormal == v2.mNormal);
}

bool operator!=(const Vertex &v1, const Vertex &v2) { return !(v1 == v2); }
}  // namespace r
