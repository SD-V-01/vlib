////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mdmath.h
//  Version:     v1.00
//  Created:     29/06/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "base_types.h"
#include "float.h"

#define MDMATH_ABI

#if FLT_EVAL_METHOD == 0
typedef float float_t;
typedef double double_t;

#elif FLT_EVAL_METHOD == 1
typedef double float_t;
typedef double double_t;

#elif FLT_EVAL_METHOD == 2
typedef long double float_t;
typedef long double double_t;

#else
#error FUCK THIS SHIT IM OUT

#endif

static inline void fp_force_evall(long double X) {
	volatile long double Y;
	Y = X;

}

static inline void fp_force_evalf(float X) {
	volatile float Y;
	Y = X;

}

static inline void fp_force_eval(double X){
	volatile double Y;
	Y = X;

}

#define MDMATH_FORCE_EVAL(x) do {                        \
if (sizeof(x) == sizeof(float)) {         \
fp_force_evalf(x);                \
} else if (sizeof(x) == sizeof(double)) { \
fp_force_eval(x);                 \
} else {                                  \
fp_force_evall(x);                \
}                                         \
} while(0)

VLIB_CABI
MDMATH_ABI double vround64(double x);

VLIB_CABIEND
