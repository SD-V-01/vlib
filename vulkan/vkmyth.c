////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   vkmyth.c
//  Version:     v1.00
//  Created:     29/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "vkmyth.h"
#include "mdos.h"

#ifdef __APPLE__
#error Dont even think about it, the apple vision pro is a misstake

#endif

#ifdef __cplusplus
extern "C"{
#endif

static mdsoHandle Libvk = mdsoNullHandle;
static VkDevice MainDevice = VK_NULL_HANDLE;

static PFN_vkVoidFunction mythVkNullifyInstanceFuncPtr(VkInstance Instance, const char* Name){
	(void)Instance;
	(void)Name;
	return NULL;

}

static PFN_vkVoidFunction mythVkNullifyDeviceFuncPtr(VkDevice Device, const char* Name){
	(void)Device;
	(void)Name;
	return NULL;

}

static PFN_vkVoidFunction mythVkLoad_loadFunc(VkInstance Instance, const char* Name){
	PFN_vkVoidFunction Func = vkGetInstanceProcAddr(Instance, Name);
	if(Func == NULL){
		VWARN("VkLoader", "Could not load Loader function {cstr}", Name);

	}

	return Func;

}

VkResult mythVkLoad(){
	mdsoHandle Handle = mdsoOpen(MYTH_VK_LOAD_DLL, mdsoFlags_localSymbols);
	if(!Handle){
		Handle = mdsoOpen(MYTH_VK_LOAD_DLL_BACKUP, mdsoFlags_localSymbols);

	}

	if(!Handle){
		VERRNF("VkLoader", "Could not load vulkan api");
		return VK_ERROR_INITIALIZATION_FAILED;

	}

	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)mdsoGetFunc(Handle, "vkGetInstanceProcAddr");
	Libvk = Handle;
	_mythVkLoadBasic(NULL, &mythVkLoad_loadFunc);

	return VK_SUCCESS;

}

void mythVkExit(){
	if(Libvk){
		mdsoClose(Libvk);

	}

	vkGetInstanceProcAddr = NULL;
	_mythVkLoadBasic(NULL, &mythVkNullifyInstanceFuncPtr);
	_mythVkLoadInstance(NULL, &mythVkNullifyInstanceFuncPtr);
	_mythVkLoadDevice(NULL, &mythVkNullifyDeviceFuncPtr);
	MainDevice = VK_NULL_HANDLE;

}

uint32_t mythVkGetInstanceVer(){
	#if defined(VK_VERSION_1_1)
	uint32_t Ver = 0;
	if(vkEnumerateInstanceVersion && vkEnumerateInstanceVersion(&Ver) == VK_SUCCESS){
		return Ver;

	}
	#endif

	if(vkCreateInstance){
		return VK_API_VERSION_1_0;

	}

	return 0;

}

static PFN_vkVoidFunction mythVkLoadInstance_loadFunc(VkInstance Instance, const char* Name) {
	PFN_vkVoidFunction Func = vkGetInstanceProcAddr(Instance, Name);
	if (Func == NULL) {
		VWARN("VkLoad", "Could not load Instance function {cstr}", Name);

	}
	/*else{
		//VERRNF("VkLoader", "#################################");
		u64* MemChecker = (u64*)Func;
		VVERBOSE("TESTING", "{u64} {ptr}", *MemChecker, Func);

	}*/

	return Func;

}

void mythVkLoadInstance(VkInstance Instance){
	VLOG("VkLoad", "Loading instance {ptr} functions", Instance);
	_mythVkLoadInstance(Instance, &mythVkLoadInstance_loadFunc);

}

static PFN_vkVoidFunction mythVkLoadDevice_laodFunc(VkDevice Device, const char* Name){
	PFN_vkVoidFunction Func = vkGetDeviceProcAddr(Device, Name);
	if(Func == NULL){
		VWARN("VkLoad", "Could not load device function {cstr}", Name);

	}

}

void mythVkLoadDevice(VkDevice Device){
	MainDevice = Device;
	_mythVkLoadDevice(Device, &mythVkLoadDevice_laodFunc);

}

void mythVkLoadArrayDevice(mythVkDeviceFuncArray* FuncArray, VkDevice Device){
	_mythVkLoadArrayDevice(FuncArray, Device, vkGetDeviceProcAddr);

}

void _mythVkLoadBasic(VkInstance Instance, PFN_vkGetInstanceProcAddr LoadFunc){

//SECTION(V): VK_LOADER_BASIC_IMPL
#if defined(VK_VERSION_1_0)
    vkCreateInstance = (PFN_vkCreateInstance)LoadFunc(Instance, "vkCreateInstance");
    vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties)LoadFunc(Instance, "vkEnumerateInstanceExtensionProperties");
    vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties)LoadFunc(Instance, "vkEnumerateInstanceLayerProperties");
#endif /*  defined(VK_VERSION_1_0)  */
#if defined(VK_VERSION_1_1)
    vkEnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion)LoadFunc(Instance, "vkEnumerateInstanceVersion");
#endif /*  defined(VK_VERSION_1_1)  */

}

MYTH_VK_LOAD_API void _mythVkLoadInstance(VkInstance Instance, PFN_vkGetInstanceProcAddr LoadFunc){

//SECTION(V): VK_LOADER_INSTANCE_IMPL
#if defined(VK_VERSION_1_0)
    vkCreateDevice = (PFN_vkCreateDevice)LoadFunc(Instance, "vkCreateDevice");
    vkDestroyInstance = (PFN_vkDestroyInstance)LoadFunc(Instance, "vkDestroyInstance");
    vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)LoadFunc(Instance, "vkEnumerateDeviceExtensionProperties");
    vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties)LoadFunc(Instance, "vkEnumerateDeviceLayerProperties");
    vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)LoadFunc(Instance, "vkEnumeratePhysicalDevices");
    vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)LoadFunc(Instance, "vkGetDeviceProcAddr");
    vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)LoadFunc(Instance, "vkGetPhysicalDeviceFeatures");
    vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties)LoadFunc(Instance, "vkGetPhysicalDeviceFormatProperties");
    vkGetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties)LoadFunc(Instance, "vkGetPhysicalDeviceImageFormatProperties");
    vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)LoadFunc(Instance, "vkGetPhysicalDeviceMemoryProperties");
    vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)LoadFunc(Instance, "vkGetPhysicalDeviceProperties");
    vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)LoadFunc(Instance, "vkGetPhysicalDeviceQueueFamilyProperties");
    vkGetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties)LoadFunc(Instance, "vkGetPhysicalDeviceSparseImageFormatProperties");
#endif /*  defined(VK_VERSION_1_0)  */
#if defined(VK_VERSION_1_1)
    vkEnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups)LoadFunc(Instance, "vkEnumeratePhysicalDeviceGroups");
    vkGetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties)LoadFunc(Instance, "vkGetPhysicalDeviceExternalBufferProperties");
    vkGetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties)LoadFunc(Instance, "vkGetPhysicalDeviceExternalFenceProperties");
    vkGetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties)LoadFunc(Instance, "vkGetPhysicalDeviceExternalSemaphoreProperties");
    vkGetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2)LoadFunc(Instance, "vkGetPhysicalDeviceFeatures2");
    vkGetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2)LoadFunc(Instance, "vkGetPhysicalDeviceFormatProperties2");
    vkGetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2)LoadFunc(Instance, "vkGetPhysicalDeviceImageFormatProperties2");
    vkGetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2)LoadFunc(Instance, "vkGetPhysicalDeviceMemoryProperties2");
    vkGetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2)LoadFunc(Instance, "vkGetPhysicalDeviceProperties2");
    vkGetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2)LoadFunc(Instance, "vkGetPhysicalDeviceQueueFamilyProperties2");
    vkGetPhysicalDeviceSparseImageFormatProperties2 = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2)LoadFunc(Instance, "vkGetPhysicalDeviceSparseImageFormatProperties2");
#endif /*  defined(VK_VERSION_1_1)  */
#if defined(VK_VERSION_1_3)
    vkGetPhysicalDeviceToolProperties = (PFN_vkGetPhysicalDeviceToolProperties)LoadFunc(Instance, "vkGetPhysicalDeviceToolProperties");
#endif /*  defined(VK_VERSION_1_3)  */
#if defined(VK_EXT_acquire_drm_display)
    vkAcquireDrmDisplayEXT = (PFN_vkAcquireDrmDisplayEXT)LoadFunc(Instance, "vkAcquireDrmDisplayEXT");
    vkGetDrmDisplayEXT = (PFN_vkGetDrmDisplayEXT)LoadFunc(Instance, "vkGetDrmDisplayEXT");
#endif /*  defined(VK_EXT_acquire_drm_display)  */
#if defined(VK_EXT_acquire_xlib_display)
    vkAcquireXlibDisplayEXT = (PFN_vkAcquireXlibDisplayEXT)LoadFunc(Instance, "vkAcquireXlibDisplayEXT");
    vkGetRandROutputDisplayEXT = (PFN_vkGetRandROutputDisplayEXT)LoadFunc(Instance, "vkGetRandROutputDisplayEXT");
#endif /*  defined(VK_EXT_acquire_xlib_display)  */
#if defined(VK_EXT_calibrated_timestamps)
    vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = (PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT)LoadFunc(Instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT");
#endif /*  defined(VK_EXT_calibrated_timestamps)  */
#if defined(VK_EXT_debug_report)
    vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)LoadFunc(Instance, "vkCreateDebugReportCallbackEXT");
    vkDebugReportMessageEXT = (PFN_vkDebugReportMessageEXT)LoadFunc(Instance, "vkDebugReportMessageEXT");
    vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)LoadFunc(Instance, "vkDestroyDebugReportCallbackEXT");
#endif /*  defined(VK_EXT_debug_report)  */
#if defined(VK_EXT_debug_utils)
    vkCmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT)LoadFunc(Instance, "vkCmdBeginDebugUtilsLabelEXT");
    vkCmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT)LoadFunc(Instance, "vkCmdEndDebugUtilsLabelEXT");
    vkCmdInsertDebugUtilsLabelEXT = (PFN_vkCmdInsertDebugUtilsLabelEXT)LoadFunc(Instance, "vkCmdInsertDebugUtilsLabelEXT");
    vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)LoadFunc(Instance, "vkCreateDebugUtilsMessengerEXT");
    vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)LoadFunc(Instance, "vkDestroyDebugUtilsMessengerEXT");
    vkQueueBeginDebugUtilsLabelEXT = (PFN_vkQueueBeginDebugUtilsLabelEXT)LoadFunc(Instance, "vkQueueBeginDebugUtilsLabelEXT");
    vkQueueEndDebugUtilsLabelEXT = (PFN_vkQueueEndDebugUtilsLabelEXT)LoadFunc(Instance, "vkQueueEndDebugUtilsLabelEXT");
    vkQueueInsertDebugUtilsLabelEXT = (PFN_vkQueueInsertDebugUtilsLabelEXT)LoadFunc(Instance, "vkQueueInsertDebugUtilsLabelEXT");
    vkSetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT)LoadFunc(Instance, "vkSetDebugUtilsObjectNameEXT");
    vkSetDebugUtilsObjectTagEXT = (PFN_vkSetDebugUtilsObjectTagEXT)LoadFunc(Instance, "vkSetDebugUtilsObjectTagEXT");
    vkSubmitDebugUtilsMessageEXT = (PFN_vkSubmitDebugUtilsMessageEXT)LoadFunc(Instance, "vkSubmitDebugUtilsMessageEXT");
#endif /*  defined(VK_EXT_debug_utils)  */
#if defined(VK_EXT_direct_mode_display)
    vkReleaseDisplayEXT = (PFN_vkReleaseDisplayEXT)LoadFunc(Instance, "vkReleaseDisplayEXT");
#endif /*  defined(VK_EXT_direct_mode_display)  */
#if defined(VK_EXT_directfb_surface)
    vkCreateDirectFBSurfaceEXT = (PFN_vkCreateDirectFBSurfaceEXT)LoadFunc(Instance, "vkCreateDirectFBSurfaceEXT");
    vkGetPhysicalDeviceDirectFBPresentationSupportEXT = (PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT)LoadFunc(Instance, "vkGetPhysicalDeviceDirectFBPresentationSupportEXT");
#endif /*  defined(VK_EXT_directfb_surface)  */
#if defined(VK_EXT_display_surface_counter)
    vkGetPhysicalDeviceSurfaceCapabilities2EXT = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT)LoadFunc(Instance, "vkGetPhysicalDeviceSurfaceCapabilities2EXT");
#endif /*  defined(VK_EXT_display_surface_counter)  */
#if defined(VK_EXT_full_screen_exclusive)
    vkGetPhysicalDeviceSurfacePresentModes2EXT = (PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)LoadFunc(Instance, "vkGetPhysicalDeviceSurfacePresentModes2EXT");
#endif /*  defined(VK_EXT_full_screen_exclusive)  */
#if defined(VK_EXT_headless_surface)
    vkCreateHeadlessSurfaceEXT = (PFN_vkCreateHeadlessSurfaceEXT)LoadFunc(Instance, "vkCreateHeadlessSurfaceEXT");
#endif /*  defined(VK_EXT_headless_surface)  */
#if defined(VK_EXT_metal_surface)
    vkCreateMetalSurfaceEXT = (PFN_vkCreateMetalSurfaceEXT)LoadFunc(Instance, "vkCreateMetalSurfaceEXT");
#endif /*  defined(VK_EXT_metal_surface)  */
#if defined(VK_EXT_sample_locations)
    vkGetPhysicalDeviceMultisamplePropertiesEXT = (PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT)LoadFunc(Instance, "vkGetPhysicalDeviceMultisamplePropertiesEXT");
#endif /*  defined(VK_EXT_sample_locations)  */
#if defined(VK_EXT_tooling_info)
    vkGetPhysicalDeviceToolPropertiesEXT = (PFN_vkGetPhysicalDeviceToolPropertiesEXT)LoadFunc(Instance, "vkGetPhysicalDeviceToolPropertiesEXT");
#endif /*  defined(VK_EXT_tooling_info)  */
#if defined(VK_FUCHSIA_imagepipe_surface)
    vkCreateImagePipeSurfaceFUCHSIA = (PFN_vkCreateImagePipeSurfaceFUCHSIA)LoadFunc(Instance, "vkCreateImagePipeSurfaceFUCHSIA");
#endif /*  defined(VK_FUCHSIA_imagepipe_surface)  */
#if defined(VK_GGP_stream_descriptor_surface)
    vkCreateStreamDescriptorSurfaceGGP = (PFN_vkCreateStreamDescriptorSurfaceGGP)LoadFunc(Instance, "vkCreateStreamDescriptorSurfaceGGP");
#endif /*  defined(VK_GGP_stream_descriptor_surface)  */
#if defined(VK_KHR_android_surface)
    vkCreateAndroidSurfaceKHR = (PFN_vkCreateAndroidSurfaceKHR)LoadFunc(Instance, "vkCreateAndroidSurfaceKHR");
#endif /*  defined(VK_KHR_android_surface)  */
#if defined(VK_KHR_calibrated_timestamps)
    vkGetPhysicalDeviceCalibrateableTimeDomainsKHR = (PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR)LoadFunc(Instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR");
#endif /*  defined(VK_KHR_calibrated_timestamps)  */
#if defined(VK_KHR_cooperative_matrix)
    vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR = (PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR");
#endif /*  defined(VK_KHR_cooperative_matrix)  */
#if defined(VK_KHR_device_group_creation)
    vkEnumeratePhysicalDeviceGroupsKHR = (PFN_vkEnumeratePhysicalDeviceGroupsKHR)LoadFunc(Instance, "vkEnumeratePhysicalDeviceGroupsKHR");
#endif /*  defined(VK_KHR_device_group_creation)  */
#if defined(VK_KHR_display)
    vkCreateDisplayModeKHR = (PFN_vkCreateDisplayModeKHR)LoadFunc(Instance, "vkCreateDisplayModeKHR");
    vkCreateDisplayPlaneSurfaceKHR = (PFN_vkCreateDisplayPlaneSurfaceKHR)LoadFunc(Instance, "vkCreateDisplayPlaneSurfaceKHR");
    vkGetDisplayModePropertiesKHR = (PFN_vkGetDisplayModePropertiesKHR)LoadFunc(Instance, "vkGetDisplayModePropertiesKHR");
    vkGetDisplayPlaneCapabilitiesKHR = (PFN_vkGetDisplayPlaneCapabilitiesKHR)LoadFunc(Instance, "vkGetDisplayPlaneCapabilitiesKHR");
    vkGetDisplayPlaneSupportedDisplaysKHR = (PFN_vkGetDisplayPlaneSupportedDisplaysKHR)LoadFunc(Instance, "vkGetDisplayPlaneSupportedDisplaysKHR");
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR");
    vkGetPhysicalDeviceDisplayPropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceDisplayPropertiesKHR");
#endif /*  defined(VK_KHR_display)  */
#if defined(VK_KHR_external_fence_capabilities)
    vkGetPhysicalDeviceExternalFencePropertiesKHR = (PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceExternalFencePropertiesKHR");
#endif /*  defined(VK_KHR_external_fence_capabilities)  */
#if defined(VK_KHR_external_memory_capabilities)
    vkGetPhysicalDeviceExternalBufferPropertiesKHR = (PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceExternalBufferPropertiesKHR");
#endif /*  defined(VK_KHR_external_memory_capabilities)  */
#if defined(VK_KHR_external_semaphore_capabilities)
    vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = (PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR");
#endif /*  defined(VK_KHR_external_semaphore_capabilities)  */
#if defined(VK_KHR_fragment_shading_rate)
    vkGetPhysicalDeviceFragmentShadingRatesKHR = (PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceFragmentShadingRatesKHR");
#endif /*  defined(VK_KHR_fragment_shading_rate)  */
#if defined(VK_KHR_get_display_properties2)
    vkGetDisplayModeProperties2KHR = (PFN_vkGetDisplayModeProperties2KHR)LoadFunc(Instance, "vkGetDisplayModeProperties2KHR");
    vkGetDisplayPlaneCapabilities2KHR = (PFN_vkGetDisplayPlaneCapabilities2KHR)LoadFunc(Instance, "vkGetDisplayPlaneCapabilities2KHR");
    vkGetPhysicalDeviceDisplayPlaneProperties2KHR = (PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR)LoadFunc(Instance, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR");
    vkGetPhysicalDeviceDisplayProperties2KHR = (PFN_vkGetPhysicalDeviceDisplayProperties2KHR)LoadFunc(Instance, "vkGetPhysicalDeviceDisplayProperties2KHR");
#endif /*  defined(VK_KHR_get_display_properties2)  */
#if defined(VK_KHR_get_physical_device_properties2)
    vkGetPhysicalDeviceFeatures2KHR = (PFN_vkGetPhysicalDeviceFeatures2KHR)LoadFunc(Instance, "vkGetPhysicalDeviceFeatures2KHR");
    vkGetPhysicalDeviceFormatProperties2KHR = (PFN_vkGetPhysicalDeviceFormatProperties2KHR)LoadFunc(Instance, "vkGetPhysicalDeviceFormatProperties2KHR");
    vkGetPhysicalDeviceImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceImageFormatProperties2KHR)LoadFunc(Instance, "vkGetPhysicalDeviceImageFormatProperties2KHR");
    vkGetPhysicalDeviceMemoryProperties2KHR = (PFN_vkGetPhysicalDeviceMemoryProperties2KHR)LoadFunc(Instance, "vkGetPhysicalDeviceMemoryProperties2KHR");
    vkGetPhysicalDeviceProperties2KHR = (PFN_vkGetPhysicalDeviceProperties2KHR)LoadFunc(Instance, "vkGetPhysicalDeviceProperties2KHR");
    vkGetPhysicalDeviceQueueFamilyProperties2KHR = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR)LoadFunc(Instance, "vkGetPhysicalDeviceQueueFamilyProperties2KHR");
    vkGetPhysicalDeviceSparseImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR)LoadFunc(Instance, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR");
#endif /*  defined(VK_KHR_get_physical_device_properties2)  */
#if defined(VK_KHR_get_surface_capabilities2)
    vkGetPhysicalDeviceSurfaceCapabilities2KHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR)LoadFunc(Instance, "vkGetPhysicalDeviceSurfaceCapabilities2KHR");
    vkGetPhysicalDeviceSurfaceFormats2KHR = (PFN_vkGetPhysicalDeviceSurfaceFormats2KHR)LoadFunc(Instance, "vkGetPhysicalDeviceSurfaceFormats2KHR");
#endif /*  defined(VK_KHR_get_surface_capabilities2)  */
#if defined(VK_KHR_performance_query)
    vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = (PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR)LoadFunc(Instance, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
    vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = (PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");
#endif /*  defined(VK_KHR_performance_query)  */
#if defined(VK_KHR_surface)
    vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)LoadFunc(Instance, "vkDestroySurfaceKHR");
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
    vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)LoadFunc(Instance, "vkGetPhysicalDeviceSurfaceFormatsKHR");
    vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceSurfacePresentModesKHR");
    vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)LoadFunc(Instance, "vkGetPhysicalDeviceSurfaceSupportKHR");
#endif /*  defined(VK_KHR_surface)  */
#if defined(VK_KHR_video_encode_queue)
    vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR = (PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR");
#endif /*  defined(VK_KHR_video_encode_queue)  */
#if defined(VK_KHR_video_queue)
    vkGetPhysicalDeviceVideoCapabilitiesKHR = (PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceVideoCapabilitiesKHR");
    vkGetPhysicalDeviceVideoFormatPropertiesKHR = (PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceVideoFormatPropertiesKHR");
#endif /*  defined(VK_KHR_video_queue)  */
#if defined(VK_KHR_wayland_surface)
    vkCreateWaylandSurfaceKHR = (PFN_vkCreateWaylandSurfaceKHR)LoadFunc(Instance, "vkCreateWaylandSurfaceKHR");
    vkGetPhysicalDeviceWaylandPresentationSupportKHR = (PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)LoadFunc(Instance, "vkGetPhysicalDeviceWaylandPresentationSupportKHR");
#endif /*  defined(VK_KHR_wayland_surface)  */
#if defined(VK_KHR_win32_surface)
    vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)LoadFunc(Instance, "vkCreateWin32SurfaceKHR");
    vkGetPhysicalDeviceWin32PresentationSupportKHR = (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)LoadFunc(Instance, "vkGetPhysicalDeviceWin32PresentationSupportKHR");
#endif /*  defined(VK_KHR_win32_surface)  */
#if defined(VK_KHR_xcb_surface)
    vkCreateXcbSurfaceKHR = (PFN_vkCreateXcbSurfaceKHR)LoadFunc(Instance, "vkCreateXcbSurfaceKHR");
    vkGetPhysicalDeviceXcbPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)LoadFunc(Instance, "vkGetPhysicalDeviceXcbPresentationSupportKHR");
#endif /*  defined(VK_KHR_xcb_surface)  */
#if defined(VK_KHR_xlib_surface)
    vkCreateXlibSurfaceKHR = (PFN_vkCreateXlibSurfaceKHR)LoadFunc(Instance, "vkCreateXlibSurfaceKHR");
    vkGetPhysicalDeviceXlibPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)LoadFunc(Instance, "vkGetPhysicalDeviceXlibPresentationSupportKHR");
#endif /*  defined(VK_KHR_xlib_surface)  */
#if defined(VK_MVK_ios_surface)
    vkCreateIOSSurfaceMVK = (PFN_vkCreateIOSSurfaceMVK)LoadFunc(Instance, "vkCreateIOSSurfaceMVK");
#endif /*  defined(VK_MVK_ios_surface)  */
#if defined(VK_MVK_macos_surface)
    vkCreateMacOSSurfaceMVK = (PFN_vkCreateMacOSSurfaceMVK)LoadFunc(Instance, "vkCreateMacOSSurfaceMVK");
#endif /*  defined(VK_MVK_macos_surface)  */
#if defined(VK_NN_vi_surface)
    vkCreateViSurfaceNN = (PFN_vkCreateViSurfaceNN)LoadFunc(Instance, "vkCreateViSurfaceNN");
#endif /*  defined(VK_NN_vi_surface)  */
#if defined(VK_NV_acquire_winrt_display)
    vkAcquireWinrtDisplayNV = (PFN_vkAcquireWinrtDisplayNV)LoadFunc(Instance, "vkAcquireWinrtDisplayNV");
    vkGetWinrtDisplayNV = (PFN_vkGetWinrtDisplayNV)LoadFunc(Instance, "vkGetWinrtDisplayNV");
#endif /*  defined(VK_NV_acquire_winrt_display)  */
#if defined(VK_NV_cooperative_matrix)
    vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = (PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV)LoadFunc(Instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV");
#endif /*  defined(VK_NV_cooperative_matrix)  */
#if defined(VK_NV_coverage_reduction_mode)
    vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = (PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV)LoadFunc(Instance, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV");
#endif /*  defined(VK_NV_coverage_reduction_mode)  */
#if defined(VK_NV_external_memory_capabilities)
    vkGetPhysicalDeviceExternalImageFormatPropertiesNV = (PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV)LoadFunc(Instance, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV");
#endif /*  defined(VK_NV_external_memory_capabilities)  */
#if defined(VK_NV_optical_flow)
    vkGetPhysicalDeviceOpticalFlowImageFormatsNV = (PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV)LoadFunc(Instance, "vkGetPhysicalDeviceOpticalFlowImageFormatsNV");
#endif /*  defined(VK_NV_optical_flow)  */
#if defined(VK_QNX_screen_surface)
    vkCreateScreenSurfaceQNX = (PFN_vkCreateScreenSurfaceQNX)LoadFunc(Instance, "vkCreateScreenSurfaceQNX");
    vkGetPhysicalDeviceScreenPresentationSupportQNX = (PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)LoadFunc(Instance, "vkGetPhysicalDeviceScreenPresentationSupportQNX");
#endif /*  defined(VK_QNX_screen_surface)  */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
    vkGetPhysicalDevicePresentRectanglesKHR = (PFN_vkGetPhysicalDevicePresentRectanglesKHR)LoadFunc(Instance, "vkGetPhysicalDevicePresentRectanglesKHR");
#endif /*  (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))  */

}

void _mythVkLoadDevice(VkDevice Device, PFN_vkGetDeviceProcAddr LoadFunc){

//SECTION(V): VK_LOADER_DEVICE_IMPL
#if defined(VK_VERSION_1_0)
    vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)LoadFunc(Device, "vkAllocateCommandBuffers");
    vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)LoadFunc(Device, "vkAllocateDescriptorSets");
    vkAllocateMemory = (PFN_vkAllocateMemory)LoadFunc(Device, "vkAllocateMemory");
    vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)LoadFunc(Device, "vkBeginCommandBuffer");
    vkBindBufferMemory = (PFN_vkBindBufferMemory)LoadFunc(Device, "vkBindBufferMemory");
    vkBindImageMemory = (PFN_vkBindImageMemory)LoadFunc(Device, "vkBindImageMemory");
    vkCmdBeginQuery = (PFN_vkCmdBeginQuery)LoadFunc(Device, "vkCmdBeginQuery");
    vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)LoadFunc(Device, "vkCmdBeginRenderPass");
    vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)LoadFunc(Device, "vkCmdBindDescriptorSets");
    vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)LoadFunc(Device, "vkCmdBindIndexBuffer");
    vkCmdBindPipeline = (PFN_vkCmdBindPipeline)LoadFunc(Device, "vkCmdBindPipeline");
    vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)LoadFunc(Device, "vkCmdBindVertexBuffers");
    vkCmdBlitImage = (PFN_vkCmdBlitImage)LoadFunc(Device, "vkCmdBlitImage");
    vkCmdClearAttachments = (PFN_vkCmdClearAttachments)LoadFunc(Device, "vkCmdClearAttachments");
    vkCmdClearColorImage = (PFN_vkCmdClearColorImage)LoadFunc(Device, "vkCmdClearColorImage");
    vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage)LoadFunc(Device, "vkCmdClearDepthStencilImage");
    vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer)LoadFunc(Device, "vkCmdCopyBuffer");
    vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)LoadFunc(Device, "vkCmdCopyBufferToImage");
    vkCmdCopyImage = (PFN_vkCmdCopyImage)LoadFunc(Device, "vkCmdCopyImage");
    vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer)LoadFunc(Device, "vkCmdCopyImageToBuffer");
    vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults)LoadFunc(Device, "vkCmdCopyQueryPoolResults");
    vkCmdDispatch = (PFN_vkCmdDispatch)LoadFunc(Device, "vkCmdDispatch");
    vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect)LoadFunc(Device, "vkCmdDispatchIndirect");
    vkCmdDraw = (PFN_vkCmdDraw)LoadFunc(Device, "vkCmdDraw");
    vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed)LoadFunc(Device, "vkCmdDrawIndexed");
    vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect)LoadFunc(Device, "vkCmdDrawIndexedIndirect");
    vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect)LoadFunc(Device, "vkCmdDrawIndirect");
    vkCmdEndQuery = (PFN_vkCmdEndQuery)LoadFunc(Device, "vkCmdEndQuery");
    vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)LoadFunc(Device, "vkCmdEndRenderPass");
    vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands)LoadFunc(Device, "vkCmdExecuteCommands");
    vkCmdFillBuffer = (PFN_vkCmdFillBuffer)LoadFunc(Device, "vkCmdFillBuffer");
    vkCmdNextSubpass = (PFN_vkCmdNextSubpass)LoadFunc(Device, "vkCmdNextSubpass");
    vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)LoadFunc(Device, "vkCmdPipelineBarrier");
    vkCmdPushConstants = (PFN_vkCmdPushConstants)LoadFunc(Device, "vkCmdPushConstants");
    vkCmdResetEvent = (PFN_vkCmdResetEvent)LoadFunc(Device, "vkCmdResetEvent");
    vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool)LoadFunc(Device, "vkCmdResetQueryPool");
    vkCmdResolveImage = (PFN_vkCmdResolveImage)LoadFunc(Device, "vkCmdResolveImage");
    vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants)LoadFunc(Device, "vkCmdSetBlendConstants");
    vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias)LoadFunc(Device, "vkCmdSetDepthBias");
    vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds)LoadFunc(Device, "vkCmdSetDepthBounds");
    vkCmdSetEvent = (PFN_vkCmdSetEvent)LoadFunc(Device, "vkCmdSetEvent");
    vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth)LoadFunc(Device, "vkCmdSetLineWidth");
    vkCmdSetScissor = (PFN_vkCmdSetScissor)LoadFunc(Device, "vkCmdSetScissor");
    vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask)LoadFunc(Device, "vkCmdSetStencilCompareMask");
    vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference)LoadFunc(Device, "vkCmdSetStencilReference");
    vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask)LoadFunc(Device, "vkCmdSetStencilWriteMask");
    vkCmdSetViewport = (PFN_vkCmdSetViewport)LoadFunc(Device, "vkCmdSetViewport");
    vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer)LoadFunc(Device, "vkCmdUpdateBuffer");
    vkCmdWaitEvents = (PFN_vkCmdWaitEvents)LoadFunc(Device, "vkCmdWaitEvents");
    vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp)LoadFunc(Device, "vkCmdWriteTimestamp");
    vkCreateBuffer = (PFN_vkCreateBuffer)LoadFunc(Device, "vkCreateBuffer");
    vkCreateBufferView = (PFN_vkCreateBufferView)LoadFunc(Device, "vkCreateBufferView");
    vkCreateCommandPool = (PFN_vkCreateCommandPool)LoadFunc(Device, "vkCreateCommandPool");
    vkCreateComputePipelines = (PFN_vkCreateComputePipelines)LoadFunc(Device, "vkCreateComputePipelines");
    vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool)LoadFunc(Device, "vkCreateDescriptorPool");
    vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)LoadFunc(Device, "vkCreateDescriptorSetLayout");
    vkCreateEvent = (PFN_vkCreateEvent)LoadFunc(Device, "vkCreateEvent");
    vkCreateFence = (PFN_vkCreateFence)LoadFunc(Device, "vkCreateFence");
    vkCreateFramebuffer = (PFN_vkCreateFramebuffer)LoadFunc(Device, "vkCreateFramebuffer");
    vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)LoadFunc(Device, "vkCreateGraphicsPipelines");
    vkCreateImage = (PFN_vkCreateImage)LoadFunc(Device, "vkCreateImage");
    vkCreateImageView = (PFN_vkCreateImageView)LoadFunc(Device, "vkCreateImageView");
    vkCreatePipelineCache = (PFN_vkCreatePipelineCache)LoadFunc(Device, "vkCreatePipelineCache");
    vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)LoadFunc(Device, "vkCreatePipelineLayout");
    vkCreateQueryPool = (PFN_vkCreateQueryPool)LoadFunc(Device, "vkCreateQueryPool");
    vkCreateRenderPass = (PFN_vkCreateRenderPass)LoadFunc(Device, "vkCreateRenderPass");
    vkCreateSampler = (PFN_vkCreateSampler)LoadFunc(Device, "vkCreateSampler");
    vkCreateSemaphore = (PFN_vkCreateSemaphore)LoadFunc(Device, "vkCreateSemaphore");
    vkCreateShaderModule = (PFN_vkCreateShaderModule)LoadFunc(Device, "vkCreateShaderModule");
    vkDestroyBuffer = (PFN_vkDestroyBuffer)LoadFunc(Device, "vkDestroyBuffer");
    vkDestroyBufferView = (PFN_vkDestroyBufferView)LoadFunc(Device, "vkDestroyBufferView");
    vkDestroyCommandPool = (PFN_vkDestroyCommandPool)LoadFunc(Device, "vkDestroyCommandPool");
    vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool)LoadFunc(Device, "vkDestroyDescriptorPool");
    vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)LoadFunc(Device, "vkDestroyDescriptorSetLayout");
    vkDestroyDevice = (PFN_vkDestroyDevice)LoadFunc(Device, "vkDestroyDevice");
    vkDestroyEvent = (PFN_vkDestroyEvent)LoadFunc(Device, "vkDestroyEvent");
    vkDestroyFence = (PFN_vkDestroyFence)LoadFunc(Device, "vkDestroyFence");
    vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer)LoadFunc(Device, "vkDestroyFramebuffer");
    vkDestroyImage = (PFN_vkDestroyImage)LoadFunc(Device, "vkDestroyImage");
    vkDestroyImageView = (PFN_vkDestroyImageView)LoadFunc(Device, "vkDestroyImageView");
    vkDestroyPipeline = (PFN_vkDestroyPipeline)LoadFunc(Device, "vkDestroyPipeline");
    vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache)LoadFunc(Device, "vkDestroyPipelineCache");
    vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)LoadFunc(Device, "vkDestroyPipelineLayout");
    vkDestroyQueryPool = (PFN_vkDestroyQueryPool)LoadFunc(Device, "vkDestroyQueryPool");
    vkDestroyRenderPass = (PFN_vkDestroyRenderPass)LoadFunc(Device, "vkDestroyRenderPass");
    vkDestroySampler = (PFN_vkDestroySampler)LoadFunc(Device, "vkDestroySampler");
    vkDestroySemaphore = (PFN_vkDestroySemaphore)LoadFunc(Device, "vkDestroySemaphore");
    vkDestroyShaderModule = (PFN_vkDestroyShaderModule)LoadFunc(Device, "vkDestroyShaderModule");
    vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle)LoadFunc(Device, "vkDeviceWaitIdle");
    vkEndCommandBuffer = (PFN_vkEndCommandBuffer)LoadFunc(Device, "vkEndCommandBuffer");
    vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges)LoadFunc(Device, "vkFlushMappedMemoryRanges");
    vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers)LoadFunc(Device, "vkFreeCommandBuffers");
    vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets)LoadFunc(Device, "vkFreeDescriptorSets");
    vkFreeMemory = (PFN_vkFreeMemory)LoadFunc(Device, "vkFreeMemory");
    vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)LoadFunc(Device, "vkGetBufferMemoryRequirements");
    vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment)LoadFunc(Device, "vkGetDeviceMemoryCommitment");
    vkGetDeviceQueue = (PFN_vkGetDeviceQueue)LoadFunc(Device, "vkGetDeviceQueue");
    vkGetEventStatus = (PFN_vkGetEventStatus)LoadFunc(Device, "vkGetEventStatus");
    vkGetFenceStatus = (PFN_vkGetFenceStatus)LoadFunc(Device, "vkGetFenceStatus");
    vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)LoadFunc(Device, "vkGetImageMemoryRequirements");
    vkGetImageSparseMemoryRequirements = (PFN_vkGetImageSparseMemoryRequirements)LoadFunc(Device, "vkGetImageSparseMemoryRequirements");
    vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout)LoadFunc(Device, "vkGetImageSubresourceLayout");
    vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData)LoadFunc(Device, "vkGetPipelineCacheData");
    vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults)LoadFunc(Device, "vkGetQueryPoolResults");
    vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity)LoadFunc(Device, "vkGetRenderAreaGranularity");
    vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges)LoadFunc(Device, "vkInvalidateMappedMemoryRanges");
    vkMapMemory = (PFN_vkMapMemory)LoadFunc(Device, "vkMapMemory");
    vkMergePipelineCaches = (PFN_vkMergePipelineCaches)LoadFunc(Device, "vkMergePipelineCaches");
    vkQueueBindSparse = (PFN_vkQueueBindSparse)LoadFunc(Device, "vkQueueBindSparse");
    vkQueueSubmit = (PFN_vkQueueSubmit)LoadFunc(Device, "vkQueueSubmit");
    vkQueueWaitIdle = (PFN_vkQueueWaitIdle)LoadFunc(Device, "vkQueueWaitIdle");
    vkResetCommandBuffer = (PFN_vkResetCommandBuffer)LoadFunc(Device, "vkResetCommandBuffer");
    vkResetCommandPool = (PFN_vkResetCommandPool)LoadFunc(Device, "vkResetCommandPool");
    vkResetDescriptorPool = (PFN_vkResetDescriptorPool)LoadFunc(Device, "vkResetDescriptorPool");
    vkResetEvent = (PFN_vkResetEvent)LoadFunc(Device, "vkResetEvent");
    vkResetFences = (PFN_vkResetFences)LoadFunc(Device, "vkResetFences");
    vkSetEvent = (PFN_vkSetEvent)LoadFunc(Device, "vkSetEvent");
    vkUnmapMemory = (PFN_vkUnmapMemory)LoadFunc(Device, "vkUnmapMemory");
    vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)LoadFunc(Device, "vkUpdateDescriptorSets");
    vkWaitForFences = (PFN_vkWaitForFences)LoadFunc(Device, "vkWaitForFences");
