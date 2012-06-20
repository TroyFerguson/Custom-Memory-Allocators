#ifndef _MEMORYHANDLE_H_
#define _MEMORYHANDLE_H_

#include "MemTypes.h"
#include "Assertion.h"
#include "MemoryHandleTable.h"

template <class T>
class MemoryHandle
{
public:

	MemoryHandle();
	explicit MemoryHandle( void* );

	~MemoryHandle();

	void operator=( const void* );
	//TODO: Check that the following can't accidentally bypass the
	//		memory handles internal process (which I think they do)
	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;

private:
	U32 HandleIndex;

	//A unique ID to avoid stale handles
	U32 ID;

	/** Using a static variable to ensure uniqueness across 
		all handle instances
	*/
	static U32 CurrentID;
};

template <class T>
U32 MemoryHandle< T >::CurrentID = 0;

template <class T>
MemoryHandle< T >::MemoryHandle()
{
	HandleIndex = MemTable->FindEmptyTableIndex();

	ASSERT( HandleIndex > 0 );
}

template <class T>
MemoryHandle< T >::MemoryHandle( void* Allocation )
{
	HandleIndex = MemTable->FindEmptyTableIndex();

	ASSERT( HandleIndex > 0 );

	MemTable->SetIndex( HandleIndex, Allocation );
}

template <class T>
MemoryHandle<T>::~MemoryHandle()
{
	MemTable->SetObject( HandleIndex, NULL );
}

template <class T>
void MemoryHandle< T >::operator=( const void* Allocation )
{
	MemTable->SetObject( HandleIndex, Allocation );
}

template <class T>
T* MemoryHandle< T >::operator->()
{
	//TODO: Add a check for stale handles
	return MemTable->GetObject( HandleIndex );
}

template <class T>
const T* MemoryHandle< T >::operator->() const
{
	return operator->();
}

template <class T>
T& MemoryHandle< T >::operator*()
{
	//TODO: Add check for stale handles
	return *MemTable->GetObject( HandleIndex );
}

template <class T>
const T& MemoryHandle< T >::operator*() const
{
	return operator*();
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