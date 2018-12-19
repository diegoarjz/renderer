#include "vertex_data_source.h"

namespace r
{
VertexDataSource::VertexDataSource()
    : mSemantics(VertexDataSourceSemantics::NULL_SEMANTICS), mIsFloat(false), mComponentCount(0), mOffset(0), mStride(0)
{
}

VertexDataSource::VertexDataSource(const VertexDataSourceSemantics &semantics, const bool &isFloat,
                                   const uint32_t &componentCount, const uint32_t &offset, const uint32_t &stride)
    : mSemantics(semantics), mIsFloat(isFloat), mComponentCount(componentCount), mOffset(offset), mStride(stride)
{
}

VertexDataSourceSemantics VertexDataSource::GetSemantics() const { return mSemantics; }

bool VertexDataSource::IsFloat() const { return mIsFloat; }

uint32_t VertexDataSource::GetComponentCount() const { return mComponentCount; }

uint32_t VertexDataSource::GetOffset() const { return mOffset; }

uint32_t VertexDataSource::GetStride() const { return mStride; }
}  // namespace r