#endif /*  defined(VK_VERSION_1_0)  */
#if defined(VK_VERSION_1_1)
    vkBindBufferMemory2 = (PFN_vkBindBufferMemory2)LoadFunc(Device, "vkBindBufferMemory2");
    vkBindImageMemory2 = (PFN_vkBindImageMemory2)LoadFunc(Device, "vkBindImageMemory2");
    vkCmdDispatchBase = (PFN_vkCmdDispatchBase)LoadFunc(Device, "vkCmdDispatchBase");
    vkCmdSetDeviceMask = (PFN_vkCmdSetDeviceMask)LoadFunc(Device, "vkCmdSetDeviceMask");
    vkCreateDescriptorUpdateTemplate = (PFN_vkCreateDescriptorUpdateTemplate)LoadFunc(Device, "vkCreateDescriptorUpdateTemplate");
    vkCreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion)LoadFunc(Device, "vkCreateSamplerYcbcrConversion");
    vkDestroyDescriptorUpdateTemplate = (PFN_vkDestroyDescriptorUpdateTemplate)LoadFunc(Device, "vkDestroyDescriptorUpdateTemplate");
    vkDestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion)LoadFunc(Device, "vkDestroySamplerYcbcrConversion");
    vkGetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2)LoadFunc(Device, "vkGetBufferMemoryRequirements2");
    vkGetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport)LoadFunc(Device, "vkGetDescriptorSetLayoutSupport");
    vkGetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures)LoadFunc(Device, "vkGetDeviceGroupPeerMemoryFeatures");
    vkGetDeviceQueue2 = (PFN_vkGetDeviceQueue2)LoadFunc(Device, "vkGetDeviceQueue2");
    vkGetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2)LoadFunc(Device, "vkGetImageMemoryRequirements2");
    vkGetImageSparseMemoryRequirements2 = (PFN_vkGetImageSparseMemoryRequirements2)LoadFunc(Device, "vkGetImageSparseMemoryRequirements2");
    vkTrimCommandPool = (PFN_vkTrimCommandPool)LoadFunc(Device, "vkTrimCommandPool");
    vkUpdateDescriptorSetWithTemplate = (PFN_vkUpdateDescriptorSetWithTemplate)LoadFunc(Device, "vkUpdateDescriptorSetWithTemplate");
#endif /*  defined(VK_VERSION_1_1)  */
#if defined(VK_VERSION_1_2)
    vkCmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2)LoadFunc(Device, "vkCmdBeginRenderPass2");
    vkCmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount)LoadFunc(Device, "vkCmdDrawIndexedIndirectCount");
    vkCmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount)LoadFunc(Device, "vkCmdDrawIndirectCount");
    vkCmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2)LoadFunc(Device, "vkCmdEndRenderPass2");
    vkCmdNextSubpass2 = (PFN_vkCmdNextSubpass2)LoadFunc(Device, "vkCmdNextSubpass2");
    vkCreateRenderPass2 = (PFN_vkCreateRenderPass2)LoadFunc(Device, "vkCreateRenderPass2");
    vkGetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress)LoadFunc(Device, "vkGetBufferDeviceAddress");
    vkGetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress)LoadFunc(Device, "vkGetBufferOpaqueCaptureAddress");
    vkGetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress)LoadFunc(Device, "vkGetDeviceMemoryOpaqueCaptureAddress");
    vkGetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue)LoadFunc(Device, "vkGetSemaphoreCounterValue");
    vkResetQueryPool = (PFN_vkResetQueryPool)LoadFunc(Device, "vkResetQueryPool");
    vkSignalSemaphore = (PFN_vkSignalSemaphore)LoadFunc(Device, "vkSignalSemaphore");
    vkWaitSemaphores = (PFN_vkWaitSemaphores)LoadFunc(Device, "vkWaitSemaphores");
#endif /*  defined(VK_VERSION_1_2)  */
#if defined(VK_VERSION_1_3)
    vkCmdBeginRendering = (PFN_vkCmdBeginRendering)LoadFunc(Device, "vkCmdBeginRendering");
    vkCmdBindVertexBuffers2 = (PFN_vkCmdBindVertexBuffers2)LoadFunc(Device, "vkCmdBindVertexBuffers2");
    vkCmdBlitImage2 = (PFN_vkCmdBlitImage2)LoadFunc(Device, "vkCmdBlitImage2");
    vkCmdCopyBuffer2 = (PFN_vkCmdCopyBuffer2)LoadFunc(Device, "vkCmdCopyBuffer2");
    vkCmdCopyBufferToImage2 = (PFN_vkCmdCopyBufferToImage2)LoadFunc(Device, "vkCmdCopyBufferToImage2");
    vkCmdCopyImage2 = (PFN_vkCmdCopyImage2)LoadFunc(Device, "vkCmdCopyImage2");
    vkCmdCopyImageToBuffer2 = (PFN_vkCmdCopyImageToBuffer2)LoadFunc(Device, "vkCmdCopyImageToBuffer2");
    vkCmdEndRendering = (PFN_vkCmdEndRendering)LoadFunc(Device, "vkCmdEndRendering");
    vkCmdPipelineBarrier2 = (PFN_vkCmdPipelineBarrier2)LoadFunc(Device, "vkCmdPipelineBarrier2");
    vkCmdResetEvent2 = (PFN_vkCmdResetEvent2)LoadFunc(Device, "vkCmdResetEvent2");
    vkCmdResolveImage2 = (PFN_vkCmdResolveImage2)LoadFunc(Device, "vkCmdResolveImage2");
    vkCmdSetCullMode = (PFN_vkCmdSetCullMode)LoadFunc(Device, "vkCmdSetCullMode");
    vkCmdSetDepthBiasEnable = (PFN_vkCmdSetDepthBiasEnable)LoadFunc(Device, "vkCmdSetDepthBiasEnable");
    vkCmdSetDepthBoundsTestEnable = (PFN_vkCmdSetDepthBoundsTestEnable)LoadFunc(Device, "vkCmdSetDepthBoundsTestEnable");
    vkCmdSetDepthCompareOp = (PFN_vkCmdSetDepthCompareOp)LoadFunc(Device, "vkCmdSetDepthCompareOp");
    vkCmdSetDepthTestEnable = (PFN_vkCmdSetDepthTestEnable)LoadFunc(Device, "vkCmdSetDepthTestEnable");
    vkCmdSetDepthWriteEnable = (PFN_vkCmdSetDepthWriteEnable)LoadFunc(Device, "vkCmdSetDepthWriteEnable");
    vkCmdSetEvent2 = (PFN_vkCmdSetEvent2)LoadFunc(Device, "vkCmdSetEvent2");
    vkCmdSetFrontFace = (PFN_vkCmdSetFrontFace)LoadFunc(Device, "vkCmdSetFrontFace");
    vkCmdSetPrimitiveRestartEnable = (PFN_vkCmdSetPrimitiveRestartEnable)LoadFunc(Device, "vkCmdSetPrimitiveRestartEnable");
    vkCmdSetPrimitiveTopology = (PFN_vkCmdSetPrimitiveTopology)LoadFunc(Device, "vkCmdSetPrimitiveTopology");
    vkCmdSetRasterizerDiscardEnable = (PFN_vkCmdSetRasterizerDiscardEnable)LoadFunc(Device, "vkCmdSetRasterizerDiscardEnable");
    vkCmdSetScissorWithCount = (PFN_vkCmdSetScissorWithCount)LoadFunc(Device, "vkCmdSetScissorWithCount");
    vkCmdSetStencilOp = (PFN_vkCmdSetStencilOp)LoadFunc(Device, "vkCmdSetStencilOp");
    vkCmdSetStencilTestEnable = (PFN_vkCmdSetStencilTestEnable)LoadFunc(Device, "vkCmdSetStencilTestEnable");
    vkCmdSetViewportWithCount = (PFN_vkCmdSetViewportWithCount)LoadFunc(Device, "vkCmdSetViewportWithCount");
    vkCmdWaitEvents2 = (PFN_vkCmdWaitEvents2)LoadFunc(Device, "vkCmdWaitEvents2");
    vkCmdWriteTimestamp2 = (PFN_vkCmdWriteTimestamp2)LoadFunc(Device, "vkCmdWriteTimestamp2");
    vkCreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot)LoadFunc(Device, "vkCreatePrivateDataSlot");
    vkDestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot)LoadFunc(Device, "vkDestroyPrivateDataSlot");
    vkGetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements)LoadFunc(Device, "vkGetDeviceBufferMemoryRequirements");
    vkGetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements)LoadFunc(Device, "vkGetDeviceImageMemoryRequirements");
    vkGetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements)LoadFunc(Device, "vkGetDeviceImageSparseMemoryRequirements");
    vkGetPrivateData = (PFN_vkGetPrivateData)LoadFunc(Device, "vkGetPrivateData");
    vkQueueSubmit2 = (PFN_vkQueueSubmit2)LoadFunc(Device, "vkQueueSubmit2");
    vkSetPrivateData = (PFN_vkSetPrivateData)LoadFunc(Device, "vkSetPrivateData");
#endif /*  defined(VK_VERSION_1_3)  */
#if defined(VK_AMDX_shader_enqueue)
    vkCmdDispatchGraphAMDX = (PFN_vkCmdDispatchGraphAMDX)LoadFunc(Device, "vkCmdDispatchGraphAMDX");
    vkCmdDispatchGraphIndirectAMDX = (PFN_vkCmdDispatchGraphIndirectAMDX)LoadFunc(Device, "vkCmdDispatchGraphIndirectAMDX");
    vkCmdDispatchGraphIndirectCountAMDX = (PFN_vkCmdDispatchGraphIndirectCountAMDX)LoadFunc(Device, "vkCmdDispatchGraphIndirectCountAMDX");
    vkCmdInitializeGraphScratchMemoryAMDX = (PFN_vkCmdInitializeGraphScratchMemoryAMDX)LoadFunc(Device, "vkCmdInitializeGraphScratchMemoryAMDX");
    vkCreateExecutionGraphPipelinesAMDX = (PFN_vkCreateExecutionGraphPipelinesAMDX)LoadFunc(Device, "vkCreateExecutionGraphPipelinesAMDX");
    vkGetExecutionGraphPipelineNodeIndexAMDX = (PFN_vkGetExecutionGraphPipelineNodeIndexAMDX)LoadFunc(Device, "vkGetExecutionGraphPipelineNodeIndexAMDX");
    vkGetExecutionGraphPipelineScratchSizeAMDX = (PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)LoadFunc(Device, "vkGetExecutionGraphPipelineScratchSizeAMDX");
#endif /*  defined(VK_AMDX_shader_enqueue)  */
#if defined(VK_AMD_anti_lag)
    vkAntiLagUpdateAMD = (PFN_vkAntiLagUpdateAMD)LoadFunc(Device, "vkAntiLagUpdateAMD");
#endif /*  defined(VK_AMD_anti_lag)  */
#if defined(VK_AMD_buffer_marker)
    vkCmdWriteBufferMarkerAMD = (PFN_vkCmdWriteBufferMarkerAMD)LoadFunc(Device, "vkCmdWriteBufferMarkerAMD");
#endif /*  defined(VK_AMD_buffer_marker)  */
#if defined(VK_AMD_display_native_hdr)
    vkSetLocalDimmingAMD = (PFN_vkSetLocalDimmingAMD)LoadFunc(Device, "vkSetLocalDimmingAMD");
#endif /*  defined(VK_AMD_display_native_hdr)  */
#if defined(VK_AMD_draw_indirect_count)
    vkCmdDrawIndexedIndirectCountAMD = (PFN_vkCmdDrawIndexedIndirectCountAMD)LoadFunc(Device, "vkCmdDrawIndexedIndirectCountAMD");
    vkCmdDrawIndirectCountAMD = (PFN_vkCmdDrawIndirectCountAMD)LoadFunc(Device, "vkCmdDrawIndirectCountAMD");
#endif /*  defined(VK_AMD_draw_indirect_count)  */
#if defined(VK_AMD_shader_info)
    vkGetShaderInfoAMD = (PFN_vkGetShaderInfoAMD)LoadFunc(Device, "vkGetShaderInfoAMD");
#endif /*  defined(VK_AMD_shader_info)  */
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
    vkGetAndroidHardwareBufferPropertiesANDROID = (PFN_vkGetAndroidHardwareBufferPropertiesANDROID)LoadFunc(Device, "vkGetAndroidHardwareBufferPropertiesANDROID");
    vkGetMemoryAndroidHardwareBufferANDROID = (PFN_vkGetMemoryAndroidHardwareBufferANDROID)LoadFunc(Device, "vkGetMemoryAndroidHardwareBufferANDROID");
#endif /*  defined(VK_ANDROID_external_memory_android_hardware_buffer)  */
#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
    vkCmdSetAttachmentFeedbackLoopEnableEXT = (PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT)LoadFunc(Device, "vkCmdSetAttachmentFeedbackLoopEnableEXT");
#endif /*  defined(VK_EXT_attachment_feedback_loop_dynamic_state)  */
#if defined(VK_EXT_buffer_device_address)
    vkGetBufferDeviceAddressEXT = (PFN_vkGetBufferDeviceAddressEXT)LoadFunc(Device, "vkGetBufferDeviceAddressEXT");
#endif /*  defined(VK_EXT_buffer_device_address)  */
#if defined(VK_EXT_calibrated_timestamps)
    vkGetCalibratedTimestampsEXT = (PFN_vkGetCalibratedTimestampsEXT)LoadFunc(Device, "vkGetCalibratedTimestampsEXT");
#endif /*  defined(VK_EXT_calibrated_timestamps)  */
#if defined(VK_EXT_color_write_enable)
    vkCmdSetColorWriteEnableEXT = (PFN_vkCmdSetColorWriteEnableEXT)LoadFunc(Device, "vkCmdSetColorWriteEnableEXT");
#endif /*  defined(VK_EXT_color_write_enable)  */
#if defined(VK_EXT_conditional_rendering)
    vkCmdBeginConditionalRenderingEXT = (PFN_vkCmdBeginConditionalRenderingEXT)LoadFunc(Device, "vkCmdBeginConditionalRenderingEXT");
    vkCmdEndConditionalRenderingEXT = (PFN_vkCmdEndConditionalRenderingEXT)LoadFunc(Device, "vkCmdEndConditionalRenderingEXT");
#endif /*  defined(VK_EXT_conditional_rendering)  */
#if defined(VK_EXT_debug_marker)
    vkCmdDebugMarkerBeginEXT = (PFN_vkCmdDebugMarkerBeginEXT)LoadFunc(Device, "vkCmdDebugMarkerBeginEXT");
    vkCmdDebugMarkerEndEXT = (PFN_vkCmdDebugMarkerEndEXT)LoadFunc(Device, "vkCmdDebugMarkerEndEXT");
    vkCmdDebugMarkerInsertEXT = (PFN_vkCmdDebugMarkerInsertEXT)LoadFunc(Device, "vkCmdDebugMarkerInsertEXT");
    vkDebugMarkerSetObjectNameEXT = (PFN_vkDebugMarkerSetObjectNameEXT)LoadFunc(Device, "vkDebugMarkerSetObjectNameEXT");
    vkDebugMarkerSetObjectTagEXT = (PFN_vkDebugMarkerSetObjectTagEXT)LoadFunc(Device, "vkDebugMarkerSetObjectTagEXT");
#endif /*  defined(VK_EXT_debug_marker)  */
#if defined(VK_EXT_depth_bias_control)
    vkCmdSetDepthBias2EXT = (PFN_vkCmdSetDepthBias2EXT)LoadFunc(Device, "vkCmdSetDepthBias2EXT");
#endif /*  defined(VK_EXT_depth_bias_control)  */
#if defined(VK_EXT_descriptor_buffer)
    vkCmdBindDescriptorBufferEmbeddedSamplersEXT = (PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT)LoadFunc(Device, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT");
    vkCmdBindDescriptorBuffersEXT = (PFN_vkCmdBindDescriptorBuffersEXT)LoadFunc(Device, "vkCmdBindDescriptorBuffersEXT");
    vkCmdSetDescriptorBufferOffsetsEXT = (PFN_vkCmdSetDescriptorBufferOffsetsEXT)LoadFunc(Device, "vkCmdSetDescriptorBufferOffsetsEXT");
    vkGetBufferOpaqueCaptureDescriptorDataEXT = (PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT)LoadFunc(Device, "vkGetBufferOpaqueCaptureDescriptorDataEXT");
    vkGetDescriptorEXT = (PFN_vkGetDescriptorEXT)LoadFunc(Device, "vkGetDescriptorEXT");
    vkGetDescriptorSetLayoutBindingOffsetEXT = (PFN_vkGetDescriptorSetLayoutBindingOffsetEXT)LoadFunc(Device, "vkGetDescriptorSetLayoutBindingOffsetEXT");
    vkGetDescriptorSetLayoutSizeEXT = (PFN_vkGetDescriptorSetLayoutSizeEXT)LoadFunc(Device, "vkGetDescriptorSetLayoutSizeEXT");
    vkGetImageOpaqueCaptureDescriptorDataEXT = (PFN_vkGetImageOpaqueCaptureDescriptorDataEXT)LoadFunc(Device, "vkGetImageOpaqueCaptureDescriptorDataEXT");
    vkGetImageViewOpaqueCaptureDescriptorDataEXT = (PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT)LoadFunc(Device, "vkGetImageViewOpaqueCaptureDescriptorDataEXT");
    vkGetSamplerOpaqueCaptureDescriptorDataEXT = (PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT)LoadFunc(Device, "vkGetSamplerOpaqueCaptureDescriptorDataEXT");
#endif /*  defined(VK_EXT_descriptor_buffer)  */
#if defined(VK_EXT_descriptor_buffer) && (defined(VK_KHR_acceleration_structure) || defined(VK_NV_ray_tracing))
    vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = (PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT)LoadFunc(Device, "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT");
#endif /*  defined(VK_EXT_descriptor_buffer) && (defined(VK_KHR_acceleration_structure) || defined(VK_NV_ray_tracing))  */
#if defined(VK_EXT_device_fault)
    vkGetDeviceFaultInfoEXT = (PFN_vkGetDeviceFaultInfoEXT)LoadFunc(Device, "vkGetDeviceFaultInfoEXT");
#endif /*  defined(VK_EXT_device_fault)  */
#if defined(VK_EXT_discard_rectangles)
    vkCmdSetDiscardRectangleEXT = (PFN_vkCmdSetDiscardRectangleEXT)LoadFunc(Device, "vkCmdSetDiscardRectangleEXT");
#endif /*  defined(VK_EXT_discard_rectangles)  */
#if defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2
    vkCmdSetDiscardRectangleEnableEXT = (PFN_vkCmdSetDiscardRectangleEnableEXT)LoadFunc(Device, "vkCmdSetDiscardRectangleEnableEXT");
    vkCmdSetDiscardRectangleModeEXT = (PFN_vkCmdSetDiscardRectangleModeEXT)LoadFunc(Device, "vkCmdSetDiscardRectangleModeEXT");
#endif /*  defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2  */
#if defined(VK_EXT_display_control)
    vkDisplayPowerControlEXT = (PFN_vkDisplayPowerControlEXT)LoadFunc(Device, "vkDisplayPowerControlEXT");
    vkGetSwapchainCounterEXT = (PFN_vkGetSwapchainCounterEXT)LoadFunc(Device, "vkGetSwapchainCounterEXT");
    vkRegisterDeviceEventEXT = (PFN_vkRegisterDeviceEventEXT)LoadFunc(Device, "vkRegisterDeviceEventEXT");
    vkRegisterDisplayEventEXT = (PFN_vkRegisterDisplayEventEXT)LoadFunc(Device, "vkRegisterDisplayEventEXT");
#endif /*  defined(VK_EXT_display_control)  */
#if defined(VK_EXT_external_memory_host)
    vkGetMemoryHostPointerPropertiesEXT = (PFN_vkGetMemoryHostPointerPropertiesEXT)LoadFunc(Device, "vkGetMemoryHostPointerPropertiesEXT");
#endif /*  defined(VK_EXT_external_memory_host)  */
#if defined(VK_EXT_full_screen_exclusive)
    vkAcquireFullScreenExclusiveModeEXT = (PFN_vkAcquireFullScreenExclusiveModeEXT)LoadFunc(Device, "vkAcquireFullScreenExclusiveModeEXT");
    vkReleaseFullScreenExclusiveModeEXT = (PFN_vkReleaseFullScreenExclusiveModeEXT)LoadFunc(Device, "vkReleaseFullScreenExclusiveModeEXT");
#endif /*  defined(VK_EXT_full_screen_exclusive)  */
#if defined(VK_EXT_hdr_metadata)
    vkSetHdrMetadataEXT = (PFN_vkSetHdrMetadataEXT)LoadFunc(Device, "vkSetHdrMetadataEXT");
#endif /*  defined(VK_EXT_hdr_metadata)  */
#if defined(VK_EXT_host_image_copy)
    vkCopyImageToImageEXT = (PFN_vkCopyImageToImageEXT)LoadFunc(Device, "vkCopyImageToImageEXT");
    vkCopyImageToMemoryEXT = (PFN_vkCopyImageToMemoryEXT)LoadFunc(Device, "vkCopyImageToMemoryEXT");
    vkCopyMemoryToImageEXT = (PFN_vkCopyMemoryToImageEXT)LoadFunc(Device, "vkCopyMemoryToImageEXT");
    vkTransitionImageLayoutEXT = (PFN_vkTransitionImageLayoutEXT)LoadFunc(Device, "vkTransitionImageLayoutEXT");
#endif /*  defined(VK_EXT_host_image_copy)  */
#if defined(VK_EXT_host_query_reset)
    vkResetQueryPoolEXT = (PFN_vkResetQueryPoolEXT)LoadFunc(Device, "vkResetQueryPoolEXT");
#endif /*  defined(VK_EXT_host_query_reset)  */
#if defined(VK_EXT_image_drm_format_modifier)
    vkGetImageDrmFormatModifierPropertiesEXT = (PFN_vkGetImageDrmFormatModifierPropertiesEXT)LoadFunc(Device, "vkGetImageDrmFormatModifierPropertiesEXT");
#endif /*  defined(VK_EXT_image_drm_format_modifier)  */
#if defined(VK_EXT_line_rasterization)
    vkCmdSetLineStippleEXT = (PFN_vkCmdSetLineStippleEXT)LoadFunc(Device, "vkCmdSetLineStippleEXT");
#endif /*  defined(VK_EXT_line_rasterization)  */
#if defined(VK_EXT_mesh_shader)
    vkCmdDrawMeshTasksEXT = (PFN_vkCmdDrawMeshTasksEXT)LoadFunc(Device, "vkCmdDrawMeshTasksEXT");
    vkCmdDrawMeshTasksIndirectCountEXT = (PFN_vkCmdDrawMeshTasksIndirectCountEXT)LoadFunc(Device, "vkCmdDrawMeshTasksIndirectCountEXT");
    vkCmdDrawMeshTasksIndirectEXT = (PFN_vkCmdDrawMeshTasksIndirectEXT)LoadFunc(Device, "vkCmdDrawMeshTasksIndirectEXT");
#endif /*  defined(VK_EXT_mesh_shader)  */
#if defined(VK_EXT_metal_objects)
    vkExportMetalObjectsEXT = (PFN_vkExportMetalObjectsEXT)LoadFunc(Device, "vkExportMetalObjectsEXT");
#endif /*  defined(VK_EXT_metal_objects)  */
#if defined(VK_EXT_multi_draw)
    vkCmdDrawMultiEXT = (PFN_vkCmdDrawMultiEXT)LoadFunc(Device, "vkCmdDrawMultiEXT");
    vkCmdDrawMultiIndexedEXT = (PFN_vkCmdDrawMultiIndexedEXT)LoadFunc(Device, "vkCmdDrawMultiIndexedEXT");
#endif /*  defined(VK_EXT_multi_draw)  */
#if defined(VK_EXT_opacity_micromap)
    vkBuildMicromapsEXT = (PFN_vkBuildMicromapsEXT)LoadFunc(Device, "vkBuildMicromapsEXT");
    vkCmdBuildMicromapsEXT = (PFN_vkCmdBuildMicromapsEXT)LoadFunc(Device, "vkCmdBuildMicromapsEXT");
    vkCmdCopyMemoryToMicromapEXT = (PFN_vkCmdCopyMemoryToMicromapEXT)LoadFunc(Device, "vkCmdCopyMemoryToMicromapEXT");
    vkCmdCopyMicromapEXT = (PFN_vkCmdCopyMicromapEXT)LoadFunc(Device, "vkCmdCopyMicromapEXT");
    vkCmdCopyMicromapToMemoryEXT = (PFN_vkCmdCopyMicromapToMemoryEXT)LoadFunc(Device, "vkCmdCopyMicromapToMemoryEXT");
    vkCmdWriteMicromapsPropertiesEXT = (PFN_vkCmdWriteMicromapsPropertiesEXT)LoadFunc(Device, "vkCmdWriteMicromapsPropertiesEXT");
    vkCopyMemoryToMicromapEXT = (PFN_vkCopyMemoryToMicromapEXT)LoadFunc(Device, "vkCopyMemoryToMicromapEXT");
    vkCopyMicromapEXT = (PFN_vkCopyMicromapEXT)LoadFunc(Device, "vkCopyMicromapEXT");
    vkCopyMicromapToMemoryEXT = (PFN_vkCopyMicromapToMemoryEXT)LoadFunc(Device, "vkCopyMicromapToMemoryEXT");
    vkCreateMicromapEXT = (PFN_vkCreateMicromapEXT)LoadFunc(Device, "vkCreateMicromapEXT");
    vkDestroyMicromapEXT = (PFN_vkDestroyMicromapEXT)LoadFunc(Device, "vkDestroyMicromapEXT");
    vkGetDeviceMicromapCompatibilityEXT = (PFN_vkGetDeviceMicromapCompatibilityEXT)LoadFunc(Device, "vkGetDeviceMicromapCompatibilityEXT");
    vkGetMicromapBuildSizesEXT = (PFN_vkGetMicromapBuildSizesEXT)LoadFunc(Device, "vkGetMicromapBuildSizesEXT");
    vkWriteMicromapsPropertiesEXT = (PFN_vkWriteMicromapsPropertiesEXT)LoadFunc(Device, "vkWriteMicromapsPropertiesEXT");
#endif /*  defined(VK_EXT_opacity_micromap)  */
#if defined(VK_EXT_pageable_device_local_memory)
    vkSetDeviceMemoryPriorityEXT = (PFN_vkSetDeviceMemoryPriorityEXT)LoadFunc(Device, "vkSetDeviceMemoryPriorityEXT");
#endif /*  defined(VK_EXT_pageable_device_local_memory)  */
#if defined(VK_EXT_pipeline_properties)
    vkGetPipelinePropertiesEXT = (PFN_vkGetPipelinePropertiesEXT)LoadFunc(Device, "vkGetPipelinePropertiesEXT");
#endif /*  defined(VK_EXT_pipeline_properties)  */
#if defined(VK_EXT_private_data)
    vkCreatePrivateDataSlotEXT = (PFN_vkCreatePrivateDataSlotEXT)LoadFunc(Device, "vkCreatePrivateDataSlotEXT");
    vkDestroyPrivateDataSlotEXT = (PFN_vkDestroyPrivateDataSlotEXT)LoadFunc(Device, "vkDestroyPrivateDataSlotEXT");
    vkGetPrivateDataEXT = (PFN_vkGetPrivateDataEXT)LoadFunc(Device, "vkGetPrivateDataEXT");
    vkSetPrivateDataEXT = (PFN_vkSetPrivateDataEXT)LoadFunc(Device, "vkSetPrivateDataEXT");
#endif /*  defined(VK_EXT_private_data)  */
#if defined(VK_EXT_sample_locations)
    vkCmdSetSampleLocationsEXT = (PFN_vkCmdSetSampleLocationsEXT)LoadFunc(Device, "vkCmdSetSampleLocationsEXT");
#endif /*  defined(VK_EXT_sample_locations)  */
#if defined(VK_EXT_shader_module_identifier)
    vkGetShaderModuleCreateInfoIdentifierEXT = (PFN_vkGetShaderModuleCreateInfoIdentifierEXT)LoadFunc(Device, "vkGetShaderModuleCreateInfoIdentifierEXT");
    vkGetShaderModuleIdentifierEXT = (PFN_vkGetShaderModuleIdentifierEXT)LoadFunc(Device, "vkGetShaderModuleIdentifierEXT");
#endif /*  defined(VK_EXT_shader_module_identifier)  */
#if defined(VK_EXT_shader_object)
    vkCmdBindShadersEXT = (PFN_vkCmdBindShadersEXT)LoadFunc(Device, "vkCmdBindShadersEXT");
    vkCreateShadersEXT = (PFN_vkCreateShadersEXT)LoadFunc(Device, "vkCreateShadersEXT");
    vkDestroyShaderEXT = (PFN_vkDestroyShaderEXT)LoadFunc(Device, "vkDestroyShaderEXT");
    vkGetShaderBinaryDataEXT = (PFN_vkGetShaderBinaryDataEXT)LoadFunc(Device, "vkGetShaderBinaryDataEXT");
#endif /*  defined(VK_EXT_shader_object)  */
#if defined(VK_EXT_swapchain_maintenance1)
    vkReleaseSwapchainImagesEXT = (PFN_vkReleaseSwapchainImagesEXT)LoadFunc(Device, "vkReleaseSwapchainImagesEXT");
#endif /*  defined(VK_EXT_swapchain_maintenance1)  */
#if defined(VK_EXT_transform_feedback)
    vkCmdBeginQueryIndexedEXT = (PFN_vkCmdBeginQueryIndexedEXT)LoadFunc(Device, "vkCmdBeginQueryIndexedEXT");
    vkCmdBeginTransformFeedbackEXT = (PFN_vkCmdBeginTransformFeedbackEXT)LoadFunc(Device, "vkCmdBeginTransformFeedbackEXT");
    vkCmdBindTransformFeedbackBuffersEXT = (PFN_vkCmdBindTransformFeedbackBuffersEXT)LoadFunc(Device, "vkCmdBindTransformFeedbackBuffersEXT");
    vkCmdDrawIndirectByteCountEXT = (PFN_vkCmdDrawIndirectByteCountEXT)LoadFunc(Device, "vkCmdDrawIndirectByteCountEXT");
    vkCmdEndQueryIndexedEXT = (PFN_vkCmdEndQueryIndexedEXT)LoadFunc(Device, "vkCmdEndQueryIndexedEXT");
    vkCmdEndTransformFeedbackEXT = (PFN_vkCmdEndTransformFeedbackEXT)LoadFunc(Device, "vkCmdEndTransformFeedbackEXT");
#endif /*  defined(VK_EXT_transform_feedback)  */
#if defined(VK_EXT_validation_cache)
    vkCreateValidationCacheEXT = (PFN_vkCreateValidationCacheEXT)LoadFunc(Device, "vkCreateValidationCacheEXT");
    vkDestroyValidationCacheEXT = (PFN_vkDestroyValidationCacheEXT)LoadFunc(Device, "vkDestroyValidationCacheEXT");
    vkGetValidationCacheDataEXT = (PFN_vkGetValidationCacheDataEXT)LoadFunc(Device, "vkGetValidationCacheDataEXT");
    vkMergeValidationCachesEXT = (PFN_vkMergeValidationCachesEXT)LoadFunc(Device, "vkMergeValidationCachesEXT");
#endif /*  defined(VK_EXT_validation_cache)  */
#if defined(VK_FUCHSIA_buffer_collection)
    vkCreateBufferCollectionFUCHSIA = (PFN_vkCreateBufferCollectionFUCHSIA)LoadFunc(Device, "vkCreateBufferCollectionFUCHSIA");
    vkDestroyBufferCollectionFUCHSIA = (PFN_vkDestroyBufferCollectionFUCHSIA)LoadFunc(Device, "vkDestroyBufferCollectionFUCHSIA");
    vkGetBufferCollectionPropertiesFUCHSIA = (PFN_vkGetBufferCollectionPropertiesFUCHSIA)LoadFunc(Device, "vkGetBufferCollectionPropertiesFUCHSIA");
    vkSetBufferCollectionBufferConstraintsFUCHSIA = (PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA)LoadFunc(Device, "vkSetBufferCollectionBufferConstraintsFUCHSIA");
    vkSetBufferCollectionImageConstraintsFUCHSIA = (PFN_vkSetBufferCollectionImageConstraintsFUCHSIA)LoadFunc(Device, "vkSetBufferCollectionImageConstraintsFUCHSIA");
#endif /*  defined(VK_FUCHSIA_buffer_collection)  */
#if defined(VK_FUCHSIA_external_memory)
    vkGetMemoryZirconHandleFUCHSIA = (PFN_vkGetMemoryZirconHandleFUCHSIA)LoadFunc(Device, "vkGetMemoryZirconHandleFUCHSIA");
    vkGetMemoryZirconHandlePropertiesFUCHSIA = (PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA)LoadFunc(Device, "vkGetMemoryZirconHandlePropertiesFUCHSIA");
#endif /*  defined(VK_FUCHSIA_external_memory)  */
#if defined(VK_FUCHSIA_external_semaphore)
    vkGetSemaphoreZirconHandleFUCHSIA = (PFN_vkGetSemaphoreZirconHandleFUCHSIA)LoadFunc(Device, "vkGetSemaphoreZirconHandleFUCHSIA");
    vkImportSemaphoreZirconHandleFUCHSIA = (PFN_vkImportSemaphoreZirconHandleFUCHSIA)LoadFunc(Device, "vkImportSemaphoreZirconHandleFUCHSIA");
#endif /*  defined(VK_FUCHSIA_external_semaphore)  */
#if defined(VK_GOOGLE_display_timing)
    vkGetPastPresentationTimingGOOGLE = (PFN_vkGetPastPresentationTimingGOOGLE)LoadFunc(Device, "vkGetPastPresentationTimingGOOGLE");
    vkGetRefreshCycleDurationGOOGLE = (PFN_vkGetRefreshCycleDurationGOOGLE)LoadFunc(Device, "vkGetRefreshCycleDurationGOOGLE");
#endif /*  defined(VK_GOOGLE_display_timing)  */
#if defined(VK_HUAWEI_cluster_culling_shader)
    vkCmdDrawClusterHUAWEI = (PFN_vkCmdDrawClusterHUAWEI)LoadFunc(Device, "vkCmdDrawClusterHUAWEI");
    vkCmdDrawClusterIndirectHUAWEI = (PFN_vkCmdDrawClusterIndirectHUAWEI)LoadFunc(Device, "vkCmdDrawClusterIndirectHUAWEI");
#endif /*  defined(VK_HUAWEI_cluster_culling_shader)  */
#if defined(VK_HUAWEI_invocation_mask)
    vkCmdBindInvocationMaskHUAWEI = (PFN_vkCmdBindInvocationMaskHUAWEI)LoadFunc(Device, "vkCmdBindInvocationMaskHUAWEI");
#endif /*  defined(VK_HUAWEI_invocation_mask)  */
#if defined(VK_HUAWEI_subpass_shading)
    vkCmdSubpassShadingHUAWEI = (PFN_vkCmdSubpassShadingHUAWEI)LoadFunc(Device, "vkCmdSubpassShadingHUAWEI");
    vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI = (PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI)LoadFunc(Device, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI");
#endif /*  defined(VK_HUAWEI_subpass_shading)  */
#if defined(VK_INTEL_performance_query)
    vkAcquirePerformanceConfigurationINTEL = (PFN_vkAcquirePerformanceConfigurationINTEL)LoadFunc(Device, "vkAcquirePerformanceConfigurationINTEL");
    vkCmdSetPerformanceMarkerINTEL = (PFN_vkCmdSetPerformanceMarkerINTEL)LoadFunc(Device, "vkCmdSetPerformanceMarkerINTEL");
    vkCmdSetPerformanceOverrideINTEL = (PFN_vkCmdSetPerformanceOverrideINTEL)LoadFunc(Device, "vkCmdSetPerformanceOverrideINTEL");
    vkCmdSetPerformanceStreamMarkerINTEL = (PFN_vkCmdSetPerformanceStreamMarkerINTEL)LoadFunc(Device, "vkCmdSetPerformanceStreamMarkerINTEL");
    vkGetPerformanceParameterINTEL = (PFN_vkGetPerformanceParameterINTEL)LoadFunc(Device, "vkGetPerformanceParameterINTEL");
    vkInitializePerformanceApiINTEL = (PFN_vkInitializePerformanceApiINTEL)LoadFunc(Device, "vkInitializePerformanceApiINTEL");
    vkQueueSetPerformanceConfigurationINTEL = (PFN_vkQueueSetPerformanceConfigurationINTEL)LoadFunc(Device, "vkQueueSetPerformanceConfigurationINTEL");
    vkReleasePerformanceConfigurationINTEL = (PFN_vkReleasePerformanceConfigurationINTEL)LoadFunc(Device, "vkReleasePerformanceConfigurationINTEL");
    vkUninitializePerformanceApiINTEL = (PFN_vkUninitializePerformanceApiINTEL)LoadFunc(Device, "vkUninitializePerformanceApiINTEL");
#endif /*  defined(VK_INTEL_performance_query)  */
#if defined(VK_KHR_acceleration_structure)
    vkBuildAccelerationStructuresKHR = (PFN_vkBuildAccelerationStructuresKHR)LoadFunc(Device, "vkBuildAccelerationStructuresKHR");
    vkCmdBuildAccelerationStructuresIndirectKHR = (PFN_vkCmdBuildAccelerationStructuresIndirectKHR)LoadFunc(Device, "vkCmdBuildAccelerationStructuresIndirectKHR");
    vkCmdBuildAccelerationStructuresKHR = (PFN_vkCmdBuildAccelerationStructuresKHR)LoadFunc(Device, "vkCmdBuildAccelerationStructuresKHR");
    vkCmdCopyAccelerationStructureKHR = (PFN_vkCmdCopyAccelerationStructureKHR)LoadFunc(Device, "vkCmdCopyAccelerationStructureKHR");
    vkCmdCopyAccelerationStructureToMemoryKHR = (PFN_vkCmdCopyAccelerationStructureToMemoryKHR)LoadFunc(Device, "vkCmdCopyAccelerationStructureToMemoryKHR");
    vkCmdCopyMemoryToAccelerationStructureKHR = (PFN_vkCmdCopyMemoryToAccelerationStructureKHR)LoadFunc(Device, "vkCmdCopyMemoryToAccelerationStructureKHR");
    vkCmdWriteAccelerationStructuresPropertiesKHR = (PFN_vkCmdWriteAccelerationStructuresPropertiesKHR)LoadFunc(Device, "vkCmdWriteAccelerationStructuresPropertiesKHR");
    vkCopyAccelerationStructureKHR = (PFN_vkCopyAccelerationStructureKHR)LoadFunc(Device, "vkCopyAccelerationStructureKHR");
    vkCopyAccelerationStructureToMemoryKHR = (PFN_vkCopyAccelerationStructureToMemoryKHR)LoadFunc(Device, "vkCopyAccelerationStructureToMemoryKHR");
    vkCopyMemoryToAccelerationStructureKHR = (PFN_vkCopyMemoryToAccelerationStructureKHR)LoadFunc(Device, "vkCopyMemoryToAccelerationStructureKHR");
    vkCreateAccelerationStructureKHR = (PFN_vkCreateAccelerationStructureKHR)LoadFunc(Device, "vkCreateAccelerationStructureKHR");
    vkDestroyAccelerationStructureKHR = (PFN_vkDestroyAccelerationStructureKHR)LoadFunc(Device, "vkDestroyAccelerationStructureKHR");
    vkGetAccelerationStructureBuildSizesKHR = (PFN_vkGetAccelerationStructureBuildSizesKHR)LoadFunc(Device, "vkGetAccelerationStructureBuildSizesKHR");
    vkGetAccelerationStructureDeviceAddressKHR = (PFN_vkGetAccelerationStructureDeviceAddressKHR)LoadFunc(Device, "vkGetAccelerationStructureDeviceAddressKHR");
    vkGetDeviceAccelerationStructureCompatibilityKHR = (PFN_vkGetDeviceAccelerationStructureCompatibilityKHR)LoadFunc(Device, "vkGetDeviceAccelerationStructureCompatibilityKHR");
    vkWriteAccelerationStructuresPropertiesKHR = (PFN_vkWriteAccelerationStructuresPropertiesKHR)LoadFunc(Device, "vkWriteAccelerationStructuresPropertiesKHR");
#endif /*  defined(VK_KHR_acceleration_structure)  */
#if defined(VK_KHR_bind_memory2)
    vkBindBufferMemory2KHR = (PFN_vkBindBufferMemory2KHR)LoadFunc(Device, "vkBindBufferMemory2KHR");
    vkBindImageMemory2KHR = (PFN_vkBindImageMemory2KHR)LoadFunc(Device, "vkBindImageMemory2KHR");
#endif /*  defined(VK_KHR_bind_memory2)  */
#if defined(VK_KHR_buffer_device_address)
    vkGetBufferDeviceAddressKHR = (PFN_vkGetBufferDeviceAddressKHR)LoadFunc(Device, "vkGetBufferDeviceAddressKHR");
    vkGetBufferOpaqueCaptureAddressKHR = (PFN_vkGetBufferOpaqueCaptureAddressKHR)LoadFunc(Device, "vkGetBufferOpaqueCaptureAddressKHR");
    vkGetDeviceMemoryOpaqueCaptureAddressKHR = (PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR)LoadFunc(Device, "vkGetDeviceMemoryOpaqueCaptureAddressKHR");
#endif /*  defined(VK_KHR_buffer_device_address)  */
#if defined(VK_KHR_calibrated_timestamps)
    vkGetCalibratedTimestampsKHR = (PFN_vkGetCalibratedTimestampsKHR)LoadFunc(Device, "vkGetCalibratedTimestampsKHR");
#endif /*  defined(VK_KHR_calibrated_timestamps)  */
#if defined(VK_KHR_copy_commands2)
    vkCmdBlitImage2KHR = (PFN_vkCmdBlitImage2KHR)LoadFunc(Device, "vkCmdBlitImage2KHR");
    vkCmdCopyBuffer2KHR = (PFN_vkCmdCopyBuffer2KHR)LoadFunc(Device, "vkCmdCopyBuffer2KHR");
    vkCmdCopyBufferToImage2KHR = (PFN_vkCmdCopyBufferToImage2KHR)LoadFunc(Device, "vkCmdCopyBufferToImage2KHR");
    vkCmdCopyImage2KHR = (PFN_vkCmdCopyImage2KHR)LoadFunc(Device, "vkCmdCopyImage2KHR");
    vkCmdCopyImageToBuffer2KHR = (PFN_vkCmdCopyImageToBuffer2KHR)LoadFunc(Device, "vkCmdCopyImageToBuffer2KHR");
    vkCmdResolveImage2KHR = (PFN_vkCmdResolveImage2KHR)LoadFunc(Device, "vkCmdResolveImage2KHR");
#endif /*  defined(VK_KHR_copy_commands2)  */
#if defined(VK_KHR_create_renderpass2)
    vkCmdBeginRenderPass2KHR = (PFN_vkCmdBeginRenderPass2KHR)LoadFunc(Device, "vkCmdBeginRenderPass2KHR");
    vkCmdEndRenderPass2KHR = (PFN_vkCmdEndRenderPass2KHR)LoadFunc(Device, "vkCmdEndRenderPass2KHR");
    vkCmdNextSubpass2KHR = (PFN_vkCmdNextSubpass2KHR)LoadFunc(Device, "vkCmdNextSubpass2KHR");
    vkCreateRenderPass2KHR = (PFN_vkCreateRenderPass2KHR)LoadFunc(Device, "vkCreateRenderPass2KHR");
#endif /*  defined(VK_KHR_create_renderpass2)  */
#if defined(VK_KHR_deferred_host_operations)
    vkCreateDeferredOperationKHR = (PFN_vkCreateDeferredOperationKHR)LoadFunc(Device, "vkCreateDeferredOperationKHR");
    vkDeferredOperationJoinKHR = (PFN_vkDeferredOperationJoinKHR)LoadFunc(Device, "vkDeferredOperationJoinKHR");
    vkDestroyDeferredOperationKHR = (PFN_vkDestroyDeferredOperationKHR)LoadFunc(Device, "vkDestroyDeferredOperationKHR");
    vkGetDeferredOperationMaxConcurrencyKHR = (PFN_vkGetDeferredOperationMaxConcurrencyKHR)LoadFunc(Device, "vkGetDeferredOperationMaxConcurrencyKHR");
    vkGetDeferredOperationResultKHR = (PFN_vkGetDeferredOperationResultKHR)LoadFunc(Device, "vkGetDeferredOperationResultKHR");
#endif /*  defined(VK_KHR_deferred_host_operations)  */
#if defined(VK_KHR_descriptor_update_template)
    vkCreateDescriptorUpdateTemplateKHR = (PFN_vkCreateDescriptorUpdateTemplateKHR)LoadFunc(Device, "vkCreateDescriptorUpdateTemplateKHR");
    vkDestroyDescriptorUpdateTemplateKHR = (PFN_vkDestroyDescriptorUpdateTemplateKHR)LoadFunc(Device, "vkDestroyDescriptorUpdateTemplateKHR");
    vkUpdateDescriptorSetWithTemplateKHR = (PFN_vkUpdateDescriptorSetWithTemplateKHR)LoadFunc(Device, "vkUpdateDescriptorSetWithTemplateKHR");
#endif /*  defined(VK_KHR_descriptor_update_template)  */
#if defined(VK_KHR_device_group)
    vkCmdDispatchBaseKHR = (PFN_vkCmdDispatchBaseKHR)LoadFunc(Device, "vkCmdDispatchBaseKHR");
    vkCmdSetDeviceMaskKHR = (PFN_vkCmdSetDeviceMaskKHR)LoadFunc(Device, "vkCmdSetDeviceMaskKHR");
    vkGetDeviceGroupPeerMemoryFeaturesKHR = (PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR)LoadFunc(Device, "vkGetDeviceGroupPeerMemoryFeaturesKHR");
#endif /*  defined(VK_KHR_device_group)  */
#if defined(VK_KHR_display_swapchain)
    vkCreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR)LoadFunc(Device, "vkCreateSharedSwapchainsKHR");
#endif /*  defined(VK_KHR_display_swapchain)  */
#if defined(VK_KHR_draw_indirect_count)
    vkCmdDrawIndexedIndirectCountKHR = (PFN_vkCmdDrawIndexedIndirectCountKHR)LoadFunc(Device, "vkCmdDrawIndexedIndirectCountKHR");
    vkCmdDrawIndirectCountKHR = (PFN_vkCmdDrawIndirectCountKHR)LoadFunc(Device, "vkCmdDrawIndirectCountKHR");
#endif /*  defined(VK_KHR_draw_indirect_count)  */
#if defined(VK_KHR_dynamic_rendering)
    vkCmdBeginRenderingKHR = (PFN_vkCmdBeginRenderingKHR)LoadFunc(Device, "vkCmdBeginRenderingKHR");
    vkCmdEndRenderingKHR = (PFN_vkCmdEndRenderingKHR)LoadFunc(Device, "vkCmdEndRenderingKHR");
#endif /*  defined(VK_KHR_dynamic_rendering)  */
#if defined(VK_KHR_dynamic_rendering_local_read)
    vkCmdSetRenderingAttachmentLocationsKHR = (PFN_vkCmdSetRenderingAttachmentLocationsKHR)LoadFunc(Device, "vkCmdSetRenderingAttachmentLocationsKHR");
    vkCmdSetRenderingInputAttachmentIndicesKHR = (PFN_vkCmdSetRenderingInputAttachmentIndicesKHR)LoadFunc(Device, "vkCmdSetRenderingInputAttachmentIndicesKHR");
#endif /*  defined(VK_KHR_dynamic_rendering_local_read)  */
#if defined(VK_KHR_external_fence_fd)
    vkGetFenceFdKHR = (PFN_vkGetFenceFdKHR)LoadFunc(Device, "vkGetFenceFdKHR");
    vkImportFenceFdKHR = (PFN_vkImportFenceFdKHR)LoadFunc(Device, "vkImportFenceFdKHR");
#endif /*  defined(VK_KHR_external_fence_fd)  */
#if defined(VK_KHR_external_fence_win32)
    vkGetFenceWin32HandleKHR = (PFN_vkGetFenceWin32HandleKHR)LoadFunc(Device, "vkGetFenceWin32HandleKHR");
    vkImportFenceWin32HandleKHR = (PFN_vkImportFenceWin32HandleKHR)LoadFunc(Device, "vkImportFenceWin32HandleKHR");
#endif /*  defined(VK_KHR_external_fence_win32)  */
#if defined(VK_KHR_external_memory_fd)
    vkGetMemoryFdKHR = (PFN_vkGetMemoryFdKHR)LoadFunc(Device, "vkGetMemoryFdKHR");
    vkGetMemoryFdPropertiesKHR = (PFN_vkGetMemoryFdPropertiesKHR)LoadFunc(Device, "vkGetMemoryFdPropertiesKHR");
#endif /*  defined(VK_KHR_external_memory_fd)  */
#if defined(VK_KHR_external_memory_win32)
    vkGetMemoryWin32HandleKHR = (PFN_vkGetMemoryWin32HandleKHR)LoadFunc(Device, "vkGetMemoryWin32HandleKHR");
    vkGetMemoryWin32HandlePropertiesKHR = (PFN_vkGetMemoryWin32HandlePropertiesKHR)LoadFunc(Device, "vkGetMemoryWin32HandlePropertiesKHR");
#endif /*  defined(VK_KHR_external_memory_win32)  */
#if defined(VK_KHR_external_semaphore_fd)
    vkGetSemaphoreFdKHR = (PFN_vkGetSemaphoreFdKHR)LoadFunc(Device, "vkGetSemaphoreFdKHR");
    vkImportSemaphoreFdKHR = (PFN_vkImportSemaphoreFdKHR)LoadFunc(Device, "vkImportSemaphoreFdKHR");
#endif /*  defined(VK_KHR_external_semaphore_fd)  */
#if defined(VK_KHR_external_semaphore_win32)
    vkGetSemaphoreWin32HandleKHR = (PFN_vkGetSemaphoreWin32HandleKHR)LoadFunc(Device, "vkGetSemaphoreWin32HandleKHR");
    vkImportSemaphoreWin32HandleKHR = (PFN_vkImportSemaphoreWin32HandleKHR)LoadFunc(Device, "vkImportSemaphoreWin32HandleKHR");
#endif /*  defined(VK_KHR_external_semaphore_win32)  */
#if defined(VK_KHR_fragment_shading_rate)
    vkCmdSetFragmentShadingRateKHR = (PFN_vkCmdSetFragmentShadingRateKHR)LoadFunc(Device, "vkCmdSetFragmentShadingRateKHR");
#endif /*  defined(VK_KHR_fragment_shading_rate)  */
#if defined(VK_KHR_get_memory_requirements2)
    vkGetBufferMemoryRequirements2KHR = (PFN_vkGetBufferMemoryRequirements2KHR)LoadFunc(Device, "vkGetBufferMemoryRequirements2KHR");
    vkGetImageMemoryRequirements2KHR = (PFN_vkGetImageMemoryRequirements2KHR)LoadFunc(Device, "vkGetImageMemoryRequirements2KHR");
    vkGetImageSparseMemoryRequirements2KHR = (PFN_vkGetImageSparseMemoryRequirements2KHR)LoadFunc(Device, "vkGetImageSparseMemoryRequirements2KHR");
#endif /*  defined(VK_KHR_get_memory_requirements2)  */
#if defined(VK_KHR_line_rasterization)
    vkCmdSetLineStippleKHR = (PFN_vkCmdSetLineStippleKHR)LoadFunc(Device, "vkCmdSetLineStippleKHR");
#endif /*  defined(VK_KHR_line_rasterization)  */
#if defined(VK_KHR_maintenance1)
    vkTrimCommandPoolKHR = (PFN_vkTrimCommandPoolKHR)LoadFunc(Device, "vkTrimCommandPoolKHR");
#endif /*  defined(VK_KHR_maintenance1)  */
#if defined(VK_KHR_maintenance3)
    vkGetDescriptorSetLayoutSupportKHR = (PFN_vkGetDescriptorSetLayoutSupportKHR)LoadFunc(Device, "vkGetDescriptorSetLayoutSupportKHR");
#endif /*  defined(VK_KHR_maintenance3)  */
#if defined(VK_KHR_maintenance4)
    vkGetDeviceBufferMemoryRequirementsKHR = (PFN_vkGetDeviceBufferMemoryRequirementsKHR)LoadFunc(Device, "vkGetDeviceBufferMemoryRequirementsKHR");
    vkGetDeviceImageMemoryRequirementsKHR = (PFN_vkGetDeviceImageMemoryRequirementsKHR)LoadFunc(Device, "vkGetDeviceImageMemoryRequirementsKHR");
    vkGetDeviceImageSparseMemoryRequirementsKHR = (PFN_vkGetDeviceImageSparseMemoryRequirementsKHR)LoadFunc(Device, "vkGetDeviceImageSparseMemoryRequirementsKHR");
#endif /*  defined(VK_KHR_maintenance4)  */
#if defined(VK_KHR_maintenance5)
    vkCmdBindIndexBuffer2KHR = (PFN_vkCmdBindIndexBuffer2KHR)LoadFunc(Device, "vkCmdBindIndexBuffer2KHR");
    vkGetDeviceImageSubresourceLayoutKHR = (PFN_vkGetDeviceImageSubresourceLayoutKHR)LoadFunc(Device, "vkGetDeviceImageSubresourceLayoutKHR");
    vkGetImageSubresourceLayout2KHR = (PFN_vkGetImageSubresourceLayout2KHR)LoadFunc(Device, "vkGetImageSubresourceLayout2KHR");
    vkGetRenderingAreaGranularityKHR = (PFN_vkGetRenderingAreaGranularityKHR)LoadFunc(Device, "vkGetRenderingAreaGranularityKHR");
#endif /*  defined(VK_KHR_maintenance5)  */
#if defined(VK_KHR_maintenance6)
    vkCmdBindDescriptorSets2KHR = (PFN_vkCmdBindDescriptorSets2KHR)LoadFunc(Device, "vkCmdBindDescriptorSets2KHR");
    vkCmdPushConstants2KHR = (PFN_vkCmdPushConstants2KHR)LoadFunc(Device, "vkCmdPushConstants2KHR");
#endif /*  defined(VK_KHR_maintenance6)  */
#if defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)
    vkCmdPushDescriptorSet2KHR = (PFN_vkCmdPushDescriptorSet2KHR)LoadFunc(Device, "vkCmdPushDescriptorSet2KHR");
    vkCmdPushDescriptorSetWithTemplate2KHR = (PFN_vkCmdPushDescriptorSetWithTemplate2KHR)LoadFunc(Device, "vkCmdPushDescriptorSetWithTemplate2KHR");
#endif /*  defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)  */
#if defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)
    vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = (PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT)LoadFunc(Device, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT");
    vkCmdSetDescriptorBufferOffsets2EXT = (PFN_vkCmdSetDescriptorBufferOffsets2EXT)LoadFunc(Device, "vkCmdSetDescriptorBufferOffsets2EXT");
#endif /*  defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)  */
#if defined(VK_KHR_map_memory2)
    vkMapMemory2KHR = (PFN_vkMapMemory2KHR)LoadFunc(Device, "vkMapMemory2KHR");
    vkUnmapMemory2KHR = (PFN_vkUnmapMemory2KHR)LoadFunc(Device, "vkUnmapMemory2KHR");
#endif /*  defined(VK_KHR_map_memory2)  */
#if defined(VK_KHR_performance_query)
    vkAcquireProfilingLockKHR = (PFN_vkAcquireProfilingLockKHR)LoadFunc(Device, "vkAcquireProfilingLockKHR");
    vkReleaseProfilingLockKHR = (PFN_vkReleaseProfilingLockKHR)LoadFunc(Device, "vkReleaseProfilingLockKHR");
#endif /*  defined(VK_KHR_performance_query)  */
#if defined(VK_KHR_pipeline_executable_properties)
    vkGetPipelineExecutableInternalRepresentationsKHR = (PFN_vkGetPipelineExecutableInternalRepresentationsKHR)LoadFunc(Device, "vkGetPipelineExecutableInternalRepresentationsKHR");
    vkGetPipelineExecutablePropertiesKHR = (PFN_vkGetPipelineExecutablePropertiesKHR)LoadFunc(Device, "vkGetPipelineExecutablePropertiesKHR");
    vkGetPipelineExecutableStatisticsKHR = (PFN_vkGetPipelineExecutableStatisticsKHR)LoadFunc(Device, "vkGetPipelineExecutableStatisticsKHR");
#endif /*  defined(VK_KHR_pipeline_executable_properties)  */
#if defined(VK_KHR_present_wait)
    vkWaitForPresentKHR = (PFN_vkWaitForPresentKHR)LoadFunc(Device, "vkWaitForPresentKHR");
#endif /*  defined(VK_KHR_present_wait)  */
#if defined(VK_KHR_push_descriptor)
    vkCmdPushDescriptorSetKHR = (PFN_vkCmdPushDescriptorSetKHR)LoadFunc(Device, "vkCmdPushDescriptorSetKHR");
#endif /*  defined(VK_KHR_push_descriptor)  */
#if defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)
    vkCmdTraceRaysIndirect2KHR = (PFN_vkCmdTraceRaysIndirect2KHR)LoadFunc(Device, "vkCmdTraceRaysIndirect2KHR");
#endif /*  defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)  */
#if defined(VK_KHR_ray_tracing_pipeline)
    vkCmdSetRayTracingPipelineStackSizeKHR = (PFN_vkCmdSetRayTracingPipelineStackSizeKHR)LoadFunc(Device, "vkCmdSetRayTracingPipelineStackSizeKHR");
    vkCmdTraceRaysIndirectKHR = (PFN_vkCmdTraceRaysIndirectKHR)LoadFunc(Device, "vkCmdTraceRaysIndirectKHR");
    vkCmdTraceRaysKHR = (PFN_vkCmdTraceRaysKHR)LoadFunc(Device, "vkCmdTraceRaysKHR");
    vkCreateRayTracingPipelinesKHR = (PFN_vkCreateRayTracingPipelinesKHR)LoadFunc(Device, "vkCreateRayTracingPipelinesKHR");
    vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = (PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR)LoadFunc(Device, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR");
    vkGetRayTracingShaderGroupHandlesKHR = (PFN_vkGetRayTracingShaderGroupHandlesKHR)LoadFunc(Device, "vkGetRayTracingShaderGroupHandlesKHR");
    vkGetRayTracingShaderGroupStackSizeKHR = (PFN_vkGetRayTracingShaderGroupStackSizeKHR)LoadFunc(Device, "vkGetRayTracingShaderGroupStackSizeKHR");
#endif /*  defined(VK_KHR_ray_tracing_pipeline)  */
#if defined(VK_KHR_sampler_ycbcr_conversion)
    vkCreateSamplerYcbcrConversionKHR = (PFN_vkCreateSamplerYcbcrConversionKHR)LoadFunc(Device, "vkCreateSamplerYcbcrConversionKHR");
    vkDestroySamplerYcbcrConversionKHR = (PFN_vkDestroySamplerYcbcrConversionKHR)LoadFunc(Device, "vkDestroySamplerYcbcrConversionKHR");
#endif /*  defined(VK_KHR_sampler_ycbcr_conversion)  */
#if defined(VK_KHR_shared_presentable_image)
    vkGetSwapchainStatusKHR = (PFN_vkGetSwapchainStatusKHR)LoadFunc(Device, "vkGetSwapchainStatusKHR");
#endif /*  defined(VK_KHR_shared_presentable_image)  */
#if defined(VK_KHR_swapchain)
    vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)LoadFunc(Device, "vkAcquireNextImageKHR");
    vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)LoadFunc(Device, "vkCreateSwapchainKHR");
    vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR)LoadFunc(Device, "vkDestroySwapchainKHR");
    vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)LoadFunc(Device, "vkGetSwapchainImagesKHR");
    vkQueuePresentKHR = (PFN_vkQueuePresentKHR)LoadFunc(Device, "vkQueuePresentKHR");
