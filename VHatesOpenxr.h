////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   VHatesOpenxr.h
//  Version:     v1.00
//  Created:     09/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "cpp_compiler.h"

#ifdef VLIB_USE_OXR
#include "base_types.h"

#define XRSUCKS_API

#ifndef XRSUCKS_APP_NAME
#define XRSUCKS_APP_NAME "vlib native app"
#endif

VLIB_CABI
XRSUCKS_API void xrsuxAndroidLoaderInit(void* Vm, void* Context);
#define XRSUCKS_FIND_IN_LIST_ERROR 666666
XRSUCKS_API st xrsuxFindNameInList(const char* Key, const char** List, st ListSize);
XRSUCKS_API bool xrsuxIsLayerPresent(const char* Wanted);
XRSUCKS_API bool xrsuxIsExtensionPresent(const char* Wanted);
XRSUCKS_API void xrsuxDumpInstanceInfo();

VLIB_CABIEND

#endif
