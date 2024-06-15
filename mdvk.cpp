////////////////////////////////////////////////////////////////////////////
//
//  VLIB Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mdvk.cpp
//  Version:     v1.00
//  Created:     11/06/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "mdvk.h"
#include "mem.h"
#include "volk.h"

static mdvkState MdvkState;

const mdvkState* mdvkGetVulkanState() {
	return &MdvkState;

}

static void* vkAllocImpl(void* UserData, st Size, st Alignment, VkSystemAllocationScope Scope) {
	void* Result = vaalloc(Size, Alignment);
	vset(Result, 0, Size);
	return Result;

}

static void* vkReallocImpl(void* UserData, void* Original, st Size, st Alignment, VkSystemAllocationScope AllocScope) {
	return varealloc(Original, Size, Alignment);

}

static void vkFreeImpl(void* UserData, void* Ptr) {
	vfree(Ptr);

}

void mdvkInitVkVmemState() {
	if (MdvkState.isVmemCallbackInit == false) {
		MdvkState.VmemCallback.pUserData = NULL;
		MdvkState.VmemCallback.pfnAllocation = &vkAllocImpl;
		MdvkState.VmemCallback.pfnReallocation = &vkReallocImpl;
		MdvkState.VmemCallback.pfnFree = &vkFreeImpl;
		MdvkState.VmemCallback.pfnInternalAllocation = NULL;
		MdvkState.VmemCallback.pfnInternalFree = NULL;

		MdvkState.isVmemCallbackInit = true;

	}

}

MDVK_ERROR mdvkInit(const mdvkInitStruct* InitStruct) {
	initVkVmemState();

	volkInitialize();

	//    NOTE(V): Creating vulkan instance
	MDVK_ERROR InstanceErr = mdvkCreateInstance(InitStruct->InstanceExtensionNames,
												InitStruct->InstanceExtensionCount,
												InitStruct->InstanceLayerNames,
												InitStruct->InstanceLayerCount,
												InitStruct->AppName,
												InitStruct->ApiVersion,
												&MdvkState.VmemCallback,
												&MdvkState.Instance);

	if (InstanceErr != MDVK_ERROR_SUCCESS) {
		return InstanceErr;

	}

//    NOTE(V): Selecting physical device
	MDVK_ERROR PhysDeviceError = mdvkGetBestPhysicalDevice(InitStruct->ApiVersion, &MdvkState.Instance, &MdvkState.PhysDevice);
	if (PhysDeviceError != MDVK_ERROR_SUCCESS) {
		return PhysDeviceError;

	}

	//    NOTE(V): VkDevice init
	

	return MDVK_ERROR_SUCCESS;

}

MDVK_ERROR mdvkGetBestPhysicalDevice(u32 ApiVer, VkInstance* Instance, VkPhysicalDevice* Result) {
	u32 DeviceCount = 0;
	VkResult EnumErr = vkEnumeratePhysicalDevices(*Instance, &DeviceCount, NULL);
	if (EnumErr != VK_SUCCESS) {
		return MDVK_ERROR_COULD_NOT_GET_NUMBER_OF_DEVICES;

	}

	VkPhysicalDevice Devices[DeviceCount];
	EnumErr = vkEnumeratePhysicalDevices(*Instance, &DeviceCount, Devices);

	if (EnumErr != VK_SUCCESS) {
		return MDVK_ERROR_PHYSICAL_DEVICE_ENUM_FAILED;

	}

//    TODO(V): Use vram as a suplementary variable to check for best device

	if(DeviceCount == 0){
		return MDVK_ERROR_NO_PHYSICAL_DEVICES_FOUND;

	}

//    NOTE(V): Checking for discret gpu
	for (u32 v = 0; v < DeviceCount; v++) {
		VkPhysicalDeviceProperties Properties;
		vkGetPhysicalDeviceProperties(Devices[v], &Properties);

		if (Properties.apiVersion > ApiVer) {
			if (Properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
				(*Result) = Devices[v];
				return MDVK_ERROR_SUCCESS;

			}

		}

	}

//    NOTE(V): Checking for integrated gpu
	for (u32 v = 0; v < DeviceCount; v++) {
		VkPhysicalDeviceProperties Properties;
		vkGetPhysicalDeviceProperties(Devices[v], &Properties);

		if (Properties.apiVersion > ApiVer) {
			if (Properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) {
				(*Result) = Devices[v];
				return MDVK_ERROR_SUCCESS;

			}

		}

	}

//    NOTE(V): We are desperate for finding a suetable physical device so we will just get anything that works
	for (u32 v = 0; v < DeviceCount; v++) {
		VkPhysicalDeviceProperties Properties;
		vkGetPhysicalDeviceProperties(Devices[v], &Properties);

		if (Properties.apiVersion > ApiVer) {
			(*Result) = Devices[v];
			return MDVK_ERROR_SUCCESS;
//            NOTE(V): This should cover the weerd stuff like llvm pipe !!!

		}

	}

	return MDVK_ERROR_NO_SUETABLE_PHYSICAL_DEVICE;

}