#endif /*  defined(VK_KHR_swapchain)  */
#if defined(VK_KHR_synchronization2)
    vkCmdPipelineBarrier2KHR = (PFN_vkCmdPipelineBarrier2KHR)LoadFunc(Device, "vkCmdPipelineBarrier2KHR");
    vkCmdResetEvent2KHR = (PFN_vkCmdResetEvent2KHR)LoadFunc(Device, "vkCmdResetEvent2KHR");
    vkCmdSetEvent2KHR = (PFN_vkCmdSetEvent2KHR)LoadFunc(Device, "vkCmdSetEvent2KHR");
    vkCmdWaitEvents2KHR = (PFN_vkCmdWaitEvents2KHR)LoadFunc(Device, "vkCmdWaitEvents2KHR");
    vkCmdWriteTimestamp2KHR = (PFN_vkCmdWriteTimestamp2KHR)LoadFunc(Device, "vkCmdWriteTimestamp2KHR");
    vkQueueSubmit2KHR = (PFN_vkQueueSubmit2KHR)LoadFunc(Device, "vkQueueSubmit2KHR");
#endif /*  defined(VK_KHR_synchronization2)  */
#if defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)
    vkCmdWriteBufferMarker2AMD = (PFN_vkCmdWriteBufferMarker2AMD)LoadFunc(Device, "vkCmdWriteBufferMarker2AMD");
#endif /*  defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)  */
#if defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)
    vkGetQueueCheckpointData2NV = (PFN_vkGetQueueCheckpointData2NV)LoadFunc(Device, "vkGetQueueCheckpointData2NV");
#endif /*  defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)  */
#if defined(VK_KHR_timeline_semaphore)
    vkGetSemaphoreCounterValueKHR = (PFN_vkGetSemaphoreCounterValueKHR)LoadFunc(Device, "vkGetSemaphoreCounterValueKHR");
    vkSignalSemaphoreKHR = (PFN_vkSignalSemaphoreKHR)LoadFunc(Device, "vkSignalSemaphoreKHR");
    vkWaitSemaphoresKHR = (PFN_vkWaitSemaphoresKHR)LoadFunc(Device, "vkWaitSemaphoresKHR");
#endif /*  defined(VK_KHR_timeline_semaphore)  */
#if defined(VK_KHR_video_decode_queue)
    vkCmdDecodeVideoKHR = (PFN_vkCmdDecodeVideoKHR)LoadFunc(Device, "vkCmdDecodeVideoKHR");
#endif /*  defined(VK_KHR_video_decode_queue)  */
#if defined(VK_KHR_video_encode_queue)
    vkCmdEncodeVideoKHR = (PFN_vkCmdEncodeVideoKHR)LoadFunc(Device, "vkCmdEncodeVideoKHR");
    vkGetEncodedVideoSessionParametersKHR = (PFN_vkGetEncodedVideoSessionParametersKHR)LoadFunc(Device, "vkGetEncodedVideoSessionParametersKHR");
#endif /*  defined(VK_KHR_video_encode_queue)  */
#if defined(VK_KHR_video_queue)
    vkBindVideoSessionMemoryKHR = (PFN_vkBindVideoSessionMemoryKHR)LoadFunc(Device, "vkBindVideoSessionMemoryKHR");
    vkCmdBeginVideoCodingKHR = (PFN_vkCmdBeginVideoCodingKHR)LoadFunc(Device, "vkCmdBeginVideoCodingKHR");
    vkCmdControlVideoCodingKHR = (PFN_vkCmdControlVideoCodingKHR)LoadFunc(Device, "vkCmdControlVideoCodingKHR");
    vkCmdEndVideoCodingKHR = (PFN_vkCmdEndVideoCodingKHR)LoadFunc(Device, "vkCmdEndVideoCodingKHR");
    vkCreateVideoSessionKHR = (PFN_vkCreateVideoSessionKHR)LoadFunc(Device, "vkCreateVideoSessionKHR");
    vkCreateVideoSessionParametersKHR = (PFN_vkCreateVideoSessionParametersKHR)LoadFunc(Device, "vkCreateVideoSessionParametersKHR");
    vkDestroyVideoSessionKHR = (PFN_vkDestroyVideoSessionKHR)LoadFunc(Device, "vkDestroyVideoSessionKHR");
    vkDestroyVideoSessionParametersKHR = (PFN_vkDestroyVideoSessionParametersKHR)LoadFunc(Device, "vkDestroyVideoSessionParametersKHR");
    vkGetVideoSessionMemoryRequirementsKHR = (PFN_vkGetVideoSessionMemoryRequirementsKHR)LoadFunc(Device, "vkGetVideoSessionMemoryRequirementsKHR");
    vkUpdateVideoSessionParametersKHR = (PFN_vkUpdateVideoSessionParametersKHR)LoadFunc(Device, "vkUpdateVideoSessionParametersKHR");
#endif /*  defined(VK_KHR_video_queue)  */
#if defined(VK_NVX_binary_import)
    vkCmdCuLaunchKernelNVX = (PFN_vkCmdCuLaunchKernelNVX)LoadFunc(Device, "vkCmdCuLaunchKernelNVX");
    vkCreateCuFunctionNVX = (PFN_vkCreateCuFunctionNVX)LoadFunc(Device, "vkCreateCuFunctionNVX");
    vkCreateCuModuleNVX = (PFN_vkCreateCuModuleNVX)LoadFunc(Device, "vkCreateCuModuleNVX");
    vkDestroyCuFunctionNVX = (PFN_vkDestroyCuFunctionNVX)LoadFunc(Device, "vkDestroyCuFunctionNVX");
    vkDestroyCuModuleNVX = (PFN_vkDestroyCuModuleNVX)LoadFunc(Device, "vkDestroyCuModuleNVX");
#endif /*  defined(VK_NVX_binary_import)  */
#if defined(VK_NVX_image_view_handle)
    vkGetImageViewAddressNVX = (PFN_vkGetImageViewAddressNVX)LoadFunc(Device, "vkGetImageViewAddressNVX");
    vkGetImageViewHandleNVX = (PFN_vkGetImageViewHandleNVX)LoadFunc(Device, "vkGetImageViewHandleNVX");
#endif /*  defined(VK_NVX_image_view_handle)  */
#if defined(VK_NV_clip_space_w_scaling)
    vkCmdSetViewportWScalingNV = (PFN_vkCmdSetViewportWScalingNV)LoadFunc(Device, "vkCmdSetViewportWScalingNV");
#endif /*  defined(VK_NV_clip_space_w_scaling)  */
#if defined(VK_NV_copy_memory_indirect)
    vkCmdCopyMemoryIndirectNV = (PFN_vkCmdCopyMemoryIndirectNV)LoadFunc(Device, "vkCmdCopyMemoryIndirectNV");
    vkCmdCopyMemoryToImageIndirectNV = (PFN_vkCmdCopyMemoryToImageIndirectNV)LoadFunc(Device, "vkCmdCopyMemoryToImageIndirectNV");
#endif /*  defined(VK_NV_copy_memory_indirect)  */
#if defined(VK_NV_cuda_kernel_launch)
    vkCmdCudaLaunchKernelNV = (PFN_vkCmdCudaLaunchKernelNV)LoadFunc(Device, "vkCmdCudaLaunchKernelNV");
    vkCreateCudaFunctionNV = (PFN_vkCreateCudaFunctionNV)LoadFunc(Device, "vkCreateCudaFunctionNV");
    vkCreateCudaModuleNV = (PFN_vkCreateCudaModuleNV)LoadFunc(Device, "vkCreateCudaModuleNV");
    vkDestroyCudaFunctionNV = (PFN_vkDestroyCudaFunctionNV)LoadFunc(Device, "vkDestroyCudaFunctionNV");
    vkDestroyCudaModuleNV = (PFN_vkDestroyCudaModuleNV)LoadFunc(Device, "vkDestroyCudaModuleNV");
    vkGetCudaModuleCacheNV = (PFN_vkGetCudaModuleCacheNV)LoadFunc(Device, "vkGetCudaModuleCacheNV");
#endif /*  defined(VK_NV_cuda_kernel_launch)  */
#if defined(VK_NV_device_diagnostic_checkpoints)
    vkCmdSetCheckpointNV = (PFN_vkCmdSetCheckpointNV)LoadFunc(Device, "vkCmdSetCheckpointNV");
    vkGetQueueCheckpointDataNV = (PFN_vkGetQueueCheckpointDataNV)LoadFunc(Device, "vkGetQueueCheckpointDataNV");
#endif /*  defined(VK_NV_device_diagnostic_checkpoints)  */
#if defined(VK_NV_device_generated_commands)
    vkCmdBindPipelineShaderGroupNV = (PFN_vkCmdBindPipelineShaderGroupNV)LoadFunc(Device, "vkCmdBindPipelineShaderGroupNV");
    vkCmdExecuteGeneratedCommandsNV = (PFN_vkCmdExecuteGeneratedCommandsNV)LoadFunc(Device, "vkCmdExecuteGeneratedCommandsNV");
    vkCmdPreprocessGeneratedCommandsNV = (PFN_vkCmdPreprocessGeneratedCommandsNV)LoadFunc(Device, "vkCmdPreprocessGeneratedCommandsNV");
    vkCreateIndirectCommandsLayoutNV = (PFN_vkCreateIndirectCommandsLayoutNV)LoadFunc(Device, "vkCreateIndirectCommandsLayoutNV");
    vkDestroyIndirectCommandsLayoutNV = (PFN_vkDestroyIndirectCommandsLayoutNV)LoadFunc(Device, "vkDestroyIndirectCommandsLayoutNV");
    vkGetGeneratedCommandsMemoryRequirementsNV = (PFN_vkGetGeneratedCommandsMemoryRequirementsNV)LoadFunc(Device, "vkGetGeneratedCommandsMemoryRequirementsNV");
#endif /*  defined(VK_NV_device_generated_commands)  */
#if defined(VK_NV_device_generated_commands_compute)
    vkCmdUpdatePipelineIndirectBufferNV = (PFN_vkCmdUpdatePipelineIndirectBufferNV)LoadFunc(Device, "vkCmdUpdatePipelineIndirectBufferNV");
    vkGetPipelineIndirectDeviceAddressNV = (PFN_vkGetPipelineIndirectDeviceAddressNV)LoadFunc(Device, "vkGetPipelineIndirectDeviceAddressNV");
    vkGetPipelineIndirectMemoryRequirementsNV = (PFN_vkGetPipelineIndirectMemoryRequirementsNV)LoadFunc(Device, "vkGetPipelineIndirectMemoryRequirementsNV");
#endif /*  defined(VK_NV_device_generated_commands_compute)  */
#if defined(VK_NV_external_memory_rdma)
    vkGetMemoryRemoteAddressNV = (PFN_vkGetMemoryRemoteAddressNV)LoadFunc(Device, "vkGetMemoryRemoteAddressNV");
#endif /*  defined(VK_NV_external_memory_rdma)  */
#if defined(VK_NV_external_memory_win32)
    vkGetMemoryWin32HandleNV = (PFN_vkGetMemoryWin32HandleNV)LoadFunc(Device, "vkGetMemoryWin32HandleNV");
#endif /*  defined(VK_NV_external_memory_win32)  */
#if defined(VK_NV_fragment_shading_rate_enums)
    vkCmdSetFragmentShadingRateEnumNV = (PFN_vkCmdSetFragmentShadingRateEnumNV)LoadFunc(Device, "vkCmdSetFragmentShadingRateEnumNV");
#endif /*  defined(VK_NV_fragment_shading_rate_enums)  */
#if defined(VK_NV_low_latency2)
    vkGetLatencyTimingsNV = (PFN_vkGetLatencyTimingsNV)LoadFunc(Device, "vkGetLatencyTimingsNV");
    vkLatencySleepNV = (PFN_vkLatencySleepNV)LoadFunc(Device, "vkLatencySleepNV");
    vkQueueNotifyOutOfBandNV = (PFN_vkQueueNotifyOutOfBandNV)LoadFunc(Device, "vkQueueNotifyOutOfBandNV");
    vkSetLatencyMarkerNV = (PFN_vkSetLatencyMarkerNV)LoadFunc(Device, "vkSetLatencyMarkerNV");
    vkSetLatencySleepModeNV = (PFN_vkSetLatencySleepModeNV)LoadFunc(Device, "vkSetLatencySleepModeNV");
#endif /*  defined(VK_NV_low_latency2)  */
#if defined(VK_NV_memory_decompression)
    vkCmdDecompressMemoryIndirectCountNV = (PFN_vkCmdDecompressMemoryIndirectCountNV)LoadFunc(Device, "vkCmdDecompressMemoryIndirectCountNV");
    vkCmdDecompressMemoryNV = (PFN_vkCmdDecompressMemoryNV)LoadFunc(Device, "vkCmdDecompressMemoryNV");
#endif /*  defined(VK_NV_memory_decompression)  */
#if defined(VK_NV_mesh_shader)
    vkCmdDrawMeshTasksIndirectCountNV = (PFN_vkCmdDrawMeshTasksIndirectCountNV)LoadFunc(Device, "vkCmdDrawMeshTasksIndirectCountNV");
    vkCmdDrawMeshTasksIndirectNV = (PFN_vkCmdDrawMeshTasksIndirectNV)LoadFunc(Device, "vkCmdDrawMeshTasksIndirectNV");
    vkCmdDrawMeshTasksNV = (PFN_vkCmdDrawMeshTasksNV)LoadFunc(Device, "vkCmdDrawMeshTasksNV");
#endif /*  defined(VK_NV_mesh_shader)  */
#if defined(VK_NV_optical_flow)
    vkBindOpticalFlowSessionImageNV = (PFN_vkBindOpticalFlowSessionImageNV)LoadFunc(Device, "vkBindOpticalFlowSessionImageNV");
    vkCmdOpticalFlowExecuteNV = (PFN_vkCmdOpticalFlowExecuteNV)LoadFunc(Device, "vkCmdOpticalFlowExecuteNV");
    vkCreateOpticalFlowSessionNV = (PFN_vkCreateOpticalFlowSessionNV)LoadFunc(Device, "vkCreateOpticalFlowSessionNV");
    vkDestroyOpticalFlowSessionNV = (PFN_vkDestroyOpticalFlowSessionNV)LoadFunc(Device, "vkDestroyOpticalFlowSessionNV");
#endif /*  defined(VK_NV_optical_flow)  */
#if defined(VK_NV_ray_tracing)
    vkBindAccelerationStructureMemoryNV = (PFN_vkBindAccelerationStructureMemoryNV)LoadFunc(Device, "vkBindAccelerationStructureMemoryNV");
    vkCmdBuildAccelerationStructureNV = (PFN_vkCmdBuildAccelerationStructureNV)LoadFunc(Device, "vkCmdBuildAccelerationStructureNV");
    vkCmdCopyAccelerationStructureNV = (PFN_vkCmdCopyAccelerationStructureNV)LoadFunc(Device, "vkCmdCopyAccelerationStructureNV");
    vkCmdTraceRaysNV = (PFN_vkCmdTraceRaysNV)LoadFunc(Device, "vkCmdTraceRaysNV");
    vkCmdWriteAccelerationStructuresPropertiesNV = (PFN_vkCmdWriteAccelerationStructuresPropertiesNV)LoadFunc(Device, "vkCmdWriteAccelerationStructuresPropertiesNV");
    vkCompileDeferredNV = (PFN_vkCompileDeferredNV)LoadFunc(Device, "vkCompileDeferredNV");
    vkCreateAccelerationStructureNV = (PFN_vkCreateAccelerationStructureNV)LoadFunc(Device, "vkCreateAccelerationStructureNV");
    vkCreateRayTracingPipelinesNV = (PFN_vkCreateRayTracingPipelinesNV)LoadFunc(Device, "vkCreateRayTracingPipelinesNV");
    vkDestroyAccelerationStructureNV = (PFN_vkDestroyAccelerationStructureNV)LoadFunc(Device, "vkDestroyAccelerationStructureNV");
    vkGetAccelerationStructureHandleNV = (PFN_vkGetAccelerationStructureHandleNV)LoadFunc(Device, "vkGetAccelerationStructureHandleNV");
    vkGetAccelerationStructureMemoryRequirementsNV = (PFN_vkGetAccelerationStructureMemoryRequirementsNV)LoadFunc(Device, "vkGetAccelerationStructureMemoryRequirementsNV");
    vkGetRayTracingShaderGroupHandlesNV = (PFN_vkGetRayTracingShaderGroupHandlesNV)LoadFunc(Device, "vkGetRayTracingShaderGroupHandlesNV");
#endif /*  defined(VK_NV_ray_tracing)  */
#if defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2
    vkCmdSetExclusiveScissorEnableNV = (PFN_vkCmdSetExclusiveScissorEnableNV)LoadFunc(Device, "vkCmdSetExclusiveScissorEnableNV");
#endif /*  defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2  */
#if defined(VK_NV_scissor_exclusive)
    vkCmdSetExclusiveScissorNV = (PFN_vkCmdSetExclusiveScissorNV)LoadFunc(Device, "vkCmdSetExclusiveScissorNV");
#endif /*  defined(VK_NV_scissor_exclusive)  */
#if defined(VK_NV_shading_rate_image)
    vkCmdBindShadingRateImageNV = (PFN_vkCmdBindShadingRateImageNV)LoadFunc(Device, "vkCmdBindShadingRateImageNV");
    vkCmdSetCoarseSampleOrderNV = (PFN_vkCmdSetCoarseSampleOrderNV)LoadFunc(Device, "vkCmdSetCoarseSampleOrderNV");
    vkCmdSetViewportShadingRatePaletteNV = (PFN_vkCmdSetViewportShadingRatePaletteNV)LoadFunc(Device, "vkCmdSetViewportShadingRatePaletteNV");
#endif /*  defined(VK_NV_shading_rate_image)  */
#if defined(VK_QCOM_tile_properties)
    vkGetDynamicRenderingTilePropertiesQCOM = (PFN_vkGetDynamicRenderingTilePropertiesQCOM)LoadFunc(Device, "vkGetDynamicRenderingTilePropertiesQCOM");
    vkGetFramebufferTilePropertiesQCOM = (PFN_vkGetFramebufferTilePropertiesQCOM)LoadFunc(Device, "vkGetFramebufferTilePropertiesQCOM");
