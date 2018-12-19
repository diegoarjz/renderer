#pragma once

#include <condition_variable>
#include <mutex>

namespace r
{
class AutoResetEvent
{
public:
	AutoResetEvent();

	void Notify();
	void Wait();

private:
	std::mutex m_mutex;
	std::condition_variable m_condition;
	bool mSignalled;
};  // class AutoResetEvent

}  // namespace r
