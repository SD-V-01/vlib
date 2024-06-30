////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   mdmembase.h
//  Version:     v1.00
//  Created:     10/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"

#ifndef _MDMEMBASE_H_
#define _MDMEMBASE_H_

//SECTION(V): memory utils functions

VLIB_CABI
bool mdmIsPow2(u32 In);
bool mdmIsPow2b64(u64 In);
i32 mdmAlignUp(i32 In, i32 Alignment);
st mdmAlignUpSt(st In, st Alignment);
st mdmAlignUpSt32(st In, i32 Alignment);
void* mdmAlignUpPtr(void* Ptr, st Alignment);
i32 mdmAlignUpPow2(i32 In, i32 Alignment);
st mdmAlignUpPow2st(st In, i32 Alignment);
void* mdmAlignUpPow2Ptr(void* Ptr, i32 Alignment);
i32 mdmAlignDownPow2(i32 In, i32 Alignment);
void* mdmAlignDownPow2Ptr(void* Ptr, i32 Alignment);
u32 mdmPow2(u32 In);

VLIB_CABIEND

#endif