#endif /*  defined(VK_QCOM_tile_properties)  */
#if defined(VK_QNX_external_memory_screen_buffer)
    vkGetScreenBufferPropertiesQNX = (PFN_vkGetScreenBufferPropertiesQNX)LoadFunc(Device, "vkGetScreenBufferPropertiesQNX");
#endif /*  defined(VK_QNX_external_memory_screen_buffer)  */
#if defined(VK_VALVE_descriptor_set_host_mapping)
    vkGetDescriptorSetHostMappingVALVE = (PFN_vkGetDescriptorSetHostMappingVALVE)LoadFunc(Device, "vkGetDescriptorSetHostMappingVALVE");
    vkGetDescriptorSetLayoutHostMappingInfoVALVE = (PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE)LoadFunc(Device, "vkGetDescriptorSetLayoutHostMappingInfoVALVE");
#endif /*  defined(VK_VALVE_descriptor_set_host_mapping)  */
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    vkCmdBindVertexBuffers2EXT = (PFN_vkCmdBindVertexBuffers2EXT)LoadFunc(Device, "vkCmdBindVertexBuffers2EXT");
    vkCmdSetCullModeEXT = (PFN_vkCmdSetCullModeEXT)LoadFunc(Device, "vkCmdSetCullModeEXT");
    vkCmdSetDepthBoundsTestEnableEXT = (PFN_vkCmdSetDepthBoundsTestEnableEXT)LoadFunc(Device, "vkCmdSetDepthBoundsTestEnableEXT");
    vkCmdSetDepthCompareOpEXT = (PFN_vkCmdSetDepthCompareOpEXT)LoadFunc(Device, "vkCmdSetDepthCompareOpEXT");
    vkCmdSetDepthTestEnableEXT = (PFN_vkCmdSetDepthTestEnableEXT)LoadFunc(Device, "vkCmdSetDepthTestEnableEXT");
    vkCmdSetDepthWriteEnableEXT = (PFN_vkCmdSetDepthWriteEnableEXT)LoadFunc(Device, "vkCmdSetDepthWriteEnableEXT");
    vkCmdSetFrontFaceEXT = (PFN_vkCmdSetFrontFaceEXT)LoadFunc(Device, "vkCmdSetFrontFaceEXT");
    vkCmdSetPrimitiveTopologyEXT = (PFN_vkCmdSetPrimitiveTopologyEXT)LoadFunc(Device, "vkCmdSetPrimitiveTopologyEXT");
    vkCmdSetScissorWithCountEXT = (PFN_vkCmdSetScissorWithCountEXT)LoadFunc(Device, "vkCmdSetScissorWithCountEXT");
    vkCmdSetStencilOpEXT = (PFN_vkCmdSetStencilOpEXT)LoadFunc(Device, "vkCmdSetStencilOpEXT");
    vkCmdSetStencilTestEnableEXT = (PFN_vkCmdSetStencilTestEnableEXT)LoadFunc(Device, "vkCmdSetStencilTestEnableEXT");
    vkCmdSetViewportWithCountEXT = (PFN_vkCmdSetViewportWithCountEXT)LoadFunc(Device, "vkCmdSetViewportWithCountEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
    vkCmdSetDepthBiasEnableEXT = (PFN_vkCmdSetDepthBiasEnableEXT)LoadFunc(Device, "vkCmdSetDepthBiasEnableEXT");
    vkCmdSetLogicOpEXT = (PFN_vkCmdSetLogicOpEXT)LoadFunc(Device, "vkCmdSetLogicOpEXT");
    vkCmdSetPatchControlPointsEXT = (PFN_vkCmdSetPatchControlPointsEXT)LoadFunc(Device, "vkCmdSetPatchControlPointsEXT");
    vkCmdSetPrimitiveRestartEnableEXT = (PFN_vkCmdSetPrimitiveRestartEnableEXT)LoadFunc(Device, "vkCmdSetPrimitiveRestartEnableEXT");
    vkCmdSetRasterizerDiscardEnableEXT = (PFN_vkCmdSetRasterizerDiscardEnableEXT)LoadFunc(Device, "vkCmdSetRasterizerDiscardEnableEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    vkCmdSetAlphaToCoverageEnableEXT = (PFN_vkCmdSetAlphaToCoverageEnableEXT)LoadFunc(Device, "vkCmdSetAlphaToCoverageEnableEXT");
    vkCmdSetAlphaToOneEnableEXT = (PFN_vkCmdSetAlphaToOneEnableEXT)LoadFunc(Device, "vkCmdSetAlphaToOneEnableEXT");
    vkCmdSetColorBlendEnableEXT = (PFN_vkCmdSetColorBlendEnableEXT)LoadFunc(Device, "vkCmdSetColorBlendEnableEXT");
    vkCmdSetColorBlendEquationEXT = (PFN_vkCmdSetColorBlendEquationEXT)LoadFunc(Device, "vkCmdSetColorBlendEquationEXT");
    vkCmdSetColorWriteMaskEXT = (PFN_vkCmdSetColorWriteMaskEXT)LoadFunc(Device, "vkCmdSetColorWriteMaskEXT");
    vkCmdSetDepthClampEnableEXT = (PFN_vkCmdSetDepthClampEnableEXT)LoadFunc(Device, "vkCmdSetDepthClampEnableEXT");
    vkCmdSetLogicOpEnableEXT = (PFN_vkCmdSetLogicOpEnableEXT)LoadFunc(Device, "vkCmdSetLogicOpEnableEXT");
    vkCmdSetPolygonModeEXT = (PFN_vkCmdSetPolygonModeEXT)LoadFunc(Device, "vkCmdSetPolygonModeEXT");
    vkCmdSetRasterizationSamplesEXT = (PFN_vkCmdSetRasterizationSamplesEXT)LoadFunc(Device, "vkCmdSetRasterizationSamplesEXT");
    vkCmdSetSampleMaskEXT = (PFN_vkCmdSetSampleMaskEXT)LoadFunc(Device, "vkCmdSetSampleMaskEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1))) || (defined(VK_EXT_shader_object))
    vkCmdSetTessellationDomainOriginEXT = (PFN_vkCmdSetTessellationDomainOriginEXT)LoadFunc(Device, "vkCmdSetTessellationDomainOriginEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1))) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))
    vkCmdSetRasterizationStreamEXT = (PFN_vkCmdSetRasterizationStreamEXT)LoadFunc(Device, "vkCmdSetRasterizationStreamEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))
    vkCmdSetConservativeRasterizationModeEXT = (PFN_vkCmdSetConservativeRasterizationModeEXT)LoadFunc(Device, "vkCmdSetConservativeRasterizationModeEXT");
    vkCmdSetExtraPrimitiveOverestimationSizeEXT = (PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT)LoadFunc(Device, "vkCmdSetExtraPrimitiveOverestimationSizeEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))
    vkCmdSetDepthClipEnableEXT = (PFN_vkCmdSetDepthClipEnableEXT)LoadFunc(Device, "vkCmdSetDepthClipEnableEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))
    vkCmdSetSampleLocationsEnableEXT = (PFN_vkCmdSetSampleLocationsEnableEXT)LoadFunc(Device, "vkCmdSetSampleLocationsEnableEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))
    vkCmdSetColorBlendAdvancedEXT = (PFN_vkCmdSetColorBlendAdvancedEXT)LoadFunc(Device, "vkCmdSetColorBlendAdvancedEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))
    vkCmdSetProvokingVertexModeEXT = (PFN_vkCmdSetProvokingVertexModeEXT)LoadFunc(Device, "vkCmdSetProvokingVertexModeEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))
    vkCmdSetLineRasterizationModeEXT = (PFN_vkCmdSetLineRasterizationModeEXT)LoadFunc(Device, "vkCmdSetLineRasterizationModeEXT");
    vkCmdSetLineStippleEnableEXT = (PFN_vkCmdSetLineStippleEnableEXT)LoadFunc(Device, "vkCmdSetLineStippleEnableEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))
    vkCmdSetDepthClipNegativeOneToOneEXT = (PFN_vkCmdSetDepthClipNegativeOneToOneEXT)LoadFunc(Device, "vkCmdSetDepthClipNegativeOneToOneEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling)) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))
    vkCmdSetViewportWScalingEnableNV = (PFN_vkCmdSetViewportWScalingEnableNV)LoadFunc(Device, "vkCmdSetViewportWScalingEnableNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling)) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle)) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))
    vkCmdSetViewportSwizzleNV = (PFN_vkCmdSetViewportSwizzleNV)LoadFunc(Device, "vkCmdSetViewportSwizzleNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle)) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color)) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))
    vkCmdSetCoverageToColorEnableNV = (PFN_vkCmdSetCoverageToColorEnableNV)LoadFunc(Device, "vkCmdSetCoverageToColorEnableNV");
    vkCmdSetCoverageToColorLocationNV = (PFN_vkCmdSetCoverageToColorLocationNV)LoadFunc(Device, "vkCmdSetCoverageToColorLocationNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color)) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples)) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))
    vkCmdSetCoverageModulationModeNV = (PFN_vkCmdSetCoverageModulationModeNV)LoadFunc(Device, "vkCmdSetCoverageModulationModeNV");
    vkCmdSetCoverageModulationTableEnableNV = (PFN_vkCmdSetCoverageModulationTableEnableNV)LoadFunc(Device, "vkCmdSetCoverageModulationTableEnableNV");
    vkCmdSetCoverageModulationTableNV = (PFN_vkCmdSetCoverageModulationTableNV)LoadFunc(Device, "vkCmdSetCoverageModulationTableNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples)) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image)) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))
    vkCmdSetShadingRateImageEnableNV = (PFN_vkCmdSetShadingRateImageEnableNV)LoadFunc(Device, "vkCmdSetShadingRateImageEnableNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image)) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test)) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))
    vkCmdSetRepresentativeFragmentTestEnableNV = (PFN_vkCmdSetRepresentativeFragmentTestEnableNV)LoadFunc(Device, "vkCmdSetRepresentativeFragmentTestEnableNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test)) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode)) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))
    vkCmdSetCoverageReductionModeNV = (PFN_vkCmdSetCoverageReductionModeNV)LoadFunc(Device, "vkCmdSetCoverageReductionModeNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode)) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))  */
#if (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
    vkGetDeviceGroupSurfacePresentModes2EXT = (PFN_vkGetDeviceGroupSurfacePresentModes2EXT)LoadFunc(Device, "vkGetDeviceGroupSurfacePresentModes2EXT");
#endif /*  (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))  */
#if (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))
    vkGetImageSubresourceLayout2EXT = (PFN_vkGetImageSubresourceLayout2EXT)LoadFunc(Device, "vkGetImageSubresourceLayout2EXT");
#endif /*  (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))  */
#if (defined(VK_EXT_shader_object)) || (defined(VK_EXT_vertex_input_dynamic_state))
    vkCmdSetVertexInputEXT = (PFN_vkCmdSetVertexInputEXT)LoadFunc(Device, "vkCmdSetVertexInputEXT");
#endif /*  (defined(VK_EXT_shader_object)) || (defined(VK_EXT_vertex_input_dynamic_state))  */
#if (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
    vkCmdPushDescriptorSetWithTemplateKHR = (PFN_vkCmdPushDescriptorSetWithTemplateKHR)LoadFunc(Device, "vkCmdPushDescriptorSetWithTemplateKHR");
#endif /*  (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))  */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
    vkGetDeviceGroupPresentCapabilitiesKHR = (PFN_vkGetDeviceGroupPresentCapabilitiesKHR)LoadFunc(Device, "vkGetDeviceGroupPresentCapabilitiesKHR");
    vkGetDeviceGroupSurfacePresentModesKHR = (PFN_vkGetDeviceGroupSurfacePresentModesKHR)LoadFunc(Device, "vkGetDeviceGroupSurfacePresentModesKHR");
#endif /*  (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))  */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
    vkAcquireNextImage2KHR = (PFN_vkAcquireNextImage2KHR)LoadFunc(Device, "vkAcquireNextImage2KHR");
#endif /*  (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))  */

}

void _mythVkLoadArrayDevice(mythVkDeviceFuncArray* FuncArray, VkDevice Device, PFN_vkGetDeviceProcAddr LoadFunc){

//SECTION(V): VK_LOADER_DEVICE_ARRAY_IMPL
#if defined(VK_VERSION_1_0)
    FuncArray->vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)LoadFunc(Device, "vkAllocateCommandBuffers");
    FuncArray->vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)LoadFunc(Device, "vkAllocateDescriptorSets");
    FuncArray->vkAllocateMemory = (PFN_vkAllocateMemory)LoadFunc(Device, "vkAllocateMemory");
    FuncArray->vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)LoadFunc(Device, "vkBeginCommandBuffer");
    FuncArray->vkBindBufferMemory = (PFN_vkBindBufferMemory)LoadFunc(Device, "vkBindBufferMemory");
    FuncArray->vkBindImageMemory = (PFN_vkBindImageMemory)LoadFunc(Device, "vkBindImageMemory");
    FuncArray->vkCmdBeginQuery = (PFN_vkCmdBeginQuery)LoadFunc(Device, "vkCmdBeginQuery");
    FuncArray->vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)LoadFunc(Device, "vkCmdBeginRenderPass");
    FuncArray->vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)LoadFunc(Device, "vkCmdBindDescriptorSets");
    FuncArray->vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)LoadFunc(Device, "vkCmdBindIndexBuffer");
    FuncArray->vkCmdBindPipeline = (PFN_vkCmdBindPipeline)LoadFunc(Device, "vkCmdBindPipeline");
    FuncArray->vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)LoadFunc(Device, "vkCmdBindVertexBuffers");
    FuncArray->vkCmdBlitImage = (PFN_vkCmdBlitImage)LoadFunc(Device, "vkCmdBlitImage");
    FuncArray->vkCmdClearAttachments = (PFN_vkCmdClearAttachments)LoadFunc(Device, "vkCmdClearAttachments");
    FuncArray->vkCmdClearColorImage = (PFN_vkCmdClearColorImage)LoadFunc(Device, "vkCmdClearColorImage");
    FuncArray->vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage)LoadFunc(Device, "vkCmdClearDepthStencilImage");
    FuncArray->vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer)LoadFunc(Device, "vkCmdCopyBuffer");
    FuncArray->vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)LoadFunc(Device, "vkCmdCopyBufferToImage");
    FuncArray->vkCmdCopyImage = (PFN_vkCmdCopyImage)LoadFunc(Device, "vkCmdCopyImage");
    FuncArray->vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer)LoadFunc(Device, "vkCmdCopyImageToBuffer");
    FuncArray->vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults)LoadFunc(Device, "vkCmdCopyQueryPoolResults");
    FuncArray->vkCmdDispatch = (PFN_vkCmdDispatch)LoadFunc(Device, "vkCmdDispatch");
    FuncArray->vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect)LoadFunc(Device, "vkCmdDispatchIndirect");
    FuncArray->vkCmdDraw = (PFN_vkCmdDraw)LoadFunc(Device, "vkCmdDraw");
    FuncArray->vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed)LoadFunc(Device, "vkCmdDrawIndexed");
    FuncArray->vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect)LoadFunc(Device, "vkCmdDrawIndexedIndirect");
    FuncArray->vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect)LoadFunc(Device, "vkCmdDrawIndirect");
    FuncArray->vkCmdEndQuery = (PFN_vkCmdEndQuery)LoadFunc(Device, "vkCmdEndQuery");
    FuncArray->vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)LoadFunc(Device, "vkCmdEndRenderPass");
    FuncArray->vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands)LoadFunc(Device, "vkCmdExecuteCommands");
    FuncArray->vkCmdFillBuffer = (PFN_vkCmdFillBuffer)LoadFunc(Device, "vkCmdFillBuffer");
    FuncArray->vkCmdNextSubpass = (PFN_vkCmdNextSubpass)LoadFunc(Device, "vkCmdNextSubpass");
    FuncArray->vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)LoadFunc(Device, "vkCmdPipelineBarrier");
    FuncArray->vkCmdPushConstants = (PFN_vkCmdPushConstants)LoadFunc(Device, "vkCmdPushConstants");
    FuncArray->vkCmdResetEvent = (PFN_vkCmdResetEvent)LoadFunc(Device, "vkCmdResetEvent");
    FuncArray->vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool)LoadFunc(Device, "vkCmdResetQueryPool");
    FuncArray->vkCmdResolveImage = (PFN_vkCmdResolveImage)LoadFunc(Device, "vkCmdResolveImage");
    FuncArray->vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants)LoadFunc(Device, "vkCmdSetBlendConstants");
    FuncArray->vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias)LoadFunc(Device, "vkCmdSetDepthBias");
    FuncArray->vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds)LoadFunc(Device, "vkCmdSetDepthBounds");
    FuncArray->vkCmdSetEvent = (PFN_vkCmdSetEvent)LoadFunc(Device, "vkCmdSetEvent");
    FuncArray->vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth)LoadFunc(Device, "vkCmdSetLineWidth");
    FuncArray->vkCmdSetScissor = (PFN_vkCmdSetScissor)LoadFunc(Device, "vkCmdSetScissor");
    FuncArray->vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask)LoadFunc(Device, "vkCmdSetStencilCompareMask");
    FuncArray->vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference)LoadFunc(Device, "vkCmdSetStencilReference");
    FuncArray->vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask)LoadFunc(Device, "vkCmdSetStencilWriteMask");
    FuncArray->vkCmdSetViewport = (PFN_vkCmdSetViewport)LoadFunc(Device, "vkCmdSetViewport");
    FuncArray->vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer)LoadFunc(Device, "vkCmdUpdateBuffer");
    FuncArray->vkCmdWaitEvents = (PFN_vkCmdWaitEvents)LoadFunc(Device, "vkCmdWaitEvents");
    FuncArray->vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp)LoadFunc(Device, "vkCmdWriteTimestamp");
    FuncArray->vkCreateBuffer = (PFN_vkCreateBuffer)LoadFunc(Device, "vkCreateBuffer");
    FuncArray->vkCreateBufferView = (PFN_vkCreateBufferView)LoadFunc(Device, "vkCreateBufferView");
    FuncArray->vkCreateCommandPool = (PFN_vkCreateCommandPool)LoadFunc(Device, "vkCreateCommandPool");
    FuncArray->vkCreateComputePipelines = (PFN_vkCreateComputePipelines)LoadFunc(Device, "vkCreateComputePipelines");
    FuncArray->vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool)LoadFunc(Device, "vkCreateDescriptorPool");
    FuncArray->vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)LoadFunc(Device, "vkCreateDescriptorSetLayout");
    FuncArray->vkCreateEvent = (PFN_vkCreateEvent)LoadFunc(Device, "vkCreateEvent");
    FuncArray->vkCreateFence = (PFN_vkCreateFence)LoadFunc(Device, "vkCreateFence");
    FuncArray->vkCreateFramebuffer = (PFN_vkCreateFramebuffer)LoadFunc(Device, "vkCreateFramebuffer");
    FuncArray->vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)LoadFunc(Device, "vkCreateGraphicsPipelines");
    FuncArray->vkCreateImage = (PFN_vkCreateImage)LoadFunc(Device, "vkCreateImage");
    FuncArray->vkCreateImageView = (PFN_vkCreateImageView)LoadFunc(Device, "vkCreateImageView");
    FuncArray->vkCreatePipelineCache = (PFN_vkCreatePipelineCache)LoadFunc(Device, "vkCreatePipelineCache");
    FuncArray->vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)LoadFunc(Device, "vkCreatePipelineLayout");
    FuncArray->vkCreateQueryPool = (PFN_vkCreateQueryPool)LoadFunc(Device, "vkCreateQueryPool");
    FuncArray->vkCreateRenderPass = (PFN_vkCreateRenderPass)LoadFunc(Device, "vkCreateRenderPass");
    FuncArray->vkCreateSampler = (PFN_vkCreateSampler)LoadFunc(Device, "vkCreateSampler");
    FuncArray->vkCreateSemaphore = (PFN_vkCreateSemaphore)LoadFunc(Device, "vkCreateSemaphore");
    FuncArray->vkCreateShaderModule = (PFN_vkCreateShaderModule)LoadFunc(Device, "vkCreateShaderModule");
    FuncArray->vkDestroyBuffer = (PFN_vkDestroyBuffer)LoadFunc(Device, "vkDestroyBuffer");
    FuncArray->vkDestroyBufferView = (PFN_vkDestroyBufferView)LoadFunc(Device, "vkDestroyBufferView");
    FuncArray->vkDestroyCommandPool = (PFN_vkDestroyCommandPool)LoadFunc(Device, "vkDestroyCommandPool");
    FuncArray->vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool)LoadFunc(Device, "vkDestroyDescriptorPool");
    FuncArray->vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)LoadFunc(Device, "vkDestroyDescriptorSetLayout");
    FuncArray->vkDestroyDevice = (PFN_vkDestroyDevice)LoadFunc(Device, "vkDestroyDevice");
    FuncArray->vkDestroyEvent = (PFN_vkDestroyEvent)LoadFunc(Device, "vkDestroyEvent");
    FuncArray->vkDestroyFence = (PFN_vkDestroyFence)LoadFunc(Device, "vkDestroyFence");
    FuncArray->vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer)LoadFunc(Device, "vkDestroyFramebuffer");
    FuncArray->vkDestroyImage = (PFN_vkDestroyImage)LoadFunc(Device, "vkDestroyImage");
    FuncArray->vkDestroyImageView = (PFN_vkDestroyImageView)LoadFunc(Device, "vkDestroyImageView");
    FuncArray->vkDestroyPipeline = (PFN_vkDestroyPipeline)LoadFunc(Device, "vkDestroyPipeline");
    FuncArray->vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache)LoadFunc(Device, "vkDestroyPipelineCache");
    FuncArray->vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)LoadFunc(Device, "vkDestroyPipelineLayout");
    FuncArray->vkDestroyQueryPool = (PFN_vkDestroyQueryPool)LoadFunc(Device, "vkDestroyQueryPool");
    FuncArray->vkDestroyRenderPass = (PFN_vkDestroyRenderPass)LoadFunc(Device, "vkDestroyRenderPass");
    FuncArray->vkDestroySampler = (PFN_vkDestroySampler)LoadFunc(Device, "vkDestroySampler");
    FuncArray->vkDestroySemaphore = (PFN_vkDestroySemaphore)LoadFunc(Device, "vkDestroySemaphore");
    FuncArray->vkDestroyShaderModule = (PFN_vkDestroyShaderModule)LoadFunc(Device, "vkDestroyShaderModule");
    FuncArray->vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle)LoadFunc(Device, "vkDeviceWaitIdle");
    FuncArray->vkEndCommandBuffer = (PFN_vkEndCommandBuffer)LoadFunc(Device, "vkEndCommandBuffer");
    FuncArray->vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges)LoadFunc(Device, "vkFlushMappedMemoryRanges");
    FuncArray->vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers)LoadFunc(Device, "vkFreeCommandBuffers");
    FuncArray->vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets)LoadFunc(Device, "vkFreeDescriptorSets");
    FuncArray->vkFreeMemory = (PFN_vkFreeMemory)LoadFunc(Device, "vkFreeMemory");
    FuncArray->vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)LoadFunc(Device, "vkGetBufferMemoryRequirements");
    FuncArray->vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment)LoadFunc(Device, "vkGetDeviceMemoryCommitment");
    FuncArray->vkGetDeviceQueue = (PFN_vkGetDeviceQueue)LoadFunc(Device, "vkGetDeviceQueue");
    FuncArray->vkGetEventStatus = (PFN_vkGetEventStatus)LoadFunc(Device, "vkGetEventStatus");
    FuncArray->vkGetFenceStatus = (PFN_vkGetFenceStatus)LoadFunc(Device, "vkGetFenceStatus");
    FuncArray->vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)LoadFunc(Device, "vkGetImageMemoryRequirements");
    FuncArray->vkGetImageSparseMemoryRequirements = (PFN_vkGetImageSparseMemoryRequirements)LoadFunc(Device, "vkGetImageSparseMemoryRequirements");
    FuncArray->vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout)LoadFunc(Device, "vkGetImageSubresourceLayout");
    FuncArray->vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData)LoadFunc(Device, "vkGetPipelineCacheData");
    FuncArray->vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults)LoadFunc(Device, "vkGetQueryPoolResults");
    FuncArray->vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity)LoadFunc(Device, "vkGetRenderAreaGranularity");
    FuncArray->vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges)LoadFunc(Device, "vkInvalidateMappedMemoryRanges");
    FuncArray->vkMapMemory = (PFN_vkMapMemory)LoadFunc(Device, "vkMapMemory");
    FuncArray->vkMergePipelineCaches = (PFN_vkMergePipelineCaches)LoadFunc(Device, "vkMergePipelineCaches");
    FuncArray->vkQueueBindSparse = (PFN_vkQueueBindSparse)LoadFunc(Device, "vkQueueBindSparse");
    FuncArray->vkQueueSubmit = (PFN_vkQueueSubmit)LoadFunc(Device, "vkQueueSubmit");
    FuncArray->vkQueueWaitIdle = (PFN_vkQueueWaitIdle)LoadFunc(Device, "vkQueueWaitIdle");
    FuncArray->vkResetCommandBuffer = (PFN_vkResetCommandBuffer)LoadFunc(Device, "vkResetCommandBuffer");
    FuncArray->vkResetCommandPool = (PFN_vkResetCommandPool)LoadFunc(Device, "vkResetCommandPool");
    FuncArray->vkResetDescriptorPool = (PFN_vkResetDescriptorPool)LoadFunc(Device, "vkResetDescriptorPool");
    FuncArray->vkResetEvent = (PFN_vkResetEvent)LoadFunc(Device, "vkResetEvent");
    FuncArray->vkResetFences = (PFN_vkResetFences)LoadFunc(Device, "vkResetFences");
    FuncArray->vkSetEvent = (PFN_vkSetEvent)LoadFunc(Device, "vkSetEvent");
    FuncArray->vkUnmapMemory = (PFN_vkUnmapMemory)LoadFunc(Device, "vkUnmapMemory");
    FuncArray->vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)LoadFunc(Device, "vkUpdateDescriptorSets");
    FuncArray->vkWaitForFences = (PFN_vkWaitForFences)LoadFunc(Device, "vkWaitForFences");
#endif /*  defined(VK_VERSION_1_0)  */
#if defined(VK_VERSION_1_1)
    FuncArray->vkBindBufferMemory2 = (PFN_vkBindBufferMemory2)LoadFunc(Device, "vkBindBufferMemory2");
    FuncArray->vkBindImageMemory2 = (PFN_vkBindImageMemory2)LoadFunc(Device, "vkBindImageMemory2");
    FuncArray->vkCmdDispatchBase = (PFN_vkCmdDispatchBase)LoadFunc(Device, "vkCmdDispatchBase");
    FuncArray->vkCmdSetDeviceMask = (PFN_vkCmdSetDeviceMask)LoadFunc(Device, "vkCmdSetDeviceMask");
    FuncArray->vkCreateDescriptorUpdateTemplate = (PFN_vkCreateDescriptorUpdateTemplate)LoadFunc(Device, "vkCreateDescriptorUpdateTemplate");
    FuncArray->vkCreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion)LoadFunc(Device, "vkCreateSamplerYcbcrConversion");
    FuncArray->vkDestroyDescriptorUpdateTemplate = (PFN_vkDestroyDescriptorUpdateTemplate)LoadFunc(Device, "vkDestroyDescriptorUpdateTemplate");
    FuncArray->vkDestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion)LoadFunc(Device, "vkDestroySamplerYcbcrConversion");
    FuncArray->vkGetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2)LoadFunc(Device, "vkGetBufferMemoryRequirements2");
    FuncArray->vkGetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport)LoadFunc(Device, "vkGetDescriptorSetLayoutSupport");
    FuncArray->vkGetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures)LoadFunc(Device, "vkGetDeviceGroupPeerMemoryFeatures");
    FuncArray->vkGetDeviceQueue2 = (PFN_vkGetDeviceQueue2)LoadFunc(Device, "vkGetDeviceQueue2");
    FuncArray->vkGetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2)LoadFunc(Device, "vkGetImageMemoryRequirements2");
    FuncArray->vkGetImageSparseMemoryRequirements2 = (PFN_vkGetImageSparseMemoryRequirements2)LoadFunc(Device, "vkGetImageSparseMemoryRequirements2");
    FuncArray->vkTrimCommandPool = (PFN_vkTrimCommandPool)LoadFunc(Device, "vkTrimCommandPool");
    FuncArray->vkUpdateDescriptorSetWithTemplate = (PFN_vkUpdateDescriptorSetWithTemplate)LoadFunc(Device, "vkUpdateDescriptorSetWithTemplate");
#endif /*  defined(VK_VERSION_1_1)  */
#if defined(VK_VERSION_1_2)
    FuncArray->vkCmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2)LoadFunc(Device, "vkCmdBeginRenderPass2");
    FuncArray->vkCmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount)LoadFunc(Device, "vkCmdDrawIndexedIndirectCount");
    FuncArray->vkCmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount)LoadFunc(Device, "vkCmdDrawIndirectCount");
    FuncArray->vkCmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2)LoadFunc(Device, "vkCmdEndRenderPass2");
    FuncArray->vkCmdNextSubpass2 = (PFN_vkCmdNextSubpass2)LoadFunc(Device, "vkCmdNextSubpass2");
    FuncArray->vkCreateRenderPass2 = (PFN_vkCreateRenderPass2)LoadFunc(Device, "vkCreateRenderPass2");
    FuncArray->vkGetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress)LoadFunc(Device, "vkGetBufferDeviceAddress");
    FuncArray->vkGetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress)LoadFunc(Device, "vkGetBufferOpaqueCaptureAddress");
    FuncArray->vkGetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress)LoadFunc(Device, "vkGetDeviceMemoryOpaqueCaptureAddress");
    FuncArray->vkGetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue)LoadFunc(Device, "vkGetSemaphoreCounterValue");
    FuncArray->vkResetQueryPool = (PFN_vkResetQueryPool)LoadFunc(Device, "vkResetQueryPool");
    FuncArray->vkSignalSemaphore = (PFN_vkSignalSemaphore)LoadFunc(Device, "vkSignalSemaphore");
    FuncArray->vkWaitSemaphores = (PFN_vkWaitSemaphores)LoadFunc(Device, "vkWaitSemaphores");
#endif /*  defined(VK_VERSION_1_2)  */
#if defined(VK_VERSION_1_3)
    FuncArray->vkCmdBeginRendering = (PFN_vkCmdBeginRendering)LoadFunc(Device, "vkCmdBeginRendering");
    FuncArray->vkCmdBindVertexBuffers2 = (PFN_vkCmdBindVertexBuffers2)LoadFunc(Device, "vkCmdBindVertexBuffers2");
    FuncArray->vkCmdBlitImage2 = (PFN_vkCmdBlitImage2)LoadFunc(Device, "vkCmdBlitImage2");
    FuncArray->vkCmdCopyBuffer2 = (PFN_vkCmdCopyBuffer2)LoadFunc(Device, "vkCmdCopyBuffer2");
    FuncArray->vkCmdCopyBufferToImage2 = (PFN_vkCmdCopyBufferToImage2)LoadFunc(Device, "vkCmdCopyBufferToImage2");
    FuncArray->vkCmdCopyImage2 = (PFN_vkCmdCopyImage2)LoadFunc(Device, "vkCmdCopyImage2");
    FuncArray->vkCmdCopyImageToBuffer2 = (PFN_vkCmdCopyImageToBuffer2)LoadFunc(Device, "vkCmdCopyImageToBuffer2");
    FuncArray->vkCmdEndRendering = (PFN_vkCmdEndRendering)LoadFunc(Device, "vkCmdEndRendering");
    FuncArray->vkCmdPipelineBarrier2 = (PFN_vkCmdPipelineBarrier2)LoadFunc(Device, "vkCmdPipelineBarrier2");
    FuncArray->vkCmdResetEvent2 = (PFN_vkCmdResetEvent2)LoadFunc(Device, "vkCmdResetEvent2");
    FuncArray->vkCmdResolveImage2 = (PFN_vkCmdResolveImage2)LoadFunc(Device, "vkCmdResolveImage2");
    FuncArray->vkCmdSetCullMode = (PFN_vkCmdSetCullMode)LoadFunc(Device, "vkCmdSetCullMode");
    FuncArray->vkCmdSetDepthBiasEnable = (PFN_vkCmdSetDepthBiasEnable)LoadFunc(Device, "vkCmdSetDepthBiasEnable");
    FuncArray->vkCmdSetDepthBoundsTestEnable = (PFN_vkCmdSetDepthBoundsTestEnable)LoadFunc(Device, "vkCmdSetDepthBoundsTestEnable");
    FuncArray->vkCmdSetDepthCompareOp = (PFN_vkCmdSetDepthCompareOp)LoadFunc(Device, "vkCmdSetDepthCompareOp");
    FuncArray->vkCmdSetDepthTestEnable = (PFN_vkCmdSetDepthTestEnable)LoadFunc(Device, "vkCmdSetDepthTestEnable");
    FuncArray->vkCmdSetDepthWriteEnable = (PFN_vkCmdSetDepthWriteEnable)LoadFunc(Device, "vkCmdSetDepthWriteEnable");
    FuncArray->vkCmdSetEvent2 = (PFN_vkCmdSetEvent2)LoadFunc(Device, "vkCmdSetEvent2");
    FuncArray->vkCmdSetFrontFace = (PFN_vkCmdSetFrontFace)LoadFunc(Device, "vkCmdSetFrontFace");
    FuncArray->vkCmdSetPrimitiveRestartEnable = (PFN_vkCmdSetPrimitiveRestartEnable)LoadFunc(Device, "vkCmdSetPrimitiveRestartEnable");
    FuncArray->vkCmdSetPrimitiveTopology = (PFN_vkCmdSetPrimitiveTopology)LoadFunc(Device, "vkCmdSetPrimitiveTopology");
    FuncArray->vkCmdSetRasterizerDiscardEnable = (PFN_vkCmdSetRasterizerDiscardEnable)LoadFunc(Device, "vkCmdSetRasterizerDiscardEnable");
    FuncArray->vkCmdSetScissorWithCount = (PFN_vkCmdSetScissorWithCount)LoadFunc(Device, "vkCmdSetScissorWithCount");
    FuncArray->vkCmdSetStencilOp = (PFN_vkCmdSetStencilOp)LoadFunc(Device, "vkCmdSetStencilOp");
    FuncArray->vkCmdSetStencilTestEnable = (PFN_vkCmdSetStencilTestEnable)LoadFunc(Device, "vkCmdSetStencilTestEnable");
    FuncArray->vkCmdSetViewportWithCount = (PFN_vkCmdSetViewportWithCount)LoadFunc(Device, "vkCmdSetViewportWithCount");
    FuncArray->vkCmdWaitEvents2 = (PFN_vkCmdWaitEvents2)LoadFunc(Device, "vkCmdWaitEvents2");
    FuncArray->vkCmdWriteTimestamp2 = (PFN_vkCmdWriteTimestamp2)LoadFunc(Device, "vkCmdWriteTimestamp2");
    FuncArray->vkCreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot)LoadFunc(Device, "vkCreatePrivateDataSlot");
    FuncArray->vkDestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot)LoadFunc(Device, "vkDestroyPrivateDataSlot");
    FuncArray->vkGetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements)LoadFunc(Device, "vkGetDeviceBufferMemoryRequirements");
    FuncArray->vkGetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements)LoadFunc(Device, "vkGetDeviceImageMemoryRequirements");
    FuncArray->vkGetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements)LoadFunc(Device, "vkGetDeviceImageSparseMemoryRequirements");
    FuncArray->vkGetPrivateData = (PFN_vkGetPrivateData)LoadFunc(Device, "vkGetPrivateData");
    FuncArray->vkQueueSubmit2 = (PFN_vkQueueSubmit2)LoadFunc(Device, "vkQueueSubmit2");
    FuncArray->vkSetPrivateData = (PFN_vkSetPrivateData)LoadFunc(Device, "vkSetPrivateData");
#endif /*  defined(VK_VERSION_1_3)  */
#if defined(VK_AMDX_shader_enqueue)
    FuncArray->vkCmdDispatchGraphAMDX = (PFN_vkCmdDispatchGraphAMDX)LoadFunc(Device, "vkCmdDispatchGraphAMDX");
    FuncArray->vkCmdDispatchGraphIndirectAMDX = (PFN_vkCmdDispatchGraphIndirectAMDX)LoadFunc(Device, "vkCmdDispatchGraphIndirectAMDX");
    FuncArray->vkCmdDispatchGraphIndirectCountAMDX = (PFN_vkCmdDispatchGraphIndirectCountAMDX)LoadFunc(Device, "vkCmdDispatchGraphIndirectCountAMDX");
    FuncArray->vkCmdInitializeGraphScratchMemoryAMDX = (PFN_vkCmdInitializeGraphScratchMemoryAMDX)LoadFunc(Device, "vkCmdInitializeGraphScratchMemoryAMDX");
    FuncArray->vkCreateExecutionGraphPipelinesAMDX = (PFN_vkCreateExecutionGraphPipelinesAMDX)LoadFunc(Device, "vkCreateExecutionGraphPipelinesAMDX");
    FuncArray->vkGetExecutionGraphPipelineNodeIndexAMDX = (PFN_vkGetExecutionGraphPipelineNodeIndexAMDX)LoadFunc(Device, "vkGetExecutionGraphPipelineNodeIndexAMDX");
    FuncArray->vkGetExecutionGraphPipelineScratchSizeAMDX = (PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)LoadFunc(Device, "vkGetExecutionGraphPipelineScratchSizeAMDX");
#endif /*  defined(VK_AMDX_shader_enqueue)  */
#if defined(VK_AMD_anti_lag)
    FuncArray->vkAntiLagUpdateAMD = (PFN_vkAntiLagUpdateAMD)LoadFunc(Device, "vkAntiLagUpdateAMD");
#endif /*  defined(VK_AMD_anti_lag)  */
#if defined(VK_AMD_buffer_marker)
    FuncArray->vkCmdWriteBufferMarkerAMD = (PFN_vkCmdWriteBufferMarkerAMD)LoadFunc(Device, "vkCmdWriteBufferMarkerAMD");
#endif /*  defined(VK_AMD_buffer_marker)  */
#if defined(VK_AMD_display_native_hdr)
    FuncArray->vkSetLocalDimmingAMD = (PFN_vkSetLocalDimmingAMD)LoadFunc(Device, "vkSetLocalDimmingAMD");
#endif /*  defined(VK_AMD_display_native_hdr)  */
#if defined(VK_AMD_draw_indirect_count)
    FuncArray->vkCmdDrawIndexedIndirectCountAMD = (PFN_vkCmdDrawIndexedIndirectCountAMD)LoadFunc(Device, "vkCmdDrawIndexedIndirectCountAMD");
    FuncArray->vkCmdDrawIndirectCountAMD = (PFN_vkCmdDrawIndirectCountAMD)LoadFunc(Device, "vkCmdDrawIndirectCountAMD");
#endif /*  defined(VK_AMD_draw_indirect_count)  */
#if defined(VK_AMD_shader_info)
    FuncArray->vkGetShaderInfoAMD = (PFN_vkGetShaderInfoAMD)LoadFunc(Device, "vkGetShaderInfoAMD");
