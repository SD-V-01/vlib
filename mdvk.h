////////////////////////////////////////////////////////////////////////////
//
//  VLIB Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mdvk.h
//  Version:     v1.00
//  Created:     11/06/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VK_NO_PROTOTYPES
#include "vulkan/vulkan.h"

#include "base_types.h"

#define MDVK_API

VLIB_STRUCT(mdvkState)
VkInstance Instance;
VkDevice Device;
VkPhysicalDevice PhysDevice;
i32 MainGraphicsQueueIndex;
VkAllocationCallbacks VmemCallback;
bool isVmemCallbackInit;

VLIB_STRUCTEND(mdvkState)

MDVK_API const mdvkState* mdvkGetVulkanState();
MDVK_API void mdvkInitVkVmemState();
MDVK_API VkAllocationCallbacks mdvkInitVmem();

VLIB_STRUCT(mdvkInitStruct)
const char* AppName;
const char** InstanceExtensionNames;
st InstanceExtensionCount;
const char** InstanceLayerNames;
st InstanceLayerCount;
const char** DeviceExtensionNames;
st DeviceExtensionCount;
const char** DeviceLayerNames;
st DeviceLayerCount;
u32 ApiVersion;
const VkDeviceQueueCreateInfo* DeviceQueueInfos;
st DeviceQueueCount;

VLIB_STRUCTEND(mdvkInitStruct)

typedef enum MDVK_ERROR {
	MDVK_ERROR_UNKNOWN = 0,
	MDVK_ERROR_SUCCESS = 1,

//    NOTE(V): physical device
	MDVK_ERROR_NO_SUETABLE_PHYSICAL_DEVICE = 100,
	MDVK_ERROR_COULD_NOT_GET_NUMBER_OF_DEVICES,
	MDVK_ERROR_PHYSICAL_DEVICE_ENUM_FAILED,
	MDVK_ERROR_NO_PHYSICAL_DEVICES_FOUND,

//    NOTE(V): init error
	MDVK_ERROR_NO_PHYSICAL_DEVICE = 200,
	MDVK_ERROR_CREATE_DEVICE_FAILED,
	MDVK_ERROR_CREATE_INSTANCE_FAILED,
	MDVK_ERROR_DEVICE_EXTENSIONS_NOT_FOUND,
	MDVK_ERROR_DEVICE_EXTENSIONS_NOT_ENUMERATABLE,
	MDVK_ERROR_WANTED_DEVICE_EXTENSION_NOT_FOUND,
	MDVK_ERROR_WANTED_DEVICE_EXTENSION_NULL_PTR,
	MDVK_ERROR_INSTANCE_EXTENSIONS_NOT_FOUND,
	MDVK_ERROR_INSTANCE_EXTENSIONS_NOT_ENUMERATABLE,
	MDVK_ERROR_WANTED_INSTANCE_EXTENSION_NOT_FOUND,
	MDVK_ERROR_WANTED_INSTANCE_EXTENSION_PTR_NULL,
	MDVK_ERROR_INSTANCE_LAYERS_NOT_FOUND,
	MDVK_ERROR_INSTANCE_LAYERS_NOT_ENUMERATABLE,
	MDVK_ERROR_WANTED_INSTANCE_LAYER_NOT_FOUND,
	MDVK_ERROR_WANTED_INSTANCE_LAYER_PTR_NULL,
	MDVK_ERROR_DEVICE_LAYERS_NOT_FOUND,
	MDVK_ERROR_DEVICE_LAYERS_NOT_ENUMERATABLE,
	MDVK_ERROR_WANTED_DEVICE_LAYER_NOT_FOUND,
	MDVK_ERROR_WANTED_DEVICE_LAYER_PTR_NULL,

//    NOTE(V): get queue error
	MDVK_ERROR_QUEUE_PROPERTIES_NOT_FOUND = 300,
	MDVK_ERROR_QUEUE_INDEX_NOT_FOUND,

//    NOTE(V): Dump to stdout error
	MDVK_ERROR_STDOUT_DUMP_INSTANCE_EXT_COUNT = 350,
	MDVK_ERROR_STDOUT_DUMP_INSTANCE_EXT_ENUM,
	MDVK_ERROR_STDOUT_DUMP_INSTANCE_LAYER_COUNT,
	MDVK_ERROR_STDOUT_DUMP_INSTANCE_LAYER_ENUM,
	MDVK_ERROR_STDOUT_DUMP_DEVICE_EXT_DEVICE_INVALID,
	MDVK_ERROR_STDOUT_DUMP_DEVICE_EXT_COUNT,
	MDVK_ERROR_STDOUT_DUMP_DEVICE_EXT_ENUM,
	MDVK_ERROR_STDOUT_DUMP_DEVICE_LAYER_DEVICE_INVALID,
	MDVK_ERROR_STDOUT_DUMP_DEVICE_LAYER_COUNT,
	MDVK_ERROR_STDOUT_DUMP_DEVICE_LAYER_ENUM

} MDVK_ERROR;

