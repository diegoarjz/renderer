#pragma once

#include "command.h"

#include <memory>

namespace r
{
class FrameMemory;
using FrameMemoryPtr = std::shared_ptr<FrameMemory>;

class CommandList
{
public:
	explicit CommandList(FrameMemoryPtr frameMemory);
	~CommandList();

	template<typename C>
	C *CreateCommand()
	{
		C *command = new C();
		if (m_head == nullptr)
		{
			m_head = command;
			m_tail = command;
		}
		else
		{
			m_tail->SetNext(command);
			m_tail = command;
		}

		return command;
	}

	void Reset()
	{
		m_head = nullptr;
		m_tail = nullptr;
	}

	Command *GetHead() { return m_head; }
	Command *GetTail() { return m_tail; }

private:
	FrameMemoryPtr m_frameMemory;
	Command *m_head;
	Command *m_tail;

	CommandList *m_next;
};  // class CommandList

using CommandListPtr = std::shared_ptr<CommandList>;

}  // namespace r
