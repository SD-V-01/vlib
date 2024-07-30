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
#include "vmem.h"
#include "system.h"
#include "mdos.h"
#include "vulkan/vkmyth.h"

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
		MdvkState.VmemCallback = mdvkInitVmem();
		MdvkState.isVmemCallbackInit = true;

	}

}

VkAllocationCallbacks mdvkInitVmem() {
	VkAllocationCallbacks Result;
	vset(&Result, 0, sizeof(Result));
	Result.pUserData = NULL;
	Result.pfnAllocation = &vkAllocImpl;
	Result.pfnReallocation = &vkReallocImpl;
	Result.pfnFree = &vkFreeImpl;
	Result.pfnInternalAllocation = NULL;
	Result.pfnInternalFree = NULL;

	return Result;

}

MDVK_ERROR mdvkInit(const mdvkInitStruct* InitStruct) {
	mdvkInitVkVmemState();

	mdvkInitLoader();

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
	MDVK_ERROR DeviceErr = mdvkCreateDevice(InitStruct->DeviceLayerNames,
											InitStruct->DeviceLayerCount,
											InitStruct->DeviceExtensionNames,
											InitStruct->DeviceExtensionCount,
											InitStruct->DeviceQueueInfos,
											InitStruct->DeviceQueueCount,
											&MdvkState.PhysDevice,
											&MdvkState.VmemCallback,
											&MdvkState.Device);

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
	//vsys_writeConsoleNullStr("#########");
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

	VERR("Vulkan", "Could not find suetable physical device after searching thru {u32} Devices", DeviceCount);
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

	mdvkLoaderLoadInstance(Result);

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

	mdvkLoaderLoadDevice(Result);

	return MDVK_ERROR_SUCCESS;

}

static st mdvkStrlen(const char* String) {
	const char* A = String;
	for (; *String; String++) {

	}
	return String - A;

}

st mdvkFindNameInList(const char* Key, const char** List, st ListSize) {
	const st WantedSize = mdvkStrlen(Key);

	for (u32 v = 0; v < ListSize; v++) {
		if (mdvkStrlen(List[v]) != WantedSize) {
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

	return MDVK_FIND_IN_LIST_FAILURE;

}

bool mdvkIsInstanceExtensionPresent(const char* WantedExt, MDVK_ERROR* Error, u32* SpecVer) {
	if (WantedExt == NULL) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_WANTED_INSTANCE_EXTENSION_PTR_NULL;

		}
		return false;

	}
	
	u32 ExtCount = 0;
	VkResult EnumErr = vkEnumerateInstanceExtensionProperties(NULL, &ExtCount, NULL);
	if (EnumErr != VK_SUCCESS) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_INSTANCE_EXTENSIONS_NOT_FOUND;

		}

		if (SpecVer != NULL) {
			(*SpecVer) = 0;

		}

		return false;

	}

	VkExtensionProperties Extensions[ExtCount];
	EnumErr = vkEnumerateInstanceExtensionProperties(NULL, &ExtCount, Extensions);
	if (EnumErr != VK_SUCCESS) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_INSTANCE_EXTENSIONS_NOT_ENUMERATABLE;

		}

		if (SpecVer != NULL) {
			(*SpecVer) = 0;

		}

		return false;

	}

	const char* ExtNamePtr[ExtCount];
	for (st v = 0; v < ExtCount; v++) {
		ExtNamePtr[v] = Extensions[v].extensionName;

	}

	st ResultOffset = mdvkFindNameInList(WantedExt, ExtNamePtr, ExtCount);
	if (ResultOffset != MDVK_FIND_IN_LIST_FAILURE) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_SUCCESS;

		}

		if (SpecVer != NULL) {
			(*SpecVer) = Extensions[ResultOffset].specVersion;

		}
		return true;

	}

	if (Error != NULL) {
		(*Error) = MDVK_ERROR_WANTED_INSTANCE_EXTENSION_NOT_FOUND;

	}

	if (SpecVer != NULL) {
		(*SpecVer) = 0;

	}

	return false;

}

