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

#include "vmem.h"
#include "base_types.h"
#include "mderror.h"

#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
#include "mimalloc.h"

#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_SYSTEM
#include "vsystemalloc.h"

#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MYTH
#include "mythalloc_api.h"

#endif

#ifdef VLIB_PLATFORM_NT
#include "windows.h"

#endif

VLIB_CABI

vfinl void* vallocimpl(st Size){
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC //NOTE(V): Mimalloc
	return mi_malloc(Size);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_SYSTEM
	return vsys_malloc(Size);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MYTH
	return mytha_malloc(Size);

	#else
	#error implement allocator

	#endif

}

vfinl void* vaallocimpl(st Size, st Alignment) {
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
	return mi_malloc_aligned(Size, Alignment);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_SYSTEM
	return vsys_aligned_malloc(Size, Alignment);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MYTH
	return mytha_aalloc(Size, Alignment);

	#else
	#error implement allocator

	#endif

}

vfinl void vfreeimpl(void* Size) {
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
	mi_free(Size);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_SYSTEM
	vsys_free(Size);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MYTH
	mytha_free(Size);

	#else
	#error implement allocator

	#endif

}

vfinl void* vreallocimpl(void* Ptr, st NewSize) {
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
	return mi_realloc(Ptr, NewSize);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_SYSTEM
	return vsys_realloc(Ptr, NewSize);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MYTH
	return mytha_realloc(Ptr, NewSize);

	#else
	#error implement allocator

	#endif

}

vfinl void* vareallocimpl(void* Ptr, st NewSize, st Alignment) {
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
	return mi_realloc_aligned(Ptr, NewSize, Alignment);
	
	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_SYSTEM
	return vsys_aligned_realloc(Ptr, NewSize, Alignment);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MYTH
	return mytha_arealloc(Ptr, NewSize, Alignment);

	#else
	#error implement allocator

	#endif

}

vfinl void* vcallocimpl(st size, st count){
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
	return mi_calloc(size, count);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_SYSTEM
	return vsys_calloc(size, count);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MYTH
	return mytha_calloc(size, count);

	#else
	#error implement allocator

	#endif
}

vfinl void* vzeroalloc(st NewSize) {
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
	return mi_zalloc(NewSize);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_SYSTEM
	return vsys_calloc(NewSize, 1);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MYTH
	return mytha_zeroalloc(NewSize);

	#else
	#error Implement

	#endif

}

vfinl void* vzerocalloc(st NewCount, st NewSize) {
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
	return mi_zalloc(NewCount * NewSize);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_SYSTEM
	void* Result = vsys_calloc(NewCount, NewSize);
	vset(Result, 0, NewCount * NewSize);
	return Result;

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MYTH
	return mytha_zerocalloc(NewCount, NewSize);

	#else
	#error Implement

	#endif

}

vfinl void vzerofree(void* Ptr) {
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
	mi_free(Ptr);
	
	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_SYSTEM
	return vsys_free(Ptr);

	#elif VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MYTH
	mytha_zerofree(Ptr);

	#else
	#error Implement

	#endif

}

void* dalloc(size_t size){
	return vallocimpl(size);

}

void* daalloc(size_t size, size_t Alignment){
	return vaallocimpl(size, Alignment);

}

void* dcalloc(size_t size, size_t count){
	return vcallocimpl(size, count);

}

void* drealloc(void* p, size_t new_size){
	return vreallocimpl(p, new_size);

}

void* darealloc(void* p, size_t new_size, size_t Alignment){
	return vareallocimpl(p, new_size, Alignment);

}

void dfree(void* p){
	vfreeimpl(p);
}

void dsafefree(void* p) {
	if (p) {
		vfreeimpl(p);
		p = NULL;

	}

}

void* vstackalloc(st Size){
	#if defined(VLIB_PLATFORM_NT) && defined(VLIB_ON_CRT)
	return _alloca(Size);

	#else
	#error Implement platform

	#endif

}

bool vIsPow2(u32 In){
	return (In & (In - 1)) == 0;

}

bool vIsPow2b64(u64 In){
	return (In & (In - 1)) == 0;

}

i32 vAlignUp(i32 In, i32 Alignment) {
	return (((In - 1) / Alignment) + 1) * Alignment;

}

st vAlignUpSt(st In, st Alignment) {
	return (((In - 1) / Alignment) + 1) * Alignment;

}

st vAlignUpSt32(st In, i32 Alignment) {
	return (((In - 1) / Alignment) + 1) * Alignment;

}

void* vAlignUpPtr(void* Ptr, st Alignment) {
	st In = (st)Ptr;
	return (void*)((((In - 1) / Alignment) + 1) * Alignment);

}

i32 vAlignUpPow2(i32 In, i32 Alignment) {
	VASSERT(vIsPow2(In), "The alignment value passed to vAlignUpPow2(i32, i32) is not a power of two, MDos memory error");
	i32 Mask = Alignment - 1;
	return (In + Mask) & ~Mask;

}

st vAlignUpPow2st(st In, i32 Alignment) {
	VASSERT(vIsPow2(In), "The alignment value passed to vAlignUpPow2st(st, i32) is not a power of two, MDos memory error");
	i32 Mask = Alignment - 1;
	return (In + Mask) & ~Mask;

}

void* vAlignUpPow2Ptr(void* Ptr, i32 Alignment) {
	st In = (st)Ptr;
	VASSERT(vIsPow2(In), "The alignment value passed to vAlignUpPow2Ptr(void*, i32) is not a power of two, MDos memory error");
	i32 Mask = Alignment - 1;
	return (void*)((In + Mask) & ~Mask);

}