#endif /*  defined(VK_AMD_shader_info)  */
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
    FuncArray->vkGetAndroidHardwareBufferPropertiesANDROID = (PFN_vkGetAndroidHardwareBufferPropertiesANDROID)LoadFunc(Device, "vkGetAndroidHardwareBufferPropertiesANDROID");
    FuncArray->vkGetMemoryAndroidHardwareBufferANDROID = (PFN_vkGetMemoryAndroidHardwareBufferANDROID)LoadFunc(Device, "vkGetMemoryAndroidHardwareBufferANDROID");
#endif /*  defined(VK_ANDROID_external_memory_android_hardware_buffer)  */
#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
    FuncArray->vkCmdSetAttachmentFeedbackLoopEnableEXT = (PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT)LoadFunc(Device, "vkCmdSetAttachmentFeedbackLoopEnableEXT");
#endif /*  defined(VK_EXT_attachment_feedback_loop_dynamic_state)  */
#if defined(VK_EXT_buffer_device_address)
    FuncArray->vkGetBufferDeviceAddressEXT = (PFN_vkGetBufferDeviceAddressEXT)LoadFunc(Device, "vkGetBufferDeviceAddressEXT");
#endif /*  defined(VK_EXT_buffer_device_address)  */
#if defined(VK_EXT_calibrated_timestamps)
    FuncArray->vkGetCalibratedTimestampsEXT = (PFN_vkGetCalibratedTimestampsEXT)LoadFunc(Device, "vkGetCalibratedTimestampsEXT");
#endif /*  defined(VK_EXT_calibrated_timestamps)  */
#if defined(VK_EXT_color_write_enable)
    FuncArray->vkCmdSetColorWriteEnableEXT = (PFN_vkCmdSetColorWriteEnableEXT)LoadFunc(Device, "vkCmdSetColorWriteEnableEXT");
#endif /*  defined(VK_EXT_color_write_enable)  */
#if defined(VK_EXT_conditional_rendering)
    FuncArray->vkCmdBeginConditionalRenderingEXT = (PFN_vkCmdBeginConditionalRenderingEXT)LoadFunc(Device, "vkCmdBeginConditionalRenderingEXT");
    FuncArray->vkCmdEndConditionalRenderingEXT = (PFN_vkCmdEndConditionalRenderingEXT)LoadFunc(Device, "vkCmdEndConditionalRenderingEXT");
#endif /*  defined(VK_EXT_conditional_rendering)  */
#if defined(VK_EXT_debug_marker)
    FuncArray->vkCmdDebugMarkerBeginEXT = (PFN_vkCmdDebugMarkerBeginEXT)LoadFunc(Device, "vkCmdDebugMarkerBeginEXT");
    FuncArray->vkCmdDebugMarkerEndEXT = (PFN_vkCmdDebugMarkerEndEXT)LoadFunc(Device, "vkCmdDebugMarkerEndEXT");
    FuncArray->vkCmdDebugMarkerInsertEXT = (PFN_vkCmdDebugMarkerInsertEXT)LoadFunc(Device, "vkCmdDebugMarkerInsertEXT");
    FuncArray->vkDebugMarkerSetObjectNameEXT = (PFN_vkDebugMarkerSetObjectNameEXT)LoadFunc(Device, "vkDebugMarkerSetObjectNameEXT");
    FuncArray->vkDebugMarkerSetObjectTagEXT = (PFN_vkDebugMarkerSetObjectTagEXT)LoadFunc(Device, "vkDebugMarkerSetObjectTagEXT");
#endif /*  defined(VK_EXT_debug_marker)  */
#if defined(VK_EXT_depth_bias_control)
    FuncArray->vkCmdSetDepthBias2EXT = (PFN_vkCmdSetDepthBias2EXT)LoadFunc(Device, "vkCmdSetDepthBias2EXT");
#endif /*  defined(VK_EXT_depth_bias_control)  */
#if defined(VK_EXT_descriptor_buffer)
    FuncArray->vkCmdBindDescriptorBufferEmbeddedSamplersEXT = (PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT)LoadFunc(Device, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT");
    FuncArray->vkCmdBindDescriptorBuffersEXT = (PFN_vkCmdBindDescriptorBuffersEXT)LoadFunc(Device, "vkCmdBindDescriptorBuffersEXT");
    FuncArray->vkCmdSetDescriptorBufferOffsetsEXT = (PFN_vkCmdSetDescriptorBufferOffsetsEXT)LoadFunc(Device, "vkCmdSetDescriptorBufferOffsetsEXT");
    FuncArray->vkGetBufferOpaqueCaptureDescriptorDataEXT = (PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT)LoadFunc(Device, "vkGetBufferOpaqueCaptureDescriptorDataEXT");
    FuncArray->vkGetDescriptorEXT = (PFN_vkGetDescriptorEXT)LoadFunc(Device, "vkGetDescriptorEXT");
    FuncArray->vkGetDescriptorSetLayoutBindingOffsetEXT = (PFN_vkGetDescriptorSetLayoutBindingOffsetEXT)LoadFunc(Device, "vkGetDescriptorSetLayoutBindingOffsetEXT");
    FuncArray->vkGetDescriptorSetLayoutSizeEXT = (PFN_vkGetDescriptorSetLayoutSizeEXT)LoadFunc(Device, "vkGetDescriptorSetLayoutSizeEXT");
    FuncArray->vkGetImageOpaqueCaptureDescriptorDataEXT = (PFN_vkGetImageOpaqueCaptureDescriptorDataEXT)LoadFunc(Device, "vkGetImageOpaqueCaptureDescriptorDataEXT");
    FuncArray->vkGetImageViewOpaqueCaptureDescriptorDataEXT = (PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT)LoadFunc(Device, "vkGetImageViewOpaqueCaptureDescriptorDataEXT");
    FuncArray->vkGetSamplerOpaqueCaptureDescriptorDataEXT = (PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT)LoadFunc(Device, "vkGetSamplerOpaqueCaptureDescriptorDataEXT");
#endif /*  defined(VK_EXT_descriptor_buffer)  */
#if defined(VK_EXT_descriptor_buffer) && (defined(VK_KHR_acceleration_structure) || defined(VK_NV_ray_tracing))
    FuncArray->vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = (PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT)LoadFunc(Device, "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT");
#endif /*  defined(VK_EXT_descriptor_buffer) && (defined(VK_KHR_acceleration_structure) || defined(VK_NV_ray_tracing))  */
#if defined(VK_EXT_device_fault)
    FuncArray->vkGetDeviceFaultInfoEXT = (PFN_vkGetDeviceFaultInfoEXT)LoadFunc(Device, "vkGetDeviceFaultInfoEXT");
#endif /*  defined(VK_EXT_device_fault)  */
#if defined(VK_EXT_discard_rectangles)
    FuncArray->vkCmdSetDiscardRectangleEXT = (PFN_vkCmdSetDiscardRectangleEXT)LoadFunc(Device, "vkCmdSetDiscardRectangleEXT");
#endif /*  defined(VK_EXT_discard_rectangles)  */
#if defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2
    FuncArray->vkCmdSetDiscardRectangleEnableEXT = (PFN_vkCmdSetDiscardRectangleEnableEXT)LoadFunc(Device, "vkCmdSetDiscardRectangleEnableEXT");
    FuncArray->vkCmdSetDiscardRectangleModeEXT = (PFN_vkCmdSetDiscardRectangleModeEXT)LoadFunc(Device, "vkCmdSetDiscardRectangleModeEXT");
#endif /*  defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2  */
#if defined(VK_EXT_display_control)
    FuncArray->vkDisplayPowerControlEXT = (PFN_vkDisplayPowerControlEXT)LoadFunc(Device, "vkDisplayPowerControlEXT");
    FuncArray->vkGetSwapchainCounterEXT = (PFN_vkGetSwapchainCounterEXT)LoadFunc(Device, "vkGetSwapchainCounterEXT");
    FuncArray->vkRegisterDeviceEventEXT = (PFN_vkRegisterDeviceEventEXT)LoadFunc(Device, "vkRegisterDeviceEventEXT");
    FuncArray->vkRegisterDisplayEventEXT = (PFN_vkRegisterDisplayEventEXT)LoadFunc(Device, "vkRegisterDisplayEventEXT");
#endif /*  defined(VK_EXT_display_control)  */
#if defined(VK_EXT_external_memory_host)
    FuncArray->vkGetMemoryHostPointerPropertiesEXT = (PFN_vkGetMemoryHostPointerPropertiesEXT)LoadFunc(Device, "vkGetMemoryHostPointerPropertiesEXT");
#endif /*  defined(VK_EXT_external_memory_host)  */
#if defined(VK_EXT_full_screen_exclusive)
    FuncArray->vkAcquireFullScreenExclusiveModeEXT = (PFN_vkAcquireFullScreenExclusiveModeEXT)LoadFunc(Device, "vkAcquireFullScreenExclusiveModeEXT");
    FuncArray->vkReleaseFullScreenExclusiveModeEXT = (PFN_vkReleaseFullScreenExclusiveModeEXT)LoadFunc(Device, "vkReleaseFullScreenExclusiveModeEXT");
#endif /*  defined(VK_EXT_full_screen_exclusive)  */
#if defined(VK_EXT_hdr_metadata)
    FuncArray->vkSetHdrMetadataEXT = (PFN_vkSetHdrMetadataEXT)LoadFunc(Device, "vkSetHdrMetadataEXT");
#endif /*  defined(VK_EXT_hdr_metadata)  */
#if defined(VK_EXT_host_image_copy)
    FuncArray->vkCopyImageToImageEXT = (PFN_vkCopyImageToImageEXT)LoadFunc(Device, "vkCopyImageToImageEXT");
    FuncArray->vkCopyImageToMemoryEXT = (PFN_vkCopyImageToMemoryEXT)LoadFunc(Device, "vkCopyImageToMemoryEXT");
    FuncArray->vkCopyMemoryToImageEXT = (PFN_vkCopyMemoryToImageEXT)LoadFunc(Device, "vkCopyMemoryToImageEXT");
    FuncArray->vkTransitionImageLayoutEXT = (PFN_vkTransitionImageLayoutEXT)LoadFunc(Device, "vkTransitionImageLayoutEXT");
#endif /*  defined(VK_EXT_host_image_copy)  */
#if defined(VK_EXT_host_query_reset)
    FuncArray->vkResetQueryPoolEXT = (PFN_vkResetQueryPoolEXT)LoadFunc(Device, "vkResetQueryPoolEXT");
#endif /*  defined(VK_EXT_host_query_reset)  */
#if defined(VK_EXT_image_drm_format_modifier)
    FuncArray->vkGetImageDrmFormatModifierPropertiesEXT = (PFN_vkGetImageDrmFormatModifierPropertiesEXT)LoadFunc(Device, "vkGetImageDrmFormatModifierPropertiesEXT");
#endif /*  defined(VK_EXT_image_drm_format_modifier)  */
#if defined(VK_EXT_line_rasterization)
    FuncArray->vkCmdSetLineStippleEXT = (PFN_vkCmdSetLineStippleEXT)LoadFunc(Device, "vkCmdSetLineStippleEXT");
#endif /*  defined(VK_EXT_line_rasterization)  */
#if defined(VK_EXT_mesh_shader)
    FuncArray->vkCmdDrawMeshTasksEXT = (PFN_vkCmdDrawMeshTasksEXT)LoadFunc(Device, "vkCmdDrawMeshTasksEXT");
    FuncArray->vkCmdDrawMeshTasksIndirectCountEXT = (PFN_vkCmdDrawMeshTasksIndirectCountEXT)LoadFunc(Device, "vkCmdDrawMeshTasksIndirectCountEXT");
    FuncArray->vkCmdDrawMeshTasksIndirectEXT = (PFN_vkCmdDrawMeshTasksIndirectEXT)LoadFunc(Device, "vkCmdDrawMeshTasksIndirectEXT");
#endif /*  defined(VK_EXT_mesh_shader)  */
#if defined(VK_EXT_metal_objects)
    FuncArray->vkExportMetalObjectsEXT = (PFN_vkExportMetalObjectsEXT)LoadFunc(Device, "vkExportMetalObjectsEXT");
#endif /*  defined(VK_EXT_metal_objects)  */
#if defined(VK_EXT_multi_draw)
    FuncArray->vkCmdDrawMultiEXT = (PFN_vkCmdDrawMultiEXT)LoadFunc(Device, "vkCmdDrawMultiEXT");
    FuncArray->vkCmdDrawMultiIndexedEXT = (PFN_vkCmdDrawMultiIndexedEXT)LoadFunc(Device, "vkCmdDrawMultiIndexedEXT");
#endif /*  defined(VK_EXT_multi_draw)  */
#if defined(VK_EXT_opacity_micromap)
    FuncArray->vkBuildMicromapsEXT = (PFN_vkBuildMicromapsEXT)LoadFunc(Device, "vkBuildMicromapsEXT");
    FuncArray->vkCmdBuildMicromapsEXT = (PFN_vkCmdBuildMicromapsEXT)LoadFunc(Device, "vkCmdBuildMicromapsEXT");
    FuncArray->vkCmdCopyMemoryToMicromapEXT = (PFN_vkCmdCopyMemoryToMicromapEXT)LoadFunc(Device, "vkCmdCopyMemoryToMicromapEXT");
    FuncArray->vkCmdCopyMicromapEXT = (PFN_vkCmdCopyMicromapEXT)LoadFunc(Device, "vkCmdCopyMicromapEXT");
    FuncArray->vkCmdCopyMicromapToMemoryEXT = (PFN_vkCmdCopyMicromapToMemoryEXT)LoadFunc(Device, "vkCmdCopyMicromapToMemoryEXT");
    FuncArray->vkCmdWriteMicromapsPropertiesEXT = (PFN_vkCmdWriteMicromapsPropertiesEXT)LoadFunc(Device, "vkCmdWriteMicromapsPropertiesEXT");
    FuncArray->vkCopyMemoryToMicromapEXT = (PFN_vkCopyMemoryToMicromapEXT)LoadFunc(Device, "vkCopyMemoryToMicromapEXT");
    FuncArray->vkCopyMicromapEXT = (PFN_vkCopyMicromapEXT)LoadFunc(Device, "vkCopyMicromapEXT");
    FuncArray->vkCopyMicromapToMemoryEXT = (PFN_vkCopyMicromapToMemoryEXT)LoadFunc(Device, "vkCopyMicromapToMemoryEXT");
    FuncArray->vkCreateMicromapEXT = (PFN_vkCreateMicromapEXT)LoadFunc(Device, "vkCreateMicromapEXT");
    FuncArray->vkDestroyMicromapEXT = (PFN_vkDestroyMicromapEXT)LoadFunc(Device, "vkDestroyMicromapEXT");
    FuncArray->vkGetDeviceMicromapCompatibilityEXT = (PFN_vkGetDeviceMicromapCompatibilityEXT)LoadFunc(Device, "vkGetDeviceMicromapCompatibilityEXT");
    FuncArray->vkGetMicromapBuildSizesEXT = (PFN_vkGetMicromapBuildSizesEXT)LoadFunc(Device, "vkGetMicromapBuildSizesEXT");
    FuncArray->vkWriteMicromapsPropertiesEXT = (PFN_vkWriteMicromapsPropertiesEXT)LoadFunc(Device, "vkWriteMicromapsPropertiesEXT");
#endif /*  defined(VK_EXT_opacity_micromap)  */
#if defined(VK_EXT_pageable_device_local_memory)
    FuncArray->vkSetDeviceMemoryPriorityEXT = (PFN_vkSetDeviceMemoryPriorityEXT)LoadFunc(Device, "vkSetDeviceMemoryPriorityEXT");
#endif /*  defined(VK_EXT_pageable_device_local_memory)  */
#if defined(VK_EXT_pipeline_properties)
    FuncArray->vkGetPipelinePropertiesEXT = (PFN_vkGetPipelinePropertiesEXT)LoadFunc(Device, "vkGetPipelinePropertiesEXT");
#endif /*  defined(VK_EXT_pipeline_properties)  */
#if defined(VK_EXT_private_data)
    FuncArray->vkCreatePrivateDataSlotEXT = (PFN_vkCreatePrivateDataSlotEXT)LoadFunc(Device, "vkCreatePrivateDataSlotEXT");
    FuncArray->vkDestroyPrivateDataSlotEXT = (PFN_vkDestroyPrivateDataSlotEXT)LoadFunc(Device, "vkDestroyPrivateDataSlotEXT");
    FuncArray->vkGetPrivateDataEXT = (PFN_vkGetPrivateDataEXT)LoadFunc(Device, "vkGetPrivateDataEXT");
    FuncArray->vkSetPrivateDataEXT = (PFN_vkSetPrivateDataEXT)LoadFunc(Device, "vkSetPrivateDataEXT");
#endif /*  defined(VK_EXT_private_data)  */
#if defined(VK_EXT_sample_locations)
    FuncArray->vkCmdSetSampleLocationsEXT = (PFN_vkCmdSetSampleLocationsEXT)LoadFunc(Device, "vkCmdSetSampleLocationsEXT");
#endif /*  defined(VK_EXT_sample_locations)  */
#if defined(VK_EXT_shader_module_identifier)
    FuncArray->vkGetShaderModuleCreateInfoIdentifierEXT = (PFN_vkGetShaderModuleCreateInfoIdentifierEXT)LoadFunc(Device, "vkGetShaderModuleCreateInfoIdentifierEXT");
    FuncArray->vkGetShaderModuleIdentifierEXT = (PFN_vkGetShaderModuleIdentifierEXT)LoadFunc(Device, "vkGetShaderModuleIdentifierEXT");
#endif /*  defined(VK_EXT_shader_module_identifier)  */
#if defined(VK_EXT_shader_object)
    FuncArray->vkCmdBindShadersEXT = (PFN_vkCmdBindShadersEXT)LoadFunc(Device, "vkCmdBindShadersEXT");
    FuncArray->vkCreateShadersEXT = (PFN_vkCreateShadersEXT)LoadFunc(Device, "vkCreateShadersEXT");
    FuncArray->vkDestroyShaderEXT = (PFN_vkDestroyShaderEXT)LoadFunc(Device, "vkDestroyShaderEXT");
    FuncArray->vkGetShaderBinaryDataEXT = (PFN_vkGetShaderBinaryDataEXT)LoadFunc(Device, "vkGetShaderBinaryDataEXT");
#endif /*  defined(VK_EXT_shader_object)  */
#if defined(VK_EXT_swapchain_maintenance1)
    FuncArray->vkReleaseSwapchainImagesEXT = (PFN_vkReleaseSwapchainImagesEXT)LoadFunc(Device, "vkReleaseSwapchainImagesEXT");
#endif /*  defined(VK_EXT_swapchain_maintenance1)  */
#if defined(VK_EXT_transform_feedback)
    FuncArray->vkCmdBeginQueryIndexedEXT = (PFN_vkCmdBeginQueryIndexedEXT)LoadFunc(Device, "vkCmdBeginQueryIndexedEXT");
    FuncArray->vkCmdBeginTransformFeedbackEXT = (PFN_vkCmdBeginTransformFeedbackEXT)LoadFunc(Device, "vkCmdBeginTransformFeedbackEXT");
    FuncArray->vkCmdBindTransformFeedbackBuffersEXT = (PFN_vkCmdBindTransformFeedbackBuffersEXT)LoadFunc(Device, "vkCmdBindTransformFeedbackBuffersEXT");
    FuncArray->vkCmdDrawIndirectByteCountEXT = (PFN_vkCmdDrawIndirectByteCountEXT)LoadFunc(Device, "vkCmdDrawIndirectByteCountEXT");
    FuncArray->vkCmdEndQueryIndexedEXT = (PFN_vkCmdEndQueryIndexedEXT)LoadFunc(Device, "vkCmdEndQueryIndexedEXT");
    FuncArray->vkCmdEndTransformFeedbackEXT = (PFN_vkCmdEndTransformFeedbackEXT)LoadFunc(Device, "vkCmdEndTransformFeedbackEXT");
#endif /*  defined(VK_EXT_transform_feedback)  */
#if defined(VK_EXT_validation_cache)
    FuncArray->vkCreateValidationCacheEXT = (PFN_vkCreateValidationCacheEXT)LoadFunc(Device, "vkCreateValidationCacheEXT");
    FuncArray->vkDestroyValidationCacheEXT = (PFN_vkDestroyValidationCacheEXT)LoadFunc(Device, "vkDestroyValidationCacheEXT");
    FuncArray->vkGetValidationCacheDataEXT = (PFN_vkGetValidationCacheDataEXT)LoadFunc(Device, "vkGetValidationCacheDataEXT");
    FuncArray->vkMergeValidationCachesEXT = (PFN_vkMergeValidationCachesEXT)LoadFunc(Device, "vkMergeValidationCachesEXT");
#endif /*  defined(VK_EXT_validation_cache)  */
#if defined(VK_FUCHSIA_buffer_collection)
    FuncArray->vkCreateBufferCollectionFUCHSIA = (PFN_vkCreateBufferCollectionFUCHSIA)LoadFunc(Device, "vkCreateBufferCollectionFUCHSIA");
    FuncArray->vkDestroyBufferCollectionFUCHSIA = (PFN_vkDestroyBufferCollectionFUCHSIA)LoadFunc(Device, "vkDestroyBufferCollectionFUCHSIA");
    FuncArray->vkGetBufferCollectionPropertiesFUCHSIA = (PFN_vkGetBufferCollectionPropertiesFUCHSIA)LoadFunc(Device, "vkGetBufferCollectionPropertiesFUCHSIA");
    FuncArray->vkSetBufferCollectionBufferConstraintsFUCHSIA = (PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA)LoadFunc(Device, "vkSetBufferCollectionBufferConstraintsFUCHSIA");
    FuncArray->vkSetBufferCollectionImageConstraintsFUCHSIA = (PFN_vkSetBufferCollectionImageConstraintsFUCHSIA)LoadFunc(Device, "vkSetBufferCollectionImageConstraintsFUCHSIA");
#endif /*  defined(VK_FUCHSIA_buffer_collection)  */
#if defined(VK_FUCHSIA_external_memory)
    FuncArray->vkGetMemoryZirconHandleFUCHSIA = (PFN_vkGetMemoryZirconHandleFUCHSIA)LoadFunc(Device, "vkGetMemoryZirconHandleFUCHSIA");
    FuncArray->vkGetMemoryZirconHandlePropertiesFUCHSIA = (PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA)LoadFunc(Device, "vkGetMemoryZirconHandlePropertiesFUCHSIA");
#endif /*  defined(VK_FUCHSIA_external_memory)  */
#if defined(VK_FUCHSIA_external_semaphore)
    FuncArray->vkGetSemaphoreZirconHandleFUCHSIA = (PFN_vkGetSemaphoreZirconHandleFUCHSIA)LoadFunc(Device, "vkGetSemaphoreZirconHandleFUCHSIA");
    FuncArray->vkImportSemaphoreZirconHandleFUCHSIA = (PFN_vkImportSemaphoreZirconHandleFUCHSIA)LoadFunc(Device, "vkImportSemaphoreZirconHandleFUCHSIA");
#endif /*  defined(VK_FUCHSIA_external_semaphore)  */
#if defined(VK_GOOGLE_display_timing)
    FuncArray->vkGetPastPresentationTimingGOOGLE = (PFN_vkGetPastPresentationTimingGOOGLE)LoadFunc(Device, "vkGetPastPresentationTimingGOOGLE");
    FuncArray->vkGetRefreshCycleDurationGOOGLE = (PFN_vkGetRefreshCycleDurationGOOGLE)LoadFunc(Device, "vkGetRefreshCycleDurationGOOGLE");
#endif /*  defined(VK_GOOGLE_display_timing)  */
#if defined(VK_HUAWEI_cluster_culling_shader)
    FuncArray->vkCmdDrawClusterHUAWEI = (PFN_vkCmdDrawClusterHUAWEI)LoadFunc(Device, "vkCmdDrawClusterHUAWEI");
    FuncArray->vkCmdDrawClusterIndirectHUAWEI = (PFN_vkCmdDrawClusterIndirectHUAWEI)LoadFunc(Device, "vkCmdDrawClusterIndirectHUAWEI");
#endif /*  defined(VK_HUAWEI_cluster_culling_shader)  */
#if defined(VK_HUAWEI_invocation_mask)
    FuncArray->vkCmdBindInvocationMaskHUAWEI = (PFN_vkCmdBindInvocationMaskHUAWEI)LoadFunc(Device, "vkCmdBindInvocationMaskHUAWEI");
#endif /*  defined(VK_HUAWEI_invocation_mask)  */
#if defined(VK_HUAWEI_subpass_shading)
    FuncArray->vkCmdSubpassShadingHUAWEI = (PFN_vkCmdSubpassShadingHUAWEI)LoadFunc(Device, "vkCmdSubpassShadingHUAWEI");
    FuncArray->vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI = (PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI)LoadFunc(Device, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI");
#endif /*  defined(VK_HUAWEI_subpass_shading)  */
#if defined(VK_INTEL_performance_query)
    FuncArray->vkAcquirePerformanceConfigurationINTEL = (PFN_vkAcquirePerformanceConfigurationINTEL)LoadFunc(Device, "vkAcquirePerformanceConfigurationINTEL");
    FuncArray->vkCmdSetPerformanceMarkerINTEL = (PFN_vkCmdSetPerformanceMarkerINTEL)LoadFunc(Device, "vkCmdSetPerformanceMarkerINTEL");
    FuncArray->vkCmdSetPerformanceOverrideINTEL = (PFN_vkCmdSetPerformanceOverrideINTEL)LoadFunc(Device, "vkCmdSetPerformanceOverrideINTEL");
    FuncArray->vkCmdSetPerformanceStreamMarkerINTEL = (PFN_vkCmdSetPerformanceStreamMarkerINTEL)LoadFunc(Device, "vkCmdSetPerformanceStreamMarkerINTEL");
    FuncArray->vkGetPerformanceParameterINTEL = (PFN_vkGetPerformanceParameterINTEL)LoadFunc(Device, "vkGetPerformanceParameterINTEL");
    FuncArray->vkInitializePerformanceApiINTEL = (PFN_vkInitializePerformanceApiINTEL)LoadFunc(Device, "vkInitializePerformanceApiINTEL");
    FuncArray->vkQueueSetPerformanceConfigurationINTEL = (PFN_vkQueueSetPerformanceConfigurationINTEL)LoadFunc(Device, "vkQueueSetPerformanceConfigurationINTEL");
    FuncArray->vkReleasePerformanceConfigurationINTEL = (PFN_vkReleasePerformanceConfigurationINTEL)LoadFunc(Device, "vkReleasePerformanceConfigurationINTEL");
    FuncArray->vkUninitializePerformanceApiINTEL = (PFN_vkUninitializePerformanceApiINTEL)LoadFunc(Device, "vkUninitializePerformanceApiINTEL");
#endif /*  defined(VK_INTEL_performance_query)  */
#if defined(VK_KHR_acceleration_structure)
    FuncArray->vkBuildAccelerationStructuresKHR = (PFN_vkBuildAccelerationStructuresKHR)LoadFunc(Device, "vkBuildAccelerationStructuresKHR");
    FuncArray->vkCmdBuildAccelerationStructuresIndirectKHR = (PFN_vkCmdBuildAccelerationStructuresIndirectKHR)LoadFunc(Device, "vkCmdBuildAccelerationStructuresIndirectKHR");
    FuncArray->vkCmdBuildAccelerationStructuresKHR = (PFN_vkCmdBuildAccelerationStructuresKHR)LoadFunc(Device, "vkCmdBuildAccelerationStructuresKHR");
    FuncArray->vkCmdCopyAccelerationStructureKHR = (PFN_vkCmdCopyAccelerationStructureKHR)LoadFunc(Device, "vkCmdCopyAccelerationStructureKHR");
    FuncArray->vkCmdCopyAccelerationStructureToMemoryKHR = (PFN_vkCmdCopyAccelerationStructureToMemoryKHR)LoadFunc(Device, "vkCmdCopyAccelerationStructureToMemoryKHR");
    FuncArray->vkCmdCopyMemoryToAccelerationStructureKHR = (PFN_vkCmdCopyMemoryToAccelerationStructureKHR)LoadFunc(Device, "vkCmdCopyMemoryToAccelerationStructureKHR");
    FuncArray->vkCmdWriteAccelerationStructuresPropertiesKHR = (PFN_vkCmdWriteAccelerationStructuresPropertiesKHR)LoadFunc(Device, "vkCmdWriteAccelerationStructuresPropertiesKHR");
    FuncArray->vkCopyAccelerationStructureKHR = (PFN_vkCopyAccelerationStructureKHR)LoadFunc(Device, "vkCopyAccelerationStructureKHR");
    FuncArray->vkCopyAccelerationStructureToMemoryKHR = (PFN_vkCopyAccelerationStructureToMemoryKHR)LoadFunc(Device, "vkCopyAccelerationStructureToMemoryKHR");
    FuncArray->vkCopyMemoryToAccelerationStructureKHR = (PFN_vkCopyMemoryToAccelerationStructureKHR)LoadFunc(Device, "vkCopyMemoryToAccelerationStructureKHR");
    FuncArray->vkCreateAccelerationStructureKHR = (PFN_vkCreateAccelerationStructureKHR)LoadFunc(Device, "vkCreateAccelerationStructureKHR");
    FuncArray->vkDestroyAccelerationStructureKHR = (PFN_vkDestroyAccelerationStructureKHR)LoadFunc(Device, "vkDestroyAccelerationStructureKHR");
    FuncArray->vkGetAccelerationStructureBuildSizesKHR = (PFN_vkGetAccelerationStructureBuildSizesKHR)LoadFunc(Device, "vkGetAccelerationStructureBuildSizesKHR");
    FuncArray->vkGetAccelerationStructureDeviceAddressKHR = (PFN_vkGetAccelerationStructureDeviceAddressKHR)LoadFunc(Device, "vkGetAccelerationStructureDeviceAddressKHR");
    FuncArray->vkGetDeviceAccelerationStructureCompatibilityKHR = (PFN_vkGetDeviceAccelerationStructureCompatibilityKHR)LoadFunc(Device, "vkGetDeviceAccelerationStructureCompatibilityKHR");
    FuncArray->vkWriteAccelerationStructuresPropertiesKHR = (PFN_vkWriteAccelerationStructuresPropertiesKHR)LoadFunc(Device, "vkWriteAccelerationStructuresPropertiesKHR");
#endif /*  defined(VK_KHR_acceleration_structure)  */
#if defined(VK_KHR_bind_memory2)
    FuncArray->vkBindBufferMemory2KHR = (PFN_vkBindBufferMemory2KHR)LoadFunc(Device, "vkBindBufferMemory2KHR");
    FuncArray->vkBindImageMemory2KHR = (PFN_vkBindImageMemory2KHR)LoadFunc(Device, "vkBindImageMemory2KHR");
#endif /*  defined(VK_KHR_bind_memory2)  */
#if defined(VK_KHR_buffer_device_address)
    FuncArray->vkGetBufferDeviceAddressKHR = (PFN_vkGetBufferDeviceAddressKHR)LoadFunc(Device, "vkGetBufferDeviceAddressKHR");
    FuncArray->vkGetBufferOpaqueCaptureAddressKHR = (PFN_vkGetBufferOpaqueCaptureAddressKHR)LoadFunc(Device, "vkGetBufferOpaqueCaptureAddressKHR");
    FuncArray->vkGetDeviceMemoryOpaqueCaptureAddressKHR = (PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR)LoadFunc(Device, "vkGetDeviceMemoryOpaqueCaptureAddressKHR");
#endif /*  defined(VK_KHR_buffer_device_address)  */
#if defined(VK_KHR_calibrated_timestamps)
    FuncArray->vkGetCalibratedTimestampsKHR = (PFN_vkGetCalibratedTimestampsKHR)LoadFunc(Device, "vkGetCalibratedTimestampsKHR");
#endif /*  defined(VK_KHR_calibrated_timestamps)  */
#if defined(VK_KHR_copy_commands2)
    FuncArray->vkCmdBlitImage2KHR = (PFN_vkCmdBlitImage2KHR)LoadFunc(Device, "vkCmdBlitImage2KHR");
    FuncArray->vkCmdCopyBuffer2KHR = (PFN_vkCmdCopyBuffer2KHR)LoadFunc(Device, "vkCmdCopyBuffer2KHR");
    FuncArray->vkCmdCopyBufferToImage2KHR = (PFN_vkCmdCopyBufferToImage2KHR)LoadFunc(Device, "vkCmdCopyBufferToImage2KHR");
    FuncArray->vkCmdCopyImage2KHR = (PFN_vkCmdCopyImage2KHR)LoadFunc(Device, "vkCmdCopyImage2KHR");
    FuncArray->vkCmdCopyImageToBuffer2KHR = (PFN_vkCmdCopyImageToBuffer2KHR)LoadFunc(Device, "vkCmdCopyImageToBuffer2KHR");
    FuncArray->vkCmdResolveImage2KHR = (PFN_vkCmdResolveImage2KHR)LoadFunc(Device, "vkCmdResolveImage2KHR");
#endif /*  defined(VK_KHR_copy_commands2)  */
#if defined(VK_KHR_create_renderpass2)
    FuncArray->vkCmdBeginRenderPass2KHR = (PFN_vkCmdBeginRenderPass2KHR)LoadFunc(Device, "vkCmdBeginRenderPass2KHR");
    FuncArray->vkCmdEndRenderPass2KHR = (PFN_vkCmdEndRenderPass2KHR)LoadFunc(Device, "vkCmdEndRenderPass2KHR");
    FuncArray->vkCmdNextSubpass2KHR = (PFN_vkCmdNextSubpass2KHR)LoadFunc(Device, "vkCmdNextSubpass2KHR");
    FuncArray->vkCreateRenderPass2KHR = (PFN_vkCreateRenderPass2KHR)LoadFunc(Device, "vkCreateRenderPass2KHR");
#endif /*  defined(VK_KHR_create_renderpass2)  */
#if defined(VK_KHR_deferred_host_operations)
    FuncArray->vkCreateDeferredOperationKHR = (PFN_vkCreateDeferredOperationKHR)LoadFunc(Device, "vkCreateDeferredOperationKHR");
    FuncArray->vkDeferredOperationJoinKHR = (PFN_vkDeferredOperationJoinKHR)LoadFunc(Device, "vkDeferredOperationJoinKHR");
    FuncArray->vkDestroyDeferredOperationKHR = (PFN_vkDestroyDeferredOperationKHR)LoadFunc(Device, "vkDestroyDeferredOperationKHR");
    FuncArray->vkGetDeferredOperationMaxConcurrencyKHR = (PFN_vkGetDeferredOperationMaxConcurrencyKHR)LoadFunc(Device, "vkGetDeferredOperationMaxConcurrencyKHR");
    FuncArray->vkGetDeferredOperationResultKHR = (PFN_vkGetDeferredOperationResultKHR)LoadFunc(Device, "vkGetDeferredOperationResultKHR");
#endif /*  defined(VK_KHR_deferred_host_operations)  */
#if defined(VK_KHR_descriptor_update_template)
    FuncArray->vkCreateDescriptorUpdateTemplateKHR = (PFN_vkCreateDescriptorUpdateTemplateKHR)LoadFunc(Device, "vkCreateDescriptorUpdateTemplateKHR");
    FuncArray->vkDestroyDescriptorUpdateTemplateKHR = (PFN_vkDestroyDescriptorUpdateTemplateKHR)LoadFunc(Device, "vkDestroyDescriptorUpdateTemplateKHR");
    FuncArray->vkUpdateDescriptorSetWithTemplateKHR = (PFN_vkUpdateDescriptorSetWithTemplateKHR)LoadFunc(Device, "vkUpdateDescriptorSetWithTemplateKHR");
#endif /*  defined(VK_KHR_descriptor_update_template)  */
#if defined(VK_KHR_device_group)
    FuncArray->vkCmdDispatchBaseKHR = (PFN_vkCmdDispatchBaseKHR)LoadFunc(Device, "vkCmdDispatchBaseKHR");
    FuncArray->vkCmdSetDeviceMaskKHR = (PFN_vkCmdSetDeviceMaskKHR)LoadFunc(Device, "vkCmdSetDeviceMaskKHR");
    FuncArray->vkGetDeviceGroupPeerMemoryFeaturesKHR = (PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR)LoadFunc(Device, "vkGetDeviceGroupPeerMemoryFeaturesKHR");
#endif /*  defined(VK_KHR_device_group)  */
#if defined(VK_KHR_display_swapchain)
    FuncArray->vkCreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR)LoadFunc(Device, "vkCreateSharedSwapchainsKHR");
#endif /*  defined(VK_KHR_display_swapchain)  */
#if defined(VK_KHR_draw_indirect_count)
    FuncArray->vkCmdDrawIndexedIndirectCountKHR = (PFN_vkCmdDrawIndexedIndirectCountKHR)LoadFunc(Device, "vkCmdDrawIndexedIndirectCountKHR");
    FuncArray->vkCmdDrawIndirectCountKHR = (PFN_vkCmdDrawIndirectCountKHR)LoadFunc(Device, "vkCmdDrawIndirectCountKHR");
#endif /*  defined(VK_KHR_draw_indirect_count)  */
#if defined(VK_KHR_dynamic_rendering)
    FuncArray->vkCmdBeginRenderingKHR = (PFN_vkCmdBeginRenderingKHR)LoadFunc(Device, "vkCmdBeginRenderingKHR");
    FuncArray->vkCmdEndRenderingKHR = (PFN_vkCmdEndRenderingKHR)LoadFunc(Device, "vkCmdEndRenderingKHR");
#endif /*  defined(VK_KHR_dynamic_rendering)  */
#if defined(VK_KHR_dynamic_rendering_local_read)
    FuncArray->vkCmdSetRenderingAttachmentLocationsKHR = (PFN_vkCmdSetRenderingAttachmentLocationsKHR)LoadFunc(Device, "vkCmdSetRenderingAttachmentLocationsKHR");
    FuncArray->vkCmdSetRenderingInputAttachmentIndicesKHR = (PFN_vkCmdSetRenderingInputAttachmentIndicesKHR)LoadFunc(Device, "vkCmdSetRenderingInputAttachmentIndicesKHR");
#endif /*  defined(VK_KHR_dynamic_rendering_local_read)  */
#if defined(VK_KHR_external_fence_fd)
    FuncArray->vkGetFenceFdKHR = (PFN_vkGetFenceFdKHR)LoadFunc(Device, "vkGetFenceFdKHR");
    FuncArray->vkImportFenceFdKHR = (PFN_vkImportFenceFdKHR)LoadFunc(Device, "vkImportFenceFdKHR");
#endif /*  defined(VK_KHR_external_fence_fd)  */
#if defined(VK_KHR_external_fence_win32)
    FuncArray->vkGetFenceWin32HandleKHR = (PFN_vkGetFenceWin32HandleKHR)LoadFunc(Device, "vkGetFenceWin32HandleKHR");
    FuncArray->vkImportFenceWin32HandleKHR = (PFN_vkImportFenceWin32HandleKHR)LoadFunc(Device, "vkImportFenceWin32HandleKHR");
#endif /*  defined(VK_KHR_external_fence_win32)  */
#if defined(VK_KHR_external_memory_fd)
    FuncArray->vkGetMemoryFdKHR = (PFN_vkGetMemoryFdKHR)LoadFunc(Device, "vkGetMemoryFdKHR");
    FuncArray->vkGetMemoryFdPropertiesKHR = (PFN_vkGetMemoryFdPropertiesKHR)LoadFunc(Device, "vkGetMemoryFdPropertiesKHR");
#endif /*  defined(VK_KHR_external_memory_fd)  */
#if defined(VK_KHR_external_memory_win32)
    FuncArray->vkGetMemoryWin32HandleKHR = (PFN_vkGetMemoryWin32HandleKHR)LoadFunc(Device, "vkGetMemoryWin32HandleKHR");
    FuncArray->vkGetMemoryWin32HandlePropertiesKHR = (PFN_vkGetMemoryWin32HandlePropertiesKHR)LoadFunc(Device, "vkGetMemoryWin32HandlePropertiesKHR");
#endif /*  defined(VK_KHR_external_memory_win32)  */
#if defined(VK_KHR_external_semaphore_fd)
    FuncArray->vkGetSemaphoreFdKHR = (PFN_vkGetSemaphoreFdKHR)LoadFunc(Device, "vkGetSemaphoreFdKHR");
    FuncArray->vkImportSemaphoreFdKHR = (PFN_vkImportSemaphoreFdKHR)LoadFunc(Device, "vkImportSemaphoreFdKHR");
#endif /*  defined(VK_KHR_external_semaphore_fd)  */
#if defined(VK_KHR_external_semaphore_win32)
    FuncArray->vkGetSemaphoreWin32HandleKHR = (PFN_vkGetSemaphoreWin32HandleKHR)LoadFunc(Device, "vkGetSemaphoreWin32HandleKHR");
    FuncArray->vkImportSemaphoreWin32HandleKHR = (PFN_vkImportSemaphoreWin32HandleKHR)LoadFunc(Device, "vkImportSemaphoreWin32HandleKHR");
#endif /*  defined(VK_KHR_external_semaphore_win32)  */
#if defined(VK_KHR_fragment_shading_rate)
    FuncArray->vkCmdSetFragmentShadingRateKHR = (PFN_vkCmdSetFragmentShadingRateKHR)LoadFunc(Device, "vkCmdSetFragmentShadingRateKHR");
#endif /*  defined(VK_KHR_fragment_shading_rate)  */
#if defined(VK_KHR_get_memory_requirements2)
    FuncArray->vkGetBufferMemoryRequirements2KHR = (PFN_vkGetBufferMemoryRequirements2KHR)LoadFunc(Device, "vkGetBufferMemoryRequirements2KHR");
    FuncArray->vkGetImageMemoryRequirements2KHR = (PFN_vkGetImageMemoryRequirements2KHR)LoadFunc(Device, "vkGetImageMemoryRequirements2KHR");
    FuncArray->vkGetImageSparseMemoryRequirements2KHR = (PFN_vkGetImageSparseMemoryRequirements2KHR)LoadFunc(Device, "vkGetImageSparseMemoryRequirements2KHR");
#endif /*  defined(VK_KHR_get_memory_requirements2)  */
#if defined(VK_KHR_line_rasterization)
    FuncArray->vkCmdSetLineStippleKHR = (PFN_vkCmdSetLineStippleKHR)LoadFunc(Device, "vkCmdSetLineStippleKHR");
#endif /*  defined(VK_KHR_line_rasterization)  */
#if defined(VK_KHR_maintenance1)
    FuncArray->vkTrimCommandPoolKHR = (PFN_vkTrimCommandPoolKHR)LoadFunc(Device, "vkTrimCommandPoolKHR");
#endif /*  defined(VK_KHR_maintenance1)  */
#if defined(VK_KHR_maintenance3)
    FuncArray->vkGetDescriptorSetLayoutSupportKHR = (PFN_vkGetDescriptorSetLayoutSupportKHR)LoadFunc(Device, "vkGetDescriptorSetLayoutSupportKHR");
#endif /*  defined(VK_KHR_maintenance3)  */
#if defined(VK_KHR_maintenance4)
    FuncArray->vkGetDeviceBufferMemoryRequirementsKHR = (PFN_vkGetDeviceBufferMemoryRequirementsKHR)LoadFunc(Device, "vkGetDeviceBufferMemoryRequirementsKHR");
    FuncArray->vkGetDeviceImageMemoryRequirementsKHR = (PFN_vkGetDeviceImageMemoryRequirementsKHR)LoadFunc(Device, "vkGetDeviceImageMemoryRequirementsKHR");
    FuncArray->vkGetDeviceImageSparseMemoryRequirementsKHR = (PFN_vkGetDeviceImageSparseMemoryRequirementsKHR)LoadFunc(Device, "vkGetDeviceImageSparseMemoryRequirementsKHR");
#endif /*  defined(VK_KHR_maintenance4)  */
#if defined(VK_KHR_maintenance5)
    FuncArray->vkCmdBindIndexBuffer2KHR = (PFN_vkCmdBindIndexBuffer2KHR)LoadFunc(Device, "vkCmdBindIndexBuffer2KHR");
    FuncArray->vkGetDeviceImageSubresourceLayoutKHR = (PFN_vkGetDeviceImageSubresourceLayoutKHR)LoadFunc(Device, "vkGetDeviceImageSubresourceLayoutKHR");
    FuncArray->vkGetImageSubresourceLayout2KHR = (PFN_vkGetImageSubresourceLayout2KHR)LoadFunc(Device, "vkGetImageSubresourceLayout2KHR");
    FuncArray->vkGetRenderingAreaGranularityKHR = (PFN_vkGetRenderingAreaGranularityKHR)LoadFunc(Device, "vkGetRenderingAreaGranularityKHR");
#endif /*  defined(VK_KHR_maintenance5)  */
#if defined(VK_KHR_maintenance6)
    FuncArray->vkCmdBindDescriptorSets2KHR = (PFN_vkCmdBindDescriptorSets2KHR)LoadFunc(Device, "vkCmdBindDescriptorSets2KHR");
    FuncArray->vkCmdPushConstants2KHR = (PFN_vkCmdPushConstants2KHR)LoadFunc(Device, "vkCmdPushConstants2KHR");
#endif /*  defined(VK_KHR_maintenance6)  */
#if defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)
    FuncArray->vkCmdPushDescriptorSet2KHR = (PFN_vkCmdPushDescriptorSet2KHR)LoadFunc(Device, "vkCmdPushDescriptorSet2KHR");
    FuncArray->vkCmdPushDescriptorSetWithTemplate2KHR = (PFN_vkCmdPushDescriptorSetWithTemplate2KHR)LoadFunc(Device, "vkCmdPushDescriptorSetWithTemplate2KHR");
#endif /*  defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)  */
#if defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)
    FuncArray->vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = (PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT)LoadFunc(Device, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT");
    FuncArray->vkCmdSetDescriptorBufferOffsets2EXT = (PFN_vkCmdSetDescriptorBufferOffsets2EXT)LoadFunc(Device, "vkCmdSetDescriptorBufferOffsets2EXT");
#endif /*  defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)  */
#if defined(VK_KHR_map_memory2)
    FuncArray->vkMapMemory2KHR = (PFN_vkMapMemory2KHR)LoadFunc(Device, "vkMapMemory2KHR");
    FuncArray->vkUnmapMemory2KHR = (PFN_vkUnmapMemory2KHR)LoadFunc(Device, "vkUnmapMemory2KHR");
#endif /*  defined(VK_KHR_map_memory2)  */
#if defined(VK_KHR_performance_query)
    FuncArray->vkAcquireProfilingLockKHR = (PFN_vkAcquireProfilingLockKHR)LoadFunc(Device, "vkAcquireProfilingLockKHR");
    FuncArray->vkReleaseProfilingLockKHR = (PFN_vkReleaseProfilingLockKHR)LoadFunc(Device, "vkReleaseProfilingLockKHR");
#endif /*  defined(VK_KHR_performance_query)  */
#if defined(VK_KHR_pipeline_executable_properties)
    FuncArray->vkGetPipelineExecutableInternalRepresentationsKHR = (PFN_vkGetPipelineExecutableInternalRepresentationsKHR)LoadFunc(Device, "vkGetPipelineExecutableInternalRepresentationsKHR");
    FuncArray->vkGetPipelineExecutablePropertiesKHR = (PFN_vkGetPipelineExecutablePropertiesKHR)LoadFunc(Device, "vkGetPipelineExecutablePropertiesKHR");
    FuncArray->vkGetPipelineExecutableStatisticsKHR = (PFN_vkGetPipelineExecutableStatisticsKHR)LoadFunc(Device, "vkGetPipelineExecutableStatisticsKHR");
#endif /*  defined(VK_KHR_pipeline_executable_properties)  */
#if defined(VK_KHR_present_wait)
    FuncArray->vkWaitForPresentKHR = (PFN_vkWaitForPresentKHR)LoadFunc(Device, "vkWaitForPresentKHR");
#endif /*  defined(VK_KHR_present_wait)  */
#if defined(VK_KHR_push_descriptor)
    FuncArray->vkCmdPushDescriptorSetKHR = (PFN_vkCmdPushDescriptorSetKHR)LoadFunc(Device, "vkCmdPushDescriptorSetKHR");
#endif /*  defined(VK_KHR_push_descriptor)  */
#if defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)
    FuncArray->vkCmdTraceRaysIndirect2KHR = (PFN_vkCmdTraceRaysIndirect2KHR)LoadFunc(Device, "vkCmdTraceRaysIndirect2KHR");
#endif /*  defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)  */
#if defined(VK_KHR_ray_tracing_pipeline)
    FuncArray->vkCmdSetRayTracingPipelineStackSizeKHR = (PFN_vkCmdSetRayTracingPipelineStackSizeKHR)LoadFunc(Device, "vkCmdSetRayTracingPipelineStackSizeKHR");
    FuncArray->vkCmdTraceRaysIndirectKHR = (PFN_vkCmdTraceRaysIndirectKHR)LoadFunc(Device, "vkCmdTraceRaysIndirectKHR");
    FuncArray->vkCmdTraceRaysKHR = (PFN_vkCmdTraceRaysKHR)LoadFunc(Device, "vkCmdTraceRaysKHR");
    FuncArray->vkCreateRayTracingPipelinesKHR = (PFN_vkCreateRayTracingPipelinesKHR)LoadFunc(Device, "vkCreateRayTracingPipelinesKHR");
    FuncArray->vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = (PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR)LoadFunc(Device, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR");
    FuncArray->vkGetRayTracingShaderGroupHandlesKHR = (PFN_vkGetRayTracingShaderGroupHandlesKHR)LoadFunc(Device, "vkGetRayTracingShaderGroupHandlesKHR");
    FuncArray->vkGetRayTracingShaderGroupStackSizeKHR = (PFN_vkGetRayTracingShaderGroupStackSizeKHR)LoadFunc(Device, "vkGetRayTracingShaderGroupStackSizeKHR");
#endif /*  defined(VK_KHR_ray_tracing_pipeline)  */
#if defined(VK_KHR_sampler_ycbcr_conversion)
    FuncArray->vkCreateSamplerYcbcrConversionKHR = (PFN_vkCreateSamplerYcbcrConversionKHR)LoadFunc(Device, "vkCreateSamplerYcbcrConversionKHR");
    FuncArray->vkDestroySamplerYcbcrConversionKHR = (PFN_vkDestroySamplerYcbcrConversionKHR)LoadFunc(Device, "vkDestroySamplerYcbcrConversionKHR");
#endif /*  defined(VK_KHR_sampler_ycbcr_conversion)  */
#if defined(VK_KHR_shared_presentable_image)
    FuncArray->vkGetSwapchainStatusKHR = (PFN_vkGetSwapchainStatusKHR)LoadFunc(Device, "vkGetSwapchainStatusKHR");
#endif /*  defined(VK_KHR_shared_presentable_image)  */
#if defined(VK_KHR_swapchain)
    FuncArray->vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)LoadFunc(Device, "vkAcquireNextImageKHR");
    FuncArray->vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)LoadFunc(Device, "vkCreateSwapchainKHR");
    FuncArray->vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR)LoadFunc(Device, "vkDestroySwapchainKHR");
    FuncArray->vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)LoadFunc(Device, "vkGetSwapchainImagesKHR");
    FuncArray->vkQueuePresentKHR = (PFN_vkQueuePresentKHR)LoadFunc(Device, "vkQueuePresentKHR");
