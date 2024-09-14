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

void mdosInit();
void mdosExit();

#include "cpp_compiler.h"

#include "vrt.h"

//SECTION(V): Android

#ifdef VLIB_ANDROID
static vrt_android AndroidEnv;

vrt_android vrt_getAndroidEnv(){
	return AndroidEnv;

}

ANativeActivity* vrt_getActivity() {
	return AndroidEnv.AppPtr->activity;

}

#endif

#if !defined(VLIB_NO_ENTRY) && defined(VLIB_ANDROID)
#ifndef VLIB_ON_CRT
#error Cannot build on android without the crt, please define VLIB_ON_CRT

#endif

#include "android_glue/android_native_app_glue.h"
#include "android/log.h"

extern "C"{
    __attribute__((visibility("default"))) void android_main(android_app* AppPtr);

	__attribute__((visibility("default"))) void android_main(android_app* AppPtr) {
		AndroidEnv.AppPtr = AppPtr;
		AndroidEnv.App = *AppPtr;

		__android_log_print(ANDROID_LOG_WARN, "mdos", "Starting mdos from android_main");

//        TODO(V): Implement !!!!!!!!!!!
	}

}

#elif !defined(VLIB_NO_ENTRY) && defined(VLIB_PLATFORM_NT)

#ifdef VLIB_ON_CRT
#error Building with a crt is not supported

#endif

#include "system.h"
#include "windows.h"
#include "cpp_compiler.h"


void vrt_CoreMemInit() {
	vsys_initCoreMemory();

}

//TODO(V): This has not being tested for 2 months and is probabelly broken, its fine its windows >:)
void __stdcall VRuntime_MDos_NTAppInit()
{
	int Result = 0;

	//    User preinit
	vrt_preInitUsr();

    //Result = WinMain(GetModuleHandle(0), 0, 0, 0);

	vsys_appRtInit();
	vrt_CoreMemInit();

	//    User function (its the main equivalent)
	mdosInit();
	vrt_usrCode();
	mdosExit();

    vsys_killProcess(Result);
}

#elif !defined(VLIB_NO_ENTRY) && defined(VLIB_ON_CRT) && defined(VLIB_PLATFORM_LINUX)

#include "system.h"
#include "vmem.h"

int main(int argc, char** argv) {
	vrt_preInitUsr();
	vsys_appRtInit();
	vsys_initCoreMemory();

	mdosInit();
	vrt_usrCode();
	mdosExit();

	return 0;

}

#elif !defined(VLIB_NO_ENTRY) && !defined(VLIB_ON_CRT) && defined(VLIB_PLATFORM_LINUX)

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
		mdosInit();
		//vrt_usrCode();
		mdosExit();

		vsys_killProcess(0);

	}


	#ifdef __cplusplus
}
#endif

#elif defined(VLIB_NO_ENTRY)

#include "system.h"

void vrt_libInit() {
	vrt_preInitUsr();
	vsys_appRtInit();
	vsys_initCoreMemory();
	mdosInit();
	vrt_usrCode();
	mdosExit();
}

#else
#error Implement platform

#endif

/*
#ifndef VLIB_NO_ENTRY

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
	mdosInit();
	vrt_usrCode();
	mdosExit();

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
		mdosInit();
		//vrt_usrCode();
		mdosExit();

		vsys_killProcess(0);

	}


	#ifdef __cplusplus
}
#endif

#endif

#else

#include "system.h"
#include "vmem.h"

int main(int argc, char** argv) {
	vrt_preInitUsr();
	vsys_appRtInit();
	vsys_initCoreMemory();

	mdosInit();
	vrt_usrCode();
	mdosExit();

	return 0;

}

#endif

#if defined(__ANDROID__)

#include "android_native_app_glue.h"
#include "android/log.h"

extern "C"{
    __attribute__((visibility("default"))) void android_main(android_app* AppPtr);


	__attribute__((visibility("default"))) void android_main(android_app* AppPtr) {
		__android_log_print(ANDROID_LOG_WARN, "mdos", "Starting mdos from android_main");

	}

}

#endif

#else
#include "system.h"

void vrt_libInit() {
	vrt_preInitUsr();
	vsys_appRtInit();
	vsys_initCoreMemory();
	mdosInit();
	vrt_usrCode();
	mdosExit();
}

#endif*/
