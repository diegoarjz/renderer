#include "command_list.h"
#include "system/frame_memory.h"

#include "geometry/load_geometry.h"
#include "geometry/render_geometry.h"

#include <GL/glew.h>

namespace r
{
CommandList::CommandList(FrameMemoryPtr frameMemory)
    : m_frameMemory(frameMemory), m_head(nullptr), m_tail(nullptr), m_next(nullptr)
{
}

CommandList::~CommandList()
{
	Command* tail = GetTail();
	if (tail != nullptr)
	{
		tail->SetNext(nullptr);
	}
	Command* head = GetHead();
	if (head != nullptr)
	{
		head->SetPrev(nullptr);
	}

	Command* current = m_head;
	while (current != nullptr)
	{
		Command* command = current;
		current = current->GetNext();
		delete command;
	}
}

}  // namespace r
