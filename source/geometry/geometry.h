#pragma once

#include "geometry_base.h"

namespace r
{
class ElementDataSource;
using ElementDataSourcePtr = std::shared_ptr<ElementDataSource>;
class VertexDataSource;
using VertexDataSourcePtr = std::shared_ptr<VertexDataSource>;

/**
 * Implements a templated GeometryBase class that is templated on
 * the type of vertex buffer.
 * This is a concrete class derived from the GeometryBase class.
 *
 * Each instance owns a vertex buffer of the type defined in the
 * template. This buffer is copied from the user specified buffer
 * in the constructor and is deleted during destruction.
 */
template<typename V>
class CustomGeometry : public GeometryBase
{
private:
	/// The vertex buffer.
	V *mVertices;

public:
	/**
	 * Constructs a CustomGeometry from the given vertex buffer
	 * the vertex count, vertex data sources and element data
	 * source.
	 *
	 * The constructor copies the vertex buffer, not taking
	 * ownership of the original one. Therefore, the client
	 * can delete the original buffer.
	 */
	CustomGeometry(V *vertices, const uint32_t &vertexCount,
	               const std::map<VertexDataSourceSemantics, VertexDataSourcePtr> &dataSources,
	               ElementDataSourcePtr elements)
	    : GeometryBase(vertexCount, sizeof(V), dataSources, elements)
	{
		mVertices = new V[vertexCount * sizeof(V)];
		memcpy(mVertices, vertices, vertexCount * sizeof(V));
	}

	virtual ~CustomGeometry() { delete[] mVertices; }

	/**
	 * Returns the pointer to the vertex buffer
	 */
	const V *GetVertices() const { return mVertices; }

	/**
	 * Returns a void pointer to the vertex buffer data.
	 */
	const void *GetVertexBufferData() const override { return (void *)mVertices; }
};  // class Geometry
}  // namespace r
