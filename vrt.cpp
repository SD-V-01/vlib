////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   vrt.cpp
//  Version:     v1.00
//  Created:     03/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#ifndef VRT_NO_ENTRY_POINT

#ifdef _WIN32

void vrt_preInitUsr();
void vrt_usrCode();

#include "system.h"
#include "windows.h"
#include "cpp_compiler.h"

#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
//If we are using mimalloc we need to call the init functions first
void vlib_mimalloc_preinit();
#endif

void vrt_CoreMemInit() {
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
	vlib_mimalloc_preinit();

	#endif

}

void __stdcall VRuntime_MDos_NTAppInit()
{
	int Result = 0;

//    User preinit
	vrt_preInitUsr();

    //Result = WinMain(GetModuleHandle(0), 0, 0, 0);

	vsys_appRtInit();
	vrt_CoreMemInit();

//    User function (its the main equivalent)
	vrt_usrCode();

    vsys_killProcess(Result);
}

#endif

#endif
