////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   cpp_compiler.c v1.00
//  Created:     29/06/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

#ifndef VLIB_ALLOCATOR_IMPL

#ifdef __ANDROID__
#warning No allocator was selected by the build system, building VLIB for android with default system allocator

#else
#warning No allocator was selected by the build system, building VLIB with mimalloc

#endif

#endif

#ifdef VLIB_NO_ALLOCATOR
#warning Building vlib without an allocator because of VLIB_NO_ALLOCATOR
#warning This should be only used for runtime debugging/porting purpuses !!!

#endif

#if defined(__ANDROID__) && !defined(VLIB_NO_ENTRY) && !defined(__cplusplus)
//NOTE(V): This is deprecated ever since we are compiling the engine core with a c++ compiler !!!
//#include "android_glue/android_native_app_glue.c"

#endif
