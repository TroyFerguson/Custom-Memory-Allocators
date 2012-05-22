#ifndef _MEMORY_POOL_H
#define _MEMORY_POOL_H

#include <string>

#define _DEBUG_MEMORY 1

struct SMemoryChunk
{
	bool IsAllocated;

	void* Data;
	void** Handle; //pointer to the eventual pointer that the user should be using, useful for defreagging the memory allocations
	std::size_t DataSize;
	
	SMemoryChunk* Next;
#if _DEBUG_MEMORY
	unsigned int Line; //The line number of this allocation
	std::string File; //The file name of this allocation
#endif

};

class MemoryPool
{
private:
	void* Memory;
	std::size_t TotalPoolSize;
	std::size_t UsedMemory;

	unsigned int MaxAllocations;

	SMemoryChunk* StartNode;
	SMemoryChunk* LastNode;

public:
	MemoryPool( std::size_t, unsigned int );
	~MemoryPool();

	SMemoryChunk* GetMemory( std::size_t );
	void FreeMemory( SMemoryChunk* );

};

#endif