#endif /*  defined(VK_KHR_swapchain)  */
#if defined(VK_KHR_synchronization2)
    FuncArray->vkCmdPipelineBarrier2KHR = (PFN_vkCmdPipelineBarrier2KHR)LoadFunc(Device, "vkCmdPipelineBarrier2KHR");
    FuncArray->vkCmdResetEvent2KHR = (PFN_vkCmdResetEvent2KHR)LoadFunc(Device, "vkCmdResetEvent2KHR");
    FuncArray->vkCmdSetEvent2KHR = (PFN_vkCmdSetEvent2KHR)LoadFunc(Device, "vkCmdSetEvent2KHR");
    FuncArray->vkCmdWaitEvents2KHR = (PFN_vkCmdWaitEvents2KHR)LoadFunc(Device, "vkCmdWaitEvents2KHR");
    FuncArray->vkCmdWriteTimestamp2KHR = (PFN_vkCmdWriteTimestamp2KHR)LoadFunc(Device, "vkCmdWriteTimestamp2KHR");
    FuncArray->vkQueueSubmit2KHR = (PFN_vkQueueSubmit2KHR)LoadFunc(Device, "vkQueueSubmit2KHR");
#endif /*  defined(VK_KHR_synchronization2)  */
#if defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)
    FuncArray->vkCmdWriteBufferMarker2AMD = (PFN_vkCmdWriteBufferMarker2AMD)LoadFunc(Device, "vkCmdWriteBufferMarker2AMD");
#endif /*  defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)  */
#if defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)
    FuncArray->vkGetQueueCheckpointData2NV = (PFN_vkGetQueueCheckpointData2NV)LoadFunc(Device, "vkGetQueueCheckpointData2NV");
#endif /*  defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)  */
#if defined(VK_KHR_timeline_semaphore)
    FuncArray->vkGetSemaphoreCounterValueKHR = (PFN_vkGetSemaphoreCounterValueKHR)LoadFunc(Device, "vkGetSemaphoreCounterValueKHR");
    FuncArray->vkSignalSemaphoreKHR = (PFN_vkSignalSemaphoreKHR)LoadFunc(Device, "vkSignalSemaphoreKHR");
    FuncArray->vkWaitSemaphoresKHR = (PFN_vkWaitSemaphoresKHR)LoadFunc(Device, "vkWaitSemaphoresKHR");
#endif /*  defined(VK_KHR_timeline_semaphore)  */
#if defined(VK_KHR_video_decode_queue)
    FuncArray->vkCmdDecodeVideoKHR = (PFN_vkCmdDecodeVideoKHR)LoadFunc(Device, "vkCmdDecodeVideoKHR");
#endif /*  defined(VK_KHR_video_decode_queue)  */
#if defined(VK_KHR_video_encode_queue)
    FuncArray->vkCmdEncodeVideoKHR = (PFN_vkCmdEncodeVideoKHR)LoadFunc(Device, "vkCmdEncodeVideoKHR");
    FuncArray->vkGetEncodedVideoSessionParametersKHR = (PFN_vkGetEncodedVideoSessionParametersKHR)LoadFunc(Device, "vkGetEncodedVideoSessionParametersKHR");
#endif /*  defined(VK_KHR_video_encode_queue)  */
#if defined(VK_KHR_video_queue)
    FuncArray->vkBindVideoSessionMemoryKHR = (PFN_vkBindVideoSessionMemoryKHR)LoadFunc(Device, "vkBindVideoSessionMemoryKHR");
    FuncArray->vkCmdBeginVideoCodingKHR = (PFN_vkCmdBeginVideoCodingKHR)LoadFunc(Device, "vkCmdBeginVideoCodingKHR");
    FuncArray->vkCmdControlVideoCodingKHR = (PFN_vkCmdControlVideoCodingKHR)LoadFunc(Device, "vkCmdControlVideoCodingKHR");
    FuncArray->vkCmdEndVideoCodingKHR = (PFN_vkCmdEndVideoCodingKHR)LoadFunc(Device, "vkCmdEndVideoCodingKHR");
    FuncArray->vkCreateVideoSessionKHR = (PFN_vkCreateVideoSessionKHR)LoadFunc(Device, "vkCreateVideoSessionKHR");
    FuncArray->vkCreateVideoSessionParametersKHR = (PFN_vkCreateVideoSessionParametersKHR)LoadFunc(Device, "vkCreateVideoSessionParametersKHR");
    FuncArray->vkDestroyVideoSessionKHR = (PFN_vkDestroyVideoSessionKHR)LoadFunc(Device, "vkDestroyVideoSessionKHR");
    FuncArray->vkDestroyVideoSessionParametersKHR = (PFN_vkDestroyVideoSessionParametersKHR)LoadFunc(Device, "vkDestroyVideoSessionParametersKHR");
    FuncArray->vkGetVideoSessionMemoryRequirementsKHR = (PFN_vkGetVideoSessionMemoryRequirementsKHR)LoadFunc(Device, "vkGetVideoSessionMemoryRequirementsKHR");
    FuncArray->vkUpdateVideoSessionParametersKHR = (PFN_vkUpdateVideoSessionParametersKHR)LoadFunc(Device, "vkUpdateVideoSessionParametersKHR");
#endif /*  defined(VK_KHR_video_queue)  */
#if defined(VK_NVX_binary_import)
    FuncArray->vkCmdCuLaunchKernelNVX = (PFN_vkCmdCuLaunchKernelNVX)LoadFunc(Device, "vkCmdCuLaunchKernelNVX");
    FuncArray->vkCreateCuFunctionNVX = (PFN_vkCreateCuFunctionNVX)LoadFunc(Device, "vkCreateCuFunctionNVX");
    FuncArray->vkCreateCuModuleNVX = (PFN_vkCreateCuModuleNVX)LoadFunc(Device, "vkCreateCuModuleNVX");
    FuncArray->vkDestroyCuFunctionNVX = (PFN_vkDestroyCuFunctionNVX)LoadFunc(Device, "vkDestroyCuFunctionNVX");
    FuncArray->vkDestroyCuModuleNVX = (PFN_vkDestroyCuModuleNVX)LoadFunc(Device, "vkDestroyCuModuleNVX");
#endif /*  defined(VK_NVX_binary_import)  */
#if defined(VK_NVX_image_view_handle)
    FuncArray->vkGetImageViewAddressNVX = (PFN_vkGetImageViewAddressNVX)LoadFunc(Device, "vkGetImageViewAddressNVX");
    FuncArray->vkGetImageViewHandleNVX = (PFN_vkGetImageViewHandleNVX)LoadFunc(Device, "vkGetImageViewHandleNVX");
#endif /*  defined(VK_NVX_image_view_handle)  */
#if defined(VK_NV_clip_space_w_scaling)
    FuncArray->vkCmdSetViewportWScalingNV = (PFN_vkCmdSetViewportWScalingNV)LoadFunc(Device, "vkCmdSetViewportWScalingNV");
#endif /*  defined(VK_NV_clip_space_w_scaling)  */
#if defined(VK_NV_copy_memory_indirect)
    FuncArray->vkCmdCopyMemoryIndirectNV = (PFN_vkCmdCopyMemoryIndirectNV)LoadFunc(Device, "vkCmdCopyMemoryIndirectNV");
    FuncArray->vkCmdCopyMemoryToImageIndirectNV = (PFN_vkCmdCopyMemoryToImageIndirectNV)LoadFunc(Device, "vkCmdCopyMemoryToImageIndirectNV");
#endif /*  defined(VK_NV_copy_memory_indirect)  */
#if defined(VK_NV_cuda_kernel_launch)
    FuncArray->vkCmdCudaLaunchKernelNV = (PFN_vkCmdCudaLaunchKernelNV)LoadFunc(Device, "vkCmdCudaLaunchKernelNV");
    FuncArray->vkCreateCudaFunctionNV = (PFN_vkCreateCudaFunctionNV)LoadFunc(Device, "vkCreateCudaFunctionNV");
    FuncArray->vkCreateCudaModuleNV = (PFN_vkCreateCudaModuleNV)LoadFunc(Device, "vkCreateCudaModuleNV");
    FuncArray->vkDestroyCudaFunctionNV = (PFN_vkDestroyCudaFunctionNV)LoadFunc(Device, "vkDestroyCudaFunctionNV");
    FuncArray->vkDestroyCudaModuleNV = (PFN_vkDestroyCudaModuleNV)LoadFunc(Device, "vkDestroyCudaModuleNV");
    FuncArray->vkGetCudaModuleCacheNV = (PFN_vkGetCudaModuleCacheNV)LoadFunc(Device, "vkGetCudaModuleCacheNV");
#endif /*  defined(VK_NV_cuda_kernel_launch)  */
#if defined(VK_NV_device_diagnostic_checkpoints)
    FuncArray->vkCmdSetCheckpointNV = (PFN_vkCmdSetCheckpointNV)LoadFunc(Device, "vkCmdSetCheckpointNV");
    FuncArray->vkGetQueueCheckpointDataNV = (PFN_vkGetQueueCheckpointDataNV)LoadFunc(Device, "vkGetQueueCheckpointDataNV");
#endif /*  defined(VK_NV_device_diagnostic_checkpoints)  */
#if defined(VK_NV_device_generated_commands)
    FuncArray->vkCmdBindPipelineShaderGroupNV = (PFN_vkCmdBindPipelineShaderGroupNV)LoadFunc(Device, "vkCmdBindPipelineShaderGroupNV");
    FuncArray->vkCmdExecuteGeneratedCommandsNV = (PFN_vkCmdExecuteGeneratedCommandsNV)LoadFunc(Device, "vkCmdExecuteGeneratedCommandsNV");
    FuncArray->vkCmdPreprocessGeneratedCommandsNV = (PFN_vkCmdPreprocessGeneratedCommandsNV)LoadFunc(Device, "vkCmdPreprocessGeneratedCommandsNV");
    FuncArray->vkCreateIndirectCommandsLayoutNV = (PFN_vkCreateIndirectCommandsLayoutNV)LoadFunc(Device, "vkCreateIndirectCommandsLayoutNV");
    FuncArray->vkDestroyIndirectCommandsLayoutNV = (PFN_vkDestroyIndirectCommandsLayoutNV)LoadFunc(Device, "vkDestroyIndirectCommandsLayoutNV");
    FuncArray->vkGetGeneratedCommandsMemoryRequirementsNV = (PFN_vkGetGeneratedCommandsMemoryRequirementsNV)LoadFunc(Device, "vkGetGeneratedCommandsMemoryRequirementsNV");
#endif /*  defined(VK_NV_device_generated_commands)  */
#if defined(VK_NV_device_generated_commands_compute)
    FuncArray->vkCmdUpdatePipelineIndirectBufferNV = (PFN_vkCmdUpdatePipelineIndirectBufferNV)LoadFunc(Device, "vkCmdUpdatePipelineIndirectBufferNV");
    FuncArray->vkGetPipelineIndirectDeviceAddressNV = (PFN_vkGetPipelineIndirectDeviceAddressNV)LoadFunc(Device, "vkGetPipelineIndirectDeviceAddressNV");
    FuncArray->vkGetPipelineIndirectMemoryRequirementsNV = (PFN_vkGetPipelineIndirectMemoryRequirementsNV)LoadFunc(Device, "vkGetPipelineIndirectMemoryRequirementsNV");
#endif /*  defined(VK_NV_device_generated_commands_compute)  */
#if defined(VK_NV_external_memory_rdma)
    FuncArray->vkGetMemoryRemoteAddressNV = (PFN_vkGetMemoryRemoteAddressNV)LoadFunc(Device, "vkGetMemoryRemoteAddressNV");
#endif /*  defined(VK_NV_external_memory_rdma)  */
#if defined(VK_NV_external_memory_win32)
    FuncArray->vkGetMemoryWin32HandleNV = (PFN_vkGetMemoryWin32HandleNV)LoadFunc(Device, "vkGetMemoryWin32HandleNV");
#endif /*  defined(VK_NV_external_memory_win32)  */
#if defined(VK_NV_fragment_shading_rate_enums)
    FuncArray->vkCmdSetFragmentShadingRateEnumNV = (PFN_vkCmdSetFragmentShadingRateEnumNV)LoadFunc(Device, "vkCmdSetFragmentShadingRateEnumNV");
#endif /*  defined(VK_NV_fragment_shading_rate_enums)  */
#if defined(VK_NV_low_latency2)
    FuncArray->vkGetLatencyTimingsNV = (PFN_vkGetLatencyTimingsNV)LoadFunc(Device, "vkGetLatencyTimingsNV");
    FuncArray->vkLatencySleepNV = (PFN_vkLatencySleepNV)LoadFunc(Device, "vkLatencySleepNV");
    FuncArray->vkQueueNotifyOutOfBandNV = (PFN_vkQueueNotifyOutOfBandNV)LoadFunc(Device, "vkQueueNotifyOutOfBandNV");
    FuncArray->vkSetLatencyMarkerNV = (PFN_vkSetLatencyMarkerNV)LoadFunc(Device, "vkSetLatencyMarkerNV");
    FuncArray->vkSetLatencySleepModeNV = (PFN_vkSetLatencySleepModeNV)LoadFunc(Device, "vkSetLatencySleepModeNV");
#endif /*  defined(VK_NV_low_latency2)  */
#if defined(VK_NV_memory_decompression)
    FuncArray->vkCmdDecompressMemoryIndirectCountNV = (PFN_vkCmdDecompressMemoryIndirectCountNV)LoadFunc(Device, "vkCmdDecompressMemoryIndirectCountNV");
    FuncArray->vkCmdDecompressMemoryNV = (PFN_vkCmdDecompressMemoryNV)LoadFunc(Device, "vkCmdDecompressMemoryNV");
#endif /*  defined(VK_NV_memory_decompression)  */
#if defined(VK_NV_mesh_shader)
    FuncArray->vkCmdDrawMeshTasksIndirectCountNV = (PFN_vkCmdDrawMeshTasksIndirectCountNV)LoadFunc(Device, "vkCmdDrawMeshTasksIndirectCountNV");
    FuncArray->vkCmdDrawMeshTasksIndirectNV = (PFN_vkCmdDrawMeshTasksIndirectNV)LoadFunc(Device, "vkCmdDrawMeshTasksIndirectNV");
    FuncArray->vkCmdDrawMeshTasksNV = (PFN_vkCmdDrawMeshTasksNV)LoadFunc(Device, "vkCmdDrawMeshTasksNV");
#endif /*  defined(VK_NV_mesh_shader)  */
#if defined(VK_NV_optical_flow)
    FuncArray->vkBindOpticalFlowSessionImageNV = (PFN_vkBindOpticalFlowSessionImageNV)LoadFunc(Device, "vkBindOpticalFlowSessionImageNV");
    FuncArray->vkCmdOpticalFlowExecuteNV = (PFN_vkCmdOpticalFlowExecuteNV)LoadFunc(Device, "vkCmdOpticalFlowExecuteNV");
    FuncArray->vkCreateOpticalFlowSessionNV = (PFN_vkCreateOpticalFlowSessionNV)LoadFunc(Device, "vkCreateOpticalFlowSessionNV");
    FuncArray->vkDestroyOpticalFlowSessionNV = (PFN_vkDestroyOpticalFlowSessionNV)LoadFunc(Device, "vkDestroyOpticalFlowSessionNV");
#endif /*  defined(VK_NV_optical_flow)  */
#if defined(VK_NV_ray_tracing)
    FuncArray->vkBindAccelerationStructureMemoryNV = (PFN_vkBindAccelerationStructureMemoryNV)LoadFunc(Device, "vkBindAccelerationStructureMemoryNV");
    FuncArray->vkCmdBuildAccelerationStructureNV = (PFN_vkCmdBuildAccelerationStructureNV)LoadFunc(Device, "vkCmdBuildAccelerationStructureNV");
    FuncArray->vkCmdCopyAccelerationStructureNV = (PFN_vkCmdCopyAccelerationStructureNV)LoadFunc(Device, "vkCmdCopyAccelerationStructureNV");
    FuncArray->vkCmdTraceRaysNV = (PFN_vkCmdTraceRaysNV)LoadFunc(Device, "vkCmdTraceRaysNV");
    FuncArray->vkCmdWriteAccelerationStructuresPropertiesNV = (PFN_vkCmdWriteAccelerationStructuresPropertiesNV)LoadFunc(Device, "vkCmdWriteAccelerationStructuresPropertiesNV");
    FuncArray->vkCompileDeferredNV = (PFN_vkCompileDeferredNV)LoadFunc(Device, "vkCompileDeferredNV");
    FuncArray->vkCreateAccelerationStructureNV = (PFN_vkCreateAccelerationStructureNV)LoadFunc(Device, "vkCreateAccelerationStructureNV");
    FuncArray->vkCreateRayTracingPipelinesNV = (PFN_vkCreateRayTracingPipelinesNV)LoadFunc(Device, "vkCreateRayTracingPipelinesNV");
    FuncArray->vkDestroyAccelerationStructureNV = (PFN_vkDestroyAccelerationStructureNV)LoadFunc(Device, "vkDestroyAccelerationStructureNV");
    FuncArray->vkGetAccelerationStructureHandleNV = (PFN_vkGetAccelerationStructureHandleNV)LoadFunc(Device, "vkGetAccelerationStructureHandleNV");
    FuncArray->vkGetAccelerationStructureMemoryRequirementsNV = (PFN_vkGetAccelerationStructureMemoryRequirementsNV)LoadFunc(Device, "vkGetAccelerationStructureMemoryRequirementsNV");
    FuncArray->vkGetRayTracingShaderGroupHandlesNV = (PFN_vkGetRayTracingShaderGroupHandlesNV)LoadFunc(Device, "vkGetRayTracingShaderGroupHandlesNV");
#endif /*  defined(VK_NV_ray_tracing)  */
#if defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2
    FuncArray->vkCmdSetExclusiveScissorEnableNV = (PFN_vkCmdSetExclusiveScissorEnableNV)LoadFunc(Device, "vkCmdSetExclusiveScissorEnableNV");
#endif /*  defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2  */
#if defined(VK_NV_scissor_exclusive)
    FuncArray->vkCmdSetExclusiveScissorNV = (PFN_vkCmdSetExclusiveScissorNV)LoadFunc(Device, "vkCmdSetExclusiveScissorNV");
#endif /*  defined(VK_NV_scissor_exclusive)  */
#if defined(VK_NV_shading_rate_image)
    FuncArray->vkCmdBindShadingRateImageNV = (PFN_vkCmdBindShadingRateImageNV)LoadFunc(Device, "vkCmdBindShadingRateImageNV");
    FuncArray->vkCmdSetCoarseSampleOrderNV = (PFN_vkCmdSetCoarseSampleOrderNV)LoadFunc(Device, "vkCmdSetCoarseSampleOrderNV");
    FuncArray->vkCmdSetViewportShadingRatePaletteNV = (PFN_vkCmdSetViewportShadingRatePaletteNV)LoadFunc(Device, "vkCmdSetViewportShadingRatePaletteNV");
#endif /*  defined(VK_NV_shading_rate_image)  */
#if defined(VK_QCOM_tile_properties)
    FuncArray->vkGetDynamicRenderingTilePropertiesQCOM = (PFN_vkGetDynamicRenderingTilePropertiesQCOM)LoadFunc(Device, "vkGetDynamicRenderingTilePropertiesQCOM");
    FuncArray->vkGetFramebufferTilePropertiesQCOM = (PFN_vkGetFramebufferTilePropertiesQCOM)LoadFunc(Device, "vkGetFramebufferTilePropertiesQCOM");
#endif /*  defined(VK_QCOM_tile_properties)  */
#if defined(VK_QNX_external_memory_screen_buffer)
    FuncArray->vkGetScreenBufferPropertiesQNX = (PFN_vkGetScreenBufferPropertiesQNX)LoadFunc(Device, "vkGetScreenBufferPropertiesQNX");
#endif /*  defined(VK_QNX_external_memory_screen_buffer)  */
#if defined(VK_VALVE_descriptor_set_host_mapping)
    FuncArray->vkGetDescriptorSetHostMappingVALVE = (PFN_vkGetDescriptorSetHostMappingVALVE)LoadFunc(Device, "vkGetDescriptorSetHostMappingVALVE");
    FuncArray->vkGetDescriptorSetLayoutHostMappingInfoVALVE = (PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE)LoadFunc(Device, "vkGetDescriptorSetLayoutHostMappingInfoVALVE");
