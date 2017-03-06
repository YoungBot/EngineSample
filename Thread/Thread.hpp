//==========================================================
//Thread.hpp
//==========================================================
//


#pragma once
#if !defined(__MYTHREADS__)
#define __MYTHREADS____

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef void(*thread_entry_cb)(void *arg);

class CThread
{
	friend void ThreadClassEntry(void *arg);
private:
	HANDLE thread_handle;

	// disable copy constructor
	CThread(CThread const &other) = delete;
	bool m_deleteWhenFinished;

protected:
	virtual void Run() = 0;

	// Question:  Why make these protected?
	void yield();
	void Sleep(unsigned int ms);

public:
	CThread() { thread_handle = NULL; }

	bool Start(char const *name,bool deleteWhenFinished = false);
	void Detach();
	void Join();
};

HANDLE ThreadCreate(char const *name, thread_entry_cb entry, void *arg);

void ThreadDetach(HANDLE handle);
void ThreadJoin(HANDLE handle);

void ThreadYield();
void ThreadSleep(unsigned int ms);

DWORD ThreadGetCurrentID();
DWORD ThreadGetID(HANDLE handle);

#endif