i32 vAlignDownPow2(i32 In, i32 Alignment) {
	VASSERT(vIsPow2(In), "The alignment value passed to vAlignDownPow2(i32, i32) is not a power of two, MDos memory error");
	return In & ~(Alignment - 1);

}

void* vAlignDownPow2Ptr(void* Ptr, i32 Alignment) {
	st In = (st)Ptr;
	VASSERT(vIsPow2(In), "The alignment value passed to vAlignDownPow2Ptr(void*, i32) is not a power of two, MDos memory error");
	return (void*)(In & ~(Alignment - 1));

}



#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)
#include "unistd.h"
#include "sys/sysinfo.h"

u64 vGetTotalRam() {
	long Pages = sysconf(_SC_PHYS_PAGES);
	long PageSize = sysconf(_SC_PAGE_SIZE);
	return Pages * PageSize;

}

#elif defined(VLIB_PLATFORM_NT)
u64 vGetTotalRam() {
	MEMORYSTATUSEX Status;
    Status.dwLength = sizeof(Status);
    GlobalMemoryStatusEx(&Status);
    return Status.ullTotalPhys;

}

#else
#error Implement for platform

#endif

VLIB_CABIEND

#ifdef VPP
extern "C" {
	#endif
	//    This is a fuck you to the compiler that insist t think that dcpy should be replaced with the crt's memcpy even thow there is no crt ??
	//    NOTE(V): I really hate modern compilers sometimes, they really suck sometimes
	void* memcpy(void* Dest, const void* Source, size_t Size) {
		return vcpy(Dest, Source, Size);

	}

	//    NOTE(V): I really hate modern compilers
	void * memset( void * pointer, int value, size_t count ){
		return vset(pointer, value, count);

	}

	void* memmove(void* Dest, const void* Src, size_t Size) {
		return vmove(Dest, Src, Size);

	}

	#ifdef VPP
}
#endif

VLIB_CABI


/*void* vmove(void* Dest, const void* Source, size_t Size) {
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

	}*/

#ifdef __GNUC__
typedef __attribute__((__may_alias__)) size_t WT;
#define WS (sizeof(WT))
#endif

void *vmove(void *dest, const void *src, size_t n)
{
	char *d = (char*)dest;
	const char *s = (const char*)src;

	if (d==s) return d;
	#ifndef VPP
	if ((uintptr_t)s-(uintptr_t)d-n <= -2*n) return (void*)vcpy(d, s, n);
	#else
	if ((uintptr_t)s-(uintptr_t)d-n <= -2*n) return vcpy(d, s, n);
	#endif

	if (d<s) {
		#ifdef __GNUC__
		if ((uintptr_t)s % WS == (uintptr_t)d % WS) {
			while ((uintptr_t)d % WS) {
				if (!n--) return dest;
				*d++ = *s++;
			}
			for (; n>=WS; n-=WS, d+=WS, s+=WS) *(WT *)d = *(WT *)s;
		}
		#endif
		for (; n; n--) *d++ = *s++;
	} else {
		#ifdef __GNUC__
		if ((uintptr_t)s % WS == (uintptr_t)d % WS) {
			while ((uintptr_t)(d+n) % WS) {
				if (!n--) return dest;
				d[n] = s[n];
			}
			while (n>=WS) n-=WS, *(WT *)(d+n) = *(WT *)(s+n);
		}
		#endif
		while (n) n--, d[n] = s[n];
	}

	return dest;
}

void* vmemrchr(const void* Array, int Char, st Size) {
	const unsigned char* String = (const unsigned char*)Array;
	Char = (unsigned char)Char;
	while (Size--) {
		if (String[Size] == Char) {
			return (void*)(String + Size);

		}

	}

	return 0;

}

#define vmemchr_UCHAR_MAX 255
#define vmemchr_SS (sizeof(size_t))
#define vmemchr_ALIGN (sizeof(size_t)-1)
#define vmemchr_ONES ((size_t)-1/vmemchr_UCHAR_MAX)
#define vmemchr_HIGHS (vmemchr_ONES * (vmemchr_UCHAR_MAX/2+1))
#define vmemchr_HASZERO(x) ((x)-vmemchr_ONES & ~(x) & vmemchr_HIGHS)

void* vmemchr(const void* Array, int Char, st Size) {
	const unsigned char* Str = (const unsigned char*)Array;
	const unsigned char UChar = Char;
	Char = UChar;
	#ifdef __GNUC__
	for (; ((uintptr_t)Str & vmemchr_ALIGN) && Size && *Str != Char; Str++, Size--);
	if (Size && *Str != Char) {
		typedef st __attribute__((__may_alias__))word;
		const word* W;
		st K = vmemchr_ONES * Char;
		for (W = (const word*)(const void*)Str; Size >= vmemchr_SS && !vmemchr_HASZERO(*W ^ K); W++, Size-=vmemchr_SS);
		Size = (st)(const void*)W;

	}
	#endif
	for(; Size && *Str != Char; Str++, Char--);
	return Size ? (void*)Str : 0;

}

int vmemcmp(const void* Vl, const void* Vr, st Size) {
	const unsigned char* L = (const unsigned char*)Vl, *R = (const unsigned char*)Vr;
	for(; Size && *L == *R; Size--, L++, R++);
	return Size ? *L - *R : 0;

}

VLIB_CABIEND
