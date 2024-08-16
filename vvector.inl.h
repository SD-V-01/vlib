////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   vvector.inl.h
//  Version:     v1.00
//  Created:     07/08/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#ifndef VLIB_VMATH_IMPL
#error Try to include "vmath.h"

#endif

#ifdef VLIB_ARM
#include "vvector_IMPL_NEON.inl.h"

#elif defined(__SSE4_1__) && defined(__AVX2__)
#include "vvector_IMPL_SSE.inl.h"

#elif defined(__SSE4_1__) && !defined(__AVX2__)
#include "vvector_IMPL_SSE.inl.h"

#else
#warning Using scalar math witch is going to slow down the vector operations


#endif
