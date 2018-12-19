#pragma once

namespace r
{
class Renderer;

class Command
{
public:
	Command();
	Command(const Command &) = delete;
	virtual ~Command();
	Command &operator=(const Command &) = delete;

	void SetNext(Command *c)
	{
		m_next = c;
		if (c != nullptr)
		{
			c->m_prev = this;
		}
	}

	void SetPrev(Command *c)
	{
		m_prev = c;
		if (c != nullptr)
		{
			c->m_next = this;
		}
	}

	Command *GetPrev() const { return m_prev; }
	Command *GetNext() const { return m_next; }

	virtual void Execute(Renderer *) = 0;

private:
	// CommandType m_type;
	Command *m_next;
	Command *m_prev;
};

}  // namespace r