bool mdvkIsInstanceLayerPresent(const char* WantedLayer, MDVK_ERROR* Error, u32* SpecVer, u32* ImplVer) {
	if (WantedLayer == NULL) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_WANTED_INSTANCE_LAYER_PTR_NULL;

		}

		return false;

	}

	u32 LayerCount = 0;
	VkResult EnumResult = vkEnumerateInstanceLayerProperties(&LayerCount, NULL);
	if (EnumResult != VK_SUCCESS) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_INSTANCE_LAYERS_NOT_FOUND;

		}

		return false;

	}

	VkLayerProperties Layers[LayerCount];
	EnumResult = vkEnumerateInstanceLayerProperties(&LayerCount, Layers);
	if (EnumResult != VK_SUCCESS) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_INSTANCE_LAYERS_NOT_ENUMERATABLE;

		}

		return false;

	}

	const char* PtrList[LayerCount];
	for (st v = 0; v < LayerCount; v++) {
		PtrList[v] = Layers[v].layerName;

	}

	st ResultOffset = mdvkFindNameInList(WantedLayer, PtrList, LayerCount);
	if (ResultOffset != MDVK_FIND_IN_LIST_FAILURE) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_SUCCESS;

		}

		if (SpecVer != NULL) {
			(*SpecVer) = Layers[ResultOffset].specVersion;

		}

		if (ImplVer != NULL) {
			(*ImplVer) = Layers[ResultOffset].implementationVersion;

		}

		return true;

	}

	if (Error != NULL) {
		(*Error) = MDVK_ERROR_WANTED_INSTANCE_LAYER_NOT_FOUND;

	}

	return false;

}

MDVK_ERROR mdvkDumpAllInstanceExtToStdout() {
	u32 ExtCount = 0;
	VkResult EnumErr = vkEnumerateInstanceExtensionProperties(NULL, &ExtCount, NULL);
	if (EnumErr != VK_SUCCESS) {
		return MDVK_ERROR_STDOUT_DUMP_INSTANCE_EXT_COUNT;

	}

	//vsys_writeConsoleNullStr("Dumping Vulkan instance extensions to stdout, \"");
	//vsys_writeConsoleInteger(ExtCount);
	//vsys_writeConsoleNullStr("\" extensions found !!!");

	VLOG("Vulkan", "Dumping Vulkan instance extensions, {u32} Extensions found !!!", ExtCount);

	VkExtensionProperties Extensions[ExtCount];
	EnumErr = vkEnumerateInstanceExtensionProperties(NULL, &ExtCount, Extensions);
	if (EnumErr != VK_SUCCESS) {
		return MDVK_ERROR_STDOUT_DUMP_INSTANCE_EXT_COUNT;

	}

	for (st v = 0; v < ExtCount; v++) {
		//vsys_writeConsoleNullStr("\n    Ext \"");
		//vsys_writeConsoleNullStr(Extensions[v].extensionName);
		//vsys_writeConsoleNullStr("\" ver ");
		//vsys_writeConsoleInteger(Extensions[v].specVersion);

		VLOG("Vulkan", "    Ext {cstr} ver {u32}", Extensions[v].extensionName, Extensions[v].specVersion);

	}
	//vsys_writeConsoleNullStr("\n");

	return MDVK_ERROR_SUCCESS;

}

MDVK_ERROR mdvkDumpAllInstanceLayerToStdout() {
	u32 LayerCount = 0;
	VkResult EnumErr = vkEnumerateInstanceLayerProperties(&LayerCount, NULL);
	if (EnumErr != VK_SUCCESS) {
		return MDVK_ERROR_STDOUT_DUMP_INSTANCE_LAYER_COUNT;

	}

	//vsys_writeConsoleNullStr("Dumping Vulkan instance layers to stdout, \"");
	//vsys_writeConsoleInteger(LayerCount);
	//vsys_writeConsoleNullStr("\" Extensions found !!!");

	VLOG("Vulkan", "Dumping Vulkan instance layers, {u32} Layers found !!", LayerCount);

	VkLayerProperties Layers[LayerCount];
	EnumErr = vkEnumerateInstanceLayerProperties(&LayerCount, Layers);
	if (EnumErr != VK_SUCCESS) {
		return MDVK_ERROR_STDOUT_DUMP_INSTANCE_LAYER_ENUM;

	}

	for (st v = 0; v < LayerCount; v++) {
		//vsys_writeConsoleNullStr("\n    Layer \"");
		//vsys_writeConsoleNullStr(Layers[v].layerName);
		//vsys_writeConsoleNullStr("\" implementation ver ");
		//vsys_writeConsoleInteger(Layers[v].implementationVersion);
		//vsys_writeConsoleNullStr(" spec ver ");
		//vsys_writeConsoleInteger(Layers[v].specVersion);

		VLOG("Vulkan", "    Layer {cstr} impl ver {u32} spec ver {u32} description {cstr}",
			 Layers[v].layerName, Layers[v].implementationVersion, Layers[v].specVersion, Layers[v].description);

	}
	//vsys_writeConsoleNullStr("\n");

	return MDVK_ERROR_SUCCESS;

}

