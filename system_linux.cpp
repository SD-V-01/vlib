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

void vsys_initConsole() {
	//    TODO(V): !!!!! STUB

}

void vsys_writeConsole(const char* InText, int Length) {
	//    TODO(V): !!!!! STUB

}

void vsys_earlyInit() {
	//    TODO(V): !!!!! STUB

}

void vsys_init() {
	//    TODO(V): !!!!! STUB

}

void vsys_killProcess(int ReturnCode) {
	//    TODO(V): !!!!! STUB

}

#endif
