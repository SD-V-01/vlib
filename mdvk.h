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

VLIB_STRUCT(mdvkState)
VkInstance Instance;
VkDevice Device;
VkPhysicalDevice PhysDevice;
i32 MainGraphicsQueueIndex;
VkAllocationCallbacks VmemCallback;
bool isVmemCallbackInit;

VLIB_STRUCTEND(mdvkState)

const mdvkState* getVulkanState();
void initVkVmemState();

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

enum MDVK_ERROR {
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

//    NOTE(V): get queue error
	MDVK_ERROR_QUEUE_PROPERTIES_NOT_FOUND = 300,
	MDVK_ERROR_QUEUE_INDEX_NOT_FOUND,

};

MDVK_ERROR mdvkInit(const mdvkInitStruct* InitStruct);
MDVK_ERROR mdvkGetBestPhysicalDevice(u32 ApiVer, VkInstance* Instance, VkPhysicalDevice* Result);
MDVK_ERROR mdvkGetFirstQueueIndex(VkPhysicalDevice PhysDevice, VkQueueFlags WantedFlags, i32* Result);
MDVK_ERROR mdvkCreateInstance(const char** Extensions, st ExtensionCount, const char** Layers, st LayerCount,
							  const char* AppName, u32 ApiVer, VkAllocationCallbacks* MemCb, VkInstance* Result);
MDVK_ERROR mdvkCreateDevice(const char** Layers, st LayerCount, const char** Extensions, st ExtensionCount,
							const VkDeviceQueueCreateInfo* Queues, st QueueCount, VkPhysicalDevice* PhysDevice,
							VkAllocationCallbacks* MemCb, VkDevice* Result);