MDVK_ERROR mdvkGetFirstQueueIndex(VkPhysicalDevice* PhysDevice, VkQueueFlags WantedFlags, i32* Result) {
	u32 QueuePropertiesCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(*PhysDevice, &QueuePropertiesCount, NULL);
	if (QueuePropertiesCount == 0) {
		return MDVK_ERROR_QUEUE_PROPERTIES_NOT_FOUND;

	}
	
	VkQueueFamilyProperties Properties[QueuePropertiesCount];
	vkGetPhysicalDeviceQueueFamilyProperties(*PhysDevice, &QueuePropertiesCount, Properties);
	
	for (u32 v = 0; v < QueuePropertiesCount; v++) {
		if ((Properties[v].queueFlags & WantedFlags) == WantedFlags) {
			(*Result) = v;
			return MDVK_ERROR_SUCCESS;

		}

	}

	return MDVK_ERROR_QUEUE_INDEX_NOT_FOUND;

}

MDVK_ERROR mdvkCreateInstance(const char** Extensions, st ExtensionCount, const char** Layers, st LayerCount,
							  const char* AppName, u32 ApiVer, VkAllocationCallbacks* MemCb, VkInstance* Result) {
	VkApplicationInfo AppInfo;
	AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	AppInfo.pNext = NULL;
	AppInfo.pApplicationName = AppName;
	AppInfo.applicationVersion = 1000;
	AppInfo.pEngineName = "DISRUPT";
	AppInfo.engineVersion = 3380;
	AppInfo.apiVersion = ApiVer;

	VkInstanceCreateInfo CreateInfo;
	CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	CreateInfo.pNext = NULL;
	CreateInfo.flags = 0;
	CreateInfo.pApplicationInfo = &AppInfo;
	if (LayerCount == 0) {
		CreateInfo.enabledLayerCount = 0;
		CreateInfo.ppEnabledLayerNames = NULL;

	}
	else {
		CreateInfo.enabledLayerCount = LayerCount;
		CreateInfo.ppEnabledLayerNames = Layers;

	}

	if (ExtensionCount == 0) {
		CreateInfo.enabledExtensionCount = 0;
		CreateInfo.ppEnabledExtensionNames = NULL;

	}
	else {
		CreateInfo.enabledExtensionCount = ExtensionCount;
		CreateInfo.ppEnabledExtensionNames = Extensions;

	}

	VkResult InstanceResult = vkCreateInstance(&CreateInfo, MemCb, Result);
	if (InstanceResult != VK_SUCCESS) {
		return MDVK_ERROR_CREATE_INSTANCE_FAILED;

	}

	return MDVK_ERROR_SUCCESS;

}

MDVK_ERROR mdvkCreateDevice(const char** Layers, st LayerCount, const char** Extensions, st ExtensionCount,
							const VkDeviceQueueCreateInfo* Queues, st QueueCount, VkPhysicalDevice* PhysDevice,
							VkAllocationCallbacks* MemCb, VkDevice* Result) {
	VkDeviceCreateInfo CreateInfo;
	CreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	CreateInfo.pNext = NULL;
	CreateInfo.flags = 0;

	if (QueueCount == 0) {
		CreateInfo.queueCreateInfoCount = 0;
		CreateInfo.pQueueCreateInfos = NULL;

	}
	else {
		CreateInfo.pQueueCreateInfos = Queues;
		CreateInfo.queueCreateInfoCount = QueueCount;

	}

	if (LayerCount == 0) {
		CreateInfo.enabledLayerCount = 0;
		CreateInfo.ppEnabledLayerNames = NULL;

	}
	else {
		CreateInfo.enabledLayerCount = LayerCount;
		CreateInfo.ppEnabledLayerNames = Layers;

	}

	if (ExtensionCount == 0) {
		CreateInfo.enabledExtensionCount = 0;
		CreateInfo.ppEnabledExtensionNames = NULL;

	}
	else {
		CreateInfo.enabledExtensionCount = ExtensionCount;
		CreateInfo.ppEnabledExtensionNames = Extensions;

	}

	CreateInfo.pEnabledFeatures = NULL;

	VkResult DeviceResult = vkCreateDevice(*PhysDevice, &CreateInfo, MemCb, Result);
	if (DeviceResult != VK_SUCCESS) {
		return MDVK_ERROR_CREATE_DEVICE_FAILED;

	}

	return MDVK_ERROR_SUCCESS;

}
