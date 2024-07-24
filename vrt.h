////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   vrt.h
//  Version:     v1.00
//  Created:     03/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"

#ifndef _VRT_H_
#define _VRT_H_

VLIBPP_START

VLIB_STRUCT(vrt_sysArgs)


VLIB_STRUCTEND(vrt_sysArgs)

void vrt_usrCode();

void vrt_CoreMemInit();

VLIBPP_END

VLIB_CABI
void vrt_libInit();

VLIB_CABIEND

//SECTION(V): Android

#ifdef VLIB_ANDROID
#include "android_glue/android_native_app_glue.h"

VLIB_STRUCT(vrt_android)
android_app* AppPtr;
android_app App;

VLIB_STRUCTEND(vrt_android)

vrt_android vrt_getAndroidEnv();
ANativeActivity* vrt_getActivity();

#endif

#endif
