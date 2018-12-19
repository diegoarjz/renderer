#include "frame_memory.h"

#include "common/logger.h"

namespace r
{
struct MemoryAllocation
{
	char *m_start;
	char *m_end;
	char *m_nextAddress;
	MemoryAllocation *m_prev;
	MemoryAllocation *m_next;
};

struct FrameMemory::Impl
{
public:
	explicit Impl(const std::size_t allocationSize)
	    : m_allocationsize(allocationSize), m_head(nullptr), m_current(nullptr), m_tail(nullptr)
	{
		LOG_TRACE(Memory, "Creating FrameMemory(0x%X) with allocation size of %d bytes", this, m_allocationsize);
	}

	~Impl() { DeallocateAll(); }

	void *Allocate(const std::size_t &size)
	{
		LOG_TRACE(Memory, "Allocating %d bytes from FrameMemory(0x%X)", size, this);

		if (size >= m_allocationsize)
		{
			LOG_ERROR("Requested allocation (%d bytes) is bigger than allowed allocation size (%d bytes).", size,
			          m_allocationsize);
			return nullptr;
		}

		// No allocations
		if (!m_head)
		{
			m_head = CreateNewAllocation(nullptr);
			if (!m_head)
			{
				return nullptr;
			}
			m_current = m_head;
			m_tail = m_head;
		}

		if (m_current->m_nextAddress + size >= m_current->m_end)
		{
			// Current Allocation is full
			if (m_current == m_tail)
			{
				// Current Allocation is the last one, create a new MemoryAllocation
				MemoryAllocation *alloc = CreateNewAllocation(m_tail);
				if (!alloc)
				{
					return nullptr;
				}
				m_tail = alloc;
				m_current = m_tail;
			}
			else
			{
				// Re use an existing MemoryAllocation
				m_current = m_current->m_next;
				m_current->m_nextAddress = m_current->m_start;
			}
		}

		char *address = m_current->m_nextAddress;
		m_current->m_nextAddress += size;

		LOG_TRACE(Memory, "\tNew Address: 0x%X bytes left: %d", address, (m_current->m_end - m_current->m_nextAddress));

		return address;
	}

	void Reset()
	{
		LOG_TRACE(Memory, "Resetting FrameMemory(0x%X)", this);
		m_current = m_head;
		if (m_current)
		{
			m_current->m_nextAddress = m_current->m_start;
		}
	}

	void DeallocateAll()
	{
		LOG_TRACE(Memory, "Deallocating all MemoryAllocation in FrameMemory(0x%X)", this);
		MemoryAllocation *current = m_head;
		while (current != nullptr)
		{
			LOG_TRACE(Memory, "\tDeleting MemoryAllocation 0x%X", current);
			delete[] current->m_start;
			MemoryAllocation *next = current->m_next;
			delete current;
			current = next;
		}
	}

private:
	MemoryAllocation *CreateNewAllocation(MemoryAllocation *previous)
	{
		LOG_TRACE(Memory, "Creating new allocation in FrameMemory(0x%X) with size %d bytes", this, m_allocationsize);
		LOG_TRACE(Memory, "\tPrevious MemoryAllocation: 0x%X", previous);
		MemoryAllocation *alloc = new MemoryAllocation;

		if (!alloc)
		{
			LOG_ERROR("Unable to allocate memory for MemoryAllocation");
			return nullptr;
		}

		alloc->m_start = new char[m_allocationsize];
		alloc->m_end = alloc->m_start + m_allocationsize;

		if (!alloc->m_start)
		{
			LOG_ERROR("Unable to allocate memory chunk for MemoryAllocation");
			delete alloc;
			return nullptr;
		}

		alloc->m_nextAddress = alloc->m_start;
		alloc->m_prev = previous;
		alloc->m_next = nullptr;

		if (previous)
		{
			previous->m_next = alloc;
		}

		LOG_TRACE(Memory, "\tNew MemoryAllocation: 0x%X", alloc->m_start);

		return alloc;
	}

	std::size_t m_allocationsize;

	MemoryAllocation *m_head;
	MemoryAllocation *m_current;
	MemoryAllocation *m_tail;
};

FrameMemory::FrameMemory(const std::size_t &allocationSize) : m_implementation(std::make_unique<Impl>(allocationSize))
{
}

FrameMemory::~FrameMemory() {}

void *FrameMemory::Allocate(const std::size_t &size) { return m_implementation->Allocate(size); }

void FrameMemory::Reset() { m_implementation->Reset(); }

void FrameMemory::DeallocateAll() { m_implementation->DeallocateAll(); }
}  // namespace r