MDVK_API MDVK_ERROR mdvkInit(const mdvkInitStruct* InitStruct);
MDVK_API MDVK_ERROR mdvkGetBestPhysicalDevice(u32 ApiVer, VkInstance* Instance, VkPhysicalDevice* Result);
MDVK_API MDVK_ERROR mdvkGetFirstQueueIndex(VkPhysicalDevice* PhysDevice, VkQueueFlags WantedFlags, i32* Result);

MDVK_API MDVK_ERROR mdvkCreateInstance(const char** Extensions, st ExtensionCount, const char** Layers, st LayerCount,
							  const char* AppName, u32 ApiVer, VkAllocationCallbacks* MemCb, VkInstance* Result);

MDVK_API MDVK_ERROR mdvkCreateDevice(const char** Layers, st LayerCount, const char** Extensions, st ExtensionCount,
							const VkDeviceQueueCreateInfo* Queues, st QueueCount, VkPhysicalDevice* PhysDevice,
							VkAllocationCallbacks* MemCb, VkDevice* Result);

#define MDVK_FIND_IN_LIST_FAILURE 666666
MDVK_API st mdvkFindNameInList(const char* Key, const char** List, st ListSize);
MDVK_API bool mdvkIsInstanceExtensionPresent(const char* WantedExt, MDVK_ERROR* Error, u32* SpecVer);
MDVK_API bool mdvkIsInstanceLayerPresent(const char* WantedLayer, MDVK_ERROR* Error, u32* SpecVer, u32* ImplVer);
MDVK_API MDVK_ERROR mdvkDumpAllInstanceExtToStdout();
MDVK_API MDVK_ERROR mdvkDumpAllInstanceLayerToStdout();
MDVK_API bool mdvkIsDeviceExtensionPresent(const char* WantedExt, VkPhysicalDevice* Device, MDVK_ERROR* Error, u32* SpecVer);
MDVK_API bool mdvkIsDeviceLayerPresent(const char* WantedExt, VkPhysicalDevice* Device, MDVK_ERROR* Error, u32* SpecVer, u32* ImplVer);
MDVK_API MDVK_ERROR mdvkDumpAllDeviceExtToStdout(VkPhysicalDevice* Device);
MDVK_API MDVK_ERROR mdvkDumpAllDeviceLayerToStdout(VkPhysicalDevice* Device);

MDVK_API MDVK_ERROR mdvkXrCreateInstance(const char** Extensions, st ExtensionCount, const char** Layers, st LayerCount,
								const char* AppName, u32 ApiVer, VkAllocationCallbacks* MemCb, VkInstance* Result);

MDVK_API MDVK_ERROR mdvkInitLoader();
MDVK_API MDVK_ERROR mdvkFreeLoader();
MDVK_API MDVK_ERROR mdvkLoaderLoadInstance(VkInstance* Instance);
MDVK_API MDVK_ERROR mdvkLoaderLoadDevice(VkDevice* Device);
