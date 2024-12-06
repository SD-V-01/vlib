////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   VHatesOpenxr.h v1.00
//  Created:     09/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "cpp_compiler.h"

#ifdef TENX_PARSER
#define VLIB_USE_OXR

#endif

#ifdef VLIB_USE_OXR
#include "base_types.h"

#define XRSUCKS_API

#ifndef XRSUCKS_APP_NAME
#define XRSUCKS_APP_NAME "IHateOpenXR@MythOS.void"
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
