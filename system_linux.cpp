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
	__syscall1(SYSCALL_EXIT, ReturnCode);

}

#define SYSCALL_WRITE 1

void vsys_writeConsole(const char* InText, int Length) {
	__syscall3(SYSCALL_WRITE, 1, (long)InText, (long)Length);

}

VLIB_CABI
int vsys_linux_getpagesize() {
	return 4096;

}
VLIB_CABIEND

#endif
