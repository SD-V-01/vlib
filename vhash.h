////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   vhash.h
//  Version:     v1.00
//  Created:     09/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"

#ifndef _VHASH_H_
#define _VHASH_H_

VLIBPP_START

u64 vfnv64std(const char* Data, u32 Size);
u64 vfnv64(const char* Data, u32 Size);

u64 vcrc64std(u64 crc, const unsigned char *s, u64 l);
u64 vcrc64(u64 crc, const unsigned char *s, u64 l);

inline u32 vrotl32(u32 X, u32 R) {
	return (X << R) | (X >> (32 - R));

}

inline u64 vrotl64(u64 X, u64 R) {
	return (X << R) | (X >> (64 - R));

}

u32 vfmix32(u32 In);
u64 vfmix64(u64 In);
u32 vmh332(const void* Data, st Length, u32 Seed);

VLIBPP_END

#endif

