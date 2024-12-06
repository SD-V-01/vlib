////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   vsystemalloc.h
//  Version:     v1.00
//  Created:     08/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "cpp_compiler.h"

#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_SYSTEM
#include "base_types.h"

VLIB_CABI
void* vsys_malloc(st Size);
void* vsys_calloc(st Size, st Count);
void* vsys_realloc(void* Ptr, st Size);
void vsys_free(void* Ptr);
void* vsys_aligned_malloc(st Size, st Alignment);
void* vsys_aligned_realloc(void* Ptr, st Size, st Alignment);

VLIB_CABIEND

#endif
