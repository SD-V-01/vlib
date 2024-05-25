////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   mem.h
//  Version:     v1.00
//  Created:     30/04/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "cpp_compiler.h"
#include "base_types.h"

#ifndef _MEM_H_
#define _MEM_H_

#define MEM_API

MEM_API void* dalloc(size_t size);
MEM_API void* dcalloc(size_t size, size_t count);
MEM_API void* drealloc(void* p, size_t new_size);
MEM_API void dfree(void* p);

MEM_API u32 dpow2(u32 In);

MEM_API void* dcpy(void* Dest, const void* Source, size_t Size);

MEM_API void* valloc(st Size);
MEM_API void vfree(void* Ptr);
MEM_API void* vrealloc(void* Ptr, st NewSize);
MEM_API void* vcalloc(st size, st count);

MEM_API void* vcpy(void* Dest, const void* Source, size_t Size);
MEM_API void* vc(const void* Source, void* Dest, st Size);
MEM_API void* vmove(void* Dest, const void* Source, size_t Size);
MEM_API void* vset(void* Target, u8 Value, size_t Size);

#ifdef VPP

VLIBPP_START

#define dmem vmem

template <typename iType> struct vmem {
private:

    u32 ArraySize;
    u32 Allocation;
    iType* Ptr;

    #define MYTH_DEFAULT_VMEM_SIZE 8
    inline void internalInit(u32 Size) {
        ArraySize = 0;
        Allocation = dpow2(Size);
        if (Allocation < MYTH_DEFAULT_VMEM_SIZE) {
            Allocation = MYTH_DEFAULT_VMEM_SIZE;

        }

        Ptr = (iType*)dalloc(Allocation * sizeof(iType));

    }

public:

    inline void checkSize(u32 Size) {
        //printf("check size %u times %lu\n", Size, sizeof(Size));
        u32 NewSize = dpow2(Size);
        if (NewSize < MYTH_DEFAULT_VMEM_SIZE) {
            NewSize = MYTH_DEFAULT_VMEM_SIZE;

        }
        if (NewSize != Allocation) {
            //printf("Allocating for %u newSize %u alloc %u\n", Size, NewSize, Allocation);
            Ptr = (iType*)drealloc(Ptr, NewSize * sizeof(iType));
            Allocation = NewSize;

        }

    }

    typedef void (*loopFn)(iType &, u64);

    inline void loopAll(loopFn UsrFunc) {
        for (u64 i = 0; i < ArraySize; i++) {
            UsrFunc(Ptr[i], i);

        }

    }

    inline void loopAllHeap(loopFn UsrFunc) {
        for (u64 i = 0; i < Allocation; i++) {
            UsrFunc(Ptr[i], i);

        }

    }

    inline void init() {
        internalInit(MYTH_DEFAULT_VMEM_SIZE);

    }

    inline void init(u32 Size) {
        internalInit(Size);

    }

    inline vmem() {
        internalInit(MYTH_DEFAULT_VMEM_SIZE);
    }

    inline vmem(u32 Size) {
        internalInit(Size);

    }

    inline vmem(vmem<iType> const& Rhs) {
        init(Rhs.Allocation);
        ArraySize = Rhs.ArraySize;
        Ptr = (iType*)dcpy(Ptr, Rhs.Ptr, Allocation * sizeof(iType));

    }

    inline iType* data() {
        return Ptr;

    }

    inline iType* last(){
        if (ArraySize == 0) {
            return NULL;

        }

        return Ptr + (ArraySize - 1);

    }

    inline u32 size() {
        return ArraySize;

    }

    inline void setSize(u32 Rhs) {
        ArraySize = Rhs;

    }

    inline u32 alloc() {
        return Allocation;

    }

    inline void append(iType const& In) {
        checkSize(ArraySize + 1);
        *(Ptr + ArraySize) = In;
        ArraySize++;

    }

    inline void appendMem(const iType* In) {
        checkSize(ArraySize + 1);
        dcpy((Ptr + ArraySize), In, sizeof(iType));
        ArraySize++;

    }

    inline void appendNull() {
        checkSize(ArraySize + 1);
        vset(Ptr + ArraySize, 0, sizeof(iType));
        ArraySize++;

    }

    inline void zeroOut() {
        vset(Ptr, 0, Allocation * sizeof(iType));

    }

    inline void clear() {
        ArraySize = 0;

    }

    inline iType getCopy(u32 Index) {
        return *(Ptr + Index);

    }

    inline iType* getPtr(u32 Index) {
        return Ptr + Index;

    }

    inline void empty() {
        checkSize(MYTH_DEFAULT_VMEM_SIZE);
        ArraySize = 0;
        vset((void*)Ptr, 0, Allocation);

    }

};

VLIBPP_END

#endif // VPP

#endif
