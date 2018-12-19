#include "auto_reset_event.h"

namespace r
{
AutoResetEvent::AutoResetEvent() { mSignalled = false; }

void AutoResetEvent::Notify()
{
	mSignalled = true;
	m_condition.notify_one();
}

void AutoResetEvent::Wait()
{
	if (!mSignalled)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_condition.wait(lock, [this] { return this->mSignalled; });
	}
	mSignalled = false;
}

}  // namespace r
