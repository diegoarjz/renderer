#pragma once

#include <thread>

namespace r
{
class Thread
{
public:
	Thread();
	virtual ~Thread();

	/**
	 * Starts the thread
	 */
	void Start();
	/**
	 * Waits for the thread to finish and joins the
	 * execution.
	 */
	void Join();

protected:
	/**
	 * Sub classes should implement this method
	 * for custom behaviour.
	 */
	virtual void run() = 0;

private:
	static void *dispatch(void *);

	std::thread mThread;

};  // class Thread

}  // namespace r
