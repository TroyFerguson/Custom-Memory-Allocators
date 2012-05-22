#ifndef _DOUBLEENDEDSTACKALLOCATOR_H_
#define _DOUBLEENDEDSTACKALLOCATOR_H_

#include "MemTypes.h"
#include "StackAllocator.h"

class DoubleEndedStackAllocator : public StackAllocator
{
public:
	//Constructor that takes the number of bytes to allocate for this allocator
	explicit DoubleEndedStackAllocator( U32 StackSize );

	//Allocates a chunk of memory from the start of the allocators memory block
	virtual void* Alloc( U32 AllocSize );

	//Allocates a chunk of memory from the start of the allocators memory block
	void* AllocFromEnd( U32 AllocSize );

	//Returns a marker, marking the current position of the allocations from the 
	//end of the memory block
	Marker GetEndMarker();

	//Rolls back the end of the allocator to a specified marker
	void FreeEndToMarker( Marker OldMarker );

	//Clears all of the allocations made from the end of the allocator
	void ClearEnd();

	//Prints the current memory usage of the allocator
	virtual void PrintUsage();

private:
	Marker CurrentEndMarker;
};

#endif