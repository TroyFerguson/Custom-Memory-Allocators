#ifndef _MEMORYHANDLETABLE_H_
#define _MEMORYHANDLETABLE_H_

#include "MemTypes.h"
#include "Assertion.h"
#include <stdlib.h>

namespace
{
	class MemoryHandleTable
	{
	public:
		MemoryHandleTable( U32 TableSize ) : TableSize( TableSize )
		{
			AllocationTable = (bool*)malloc( sizeof( bool ) * TableSize );
			ASSERT( AllocationTable != NULL );

			MemoryTable = (void**)malloc( sizeof( void* ) * TableSize );
			ASSERT( MemoryTable != NULL );
		}

		/** Finds an unused entry in the memory table
		*	@return The index of the found entry else -1 if not found
		*/
		inline U32 FindEmptyTableIndex()
		{
			ASSERT( AllocationTable != NULL );
			ASSERT( MemoryTable != NULL );

			for( U32 iter = 0; iter < TableSize; iter++ )
			{
				if( !AllocationTable[ iter ] )
				{
					AllocationTable[ iter ] = true;
					return iter;
				}
			}

			return -1;
		}

		/** Assigns the value of an allocation in the memory table
		*	@param Index - The index of the allocation to set
		*	@param Allocation - The pointer to the object you are assigning 
		*/
		inline void SetObject( U32 Index, void* Allocation )
		{
			ASSERT( MemoryTable != NULL );
			ASSERT( Index < TableSize );

			MemoryTable[Index] = Allocation;
		}

		/** Retrieves the pointer at the given index
		*	@param Index - The index of the allocation to get
		*	@return The pointer to the object stored at the specified index 
		*/
		inline void* GetObject( U32 Index )
		{
			ASSERT( MemoryTable != NULL );
			ASSERT( Index < TableSize );

			return MemoryTable[Index];
		}
	private:
		/** A dynamic array that stores the pointers to the objects.
			The index of that element is then passed out to the memory 
			handles.
		*/
		void** MemoryTable;

		/** An array of bools that track which indexes in the memory 
			array have been allocated.
		*/
		bool* AllocationTable;

		/** The largest size for the tables.
		*/
		U32 TableSize;
	};

	/** This should probably be done using a define somewhere rather than 
		hard coding it, but for now it should be fine
	*/
	MemoryHandleTable* MemTable = new MemoryHandleTable( 1000 );
}

#endif