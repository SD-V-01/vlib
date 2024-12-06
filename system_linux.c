////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   system_linux.c v1.00
//  Created:     23/05/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

#include "cpp_compiler.h"
#include "system.h"

#ifdef VLIB_PLATFORM_LINUX

#ifdef VLIB_ON_CRT
#include <unistd.h>
#include <stdlib.h>

#endif

#ifdef VLIB_ANDROID
#include "android/log.h"

#endif

void _DEPRECATED_DO_NOT_USE_vlib_crtinterop_getenv(const char* In, char* Buffer, vsys_size BufferSize){
	//    TODO(V): !!!!! STUB

}

void vsys_breakpoint() {
	__builtin_debugtrap();

}

vsys_bool vsys_enableLargePage(vsys_size* PageSize) {
	//    TODO(V): !!!!! STUB
	return vsys_false;

}

void vsys_initMemory(vsys_coreMemoryProfile* MemProfile) {
	//    TODO(V): !!!!! STUB

}

void* vsys_allocSmallPageGeneric(vsys_size Size) {
	//    TODO(V): !!!!! STUB
	return vsys_nullptr;

}

void vsys_freeSmallPageGeneric(void* Ptr) {
	//    TODO(V): !!!!! STUB

}

void vsys_initConsole() {
	//    NOTE(V): I am pretty sure linux doesent need that unlike win32

}

void vsys_getOsVar(const char* In, char* Buffer, vsys_size BufferSize) {
	#ifdef VLIB_ON_CRT
	char* GetenvResult = getenv(In);
	vsys_size Size = vsys_strlen(GetenvResult);
	vsys_size NullCharOffset = 0;
	if (Size < BufferSize) {
		NullCharOffset = Size;

	}
	else {
		Size = BufferSize;
		NullCharOffset = BufferSize - 1;

	}

	vsys_copy(Buffer, GetenvResult, Size);
	Buffer[NullCharOffset] = 0;

	#else
	#error IMPLEMENT PLATFORM !!!

	#endif

}

void vsys_init() {
	#ifdef VLIB_ON_CRT
	vsys_writeConsoleNullStr("Initializing V Runtime enviroment for Linux on CRT\n");

	#else
	vsys_writeConsoleNullStr("Initializing V Runtime enviroment for linux\n");

	#endif

}

#define SYSCALL_EXIT 60

void vsys_killProcess(int ReturnCode) {
	#ifndef VLIB_ON_CRT
	__syscall1(SYSCALL_EXIT, ReturnCode);
	#else
	_exit(ReturnCode);
	#endif

}

#define SYSCALL_WRITE 1

void vsys_writeConsole(const char* InText, int Length) {
	
	#ifndef VLIB_ANDROID
	//__syscall3(SYSCALL_WRITE, 1, (long)InText, (long)Length);
	#ifdef VLIB_ON_CRT
	write(1, InText, Length);
	#else
	#error implement
	#endif

	#else
	char Temp[Length + 1];
	//vcpy(Temp, InText, Length);
	for (unsigned int v = 0; v < Length; v++) {
		Temp[v] = InText[v];

	}
	Temp[Length] = 0;
	__android_log_print(ANDROID_LOG_INFO, "mdos", "%s", Temp);

	#endif

}

VLIB_CABI
int vsys_linux_getpagesize() {
	return 4096;

}
VLIB_CABIEND

#endif
