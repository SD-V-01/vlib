////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   mdmembase.cpp
//  Version:     v1.00
//  Created:     10/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "mdmem.h"
#include "mderror.h"

//SECTION(V): memory utils functions
VLIB_CABI
bool mdmIsPow2(u32 In){
	return (In & (In - 1)) == 0;

}

bool mdmIsPow2b64(u64 In){
	return (In & (In - 1)) == 0;

}

i32 mdmAlignUp(i32 In, i32 Alignment) {
	return (((In - 1) / Alignment) + 1) * Alignment;

}

st mdmAlignUpSt(st In, st Alignment) {
	return (((In - 1) / Alignment) + 1) * Alignment;

}

st mdmAlignUpSt32(st In, i32 Alignment) {
	return (((In - 1) / Alignment) + 1) * Alignment;

}

void* mdmAlignUpPtr(void* Ptr, st Alignment) {
	st In = (st)Ptr;
	return (void*)((((In - 1) / Alignment) + 1) * Alignment);

}

i32 mdmAlignUpPow2(i32 In, i32 Alignment) {
	VASSERT(mdmIsPow2(In), "The alignment value passed to mdmAlignUpPow2(i32, i32) is not a power of two, MDos memory error");
	i32 Mask = Alignment - 1;
	return (In + Mask) & ~Mask;

}

st mdmAlignUpPow2st(st In, i32 Alignment) {
	VASSERT(mdmIsPow2(In), "The alignment value passed to mdmAlignUpPow2st(st, i32) is not a power of two, MDos memory error");
	i32 Mask = Alignment - 1;
	return (In + Mask) & ~Mask;

}

void* mdmAlignUpPow2Ptr(void* Ptr, i32 Alignment) {
	VASSERT(mdmIsPow2(In), "The alignment value passed to mdmAlignUpPow2Ptr(void*, i32) is not a power of two, MDos memory error");
	st In = (st)Ptr;
	i32 Mask = Alignment - 1;
	return (void*)((In + Mask) & ~Mask);

}

i32 mdmAlignDownPow2(i32 In, i32 Alignment) {
	VASSERT(mdmIsPow2(In), "The alignment value passed to mdmAlignDownPow2(i32, i32) is not a power of two, MDos memory error");
	return In & ~(Alignment - 1);

}

void* mdmAlignDownPow2Ptr(void* Ptr, i32 Alignment) {
	VASSERT(mdmIsPow2(In), "The alignment value passed to mdmAlignDownPow2Ptr(void*, i32) is not a power of two, MDos memory error");
	st In = (st)Ptr;
	return (void*)(In & ~(Alignment - 1));

}

u32 mdmPow2(u32 In) {
    In--;
    In |= In >> 1;
    In |= In >> 2;
    In |= In >> 4;
    In |= In >> 8;
    In |= In >> 16;
    In++;
    return In;

}

VLIB_CABIEND
