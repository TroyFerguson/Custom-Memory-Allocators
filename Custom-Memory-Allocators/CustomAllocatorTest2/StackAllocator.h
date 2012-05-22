#ifndef _STACKALLOCATOR_H_
#define _STACKALLOCATOR_H_

#include "MemTypes.h"

class StackAllocator
{
public:
	//Defines a stack marker that you can use to roll back allocations to a previously set point
	typedef U32 Marker;

	//Constructor that takes the number of bytes to allocate for this allocator
	explicit StackAllocator( U32 StackSize );

	//Allocates memory from the top of the stack of the given size
	virtual void* Alloc( U32 AllocSize );

	//Returns a marker, marking the current position of the stack
	Marker GetMarker();

	//Rolls back to the position of the marker passed in
	void FreeToMarker( Marker OldMarker );

	//rolls back the entire stack
	void Clear();

	/** Debugging functions */
	virtual void PrintUsage();

protected:
	void* Memory;
	Marker CurrentMarker;
	U32 StackSize;
};

#endif