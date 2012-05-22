#include "DoubleEndedStackAllocator.h"
#include "MemTypes.h"
#include "Assertion.h"
#include <stdlib.h>
#include <stdio.h>

DoubleEndedStackAllocator::DoubleEndedStackAllocator( U32 StackSize )
	: StackAllocator( StackSize )
{
	CurrentEndMarker = ( (U32)Memory ) + StackSize;
}

void* DoubleEndedStackAllocator::Alloc( U32 AllocSize )
{
	if( ( CurrentMarker + AllocSize ) > CurrentEndMarker )
	{
		return NULL;
	}

	void* MemBlock = (void*)CurrentMarker;

	CurrentMarker += AllocSize;

	return MemBlock;
}

void* DoubleEndedStackAllocator::AllocFromEnd( U32 AllocSize )
{
	if( ( CurrentEndMarker - AllocSize ) < CurrentMarker )
	{
		return NULL;
	}

	CurrentEndMarker -= AllocSize;

	void* MemBlock = (void*)CurrentEndMarker;

	return MemBlock;
}

StackAllocator::Marker DoubleEndedStackAllocator::GetEndMarker()
{
	return CurrentEndMarker;
}

void DoubleEndedStackAllocator::FreeEndToMarker( StackAllocator::Marker OldMarker )
{
	//TODO: Add checking to make sure the marker is within the right bounds
	//to avoid memory corruption and breaking the allocator
	CurrentEndMarker = OldMarker;
}

void DoubleEndedStackAllocator::ClearEnd()
{
	CurrentEndMarker = ( (U32)Memory ) + StackSize;
}

void DoubleEndedStackAllocator::PrintUsage()
{
	U32 FrontAmountUsed, EndAmountUsed, TotalAmountUsed;

	FrontAmountUsed = ( CurrentMarker - (U32)Memory );
	EndAmountUsed = ( ( (U32)Memory + StackSize ) - CurrentEndMarker );
	TotalAmountUsed = FrontAmountUsed + EndAmountUsed;

	printf( "Useage of DoubleEndedStackAllocator %x \n", this );
	printf( "\t %i bytes used of %i (~%.2f%%)\n", TotalAmountUsed, StackSize, (float)( TotalAmountUsed / (float)StackSize ) );
	printf( "\t %i bytes allocated from front (~%.2f%%)\n", FrontAmountUsed, (float)( FrontAmountUsed / (float)TotalAmountUsed ) );
	printf( "\t %i bytes allocated from end (~%.2f%%)\n", EndAmountUsed, (float)( EndAmountUsed / (float)TotalAmountUsed ) );
}