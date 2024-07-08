////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   cpp_compiler.h
//  Version:     v1.00
//  Created:     30/04/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#ifndef _CPP_COMPILER_H_
#define _CPP_COMPILER_H_

#ifndef VLIB_NAMESPACE
#define VLIB_NAMESPACE vlib
#endif

#if defined(_WIN32)
#define VLIB_PLATFORM_NT

#elif defined(__ANDROID__)
#define VLIB_PLATFORM_LINUX
#ifndef VLIB_ON_CRT
#define VLIB_ON_CRT
#endif
#define VLIB_ANDROID

#elif defined(__unix__) && !defined(__APPLE__)
#define VLIB_PLATFORM_LINUX

#else
#error Specify your platform define here

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

#define VLIB_STRUCT(Name) typedef struct {
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
#define VLIB_ALLOCATOR_IMPL_MIMALLOC 3
#define VLIB_ALLOCATOR_IMPL_VALLOC 4
#define VLIB_ALLOCATOR_IMPL_SYSTEM 5

#ifndef VLIB_ALLOCATOR_IMPL
#ifdef VLIB_NO_ALLOCATOR
#define VLIB_ALLOCATOR_IMPL VLIB_ALLOCATOR_IMPL_NONE
#else
#define VLIB_ALLOCATOR_IMPL VLIB_ALLOCATOR_IMPL_MIMALLOC
#endif

#endif

#endif
