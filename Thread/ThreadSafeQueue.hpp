#pragma once
#if !defined(__THREAD_SAFE_QUEUE__)
#define __THREAD_SAFE_QUEUE__

#include "Lock.hpp"
#include <queue>

template <typename _Tx>
class CThreadSafeQueue
{
private:
	mutable CCriticalSection cs;
	std::queue<_Tx> queue;

public:
	void Enqueue(_Tx &item)
	{
		cs.enter();
		queue.push(item);
		cs.exit();
	}

	bool Dequeue(_Tx *out)
	{
		bool success = false;
		cs.enter();
		if (queue.size() > 0) {
			*out = queue.front();
			queue.pop();
			success = true;
		}
		cs.exit();
		return success;
	}

	size_t Size() const
	{
		size_t size = 0;
		cs.enter();
		queue.size();
		cs.exit();

		return size;
	}
};

#endif