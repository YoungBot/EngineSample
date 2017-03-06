#include "Engine/Time/Time.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

float g_secondsPerTick = 0.0f;

void InitializeTimer()
{
	LARGE_INTEGER ticksPerSecond;
	QueryPerformanceFrequency(&ticksPerSecond);
	g_secondsPerTick = 1.0f/ticksPerSecond.QuadPart;
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

double GetCurrentSeconds()
{
	LARGE_INTEGER ticksPerSecond;
	QueryPerformanceCounter(&ticksPerSecond);
	double currentSecond = ticksPerSecond.QuadPart *g_secondsPerTick;
	return currentSecond;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

uint64_t __fastcall TimeOpCountTo_us(uint64_t op_count)
{
	uint64_t f;
	QueryPerformanceFrequency((LARGE_INTEGER*)&f);
	if(f > 0)
	{
		op_count *= 1000 * 1000;
		op_count /= f;
		return(uint64_t)(op_count);

	}
	else
		return 0;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

uint64_t __fastcall TimeOpCountTo_ms(uint64_t op_count)
{
	uint64_t f;
	QueryPerformanceFrequency((LARGE_INTEGER*)&f);
	if (f > 0)
	{
		op_count *= 1000;
		op_count /= f;
		return(uint64_t)(op_count);

	}
	else
		return 0;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

uint64_t __fastcall TimeGetOpCount()
{
	LARGE_INTEGER ticksPerSecond;
	QueryPerformanceCounter(&ticksPerSecond);
	uint64_t currentSecond = ticksPerSecond.QuadPart;
	return (uint64_t)currentSecond;
}



