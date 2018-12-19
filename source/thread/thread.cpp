#include "thread.h"

#include <iostream>

namespace r
{
Thread::Thread() {}

Thread::~Thread() {}

void Thread::Start() { mThread = std::thread(Thread::dispatch, this); }

void Thread::Join() { mThread.join(); }

void *Thread::dispatch(void *ptr)
{
	if (!ptr)
	{
		return 0;
	}

	static_cast<Thread *>(ptr)->run();

	return 0;
}

}  // namespace r
