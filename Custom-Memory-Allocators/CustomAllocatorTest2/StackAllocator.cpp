#include "StackAllocator.h"
#include "MemTypes.h"
#include "Assertion.h"
#include <stdlib.h>
#include <stdio.h>

StackAllocator::StackAllocator( U32 StackSize ) : StackSize( StackSize )
{
	Memory = malloc( StackSize );

	ASSERT(Memory != NULL);

	CurrentMarker = (U32)Memory;
}

void* StackAllocator::Alloc( U32 AllocSize )
{
	if( ( ( CurrentMarker - (U32)Memory ) + AllocSize ) > StackSize )
	{
		return NULL;
	}

	void* MemBlock = (void*)CurrentMarker;

	CurrentMarker += AllocSize;

	return MemBlock;
}

StackAllocator::Marker StackAllocator::GetMarker()
{
	return CurrentMarker;
}

void StackAllocator::FreeToMarker( StackAllocator::Marker OldMarker )
{
	//TODO: Add checking to make sure the marker is within the right bounds
	//to avoid memory corruption and breaking the allocator
	CurrentMarker = OldMarker;
}

void StackAllocator::Clear()
{
	CurrentMarker = (U32)Memory;
}

void StackAllocator::PrintUsage()
{
	printf( "Useage of StackAllocator %x \n", this );
	printf( "\t %i bytes used of %i (~%.2f%%)\n", ( CurrentMarker - (U32)Memory ), StackSize, (float)( ( CurrentMarker - (U32)Memory ) / (float)StackSize ) );
}