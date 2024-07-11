////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   VHatesOpenxr.c
//  Version:     v1.00
//  Created:     09/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "cpp_compiler.h"

#ifdef VLIB_USE_OXR

#include "VHatesOpenxr.h"
#include "mderror.h"
#include "vstr32.h"

#include "vulkan/vulkan_core.h"
#define XR_USE_GRAPHICS_API_VULKAN
#ifdef VLIB_ANDROID
#define XR_USE_PLATFORM_ANDROID
#endif
#include "openxr/openxr_platform.h"
#include "openxr/openxr.h"

VLIB_CABI

#ifdef VLIB_ANDROID
void xrsuxAndroidLoaderInit(void* Vm, void* Context){
//    NOTE(V): I will piledive to the person that tought it was a good idea to run
//        C code inside a java VM
	XrLoaderInitInfoAndroidKHR LoaderInfo;
	vset(&LoaderInfo, 0, sizeof(LoaderInfo));
	LoaderInfo.type = XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR;
//    NOTE(V): This pointer "next" is useless
	LoaderInfo.next = NULL;
	LoaderInfo.applicationVM = Vm; // This is actually a pointer to internal java vm memory because why not >:)
	LoaderInfo.applicationContext = Context;

	PFN_xrInitializeLoaderKHR xrInitializeLoaderKHR;
	//    NOTE(V): The comitie forgor to bring batteries with there legalized nuclear bomb
	XrResult GetFunc = xrGetInstanceProcAddr(
		XR_NULL_HANDLE, "xrInitializeLoaderKHR", (PFN_xrVoidFunction*)&xrInitializeLoaderKHR);
	if (!XR_SUCCEEDED(GetFunc)) {
		VASSERT(0, "Getting the function pointer to initialize the android bullshit because the openxr working group forgor what an abi is");
		return;

	}

	XrResult LoaderResult = xrInitializeLoaderKHR((XrLoaderInitInfoBaseHeaderKHR*)&LoaderInfo);
	if (!XR_SUCCEEDED(GetFunc)) {
		VASSERT(0, "Wrangling the android dogshit runtime failed, along your programing career");

	}

//    NOTE(V): I don't even know how i do this anymore, at least this is not the vision pro api

}

#else
void xrsuxAndroidLoaderInit(void* Vm, void* Context){
//    NOTE(V): We do not need to do anything on other platforms because other platforms don't SUCK
	return;

}

#endif

st xrsuxFindNameInList(const char* Key, const char** List, st ListSize) {
	const st WantedSize = vstrlen8(Key);

	for (u32 v = 0; v < ListSize; v++) {
		if (vstrlen8(List[v]) != WantedSize) {
			goto END_DEVICE_EXTENSION_LOOP;

		}

		for (u32 n = 0; n < WantedSize; n++) {
			if (List[v][n] != Key[n]) {
				goto END_DEVICE_EXTENSION_LOOP;

			}

		}

		return v;

		END_DEVICE_EXTENSION_LOOP:
		(void)NULL;

	}

	return XRSUCKS_FIND_IN_LIST_ERROR;

}

bool xrsuxIsLayerPresent(const char* Wanted) {
	if (Wanted == NULL) {
		VASSERT(0, "NULL pointer passed to xrsuxIsLayerPresent");

	}

	XrResult Result;
	u32 LayerCount = 0;
	Result = xrEnumerateApiLayerProperties(0, &LayerCount, NULL);
	if (!XR_SUCCEEDED(Result)) {
		VASSERT(0, "Could not get number of api layer count");
		return false;

	}

	if (LayerCount == 0) {
		return false;

	}

	XrApiLayerProperties Properties[LayerCount];
	Result = xrEnumerateApiLayerProperties(LayerCount, &LayerCount, Properties);
	if (!XR_SUCCEEDED(Result)) {
		VASSERT(0, "Could not enumerate api layers");
		return false;

	}

	const char* Layers[LayerCount];
	for (st v = 0; v < LayerCount; v++) {
		Layers[v] = Properties[v].layerName;

	}

	st SearchResult = xrsuxFindNameInList(Wanted, Layers, LayerCount);
	if (SearchResult != XRSUCKS_FIND_IN_LIST_ERROR) {
		return true;

	}
	else {
		return false;

	}

}

bool xrsuxIsExtensionPresent(const char* Wanted) {
	if (Wanted == NULL) {
		VASSERT(0, "Null pointer passed to xrsuxIsExtensionPresent");
		return false;

	}

	XrResult Result;
	u32 ExtensionCount = 0;
	Result = xrEnumerateInstanceExtensionProperties(NULL, 0, &ExtensionCount, NULL);
	if (!XR_SUCCEEDED(Result)) {
		VASSERT(0, "Could not get number of instance extensions");
		return false;

	}

	if (ExtensionCount == 0) {
		return false;

	}

	XrExtensionProperties Properties[ExtensionCount];
	Result = xrEnumerateInstanceExtensionProperties(NULL, ExtensionCount, &ExtensionCount, Properties);
	if (!XR_SUCCEEDED(Result)) {
		VASSERT(0, "Could not enumerate instance extensions");
		return false;

	}

	const char* Extensions[ExtensionCount];
	for (st v = 0; v < ExtensionCount; v++) {
		Extensions[v] = Properties[v].extensionName;

	}

	st SearchResult = xrsuxFindNameInList(Wanted, Extensions, ExtensionCount);
	if (SearchResult != XRSUCKS_FIND_IN_LIST_ERROR) {
		return true;

	}
	else {
		return false;

	}

}

VLIB_CABIEND

#endif
