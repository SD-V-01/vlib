////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   mem.cpp
//  Version:     v1.00
//  Created:     03/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "mem.h"
#include "base_types.h"

#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
#include "mimalloc.h"

#endif

void* valloc(st Size){
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC //NOTE(V): Mimalloc
	return mi_malloc(Size);
	#endif

}

void vfree(void* Size) {
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
	mi_free(Size);
	#endif

}

void* vrealloc(void* Ptr, st NewSize) {
	//    STUB(V): Implement
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
	return mi_realloc(Ptr, NewSize);
	#endif

}

void* vcalloc(st size, st count){
	//    STUB(V): Implement
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
	return mi_calloc(size, count);
	#endif
}

void* dalloc(size_t size){
	return valloc(size);

}

void* dcalloc(size_t size, size_t count){
	return vcalloc(size, count);

}

void* drealloc(void* p, size_t new_size){
	return vrealloc(p, new_size);

}

void dfree(void* p){
	vfree(p);
}

extern "C" {
	//    This is a fuck you to the compiler that insist t think that dcpy should be replaced with the crt's memcpy even thow there is no crt ??
	//    NOTE(V): I really hate modern compilers sometimes, they really suck sometimes
	void* memcpy(void* Dest, const void* Source, size_t Size) {
		return vcpy(Dest, Source, Size);

	}

//    NOTE(V): I really hate modern compilers
	void * memset( void * pointer, int value, size_t count ){
		return vset(pointer, value, count);

	}

}

void* dcpy(void* Dest, const void* Source, size_t Size) {
	return vcpy(Dest, Source, Size);

}

void* vc(const void* Source, void* Dest, st Size) {
	return vcpy(Dest, Source, Size);

}

void* vcpy(void* Dest, const void* Source, size_t Size) {
    size_t i;

    if ((uintptr_t) Dest % sizeof(long) == 0 && (uintptr_t) Source % sizeof(long) == 0 && Size % sizeof(long) == 0) {
        long* DIt = (long*)Dest;
        const long* SIt = (const long*)Source;

        for (i = 0; i < Size / sizeof(long); i++) {
            DIt[i] = SIt[i];

        }

    }
    else {
        char* DIt = (char*)Dest;
        const char* SIt = (const char*)Source;

        for (i = 0; i < Size; i++) {
            DIt[i] = SIt[i];

        }

    }

    return Dest;

}

void* vset(void* Target, u8 Value, size_t Size) {
    unsigned char *ptr = (unsigned char*)Target;
    while (Size-- > 0)
        *ptr++ = Value;
    return Target;

}

void* vmove(void* Dest, const void* Source, size_t Size) {
    char* DIt = (char*)Dest;
    const char* SIt = (const char*)Source;

    if (DIt < SIt) {
        while (Size--) {
            *DIt++ = *SIt++;

        }

    }
    else {
        char* LastS = (char*)SIt + (Size - 1);
        char* LastD = DIt + (Size - 1);

        while (Size--) {
            *LastD-- = *LastS--;

        }

    }

    return Dest;

}

u32 dpow2(u32 In) {
    In--;
    In |= In >> 1;
    In |= In >> 2;
    In |= In >> 4;
    In |= In >> 8;
    In |= In >> 16;
    In++;
    return In;

}
