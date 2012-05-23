#ifndef _MEMORYHANDLE_H_
#define _MEMORYHANDLE_H_

#include "MemTypes.h"
#include "Assertion.h"

template <class T>
class MemoryHandle
{
public:

	MemoryHandle();
	explicit MemoryHandle( void* );

	~MemoryHandle();

	void operator=( const void* );
	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;

private:
	U32 HandleIndex;
	//TODO: add in ID to prevent stale object issue
};

//Singleton class that keeps track of all my memory handles addresses
class MemoryHandleTable
{
public:
	static MemoryHandleTable* Get();
	U32 FindEmptyTableEntry();
	void Init( U32 MaxHandleSpace );
	void SetIndex( U32 index, void* ALlocation );
	void* GetIndex( U32 Index );
protected:
	MemoryHandleTable() : Table() {};
	~MemoryHandleTable() {};
	MemoryHandleTable(const MemoryHandleTable&);                 // Prevent copy-construction
	MemoryHandleTable& operator=(const MemoryHandleTable&);
private:
	static MemoryHandleTable* _Instance;
	void** Table;
	U32 TableSize;
};

MemoryHandleTable* MemoryHandleTable::_Instance = NULL;

MemoryHandleTable* MemoryHandleTable::Get()
{
	if( _Instance == NULL )
	{
		_Instance = new MemoryHandleTable();
	}
	return _Instance;
}

void MemoryHandleTable::Init( U32 MaxHandleSpace )
{
	ASSERT( Table == NULL );

	//The trailing parenthesis initialises the members to be NULL
	Table = new void*[ MaxHandleSpace ]();
	TableSize = MaxHandleSpace;
}

U32 MemoryHandleTable::FindEmptyTableEntry()
{
	ASSERT( Table != NULL );

	for( U32 Iter = 0; Iter < TableSize; Iter++ )
	{
		//TODO: Find another way to keep track of empty indexes
		//At the moment if a handle is created but not assigned anything you can get double allocations on that index
		//Also if the value the index points to is set to NULL it could be prematurely recycled
		if( Table[ Iter ] == NULL )
		{
			return Iter;
		}
	}

	return -1;
}

void MemoryHandleTable::SetIndex( U32 Index, void* Allocation )
{
	ASSERT( Table != NULL );
	ASSERT( Index < TableSize );

	Table[ Index ] = Allocation;
}

void* MemoryHandleTable::GetIndex( U32 Index )
{
	ASSERT( Table != NULL );
	ASSERT( Index < TableSize );

	return Table[ Index ];
}



template <class T>
MemoryHandle< T >::MemoryHandle()
{
	HandleIndex = MemoryHandleTable::Get()->FindEmptyTableEntry();

	ASSERT( HandleIndex > 0 );
}

template <class T>
MemoryHandle< T >::MemoryHandle( void* Allocation )
{
	MemoryHandleTable* Handles = MemoryHandleTable::Get();

	HandleIndex = Handles->FindEmptyTableEntry();

	ASSERT( HandleIndex > 0 );

	Handles->SetIndex( HandleIndex, Allocation );
}

template <class T>
MemoryHandle<T>::~MemoryHandle()
{
	MemoryHandleTable::Get()->SetIndex( HandleIndex, NULL );
}

template <class T>
void MemoryHandle< T >::operator=( const void* Allocation )
{
	MemoryHandleTable::Get()->SetIndex( HandleIndex, Allocation );
}

#endif

//T* operator->() {
//        return ptr;
//    }
//
//    // const version, returns a pointer-to-const instead of just a pointer to
//    // enforce the idea of the logical constness of this object 
//    const T* operator->() const {
//        return ptr;
//    }
//
//    T& operator*() {
//        return *ptr;
//    }
//
//    // const version, returns a const reference instead of just a reference
//    // to enforce the idea of the logical constness of this object
//    const T& operator*() const {
//        return *ptr;
//    }