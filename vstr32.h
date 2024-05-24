////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   vstr32.h
//  Version:     v1.00
//  Created:     09/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"

#ifndef _VSTR32_H_
#define _VSTR32_H_

#define VSTR32_API

#ifdef VPP
namespace VLIB_NAMESPACE{
	VSTR32_API st mstrlen(const char* String);
	VSTR32_API st mstrlen(const char32_t* String);

}

#endif

VLIB_CABI

VSTR32_API st vstrlen8(const char* String);
VSTR32_API st vstrlen16(const wchar_t* String);
VSTR32_API st vstrlen32(const vchar* String);

VSTR32_API char* vstrchr8(const char* Str, int Char);
VSTR32_API char* vstrstr8(const char* In, const char* Search);
VSTR32_API long int vstrtol8(const char* Str, char** EndPtr, int Base);

VSTR32_API u32 vdigitlen(u64 In);
VSTR32_API u32 vdigitlensigned(i64 In);
VSTR32_API void v32to8char(const vchar* Source, char* Target, u32 Size);
VSTR32_API void v8to32char(const char* Source, char32_t* Target, u32 Size);

VSTR32_API int vLEGACYstrcmp(const char* s1, const char* s2);
VSTR32_API void vLEGACYstrcopy(const char* Source, char* Dest);
VSTR32_API char* vLEGACYstrncat(char* Dest, const char* Source, size_t Size);
VSTR32_API char* vLEGACYgcvt(double In, int NumDigits, char* Buf);

VLIB_CABIEND

#endif

