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

void vrt_preInitUsr();
void vrt_usrCode();

#if !defined(VLIB_ON_CRT) && !defined(VLIB_NO_ENTRY)

#if defined(_WIN32)



#include "system.h"
#include "windows.h"
#include "cpp_compiler.h"


void vrt_CoreMemInit() {
	vsys_initCoreMemory();

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

#if defined(__unix__)

#include "system.h"

#ifdef __cplusplus
extern "C" {
	#endif
=
	__attribute__((force_align_arg_pointer))
	void _start() {

		//vrt_preInitUsr();

		vsys_appRtInit();
		vsys_initCoreMemory();
		//vrt_usrCode();


		vsys_killProcess(0);

	}


	#ifdef __cplusplus
}
#endif

#endif

#else

#include "system.h"
#include "mem.h"

int main(int argc, char** argv) {
	vrt_preInitUsr();
	vsys_appRtInit();
	vsys_initCoreMemory();
	vrt_usrCode();

	return 0;

}

#endif
