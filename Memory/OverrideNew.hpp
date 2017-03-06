//==========================================================
//OverrideNew.hpp
//==========================================================

unsigned int GetTotalNumberOfAllocations();
size_t GetTotalNumberOfBytesAllocated();
size_t GetLagerestBytesAllocated();
size_t GetAverageBytesAllocated();
void TrackAllocation(void* ptr, char const* file, size_t line, size_t size);
void UntrackAllocation(void* ptr);
void CheckMemoryLeak();
void MemoryLeakCheckConsolePrint();
void* operator new(size_t size, char const* file, size_t line);
void operator delete (void *ptr, char const *file, size_t line);
void* operator new[](size_t size, char const *file, size_t line);
void operator delete[](void* ptr, char const *file, size_t line);
void* operator new[](size_t size);
void operator delete[](void *ptr);
#define new new(__FILE__,__LINE__)