#pragma once

#include "vertex_data_source_semantics.h"

#include <cstdint>
#include <vector>

namespace r
{
/**
 * Describes a vertex channel in a vertex buffer.
 *
 * It indicates the semantics of a channel, whether the
 * channel has floating point components, the number of comonents
 * for each vertex and the size in bytes per component.
 */
struct VertexChannelDescription
{
	/// The semantics of a vertex channel.
	VertexDataSourceSemantics mSourceSemantics;
	/// Indicates if the channel components are floating point values.
	bool mIsFloat;
	/// Number of components per channel item.
	uint32_t mComponentCount;
	/// Number of bytes of each components.
	uint32_t mBytesPerComponent;
};

/**
 * Describes all channels in a vertex.
 */
typedef std::vector<VertexChannelDescription> VertexDescription;
}  // namespace r
