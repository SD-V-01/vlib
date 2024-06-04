////////////////////////////////////////////////////////////////////////////
//
//  VLIB Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   system_linux.cpp
//  Version:     v1.00
//  Created:     23/05/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "cpp_compiler.h"
#include "system.h"

#ifdef VLIB_PLATFORM_LINUX

#ifdef VLIB_ON_CRT
#include <unistd.h>

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

}

void vsys_initMemory(vsys_coreMemoryProfile* MemProfile) {
	//    TODO(V): !!!!! STUB

}

void* vsys_allocSmallPageGeneric(vsys_size Size) {
	//    TODO(V): !!!!! STUB

}

void vsys_freeSmallPageGeneric(void* Ptr) {
	//    TODO(V): !!!!! STUB

}

// frw
VLIB_CABI
void mdosPrintTermHeader();
VLIB_CABIEND

void vsys_initConsole() {
//    NOTE(V): I am pretty sure linux doesent need that unlike win32
	mdosPrintTermHeader();

}

void vsys_earlyInit() {
	//    TODO(V): !!!!! STUB

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
