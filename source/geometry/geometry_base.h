#pragma once

#include "vertex_data_source_semantics.h"

#include "rendering/bindable.h"

#include <map>
#include <memory>

namespace r
{
class ElementDataSource;
using ElementDataSourcePtr = std::shared_ptr<ElementDataSource>;
class VertexDataSource;
using VertexDataSourcePtr = std::shared_ptr<VertexDataSource>;

/**
 * Base class for a geometry.
 * A geometry is composed of several vertex data sources
 * each with different semantics and an element data source.
 *
 * Vertex data sources are used to describe how a given
 * semantic vertex channel is read from the vertex buffer.
 * The element data source describes which type of primitives
 * are represented and how they are constructed from the vertex
 * buffer.
 *
 * The GeometryBase is an abstract class that does not
 * hold vertex data information. Instead concrete derived
 * classes are expected to hold a pointer to
 * a buffer holding vertex data.
 *
 * This way, different types of vertices can be used, while
 * the vertex data sources and element data source are used
 * to explain how a geometry is constructed from the vertex
 * buffer.
 *
 */
class GeometryBase
{
public:
	constexpr static int max_vertex_channels = VertexDataSourceSemantics::MAX_VERTEX_DATA_SOURCE_SEMANTICS;

public:
	/**
	 * Creates a geometry given a count of vertices, a map
	 * of vertex semantics to vertex data sources and an
	 * element data source.
	 *
	 * If the map does not contain a vertex data source for a
	 * given semantics, then that channel is set to nullptr.
	 */
	GeometryBase(const uint32_t &vertexCount, const std::size_t &vertexSize,
	             const std::map<VertexDataSourceSemantics, VertexDataSourcePtr> &dataSources,
	             ElementDataSourcePtr elements);
	virtual ~GeometryBase();

	/**
	 * Returns the number of vertices in the geometry.
	 */
	uint32_t GetVertexCount() const;
	/**
	 * Returns the size in bytes of the vertex buffer.
	 */
	std::size_t GetVertexBufferSizeInBytes() const;
	/**
	 * Returns the semantic data source for the given semantics.
	 */
	VertexDataSourcePtr GetVertexDataSourceForSemantics(const VertexDataSourceSemantics &s);
	/**
	 * Returns the element data source.
	 */
	ElementDataSourcePtr GetElementDataSource();

	/**
	 * Returns a pointer to the vertex buffer.
	 */
	virtual const void *GetVertexBufferData() const = 0;

	Bindable &GetVertexBufferBindable() { return m_glVertexBuffer; }
	Bindable &GetVertexArrayObjectBindable() { return m_glVertexArrayObject; }

protected:
	/// Number of vertices in the geometry.
	uint32_t mVertexCount;
	/// Size in bytes of a vertex;
	std::size_t m_vertexSize;
	/// The semantic vertex data sources.
	VertexDataSourcePtr mVertexDataSources[max_vertex_channels];
	/// The element data source, describing how primitives are created.
	ElementDataSourcePtr mElementDataSource;

	Bindable m_glVertexArrayObject;
	Bindable m_glVertexBuffer;

};  // class GeometryBase
}  // namespace r
