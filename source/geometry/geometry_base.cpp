#include "geometry_base.h"

#include "element_data_source.h"
#include "vertex_data_source.h"

namespace r
{
GeometryBase::GeometryBase(const uint32_t &vertexCount, const std::size_t &vertexSize,
                           const std::map<VertexDataSourceSemantics, VertexDataSourcePtr> &dataSources,
                           ElementDataSourcePtr elements)
    : mVertexCount(vertexCount),
      m_vertexSize(vertexSize),
      m_glVertexArrayObject(Bindable::BindableType::VertexArrayBuffer),
      m_glVertexBuffer(Bindable::BindableType::VertexBuffer)
{
	// Set every position in the vertex data source array to nullptr
	memset(mVertexDataSources, 0, sizeof(VertexDataSourcePtr) * max_vertex_channels);
	// For each of the vertex data sources in the map,
	// set its corresponding position in the vertex
	// data source array
	for (auto ds : dataSources)
	{
		mVertexDataSources[static_cast<int>(ds.first)] = ds.second;
	}

	mElementDataSource = elements;
}

GeometryBase::~GeometryBase() {}

uint32_t GeometryBase::GetVertexCount() const { return mVertexCount; }
std::size_t GeometryBase::GetVertexBufferSizeInBytes() const { return mVertexCount * m_vertexSize; }

VertexDataSourcePtr GeometryBase::GetVertexDataSourceForSemantics(const VertexDataSourceSemantics &s)
{
	return mVertexDataSources[s];
}

ElementDataSourcePtr GeometryBase::GetElementDataSource() { return mElementDataSource; }
}  // namespace r