#endif /*  defined(VK_VALVE_descriptor_set_host_mapping)  */
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    FuncArray->vkCmdBindVertexBuffers2EXT = (PFN_vkCmdBindVertexBuffers2EXT)LoadFunc(Device, "vkCmdBindVertexBuffers2EXT");
    FuncArray->vkCmdSetCullModeEXT = (PFN_vkCmdSetCullModeEXT)LoadFunc(Device, "vkCmdSetCullModeEXT");
    FuncArray->vkCmdSetDepthBoundsTestEnableEXT = (PFN_vkCmdSetDepthBoundsTestEnableEXT)LoadFunc(Device, "vkCmdSetDepthBoundsTestEnableEXT");
    FuncArray->vkCmdSetDepthCompareOpEXT = (PFN_vkCmdSetDepthCompareOpEXT)LoadFunc(Device, "vkCmdSetDepthCompareOpEXT");
    FuncArray->vkCmdSetDepthTestEnableEXT = (PFN_vkCmdSetDepthTestEnableEXT)LoadFunc(Device, "vkCmdSetDepthTestEnableEXT");
    FuncArray->vkCmdSetDepthWriteEnableEXT = (PFN_vkCmdSetDepthWriteEnableEXT)LoadFunc(Device, "vkCmdSetDepthWriteEnableEXT");
    FuncArray->vkCmdSetFrontFaceEXT = (PFN_vkCmdSetFrontFaceEXT)LoadFunc(Device, "vkCmdSetFrontFaceEXT");
    FuncArray->vkCmdSetPrimitiveTopologyEXT = (PFN_vkCmdSetPrimitiveTopologyEXT)LoadFunc(Device, "vkCmdSetPrimitiveTopologyEXT");
    FuncArray->vkCmdSetScissorWithCountEXT = (PFN_vkCmdSetScissorWithCountEXT)LoadFunc(Device, "vkCmdSetScissorWithCountEXT");
    FuncArray->vkCmdSetStencilOpEXT = (PFN_vkCmdSetStencilOpEXT)LoadFunc(Device, "vkCmdSetStencilOpEXT");
    FuncArray->vkCmdSetStencilTestEnableEXT = (PFN_vkCmdSetStencilTestEnableEXT)LoadFunc(Device, "vkCmdSetStencilTestEnableEXT");
    FuncArray->vkCmdSetViewportWithCountEXT = (PFN_vkCmdSetViewportWithCountEXT)LoadFunc(Device, "vkCmdSetViewportWithCountEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
    FuncArray->vkCmdSetDepthBiasEnableEXT = (PFN_vkCmdSetDepthBiasEnableEXT)LoadFunc(Device, "vkCmdSetDepthBiasEnableEXT");
    FuncArray->vkCmdSetLogicOpEXT = (PFN_vkCmdSetLogicOpEXT)LoadFunc(Device, "vkCmdSetLogicOpEXT");
    FuncArray->vkCmdSetPatchControlPointsEXT = (PFN_vkCmdSetPatchControlPointsEXT)LoadFunc(Device, "vkCmdSetPatchControlPointsEXT");
    FuncArray->vkCmdSetPrimitiveRestartEnableEXT = (PFN_vkCmdSetPrimitiveRestartEnableEXT)LoadFunc(Device, "vkCmdSetPrimitiveRestartEnableEXT");
    FuncArray->vkCmdSetRasterizerDiscardEnableEXT = (PFN_vkCmdSetRasterizerDiscardEnableEXT)LoadFunc(Device, "vkCmdSetRasterizerDiscardEnableEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    FuncArray->vkCmdSetAlphaToCoverageEnableEXT = (PFN_vkCmdSetAlphaToCoverageEnableEXT)LoadFunc(Device, "vkCmdSetAlphaToCoverageEnableEXT");
    FuncArray->vkCmdSetAlphaToOneEnableEXT = (PFN_vkCmdSetAlphaToOneEnableEXT)LoadFunc(Device, "vkCmdSetAlphaToOneEnableEXT");
    FuncArray->vkCmdSetColorBlendEnableEXT = (PFN_vkCmdSetColorBlendEnableEXT)LoadFunc(Device, "vkCmdSetColorBlendEnableEXT");
    FuncArray->vkCmdSetColorBlendEquationEXT = (PFN_vkCmdSetColorBlendEquationEXT)LoadFunc(Device, "vkCmdSetColorBlendEquationEXT");
    FuncArray->vkCmdSetColorWriteMaskEXT = (PFN_vkCmdSetColorWriteMaskEXT)LoadFunc(Device, "vkCmdSetColorWriteMaskEXT");
    FuncArray->vkCmdSetDepthClampEnableEXT = (PFN_vkCmdSetDepthClampEnableEXT)LoadFunc(Device, "vkCmdSetDepthClampEnableEXT");
    FuncArray->vkCmdSetLogicOpEnableEXT = (PFN_vkCmdSetLogicOpEnableEXT)LoadFunc(Device, "vkCmdSetLogicOpEnableEXT");
    FuncArray->vkCmdSetPolygonModeEXT = (PFN_vkCmdSetPolygonModeEXT)LoadFunc(Device, "vkCmdSetPolygonModeEXT");
    FuncArray->vkCmdSetRasterizationSamplesEXT = (PFN_vkCmdSetRasterizationSamplesEXT)LoadFunc(Device, "vkCmdSetRasterizationSamplesEXT");
    FuncArray->vkCmdSetSampleMaskEXT = (PFN_vkCmdSetSampleMaskEXT)LoadFunc(Device, "vkCmdSetSampleMaskEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1))) || (defined(VK_EXT_shader_object))
    FuncArray->vkCmdSetTessellationDomainOriginEXT = (PFN_vkCmdSetTessellationDomainOriginEXT)LoadFunc(Device, "vkCmdSetTessellationDomainOriginEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1))) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))
    FuncArray->vkCmdSetRasterizationStreamEXT = (PFN_vkCmdSetRasterizationStreamEXT)LoadFunc(Device, "vkCmdSetRasterizationStreamEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))
    FuncArray->vkCmdSetConservativeRasterizationModeEXT = (PFN_vkCmdSetConservativeRasterizationModeEXT)LoadFunc(Device, "vkCmdSetConservativeRasterizationModeEXT");
    FuncArray->vkCmdSetExtraPrimitiveOverestimationSizeEXT = (PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT)LoadFunc(Device, "vkCmdSetExtraPrimitiveOverestimationSizeEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))
    FuncArray->vkCmdSetDepthClipEnableEXT = (PFN_vkCmdSetDepthClipEnableEXT)LoadFunc(Device, "vkCmdSetDepthClipEnableEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))
    FuncArray->vkCmdSetSampleLocationsEnableEXT = (PFN_vkCmdSetSampleLocationsEnableEXT)LoadFunc(Device, "vkCmdSetSampleLocationsEnableEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))
    FuncArray->vkCmdSetColorBlendAdvancedEXT = (PFN_vkCmdSetColorBlendAdvancedEXT)LoadFunc(Device, "vkCmdSetColorBlendAdvancedEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))
    FuncArray->vkCmdSetProvokingVertexModeEXT = (PFN_vkCmdSetProvokingVertexModeEXT)LoadFunc(Device, "vkCmdSetProvokingVertexModeEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))
    FuncArray->vkCmdSetLineRasterizationModeEXT = (PFN_vkCmdSetLineRasterizationModeEXT)LoadFunc(Device, "vkCmdSetLineRasterizationModeEXT");
    FuncArray->vkCmdSetLineStippleEnableEXT = (PFN_vkCmdSetLineStippleEnableEXT)LoadFunc(Device, "vkCmdSetLineStippleEnableEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))
    FuncArray->vkCmdSetDepthClipNegativeOneToOneEXT = (PFN_vkCmdSetDepthClipNegativeOneToOneEXT)LoadFunc(Device, "vkCmdSetDepthClipNegativeOneToOneEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling)) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))
    FuncArray->vkCmdSetViewportWScalingEnableNV = (PFN_vkCmdSetViewportWScalingEnableNV)LoadFunc(Device, "vkCmdSetViewportWScalingEnableNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling)) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle)) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))
    FuncArray->vkCmdSetViewportSwizzleNV = (PFN_vkCmdSetViewportSwizzleNV)LoadFunc(Device, "vkCmdSetViewportSwizzleNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle)) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color)) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))
    FuncArray->vkCmdSetCoverageToColorEnableNV = (PFN_vkCmdSetCoverageToColorEnableNV)LoadFunc(Device, "vkCmdSetCoverageToColorEnableNV");
    FuncArray->vkCmdSetCoverageToColorLocationNV = (PFN_vkCmdSetCoverageToColorLocationNV)LoadFunc(Device, "vkCmdSetCoverageToColorLocationNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color)) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples)) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))
    FuncArray->vkCmdSetCoverageModulationModeNV = (PFN_vkCmdSetCoverageModulationModeNV)LoadFunc(Device, "vkCmdSetCoverageModulationModeNV");
    FuncArray->vkCmdSetCoverageModulationTableEnableNV = (PFN_vkCmdSetCoverageModulationTableEnableNV)LoadFunc(Device, "vkCmdSetCoverageModulationTableEnableNV");
    FuncArray->vkCmdSetCoverageModulationTableNV = (PFN_vkCmdSetCoverageModulationTableNV)LoadFunc(Device, "vkCmdSetCoverageModulationTableNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples)) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image)) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))
    FuncArray->vkCmdSetShadingRateImageEnableNV = (PFN_vkCmdSetShadingRateImageEnableNV)LoadFunc(Device, "vkCmdSetShadingRateImageEnableNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image)) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test)) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))
    FuncArray->vkCmdSetRepresentativeFragmentTestEnableNV = (PFN_vkCmdSetRepresentativeFragmentTestEnableNV)LoadFunc(Device, "vkCmdSetRepresentativeFragmentTestEnableNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test)) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode)) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))
    FuncArray->vkCmdSetCoverageReductionModeNV = (PFN_vkCmdSetCoverageReductionModeNV)LoadFunc(Device, "vkCmdSetCoverageReductionModeNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode)) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))  */
#if (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
    FuncArray->vkGetDeviceGroupSurfacePresentModes2EXT = (PFN_vkGetDeviceGroupSurfacePresentModes2EXT)LoadFunc(Device, "vkGetDeviceGroupSurfacePresentModes2EXT");
#endif /*  (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))  */
#if (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))
    FuncArray->vkGetImageSubresourceLayout2EXT = (PFN_vkGetImageSubresourceLayout2EXT)LoadFunc(Device, "vkGetImageSubresourceLayout2EXT");
#endif /*  (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))  */
#if (defined(VK_EXT_shader_object)) || (defined(VK_EXT_vertex_input_dynamic_state))
    FuncArray->vkCmdSetVertexInputEXT = (PFN_vkCmdSetVertexInputEXT)LoadFunc(Device, "vkCmdSetVertexInputEXT");
#endif /*  (defined(VK_EXT_shader_object)) || (defined(VK_EXT_vertex_input_dynamic_state))  */
#if (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
    FuncArray->vkCmdPushDescriptorSetWithTemplateKHR = (PFN_vkCmdPushDescriptorSetWithTemplateKHR)LoadFunc(Device, "vkCmdPushDescriptorSetWithTemplateKHR");
#endif /*  (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))  */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
    FuncArray->vkGetDeviceGroupPresentCapabilitiesKHR = (PFN_vkGetDeviceGroupPresentCapabilitiesKHR)LoadFunc(Device, "vkGetDeviceGroupPresentCapabilitiesKHR");
    FuncArray->vkGetDeviceGroupSurfacePresentModesKHR = (PFN_vkGetDeviceGroupSurfacePresentModesKHR)LoadFunc(Device, "vkGetDeviceGroupSurfacePresentModesKHR");
#endif /*  (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))  */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
    FuncArray->vkAcquireNextImage2KHR = (PFN_vkAcquireNextImage2KHR)LoadFunc(Device, "vkAcquireNextImage2KHR");
#endif /*  (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))  */

}

//SECTION(V): VK_PROTOTYPES_IMPL
#if defined(VK_VERSION_1_0)
PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
PFN_vkAllocateMemory vkAllocateMemory;
PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
PFN_vkBindBufferMemory vkBindBufferMemory;
PFN_vkBindImageMemory vkBindImageMemory;
PFN_vkCmdBeginQuery vkCmdBeginQuery;
PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;
PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;
PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
PFN_vkCmdBindPipeline vkCmdBindPipeline;
PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;
PFN_vkCmdBlitImage vkCmdBlitImage;
PFN_vkCmdClearAttachments vkCmdClearAttachments;
PFN_vkCmdClearColorImage vkCmdClearColorImage;
PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage;
PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;
PFN_vkCmdCopyImage vkCmdCopyImage;
PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer;
PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults;
PFN_vkCmdDispatch vkCmdDispatch;
PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect;
PFN_vkCmdDraw vkCmdDraw;
PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect;
PFN_vkCmdDrawIndirect vkCmdDrawIndirect;
PFN_vkCmdEndQuery vkCmdEndQuery;
PFN_vkCmdEndRenderPass vkCmdEndRenderPass;
PFN_vkCmdExecuteCommands vkCmdExecuteCommands;
PFN_vkCmdFillBuffer vkCmdFillBuffer;
PFN_vkCmdNextSubpass vkCmdNextSubpass;
PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;
PFN_vkCmdPushConstants vkCmdPushConstants;
PFN_vkCmdResetEvent vkCmdResetEvent;
PFN_vkCmdResetQueryPool vkCmdResetQueryPool;
PFN_vkCmdResolveImage vkCmdResolveImage;
PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants;
PFN_vkCmdSetDepthBias vkCmdSetDepthBias;
PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds;
PFN_vkCmdSetEvent vkCmdSetEvent;
PFN_vkCmdSetLineWidth vkCmdSetLineWidth;
PFN_vkCmdSetScissor vkCmdSetScissor;
PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask;
PFN_vkCmdSetStencilReference vkCmdSetStencilReference;
PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask;
PFN_vkCmdSetViewport vkCmdSetViewport;
PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer;
PFN_vkCmdWaitEvents vkCmdWaitEvents;
PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp;
PFN_vkCreateBuffer vkCreateBuffer;
PFN_vkCreateBufferView vkCreateBufferView;
PFN_vkCreateCommandPool vkCreateCommandPool;
PFN_vkCreateComputePipelines vkCreateComputePipelines;
PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
PFN_vkCreateDevice vkCreateDevice;
PFN_vkCreateEvent vkCreateEvent;
PFN_vkCreateFence vkCreateFence;
PFN_vkCreateFramebuffer vkCreateFramebuffer;
PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
PFN_vkCreateImage vkCreateImage;
PFN_vkCreateImageView vkCreateImageView;
PFN_vkCreateInstance vkCreateInstance;
PFN_vkCreatePipelineCache vkCreatePipelineCache;
PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
PFN_vkCreateQueryPool vkCreateQueryPool;
PFN_vkCreateRenderPass vkCreateRenderPass;
PFN_vkCreateSampler vkCreateSampler;
PFN_vkCreateSemaphore vkCreateSemaphore;
PFN_vkCreateShaderModule vkCreateShaderModule;
PFN_vkDestroyBuffer vkDestroyBuffer;
PFN_vkDestroyBufferView vkDestroyBufferView;
PFN_vkDestroyCommandPool vkDestroyCommandPool;
PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;
PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;
PFN_vkDestroyDevice vkDestroyDevice;
PFN_vkDestroyEvent vkDestroyEvent;
PFN_vkDestroyFence vkDestroyFence;
PFN_vkDestroyFramebuffer vkDestroyFramebuffer;
PFN_vkDestroyImage vkDestroyImage;
PFN_vkDestroyImageView vkDestroyImageView;
PFN_vkDestroyInstance vkDestroyInstance;
PFN_vkDestroyPipeline vkDestroyPipeline;
PFN_vkDestroyPipelineCache vkDestroyPipelineCache;
PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;
PFN_vkDestroyQueryPool vkDestroyQueryPool;
PFN_vkDestroyRenderPass vkDestroyRenderPass;
PFN_vkDestroySampler vkDestroySampler;
PFN_vkDestroySemaphore vkDestroySemaphore;
PFN_vkDestroyShaderModule vkDestroyShaderModule;
PFN_vkDeviceWaitIdle vkDeviceWaitIdle;
PFN_vkEndCommandBuffer vkEndCommandBuffer;
PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties;
PFN_vkEnumerateDeviceLayerProperties vkEnumerateDeviceLayerProperties;
PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
PFN_vkFreeCommandBuffers vkFreeCommandBuffers;
PFN_vkFreeDescriptorSets vkFreeDescriptorSets;
PFN_vkFreeMemory vkFreeMemory;
PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment;
PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
PFN_vkGetDeviceQueue vkGetDeviceQueue;
PFN_vkGetEventStatus vkGetEventStatus;
PFN_vkGetFenceStatus vkGetFenceStatus;
PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements;
PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout;
PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties;
PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties;
PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties;
PFN_vkGetPipelineCacheData vkGetPipelineCacheData;
PFN_vkGetQueryPoolResults vkGetQueryPoolResults;
PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity;
PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;
PFN_vkMapMemory vkMapMemory;
PFN_vkMergePipelineCaches vkMergePipelineCaches;
PFN_vkQueueBindSparse vkQueueBindSparse;
PFN_vkQueueSubmit vkQueueSubmit;
PFN_vkQueueWaitIdle vkQueueWaitIdle;
PFN_vkResetCommandBuffer vkResetCommandBuffer;
PFN_vkResetCommandPool vkResetCommandPool;
PFN_vkResetDescriptorPool vkResetDescriptorPool;
PFN_vkResetEvent vkResetEvent;
PFN_vkResetFences vkResetFences;
PFN_vkSetEvent vkSetEvent;
PFN_vkUnmapMemory vkUnmapMemory;
PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;
PFN_vkWaitForFences vkWaitForFences;
#endif /*  defined(VK_VERSION_1_0)  */
#if defined(VK_VERSION_1_1)
PFN_vkBindBufferMemory2 vkBindBufferMemory2;
PFN_vkBindImageMemory2 vkBindImageMemory2;
PFN_vkCmdDispatchBase vkCmdDispatchBase;
PFN_vkCmdSetDeviceMask vkCmdSetDeviceMask;
PFN_vkCreateDescriptorUpdateTemplate vkCreateDescriptorUpdateTemplate;
PFN_vkCreateSamplerYcbcrConversion vkCreateSamplerYcbcrConversion;
PFN_vkDestroyDescriptorUpdateTemplate vkDestroyDescriptorUpdateTemplate;
PFN_vkDestroySamplerYcbcrConversion vkDestroySamplerYcbcrConversion;
PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion;
PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups;
PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2;
PFN_vkGetDescriptorSetLayoutSupport vkGetDescriptorSetLayoutSupport;
PFN_vkGetDeviceGroupPeerMemoryFeatures vkGetDeviceGroupPeerMemoryFeatures;
PFN_vkGetDeviceQueue2 vkGetDeviceQueue2;
PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2;
PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2;
PFN_vkGetPhysicalDeviceExternalBufferProperties vkGetPhysicalDeviceExternalBufferProperties;
PFN_vkGetPhysicalDeviceExternalFenceProperties vkGetPhysicalDeviceExternalFenceProperties;
PFN_vkGetPhysicalDeviceExternalSemaphoreProperties vkGetPhysicalDeviceExternalSemaphoreProperties;
PFN_vkGetPhysicalDeviceFeatures2 vkGetPhysicalDeviceFeatures2;
PFN_vkGetPhysicalDeviceFormatProperties2 vkGetPhysicalDeviceFormatProperties2;
PFN_vkGetPhysicalDeviceImageFormatProperties2 vkGetPhysicalDeviceImageFormatProperties2;
PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2;
PFN_vkGetPhysicalDeviceProperties2 vkGetPhysicalDeviceProperties2;
PFN_vkGetPhysicalDeviceQueueFamilyProperties2 vkGetPhysicalDeviceQueueFamilyProperties2;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2;
PFN_vkTrimCommandPool vkTrimCommandPool;
PFN_vkUpdateDescriptorSetWithTemplate vkUpdateDescriptorSetWithTemplate;
#endif /*  defined(VK_VERSION_1_1)  */
#if defined(VK_VERSION_1_2)
PFN_vkCmdBeginRenderPass2 vkCmdBeginRenderPass2;
PFN_vkCmdDrawIndexedIndirectCount vkCmdDrawIndexedIndirectCount;
PFN_vkCmdDrawIndirectCount vkCmdDrawIndirectCount;
PFN_vkCmdEndRenderPass2 vkCmdEndRenderPass2;
PFN_vkCmdNextSubpass2 vkCmdNextSubpass2;
PFN_vkCreateRenderPass2 vkCreateRenderPass2;
PFN_vkGetBufferDeviceAddress vkGetBufferDeviceAddress;
PFN_vkGetBufferOpaqueCaptureAddress vkGetBufferOpaqueCaptureAddress;
PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress;
PFN_vkGetSemaphoreCounterValue vkGetSemaphoreCounterValue;
PFN_vkResetQueryPool vkResetQueryPool;
PFN_vkSignalSemaphore vkSignalSemaphore;
PFN_vkWaitSemaphores vkWaitSemaphores;
#endif /*  defined(VK_VERSION_1_2)  */
#if defined(VK_VERSION_1_3)
PFN_vkCmdBeginRendering vkCmdBeginRendering;
PFN_vkCmdBindVertexBuffers2 vkCmdBindVertexBuffers2;
PFN_vkCmdBlitImage2 vkCmdBlitImage2;
PFN_vkCmdCopyBuffer2 vkCmdCopyBuffer2;
PFN_vkCmdCopyBufferToImage2 vkCmdCopyBufferToImage2;
PFN_vkCmdCopyImage2 vkCmdCopyImage2;
PFN_vkCmdCopyImageToBuffer2 vkCmdCopyImageToBuffer2;
PFN_vkCmdEndRendering vkCmdEndRendering;
PFN_vkCmdPipelineBarrier2 vkCmdPipelineBarrier2;
PFN_vkCmdResetEvent2 vkCmdResetEvent2;
PFN_vkCmdResolveImage2 vkCmdResolveImage2;
PFN_vkCmdSetCullMode vkCmdSetCullMode;
PFN_vkCmdSetDepthBiasEnable vkCmdSetDepthBiasEnable;
PFN_vkCmdSetDepthBoundsTestEnable vkCmdSetDepthBoundsTestEnable;
PFN_vkCmdSetDepthCompareOp vkCmdSetDepthCompareOp;
PFN_vkCmdSetDepthTestEnable vkCmdSetDepthTestEnable;
PFN_vkCmdSetDepthWriteEnable vkCmdSetDepthWriteEnable;
PFN_vkCmdSetEvent2 vkCmdSetEvent2;
PFN_vkCmdSetFrontFace vkCmdSetFrontFace;
PFN_vkCmdSetPrimitiveRestartEnable vkCmdSetPrimitiveRestartEnable;
PFN_vkCmdSetPrimitiveTopology vkCmdSetPrimitiveTopology;
PFN_vkCmdSetRasterizerDiscardEnable vkCmdSetRasterizerDiscardEnable;
PFN_vkCmdSetScissorWithCount vkCmdSetScissorWithCount;
PFN_vkCmdSetStencilOp vkCmdSetStencilOp;
PFN_vkCmdSetStencilTestEnable vkCmdSetStencilTestEnable;
PFN_vkCmdSetViewportWithCount vkCmdSetViewportWithCount;
PFN_vkCmdWaitEvents2 vkCmdWaitEvents2;
PFN_vkCmdWriteTimestamp2 vkCmdWriteTimestamp2;
PFN_vkCreatePrivateDataSlot vkCreatePrivateDataSlot;
PFN_vkDestroyPrivateDataSlot vkDestroyPrivateDataSlot;
PFN_vkGetDeviceBufferMemoryRequirements vkGetDeviceBufferMemoryRequirements;
PFN_vkGetDeviceImageMemoryRequirements vkGetDeviceImageMemoryRequirements;
PFN_vkGetDeviceImageSparseMemoryRequirements vkGetDeviceImageSparseMemoryRequirements;
PFN_vkGetPhysicalDeviceToolProperties vkGetPhysicalDeviceToolProperties;
PFN_vkGetPrivateData vkGetPrivateData;
PFN_vkQueueSubmit2 vkQueueSubmit2;
PFN_vkSetPrivateData vkSetPrivateData;
#endif /*  defined(VK_VERSION_1_3)  */
#if defined(VK_AMDX_shader_enqueue)
PFN_vkCmdDispatchGraphAMDX vkCmdDispatchGraphAMDX;
PFN_vkCmdDispatchGraphIndirectAMDX vkCmdDispatchGraphIndirectAMDX;
PFN_vkCmdDispatchGraphIndirectCountAMDX vkCmdDispatchGraphIndirectCountAMDX;
PFN_vkCmdInitializeGraphScratchMemoryAMDX vkCmdInitializeGraphScratchMemoryAMDX;
PFN_vkCreateExecutionGraphPipelinesAMDX vkCreateExecutionGraphPipelinesAMDX;
PFN_vkGetExecutionGraphPipelineNodeIndexAMDX vkGetExecutionGraphPipelineNodeIndexAMDX;
PFN_vkGetExecutionGraphPipelineScratchSizeAMDX vkGetExecutionGraphPipelineScratchSizeAMDX;
#endif /*  defined(VK_AMDX_shader_enqueue)  */
#if defined(VK_AMD_anti_lag)
PFN_vkAntiLagUpdateAMD vkAntiLagUpdateAMD;
#endif /*  defined(VK_AMD_anti_lag)  */
#if defined(VK_AMD_buffer_marker)
PFN_vkCmdWriteBufferMarkerAMD vkCmdWriteBufferMarkerAMD;
#endif /*  defined(VK_AMD_buffer_marker)  */
#if defined(VK_AMD_display_native_hdr)
PFN_vkSetLocalDimmingAMD vkSetLocalDimmingAMD;
#endif /*  defined(VK_AMD_display_native_hdr)  */
#if defined(VK_AMD_draw_indirect_count)
PFN_vkCmdDrawIndexedIndirectCountAMD vkCmdDrawIndexedIndirectCountAMD;
PFN_vkCmdDrawIndirectCountAMD vkCmdDrawIndirectCountAMD;
#endif /*  defined(VK_AMD_draw_indirect_count)  */
#if defined(VK_AMD_shader_info)
PFN_vkGetShaderInfoAMD vkGetShaderInfoAMD;
#endif /*  defined(VK_AMD_shader_info)  */
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
PFN_vkGetAndroidHardwareBufferPropertiesANDROID vkGetAndroidHardwareBufferPropertiesANDROID;
PFN_vkGetMemoryAndroidHardwareBufferANDROID vkGetMemoryAndroidHardwareBufferANDROID;
#endif /*  defined(VK_ANDROID_external_memory_android_hardware_buffer)  */
#if defined(VK_EXT_acquire_drm_display)
PFN_vkAcquireDrmDisplayEXT vkAcquireDrmDisplayEXT;
PFN_vkGetDrmDisplayEXT vkGetDrmDisplayEXT;
#endif /*  defined(VK_EXT_acquire_drm_display)  */
#if defined(VK_EXT_acquire_xlib_display)
PFN_vkAcquireXlibDisplayEXT vkAcquireXlibDisplayEXT;
PFN_vkGetRandROutputDisplayEXT vkGetRandROutputDisplayEXT;
#endif /*  defined(VK_EXT_acquire_xlib_display)  */
#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT vkCmdSetAttachmentFeedbackLoopEnableEXT;
#endif /*  defined(VK_EXT_attachment_feedback_loop_dynamic_state)  */
#if defined(VK_EXT_buffer_device_address)
PFN_vkGetBufferDeviceAddressEXT vkGetBufferDeviceAddressEXT;
#endif /*  defined(VK_EXT_buffer_device_address)  */
#if defined(VK_EXT_calibrated_timestamps)
PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT;
PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT;
#endif /*  defined(VK_EXT_calibrated_timestamps)  */
#if defined(VK_EXT_color_write_enable)
PFN_vkCmdSetColorWriteEnableEXT vkCmdSetColorWriteEnableEXT;
#endif /*  defined(VK_EXT_color_write_enable)  */
#if defined(VK_EXT_conditional_rendering)
PFN_vkCmdBeginConditionalRenderingEXT vkCmdBeginConditionalRenderingEXT;
PFN_vkCmdEndConditionalRenderingEXT vkCmdEndConditionalRenderingEXT;
#endif /*  defined(VK_EXT_conditional_rendering)  */
#if defined(VK_EXT_debug_marker)
PFN_vkCmdDebugMarkerBeginEXT vkCmdDebugMarkerBeginEXT;
PFN_vkCmdDebugMarkerEndEXT vkCmdDebugMarkerEndEXT;
PFN_vkCmdDebugMarkerInsertEXT vkCmdDebugMarkerInsertEXT;
PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectNameEXT;
PFN_vkDebugMarkerSetObjectTagEXT vkDebugMarkerSetObjectTagEXT;
#endif /*  defined(VK_EXT_debug_marker)  */
#if defined(VK_EXT_debug_report)
PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT;
PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
#endif /*  defined(VK_EXT_debug_report)  */
#if defined(VK_EXT_debug_utils)
PFN_vkCmdBeginDebugUtilsLabelEXT vkCmdBeginDebugUtilsLabelEXT;
PFN_vkCmdEndDebugUtilsLabelEXT vkCmdEndDebugUtilsLabelEXT;
PFN_vkCmdInsertDebugUtilsLabelEXT vkCmdInsertDebugUtilsLabelEXT;
PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
PFN_vkQueueBeginDebugUtilsLabelEXT vkQueueBeginDebugUtilsLabelEXT;
PFN_vkQueueEndDebugUtilsLabelEXT vkQueueEndDebugUtilsLabelEXT;
PFN_vkQueueInsertDebugUtilsLabelEXT vkQueueInsertDebugUtilsLabelEXT;
PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT;
PFN_vkSetDebugUtilsObjectTagEXT vkSetDebugUtilsObjectTagEXT;
PFN_vkSubmitDebugUtilsMessageEXT vkSubmitDebugUtilsMessageEXT;
#endif /*  defined(VK_EXT_debug_utils)  */
#if defined(VK_EXT_depth_bias_control)
PFN_vkCmdSetDepthBias2EXT vkCmdSetDepthBias2EXT;
#endif /*  defined(VK_EXT_depth_bias_control)  */
#if defined(VK_EXT_descriptor_buffer)
PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT vkCmdBindDescriptorBufferEmbeddedSamplersEXT;
PFN_vkCmdBindDescriptorBuffersEXT vkCmdBindDescriptorBuffersEXT;
PFN_vkCmdSetDescriptorBufferOffsetsEXT vkCmdSetDescriptorBufferOffsetsEXT;
PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT vkGetBufferOpaqueCaptureDescriptorDataEXT;
PFN_vkGetDescriptorEXT vkGetDescriptorEXT;
PFN_vkGetDescriptorSetLayoutBindingOffsetEXT vkGetDescriptorSetLayoutBindingOffsetEXT;
PFN_vkGetDescriptorSetLayoutSizeEXT vkGetDescriptorSetLayoutSizeEXT;
PFN_vkGetImageOpaqueCaptureDescriptorDataEXT vkGetImageOpaqueCaptureDescriptorDataEXT;
PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT vkGetImageViewOpaqueCaptureDescriptorDataEXT;
PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT vkGetSamplerOpaqueCaptureDescriptorDataEXT;
#endif /*  defined(VK_EXT_descriptor_buffer)  */
#if defined(VK_EXT_descriptor_buffer) && (defined(VK_KHR_acceleration_structure) || defined(VK_NV_ray_tracing))
PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT;
#endif /*  defined(VK_EXT_descriptor_buffer) && (defined(VK_KHR_acceleration_structure) || defined(VK_NV_ray_tracing))  */
#if defined(VK_EXT_device_fault)
PFN_vkGetDeviceFaultInfoEXT vkGetDeviceFaultInfoEXT;
#endif /*  defined(VK_EXT_device_fault)  */
#if defined(VK_EXT_direct_mode_display)
PFN_vkReleaseDisplayEXT vkReleaseDisplayEXT;
#endif /*  defined(VK_EXT_direct_mode_display)  */
#if defined(VK_EXT_directfb_surface)
PFN_vkCreateDirectFBSurfaceEXT vkCreateDirectFBSurfaceEXT;
PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT vkGetPhysicalDeviceDirectFBPresentationSupportEXT;
#endif /*  defined(VK_EXT_directfb_surface)  */
#if defined(VK_EXT_discard_rectangles)
PFN_vkCmdSetDiscardRectangleEXT vkCmdSetDiscardRectangleEXT;
#endif /*  defined(VK_EXT_discard_rectangles)  */
#if defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2
PFN_vkCmdSetDiscardRectangleEnableEXT vkCmdSetDiscardRectangleEnableEXT;
PFN_vkCmdSetDiscardRectangleModeEXT vkCmdSetDiscardRectangleModeEXT;
#endif /*  defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2  */
#if defined(VK_EXT_display_control)
PFN_vkDisplayPowerControlEXT vkDisplayPowerControlEXT;
PFN_vkGetSwapchainCounterEXT vkGetSwapchainCounterEXT;
PFN_vkRegisterDeviceEventEXT vkRegisterDeviceEventEXT;
PFN_vkRegisterDisplayEventEXT vkRegisterDisplayEventEXT;
#endif /*  defined(VK_EXT_display_control)  */
#if defined(VK_EXT_display_surface_counter)
PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT vkGetPhysicalDeviceSurfaceCapabilities2EXT;
#endif /*  defined(VK_EXT_display_surface_counter)  */
#if defined(VK_EXT_external_memory_host)
PFN_vkGetMemoryHostPointerPropertiesEXT vkGetMemoryHostPointerPropertiesEXT;
#endif /*  defined(VK_EXT_external_memory_host)  */
#if defined(VK_EXT_full_screen_exclusive)
PFN_vkAcquireFullScreenExclusiveModeEXT vkAcquireFullScreenExclusiveModeEXT;
PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT vkGetPhysicalDeviceSurfacePresentModes2EXT;
PFN_vkReleaseFullScreenExclusiveModeEXT vkReleaseFullScreenExclusiveModeEXT;
#endif /*  defined(VK_EXT_full_screen_exclusive)  */
#if defined(VK_EXT_hdr_metadata)
PFN_vkSetHdrMetadataEXT vkSetHdrMetadataEXT;
#endif /*  defined(VK_EXT_hdr_metadata)  */
#if defined(VK_EXT_headless_surface)
PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT;
#endif /*  defined(VK_EXT_headless_surface)  */
#if defined(VK_EXT_host_image_copy)
PFN_vkCopyImageToImageEXT vkCopyImageToImageEXT;
PFN_vkCopyImageToMemoryEXT vkCopyImageToMemoryEXT;
PFN_vkCopyMemoryToImageEXT vkCopyMemoryToImageEXT;
PFN_vkTransitionImageLayoutEXT vkTransitionImageLayoutEXT;
#endif /*  defined(VK_EXT_host_image_copy)  */
#if defined(VK_EXT_host_query_reset)
PFN_vkResetQueryPoolEXT vkResetQueryPoolEXT;
#endif /*  defined(VK_EXT_host_query_reset)  */
#if defined(VK_EXT_image_drm_format_modifier)
PFN_vkGetImageDrmFormatModifierPropertiesEXT vkGetImageDrmFormatModifierPropertiesEXT;
#endif /*  defined(VK_EXT_image_drm_format_modifier)  */
#if defined(VK_EXT_line_rasterization)
PFN_vkCmdSetLineStippleEXT vkCmdSetLineStippleEXT;
#endif /*  defined(VK_EXT_line_rasterization)  */
#if defined(VK_EXT_mesh_shader)
PFN_vkCmdDrawMeshTasksEXT vkCmdDrawMeshTasksEXT;
PFN_vkCmdDrawMeshTasksIndirectCountEXT vkCmdDrawMeshTasksIndirectCountEXT;
PFN_vkCmdDrawMeshTasksIndirectEXT vkCmdDrawMeshTasksIndirectEXT;
#endif /*  defined(VK_EXT_mesh_shader)  */
#if defined(VK_EXT_metal_objects)
PFN_vkExportMetalObjectsEXT vkExportMetalObjectsEXT;
#endif /*  defined(VK_EXT_metal_objects)  */
#if defined(VK_EXT_metal_surface)
PFN_vkCreateMetalSurfaceEXT vkCreateMetalSurfaceEXT;
#endif /*  defined(VK_EXT_metal_surface)  */
#if defined(VK_EXT_multi_draw)
PFN_vkCmdDrawMultiEXT vkCmdDrawMultiEXT;
PFN_vkCmdDrawMultiIndexedEXT vkCmdDrawMultiIndexedEXT;
#endif /*  defined(VK_EXT_multi_draw)  */
#if defined(VK_EXT_opacity_micromap)
PFN_vkBuildMicromapsEXT vkBuildMicromapsEXT;
PFN_vkCmdBuildMicromapsEXT vkCmdBuildMicromapsEXT;
PFN_vkCmdCopyMemoryToMicromapEXT vkCmdCopyMemoryToMicromapEXT;
PFN_vkCmdCopyMicromapEXT vkCmdCopyMicromapEXT;
PFN_vkCmdCopyMicromapToMemoryEXT vkCmdCopyMicromapToMemoryEXT;
PFN_vkCmdWriteMicromapsPropertiesEXT vkCmdWriteMicromapsPropertiesEXT;
PFN_vkCopyMemoryToMicromapEXT vkCopyMemoryToMicromapEXT;
PFN_vkCopyMicromapEXT vkCopyMicromapEXT;
PFN_vkCopyMicromapToMemoryEXT vkCopyMicromapToMemoryEXT;
PFN_vkCreateMicromapEXT vkCreateMicromapEXT;
PFN_vkDestroyMicromapEXT vkDestroyMicromapEXT;
PFN_vkGetDeviceMicromapCompatibilityEXT vkGetDeviceMicromapCompatibilityEXT;
PFN_vkGetMicromapBuildSizesEXT vkGetMicromapBuildSizesEXT;
PFN_vkWriteMicromapsPropertiesEXT vkWriteMicromapsPropertiesEXT;
#endif /*  defined(VK_EXT_opacity_micromap)  */
#if defined(VK_EXT_pageable_device_local_memory)
PFN_vkSetDeviceMemoryPriorityEXT vkSetDeviceMemoryPriorityEXT;
#endif /*  defined(VK_EXT_pageable_device_local_memory)  */
#if defined(VK_EXT_pipeline_properties)
PFN_vkGetPipelinePropertiesEXT vkGetPipelinePropertiesEXT;
#endif /*  defined(VK_EXT_pipeline_properties)  */
#if defined(VK_EXT_private_data)
PFN_vkCreatePrivateDataSlotEXT vkCreatePrivateDataSlotEXT;
PFN_vkDestroyPrivateDataSlotEXT vkDestroyPrivateDataSlotEXT;
PFN_vkGetPrivateDataEXT vkGetPrivateDataEXT;
PFN_vkSetPrivateDataEXT vkSetPrivateDataEXT;
#endif /*  defined(VK_EXT_private_data)  */
#if defined(VK_EXT_sample_locations)
PFN_vkCmdSetSampleLocationsEXT vkCmdSetSampleLocationsEXT;
PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT vkGetPhysicalDeviceMultisamplePropertiesEXT;
#endif /*  defined(VK_EXT_sample_locations)  */
#if defined(VK_EXT_shader_module_identifier)
PFN_vkGetShaderModuleCreateInfoIdentifierEXT vkGetShaderModuleCreateInfoIdentifierEXT;
PFN_vkGetShaderModuleIdentifierEXT vkGetShaderModuleIdentifierEXT;
#endif /*  defined(VK_EXT_shader_module_identifier)  */
#if defined(VK_EXT_shader_object)
PFN_vkCmdBindShadersEXT vkCmdBindShadersEXT;
PFN_vkCreateShadersEXT vkCreateShadersEXT;
PFN_vkDestroyShaderEXT vkDestroyShaderEXT;
PFN_vkGetShaderBinaryDataEXT vkGetShaderBinaryDataEXT;
#endif /*  defined(VK_EXT_shader_object)  */
#if defined(VK_EXT_swapchain_maintenance1)
PFN_vkReleaseSwapchainImagesEXT vkReleaseSwapchainImagesEXT;
#endif /*  defined(VK_EXT_swapchain_maintenance1)  */
#if defined(VK_EXT_tooling_info)
PFN_vkGetPhysicalDeviceToolPropertiesEXT vkGetPhysicalDeviceToolPropertiesEXT;
#endif /*  defined(VK_EXT_tooling_info)  */
#if defined(VK_EXT_transform_feedback)
PFN_vkCmdBeginQueryIndexedEXT vkCmdBeginQueryIndexedEXT;
PFN_vkCmdBeginTransformFeedbackEXT vkCmdBeginTransformFeedbackEXT;
PFN_vkCmdBindTransformFeedbackBuffersEXT vkCmdBindTransformFeedbackBuffersEXT;
PFN_vkCmdDrawIndirectByteCountEXT vkCmdDrawIndirectByteCountEXT;
PFN_vkCmdEndQueryIndexedEXT vkCmdEndQueryIndexedEXT;
PFN_vkCmdEndTransformFeedbackEXT vkCmdEndTransformFeedbackEXT;
#endif /*  defined(VK_EXT_transform_feedback)  */
#if defined(VK_EXT_validation_cache)
PFN_vkCreateValidationCacheEXT vkCreateValidationCacheEXT;
PFN_vkDestroyValidationCacheEXT vkDestroyValidationCacheEXT;
PFN_vkGetValidationCacheDataEXT vkGetValidationCacheDataEXT;
PFN_vkMergeValidationCachesEXT vkMergeValidationCachesEXT;
#endif /*  defined(VK_EXT_validation_cache)  */
#if defined(VK_FUCHSIA_buffer_collection)
PFN_vkCreateBufferCollectionFUCHSIA vkCreateBufferCollectionFUCHSIA;
PFN_vkDestroyBufferCollectionFUCHSIA vkDestroyBufferCollectionFUCHSIA;
PFN_vkGetBufferCollectionPropertiesFUCHSIA vkGetBufferCollectionPropertiesFUCHSIA;
PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA vkSetBufferCollectionBufferConstraintsFUCHSIA;
PFN_vkSetBufferCollectionImageConstraintsFUCHSIA vkSetBufferCollectionImageConstraintsFUCHSIA;
#endif /*  defined(VK_FUCHSIA_buffer_collection)  */
#if defined(VK_FUCHSIA_external_memory)
PFN_vkGetMemoryZirconHandleFUCHSIA vkGetMemoryZirconHandleFUCHSIA;
PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA vkGetMemoryZirconHandlePropertiesFUCHSIA;
#endif /*  defined(VK_FUCHSIA_external_memory)  */
#if defined(VK_FUCHSIA_external_semaphore)
PFN_vkGetSemaphoreZirconHandleFUCHSIA vkGetSemaphoreZirconHandleFUCHSIA;
PFN_vkImportSemaphoreZirconHandleFUCHSIA vkImportSemaphoreZirconHandleFUCHSIA;
#endif /*  defined(VK_FUCHSIA_external_semaphore)  */
#if defined(VK_FUCHSIA_imagepipe_surface)
PFN_vkCreateImagePipeSurfaceFUCHSIA vkCreateImagePipeSurfaceFUCHSIA;
#endif /*  defined(VK_FUCHSIA_imagepipe_surface)  */
#if defined(VK_GGP_stream_descriptor_surface)
PFN_vkCreateStreamDescriptorSurfaceGGP vkCreateStreamDescriptorSurfaceGGP;
#endif /*  defined(VK_GGP_stream_descriptor_surface)  */
#if defined(VK_GOOGLE_display_timing)
PFN_vkGetPastPresentationTimingGOOGLE vkGetPastPresentationTimingGOOGLE;
PFN_vkGetRefreshCycleDurationGOOGLE vkGetRefreshCycleDurationGOOGLE;
#endif /*  defined(VK_GOOGLE_display_timing)  */
#if defined(VK_HUAWEI_cluster_culling_shader)
PFN_vkCmdDrawClusterHUAWEI vkCmdDrawClusterHUAWEI;
PFN_vkCmdDrawClusterIndirectHUAWEI vkCmdDrawClusterIndirectHUAWEI;
#endif /*  defined(VK_HUAWEI_cluster_culling_shader)  */
#if defined(VK_HUAWEI_invocation_mask)
PFN_vkCmdBindInvocationMaskHUAWEI vkCmdBindInvocationMaskHUAWEI;
#endif /*  defined(VK_HUAWEI_invocation_mask)  */
#if defined(VK_HUAWEI_subpass_shading)
PFN_vkCmdSubpassShadingHUAWEI vkCmdSubpassShadingHUAWEI;
PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI;
#endif /*  defined(VK_HUAWEI_subpass_shading)  */
#if defined(VK_INTEL_performance_query)
PFN_vkAcquirePerformanceConfigurationINTEL vkAcquirePerformanceConfigurationINTEL;
PFN_vkCmdSetPerformanceMarkerINTEL vkCmdSetPerformanceMarkerINTEL;
PFN_vkCmdSetPerformanceOverrideINTEL vkCmdSetPerformanceOverrideINTEL;
PFN_vkCmdSetPerformanceStreamMarkerINTEL vkCmdSetPerformanceStreamMarkerINTEL;
PFN_vkGetPerformanceParameterINTEL vkGetPerformanceParameterINTEL;
PFN_vkInitializePerformanceApiINTEL vkInitializePerformanceApiINTEL;
PFN_vkQueueSetPerformanceConfigurationINTEL vkQueueSetPerformanceConfigurationINTEL;
PFN_vkReleasePerformanceConfigurationINTEL vkReleasePerformanceConfigurationINTEL;
PFN_vkUninitializePerformanceApiINTEL vkUninitializePerformanceApiINTEL;
#endif /*  defined(VK_INTEL_performance_query)  */
#if defined(VK_KHR_acceleration_structure)
PFN_vkBuildAccelerationStructuresKHR vkBuildAccelerationStructuresKHR;
PFN_vkCmdBuildAccelerationStructuresIndirectKHR vkCmdBuildAccelerationStructuresIndirectKHR;
PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR;
PFN_vkCmdCopyAccelerationStructureKHR vkCmdCopyAccelerationStructureKHR;
PFN_vkCmdCopyAccelerationStructureToMemoryKHR vkCmdCopyAccelerationStructureToMemoryKHR;
PFN_vkCmdCopyMemoryToAccelerationStructureKHR vkCmdCopyMemoryToAccelerationStructureKHR;
PFN_vkCmdWriteAccelerationStructuresPropertiesKHR vkCmdWriteAccelerationStructuresPropertiesKHR;
PFN_vkCopyAccelerationStructureKHR vkCopyAccelerationStructureKHR;
PFN_vkCopyAccelerationStructureToMemoryKHR vkCopyAccelerationStructureToMemoryKHR;
PFN_vkCopyMemoryToAccelerationStructureKHR vkCopyMemoryToAccelerationStructureKHR;
PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR;
PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR;
PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
PFN_vkGetDeviceAccelerationStructureCompatibilityKHR vkGetDeviceAccelerationStructureCompatibilityKHR;
PFN_vkWriteAccelerationStructuresPropertiesKHR vkWriteAccelerationStructuresPropertiesKHR;
#endif /*  defined(VK_KHR_acceleration_structure)  */
#if defined(VK_KHR_android_surface)
PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
#endif /*  defined(VK_KHR_android_surface)  */
#if defined(VK_KHR_bind_memory2)
PFN_vkBindBufferMemory2KHR vkBindBufferMemory2KHR;
PFN_vkBindImageMemory2KHR vkBindImageMemory2KHR;
#endif /*  defined(VK_KHR_bind_memory2)  */
#if defined(VK_KHR_buffer_device_address)
PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR;
PFN_vkGetBufferOpaqueCaptureAddressKHR vkGetBufferOpaqueCaptureAddressKHR;
PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR vkGetDeviceMemoryOpaqueCaptureAddressKHR;
#endif /*  defined(VK_KHR_buffer_device_address)  */
#if defined(VK_KHR_calibrated_timestamps)
PFN_vkGetCalibratedTimestampsKHR vkGetCalibratedTimestampsKHR;
PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR vkGetPhysicalDeviceCalibrateableTimeDomainsKHR;
#endif /*  defined(VK_KHR_calibrated_timestamps)  */
#if defined(VK_KHR_cooperative_matrix)
PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR;
#endif /*  defined(VK_KHR_cooperative_matrix)  */
#if defined(VK_KHR_copy_commands2)
PFN_vkCmdBlitImage2KHR vkCmdBlitImage2KHR;
PFN_vkCmdCopyBuffer2KHR vkCmdCopyBuffer2KHR;
PFN_vkCmdCopyBufferToImage2KHR vkCmdCopyBufferToImage2KHR;
PFN_vkCmdCopyImage2KHR vkCmdCopyImage2KHR;
PFN_vkCmdCopyImageToBuffer2KHR vkCmdCopyImageToBuffer2KHR;
PFN_vkCmdResolveImage2KHR vkCmdResolveImage2KHR;
#endif /*  defined(VK_KHR_copy_commands2)  */
#if defined(VK_KHR_create_renderpass2)
PFN_vkCmdBeginRenderPass2KHR vkCmdBeginRenderPass2KHR;
PFN_vkCmdEndRenderPass2KHR vkCmdEndRenderPass2KHR;
PFN_vkCmdNextSubpass2KHR vkCmdNextSubpass2KHR;
PFN_vkCreateRenderPass2KHR vkCreateRenderPass2KHR;
#endif /*  defined(VK_KHR_create_renderpass2)  */
#if defined(VK_KHR_deferred_host_operations)
PFN_vkCreateDeferredOperationKHR vkCreateDeferredOperationKHR;
PFN_vkDeferredOperationJoinKHR vkDeferredOperationJoinKHR;
PFN_vkDestroyDeferredOperationKHR vkDestroyDeferredOperationKHR;
PFN_vkGetDeferredOperationMaxConcurrencyKHR vkGetDeferredOperationMaxConcurrencyKHR;
PFN_vkGetDeferredOperationResultKHR vkGetDeferredOperationResultKHR;
#endif /*  defined(VK_KHR_deferred_host_operations)  */
#if defined(VK_KHR_descriptor_update_template)
PFN_vkCreateDescriptorUpdateTemplateKHR vkCreateDescriptorUpdateTemplateKHR;
PFN_vkDestroyDescriptorUpdateTemplateKHR vkDestroyDescriptorUpdateTemplateKHR;
PFN_vkUpdateDescriptorSetWithTemplateKHR vkUpdateDescriptorSetWithTemplateKHR;
#endif /*  defined(VK_KHR_descriptor_update_template)  */
#if defined(VK_KHR_device_group)
PFN_vkCmdDispatchBaseKHR vkCmdDispatchBaseKHR;
PFN_vkCmdSetDeviceMaskKHR vkCmdSetDeviceMaskKHR;
PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR vkGetDeviceGroupPeerMemoryFeaturesKHR;
#endif /*  defined(VK_KHR_device_group)  */
#if defined(VK_KHR_device_group_creation)
PFN_vkEnumeratePhysicalDeviceGroupsKHR vkEnumeratePhysicalDeviceGroupsKHR;
#endif /*  defined(VK_KHR_device_group_creation)  */
#if defined(VK_KHR_display)
PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR;
PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR;
PFN_vkGetDisplayModePropertiesKHR vkGetDisplayModePropertiesKHR;
PFN_vkGetDisplayPlaneCapabilitiesKHR vkGetDisplayPlaneCapabilitiesKHR;
PFN_vkGetDisplayPlaneSupportedDisplaysKHR vkGetDisplayPlaneSupportedDisplaysKHR;
PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
PFN_vkGetPhysicalDeviceDisplayPropertiesKHR vkGetPhysicalDeviceDisplayPropertiesKHR;
#endif /*  defined(VK_KHR_display)  */
#if defined(VK_KHR_display_swapchain)
PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR;
#endif /*  defined(VK_KHR_display_swapchain)  */
#if defined(VK_KHR_draw_indirect_count)
PFN_vkCmdDrawIndexedIndirectCountKHR vkCmdDrawIndexedIndirectCountKHR;
PFN_vkCmdDrawIndirectCountKHR vkCmdDrawIndirectCountKHR;
#endif /*  defined(VK_KHR_draw_indirect_count)  */
#if defined(VK_KHR_dynamic_rendering)
PFN_vkCmdBeginRenderingKHR vkCmdBeginRenderingKHR;
PFN_vkCmdEndRenderingKHR vkCmdEndRenderingKHR;
#endif /*  defined(VK_KHR_dynamic_rendering)  */
#if defined(VK_KHR_dynamic_rendering_local_read)
PFN_vkCmdSetRenderingAttachmentLocationsKHR vkCmdSetRenderingAttachmentLocationsKHR;
PFN_vkCmdSetRenderingInputAttachmentIndicesKHR vkCmdSetRenderingInputAttachmentIndicesKHR;
#endif /*  defined(VK_KHR_dynamic_rendering_local_read)  */
#if defined(VK_KHR_external_fence_capabilities)
PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR vkGetPhysicalDeviceExternalFencePropertiesKHR;
#endif /*  defined(VK_KHR_external_fence_capabilities)  */
#if defined(VK_KHR_external_fence_fd)
PFN_vkGetFenceFdKHR vkGetFenceFdKHR;
PFN_vkImportFenceFdKHR vkImportFenceFdKHR;
#endif /*  defined(VK_KHR_external_fence_fd)  */
#if defined(VK_KHR_external_fence_win32)
PFN_vkGetFenceWin32HandleKHR vkGetFenceWin32HandleKHR;
PFN_vkImportFenceWin32HandleKHR vkImportFenceWin32HandleKHR;
#endif /*  defined(VK_KHR_external_fence_win32)  */
#if defined(VK_KHR_external_memory_capabilities)
PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR vkGetPhysicalDeviceExternalBufferPropertiesKHR;
#endif /*  defined(VK_KHR_external_memory_capabilities)  */
#if defined(VK_KHR_external_memory_fd)
PFN_vkGetMemoryFdKHR vkGetMemoryFdKHR;
PFN_vkGetMemoryFdPropertiesKHR vkGetMemoryFdPropertiesKHR;
#endif /*  defined(VK_KHR_external_memory_fd)  */
#if defined(VK_KHR_external_memory_win32)
PFN_vkGetMemoryWin32HandleKHR vkGetMemoryWin32HandleKHR;
PFN_vkGetMemoryWin32HandlePropertiesKHR vkGetMemoryWin32HandlePropertiesKHR;
#endif /*  defined(VK_KHR_external_memory_win32)  */
#if defined(VK_KHR_external_semaphore_capabilities)
PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
#endif /*  defined(VK_KHR_external_semaphore_capabilities)  */
#if defined(VK_KHR_external_semaphore_fd)
PFN_vkGetSemaphoreFdKHR vkGetSemaphoreFdKHR;
PFN_vkImportSemaphoreFdKHR vkImportSemaphoreFdKHR;
#endif /*  defined(VK_KHR_external_semaphore_fd)  */
#if defined(VK_KHR_external_semaphore_win32)
PFN_vkGetSemaphoreWin32HandleKHR vkGetSemaphoreWin32HandleKHR;
PFN_vkImportSemaphoreWin32HandleKHR vkImportSemaphoreWin32HandleKHR;
#endif /*  defined(VK_KHR_external_semaphore_win32)  */
#if defined(VK_KHR_fragment_shading_rate)
PFN_vkCmdSetFragmentShadingRateKHR vkCmdSetFragmentShadingRateKHR;
PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR vkGetPhysicalDeviceFragmentShadingRatesKHR;
#endif /*  defined(VK_KHR_fragment_shading_rate)  */
#if defined(VK_KHR_get_display_properties2)
PFN_vkGetDisplayModeProperties2KHR vkGetDisplayModeProperties2KHR;
PFN_vkGetDisplayPlaneCapabilities2KHR vkGetDisplayPlaneCapabilities2KHR;
PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR vkGetPhysicalDeviceDisplayPlaneProperties2KHR;
PFN_vkGetPhysicalDeviceDisplayProperties2KHR vkGetPhysicalDeviceDisplayProperties2KHR;
#endif /*  defined(VK_KHR_get_display_properties2)  */
#if defined(VK_KHR_get_memory_requirements2)
PFN_vkGetBufferMemoryRequirements2KHR vkGetBufferMemoryRequirements2KHR;
PFN_vkGetImageMemoryRequirements2KHR vkGetImageMemoryRequirements2KHR;
PFN_vkGetImageSparseMemoryRequirements2KHR vkGetImageSparseMemoryRequirements2KHR;
#endif /*  defined(VK_KHR_get_memory_requirements2)  */
#if defined(VK_KHR_get_physical_device_properties2)
PFN_vkGetPhysicalDeviceFeatures2KHR vkGetPhysicalDeviceFeatures2KHR;
PFN_vkGetPhysicalDeviceFormatProperties2KHR vkGetPhysicalDeviceFormatProperties2KHR;
PFN_vkGetPhysicalDeviceImageFormatProperties2KHR vkGetPhysicalDeviceImageFormatProperties2KHR;
PFN_vkGetPhysicalDeviceMemoryProperties2KHR vkGetPhysicalDeviceMemoryProperties2KHR;
PFN_vkGetPhysicalDeviceProperties2KHR vkGetPhysicalDeviceProperties2KHR;
PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR vkGetPhysicalDeviceQueueFamilyProperties2KHR;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
#endif /*  defined(VK_KHR_get_physical_device_properties2)  */
#if defined(VK_KHR_get_surface_capabilities2)
PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR;
PFN_vkGetPhysicalDeviceSurfaceFormats2KHR vkGetPhysicalDeviceSurfaceFormats2KHR;
#endif /*  defined(VK_KHR_get_surface_capabilities2)  */
#if defined(VK_KHR_line_rasterization)
PFN_vkCmdSetLineStippleKHR vkCmdSetLineStippleKHR;
#endif /*  defined(VK_KHR_line_rasterization)  */
#if defined(VK_KHR_maintenance1)
PFN_vkTrimCommandPoolKHR vkTrimCommandPoolKHR;
#endif /*  defined(VK_KHR_maintenance1)  */
#if defined(VK_KHR_maintenance3)
PFN_vkGetDescriptorSetLayoutSupportKHR vkGetDescriptorSetLayoutSupportKHR;
#endif /*  defined(VK_KHR_maintenance3)  */
#if defined(VK_KHR_maintenance4)
PFN_vkGetDeviceBufferMemoryRequirementsKHR vkGetDeviceBufferMemoryRequirementsKHR;
PFN_vkGetDeviceImageMemoryRequirementsKHR vkGetDeviceImageMemoryRequirementsKHR;
PFN_vkGetDeviceImageSparseMemoryRequirementsKHR vkGetDeviceImageSparseMemoryRequirementsKHR;
#endif /*  defined(VK_KHR_maintenance4)  */
#if defined(VK_KHR_maintenance5)
PFN_vkCmdBindIndexBuffer2KHR vkCmdBindIndexBuffer2KHR;
PFN_vkGetDeviceImageSubresourceLayoutKHR vkGetDeviceImageSubresourceLayoutKHR;
PFN_vkGetImageSubresourceLayout2KHR vkGetImageSubresourceLayout2KHR;
PFN_vkGetRenderingAreaGranularityKHR vkGetRenderingAreaGranularityKHR;
#endif /*  defined(VK_KHR_maintenance5)  */
#if defined(VK_KHR_maintenance6)
PFN_vkCmdBindDescriptorSets2KHR vkCmdBindDescriptorSets2KHR;
PFN_vkCmdPushConstants2KHR vkCmdPushConstants2KHR;
#endif /*  defined(VK_KHR_maintenance6)  */
#if defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)
PFN_vkCmdPushDescriptorSet2KHR vkCmdPushDescriptorSet2KHR;
PFN_vkCmdPushDescriptorSetWithTemplate2KHR vkCmdPushDescriptorSetWithTemplate2KHR;
#endif /*  defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)  */
#if defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)
PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT vkCmdBindDescriptorBufferEmbeddedSamplers2EXT;
PFN_vkCmdSetDescriptorBufferOffsets2EXT vkCmdSetDescriptorBufferOffsets2EXT;
#endif /*  defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)  */
#if defined(VK_KHR_map_memory2)
PFN_vkMapMemory2KHR vkMapMemory2KHR;
PFN_vkUnmapMemory2KHR vkUnmapMemory2KHR;
#endif /*  defined(VK_KHR_map_memory2)  */
#if defined(VK_KHR_performance_query)
PFN_vkAcquireProfilingLockKHR vkAcquireProfilingLockKHR;
PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
PFN_vkReleaseProfilingLockKHR vkReleaseProfilingLockKHR;
#endif /*  defined(VK_KHR_performance_query)  */
#if defined(VK_KHR_pipeline_executable_properties)
PFN_vkGetPipelineExecutableInternalRepresentationsKHR vkGetPipelineExecutableInternalRepresentationsKHR;
PFN_vkGetPipelineExecutablePropertiesKHR vkGetPipelineExecutablePropertiesKHR;
PFN_vkGetPipelineExecutableStatisticsKHR vkGetPipelineExecutableStatisticsKHR;
#endif /*  defined(VK_KHR_pipeline_executable_properties)  */
#if defined(VK_KHR_present_wait)
PFN_vkWaitForPresentKHR vkWaitForPresentKHR;
#endif /*  defined(VK_KHR_present_wait)  */
#if defined(VK_KHR_push_descriptor)
PFN_vkCmdPushDescriptorSetKHR vkCmdPushDescriptorSetKHR;
#endif /*  defined(VK_KHR_push_descriptor)  */
#if defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)
PFN_vkCmdTraceRaysIndirect2KHR vkCmdTraceRaysIndirect2KHR;
#endif /*  defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)  */
#if defined(VK_KHR_ray_tracing_pipeline)
PFN_vkCmdSetRayTracingPipelineStackSizeKHR vkCmdSetRayTracingPipelineStackSizeKHR;
PFN_vkCmdTraceRaysIndirectKHR vkCmdTraceRaysIndirectKHR;
PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;
PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;
PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR;
PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
PFN_vkGetRayTracingShaderGroupStackSizeKHR vkGetRayTracingShaderGroupStackSizeKHR;
#endif /*  defined(VK_KHR_ray_tracing_pipeline)  */
#if defined(VK_KHR_sampler_ycbcr_conversion)
PFN_vkCreateSamplerYcbcrConversionKHR vkCreateSamplerYcbcrConversionKHR;
PFN_vkDestroySamplerYcbcrConversionKHR vkDestroySamplerYcbcrConversionKHR;
#endif /*  defined(VK_KHR_sampler_ycbcr_conversion)  */
#if defined(VK_KHR_shared_presentable_image)
PFN_vkGetSwapchainStatusKHR vkGetSwapchainStatusKHR;
#endif /*  defined(VK_KHR_shared_presentable_image)  */
#if defined(VK_KHR_surface)
PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR;
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR;
PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
#endif /*  defined(VK_KHR_surface)  */
#if defined(VK_KHR_swapchain)
PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR;
PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR;
PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;
PFN_vkQueuePresentKHR vkQueuePresentKHR;
#endif /*  defined(VK_KHR_swapchain)  */
#if defined(VK_KHR_synchronization2)
PFN_vkCmdPipelineBarrier2KHR vkCmdPipelineBarrier2KHR;
PFN_vkCmdResetEvent2KHR vkCmdResetEvent2KHR;
PFN_vkCmdSetEvent2KHR vkCmdSetEvent2KHR;
PFN_vkCmdWaitEvents2KHR vkCmdWaitEvents2KHR;
PFN_vkCmdWriteTimestamp2KHR vkCmdWriteTimestamp2KHR;
PFN_vkQueueSubmit2KHR vkQueueSubmit2KHR;
#endif /*  defined(VK_KHR_synchronization2)  */
#if defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)
PFN_vkCmdWriteBufferMarker2AMD vkCmdWriteBufferMarker2AMD;
#endif /*  defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)  */
#if defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)
PFN_vkGetQueueCheckpointData2NV vkGetQueueCheckpointData2NV;
#endif /*  defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)  */
#if defined(VK_KHR_timeline_semaphore)
PFN_vkGetSemaphoreCounterValueKHR vkGetSemaphoreCounterValueKHR;
PFN_vkSignalSemaphoreKHR vkSignalSemaphoreKHR;
PFN_vkWaitSemaphoresKHR vkWaitSemaphoresKHR;
#endif /*  defined(VK_KHR_timeline_semaphore)  */
#if defined(VK_KHR_video_decode_queue)
PFN_vkCmdDecodeVideoKHR vkCmdDecodeVideoKHR;
#endif /*  defined(VK_KHR_video_decode_queue)  */
#if defined(VK_KHR_video_encode_queue)
PFN_vkCmdEncodeVideoKHR vkCmdEncodeVideoKHR;
PFN_vkGetEncodedVideoSessionParametersKHR vkGetEncodedVideoSessionParametersKHR;
PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR;
#endif /*  defined(VK_KHR_video_encode_queue)  */
#if defined(VK_KHR_video_queue)
PFN_vkBindVideoSessionMemoryKHR vkBindVideoSessionMemoryKHR;
PFN_vkCmdBeginVideoCodingKHR vkCmdBeginVideoCodingKHR;
PFN_vkCmdControlVideoCodingKHR vkCmdControlVideoCodingKHR;
PFN_vkCmdEndVideoCodingKHR vkCmdEndVideoCodingKHR;
PFN_vkCreateVideoSessionKHR vkCreateVideoSessionKHR;
PFN_vkCreateVideoSessionParametersKHR vkCreateVideoSessionParametersKHR;
PFN_vkDestroyVideoSessionKHR vkDestroyVideoSessionKHR;
PFN_vkDestroyVideoSessionParametersKHR vkDestroyVideoSessionParametersKHR;
PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR vkGetPhysicalDeviceVideoCapabilitiesKHR;
PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR vkGetPhysicalDeviceVideoFormatPropertiesKHR;
PFN_vkGetVideoSessionMemoryRequirementsKHR vkGetVideoSessionMemoryRequirementsKHR;
PFN_vkUpdateVideoSessionParametersKHR vkUpdateVideoSessionParametersKHR;
#endif /*  defined(VK_KHR_video_queue)  */
#if defined(VK_KHR_wayland_surface)
PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;
PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif /*  defined(VK_KHR_wayland_surface)  */
#if defined(VK_KHR_win32_surface)
PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR;
#endif /*  defined(VK_KHR_win32_surface)  */
#if defined(VK_KHR_xcb_surface)
PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR;
PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif /*  defined(VK_KHR_xcb_surface)  */
#if defined(VK_KHR_xlib_surface)
PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;
PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif /*  defined(VK_KHR_xlib_surface)  */
#if defined(VK_MVK_ios_surface)
PFN_vkCreateIOSSurfaceMVK vkCreateIOSSurfaceMVK;
#endif /*  defined(VK_MVK_ios_surface)  */
#if defined(VK_MVK_macos_surface)
PFN_vkCreateMacOSSurfaceMVK vkCreateMacOSSurfaceMVK;
#endif /*  defined(VK_MVK_macos_surface)  */
#if defined(VK_NN_vi_surface)
PFN_vkCreateViSurfaceNN vkCreateViSurfaceNN;
#endif /*  defined(VK_NN_vi_surface)  */
#if defined(VK_NVX_binary_import)
PFN_vkCmdCuLaunchKernelNVX vkCmdCuLaunchKernelNVX;
PFN_vkCreateCuFunctionNVX vkCreateCuFunctionNVX;
PFN_vkCreateCuModuleNVX vkCreateCuModuleNVX;
PFN_vkDestroyCuFunctionNVX vkDestroyCuFunctionNVX;
PFN_vkDestroyCuModuleNVX vkDestroyCuModuleNVX;
#endif /*  defined(VK_NVX_binary_import)  */
#if defined(VK_NVX_image_view_handle)
PFN_vkGetImageViewAddressNVX vkGetImageViewAddressNVX;
PFN_vkGetImageViewHandleNVX vkGetImageViewHandleNVX;
#endif /*  defined(VK_NVX_image_view_handle)  */
#if defined(VK_NV_acquire_winrt_display)
PFN_vkAcquireWinrtDisplayNV vkAcquireWinrtDisplayNV;
PFN_vkGetWinrtDisplayNV vkGetWinrtDisplayNV;
#endif /*  defined(VK_NV_acquire_winrt_display)  */
#if defined(VK_NV_clip_space_w_scaling)
PFN_vkCmdSetViewportWScalingNV vkCmdSetViewportWScalingNV;
#endif /*  defined(VK_NV_clip_space_w_scaling)  */
#if defined(VK_NV_cooperative_matrix)
PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV vkGetPhysicalDeviceCooperativeMatrixPropertiesNV;
#endif /*  defined(VK_NV_cooperative_matrix)  */
#if defined(VK_NV_copy_memory_indirect)
PFN_vkCmdCopyMemoryIndirectNV vkCmdCopyMemoryIndirectNV;
PFN_vkCmdCopyMemoryToImageIndirectNV vkCmdCopyMemoryToImageIndirectNV;
#endif /*  defined(VK_NV_copy_memory_indirect)  */
#if defined(VK_NV_coverage_reduction_mode)
PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV;
#endif /*  defined(VK_NV_coverage_reduction_mode)  */
#if defined(VK_NV_cuda_kernel_launch)
PFN_vkCmdCudaLaunchKernelNV vkCmdCudaLaunchKernelNV;
PFN_vkCreateCudaFunctionNV vkCreateCudaFunctionNV;
PFN_vkCreateCudaModuleNV vkCreateCudaModuleNV;
PFN_vkDestroyCudaFunctionNV vkDestroyCudaFunctionNV;
PFN_vkDestroyCudaModuleNV vkDestroyCudaModuleNV;
PFN_vkGetCudaModuleCacheNV vkGetCudaModuleCacheNV;
#endif /*  defined(VK_NV_cuda_kernel_launch)  */
#if defined(VK_NV_device_diagnostic_checkpoints)
PFN_vkCmdSetCheckpointNV vkCmdSetCheckpointNV;
PFN_vkGetQueueCheckpointDataNV vkGetQueueCheckpointDataNV;
#endif /*  defined(VK_NV_device_diagnostic_checkpoints)  */
#if defined(VK_NV_device_generated_commands)
PFN_vkCmdBindPipelineShaderGroupNV vkCmdBindPipelineShaderGroupNV;
PFN_vkCmdExecuteGeneratedCommandsNV vkCmdExecuteGeneratedCommandsNV;
PFN_vkCmdPreprocessGeneratedCommandsNV vkCmdPreprocessGeneratedCommandsNV;
PFN_vkCreateIndirectCommandsLayoutNV vkCreateIndirectCommandsLayoutNV;
PFN_vkDestroyIndirectCommandsLayoutNV vkDestroyIndirectCommandsLayoutNV;
PFN_vkGetGeneratedCommandsMemoryRequirementsNV vkGetGeneratedCommandsMemoryRequirementsNV;
#endif /*  defined(VK_NV_device_generated_commands)  */
#if defined(VK_NV_device_generated_commands_compute)
PFN_vkCmdUpdatePipelineIndirectBufferNV vkCmdUpdatePipelineIndirectBufferNV;
PFN_vkGetPipelineIndirectDeviceAddressNV vkGetPipelineIndirectDeviceAddressNV;
PFN_vkGetPipelineIndirectMemoryRequirementsNV vkGetPipelineIndirectMemoryRequirementsNV;
#endif /*  defined(VK_NV_device_generated_commands_compute)  */
#if defined(VK_NV_external_memory_capabilities)
PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV vkGetPhysicalDeviceExternalImageFormatPropertiesNV;
#endif /*  defined(VK_NV_external_memory_capabilities)  */
#if defined(VK_NV_external_memory_rdma)
PFN_vkGetMemoryRemoteAddressNV vkGetMemoryRemoteAddressNV;
#endif /*  defined(VK_NV_external_memory_rdma)  */
#if defined(VK_NV_external_memory_win32)
PFN_vkGetMemoryWin32HandleNV vkGetMemoryWin32HandleNV;
#endif /*  defined(VK_NV_external_memory_win32)  */
#if defined(VK_NV_fragment_shading_rate_enums)
PFN_vkCmdSetFragmentShadingRateEnumNV vkCmdSetFragmentShadingRateEnumNV;
#endif /*  defined(VK_NV_fragment_shading_rate_enums)  */
#if defined(VK_NV_low_latency2)
PFN_vkGetLatencyTimingsNV vkGetLatencyTimingsNV;
PFN_vkLatencySleepNV vkLatencySleepNV;
PFN_vkQueueNotifyOutOfBandNV vkQueueNotifyOutOfBandNV;
PFN_vkSetLatencyMarkerNV vkSetLatencyMarkerNV;
PFN_vkSetLatencySleepModeNV vkSetLatencySleepModeNV;
#endif /*  defined(VK_NV_low_latency2)  */
#if defined(VK_NV_memory_decompression)
PFN_vkCmdDecompressMemoryIndirectCountNV vkCmdDecompressMemoryIndirectCountNV;
PFN_vkCmdDecompressMemoryNV vkCmdDecompressMemoryNV;
#endif /*  defined(VK_NV_memory_decompression)  */
#if defined(VK_NV_mesh_shader)
PFN_vkCmdDrawMeshTasksIndirectCountNV vkCmdDrawMeshTasksIndirectCountNV;
PFN_vkCmdDrawMeshTasksIndirectNV vkCmdDrawMeshTasksIndirectNV;
PFN_vkCmdDrawMeshTasksNV vkCmdDrawMeshTasksNV;
#endif /*  defined(VK_NV_mesh_shader)  */
#if defined(VK_NV_optical_flow)
PFN_vkBindOpticalFlowSessionImageNV vkBindOpticalFlowSessionImageNV;
PFN_vkCmdOpticalFlowExecuteNV vkCmdOpticalFlowExecuteNV;
PFN_vkCreateOpticalFlowSessionNV vkCreateOpticalFlowSessionNV;
PFN_vkDestroyOpticalFlowSessionNV vkDestroyOpticalFlowSessionNV;
PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV vkGetPhysicalDeviceOpticalFlowImageFormatsNV;
#endif /*  defined(VK_NV_optical_flow)  */
#if defined(VK_NV_ray_tracing)
PFN_vkBindAccelerationStructureMemoryNV vkBindAccelerationStructureMemoryNV;
PFN_vkCmdBuildAccelerationStructureNV vkCmdBuildAccelerationStructureNV;
PFN_vkCmdCopyAccelerationStructureNV vkCmdCopyAccelerationStructureNV;
PFN_vkCmdTraceRaysNV vkCmdTraceRaysNV;
PFN_vkCmdWriteAccelerationStructuresPropertiesNV vkCmdWriteAccelerationStructuresPropertiesNV;
PFN_vkCompileDeferredNV vkCompileDeferredNV;
PFN_vkCreateAccelerationStructureNV vkCreateAccelerationStructureNV;
PFN_vkCreateRayTracingPipelinesNV vkCreateRayTracingPipelinesNV;
PFN_vkDestroyAccelerationStructureNV vkDestroyAccelerationStructureNV;
PFN_vkGetAccelerationStructureHandleNV vkGetAccelerationStructureHandleNV;
PFN_vkGetAccelerationStructureMemoryRequirementsNV vkGetAccelerationStructureMemoryRequirementsNV;
PFN_vkGetRayTracingShaderGroupHandlesNV vkGetRayTracingShaderGroupHandlesNV;
#endif /*  defined(VK_NV_ray_tracing)  */
#if defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2
PFN_vkCmdSetExclusiveScissorEnableNV vkCmdSetExclusiveScissorEnableNV;
#endif /*  defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2  */
#if defined(VK_NV_scissor_exclusive)
PFN_vkCmdSetExclusiveScissorNV vkCmdSetExclusiveScissorNV;
#endif /*  defined(VK_NV_scissor_exclusive)  */
#if defined(VK_NV_shading_rate_image)
PFN_vkCmdBindShadingRateImageNV vkCmdBindShadingRateImageNV;
PFN_vkCmdSetCoarseSampleOrderNV vkCmdSetCoarseSampleOrderNV;
PFN_vkCmdSetViewportShadingRatePaletteNV vkCmdSetViewportShadingRatePaletteNV;
#endif /*  defined(VK_NV_shading_rate_image)  */
#if defined(VK_QCOM_tile_properties)
PFN_vkGetDynamicRenderingTilePropertiesQCOM vkGetDynamicRenderingTilePropertiesQCOM;
PFN_vkGetFramebufferTilePropertiesQCOM vkGetFramebufferTilePropertiesQCOM;
#endif /*  defined(VK_QCOM_tile_properties)  */
#if defined(VK_QNX_external_memory_screen_buffer)
PFN_vkGetScreenBufferPropertiesQNX vkGetScreenBufferPropertiesQNX;
#endif /*  defined(VK_QNX_external_memory_screen_buffer)  */
#if defined(VK_QNX_screen_surface)
PFN_vkCreateScreenSurfaceQNX vkCreateScreenSurfaceQNX;
PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX vkGetPhysicalDeviceScreenPresentationSupportQNX;
#endif /*  defined(VK_QNX_screen_surface)  */
#if defined(VK_VALVE_descriptor_set_host_mapping)
PFN_vkGetDescriptorSetHostMappingVALVE vkGetDescriptorSetHostMappingVALVE;
PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE vkGetDescriptorSetLayoutHostMappingInfoVALVE;
#endif /*  defined(VK_VALVE_descriptor_set_host_mapping)  */
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
PFN_vkCmdBindVertexBuffers2EXT vkCmdBindVertexBuffers2EXT;
PFN_vkCmdSetCullModeEXT vkCmdSetCullModeEXT;
PFN_vkCmdSetDepthBoundsTestEnableEXT vkCmdSetDepthBoundsTestEnableEXT;
PFN_vkCmdSetDepthCompareOpEXT vkCmdSetDepthCompareOpEXT;
PFN_vkCmdSetDepthTestEnableEXT vkCmdSetDepthTestEnableEXT;
PFN_vkCmdSetDepthWriteEnableEXT vkCmdSetDepthWriteEnableEXT;
PFN_vkCmdSetFrontFaceEXT vkCmdSetFrontFaceEXT;
PFN_vkCmdSetPrimitiveTopologyEXT vkCmdSetPrimitiveTopologyEXT;
PFN_vkCmdSetScissorWithCountEXT vkCmdSetScissorWithCountEXT;
PFN_vkCmdSetStencilOpEXT vkCmdSetStencilOpEXT;
PFN_vkCmdSetStencilTestEnableEXT vkCmdSetStencilTestEnableEXT;
PFN_vkCmdSetViewportWithCountEXT vkCmdSetViewportWithCountEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
PFN_vkCmdSetDepthBiasEnableEXT vkCmdSetDepthBiasEnableEXT;
PFN_vkCmdSetLogicOpEXT vkCmdSetLogicOpEXT;
PFN_vkCmdSetPatchControlPointsEXT vkCmdSetPatchControlPointsEXT;
PFN_vkCmdSetPrimitiveRestartEnableEXT vkCmdSetPrimitiveRestartEnableEXT;
PFN_vkCmdSetRasterizerDiscardEnableEXT vkCmdSetRasterizerDiscardEnableEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
PFN_vkCmdSetAlphaToCoverageEnableEXT vkCmdSetAlphaToCoverageEnableEXT;
PFN_vkCmdSetAlphaToOneEnableEXT vkCmdSetAlphaToOneEnableEXT;
PFN_vkCmdSetColorBlendEnableEXT vkCmdSetColorBlendEnableEXT;
PFN_vkCmdSetColorBlendEquationEXT vkCmdSetColorBlendEquationEXT;
PFN_vkCmdSetColorWriteMaskEXT vkCmdSetColorWriteMaskEXT;
PFN_vkCmdSetDepthClampEnableEXT vkCmdSetDepthClampEnableEXT;
PFN_vkCmdSetLogicOpEnableEXT vkCmdSetLogicOpEnableEXT;
PFN_vkCmdSetPolygonModeEXT vkCmdSetPolygonModeEXT;
PFN_vkCmdSetRasterizationSamplesEXT vkCmdSetRasterizationSamplesEXT;
PFN_vkCmdSetSampleMaskEXT vkCmdSetSampleMaskEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1))) || (defined(VK_EXT_shader_object))
PFN_vkCmdSetTessellationDomainOriginEXT vkCmdSetTessellationDomainOriginEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1))) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))
PFN_vkCmdSetRasterizationStreamEXT vkCmdSetRasterizationStreamEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))
PFN_vkCmdSetConservativeRasterizationModeEXT vkCmdSetConservativeRasterizationModeEXT;
PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT vkCmdSetExtraPrimitiveOverestimationSizeEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))
PFN_vkCmdSetDepthClipEnableEXT vkCmdSetDepthClipEnableEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))
PFN_vkCmdSetSampleLocationsEnableEXT vkCmdSetSampleLocationsEnableEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))
PFN_vkCmdSetColorBlendAdvancedEXT vkCmdSetColorBlendAdvancedEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))
PFN_vkCmdSetProvokingVertexModeEXT vkCmdSetProvokingVertexModeEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))
PFN_vkCmdSetLineRasterizationModeEXT vkCmdSetLineRasterizationModeEXT;
PFN_vkCmdSetLineStippleEnableEXT vkCmdSetLineStippleEnableEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))
PFN_vkCmdSetDepthClipNegativeOneToOneEXT vkCmdSetDepthClipNegativeOneToOneEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling)) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))
PFN_vkCmdSetViewportWScalingEnableNV vkCmdSetViewportWScalingEnableNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling)) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle)) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))
PFN_vkCmdSetViewportSwizzleNV vkCmdSetViewportSwizzleNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle)) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color)) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))
PFN_vkCmdSetCoverageToColorEnableNV vkCmdSetCoverageToColorEnableNV;
PFN_vkCmdSetCoverageToColorLocationNV vkCmdSetCoverageToColorLocationNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color)) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples)) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))
PFN_vkCmdSetCoverageModulationModeNV vkCmdSetCoverageModulationModeNV;
PFN_vkCmdSetCoverageModulationTableEnableNV vkCmdSetCoverageModulationTableEnableNV;
PFN_vkCmdSetCoverageModulationTableNV vkCmdSetCoverageModulationTableNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples)) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image)) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))
PFN_vkCmdSetShadingRateImageEnableNV vkCmdSetShadingRateImageEnableNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image)) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test)) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))
PFN_vkCmdSetRepresentativeFragmentTestEnableNV vkCmdSetRepresentativeFragmentTestEnableNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test)) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode)) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))
PFN_vkCmdSetCoverageReductionModeNV vkCmdSetCoverageReductionModeNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode)) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))  */
#if (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
PFN_vkGetDeviceGroupSurfacePresentModes2EXT vkGetDeviceGroupSurfacePresentModes2EXT;
#endif /*  (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))  */
#if (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))
PFN_vkGetImageSubresourceLayout2EXT vkGetImageSubresourceLayout2EXT;
#endif /*  (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))  */
#if (defined(VK_EXT_shader_object)) || (defined(VK_EXT_vertex_input_dynamic_state))
PFN_vkCmdSetVertexInputEXT vkCmdSetVertexInputEXT;
#endif /*  (defined(VK_EXT_shader_object)) || (defined(VK_EXT_vertex_input_dynamic_state))  */
#if (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
PFN_vkCmdPushDescriptorSetWithTemplateKHR vkCmdPushDescriptorSetWithTemplateKHR;
#endif /*  (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))  */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
PFN_vkGetDeviceGroupPresentCapabilitiesKHR vkGetDeviceGroupPresentCapabilitiesKHR;
PFN_vkGetDeviceGroupSurfacePresentModesKHR vkGetDeviceGroupSurfacePresentModesKHR;
PFN_vkGetPhysicalDevicePresentRectanglesKHR vkGetPhysicalDevicePresentRectanglesKHR;
#endif /*  (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))  */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
PFN_vkAcquireNextImage2KHR vkAcquireNextImage2KHR;
#endif /*  (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))  */

#ifdef __cplusplus
}
#endif
