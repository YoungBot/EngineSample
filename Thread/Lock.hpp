#pragma once
#if !defined(__LOCK__)
#define __LOCK__
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class CCriticalSection
{
private:
	CRITICAL_SECTION cs;

public:
	CCriticalSection()
	{
		::InitializeCriticalSection(&cs);
	}

	void enter()
	{
		::EnterCriticalSection(&cs);
	}

	void exit()
	{
		::LeaveCriticalSection(&cs);
	}
};

#endif