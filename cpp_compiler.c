////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   cpp_compiler.c
//  Version:     v1.00
//  Created:     29/06/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#ifndef VLIB_ALLOCATOR_IMPL
#warning No allocator was selected by the build system, building VLIB with mimalloc

#endif

#ifdef VLIB_NO_ALLOCATOR
#warning Building vlib without an allocator because of VLIB_NO_ALLOCATOR
#warning This should be only used for runtime debugging/porting purpuses !!!

#endif
