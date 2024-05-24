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

#ifndef _BASE_TYPES_H_
#define _BASE_TYPES_H_

typedef signed char __int8_t;
typedef signed short int __int16_t;
typedef signed int __int32_t;

//NOTE(V): 64 bit types are not portable bettwen compilers for some reason ?
//typedef signed long int __int64_t;
typedef __INT64_TYPE__ __int64_t;

typedef unsigned char __uint8_t;
typedef unsigned short int __uint16_t;
typedef unsigned int __uint32_t;

//typedef unsigned long int __uint64_t;
typedef __UINT64_TYPE__ __uint64_t;

typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;

typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef u8 byte;

typedef size_t sizeType;
typedef size_t st;
typedef void* pvoid;
typedef const void* cpvoid;
#ifdef VPP
#define NULL 0

#endif

#ifdef VPP
typedef char32_t dchar;
typedef char32_t vchar;
typedef char32_t wchar;

#endif

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
#else
#define va_start(v,l) __builtin_va_start(v,l)
#endif
#define va_end(v) __builtin_va_end(v)
#define va_arg(v,l) __builtin_va_arg(v,l)

typedef __builtin_va_list va_list;

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