bool mdvkIsDeviceExtensionPresent(const char* WantedExt, VkPhysicalDevice* Device, MDVK_ERROR* Error, u32* SpecVer) {
	if (WantedExt == NULL) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_WANTED_DEVICE_EXTENSION_NULL_PTR;

		}

		if (SpecVer != NULL) {
			(*SpecVer) = 0;

		}

		return false;

	}

	u32 ExtensionCount = 0;
	VkResult EnumErr = vkEnumerateDeviceExtensionProperties(*Device, NULL, &ExtensionCount, NULL);
	if (EnumErr != VK_SUCCESS) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_DEVICE_EXTENSIONS_NOT_FOUND;

		}

		if (SpecVer != NULL) {
			(*SpecVer) = 0;

		}

		return false;

	}

	VkExtensionProperties Extensions[ExtensionCount];
	EnumErr = vkEnumerateDeviceExtensionProperties(*Device, NULL, &ExtensionCount, Extensions);
	if (EnumErr != VK_SUCCESS) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_DEVICE_EXTENSIONS_NOT_ENUMERATABLE;

		}

		if (SpecVer != NULL) {
			(*SpecVer) = 0;

		}

		return false;

	}

	const char* ExtNameList[ExtensionCount];
	for (st v = 0; v < ExtensionCount; v++) {
		ExtNameList[v] = Extensions[v].extensionName;

	}

	st ResultOffset = mdvkFindNameInList(WantedExt, ExtNameList, ExtensionCount);
	if (ResultOffset != MDVK_FIND_IN_LIST_FAILURE) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_SUCCESS;

		}

		if (SpecVer != NULL) {
			(*SpecVer) = Extensions[ResultOffset].specVersion;

		}

		return true;

	}

	if (Error != NULL) {
		(*Error) = MDVK_ERROR_WANTED_DEVICE_EXTENSION_NOT_FOUND;

	}

	if (SpecVer != NULL) {
		(*SpecVer) = 0;

	}

	return false;

}

bool mdvkIsDeviceLayerPresent(const char* WantedExt, VkPhysicalDevice* Device, MDVK_ERROR* Error, u32* SpecVer, u32* ImplVer) {
	if (WantedExt == NULL) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_WANTED_DEVICE_LAYER_PTR_NULL;

		}

		if (SpecVer != NULL) {
			(*SpecVer) = 0;

		}

		if (ImplVer != NULL) {
			(*ImplVer) = 0;

		}

		return false;

	}

	u32 LayerCount;
	VkResult EnumResult = vkEnumerateDeviceLayerProperties(*Device, &LayerCount, NULL);
	if (EnumResult != VK_SUCCESS) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_DEVICE_LAYERS_NOT_FOUND;

		}

		if (SpecVer != NULL) {
			(*SpecVer) = 0;

		}

		if (ImplVer != NULL) {
			(*ImplVer) = 0;

		}

		return false;

	}

	VkLayerProperties Layers[LayerCount];
	EnumResult = vkEnumerateDeviceLayerProperties(*Device, &LayerCount, Layers);
	if (EnumResult != VK_SUCCESS) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_DEVICE_LAYERS_NOT_ENUMERATABLE;

		}

		if (SpecVer != NULL) {
			(*SpecVer) = 0;

		}

		if (ImplVer != NULL) {
			(*ImplVer) = 0;

		}

		return false;

	}

	const char* LayerPtr[LayerCount];
	for (st v = 0; v < LayerCount; v++) {
		LayerPtr[v] = Layers[v].layerName;

	}

	st ResultOffset = mdvkFindNameInList(WantedExt, LayerPtr, LayerCount);
	if (ResultOffset != MDVK_FIND_IN_LIST_FAILURE) {
		if (Error != NULL) {
			(*Error) = MDVK_ERROR_SUCCESS;

		}

		if (SpecVer != NULL) {
			(*SpecVer) = Layers[ResultOffset].specVersion;

		}

		if (ImplVer != NULL) {
			(*ImplVer) = Layers[ResultOffset].implementationVersion;

		}

		return true;

	}

	if (Error != NULL) {
		(*Error) = MDVK_ERROR_WANTED_DEVICE_LAYER_NOT_FOUND;

	}

	if (SpecVer != NULL) {
		(*SpecVer) = 0;

	}

	if (ImplVer != NULL) {
		(*ImplVer) = 0;

	}

	return false;

}

