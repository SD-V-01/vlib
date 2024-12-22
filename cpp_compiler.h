////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   cpp_compiler.h v1.00
//  Created:     30/04/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

#ifndef _CPP_COMPILER_H_
#define _CPP_COMPILER_H_

#ifndef VLIB_NAMESPACE
#define VLIB_NAMESPACE vlib
#endif

#if defined(_WIN32)
#define VLIB_PLATFORM_NT

#define VLIB_ABIEXPORT __declspec(dllexport)
#define VLIB_ABIIMPORT __declspec(dllimport)

#ifndef VLIB_ON_CRT
#define VLIB_ON_CRT
#warning Not being on a CRT is not supported, please define VLIB_ON_CRT everywhere

#endif

#elif defined(__ANDROID__)
#define VLIB_PLATFORM_LINUX
#ifndef VLIB_ON_CRT
#define VLIB_ON_CRT
#endif
#define VLIB_ANDROID

#define VLIB_ABIEXPORT __attribute__((visibility("default")))
#define VLIB_ABIIMPORT 

#elif defined(__linux__)
#define VLIB_PLATFORM_LINUX

#define VLIB_ABIEXPORT __attribute__((visibility("default")))
#define VLIB_ABIIMPORT 

#elif defined(TENX_PARSER) || defined(IDE_PARSER)
#error This code is for the IDE, not the compiler !!!


#define VLIB_ABIEXPORT 
#define VLIB_ABIIMPORT 

#else
#error Specify your platform define here

#endif

#ifdef __ARM_NEON
#define VLIB_ARM

#elif defined(__x86_64__)
#define VLIB_X64

#if defined(__AVX2__)
#define VMATH_AVX
#define VMATH_SSE

#elif defined(__SSE4_1__)
#define VMATH_SSE

#endif

#else
#error Implement cpu arch

#endif

#ifdef __cplusplus
#define VCPP
#define VPP
#endif

#ifdef VPP
#define VLIBPP_START namespace VLIB_NAMESPACE{
#define VLIBPP_END }

#define VLIB_STRUCT(Name) struct Name {
#define VLIB_STRUCTEND(Name) };

#define VLIB_CABI extern "C" {
#define VLIB_CABIEND }

#else
#define VLIBPP_START
#define VLIBPP_END

#define VLIB_STRUCT(Name) typedef struct s_##Name {
#define VLIB_STRUCTEND(Name) } Name;

#define VLIB_CABI
#define VLIB_CABIEND

#endif

#ifndef VLIB_NO_RUNTIME
#define VRT 1
#else
#define VRT 0
#endif

#define VUNDEF(param) ((void)(param))
#define VALIGNAS(Val) __attribute__((aligned(x)))
#define VALIGNAS_DEF

#define VLIB_ALLOCATOR_IMPL_NONE 0
#define VLIB_ALLOCATOR_IMPL_MYTH 2
#define VLIB_ALLOCATOR_IMPL_MIMALLOC 3
#define VLIB_ALLOCATOR_IMPL_VALLOC 4
#define VLIB_ALLOCATOR_IMPL_SYSTEM 5

#define global static
#ifndef intern
#define intern static

#endif
#define internal intern

#define Kilobytes(Bytes) ((Bytes)*1024LL)
#define Megabytes(Bytes) (Kilobytes(Bytes)*1024LL)
#define Gigabytes(Bytes) (Megabytes(Bytes)*1024LL)
#define Terabytes(Bytes) (Gigabytes(Bytes)*1024LL)

#define Pi32 3.14159265359f
#define Tau32 6.28318530717958647692f

#define VImplement VASSERT(0, "VImplement");

#define VFinishR _ReadBarrier()
#define VFinishW _WriteBarrier()
#define VFinishRW _ReadWriteBarrier()

#ifdef _WIN32
#define vfinl __forceinline

#else
#define vfinl __attribute__((always_inline)) inline

#endif

#ifdef VPP
#define vinl inline
#define vinlpp inline

#else
#define vinl inline static
#define vinlpp inline

#endif

#define rv const

#ifndef VLIB_ALLOCATOR_IMPL
#ifdef VLIB_NO_ALLOCATOR
#define VLIB_ALLOCATOR_IMPL VLIB_ALLOCATOR_IMPL_NONE

#elif defined(VLIB_ANDROID)
#define VLIB_ALLOCATOR_IMPL VLIB_ALLOCATOR_IMPL_SYSTEM

#else
#define VLIB_ALLOCATOR_IMPL VLIB_ALLOCATOR_IMPL_MIMALLOC
#endif

#endif

#endif
