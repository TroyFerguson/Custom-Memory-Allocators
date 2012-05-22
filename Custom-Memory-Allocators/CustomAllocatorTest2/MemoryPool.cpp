#include <string>
#include <iostream>
#include "MemoryPool.h"

MemoryPool::MemoryPool( std::size_t PoolSize, unsigned int MaxAllocations ) : TotalPoolSize( PoolSize ), UsedMemory( 0 ), MaxAllocations( MaxAllocations )
{
	Memory = malloc( PoolSize );
	StartNode = ( SMemoryChunk* )malloc( MaxAllocations * sizeof( SMemoryChunk ) );
}

MemoryPool::~MemoryPool()
{
	free( Memory );
	free( StartNode );
}

SMemoryChunk* MemoryPool::GetMemory( std::size_t AllocationSize )
{
	//check to see if there is enough memory left
	if( UsedMemory + AllocationSize > TotalPoolSize )
	{
		return NULL;
	}

	//create new allocation 
	SMemoryChunk* NewAllocation = ++LastNode;
	NewAllocation->DataSize = AllocationSize;
	NewAllocation->IsAllocated = true;
	//assign chunk of Memory to the new allocation
	NewAllocation->Data = ( ( ( char* )Memory ) + UsedMemory );
	UsedMemory += AllocationSize;
	//return the new allocation
	return NewAllocation;
}