//==========================================================
//OverrideNew.cpp
//==========================================================

#include "OverrideNew.hpp"
#include "Engine/Utility/Utility.hpp"
#include "Engine/Console/Console.hpp"
#include <map>
#include <malloc.h>
#undef new

struct MemoryData
{
	char const* m_file;
	size_t m_line;
	size_t m_size;
	MemoryData(char const* file, size_t line, size_t size)
		:m_file(file)
		, m_line(line)
		, m_size(size)
	{

	}
};

struct MemoryDataLink
{
	MemoryData* m_data;
	MemoryDataLink* m_parent;
	MemoryDataLink* m_child;
	MemoryDataLink(MemoryData* data, MemoryDataLink* parent)
		:m_child(nullptr)
	{
		m_data = data; 
		m_parent = parent; 
	}
};
static MemoryDataLink s_AllocationTrackerList = MemoryDataLink(nullptr,nullptr);
static std::map < void*, MemoryData > s_AllocationTracker;

//a.total number of allocations requested
//b.total bytes allocated
//c.largest allocation requested
//d.average allocation requested

unsigned int GetTotalNumberOfAllocations()
{
	return s_AllocationTracker.size();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

size_t GetTotalNumberOfBytesAllocated()
{
	size_t outputSize = 0;
	for (std::map < void*, MemoryData >::iterator allocationTrackerIter = s_AllocationTracker.begin(); allocationTrackerIter != s_AllocationTracker.end(); ++allocationTrackerIter)
	{
		size_t currentAllocationSize = allocationTrackerIter->second.m_size;
		outputSize += currentAllocationSize;
	}
	return outputSize;
}
///----------------------------------------------------------
///
///----------------------------------------------------------
size_t GetLagerestBytesAllocated()
{
	size_t lagerestSize = 0;
	for (std::map < void*, MemoryData >::iterator allocationTrackerIter = s_AllocationTracker.begin(); allocationTrackerIter != s_AllocationTracker.end(); ++allocationTrackerIter)
	{
		size_t currentAllocationSize = allocationTrackerIter->second.m_size;
		if (currentAllocationSize>lagerestSize)
		{
			lagerestSize = currentAllocationSize;
		}
	}
	return lagerestSize;
}
///----------------------------------------------------------
///
///----------------------------------------------------------
size_t GetAverageBytesAllocated()
{
	size_t totalBytes = GetTotalNumberOfBytesAllocated();
	return totalBytes / s_AllocationTracker.size();
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void TrackAllocation(void* ptr, char const* file, size_t line, size_t size)
{
	if (line ==0)
		return;
	MemoryData newData =MemoryData(file, line, size);
	s_AllocationTracker.insert(std::pair<void*,MemoryData>(ptr, newData));
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void UntrackAllocation(void* ptr)
{
	if (s_AllocationTracker.size()==0)
	{
		return;
	}
	std::map < void*, MemoryData >::iterator memIter = s_AllocationTracker.find(ptr);
	if (memIter != s_AllocationTracker.end())
		s_AllocationTracker.erase(memIter);
	//else
	//	FATAL_ERROR("Untrack allocation Failed.");
}
///----------------------------------------------------------
///
///----------------------------------------------------------
void CheckMemoryLeak()
{
	std::string log;
	for (std::map < void*, MemoryData >::iterator allocationTrackerIter = s_AllocationTracker.begin(); allocationTrackerIter != s_AllocationTracker.end(); ++allocationTrackerIter)
	{
		std::string fileName = allocationTrackerIter->second.m_file;
		std::string lineNumber = std::to_string(allocationTrackerIter->second.m_line);
		std::string sizeByte = std::to_string(allocationTrackerIter->second.m_size);
		log += "Memory leak of ";
		log += sizeByte;
		log += " bytes, allocated on line ";
		log += lineNumber;
		log += " of ";
		log += fileName;
		log += "\n\r";		
	}
	LogPrintf(log.c_str());
	
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void* operator new(size_t size, char const* file, size_t line)
{
	void *ptr = malloc(size);
	TrackAllocation(ptr, file, line, size);
	return ptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void operator delete (void *ptr, char const *file, size_t line)
{
	file;
	line;
	free(ptr);
	UntrackAllocation(ptr);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

//void* operator new (size_t size, void* buffer)
//{
//	return buffer;
//}
/////----------------------------------------------------------
/////
/////----------------------------------------------------------
//
//void operator delete(void* ptr, void* buffer)
//{
//
//}
///----------------------------------------------------------
///
///----------------------------------------------------------

void* operator new (size_t size)
{
	void *ptr = malloc(size);
	//TrackAllocation(ptr, "", 0, size);
	return ptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void operator delete(void *ptr)
{
	free(ptr);
	UntrackAllocation(ptr);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void* operator new[](size_t size, char const *file, size_t line)
{
	void* ptr = malloc(size);
	TrackAllocation(ptr, file, line, size);
	return ptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void operator delete[](void* ptr, char const *file, size_t line)
{
	file;
	line;
	free(ptr);
	UntrackAllocation(ptr);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

//void* operator new[](size_t size, void* buffer)
//{
//	return buffer;
//}
/////----------------------------------------------------------
/////
/////----------------------------------------------------------
//
//void operator delete[](void* ptr, void* buffer)
//{
//
//}
///----------------------------------------------------------
///
///----------------------------------------------------------

void* operator new[](size_t size)
{
	void *ptr = malloc(size);
	TrackAllocation(ptr, "", 0, size);
	return ptr;
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void operator delete[](void *ptr)
{
	free(ptr);
	UntrackAllocation(ptr);
}
///----------------------------------------------------------
///
///----------------------------------------------------------

void MemoryLeakCheckConsolePrint()
{
	if (s_AllocationTracker.size() > 0)
	{
		for (std::map < void*, MemoryData >::iterator allocationTrackerIter = s_AllocationTracker.begin(); allocationTrackerIter != s_AllocationTracker.end(); ++allocationTrackerIter)
		{
			std::string log = "";
			std::string fileName = allocationTrackerIter->second.m_file;
			std::string lineNumber = std::to_string(allocationTrackerIter->second.m_line);
			std::string sizeByte = std::to_string(allocationTrackerIter->second.m_size);
			log += fileName;
			log += "(";
			log += lineNumber;
			log += ")";
			log += " MEMORY LEAK. \n\r";
			OutputDebugStringA(log.c_str());
		}
	}

}




























































