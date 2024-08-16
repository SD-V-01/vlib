////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   base_types.h
//  Version:     v1.00
//  Created:     30/04/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "cpp_compiler.h"
#if defined(VLIB_X64)
#include "immintrin.h"

#elif defined(VLIB_ARM)
#include "arm_neon.h"

#else
#error Implement platform

#endif

#ifdef VLIB_PLATFORM_LINUX
#include "stddef.h"
#include "sys/types.h"

#endif

#ifndef _BASE_TYPES_H_
#define _BASE_TYPES_H_

#ifdef TENX_PARSER
#define __clang__

#endif

#ifndef __cplusplus
#define bool _Bool
#define true 1
#define false 0

#endif

#ifdef __clang__
//NOTE(V): 64 bit types are not portable bettwen compilers for some reason ?
//NOTE(V): I do prefer the clang way of handeling fixed size datatype because glibc is a mess with that !!


typedef __INT8_TYPE__ __int8_t;
typedef __UINT8_TYPE__ __uint8_t;

typedef __INT16_TYPE__ __int16_t;
typedef __UINT16_TYPE__ __uint16_t;

#ifdef __INT24_TYPE__
typedef __INT24_TYPE__ __int24_t;
typedef __UINT24_TYPE__ __uint24_t;
#define VLIB_24_BIT_PRESENT

#endif

typedef __INT32_TYPE__ __int32_t;
typedef __UINT32_TYPE__ __uint32_t;

#ifdef __INT40_TYPE__
typedef __INT40_TYPE__ __int40_t;
typedef __UINT40_TYPE__ __uint40_t;
#define VLIB_40_BIT_PRESENT

#endif

#ifdef __INT48_TYPE__
typedef __INT48_TYPE__ __int48_t;
typedef __UINT48_TYPE__ __uint48_t;
#define VLIB_48_BIT_PRESENT

#endif

#ifdef __INT56_TYPE__
typedef __INT56_TYPE__ __int56_t;
typedef __UINT56_TYPE__ __uint56_t;
#define VLIB_56_BIT_PRESENT

#endif

//typedef __INT64_TYPE__ ssize_t

typedef __INT64_TYPE__ __int64_t;
typedef __UINT64_TYPE__ __uint64_t;

#elif defined(__GNUC__)
typedef __INT8_TYPE__ __int8_t;
typedef __UINT8_TYPE__ __uint8_t;

typedef __INT16_TYPE__ __int16_t;
typedef __UINT16_TYPE__ __uint16_t;

typedef __INT32_TYPE__ __int32_t;
typedef __UINT32_TYPE__ __uint32_t;

typedef __INT64_TYPE__ __int64_t;
typedef __UINT64_TYPE__ __uint64_t;

typedef __SIZE_TYPE__ size_t;
typedef __INT64_TYPE__ ssize_t;
typedef __CHAR16_TYPE__ char16_t;
typedef __CHAR32_TYPE__ char32_t;

#else

typedef signed char __int8_t;
typedef signed short int __int16_t;
typedef signed int __int32_t;
typedef unsigned char __uint8_t;
typedef unsigned short int __uint16_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;

#warning Could not detect compiler for standard integers, this will probabelly cause issues !!

#endif

#ifdef VLIB_24_BIT_PRESENT
typedef __int24_t int24_t;
typedef __uint24_t uint24_t;
typedef uint24_t u24;
typedef int24_t i24;
#endif

#ifdef VLIB_40_BIT_PRESENT
typedef __int40_t int40_t;
typedef __uint40_t uint40_t;
typedef uint40_t u40;
typedef int40_t i40;

#endif

#ifdef VLIB_48_BIT_PRESENT
typedef __int48_t int48_t;
typedef __uint48_t uint48_t;
typedef uint48_t u48;
typedef int48_t i48;

#endif

#ifdef VLIB_56_BIT_PRESENT
typedef __int56_t int56_t;
typedef __uint56_t uint56_t;
typedef uint56_t u56;
typedef int56_t i56;

#endif

typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;

typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef u8 byte;

typedef size_t sizeType;
typedef size_t st;
typedef ssize_t sst;
typedef void* pvoid;
typedef const void* cpvoid;
#ifdef VPP
#ifndef NULL
#define NULL 0
#endif

#elif defined(__GNUC__)
#ifndef NULL
#define NULL 0
#endif


#endif


//NOTE(V): 32bit char
#ifdef __clang__
typedef u32 dchar;
typedef u32 vchar;
typedef u32 wchar;
typedef u16 char16;

#else
typedef char32_t dchar;
typedef char32_t vchar;
typedef char32_t wchar;
typedef char16_t char16;

#endif

#define INT8_C(c)  c
#define INT16_C(c) c
#define INT32_C(c) c
#define UINT8_C(c)  c
#define UINT16_C(c) c
#define UINT32_C(c) c ## U
#ifdef INT64_C
#define INT64_C(c) c ## L
#endif
#ifndef UINT64_C
#define UINT64_C(c) c ## UL
#endif

//NOTE(V): Extra standard types

//NOTE(V): This is not portable bettwen compilers
//typedef unsigned long int uintptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;

#ifdef va_start
#undef va_start
#endif

#ifdef va_end
#undef va_end
#endif

#ifdef va_arg
#undef va_arg
#endif

#if defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L
#define va_start(v, ...) __builtin_va_start(v, 0)
#define v_varargStart(v, ...) __builtin_va_start(v, 0)
#else
#define va_start(v,l) __builtin_va_start(v,l)
#define v_varargStart(v,l) __builtin_va_start(v,l)
#endif
#define va_end(v) __builtin_va_end(v)
#define v_varargEnd(v) __builtin_va_end(v)
#define va_arg(v,l) __builtin_va_arg(v,l)
#define v_vararg(v,l) __builtin_va_arg(v,l)

typedef __builtin_va_list va_list;
typedef __builtin_va_list v_varargList;

#define MYTH_BIT(Val) = 1 << Val

#define MYTH_ENUM_FLAG(EnumType, ValueType) inline EnumType operator|(EnumType Lhs, EnumType Rhs) { \
return (EnumType)(((ValueType)Lhs) | ((ValueType) Rhs));}\
inline EnumType operator~(EnumType Lhs) { \
return (EnumType)(~(ValueType)Lhs); }\
inline EnumType operator&(EnumType Lhs, EnumType Rhs) { \
return (EnumType)(((ValueType)Lhs) & ((ValueType)Rhs)); }\
inline void setBit(EnumType Flag, EnumType& Target) { \
Target = Target | Flag; }\
inline void unsetBit(EnumType Flag, EnumType& Target) { \
Target = Target & ~Flag; }\
inline bool getBit(EnumType Flag, EnumType& Target) { \
return (Target & Flag) == Flag; }

#endif
