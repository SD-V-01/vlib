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

#define VLIB_DSTR8_STACK_SPACE 40

VLIB_STRUCT(dstr8)
char* DataPtr;
st Size;
st Alloc;
char DataStack[VLIB_DSTR8_STACK_SPACE];

VLIB_STRUCTEND(dstr8)

#define VLIB_DSTR32_SMALLEST_SIZE 8

VLIB_STRUCT(dstr32)
vchar* DataPtr;
st Size;
st Alloc;

VLIB_STRUCTEND(dstr32)

VLIB_CABI
VSTR32_API void dstrinit32(st Size);
VSTR32_API void dstrdestroy32(dstr32* This);
VSTR32_API void dstrchecksize32(const st TargetSize, dstr32* This);
VSTR32_API void dstrset32(const vchar* Str, const st Size, dstr32* This);

VLIB_CABIEND

VLIB_CABI
VSTR32_API st vstrlen8(const char* String);
VSTR32_API st vstrlen16(const char16* String);
VSTR32_API st vstrlen32(const vchar* String);

VSTR32_API char* vstrchr8(const char* Str, int Char);
VSTR32_API char* vstrchrnul8(const char* Str, int Char);
VSTR32_API char* vstrrchr8(const char* Str, int Char);
VSTR32_API char* vstrstr8(const char* In, const char* Search);
VSTR32_API char* vstrstr2(const unsigned char* In, const unsigned char* Search);
VSTR32_API char* vstrstr3(const unsigned char* In, const unsigned char* Search);
VSTR32_API char* vstrstr4(const unsigned char* In, const unsigned char* Search);
VSTR32_API char* vstrstrtw(const unsigned char* In, const unsigned char* Search);
VSTR32_API long int vstrtol8(const char* Str, char** EndPtr, int Base);

VSTR32_API u32 vdigitlen(u64 In);
VSTR32_API u32 vdigitlensigned(i64 In);
VSTR32_API void v32to8char(const vchar* Source, char* Target, u32 Size);
VSTR32_API void v8to32char(const char* Source, vchar* Target, u32 Size);

VSTR32_API int vLEGACYstrcmp(const char* s1, const char* s2);
VSTR32_API void vLEGACYstrcopy(const char* Source, char* Dest);
VSTR32_API char* vLEGACYstrncat(char* Dest, const char* Source, size_t Size);
VSTR32_API char* vLEGACYgcvt(double In, int NumDigits, char* Buf);
VSTR32_API char* vLEGACYrealpath(const char* filename, char* resolved);

VSTR32_API st vinttostr8(u64 Var, char* Result, st MaxSize);
VSTR32_API st vinttostr32(u64 Var, vchar* Result, st MaxSize);
VSTR32_API st vinttohex8(u64 Var, char* Result, st MaxSize);
VSTR32_API st vinttohex8b32(u32 Var, char* Result, st MaxSize);
VSTR32_API st vdoubletostr8(double Val, char* Result, st MaxSize);
VSTR32_API char* vstrlastchar8(const char* Str, int Char);

VSTR32_API void vformaterror(const char* Message);
VSTR32_API st vformat8impl(const char* Fmt, char* Buf, sst BufSize, v_varargList Args);
VSTR32_API st vformat8(const char* Fmt, char* Buf, st BufSize, ...);
VSTR32_API u64 vformathash(const char* In);
VSTR32_API bool vformatisexactmatch8(const char* Buf, const char* Search);

VLIB_CABIEND

#endif
