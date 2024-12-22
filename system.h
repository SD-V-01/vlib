////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   system.h v1.00
//  Created:     03/05/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#ifdef __unix__
#include "stddef.h"

#endif

#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
//TODO(V): Remove this, this is here so the multithreading and maybe other future stuff will not error
//	on compile but the windows.h header sucks big time so if compile times gose bleak remove this pronto
#include <Windows.h>
//TODO(V): IMPORTANT !!!!!!!!!!!!!
//#warning Windows.h included !

#endif

#if defined(__aarch64__) || defined(_M_ARM64)
#include "arm_neon.h"

#endif

#ifdef __cplusplus
extern "C"{
	#endif

	#ifdef __cplusplus
	typedef bool vsys_bool;
	#define vsys_true true;
	#define vsys_false false;
	#define vsys_nullptr nullptr
	typedef size_t vsys_size;
	typedef __UINTPTR_TYPE__ vsys_uintptr;

	#else
	typedef _Bool vsys_bool;
	#define vsys_true 1;
	#define vsys_false 0;
	#define vsys_nullptr 0
	#ifndef __GNUC__
	typedef size_t vsys_size;
	#else
	typedef __SIZE_TYPE__ vsys_size;
	#endif

	typedef __UINTPTR_TYPE__ vsys_uintptr;

	#endif

	typedef struct {
		vsys_size smallPageSize;
		vsys_size largePageSize;
		vsys_size allocGranularity;
		vsys_bool hasOvercomit;
		vsys_bool mustFreeWhole;
		vsys_bool hasVirtualReserve;
	} vsys_coreMemoryProfile;
	
	vsys_size vsys_strlen(const char* String);
	void* vsys_copy(void* Dest, const void* Source, vsys_size Size);

//    NOTE(V): General initialization helpers
	void vsys_appRtInit();
	void vsys_intToStr(unsigned long int In, char* Target);
	unsigned int vsys_getNumberOfDigits(unsigned long int In);

	//NOTE(V): System specific init
	void vsys_init();

	//NOTE(V): Console/Logging syscall wrapper
	void vsys_writeConsole(const char* InText, int Length);
	void vsys_writeConsoleNullStr(const char* InText);
	void vsys_initConsole();
	void vsys_getOsVar(const char* In, char* Buffer, vsys_size BufferSize);

//    NOTE(V): General helpers
	void vsys_writeConsoleInteger(unsigned long int In);

//    NOTE(V): Process api
	void vsys_killProcess(int ReturnCode);

//    NOTE(V): Memory
	vsys_bool vsys_enableLargePage(vsys_size* PageSize);
	void vsys_initCoreMemory();
	void vsys_initMemory(vsys_coreMemoryProfile* MemProfile);
	void* vsys_allocSmallPageGeneric(vsys_size Size);
	void vsys_freeSmallPageGeneric(void* Ptr);

//    NOTE(V): Debugging api
	void vsys_breakpoint();

	#if defined(__GNUC__) && defined(_WIN32)
	typedef __WCHAR_TYPE__ wchar_t;

	#endif

//    NOTE(V): Only for porting purpuses, DO NOT USE
	void _DEPRECATED_DO_NOT_USE_vlib_crtinterop_getenv(const char* In, char* Buffer, vsys_size BufferSize);
	void _DEPRECATED_DO_NOT_USE_vlib_crtinterop_getenv_32(const wchar_t* In, wchar_t* Buffer, vsys_size BufferSize);

//    NOTE(V): LEGACY DO NOT USE !!!
	int vLEGACYatexit(void(*Func)());

	#ifdef TENX_PARSER
	#define __linux__
	#endif
	#ifdef __linux__
	int vsys_linux_getpagesize();

	#endif

	#ifdef __cplusplus
}
#endif

#endif