MDVK_ERROR mdvkDumpAllDeviceExtToStdout(VkPhysicalDevice* Device) {
	if (Device == NULL) {
		return MDVK_ERROR_STDOUT_DUMP_DEVICE_EXT_DEVICE_INVALID;

	}

	u32 ExtCount = 0;
	VkResult EnumErr = vkEnumerateDeviceExtensionProperties(*Device, NULL, &ExtCount, NULL);
	if (EnumErr != VK_SUCCESS) {
		return MDVK_ERROR_STDOUT_DUMP_DEVICE_EXT_COUNT;

	}

	//vsys_writeConsoleNullStr("Dumping Vulkan device extensions to stdout, \"");
	//vsys_writeConsoleInteger(ExtCount);
	//vsys_writeConsoleNullStr("\" Extensions found !!!");

	VLOG("Vulkan", "Dumping vulkan device extensions, {u32} Extensions found !!!", ExtCount);

	VkExtensionProperties Extensions[ExtCount];
	EnumErr = vkEnumerateDeviceExtensionProperties(*Device, NULL, &ExtCount, Extensions);
	if (EnumErr != VK_SUCCESS) {
		return MDVK_ERROR_STDOUT_DUMP_DEVICE_EXT_ENUM;

	}

	for (st v = 0; v < ExtCount; v++) {
		//vsys_writeConsoleNullStr("\n    Ext \"");
		//vsys_writeConsoleNullStr(Extensions[v].extensionName);
		//vsys_writeConsoleNullStr("\" ver ");
		//vsys_writeConsoleInteger(Extensions[v].specVersion);

		VLOG("Vulkan", "    Ext {cstr} ver {u32}", Extensions[v].extensionName, Extensions[v].specVersion);

	}

	//vsys_writeConsoleNullStr("\n");
	return MDVK_ERROR_SUCCESS;

}

MDVK_ERROR mdvkDumpAllDeviceLayerToStdout(VkPhysicalDevice* Device) {
	if (Device == NULL) {
		return MDVK_ERROR_STDOUT_DUMP_DEVICE_LAYER_DEVICE_INVALID;

	}

	u32 LayerCount = 0;
	VkResult LayerEnumErr = vkEnumerateDeviceLayerProperties(*Device, &LayerCount, NULL);
	if (LayerEnumErr != VK_SUCCESS) {
		return MDVK_ERROR_STDOUT_DUMP_DEVICE_LAYER_COUNT;

	}

	//vsys_writeConsoleNullStr("Dumping Vulkan device layers to stdout, \"");
	//vsys_writeConsoleInteger(LayerCount);
	//vsys_writeConsoleNullStr("\" Layers found !!!");

	VLOG("Vulkan", "Dumping Vulkan device layers, {u32} Layers found !!", LayerCount);

	VkLayerProperties Layers[LayerCount];
	LayerEnumErr = vkEnumerateDeviceLayerProperties(*Device, &LayerCount, Layers);
	if (LayerEnumErr != VK_SUCCESS) {
		return MDVK_ERROR_STDOUT_DUMP_DEVICE_LAYER_ENUM;

	}

	for (st v = 0; v < LayerCount; v++) {
		//vsys_writeConsoleNullStr("\n    Layer \"");
		//vsys_writeConsoleNullStr(Layers[v].layerName);
		//vsys_writeConsoleNullStr("\" implementation ver ");
		//vsys_writeConsoleInteger(Layers[v].implementationVersion);
		//vsys_writeConsoleNullStr(" spec ver ");
		//vsys_writeConsoleInteger(Layers[v].specVersion);

		VLOG("Vulkan", "    Layer {cstr} impl ver {u32} spec ver {u32} description {cstr}",
			 Layers[v].layerName, Layers[v].implementationVersion, Layers[v].specVersion, Layers[v].description);

	}

	//vsys_writeConsoleNullStr("\n");

	return MDVK_ERROR_SUCCESS;

}

MDVK_ERROR mdvkInitLoader() {
	if (mythVkLoad() == VK_SUCCESS) {
		return MDVK_ERROR_SUCCESS;

	}
	else {
		return MDVK_ERROR_UNKNOWN;

	}

}

MDVK_ERROR mdvkFreeLoader() {
	mythVkExit();
	return MDVK_ERROR_SUCCESS;

}

MDVK_ERROR mdvkLoaderLoadInstance(VkInstance* Instance) {
	mythVkLoadInstance(*Instance);
	return MDVK_ERROR_SUCCESS;

}

MDVK_ERROR mdvkLoaderLoadDevice(VkDevice* Device) {
	mythVkLoadDevice(*Device);
	return MDVK_ERROR_SUCCESS;

}
