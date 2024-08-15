////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   vmath.h
//  Version:     v1.00
//  Created:     01/08/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VLIB_VMATH_IMPL

#include "base_types.h"
#include "float.h"
#include "math.h"

//SECTION(V): math utils

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

static __inline unsigned __FLOAT_BITS(float __f)
{
	union {float __f; unsigned __i;} __u;
	__u.__f = __f;
	return __u.__i;
}
static __inline unsigned long long __DOUBLE_BITS(double __f)
{
	union {double __f; unsigned long long __i;} __u;
	__u.__f = __f;
	return __u.__i;
}

#define vmathisinf(x) isinf(x)

#define vmathisnan(x) isnan(x)

VLIB_CABI
MDMATH_ABI double vround64(double x);

VLIB_CABIEND

//SECTION(V): vector math

#ifdef _MSC_VER
#define VMATH_ALIGN(type) __declspec(align(16)) type

#elif defined(__GNUC__) || defined(__clang__)
#define VMATH_ALIGN(type) type __attribute__((aligned(16)))

#endif

#include "vvector.inl.h"
