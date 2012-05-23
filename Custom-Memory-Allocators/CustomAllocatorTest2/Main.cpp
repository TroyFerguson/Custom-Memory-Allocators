#include <iostream>
#include <string>
#include "StackAllocator.h"
#include "DoubleEndedStackAllocator.h"
#include "MemoryHandle.h"

int main( int argc, char *argv[] )
{
	/*StackAllocator* SA = new StackAllocator( 1024 );

	SA->Alloc(100);
	SA->PrintUsage();

	DoubleEndedStackAllocator* DESA = new DoubleEndedStackAllocator( 1024 );
	DESA->Alloc( 100 );
	DESA->AllocFromEnd( 300 );
	DESA->PrintUsage();*/

	MemoryHandleTable::Get()->Init( 100 );

	MemoryHandle<int> intHandle;

	return 0;
}