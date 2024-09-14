////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mythalloc_api.h
//  Version:     v1.00
//  Created:     28/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "base_types.h"

#define MYTHALLOC_API

VLIB_CABI
MYTHALLOC_API void mytha_init();
MYTHALLOC_API void* mytha_malloc(st Size);
MYTHALLOC_API void* mytha_aalloc(st Size, st Alignment);
MYTHALLOC_API void mytha_free(void* Ptr);
MYTHALLOC_API void* mytha_realloc(void* Ptr, st NewSize);
MYTHALLOC_API void* mytha_arealloc(void* Ptr, st NewSize, st Alignment);
MYTHALLOC_API void* mytha_calloc(st Size, st Count);

MYTHALLOC_API void* mytha_zeroalloc(st NewSize);
MYTHALLOC_API void* mytha_zerocalloc(st NewCount, st NewSize);
MYTHALLOC_API void* mytha_zerorealloc(void* Ptr, st NewSize);
MYTHALLOC_API void mytha_zerofree(void* Ptr);

VLIB_CABIEND
