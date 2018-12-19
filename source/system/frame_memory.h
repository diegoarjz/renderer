#pragma once

#include <memory>

namespace r
{
class FrameMemory
{
public:
	explicit FrameMemory(const std::size_t &allocationSize);
	~FrameMemory();

	void *Allocate(const std::size_t &size);
	void Reset();
	void DeallocateAll();

	template<typename T>
	T *AllocateAs()
	{
		return static_cast<T *>(Allocate(sizeof(T)));
	}

private:
	struct Impl;
	std::unique_ptr<Impl> m_implementation;
};
}  // namespace r
