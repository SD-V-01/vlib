////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   vsystemalloc.c
//  Version:     v1.00
//  Created:     08/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "vsystemalloc.h"

#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_SYSTEM
#include "stdlib.h"
#include "malloc.h"
#include "string.h"

#warning Building vlib with system allocator, not recomended for performance and consistency reasons

void* vsys_malloc(st Size){
	return malloc(Size);

}

void* vsys_calloc(st Size, st Count) {
	return calloc(Size, Count);

}

void* vsys_realloc(void* Ptr, st Size) {
	return realloc(Ptr, Size);

}

void vsys_free(void* Ptr) {
	free(Ptr);

}

void* vsys_aligned_malloc(st Size, st Alignment) {
	return aligned_alloc(Alignment, Size); // C11 aligned_alloc

}

static void *aligned_realloc(void *ptr, size_t align, size_t size) {
	if (!ptr) return aligned_alloc(align, size);

	// according to standard c in this line    char *x = malloc(77)
	// you can't access the 78th element
	// but that's not how real memory allocators work
	size_t usable = malloc_usable_size(ptr);
	if (!((uintptr_t)ptr & (align - 1))) {
		if (usable == size) return ptr;
		if (usable > size) {
			#ifdef MY_COMPILER_IS_AN_IDIOT
			// this is not needed for gcc/clang/icc/tcc/probably any compiler
			void *tmp = ptr;
			if (!(ptr = realloc(tmp, size))) return NULL;
			#ifdef MY_LIBC_IS_SHIT
			// this is not needed for any libc that supports malloc_usable_size
			if ((uintptr_t) ptr & (align - 1))
			#endif
			#endif
			return ptr;
		}
	}

	void *newptr = aligned_alloc(align, size);
	if (!newptr) return NULL;
	memcpy(newptr, ptr, usable < size ? usable : size);
	free(ptr);

	return newptr;
}

void* vsys_aligned_realloc(void* Ptr, st Size, st Alignment) {
	return aligned_realloc(Ptr, Alignment, Size);

}

#endif
