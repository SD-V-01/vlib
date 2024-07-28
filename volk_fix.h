////////////////////////////////////////////////////////////////////////////
//
//  VLIB Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   volk_fix.h
//  Version:     v1.00
//  Created:     29/05/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "cpp_compiler.h"

#include "system.h"

#ifdef VLIB_ON_CRT
#include <dlfcn.h>

extern inline void* volk_dlopen(const char* Filename, int Flags);
inline void* volk_dlopen(const char* Filename, int Flags){
	return dlopen(Filename, Flags);

}

extern inline void* volk_dlsym(void* Handle, const char* Symbol);
inline void* volk_dlsym(void* Handle, const char* Symbol) {
	return dlsym(Handle, Symbol);

}

extern inline int volk_dlclose(void* Handle);
inline int volk_dlclose(void* Handle) {
	return dlclose(Handle);

}

#else
#error Implement these crt function
#endif
