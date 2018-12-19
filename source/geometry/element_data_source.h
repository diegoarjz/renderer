#pragma once

#include "rendering/bindable.h"

#include <cstdint>

namespace r
{
/**
 * Types of primitives that can be defined by a ElementDataSource.
 */
enum PrimitiveType
{
	Triangles,
	TriangleStrip,
};  // enum PrimitiveType

/**
 * Describes how vertices are combined into renderable primitives.
 *
 * The ElementDataSource contains a buffer of indices a vertex buffer.
 * Together with the primitive type it is, then, possible to describe
 * how primitives are put together from a buffer of vertices.
 *
 * Each ElementDataSource owns a buffer of indices that is copied from
 * a user specified buffer during construction. This buffer is deleted
 * during destruction. Therefore, the original buffer can be deleted
 * if the user desires.
 */
class ElementDataSource
{
public:
	/**
	 * Constructor taking an array of elements, the type of primitives,
	 * the number of primitives and the number of elements.
	 *
	 * Creates a copy of the array of elements. The passed array can, then,
	 * be safely deleted outside.
	 */
	ElementDataSource(const uint32_t *elements, const PrimitiveType &primitiveType, const uint32_t &primitiveCount,
	                  const uint32_t &elementCount);
	/**
	 * Deletes the index buffer.
	 */
	~ElementDataSource();

	/**
	 * Returns a pointer to the index buffer.
	 */
	const uint32_t *GetElements() const;
	/**
	 * Returns the type of primitives constructed.
	 */
	PrimitiveType GetPrimitiveType() const;
	/**
	 * Returns the number of primiives to be created.
	 */
	uint32_t GetPrimitiveCount() const;
	/**
	 * Returns the number of elements in the index buffer.
	 */
	uint32_t GetElementsCount() const;
	/**
	 * Returns the size in bytes of the index buffer.
	 */
	uint32_t GetSizeInBytes() const;
	/**
	 * Returns the gl binding data for the element buffer.
	 */
	Bindable &GetBindingData() { return m_glElementBuffer; }

private:
	uint32_t *mElements;           ///< Array of elements.
	PrimitiveType mPrimitiveType;  ///< The type of primitive.
	uint32_t mPrimitiveCount;      ///< Total number of primitives
	uint32_t mElementsCount;       ///< Total number of elements.
	Bindable m_glElementBuffer;
};  // class ElementDataSource
}  // namespace r
