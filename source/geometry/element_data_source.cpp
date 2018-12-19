#include "element_data_source.h"

#include <cstring>

namespace r
{
ElementDataSource::ElementDataSource(const uint32_t *elements, const PrimitiveType &primitiveType,
                                     const uint32_t &primitiveCount, const uint32_t &elementCount)
    : m_glElementBuffer(Bindable::BindableType::ElementBuffer),
      mPrimitiveType(primitiveType),
      mPrimitiveCount(primitiveCount),
      mElementsCount(elementCount)
{
	mElements = new uint32_t[elementCount * sizeof(uint32_t)];
	memcpy(mElements, elements, elementCount * sizeof(uint32_t));
}

ElementDataSource::~ElementDataSource() { delete[] mElements; }

/* ******************
 * Getters & Setters *
 * ******************/
const uint32_t *ElementDataSource::GetElements() const { return mElements; }

PrimitiveType ElementDataSource::GetPrimitiveType() const { return mPrimitiveType; }

uint32_t ElementDataSource::GetPrimitiveCount() const { return mPrimitiveCount; }

uint32_t ElementDataSource::GetElementsCount() const { return mElementsCount; }

uint32_t ElementDataSource::GetSizeInBytes() const { return mElementsCount * sizeof(uint32_t); }
}  // namespace r
