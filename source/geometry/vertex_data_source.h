#pragma once

#include "vertex_data_source_semantics.h"

#include <cstdint>

namespace r
{
/**
 * Indicates how a specific semantic channel of vertex data
 * (e.g., position or normals) should be read from a vertex buffer.
 */
class VertexDataSource
{
public:
	/**
	 * Constructs a vertex data source with a null semantics.
	 */
	VertexDataSource();
	/**
	 * Constructs the vertex data source with the given
	 * semantics and parameters.
	 */
	VertexDataSource(
	    /// The semantics for the data source
	    const VertexDataSourceSemantics &semantics,
	    /// If the data is float.
	    const bool &isFloat,
	    /// Number of components in each vertex.
	    const uint32_t &componentCount,
	    /// The offset within a vertex buffer
	    const uint32_t &offset,
	    /// The stride between elements in a vertex buffer
	    const uint32_t &stride);

	/**
	 * Returns the semantics of this data source.
	 */
	VertexDataSourceSemantics GetSemantics() const;
	/**
	 * Returns the number of vertices.
	 */
	uint32_t GetVertexCount() const;
	/**
	 * Returns wether the data in this data source
	 * is float or not.
	 */
	bool IsFloat() const;
	/**
	 * Returns the number of components per vertex.
	 */
	uint32_t GetComponentCount() const;
	/**
	 * Returns the offset in the data source.
	 */
	uint32_t GetOffset() const;
	/**
	 * Returns the stride in the vertex buffer.
	 */
	uint32_t GetStride() const;

private:
	/// The data source semantics.
	VertexDataSourceSemantics mSemantics;
	/// Indicates if the data source elements are floats.
	bool mIsFloat;
	/// The number of components per vertex.
	uint32_t mComponentCount;
	/// The offset within a vertex buffer
	uint32_t mOffset;
	/// The stride between elements in a vertex buffer.
	uint32_t mStride;

};  // class VertexDataSource
}  // namespace r
