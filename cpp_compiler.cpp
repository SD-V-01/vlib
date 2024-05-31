////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   cpp_compiler.cpp
//  Version:     v1.00
//  Created:     09/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#ifndef VLIB_ALLOCATOR_IMPL
#warning No allocator was selected by the build system, building VLIB with mimalloc

#endif

#ifdef VLIB_NO_ALLOCATOR
#warning Building vlib without an allocator because of VLIB_NO_ALLOCATOR
#warning This should be only used for runtime debugging/porting purpuses !!!

#endif
