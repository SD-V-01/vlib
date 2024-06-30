////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mdmath.c
//  Version:     v1.00
//  Created:     29/06/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "mdmath.h"

VLIB_CABI
#if FLT_EVAL_METHOD==0 || FLT_EVAL_METHOD==1
#define vround_EPS DBL_EPSILON
#elif FLT_EVAL_METHOD==2
#define vround_EPS LDBL_EPSILON
#endif
static const double_t toint = 1/vround_EPS;

double vround64(double x){
	union {double f; uint64_t i;} u = {x};
	int e = u.i >> 52 & 0x7ff;
	double_t y;

	if (e >= 0x3ff+52)
		return x;
	if (u.i >> 63)
		x = -x;
	if (e < 0x3ff-1) {
		/* raise inexact if x!=0 */
		MDMATH_FORCE_EVAL(x + toint);
		return 0*u.f;
	}
	y = x + toint - toint - x;
	if (y > 0.5)
		y = y + x - 1;
	else if (y <= -0.5)
		y = y + x + 1;
	else
		y = y + x;
	if (u.i >> 63)
		y = -y;
	return y;

}

VLIB_CABIEND
