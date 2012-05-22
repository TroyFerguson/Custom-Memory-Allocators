#ifndef _MEMORYHANDLE_H_
#define _MEMORYHANDLE_H_

#include "MemTypes.h"

template <class T>
class MemoryHandle
{
public:

	MemoryHandle();
	MemoryHandle( void* );

	void operator=( const void* );
	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;

private:
	U32 HandleIndex;
	//TODO: add in ID to prevent stale object issue
};

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