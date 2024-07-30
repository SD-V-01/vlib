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
	_mythVkLoadBasic(NULL, vkGetInstanceProcAddr);

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

void mythVkLoadInstance(VkInstance Instance){
	_mythVkLoadInstance(Instance, vkGetInstanceProcAddr);

}

void mythVkLoadDevice(VkDevice Device){
	MainDevice = Device;
	_mythVkLoadDevice(Device, vkGetDeviceProcAddr);

}

void mythVkLoadArrayDevice(mythVkDeviceFuncArray* FuncArray, VkDevice Device){
	_mythVkLoadArrayDevice(FuncArray, Device, vkGetDeviceProcAddr);

}

void _mythVkLoadBasic(VkInstance Instance, PFN_vkGetInstanceProcAddr LoadFunc){

//SECTION(V): VK_LOADER_BASIC_IMPL
#if defined(VK_VERSION_1_0)
	vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)LoadFunc(Instance, "vkBeginCommandBuffer");
	vkCmdBeginQuery = (PFN_vkCmdBeginQuery)LoadFunc(Instance, "vkCmdBeginQuery");
	vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)LoadFunc(Instance, "vkCmdBeginRenderPass");
	vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)LoadFunc(Instance, "vkCmdBindDescriptorSets");
	vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)LoadFunc(Instance, "vkCmdBindIndexBuffer");
	vkCmdBindPipeline = (PFN_vkCmdBindPipeline)LoadFunc(Instance, "vkCmdBindPipeline");
	vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)LoadFunc(Instance, "vkCmdBindVertexBuffers");
	vkCmdBlitImage = (PFN_vkCmdBlitImage)LoadFunc(Instance, "vkCmdBlitImage");
	vkCmdClearAttachments = (PFN_vkCmdClearAttachments)LoadFunc(Instance, "vkCmdClearAttachments");
	vkCmdClearColorImage = (PFN_vkCmdClearColorImage)LoadFunc(Instance, "vkCmdClearColorImage");
	vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage)LoadFunc(Instance, "vkCmdClearDepthStencilImage");
	vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer)LoadFunc(Instance, "vkCmdCopyBuffer");
	vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)LoadFunc(Instance, "vkCmdCopyBufferToImage");
	vkCmdCopyImage = (PFN_vkCmdCopyImage)LoadFunc(Instance, "vkCmdCopyImage");
	vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer)LoadFunc(Instance, "vkCmdCopyImageToBuffer");
	vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults)LoadFunc(Instance, "vkCmdCopyQueryPoolResults");
	vkCmdDispatch = (PFN_vkCmdDispatch)LoadFunc(Instance, "vkCmdDispatch");
	vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect)LoadFunc(Instance, "vkCmdDispatchIndirect");
	vkCmdDraw = (PFN_vkCmdDraw)LoadFunc(Instance, "vkCmdDraw");
	vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed)LoadFunc(Instance, "vkCmdDrawIndexed");
	vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect)LoadFunc(Instance, "vkCmdDrawIndexedIndirect");
	vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect)LoadFunc(Instance, "vkCmdDrawIndirect");
	vkCmdEndQuery = (PFN_vkCmdEndQuery)LoadFunc(Instance, "vkCmdEndQuery");
	vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)LoadFunc(Instance, "vkCmdEndRenderPass");
	vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands)LoadFunc(Instance, "vkCmdExecuteCommands");
	vkCmdFillBuffer = (PFN_vkCmdFillBuffer)LoadFunc(Instance, "vkCmdFillBuffer");
	vkCmdNextSubpass = (PFN_vkCmdNextSubpass)LoadFunc(Instance, "vkCmdNextSubpass");
	vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)LoadFunc(Instance, "vkCmdPipelineBarrier");
	vkCmdPushConstants = (PFN_vkCmdPushConstants)LoadFunc(Instance, "vkCmdPushConstants");
	vkCmdResetEvent = (PFN_vkCmdResetEvent)LoadFunc(Instance, "vkCmdResetEvent");
	vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool)LoadFunc(Instance, "vkCmdResetQueryPool");
	vkCmdResolveImage = (PFN_vkCmdResolveImage)LoadFunc(Instance, "vkCmdResolveImage");
	vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants)LoadFunc(Instance, "vkCmdSetBlendConstants");
	vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias)LoadFunc(Instance, "vkCmdSetDepthBias");
	vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds)LoadFunc(Instance, "vkCmdSetDepthBounds");
	vkCmdSetEvent = (PFN_vkCmdSetEvent)LoadFunc(Instance, "vkCmdSetEvent");
	vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth)LoadFunc(Instance, "vkCmdSetLineWidth");
	vkCmdSetScissor = (PFN_vkCmdSetScissor)LoadFunc(Instance, "vkCmdSetScissor");
	vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask)LoadFunc(Instance, "vkCmdSetStencilCompareMask");
	vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference)LoadFunc(Instance, "vkCmdSetStencilReference");
	vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask)LoadFunc(Instance, "vkCmdSetStencilWriteMask");
	vkCmdSetViewport = (PFN_vkCmdSetViewport)LoadFunc(Instance, "vkCmdSetViewport");
	vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer)LoadFunc(Instance, "vkCmdUpdateBuffer");
	vkCmdWaitEvents = (PFN_vkCmdWaitEvents)LoadFunc(Instance, "vkCmdWaitEvents");
	vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp)LoadFunc(Instance, "vkCmdWriteTimestamp");
	vkCreateDevice = (PFN_vkCreateDevice)LoadFunc(Instance, "vkCreateDevice");
	vkCreateInstance = (PFN_vkCreateInstance)LoadFunc(Instance, "vkCreateInstance");
	vkEndCommandBuffer = (PFN_vkEndCommandBuffer)LoadFunc(Instance, "vkEndCommandBuffer");
	vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)LoadFunc(Instance, "vkEnumerateDeviceExtensionProperties");
	vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties)LoadFunc(Instance, "vkEnumerateDeviceLayerProperties");
	vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties)LoadFunc(Instance, "vkEnumerateInstanceExtensionProperties");
	vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties)LoadFunc(Instance, "vkEnumerateInstanceLayerProperties");
	vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)LoadFunc(Instance, "vkGetPhysicalDeviceFeatures");
	vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties)LoadFunc(Instance, "vkGetPhysicalDeviceFormatProperties");
	vkGetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties)LoadFunc(Instance, "vkGetPhysicalDeviceImageFormatProperties");
	vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)LoadFunc(Instance, "vkGetPhysicalDeviceMemoryProperties");
	vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)LoadFunc(Instance, "vkGetPhysicalDeviceProperties");
	vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)LoadFunc(Instance, "vkGetPhysicalDeviceQueueFamilyProperties");
	vkGetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties)LoadFunc(Instance, "vkGetPhysicalDeviceSparseImageFormatProperties");
	vkQueueBindSparse = (PFN_vkQueueBindSparse)LoadFunc(Instance, "vkQueueBindSparse");
	vkQueueSubmit = (PFN_vkQueueSubmit)LoadFunc(Instance, "vkQueueSubmit");
	vkQueueWaitIdle = (PFN_vkQueueWaitIdle)LoadFunc(Instance, "vkQueueWaitIdle");
	vkResetCommandBuffer = (PFN_vkResetCommandBuffer)LoadFunc(Instance, "vkResetCommandBuffer");
#endif /*  defined(VK_VERSION_1_0)  */
#if defined(VK_VERSION_1_1)
	vkCmdDispatchBase = (PFN_vkCmdDispatchBase)LoadFunc(Instance, "vkCmdDispatchBase");
	vkCmdSetDeviceMask = (PFN_vkCmdSetDeviceMask)LoadFunc(Instance, "vkCmdSetDeviceMask");
	vkEnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion)LoadFunc(Instance, "vkEnumerateInstanceVersion");
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
#if defined(VK_VERSION_1_2)
	vkCmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2)LoadFunc(Instance, "vkCmdBeginRenderPass2");
	vkCmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount)LoadFunc(Instance, "vkCmdDrawIndexedIndirectCount");
	vkCmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount)LoadFunc(Instance, "vkCmdDrawIndirectCount");
	vkCmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2)LoadFunc(Instance, "vkCmdEndRenderPass2");
	vkCmdNextSubpass2 = (PFN_vkCmdNextSubpass2)LoadFunc(Instance, "vkCmdNextSubpass2");
#endif /*  defined(VK_VERSION_1_2)  */
#if defined(VK_VERSION_1_3)
	vkCmdBeginRendering = (PFN_vkCmdBeginRendering)LoadFunc(Instance, "vkCmdBeginRendering");
	vkCmdBindVertexBuffers2 = (PFN_vkCmdBindVertexBuffers2)LoadFunc(Instance, "vkCmdBindVertexBuffers2");
	vkCmdBlitImage2 = (PFN_vkCmdBlitImage2)LoadFunc(Instance, "vkCmdBlitImage2");
	vkCmdCopyBuffer2 = (PFN_vkCmdCopyBuffer2)LoadFunc(Instance, "vkCmdCopyBuffer2");
	vkCmdCopyBufferToImage2 = (PFN_vkCmdCopyBufferToImage2)LoadFunc(Instance, "vkCmdCopyBufferToImage2");
	vkCmdCopyImage2 = (PFN_vkCmdCopyImage2)LoadFunc(Instance, "vkCmdCopyImage2");
	vkCmdCopyImageToBuffer2 = (PFN_vkCmdCopyImageToBuffer2)LoadFunc(Instance, "vkCmdCopyImageToBuffer2");
	vkCmdEndRendering = (PFN_vkCmdEndRendering)LoadFunc(Instance, "vkCmdEndRendering");
	vkCmdPipelineBarrier2 = (PFN_vkCmdPipelineBarrier2)LoadFunc(Instance, "vkCmdPipelineBarrier2");
	vkCmdResetEvent2 = (PFN_vkCmdResetEvent2)LoadFunc(Instance, "vkCmdResetEvent2");
	vkCmdResolveImage2 = (PFN_vkCmdResolveImage2)LoadFunc(Instance, "vkCmdResolveImage2");
	vkCmdSetCullMode = (PFN_vkCmdSetCullMode)LoadFunc(Instance, "vkCmdSetCullMode");
	vkCmdSetDepthBiasEnable = (PFN_vkCmdSetDepthBiasEnable)LoadFunc(Instance, "vkCmdSetDepthBiasEnable");
	vkCmdSetDepthBoundsTestEnable = (PFN_vkCmdSetDepthBoundsTestEnable)LoadFunc(Instance, "vkCmdSetDepthBoundsTestEnable");
	vkCmdSetDepthCompareOp = (PFN_vkCmdSetDepthCompareOp)LoadFunc(Instance, "vkCmdSetDepthCompareOp");
	vkCmdSetDepthTestEnable = (PFN_vkCmdSetDepthTestEnable)LoadFunc(Instance, "vkCmdSetDepthTestEnable");
	vkCmdSetDepthWriteEnable = (PFN_vkCmdSetDepthWriteEnable)LoadFunc(Instance, "vkCmdSetDepthWriteEnable");
	vkCmdSetEvent2 = (PFN_vkCmdSetEvent2)LoadFunc(Instance, "vkCmdSetEvent2");
	vkCmdSetFrontFace = (PFN_vkCmdSetFrontFace)LoadFunc(Instance, "vkCmdSetFrontFace");
	vkCmdSetPrimitiveRestartEnable = (PFN_vkCmdSetPrimitiveRestartEnable)LoadFunc(Instance, "vkCmdSetPrimitiveRestartEnable");
	vkCmdSetPrimitiveTopology = (PFN_vkCmdSetPrimitiveTopology)LoadFunc(Instance, "vkCmdSetPrimitiveTopology");
	vkCmdSetRasterizerDiscardEnable = (PFN_vkCmdSetRasterizerDiscardEnable)LoadFunc(Instance, "vkCmdSetRasterizerDiscardEnable");
	vkCmdSetScissorWithCount = (PFN_vkCmdSetScissorWithCount)LoadFunc(Instance, "vkCmdSetScissorWithCount");
	vkCmdSetStencilOp = (PFN_vkCmdSetStencilOp)LoadFunc(Instance, "vkCmdSetStencilOp");
	vkCmdSetStencilTestEnable = (PFN_vkCmdSetStencilTestEnable)LoadFunc(Instance, "vkCmdSetStencilTestEnable");
	vkCmdSetViewportWithCount = (PFN_vkCmdSetViewportWithCount)LoadFunc(Instance, "vkCmdSetViewportWithCount");
	vkCmdWaitEvents2 = (PFN_vkCmdWaitEvents2)LoadFunc(Instance, "vkCmdWaitEvents2");
	vkCmdWriteTimestamp2 = (PFN_vkCmdWriteTimestamp2)LoadFunc(Instance, "vkCmdWriteTimestamp2");
	vkGetPhysicalDeviceToolProperties = (PFN_vkGetPhysicalDeviceToolProperties)LoadFunc(Instance, "vkGetPhysicalDeviceToolProperties");
	vkQueueSubmit2 = (PFN_vkQueueSubmit2)LoadFunc(Instance, "vkQueueSubmit2");
#endif /*  defined(VK_VERSION_1_3)  */
#if defined(VK_AMDX_shader_enqueue)
	vkCmdDispatchGraphAMDX = (PFN_vkCmdDispatchGraphAMDX)LoadFunc(Instance, "vkCmdDispatchGraphAMDX");
	vkCmdDispatchGraphIndirectAMDX = (PFN_vkCmdDispatchGraphIndirectAMDX)LoadFunc(Instance, "vkCmdDispatchGraphIndirectAMDX");
	vkCmdDispatchGraphIndirectCountAMDX = (PFN_vkCmdDispatchGraphIndirectCountAMDX)LoadFunc(Instance, "vkCmdDispatchGraphIndirectCountAMDX");
	vkCmdInitializeGraphScratchMemoryAMDX = (PFN_vkCmdInitializeGraphScratchMemoryAMDX)LoadFunc(Instance, "vkCmdInitializeGraphScratchMemoryAMDX");
#endif /*  defined(VK_AMDX_shader_enqueue)  */
#if defined(VK_AMD_buffer_marker)
	vkCmdWriteBufferMarkerAMD = (PFN_vkCmdWriteBufferMarkerAMD)LoadFunc(Instance, "vkCmdWriteBufferMarkerAMD");
#endif /*  defined(VK_AMD_buffer_marker)  */
#if defined(VK_AMD_draw_indirect_count)
	vkCmdDrawIndexedIndirectCountAMD = (PFN_vkCmdDrawIndexedIndirectCountAMD)LoadFunc(Instance, "vkCmdDrawIndexedIndirectCountAMD");
	vkCmdDrawIndirectCountAMD = (PFN_vkCmdDrawIndirectCountAMD)LoadFunc(Instance, "vkCmdDrawIndirectCountAMD");
#endif /*  defined(VK_AMD_draw_indirect_count)  */
#if defined(VK_EXT_acquire_drm_display)
	vkAcquireDrmDisplayEXT = (PFN_vkAcquireDrmDisplayEXT)LoadFunc(Instance, "vkAcquireDrmDisplayEXT");
	vkGetDrmDisplayEXT = (PFN_vkGetDrmDisplayEXT)LoadFunc(Instance, "vkGetDrmDisplayEXT");
#endif /*  defined(VK_EXT_acquire_drm_display)  */
#if defined(VK_EXT_acquire_xlib_display)
	vkAcquireXlibDisplayEXT = (PFN_vkAcquireXlibDisplayEXT)LoadFunc(Instance, "vkAcquireXlibDisplayEXT");
	vkGetRandROutputDisplayEXT = (PFN_vkGetRandROutputDisplayEXT)LoadFunc(Instance, "vkGetRandROutputDisplayEXT");
#endif /*  defined(VK_EXT_acquire_xlib_display)  */
#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
	vkCmdSetAttachmentFeedbackLoopEnableEXT = (PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT)LoadFunc(Instance, "vkCmdSetAttachmentFeedbackLoopEnableEXT");
#endif /*  defined(VK_EXT_attachment_feedback_loop_dynamic_state)  */
#if defined(VK_EXT_calibrated_timestamps)
	vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = (PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT)LoadFunc(Instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT");
#endif /*  defined(VK_EXT_calibrated_timestamps)  */
#if defined(VK_EXT_color_write_enable)
	vkCmdSetColorWriteEnableEXT = (PFN_vkCmdSetColorWriteEnableEXT)LoadFunc(Instance, "vkCmdSetColorWriteEnableEXT");
#endif /*  defined(VK_EXT_color_write_enable)  */
#if defined(VK_EXT_conditional_rendering)
	vkCmdBeginConditionalRenderingEXT = (PFN_vkCmdBeginConditionalRenderingEXT)LoadFunc(Instance, "vkCmdBeginConditionalRenderingEXT");
	vkCmdEndConditionalRenderingEXT = (PFN_vkCmdEndConditionalRenderingEXT)LoadFunc(Instance, "vkCmdEndConditionalRenderingEXT");
#endif /*  defined(VK_EXT_conditional_rendering)  */
#if defined(VK_EXT_debug_marker)
	vkCmdDebugMarkerBeginEXT = (PFN_vkCmdDebugMarkerBeginEXT)LoadFunc(Instance, "vkCmdDebugMarkerBeginEXT");
	vkCmdDebugMarkerEndEXT = (PFN_vkCmdDebugMarkerEndEXT)LoadFunc(Instance, "vkCmdDebugMarkerEndEXT");
	vkCmdDebugMarkerInsertEXT = (PFN_vkCmdDebugMarkerInsertEXT)LoadFunc(Instance, "vkCmdDebugMarkerInsertEXT");
#endif /*  defined(VK_EXT_debug_marker)  */
#if defined(VK_EXT_debug_utils)
	vkCmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT)LoadFunc(Instance, "vkCmdBeginDebugUtilsLabelEXT");
	vkCmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT)LoadFunc(Instance, "vkCmdEndDebugUtilsLabelEXT");
	vkCmdInsertDebugUtilsLabelEXT = (PFN_vkCmdInsertDebugUtilsLabelEXT)LoadFunc(Instance, "vkCmdInsertDebugUtilsLabelEXT");
	vkQueueBeginDebugUtilsLabelEXT = (PFN_vkQueueBeginDebugUtilsLabelEXT)LoadFunc(Instance, "vkQueueBeginDebugUtilsLabelEXT");
	vkQueueEndDebugUtilsLabelEXT = (PFN_vkQueueEndDebugUtilsLabelEXT)LoadFunc(Instance, "vkQueueEndDebugUtilsLabelEXT");
	vkQueueInsertDebugUtilsLabelEXT = (PFN_vkQueueInsertDebugUtilsLabelEXT)LoadFunc(Instance, "vkQueueInsertDebugUtilsLabelEXT");
	vkSetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT)LoadFunc(Instance, "vkSetDebugUtilsObjectNameEXT");
	vkSetDebugUtilsObjectTagEXT = (PFN_vkSetDebugUtilsObjectTagEXT)LoadFunc(Instance, "vkSetDebugUtilsObjectTagEXT");
#endif /*  defined(VK_EXT_debug_utils)  */
#if defined(VK_EXT_depth_bias_control)
	vkCmdSetDepthBias2EXT = (PFN_vkCmdSetDepthBias2EXT)LoadFunc(Instance, "vkCmdSetDepthBias2EXT");
#endif /*  defined(VK_EXT_depth_bias_control)  */
#if defined(VK_EXT_descriptor_buffer)
	vkCmdBindDescriptorBufferEmbeddedSamplersEXT = (PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT)LoadFunc(Instance, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT");
	vkCmdBindDescriptorBuffersEXT = (PFN_vkCmdBindDescriptorBuffersEXT)LoadFunc(Instance, "vkCmdBindDescriptorBuffersEXT");
	vkCmdSetDescriptorBufferOffsetsEXT = (PFN_vkCmdSetDescriptorBufferOffsetsEXT)LoadFunc(Instance, "vkCmdSetDescriptorBufferOffsetsEXT");
#endif /*  defined(VK_EXT_descriptor_buffer)  */
#if defined(VK_EXT_direct_mode_display)
	vkReleaseDisplayEXT = (PFN_vkReleaseDisplayEXT)LoadFunc(Instance, "vkReleaseDisplayEXT");
#endif /*  defined(VK_EXT_direct_mode_display)  */
#if defined(VK_EXT_directfb_surface)
	vkGetPhysicalDeviceDirectFBPresentationSupportEXT = (PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT)LoadFunc(Instance, "vkGetPhysicalDeviceDirectFBPresentationSupportEXT");
#endif /*  defined(VK_EXT_directfb_surface)  */
#if defined(VK_EXT_discard_rectangles)
	vkCmdSetDiscardRectangleEXT = (PFN_vkCmdSetDiscardRectangleEXT)LoadFunc(Instance, "vkCmdSetDiscardRectangleEXT");
#endif /*  defined(VK_EXT_discard_rectangles)  */
#if defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2
	vkCmdSetDiscardRectangleEnableEXT = (PFN_vkCmdSetDiscardRectangleEnableEXT)LoadFunc(Instance, "vkCmdSetDiscardRectangleEnableEXT");
	vkCmdSetDiscardRectangleModeEXT = (PFN_vkCmdSetDiscardRectangleModeEXT)LoadFunc(Instance, "vkCmdSetDiscardRectangleModeEXT");
#endif /*  defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2  */
#if defined(VK_EXT_display_surface_counter)
	vkGetPhysicalDeviceSurfaceCapabilities2EXT = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT)LoadFunc(Instance, "vkGetPhysicalDeviceSurfaceCapabilities2EXT");
#endif /*  defined(VK_EXT_display_surface_counter)  */
#if defined(VK_EXT_full_screen_exclusive)
	vkGetPhysicalDeviceSurfacePresentModes2EXT = (PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)LoadFunc(Instance, "vkGetPhysicalDeviceSurfacePresentModes2EXT");
#endif /*  defined(VK_EXT_full_screen_exclusive)  */
#if defined(VK_EXT_line_rasterization)
	vkCmdSetLineStippleEXT = (PFN_vkCmdSetLineStippleEXT)LoadFunc(Instance, "vkCmdSetLineStippleEXT");
#endif /*  defined(VK_EXT_line_rasterization)  */
#if defined(VK_EXT_mesh_shader)
	vkCmdDrawMeshTasksEXT = (PFN_vkCmdDrawMeshTasksEXT)LoadFunc(Instance, "vkCmdDrawMeshTasksEXT");
	vkCmdDrawMeshTasksIndirectCountEXT = (PFN_vkCmdDrawMeshTasksIndirectCountEXT)LoadFunc(Instance, "vkCmdDrawMeshTasksIndirectCountEXT");
	vkCmdDrawMeshTasksIndirectEXT = (PFN_vkCmdDrawMeshTasksIndirectEXT)LoadFunc(Instance, "vkCmdDrawMeshTasksIndirectEXT");
#endif /*  defined(VK_EXT_mesh_shader)  */
#if defined(VK_EXT_multi_draw)
	vkCmdDrawMultiEXT = (PFN_vkCmdDrawMultiEXT)LoadFunc(Instance, "vkCmdDrawMultiEXT");
	vkCmdDrawMultiIndexedEXT = (PFN_vkCmdDrawMultiIndexedEXT)LoadFunc(Instance, "vkCmdDrawMultiIndexedEXT");
#endif /*  defined(VK_EXT_multi_draw)  */
#if defined(VK_EXT_opacity_micromap)
	vkCmdBuildMicromapsEXT = (PFN_vkCmdBuildMicromapsEXT)LoadFunc(Instance, "vkCmdBuildMicromapsEXT");
	vkCmdCopyMemoryToMicromapEXT = (PFN_vkCmdCopyMemoryToMicromapEXT)LoadFunc(Instance, "vkCmdCopyMemoryToMicromapEXT");
	vkCmdCopyMicromapEXT = (PFN_vkCmdCopyMicromapEXT)LoadFunc(Instance, "vkCmdCopyMicromapEXT");
	vkCmdCopyMicromapToMemoryEXT = (PFN_vkCmdCopyMicromapToMemoryEXT)LoadFunc(Instance, "vkCmdCopyMicromapToMemoryEXT");
	vkCmdWriteMicromapsPropertiesEXT = (PFN_vkCmdWriteMicromapsPropertiesEXT)LoadFunc(Instance, "vkCmdWriteMicromapsPropertiesEXT");
#endif /*  defined(VK_EXT_opacity_micromap)  */
#if defined(VK_EXT_sample_locations)
	vkCmdSetSampleLocationsEXT = (PFN_vkCmdSetSampleLocationsEXT)LoadFunc(Instance, "vkCmdSetSampleLocationsEXT");
	vkGetPhysicalDeviceMultisamplePropertiesEXT = (PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT)LoadFunc(Instance, "vkGetPhysicalDeviceMultisamplePropertiesEXT");
#endif /*  defined(VK_EXT_sample_locations)  */
#if defined(VK_EXT_shader_object)
	vkCmdBindShadersEXT = (PFN_vkCmdBindShadersEXT)LoadFunc(Instance, "vkCmdBindShadersEXT");
#endif /*  defined(VK_EXT_shader_object)  */
#if defined(VK_EXT_tooling_info)
	vkGetPhysicalDeviceToolPropertiesEXT = (PFN_vkGetPhysicalDeviceToolPropertiesEXT)LoadFunc(Instance, "vkGetPhysicalDeviceToolPropertiesEXT");
#endif /*  defined(VK_EXT_tooling_info)  */
#if defined(VK_EXT_transform_feedback)
	vkCmdBeginQueryIndexedEXT = (PFN_vkCmdBeginQueryIndexedEXT)LoadFunc(Instance, "vkCmdBeginQueryIndexedEXT");
	vkCmdBeginTransformFeedbackEXT = (PFN_vkCmdBeginTransformFeedbackEXT)LoadFunc(Instance, "vkCmdBeginTransformFeedbackEXT");
	vkCmdBindTransformFeedbackBuffersEXT = (PFN_vkCmdBindTransformFeedbackBuffersEXT)LoadFunc(Instance, "vkCmdBindTransformFeedbackBuffersEXT");
	vkCmdDrawIndirectByteCountEXT = (PFN_vkCmdDrawIndirectByteCountEXT)LoadFunc(Instance, "vkCmdDrawIndirectByteCountEXT");
	vkCmdEndQueryIndexedEXT = (PFN_vkCmdEndQueryIndexedEXT)LoadFunc(Instance, "vkCmdEndQueryIndexedEXT");
	vkCmdEndTransformFeedbackEXT = (PFN_vkCmdEndTransformFeedbackEXT)LoadFunc(Instance, "vkCmdEndTransformFeedbackEXT");
#endif /*  defined(VK_EXT_transform_feedback)  */
#if defined(VK_HUAWEI_cluster_culling_shader)
	vkCmdDrawClusterHUAWEI = (PFN_vkCmdDrawClusterHUAWEI)LoadFunc(Instance, "vkCmdDrawClusterHUAWEI");
	vkCmdDrawClusterIndirectHUAWEI = (PFN_vkCmdDrawClusterIndirectHUAWEI)LoadFunc(Instance, "vkCmdDrawClusterIndirectHUAWEI");
#endif /*  defined(VK_HUAWEI_cluster_culling_shader)  */
#if defined(VK_HUAWEI_invocation_mask)
	vkCmdBindInvocationMaskHUAWEI = (PFN_vkCmdBindInvocationMaskHUAWEI)LoadFunc(Instance, "vkCmdBindInvocationMaskHUAWEI");
#endif /*  defined(VK_HUAWEI_invocation_mask)  */
#if defined(VK_HUAWEI_subpass_shading)
	vkCmdSubpassShadingHUAWEI = (PFN_vkCmdSubpassShadingHUAWEI)LoadFunc(Instance, "vkCmdSubpassShadingHUAWEI");
#endif /*  defined(VK_HUAWEI_subpass_shading)  */
#if defined(VK_INTEL_performance_query)
	vkCmdSetPerformanceMarkerINTEL = (PFN_vkCmdSetPerformanceMarkerINTEL)LoadFunc(Instance, "vkCmdSetPerformanceMarkerINTEL");
	vkCmdSetPerformanceOverrideINTEL = (PFN_vkCmdSetPerformanceOverrideINTEL)LoadFunc(Instance, "vkCmdSetPerformanceOverrideINTEL");
	vkCmdSetPerformanceStreamMarkerINTEL = (PFN_vkCmdSetPerformanceStreamMarkerINTEL)LoadFunc(Instance, "vkCmdSetPerformanceStreamMarkerINTEL");
	vkQueueSetPerformanceConfigurationINTEL = (PFN_vkQueueSetPerformanceConfigurationINTEL)LoadFunc(Instance, "vkQueueSetPerformanceConfigurationINTEL");
#endif /*  defined(VK_INTEL_performance_query)  */
#if defined(VK_KHR_acceleration_structure)
	vkCmdBuildAccelerationStructuresIndirectKHR = (PFN_vkCmdBuildAccelerationStructuresIndirectKHR)LoadFunc(Instance, "vkCmdBuildAccelerationStructuresIndirectKHR");
	vkCmdBuildAccelerationStructuresKHR = (PFN_vkCmdBuildAccelerationStructuresKHR)LoadFunc(Instance, "vkCmdBuildAccelerationStructuresKHR");
	vkCmdCopyAccelerationStructureKHR = (PFN_vkCmdCopyAccelerationStructureKHR)LoadFunc(Instance, "vkCmdCopyAccelerationStructureKHR");
	vkCmdCopyAccelerationStructureToMemoryKHR = (PFN_vkCmdCopyAccelerationStructureToMemoryKHR)LoadFunc(Instance, "vkCmdCopyAccelerationStructureToMemoryKHR");
	vkCmdCopyMemoryToAccelerationStructureKHR = (PFN_vkCmdCopyMemoryToAccelerationStructureKHR)LoadFunc(Instance, "vkCmdCopyMemoryToAccelerationStructureKHR");
	vkCmdWriteAccelerationStructuresPropertiesKHR = (PFN_vkCmdWriteAccelerationStructuresPropertiesKHR)LoadFunc(Instance, "vkCmdWriteAccelerationStructuresPropertiesKHR");
#endif /*  defined(VK_KHR_acceleration_structure)  */
#if defined(VK_KHR_calibrated_timestamps)
	vkGetPhysicalDeviceCalibrateableTimeDomainsKHR = (PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR)LoadFunc(Instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR");
#endif /*  defined(VK_KHR_calibrated_timestamps)  */
#if defined(VK_KHR_cooperative_matrix)
	vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR = (PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR");
#endif /*  defined(VK_KHR_cooperative_matrix)  */
#if defined(VK_KHR_copy_commands2)
	vkCmdBlitImage2KHR = (PFN_vkCmdBlitImage2KHR)LoadFunc(Instance, "vkCmdBlitImage2KHR");
	vkCmdCopyBuffer2KHR = (PFN_vkCmdCopyBuffer2KHR)LoadFunc(Instance, "vkCmdCopyBuffer2KHR");
	vkCmdCopyBufferToImage2KHR = (PFN_vkCmdCopyBufferToImage2KHR)LoadFunc(Instance, "vkCmdCopyBufferToImage2KHR");
	vkCmdCopyImage2KHR = (PFN_vkCmdCopyImage2KHR)LoadFunc(Instance, "vkCmdCopyImage2KHR");
	vkCmdCopyImageToBuffer2KHR = (PFN_vkCmdCopyImageToBuffer2KHR)LoadFunc(Instance, "vkCmdCopyImageToBuffer2KHR");
	vkCmdResolveImage2KHR = (PFN_vkCmdResolveImage2KHR)LoadFunc(Instance, "vkCmdResolveImage2KHR");
#endif /*  defined(VK_KHR_copy_commands2)  */
#if defined(VK_KHR_create_renderpass2)
	vkCmdBeginRenderPass2KHR = (PFN_vkCmdBeginRenderPass2KHR)LoadFunc(Instance, "vkCmdBeginRenderPass2KHR");
	vkCmdEndRenderPass2KHR = (PFN_vkCmdEndRenderPass2KHR)LoadFunc(Instance, "vkCmdEndRenderPass2KHR");
	vkCmdNextSubpass2KHR = (PFN_vkCmdNextSubpass2KHR)LoadFunc(Instance, "vkCmdNextSubpass2KHR");
#endif /*  defined(VK_KHR_create_renderpass2)  */
#if defined(VK_KHR_device_group)
	vkCmdDispatchBaseKHR = (PFN_vkCmdDispatchBaseKHR)LoadFunc(Instance, "vkCmdDispatchBaseKHR");
	vkCmdSetDeviceMaskKHR = (PFN_vkCmdSetDeviceMaskKHR)LoadFunc(Instance, "vkCmdSetDeviceMaskKHR");
#endif /*  defined(VK_KHR_device_group)  */
#if defined(VK_KHR_display)
	vkCreateDisplayModeKHR = (PFN_vkCreateDisplayModeKHR)LoadFunc(Instance, "vkCreateDisplayModeKHR");
	vkGetDisplayModePropertiesKHR = (PFN_vkGetDisplayModePropertiesKHR)LoadFunc(Instance, "vkGetDisplayModePropertiesKHR");
	vkGetDisplayPlaneCapabilitiesKHR = (PFN_vkGetDisplayPlaneCapabilitiesKHR)LoadFunc(Instance, "vkGetDisplayPlaneCapabilitiesKHR");
	vkGetDisplayPlaneSupportedDisplaysKHR = (PFN_vkGetDisplayPlaneSupportedDisplaysKHR)LoadFunc(Instance, "vkGetDisplayPlaneSupportedDisplaysKHR");
	vkGetPhysicalDeviceDisplayPlanePropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR");
	vkGetPhysicalDeviceDisplayPropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceDisplayPropertiesKHR");
#endif /*  defined(VK_KHR_display)  */
#if defined(VK_KHR_draw_indirect_count)
	vkCmdDrawIndexedIndirectCountKHR = (PFN_vkCmdDrawIndexedIndirectCountKHR)LoadFunc(Instance, "vkCmdDrawIndexedIndirectCountKHR");
	vkCmdDrawIndirectCountKHR = (PFN_vkCmdDrawIndirectCountKHR)LoadFunc(Instance, "vkCmdDrawIndirectCountKHR");
#endif /*  defined(VK_KHR_draw_indirect_count)  */
#if defined(VK_KHR_dynamic_rendering)
	vkCmdBeginRenderingKHR = (PFN_vkCmdBeginRenderingKHR)LoadFunc(Instance, "vkCmdBeginRenderingKHR");
	vkCmdEndRenderingKHR = (PFN_vkCmdEndRenderingKHR)LoadFunc(Instance, "vkCmdEndRenderingKHR");
#endif /*  defined(VK_KHR_dynamic_rendering)  */
#if defined(VK_KHR_dynamic_rendering_local_read)
	vkCmdSetRenderingAttachmentLocationsKHR = (PFN_vkCmdSetRenderingAttachmentLocationsKHR)LoadFunc(Instance, "vkCmdSetRenderingAttachmentLocationsKHR");
	vkCmdSetRenderingInputAttachmentIndicesKHR = (PFN_vkCmdSetRenderingInputAttachmentIndicesKHR)LoadFunc(Instance, "vkCmdSetRenderingInputAttachmentIndicesKHR");
#endif /*  defined(VK_KHR_dynamic_rendering_local_read)  */
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
	vkCmdSetFragmentShadingRateKHR = (PFN_vkCmdSetFragmentShadingRateKHR)LoadFunc(Instance, "vkCmdSetFragmentShadingRateKHR");
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
#if defined(VK_KHR_line_rasterization)
	vkCmdSetLineStippleKHR = (PFN_vkCmdSetLineStippleKHR)LoadFunc(Instance, "vkCmdSetLineStippleKHR");
#endif /*  defined(VK_KHR_line_rasterization)  */
#if defined(VK_KHR_maintenance5)
	vkCmdBindIndexBuffer2KHR = (PFN_vkCmdBindIndexBuffer2KHR)LoadFunc(Instance, "vkCmdBindIndexBuffer2KHR");
#endif /*  defined(VK_KHR_maintenance5)  */
#if defined(VK_KHR_maintenance6)
	vkCmdBindDescriptorSets2KHR = (PFN_vkCmdBindDescriptorSets2KHR)LoadFunc(Instance, "vkCmdBindDescriptorSets2KHR");
	vkCmdPushConstants2KHR = (PFN_vkCmdPushConstants2KHR)LoadFunc(Instance, "vkCmdPushConstants2KHR");
#endif /*  defined(VK_KHR_maintenance6)  */
#if defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)
	vkCmdPushDescriptorSet2KHR = (PFN_vkCmdPushDescriptorSet2KHR)LoadFunc(Instance, "vkCmdPushDescriptorSet2KHR");
	vkCmdPushDescriptorSetWithTemplate2KHR = (PFN_vkCmdPushDescriptorSetWithTemplate2KHR)LoadFunc(Instance, "vkCmdPushDescriptorSetWithTemplate2KHR");
#endif /*  defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)  */
#if defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)
	vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = (PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT)LoadFunc(Instance, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT");
	vkCmdSetDescriptorBufferOffsets2EXT = (PFN_vkCmdSetDescriptorBufferOffsets2EXT)LoadFunc(Instance, "vkCmdSetDescriptorBufferOffsets2EXT");
#endif /*  defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)  */
#if defined(VK_KHR_performance_query)
	vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = (PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR)LoadFunc(Instance, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
	vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = (PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");
#endif /*  defined(VK_KHR_performance_query)  */
#if defined(VK_KHR_push_descriptor)
	vkCmdPushDescriptorSetKHR = (PFN_vkCmdPushDescriptorSetKHR)LoadFunc(Instance, "vkCmdPushDescriptorSetKHR");
#endif /*  defined(VK_KHR_push_descriptor)  */
#if defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)
	vkCmdTraceRaysIndirect2KHR = (PFN_vkCmdTraceRaysIndirect2KHR)LoadFunc(Instance, "vkCmdTraceRaysIndirect2KHR");
#endif /*  defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)  */
#if defined(VK_KHR_ray_tracing_pipeline)
	vkCmdSetRayTracingPipelineStackSizeKHR = (PFN_vkCmdSetRayTracingPipelineStackSizeKHR)LoadFunc(Instance, "vkCmdSetRayTracingPipelineStackSizeKHR");
	vkCmdTraceRaysIndirectKHR = (PFN_vkCmdTraceRaysIndirectKHR)LoadFunc(Instance, "vkCmdTraceRaysIndirectKHR");
	vkCmdTraceRaysKHR = (PFN_vkCmdTraceRaysKHR)LoadFunc(Instance, "vkCmdTraceRaysKHR");
#endif /*  defined(VK_KHR_ray_tracing_pipeline)  */
#if defined(VK_KHR_surface)
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)LoadFunc(Instance, "vkGetPhysicalDeviceSurfaceFormatsKHR");
	vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceSurfacePresentModesKHR");
	vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)LoadFunc(Instance, "vkGetPhysicalDeviceSurfaceSupportKHR");
#endif /*  defined(VK_KHR_surface)  */
#if defined(VK_KHR_swapchain)
	vkQueuePresentKHR = (PFN_vkQueuePresentKHR)LoadFunc(Instance, "vkQueuePresentKHR");
#endif /*  defined(VK_KHR_swapchain)  */
#if defined(VK_KHR_synchronization2)
	vkCmdPipelineBarrier2KHR = (PFN_vkCmdPipelineBarrier2KHR)LoadFunc(Instance, "vkCmdPipelineBarrier2KHR");
	vkCmdResetEvent2KHR = (PFN_vkCmdResetEvent2KHR)LoadFunc(Instance, "vkCmdResetEvent2KHR");
	vkCmdSetEvent2KHR = (PFN_vkCmdSetEvent2KHR)LoadFunc(Instance, "vkCmdSetEvent2KHR");
	vkCmdWaitEvents2KHR = (PFN_vkCmdWaitEvents2KHR)LoadFunc(Instance, "vkCmdWaitEvents2KHR");
	vkCmdWriteTimestamp2KHR = (PFN_vkCmdWriteTimestamp2KHR)LoadFunc(Instance, "vkCmdWriteTimestamp2KHR");
	vkQueueSubmit2KHR = (PFN_vkQueueSubmit2KHR)LoadFunc(Instance, "vkQueueSubmit2KHR");
#endif /*  defined(VK_KHR_synchronization2)  */
#if defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)
	vkCmdWriteBufferMarker2AMD = (PFN_vkCmdWriteBufferMarker2AMD)LoadFunc(Instance, "vkCmdWriteBufferMarker2AMD");
#endif /*  defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)  */
#if defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)
	vkGetQueueCheckpointData2NV = (PFN_vkGetQueueCheckpointData2NV)LoadFunc(Instance, "vkGetQueueCheckpointData2NV");
#endif /*  defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)  */
#if defined(VK_KHR_video_decode_queue)
	vkCmdDecodeVideoKHR = (PFN_vkCmdDecodeVideoKHR)LoadFunc(Instance, "vkCmdDecodeVideoKHR");
#endif /*  defined(VK_KHR_video_decode_queue)  */
#if defined(VK_KHR_video_encode_queue)
	vkCmdEncodeVideoKHR = (PFN_vkCmdEncodeVideoKHR)LoadFunc(Instance, "vkCmdEncodeVideoKHR");
	vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR = (PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR");
#endif /*  defined(VK_KHR_video_encode_queue)  */
#if defined(VK_KHR_video_queue)
	vkCmdBeginVideoCodingKHR = (PFN_vkCmdBeginVideoCodingKHR)LoadFunc(Instance, "vkCmdBeginVideoCodingKHR");
	vkCmdControlVideoCodingKHR = (PFN_vkCmdControlVideoCodingKHR)LoadFunc(Instance, "vkCmdControlVideoCodingKHR");
	vkCmdEndVideoCodingKHR = (PFN_vkCmdEndVideoCodingKHR)LoadFunc(Instance, "vkCmdEndVideoCodingKHR");
	vkGetPhysicalDeviceVideoCapabilitiesKHR = (PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceVideoCapabilitiesKHR");
	vkGetPhysicalDeviceVideoFormatPropertiesKHR = (PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR)LoadFunc(Instance, "vkGetPhysicalDeviceVideoFormatPropertiesKHR");
#endif /*  defined(VK_KHR_video_queue)  */
#if defined(VK_KHR_wayland_surface)
	vkGetPhysicalDeviceWaylandPresentationSupportKHR = (PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)LoadFunc(Instance, "vkGetPhysicalDeviceWaylandPresentationSupportKHR");
#endif /*  defined(VK_KHR_wayland_surface)  */
#if defined(VK_KHR_win32_surface)
	vkGetPhysicalDeviceWin32PresentationSupportKHR = (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)LoadFunc(Instance, "vkGetPhysicalDeviceWin32PresentationSupportKHR");
#endif /*  defined(VK_KHR_win32_surface)  */
#if defined(VK_KHR_xcb_surface)
	vkGetPhysicalDeviceXcbPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)LoadFunc(Instance, "vkGetPhysicalDeviceXcbPresentationSupportKHR");
#endif /*  defined(VK_KHR_xcb_surface)  */
#if defined(VK_KHR_xlib_surface)
	vkGetPhysicalDeviceXlibPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)LoadFunc(Instance, "vkGetPhysicalDeviceXlibPresentationSupportKHR");
#endif /*  defined(VK_KHR_xlib_surface)  */
#if defined(VK_NVX_binary_import)
	vkCmdCuLaunchKernelNVX = (PFN_vkCmdCuLaunchKernelNVX)LoadFunc(Instance, "vkCmdCuLaunchKernelNVX");
#endif /*  defined(VK_NVX_binary_import)  */
#if defined(VK_NV_acquire_winrt_display)
	vkAcquireWinrtDisplayNV = (PFN_vkAcquireWinrtDisplayNV)LoadFunc(Instance, "vkAcquireWinrtDisplayNV");
	vkGetWinrtDisplayNV = (PFN_vkGetWinrtDisplayNV)LoadFunc(Instance, "vkGetWinrtDisplayNV");
#endif /*  defined(VK_NV_acquire_winrt_display)  */
#if defined(VK_NV_clip_space_w_scaling)
	vkCmdSetViewportWScalingNV = (PFN_vkCmdSetViewportWScalingNV)LoadFunc(Instance, "vkCmdSetViewportWScalingNV");
#endif /*  defined(VK_NV_clip_space_w_scaling)  */
#if defined(VK_NV_cooperative_matrix)
	vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = (PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV)LoadFunc(Instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV");
#endif /*  defined(VK_NV_cooperative_matrix)  */
#if defined(VK_NV_copy_memory_indirect)
	vkCmdCopyMemoryIndirectNV = (PFN_vkCmdCopyMemoryIndirectNV)LoadFunc(Instance, "vkCmdCopyMemoryIndirectNV");
	vkCmdCopyMemoryToImageIndirectNV = (PFN_vkCmdCopyMemoryToImageIndirectNV)LoadFunc(Instance, "vkCmdCopyMemoryToImageIndirectNV");
#endif /*  defined(VK_NV_copy_memory_indirect)  */
#if defined(VK_NV_coverage_reduction_mode)
	vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = (PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV)LoadFunc(Instance, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV");
#endif /*  defined(VK_NV_coverage_reduction_mode)  */
#if defined(VK_NV_cuda_kernel_launch)
	vkCmdCudaLaunchKernelNV = (PFN_vkCmdCudaLaunchKernelNV)LoadFunc(Instance, "vkCmdCudaLaunchKernelNV");
#endif /*  defined(VK_NV_cuda_kernel_launch)  */
#if defined(VK_NV_device_diagnostic_checkpoints)
	vkCmdSetCheckpointNV = (PFN_vkCmdSetCheckpointNV)LoadFunc(Instance, "vkCmdSetCheckpointNV");
	vkGetQueueCheckpointDataNV = (PFN_vkGetQueueCheckpointDataNV)LoadFunc(Instance, "vkGetQueueCheckpointDataNV");
#endif /*  defined(VK_NV_device_diagnostic_checkpoints)  */
#if defined(VK_NV_device_generated_commands)
	vkCmdBindPipelineShaderGroupNV = (PFN_vkCmdBindPipelineShaderGroupNV)LoadFunc(Instance, "vkCmdBindPipelineShaderGroupNV");
	vkCmdExecuteGeneratedCommandsNV = (PFN_vkCmdExecuteGeneratedCommandsNV)LoadFunc(Instance, "vkCmdExecuteGeneratedCommandsNV");
	vkCmdPreprocessGeneratedCommandsNV = (PFN_vkCmdPreprocessGeneratedCommandsNV)LoadFunc(Instance, "vkCmdPreprocessGeneratedCommandsNV");
#endif /*  defined(VK_NV_device_generated_commands)  */
#if defined(VK_NV_device_generated_commands_compute)
	vkCmdUpdatePipelineIndirectBufferNV = (PFN_vkCmdUpdatePipelineIndirectBufferNV)LoadFunc(Instance, "vkCmdUpdatePipelineIndirectBufferNV");
#endif /*  defined(VK_NV_device_generated_commands_compute)  */
#if defined(VK_NV_external_memory_capabilities)
	vkGetPhysicalDeviceExternalImageFormatPropertiesNV = (PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV)LoadFunc(Instance, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV");
#endif /*  defined(VK_NV_external_memory_capabilities)  */
#if defined(VK_NV_fragment_shading_rate_enums)
	vkCmdSetFragmentShadingRateEnumNV = (PFN_vkCmdSetFragmentShadingRateEnumNV)LoadFunc(Instance, "vkCmdSetFragmentShadingRateEnumNV");
#endif /*  defined(VK_NV_fragment_shading_rate_enums)  */
#if defined(VK_NV_low_latency2)
	vkQueueNotifyOutOfBandNV = (PFN_vkQueueNotifyOutOfBandNV)LoadFunc(Instance, "vkQueueNotifyOutOfBandNV");
#endif /*  defined(VK_NV_low_latency2)  */
#if defined(VK_NV_memory_decompression)
	vkCmdDecompressMemoryIndirectCountNV = (PFN_vkCmdDecompressMemoryIndirectCountNV)LoadFunc(Instance, "vkCmdDecompressMemoryIndirectCountNV");
	vkCmdDecompressMemoryNV = (PFN_vkCmdDecompressMemoryNV)LoadFunc(Instance, "vkCmdDecompressMemoryNV");
#endif /*  defined(VK_NV_memory_decompression)  */
#if defined(VK_NV_mesh_shader)
	vkCmdDrawMeshTasksIndirectCountNV = (PFN_vkCmdDrawMeshTasksIndirectCountNV)LoadFunc(Instance, "vkCmdDrawMeshTasksIndirectCountNV");
	vkCmdDrawMeshTasksIndirectNV = (PFN_vkCmdDrawMeshTasksIndirectNV)LoadFunc(Instance, "vkCmdDrawMeshTasksIndirectNV");
	vkCmdDrawMeshTasksNV = (PFN_vkCmdDrawMeshTasksNV)LoadFunc(Instance, "vkCmdDrawMeshTasksNV");
#endif /*  defined(VK_NV_mesh_shader)  */
#if defined(VK_NV_optical_flow)
	vkCmdOpticalFlowExecuteNV = (PFN_vkCmdOpticalFlowExecuteNV)LoadFunc(Instance, "vkCmdOpticalFlowExecuteNV");
	vkGetPhysicalDeviceOpticalFlowImageFormatsNV = (PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV)LoadFunc(Instance, "vkGetPhysicalDeviceOpticalFlowImageFormatsNV");
#endif /*  defined(VK_NV_optical_flow)  */
#if defined(VK_NV_ray_tracing)
	vkCmdBuildAccelerationStructureNV = (PFN_vkCmdBuildAccelerationStructureNV)LoadFunc(Instance, "vkCmdBuildAccelerationStructureNV");
	vkCmdCopyAccelerationStructureNV = (PFN_vkCmdCopyAccelerationStructureNV)LoadFunc(Instance, "vkCmdCopyAccelerationStructureNV");
	vkCmdTraceRaysNV = (PFN_vkCmdTraceRaysNV)LoadFunc(Instance, "vkCmdTraceRaysNV");
	vkCmdWriteAccelerationStructuresPropertiesNV = (PFN_vkCmdWriteAccelerationStructuresPropertiesNV)LoadFunc(Instance, "vkCmdWriteAccelerationStructuresPropertiesNV");
#endif /*  defined(VK_NV_ray_tracing)  */
#if defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2
	vkCmdSetExclusiveScissorEnableNV = (PFN_vkCmdSetExclusiveScissorEnableNV)LoadFunc(Instance, "vkCmdSetExclusiveScissorEnableNV");
#endif /*  defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2  */
#if defined(VK_NV_scissor_exclusive)
	vkCmdSetExclusiveScissorNV = (PFN_vkCmdSetExclusiveScissorNV)LoadFunc(Instance, "vkCmdSetExclusiveScissorNV");
#endif /*  defined(VK_NV_scissor_exclusive)  */
#if defined(VK_NV_shading_rate_image)
	vkCmdBindShadingRateImageNV = (PFN_vkCmdBindShadingRateImageNV)LoadFunc(Instance, "vkCmdBindShadingRateImageNV");
	vkCmdSetCoarseSampleOrderNV = (PFN_vkCmdSetCoarseSampleOrderNV)LoadFunc(Instance, "vkCmdSetCoarseSampleOrderNV");
	vkCmdSetViewportShadingRatePaletteNV = (PFN_vkCmdSetViewportShadingRatePaletteNV)LoadFunc(Instance, "vkCmdSetViewportShadingRatePaletteNV");
#endif /*  defined(VK_NV_shading_rate_image)  */
#if defined(VK_QNX_screen_surface)
	vkGetPhysicalDeviceScreenPresentationSupportQNX = (PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX)LoadFunc(Instance, "vkGetPhysicalDeviceScreenPresentationSupportQNX");
#endif /*  defined(VK_QNX_screen_surface)  */
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
	vkCmdBindVertexBuffers2EXT = (PFN_vkCmdBindVertexBuffers2EXT)LoadFunc(Instance, "vkCmdBindVertexBuffers2EXT");
	vkCmdSetCullModeEXT = (PFN_vkCmdSetCullModeEXT)LoadFunc(Instance, "vkCmdSetCullModeEXT");
	vkCmdSetDepthBoundsTestEnableEXT = (PFN_vkCmdSetDepthBoundsTestEnableEXT)LoadFunc(Instance, "vkCmdSetDepthBoundsTestEnableEXT");
	vkCmdSetDepthCompareOpEXT = (PFN_vkCmdSetDepthCompareOpEXT)LoadFunc(Instance, "vkCmdSetDepthCompareOpEXT");
	vkCmdSetDepthTestEnableEXT = (PFN_vkCmdSetDepthTestEnableEXT)LoadFunc(Instance, "vkCmdSetDepthTestEnableEXT");
	vkCmdSetDepthWriteEnableEXT = (PFN_vkCmdSetDepthWriteEnableEXT)LoadFunc(Instance, "vkCmdSetDepthWriteEnableEXT");
	vkCmdSetFrontFaceEXT = (PFN_vkCmdSetFrontFaceEXT)LoadFunc(Instance, "vkCmdSetFrontFaceEXT");
	vkCmdSetPrimitiveTopologyEXT = (PFN_vkCmdSetPrimitiveTopologyEXT)LoadFunc(Instance, "vkCmdSetPrimitiveTopologyEXT");
	vkCmdSetScissorWithCountEXT = (PFN_vkCmdSetScissorWithCountEXT)LoadFunc(Instance, "vkCmdSetScissorWithCountEXT");
	vkCmdSetStencilOpEXT = (PFN_vkCmdSetStencilOpEXT)LoadFunc(Instance, "vkCmdSetStencilOpEXT");
	vkCmdSetStencilTestEnableEXT = (PFN_vkCmdSetStencilTestEnableEXT)LoadFunc(Instance, "vkCmdSetStencilTestEnableEXT");
	vkCmdSetViewportWithCountEXT = (PFN_vkCmdSetViewportWithCountEXT)LoadFunc(Instance, "vkCmdSetViewportWithCountEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
	vkCmdSetDepthBiasEnableEXT = (PFN_vkCmdSetDepthBiasEnableEXT)LoadFunc(Instance, "vkCmdSetDepthBiasEnableEXT");
	vkCmdSetLogicOpEXT = (PFN_vkCmdSetLogicOpEXT)LoadFunc(Instance, "vkCmdSetLogicOpEXT");
	vkCmdSetPatchControlPointsEXT = (PFN_vkCmdSetPatchControlPointsEXT)LoadFunc(Instance, "vkCmdSetPatchControlPointsEXT");
	vkCmdSetPrimitiveRestartEnableEXT = (PFN_vkCmdSetPrimitiveRestartEnableEXT)LoadFunc(Instance, "vkCmdSetPrimitiveRestartEnableEXT");
	vkCmdSetRasterizerDiscardEnableEXT = (PFN_vkCmdSetRasterizerDiscardEnableEXT)LoadFunc(Instance, "vkCmdSetRasterizerDiscardEnableEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
	vkCmdSetAlphaToCoverageEnableEXT = (PFN_vkCmdSetAlphaToCoverageEnableEXT)LoadFunc(Instance, "vkCmdSetAlphaToCoverageEnableEXT");
	vkCmdSetAlphaToOneEnableEXT = (PFN_vkCmdSetAlphaToOneEnableEXT)LoadFunc(Instance, "vkCmdSetAlphaToOneEnableEXT");
	vkCmdSetColorBlendEnableEXT = (PFN_vkCmdSetColorBlendEnableEXT)LoadFunc(Instance, "vkCmdSetColorBlendEnableEXT");
	vkCmdSetColorBlendEquationEXT = (PFN_vkCmdSetColorBlendEquationEXT)LoadFunc(Instance, "vkCmdSetColorBlendEquationEXT");
	vkCmdSetColorWriteMaskEXT = (PFN_vkCmdSetColorWriteMaskEXT)LoadFunc(Instance, "vkCmdSetColorWriteMaskEXT");
	vkCmdSetDepthClampEnableEXT = (PFN_vkCmdSetDepthClampEnableEXT)LoadFunc(Instance, "vkCmdSetDepthClampEnableEXT");
	vkCmdSetLogicOpEnableEXT = (PFN_vkCmdSetLogicOpEnableEXT)LoadFunc(Instance, "vkCmdSetLogicOpEnableEXT");
	vkCmdSetPolygonModeEXT = (PFN_vkCmdSetPolygonModeEXT)LoadFunc(Instance, "vkCmdSetPolygonModeEXT");
	vkCmdSetRasterizationSamplesEXT = (PFN_vkCmdSetRasterizationSamplesEXT)LoadFunc(Instance, "vkCmdSetRasterizationSamplesEXT");
	vkCmdSetSampleMaskEXT = (PFN_vkCmdSetSampleMaskEXT)LoadFunc(Instance, "vkCmdSetSampleMaskEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1))) || (defined(VK_EXT_shader_object))
	vkCmdSetTessellationDomainOriginEXT = (PFN_vkCmdSetTessellationDomainOriginEXT)LoadFunc(Instance, "vkCmdSetTessellationDomainOriginEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1))) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))
	vkCmdSetRasterizationStreamEXT = (PFN_vkCmdSetRasterizationStreamEXT)LoadFunc(Instance, "vkCmdSetRasterizationStreamEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))
	vkCmdSetConservativeRasterizationModeEXT = (PFN_vkCmdSetConservativeRasterizationModeEXT)LoadFunc(Instance, "vkCmdSetConservativeRasterizationModeEXT");
	vkCmdSetExtraPrimitiveOverestimationSizeEXT = (PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT)LoadFunc(Instance, "vkCmdSetExtraPrimitiveOverestimationSizeEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))
	vkCmdSetDepthClipEnableEXT = (PFN_vkCmdSetDepthClipEnableEXT)LoadFunc(Instance, "vkCmdSetDepthClipEnableEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))
	vkCmdSetSampleLocationsEnableEXT = (PFN_vkCmdSetSampleLocationsEnableEXT)LoadFunc(Instance, "vkCmdSetSampleLocationsEnableEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))
	vkCmdSetColorBlendAdvancedEXT = (PFN_vkCmdSetColorBlendAdvancedEXT)LoadFunc(Instance, "vkCmdSetColorBlendAdvancedEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))
	vkCmdSetProvokingVertexModeEXT = (PFN_vkCmdSetProvokingVertexModeEXT)LoadFunc(Instance, "vkCmdSetProvokingVertexModeEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))
	vkCmdSetLineRasterizationModeEXT = (PFN_vkCmdSetLineRasterizationModeEXT)LoadFunc(Instance, "vkCmdSetLineRasterizationModeEXT");
	vkCmdSetLineStippleEnableEXT = (PFN_vkCmdSetLineStippleEnableEXT)LoadFunc(Instance, "vkCmdSetLineStippleEnableEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))
	vkCmdSetDepthClipNegativeOneToOneEXT = (PFN_vkCmdSetDepthClipNegativeOneToOneEXT)LoadFunc(Instance, "vkCmdSetDepthClipNegativeOneToOneEXT");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling)) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))
	vkCmdSetViewportWScalingEnableNV = (PFN_vkCmdSetViewportWScalingEnableNV)LoadFunc(Instance, "vkCmdSetViewportWScalingEnableNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling)) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle)) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))
	vkCmdSetViewportSwizzleNV = (PFN_vkCmdSetViewportSwizzleNV)LoadFunc(Instance, "vkCmdSetViewportSwizzleNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle)) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color)) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))
	vkCmdSetCoverageToColorEnableNV = (PFN_vkCmdSetCoverageToColorEnableNV)LoadFunc(Instance, "vkCmdSetCoverageToColorEnableNV");
	vkCmdSetCoverageToColorLocationNV = (PFN_vkCmdSetCoverageToColorLocationNV)LoadFunc(Instance, "vkCmdSetCoverageToColorLocationNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color)) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples)) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))
	vkCmdSetCoverageModulationModeNV = (PFN_vkCmdSetCoverageModulationModeNV)LoadFunc(Instance, "vkCmdSetCoverageModulationModeNV");
	vkCmdSetCoverageModulationTableEnableNV = (PFN_vkCmdSetCoverageModulationTableEnableNV)LoadFunc(Instance, "vkCmdSetCoverageModulationTableEnableNV");
	vkCmdSetCoverageModulationTableNV = (PFN_vkCmdSetCoverageModulationTableNV)LoadFunc(Instance, "vkCmdSetCoverageModulationTableNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples)) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image)) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))
	vkCmdSetShadingRateImageEnableNV = (PFN_vkCmdSetShadingRateImageEnableNV)LoadFunc(Instance, "vkCmdSetShadingRateImageEnableNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image)) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test)) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))
	vkCmdSetRepresentativeFragmentTestEnableNV = (PFN_vkCmdSetRepresentativeFragmentTestEnableNV)LoadFunc(Instance, "vkCmdSetRepresentativeFragmentTestEnableNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test)) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode)) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))
	vkCmdSetCoverageReductionModeNV = (PFN_vkCmdSetCoverageReductionModeNV)LoadFunc(Instance, "vkCmdSetCoverageReductionModeNV");
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode)) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))  */
#if (defined(VK_EXT_shader_object)) || (defined(VK_EXT_vertex_input_dynamic_state))
	vkCmdSetVertexInputEXT = (PFN_vkCmdSetVertexInputEXT)LoadFunc(Instance, "vkCmdSetVertexInputEXT");
#endif /*  (defined(VK_EXT_shader_object)) || (defined(VK_EXT_vertex_input_dynamic_state))  */
#if (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
	vkCmdPushDescriptorSetWithTemplateKHR = (PFN_vkCmdPushDescriptorSetWithTemplateKHR)LoadFunc(Instance, "vkCmdPushDescriptorSetWithTemplateKHR");
#endif /*  (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))  */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
	vkGetPhysicalDevicePresentRectanglesKHR = (PFN_vkGetPhysicalDevicePresentRectanglesKHR)LoadFunc(Instance, "vkGetPhysicalDevicePresentRectanglesKHR");
#endif /*  (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))  */

}

MYTH_VK_LOAD_API void _mythVkLoadInstance(VkInstance Instance, PFN_vkGetInstanceProcAddr LoadFunc){

//SECTION(V): VK_LOADER_INSTANCE_IMPL
#if defined(VK_VERSION_1_0)
	vkDestroyInstance = (PFN_vkDestroyInstance)LoadFunc(Instance, "vkDestroyInstance");
	vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)LoadFunc(Instance, "vkEnumeratePhysicalDevices");
	vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)LoadFunc(Instance, "vkGetDeviceProcAddr");
#endif /*  defined(VK_VERSION_1_0)  */
#if defined(VK_VERSION_1_1)
	vkEnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups)LoadFunc(Instance, "vkEnumeratePhysicalDeviceGroups");
#endif /*  defined(VK_VERSION_1_1)  */
#if defined(VK_EXT_debug_report)
	vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)LoadFunc(Instance, "vkCreateDebugReportCallbackEXT");
	vkDebugReportMessageEXT = (PFN_vkDebugReportMessageEXT)LoadFunc(Instance, "vkDebugReportMessageEXT");
	vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)LoadFunc(Instance, "vkDestroyDebugReportCallbackEXT");
#endif /*  defined(VK_EXT_debug_report)  */
#if defined(VK_EXT_debug_utils)
	vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)LoadFunc(Instance, "vkCreateDebugUtilsMessengerEXT");
	vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)LoadFunc(Instance, "vkDestroyDebugUtilsMessengerEXT");
	vkSubmitDebugUtilsMessageEXT = (PFN_vkSubmitDebugUtilsMessageEXT)LoadFunc(Instance, "vkSubmitDebugUtilsMessageEXT");
#endif /*  defined(VK_EXT_debug_utils)  */
#if defined(VK_EXT_directfb_surface)
	vkCreateDirectFBSurfaceEXT = (PFN_vkCreateDirectFBSurfaceEXT)LoadFunc(Instance, "vkCreateDirectFBSurfaceEXT");
#endif /*  defined(VK_EXT_directfb_surface)  */
#if defined(VK_EXT_headless_surface)
	vkCreateHeadlessSurfaceEXT = (PFN_vkCreateHeadlessSurfaceEXT)LoadFunc(Instance, "vkCreateHeadlessSurfaceEXT");
#endif /*  defined(VK_EXT_headless_surface)  */
#if defined(VK_EXT_metal_surface)
	vkCreateMetalSurfaceEXT = (PFN_vkCreateMetalSurfaceEXT)LoadFunc(Instance, "vkCreateMetalSurfaceEXT");
#endif /*  defined(VK_EXT_metal_surface)  */
#if defined(VK_FUCHSIA_imagepipe_surface)
	vkCreateImagePipeSurfaceFUCHSIA = (PFN_vkCreateImagePipeSurfaceFUCHSIA)LoadFunc(Instance, "vkCreateImagePipeSurfaceFUCHSIA");
#endif /*  defined(VK_FUCHSIA_imagepipe_surface)  */
#if defined(VK_GGP_stream_descriptor_surface)
	vkCreateStreamDescriptorSurfaceGGP = (PFN_vkCreateStreamDescriptorSurfaceGGP)LoadFunc(Instance, "vkCreateStreamDescriptorSurfaceGGP");
#endif /*  defined(VK_GGP_stream_descriptor_surface)  */
#if defined(VK_KHR_android_surface)
	vkCreateAndroidSurfaceKHR = (PFN_vkCreateAndroidSurfaceKHR)LoadFunc(Instance, "vkCreateAndroidSurfaceKHR");
#endif /*  defined(VK_KHR_android_surface)  */
#if defined(VK_KHR_device_group_creation)
	vkEnumeratePhysicalDeviceGroupsKHR = (PFN_vkEnumeratePhysicalDeviceGroupsKHR)LoadFunc(Instance, "vkEnumeratePhysicalDeviceGroupsKHR");
#endif /*  defined(VK_KHR_device_group_creation)  */
#if defined(VK_KHR_display)
	vkCreateDisplayPlaneSurfaceKHR = (PFN_vkCreateDisplayPlaneSurfaceKHR)LoadFunc(Instance, "vkCreateDisplayPlaneSurfaceKHR");
#endif /*  defined(VK_KHR_display)  */
#if defined(VK_KHR_surface)
	vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)LoadFunc(Instance, "vkDestroySurfaceKHR");
#endif /*  defined(VK_KHR_surface)  */
#if defined(VK_KHR_wayland_surface)
	vkCreateWaylandSurfaceKHR = (PFN_vkCreateWaylandSurfaceKHR)LoadFunc(Instance, "vkCreateWaylandSurfaceKHR");
#endif /*  defined(VK_KHR_wayland_surface)  */
#if defined(VK_KHR_win32_surface)
	vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)LoadFunc(Instance, "vkCreateWin32SurfaceKHR");
#endif /*  defined(VK_KHR_win32_surface)  */
#if defined(VK_KHR_xcb_surface)
	vkCreateXcbSurfaceKHR = (PFN_vkCreateXcbSurfaceKHR)LoadFunc(Instance, "vkCreateXcbSurfaceKHR");
#endif /*  defined(VK_KHR_xcb_surface)  */
#if defined(VK_KHR_xlib_surface)
	vkCreateXlibSurfaceKHR = (PFN_vkCreateXlibSurfaceKHR)LoadFunc(Instance, "vkCreateXlibSurfaceKHR");
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
#if defined(VK_QNX_screen_surface)
	vkCreateScreenSurfaceQNX = (PFN_vkCreateScreenSurfaceQNX)LoadFunc(Instance, "vkCreateScreenSurfaceQNX");
#endif /*  defined(VK_QNX_screen_surface)  */

}

void _mythVkLoadDevice(VkDevice Device, PFN_vkGetDeviceProcAddr LoadFunc){

//SECTION(V): VK_LOADER_DEVICE_IMPL
#if defined(VK_VERSION_1_0)
	vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)LoadFunc(Device, "vkAllocateCommandBuffers");
	vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)LoadFunc(Device, "vkAllocateDescriptorSets");
	vkAllocateMemory = (PFN_vkAllocateMemory)LoadFunc(Device, "vkAllocateMemory");
	vkBindBufferMemory = (PFN_vkBindBufferMemory)LoadFunc(Device, "vkBindBufferMemory");
	vkBindImageMemory = (PFN_vkBindImageMemory)LoadFunc(Device, "vkBindImageMemory");
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
	vkCreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot)LoadFunc(Device, "vkCreatePrivateDataSlot");
	vkDestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot)LoadFunc(Device, "vkDestroyPrivateDataSlot");
	vkGetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements)LoadFunc(Device, "vkGetDeviceBufferMemoryRequirements");
	vkGetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements)LoadFunc(Device, "vkGetDeviceImageMemoryRequirements");
	vkGetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements)LoadFunc(Device, "vkGetDeviceImageSparseMemoryRequirements");
	vkGetPrivateData = (PFN_vkGetPrivateData)LoadFunc(Device, "vkGetPrivateData");
	vkSetPrivateData = (PFN_vkSetPrivateData)LoadFunc(Device, "vkSetPrivateData");
#endif /*  defined(VK_VERSION_1_3)  */
#if defined(VK_AMDX_shader_enqueue)
	vkCreateExecutionGraphPipelinesAMDX = (PFN_vkCreateExecutionGraphPipelinesAMDX)LoadFunc(Device, "vkCreateExecutionGraphPipelinesAMDX");
	vkGetExecutionGraphPipelineNodeIndexAMDX = (PFN_vkGetExecutionGraphPipelineNodeIndexAMDX)LoadFunc(Device, "vkGetExecutionGraphPipelineNodeIndexAMDX");
	vkGetExecutionGraphPipelineScratchSizeAMDX = (PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)LoadFunc(Device, "vkGetExecutionGraphPipelineScratchSizeAMDX");
#endif /*  defined(VK_AMDX_shader_enqueue)  */
#if defined(VK_AMD_anti_lag)
	vkAntiLagUpdateAMD = (PFN_vkAntiLagUpdateAMD)LoadFunc(Device, "vkAntiLagUpdateAMD");
#endif /*  defined(VK_AMD_anti_lag)  */
#if defined(VK_AMD_display_native_hdr)
	vkSetLocalDimmingAMD = (PFN_vkSetLocalDimmingAMD)LoadFunc(Device, "vkSetLocalDimmingAMD");
#endif /*  defined(VK_AMD_display_native_hdr)  */
#if defined(VK_AMD_shader_info)
	vkGetShaderInfoAMD = (PFN_vkGetShaderInfoAMD)LoadFunc(Device, "vkGetShaderInfoAMD");
#endif /*  defined(VK_AMD_shader_info)  */
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
	vkGetAndroidHardwareBufferPropertiesANDROID = (PFN_vkGetAndroidHardwareBufferPropertiesANDROID)LoadFunc(Device, "vkGetAndroidHardwareBufferPropertiesANDROID");
	vkGetMemoryAndroidHardwareBufferANDROID = (PFN_vkGetMemoryAndroidHardwareBufferANDROID)LoadFunc(Device, "vkGetMemoryAndroidHardwareBufferANDROID");
#endif /*  defined(VK_ANDROID_external_memory_android_hardware_buffer)  */
#if defined(VK_EXT_buffer_device_address)
	vkGetBufferDeviceAddressEXT = (PFN_vkGetBufferDeviceAddressEXT)LoadFunc(Device, "vkGetBufferDeviceAddressEXT");
#endif /*  defined(VK_EXT_buffer_device_address)  */
#if defined(VK_EXT_calibrated_timestamps)
	vkGetCalibratedTimestampsEXT = (PFN_vkGetCalibratedTimestampsEXT)LoadFunc(Device, "vkGetCalibratedTimestampsEXT");
#endif /*  defined(VK_EXT_calibrated_timestamps)  */
#if defined(VK_EXT_debug_marker)
	vkDebugMarkerSetObjectNameEXT = (PFN_vkDebugMarkerSetObjectNameEXT)LoadFunc(Device, "vkDebugMarkerSetObjectNameEXT");
	vkDebugMarkerSetObjectTagEXT = (PFN_vkDebugMarkerSetObjectTagEXT)LoadFunc(Device, "vkDebugMarkerSetObjectTagEXT");
#endif /*  defined(VK_EXT_debug_marker)  */
#if defined(VK_EXT_descriptor_buffer)
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
#if defined(VK_EXT_metal_objects)
	vkExportMetalObjectsEXT = (PFN_vkExportMetalObjectsEXT)LoadFunc(Device, "vkExportMetalObjectsEXT");
#endif /*  defined(VK_EXT_metal_objects)  */
#if defined(VK_EXT_opacity_micromap)
	vkBuildMicromapsEXT = (PFN_vkBuildMicromapsEXT)LoadFunc(Device, "vkBuildMicromapsEXT");
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
#if defined(VK_EXT_shader_module_identifier)
	vkGetShaderModuleCreateInfoIdentifierEXT = (PFN_vkGetShaderModuleCreateInfoIdentifierEXT)LoadFunc(Device, "vkGetShaderModuleCreateInfoIdentifierEXT");
	vkGetShaderModuleIdentifierEXT = (PFN_vkGetShaderModuleIdentifierEXT)LoadFunc(Device, "vkGetShaderModuleIdentifierEXT");
#endif /*  defined(VK_EXT_shader_module_identifier)  */
#if defined(VK_EXT_shader_object)
	vkCreateShadersEXT = (PFN_vkCreateShadersEXT)LoadFunc(Device, "vkCreateShadersEXT");
	vkDestroyShaderEXT = (PFN_vkDestroyShaderEXT)LoadFunc(Device, "vkDestroyShaderEXT");
	vkGetShaderBinaryDataEXT = (PFN_vkGetShaderBinaryDataEXT)LoadFunc(Device, "vkGetShaderBinaryDataEXT");
#endif /*  defined(VK_EXT_shader_object)  */
#if defined(VK_EXT_swapchain_maintenance1)
	vkReleaseSwapchainImagesEXT = (PFN_vkReleaseSwapchainImagesEXT)LoadFunc(Device, "vkReleaseSwapchainImagesEXT");
#endif /*  defined(VK_EXT_swapchain_maintenance1)  */
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
#if defined(VK_HUAWEI_subpass_shading)
	vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI = (PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI)LoadFunc(Device, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI");
#endif /*  defined(VK_HUAWEI_subpass_shading)  */
#if defined(VK_INTEL_performance_query)
	vkAcquirePerformanceConfigurationINTEL = (PFN_vkAcquirePerformanceConfigurationINTEL)LoadFunc(Device, "vkAcquirePerformanceConfigurationINTEL");
	vkGetPerformanceParameterINTEL = (PFN_vkGetPerformanceParameterINTEL)LoadFunc(Device, "vkGetPerformanceParameterINTEL");
	vkInitializePerformanceApiINTEL = (PFN_vkInitializePerformanceApiINTEL)LoadFunc(Device, "vkInitializePerformanceApiINTEL");
	vkReleasePerformanceConfigurationINTEL = (PFN_vkReleasePerformanceConfigurationINTEL)LoadFunc(Device, "vkReleasePerformanceConfigurationINTEL");
	vkUninitializePerformanceApiINTEL = (PFN_vkUninitializePerformanceApiINTEL)LoadFunc(Device, "vkUninitializePerformanceApiINTEL");
#endif /*  defined(VK_INTEL_performance_query)  */
#if defined(VK_KHR_acceleration_structure)
	vkBuildAccelerationStructuresKHR = (PFN_vkBuildAccelerationStructuresKHR)LoadFunc(Device, "vkBuildAccelerationStructuresKHR");
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
#if defined(VK_KHR_create_renderpass2)
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
	vkGetDeviceGroupPeerMemoryFeaturesKHR = (PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR)LoadFunc(Device, "vkGetDeviceGroupPeerMemoryFeaturesKHR");
#endif /*  defined(VK_KHR_device_group)  */
#if defined(VK_KHR_display_swapchain)
	vkCreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR)LoadFunc(Device, "vkCreateSharedSwapchainsKHR");
#endif /*  defined(VK_KHR_display_swapchain)  */
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
#if defined(VK_KHR_get_memory_requirements2)
	vkGetBufferMemoryRequirements2KHR = (PFN_vkGetBufferMemoryRequirements2KHR)LoadFunc(Device, "vkGetBufferMemoryRequirements2KHR");
	vkGetImageMemoryRequirements2KHR = (PFN_vkGetImageMemoryRequirements2KHR)LoadFunc(Device, "vkGetImageMemoryRequirements2KHR");
	vkGetImageSparseMemoryRequirements2KHR = (PFN_vkGetImageSparseMemoryRequirements2KHR)LoadFunc(Device, "vkGetImageSparseMemoryRequirements2KHR");
#endif /*  defined(VK_KHR_get_memory_requirements2)  */
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
	vkGetDeviceImageSubresourceLayoutKHR = (PFN_vkGetDeviceImageSubresourceLayoutKHR)LoadFunc(Device, "vkGetDeviceImageSubresourceLayoutKHR");
	vkGetImageSubresourceLayout2KHR = (PFN_vkGetImageSubresourceLayout2KHR)LoadFunc(Device, "vkGetImageSubresourceLayout2KHR");
	vkGetRenderingAreaGranularityKHR = (PFN_vkGetRenderingAreaGranularityKHR)LoadFunc(Device, "vkGetRenderingAreaGranularityKHR");
#endif /*  defined(VK_KHR_maintenance5)  */
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
#if defined(VK_KHR_ray_tracing_pipeline)
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
#endif /*  defined(VK_KHR_swapchain)  */
#if defined(VK_KHR_timeline_semaphore)
	vkGetSemaphoreCounterValueKHR = (PFN_vkGetSemaphoreCounterValueKHR)LoadFunc(Device, "vkGetSemaphoreCounterValueKHR");
	vkSignalSemaphoreKHR = (PFN_vkSignalSemaphoreKHR)LoadFunc(Device, "vkSignalSemaphoreKHR");
	vkWaitSemaphoresKHR = (PFN_vkWaitSemaphoresKHR)LoadFunc(Device, "vkWaitSemaphoresKHR");
#endif /*  defined(VK_KHR_timeline_semaphore)  */
#if defined(VK_KHR_video_encode_queue)
	vkGetEncodedVideoSessionParametersKHR = (PFN_vkGetEncodedVideoSessionParametersKHR)LoadFunc(Device, "vkGetEncodedVideoSessionParametersKHR");
#endif /*  defined(VK_KHR_video_encode_queue)  */
#if defined(VK_KHR_video_queue)
	vkBindVideoSessionMemoryKHR = (PFN_vkBindVideoSessionMemoryKHR)LoadFunc(Device, "vkBindVideoSessionMemoryKHR");
	vkCreateVideoSessionKHR = (PFN_vkCreateVideoSessionKHR)LoadFunc(Device, "vkCreateVideoSessionKHR");
	vkCreateVideoSessionParametersKHR = (PFN_vkCreateVideoSessionParametersKHR)LoadFunc(Device, "vkCreateVideoSessionParametersKHR");
	vkDestroyVideoSessionKHR = (PFN_vkDestroyVideoSessionKHR)LoadFunc(Device, "vkDestroyVideoSessionKHR");
	vkDestroyVideoSessionParametersKHR = (PFN_vkDestroyVideoSessionParametersKHR)LoadFunc(Device, "vkDestroyVideoSessionParametersKHR");
	vkGetVideoSessionMemoryRequirementsKHR = (PFN_vkGetVideoSessionMemoryRequirementsKHR)LoadFunc(Device, "vkGetVideoSessionMemoryRequirementsKHR");
	vkUpdateVideoSessionParametersKHR = (PFN_vkUpdateVideoSessionParametersKHR)LoadFunc(Device, "vkUpdateVideoSessionParametersKHR");
#endif /*  defined(VK_KHR_video_queue)  */
#if defined(VK_NVX_binary_import)
	vkCreateCuFunctionNVX = (PFN_vkCreateCuFunctionNVX)LoadFunc(Device, "vkCreateCuFunctionNVX");
	vkCreateCuModuleNVX = (PFN_vkCreateCuModuleNVX)LoadFunc(Device, "vkCreateCuModuleNVX");
	vkDestroyCuFunctionNVX = (PFN_vkDestroyCuFunctionNVX)LoadFunc(Device, "vkDestroyCuFunctionNVX");
	vkDestroyCuModuleNVX = (PFN_vkDestroyCuModuleNVX)LoadFunc(Device, "vkDestroyCuModuleNVX");
#endif /*  defined(VK_NVX_binary_import)  */
#if defined(VK_NVX_image_view_handle)
	vkGetImageViewAddressNVX = (PFN_vkGetImageViewAddressNVX)LoadFunc(Device, "vkGetImageViewAddressNVX");
	vkGetImageViewHandleNVX = (PFN_vkGetImageViewHandleNVX)LoadFunc(Device, "vkGetImageViewHandleNVX");
#endif /*  defined(VK_NVX_image_view_handle)  */
#if defined(VK_NV_cuda_kernel_launch)
	vkCreateCudaFunctionNV = (PFN_vkCreateCudaFunctionNV)LoadFunc(Device, "vkCreateCudaFunctionNV");
	vkCreateCudaModuleNV = (PFN_vkCreateCudaModuleNV)LoadFunc(Device, "vkCreateCudaModuleNV");
	vkDestroyCudaFunctionNV = (PFN_vkDestroyCudaFunctionNV)LoadFunc(Device, "vkDestroyCudaFunctionNV");
	vkDestroyCudaModuleNV = (PFN_vkDestroyCudaModuleNV)LoadFunc(Device, "vkDestroyCudaModuleNV");
	vkGetCudaModuleCacheNV = (PFN_vkGetCudaModuleCacheNV)LoadFunc(Device, "vkGetCudaModuleCacheNV");
#endif /*  defined(VK_NV_cuda_kernel_launch)  */
#if defined(VK_NV_device_generated_commands)
	vkCreateIndirectCommandsLayoutNV = (PFN_vkCreateIndirectCommandsLayoutNV)LoadFunc(Device, "vkCreateIndirectCommandsLayoutNV");
	vkDestroyIndirectCommandsLayoutNV = (PFN_vkDestroyIndirectCommandsLayoutNV)LoadFunc(Device, "vkDestroyIndirectCommandsLayoutNV");
	vkGetGeneratedCommandsMemoryRequirementsNV = (PFN_vkGetGeneratedCommandsMemoryRequirementsNV)LoadFunc(Device, "vkGetGeneratedCommandsMemoryRequirementsNV");
#endif /*  defined(VK_NV_device_generated_commands)  */
#if defined(VK_NV_device_generated_commands_compute)
	vkGetPipelineIndirectDeviceAddressNV = (PFN_vkGetPipelineIndirectDeviceAddressNV)LoadFunc(Device, "vkGetPipelineIndirectDeviceAddressNV");
	vkGetPipelineIndirectMemoryRequirementsNV = (PFN_vkGetPipelineIndirectMemoryRequirementsNV)LoadFunc(Device, "vkGetPipelineIndirectMemoryRequirementsNV");
#endif /*  defined(VK_NV_device_generated_commands_compute)  */
#if defined(VK_NV_external_memory_rdma)
	vkGetMemoryRemoteAddressNV = (PFN_vkGetMemoryRemoteAddressNV)LoadFunc(Device, "vkGetMemoryRemoteAddressNV");
#endif /*  defined(VK_NV_external_memory_rdma)  */
#if defined(VK_NV_external_memory_win32)
	vkGetMemoryWin32HandleNV = (PFN_vkGetMemoryWin32HandleNV)LoadFunc(Device, "vkGetMemoryWin32HandleNV");
#endif /*  defined(VK_NV_external_memory_win32)  */
#if defined(VK_NV_low_latency2)
	vkGetLatencyTimingsNV = (PFN_vkGetLatencyTimingsNV)LoadFunc(Device, "vkGetLatencyTimingsNV");
	vkLatencySleepNV = (PFN_vkLatencySleepNV)LoadFunc(Device, "vkLatencySleepNV");
	vkSetLatencyMarkerNV = (PFN_vkSetLatencyMarkerNV)LoadFunc(Device, "vkSetLatencyMarkerNV");
	vkSetLatencySleepModeNV = (PFN_vkSetLatencySleepModeNV)LoadFunc(Device, "vkSetLatencySleepModeNV");
#endif /*  defined(VK_NV_low_latency2)  */
#if defined(VK_NV_optical_flow)
	vkBindOpticalFlowSessionImageNV = (PFN_vkBindOpticalFlowSessionImageNV)LoadFunc(Device, "vkBindOpticalFlowSessionImageNV");
	vkCreateOpticalFlowSessionNV = (PFN_vkCreateOpticalFlowSessionNV)LoadFunc(Device, "vkCreateOpticalFlowSessionNV");
	vkDestroyOpticalFlowSessionNV = (PFN_vkDestroyOpticalFlowSessionNV)LoadFunc(Device, "vkDestroyOpticalFlowSessionNV");
#endif /*  defined(VK_NV_optical_flow)  */
#if defined(VK_NV_ray_tracing)
	vkBindAccelerationStructureMemoryNV = (PFN_vkBindAccelerationStructureMemoryNV)LoadFunc(Device, "vkBindAccelerationStructureMemoryNV");
	vkCompileDeferredNV = (PFN_vkCompileDeferredNV)LoadFunc(Device, "vkCompileDeferredNV");
	vkCreateAccelerationStructureNV = (PFN_vkCreateAccelerationStructureNV)LoadFunc(Device, "vkCreateAccelerationStructureNV");
	vkCreateRayTracingPipelinesNV = (PFN_vkCreateRayTracingPipelinesNV)LoadFunc(Device, "vkCreateRayTracingPipelinesNV");
	vkDestroyAccelerationStructureNV = (PFN_vkDestroyAccelerationStructureNV)LoadFunc(Device, "vkDestroyAccelerationStructureNV");
	vkGetAccelerationStructureHandleNV = (PFN_vkGetAccelerationStructureHandleNV)LoadFunc(Device, "vkGetAccelerationStructureHandleNV");
	vkGetAccelerationStructureMemoryRequirementsNV = (PFN_vkGetAccelerationStructureMemoryRequirementsNV)LoadFunc(Device, "vkGetAccelerationStructureMemoryRequirementsNV");
	vkGetRayTracingShaderGroupHandlesNV = (PFN_vkGetRayTracingShaderGroupHandlesNV)LoadFunc(Device, "vkGetRayTracingShaderGroupHandlesNV");
#endif /*  defined(VK_NV_ray_tracing)  */
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
#if (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
	vkGetDeviceGroupSurfacePresentModes2EXT = (PFN_vkGetDeviceGroupSurfacePresentModes2EXT)LoadFunc(Device, "vkGetDeviceGroupSurfacePresentModes2EXT");
#endif /*  (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))  */
#if (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))
	vkGetImageSubresourceLayout2EXT = (PFN_vkGetImageSubresourceLayout2EXT)LoadFunc(Device, "vkGetImageSubresourceLayout2EXT");
#endif /*  (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))  */
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
	FuncArray->vkBindBufferMemory = (PFN_vkBindBufferMemory)LoadFunc(Device, "vkBindBufferMemory");
	FuncArray->vkBindImageMemory = (PFN_vkBindImageMemory)LoadFunc(Device, "vkBindImageMemory");
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
	FuncArray->vkCreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot)LoadFunc(Device, "vkCreatePrivateDataSlot");
	FuncArray->vkDestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot)LoadFunc(Device, "vkDestroyPrivateDataSlot");
	FuncArray->vkGetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements)LoadFunc(Device, "vkGetDeviceBufferMemoryRequirements");
	FuncArray->vkGetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements)LoadFunc(Device, "vkGetDeviceImageMemoryRequirements");
	FuncArray->vkGetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements)LoadFunc(Device, "vkGetDeviceImageSparseMemoryRequirements");
	FuncArray->vkGetPrivateData = (PFN_vkGetPrivateData)LoadFunc(Device, "vkGetPrivateData");
	FuncArray->vkSetPrivateData = (PFN_vkSetPrivateData)LoadFunc(Device, "vkSetPrivateData");
#endif /*  defined(VK_VERSION_1_3)  */
#if defined(VK_AMDX_shader_enqueue)
	FuncArray->vkCreateExecutionGraphPipelinesAMDX = (PFN_vkCreateExecutionGraphPipelinesAMDX)LoadFunc(Device, "vkCreateExecutionGraphPipelinesAMDX");
	FuncArray->vkGetExecutionGraphPipelineNodeIndexAMDX = (PFN_vkGetExecutionGraphPipelineNodeIndexAMDX)LoadFunc(Device, "vkGetExecutionGraphPipelineNodeIndexAMDX");
	FuncArray->vkGetExecutionGraphPipelineScratchSizeAMDX = (PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)LoadFunc(Device, "vkGetExecutionGraphPipelineScratchSizeAMDX");
#endif /*  defined(VK_AMDX_shader_enqueue)  */
#if defined(VK_AMD_anti_lag)
	FuncArray->vkAntiLagUpdateAMD = (PFN_vkAntiLagUpdateAMD)LoadFunc(Device, "vkAntiLagUpdateAMD");
#endif /*  defined(VK_AMD_anti_lag)  */
#if defined(VK_AMD_display_native_hdr)
	FuncArray->vkSetLocalDimmingAMD = (PFN_vkSetLocalDimmingAMD)LoadFunc(Device, "vkSetLocalDimmingAMD");
#endif /*  defined(VK_AMD_display_native_hdr)  */
#if defined(VK_AMD_shader_info)
	FuncArray->vkGetShaderInfoAMD = (PFN_vkGetShaderInfoAMD)LoadFunc(Device, "vkGetShaderInfoAMD");
#endif /*  defined(VK_AMD_shader_info)  */
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
	FuncArray->vkGetAndroidHardwareBufferPropertiesANDROID = (PFN_vkGetAndroidHardwareBufferPropertiesANDROID)LoadFunc(Device, "vkGetAndroidHardwareBufferPropertiesANDROID");
	FuncArray->vkGetMemoryAndroidHardwareBufferANDROID = (PFN_vkGetMemoryAndroidHardwareBufferANDROID)LoadFunc(Device, "vkGetMemoryAndroidHardwareBufferANDROID");
#endif /*  defined(VK_ANDROID_external_memory_android_hardware_buffer)  */
#if defined(VK_EXT_buffer_device_address)
	FuncArray->vkGetBufferDeviceAddressEXT = (PFN_vkGetBufferDeviceAddressEXT)LoadFunc(Device, "vkGetBufferDeviceAddressEXT");
#endif /*  defined(VK_EXT_buffer_device_address)  */
#if defined(VK_EXT_calibrated_timestamps)
	FuncArray->vkGetCalibratedTimestampsEXT = (PFN_vkGetCalibratedTimestampsEXT)LoadFunc(Device, "vkGetCalibratedTimestampsEXT");
#endif /*  defined(VK_EXT_calibrated_timestamps)  */
#if defined(VK_EXT_debug_marker)
	FuncArray->vkDebugMarkerSetObjectNameEXT = (PFN_vkDebugMarkerSetObjectNameEXT)LoadFunc(Device, "vkDebugMarkerSetObjectNameEXT");
	FuncArray->vkDebugMarkerSetObjectTagEXT = (PFN_vkDebugMarkerSetObjectTagEXT)LoadFunc(Device, "vkDebugMarkerSetObjectTagEXT");
#endif /*  defined(VK_EXT_debug_marker)  */
#if defined(VK_EXT_descriptor_buffer)
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
#if defined(VK_EXT_metal_objects)
	FuncArray->vkExportMetalObjectsEXT = (PFN_vkExportMetalObjectsEXT)LoadFunc(Device, "vkExportMetalObjectsEXT");
#endif /*  defined(VK_EXT_metal_objects)  */
#if defined(VK_EXT_opacity_micromap)
	FuncArray->vkBuildMicromapsEXT = (PFN_vkBuildMicromapsEXT)LoadFunc(Device, "vkBuildMicromapsEXT");
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
#if defined(VK_EXT_shader_module_identifier)
	FuncArray->vkGetShaderModuleCreateInfoIdentifierEXT = (PFN_vkGetShaderModuleCreateInfoIdentifierEXT)LoadFunc(Device, "vkGetShaderModuleCreateInfoIdentifierEXT");
	FuncArray->vkGetShaderModuleIdentifierEXT = (PFN_vkGetShaderModuleIdentifierEXT)LoadFunc(Device, "vkGetShaderModuleIdentifierEXT");
#endif /*  defined(VK_EXT_shader_module_identifier)  */
#if defined(VK_EXT_shader_object)
	FuncArray->vkCreateShadersEXT = (PFN_vkCreateShadersEXT)LoadFunc(Device, "vkCreateShadersEXT");
	FuncArray->vkDestroyShaderEXT = (PFN_vkDestroyShaderEXT)LoadFunc(Device, "vkDestroyShaderEXT");
	FuncArray->vkGetShaderBinaryDataEXT = (PFN_vkGetShaderBinaryDataEXT)LoadFunc(Device, "vkGetShaderBinaryDataEXT");
#endif /*  defined(VK_EXT_shader_object)  */
#if defined(VK_EXT_swapchain_maintenance1)
	FuncArray->vkReleaseSwapchainImagesEXT = (PFN_vkReleaseSwapchainImagesEXT)LoadFunc(Device, "vkReleaseSwapchainImagesEXT");
#endif /*  defined(VK_EXT_swapchain_maintenance1)  */
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
#if defined(VK_HUAWEI_subpass_shading)
	FuncArray->vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI = (PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI)LoadFunc(Device, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI");
#endif /*  defined(VK_HUAWEI_subpass_shading)  */
#if defined(VK_INTEL_performance_query)
	FuncArray->vkAcquirePerformanceConfigurationINTEL = (PFN_vkAcquirePerformanceConfigurationINTEL)LoadFunc(Device, "vkAcquirePerformanceConfigurationINTEL");
	FuncArray->vkGetPerformanceParameterINTEL = (PFN_vkGetPerformanceParameterINTEL)LoadFunc(Device, "vkGetPerformanceParameterINTEL");
	FuncArray->vkInitializePerformanceApiINTEL = (PFN_vkInitializePerformanceApiINTEL)LoadFunc(Device, "vkInitializePerformanceApiINTEL");
	FuncArray->vkReleasePerformanceConfigurationINTEL = (PFN_vkReleasePerformanceConfigurationINTEL)LoadFunc(Device, "vkReleasePerformanceConfigurationINTEL");
	FuncArray->vkUninitializePerformanceApiINTEL = (PFN_vkUninitializePerformanceApiINTEL)LoadFunc(Device, "vkUninitializePerformanceApiINTEL");
#endif /*  defined(VK_INTEL_performance_query)  */
#if defined(VK_KHR_acceleration_structure)
	FuncArray->vkBuildAccelerationStructuresKHR = (PFN_vkBuildAccelerationStructuresKHR)LoadFunc(Device, "vkBuildAccelerationStructuresKHR");
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
#if defined(VK_KHR_create_renderpass2)
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
	FuncArray->vkGetDeviceGroupPeerMemoryFeaturesKHR = (PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR)LoadFunc(Device, "vkGetDeviceGroupPeerMemoryFeaturesKHR");
#endif /*  defined(VK_KHR_device_group)  */
#if defined(VK_KHR_display_swapchain)
	FuncArray->vkCreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR)LoadFunc(Device, "vkCreateSharedSwapchainsKHR");
#endif /*  defined(VK_KHR_display_swapchain)  */
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
#if defined(VK_KHR_get_memory_requirements2)
	FuncArray->vkGetBufferMemoryRequirements2KHR = (PFN_vkGetBufferMemoryRequirements2KHR)LoadFunc(Device, "vkGetBufferMemoryRequirements2KHR");
	FuncArray->vkGetImageMemoryRequirements2KHR = (PFN_vkGetImageMemoryRequirements2KHR)LoadFunc(Device, "vkGetImageMemoryRequirements2KHR");
	FuncArray->vkGetImageSparseMemoryRequirements2KHR = (PFN_vkGetImageSparseMemoryRequirements2KHR)LoadFunc(Device, "vkGetImageSparseMemoryRequirements2KHR");
#endif /*  defined(VK_KHR_get_memory_requirements2)  */
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
	FuncArray->vkGetDeviceImageSubresourceLayoutKHR = (PFN_vkGetDeviceImageSubresourceLayoutKHR)LoadFunc(Device, "vkGetDeviceImageSubresourceLayoutKHR");
	FuncArray->vkGetImageSubresourceLayout2KHR = (PFN_vkGetImageSubresourceLayout2KHR)LoadFunc(Device, "vkGetImageSubresourceLayout2KHR");
	FuncArray->vkGetRenderingAreaGranularityKHR = (PFN_vkGetRenderingAreaGranularityKHR)LoadFunc(Device, "vkGetRenderingAreaGranularityKHR");
#endif /*  defined(VK_KHR_maintenance5)  */
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
#if defined(VK_KHR_ray_tracing_pipeline)
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
#endif /*  defined(VK_KHR_swapchain)  */
#if defined(VK_KHR_timeline_semaphore)
	FuncArray->vkGetSemaphoreCounterValueKHR = (PFN_vkGetSemaphoreCounterValueKHR)LoadFunc(Device, "vkGetSemaphoreCounterValueKHR");
	FuncArray->vkSignalSemaphoreKHR = (PFN_vkSignalSemaphoreKHR)LoadFunc(Device, "vkSignalSemaphoreKHR");
	FuncArray->vkWaitSemaphoresKHR = (PFN_vkWaitSemaphoresKHR)LoadFunc(Device, "vkWaitSemaphoresKHR");
#endif /*  defined(VK_KHR_timeline_semaphore)  */
#if defined(VK_KHR_video_encode_queue)
	FuncArray->vkGetEncodedVideoSessionParametersKHR = (PFN_vkGetEncodedVideoSessionParametersKHR)LoadFunc(Device, "vkGetEncodedVideoSessionParametersKHR");
#endif /*  defined(VK_KHR_video_encode_queue)  */
#if defined(VK_KHR_video_queue)
	FuncArray->vkBindVideoSessionMemoryKHR = (PFN_vkBindVideoSessionMemoryKHR)LoadFunc(Device, "vkBindVideoSessionMemoryKHR");
	FuncArray->vkCreateVideoSessionKHR = (PFN_vkCreateVideoSessionKHR)LoadFunc(Device, "vkCreateVideoSessionKHR");
	FuncArray->vkCreateVideoSessionParametersKHR = (PFN_vkCreateVideoSessionParametersKHR)LoadFunc(Device, "vkCreateVideoSessionParametersKHR");
	FuncArray->vkDestroyVideoSessionKHR = (PFN_vkDestroyVideoSessionKHR)LoadFunc(Device, "vkDestroyVideoSessionKHR");
	FuncArray->vkDestroyVideoSessionParametersKHR = (PFN_vkDestroyVideoSessionParametersKHR)LoadFunc(Device, "vkDestroyVideoSessionParametersKHR");
	FuncArray->vkGetVideoSessionMemoryRequirementsKHR = (PFN_vkGetVideoSessionMemoryRequirementsKHR)LoadFunc(Device, "vkGetVideoSessionMemoryRequirementsKHR");
	FuncArray->vkUpdateVideoSessionParametersKHR = (PFN_vkUpdateVideoSessionParametersKHR)LoadFunc(Device, "vkUpdateVideoSessionParametersKHR");
#endif /*  defined(VK_KHR_video_queue)  */
#if defined(VK_NVX_binary_import)
	FuncArray->vkCreateCuFunctionNVX = (PFN_vkCreateCuFunctionNVX)LoadFunc(Device, "vkCreateCuFunctionNVX");
	FuncArray->vkCreateCuModuleNVX = (PFN_vkCreateCuModuleNVX)LoadFunc(Device, "vkCreateCuModuleNVX");
	FuncArray->vkDestroyCuFunctionNVX = (PFN_vkDestroyCuFunctionNVX)LoadFunc(Device, "vkDestroyCuFunctionNVX");
	FuncArray->vkDestroyCuModuleNVX = (PFN_vkDestroyCuModuleNVX)LoadFunc(Device, "vkDestroyCuModuleNVX");
#endif /*  defined(VK_NVX_binary_import)  */
#if defined(VK_NVX_image_view_handle)
	FuncArray->vkGetImageViewAddressNVX = (PFN_vkGetImageViewAddressNVX)LoadFunc(Device, "vkGetImageViewAddressNVX");
	FuncArray->vkGetImageViewHandleNVX = (PFN_vkGetImageViewHandleNVX)LoadFunc(Device, "vkGetImageViewHandleNVX");
#endif /*  defined(VK_NVX_image_view_handle)  */
#if defined(VK_NV_cuda_kernel_launch)
	FuncArray->vkCreateCudaFunctionNV = (PFN_vkCreateCudaFunctionNV)LoadFunc(Device, "vkCreateCudaFunctionNV");
	FuncArray->vkCreateCudaModuleNV = (PFN_vkCreateCudaModuleNV)LoadFunc(Device, "vkCreateCudaModuleNV");
	FuncArray->vkDestroyCudaFunctionNV = (PFN_vkDestroyCudaFunctionNV)LoadFunc(Device, "vkDestroyCudaFunctionNV");
	FuncArray->vkDestroyCudaModuleNV = (PFN_vkDestroyCudaModuleNV)LoadFunc(Device, "vkDestroyCudaModuleNV");
	FuncArray->vkGetCudaModuleCacheNV = (PFN_vkGetCudaModuleCacheNV)LoadFunc(Device, "vkGetCudaModuleCacheNV");
#endif /*  defined(VK_NV_cuda_kernel_launch)  */
#if defined(VK_NV_device_generated_commands)
	FuncArray->vkCreateIndirectCommandsLayoutNV = (PFN_vkCreateIndirectCommandsLayoutNV)LoadFunc(Device, "vkCreateIndirectCommandsLayoutNV");
	FuncArray->vkDestroyIndirectCommandsLayoutNV = (PFN_vkDestroyIndirectCommandsLayoutNV)LoadFunc(Device, "vkDestroyIndirectCommandsLayoutNV");
	FuncArray->vkGetGeneratedCommandsMemoryRequirementsNV = (PFN_vkGetGeneratedCommandsMemoryRequirementsNV)LoadFunc(Device, "vkGetGeneratedCommandsMemoryRequirementsNV");
#endif /*  defined(VK_NV_device_generated_commands)  */
#if defined(VK_NV_device_generated_commands_compute)
	FuncArray->vkGetPipelineIndirectDeviceAddressNV = (PFN_vkGetPipelineIndirectDeviceAddressNV)LoadFunc(Device, "vkGetPipelineIndirectDeviceAddressNV");
	FuncArray->vkGetPipelineIndirectMemoryRequirementsNV = (PFN_vkGetPipelineIndirectMemoryRequirementsNV)LoadFunc(Device, "vkGetPipelineIndirectMemoryRequirementsNV");
#endif /*  defined(VK_NV_device_generated_commands_compute)  */
#if defined(VK_NV_external_memory_rdma)
	FuncArray->vkGetMemoryRemoteAddressNV = (PFN_vkGetMemoryRemoteAddressNV)LoadFunc(Device, "vkGetMemoryRemoteAddressNV");
#endif /*  defined(VK_NV_external_memory_rdma)  */
#if defined(VK_NV_external_memory_win32)
	FuncArray->vkGetMemoryWin32HandleNV = (PFN_vkGetMemoryWin32HandleNV)LoadFunc(Device, "vkGetMemoryWin32HandleNV");
#endif /*  defined(VK_NV_external_memory_win32)  */
#if defined(VK_NV_low_latency2)
	FuncArray->vkGetLatencyTimingsNV = (PFN_vkGetLatencyTimingsNV)LoadFunc(Device, "vkGetLatencyTimingsNV");
	FuncArray->vkLatencySleepNV = (PFN_vkLatencySleepNV)LoadFunc(Device, "vkLatencySleepNV");
	FuncArray->vkSetLatencyMarkerNV = (PFN_vkSetLatencyMarkerNV)LoadFunc(Device, "vkSetLatencyMarkerNV");
	FuncArray->vkSetLatencySleepModeNV = (PFN_vkSetLatencySleepModeNV)LoadFunc(Device, "vkSetLatencySleepModeNV");
#endif /*  defined(VK_NV_low_latency2)  */
#if defined(VK_NV_optical_flow)
	FuncArray->vkBindOpticalFlowSessionImageNV = (PFN_vkBindOpticalFlowSessionImageNV)LoadFunc(Device, "vkBindOpticalFlowSessionImageNV");
	FuncArray->vkCreateOpticalFlowSessionNV = (PFN_vkCreateOpticalFlowSessionNV)LoadFunc(Device, "vkCreateOpticalFlowSessionNV");
	FuncArray->vkDestroyOpticalFlowSessionNV = (PFN_vkDestroyOpticalFlowSessionNV)LoadFunc(Device, "vkDestroyOpticalFlowSessionNV");
#endif /*  defined(VK_NV_optical_flow)  */
#if defined(VK_NV_ray_tracing)
	FuncArray->vkBindAccelerationStructureMemoryNV = (PFN_vkBindAccelerationStructureMemoryNV)LoadFunc(Device, "vkBindAccelerationStructureMemoryNV");
	FuncArray->vkCompileDeferredNV = (PFN_vkCompileDeferredNV)LoadFunc(Device, "vkCompileDeferredNV");
	FuncArray->vkCreateAccelerationStructureNV = (PFN_vkCreateAccelerationStructureNV)LoadFunc(Device, "vkCreateAccelerationStructureNV");
	FuncArray->vkCreateRayTracingPipelinesNV = (PFN_vkCreateRayTracingPipelinesNV)LoadFunc(Device, "vkCreateRayTracingPipelinesNV");
	FuncArray->vkDestroyAccelerationStructureNV = (PFN_vkDestroyAccelerationStructureNV)LoadFunc(Device, "vkDestroyAccelerationStructureNV");
	FuncArray->vkGetAccelerationStructureHandleNV = (PFN_vkGetAccelerationStructureHandleNV)LoadFunc(Device, "vkGetAccelerationStructureHandleNV");
	FuncArray->vkGetAccelerationStructureMemoryRequirementsNV = (PFN_vkGetAccelerationStructureMemoryRequirementsNV)LoadFunc(Device, "vkGetAccelerationStructureMemoryRequirementsNV");
	FuncArray->vkGetRayTracingShaderGroupHandlesNV = (PFN_vkGetRayTracingShaderGroupHandlesNV)LoadFunc(Device, "vkGetRayTracingShaderGroupHandlesNV");
#endif /*  defined(VK_NV_ray_tracing)  */
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
#if (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
	FuncArray->vkGetDeviceGroupSurfacePresentModes2EXT = (PFN_vkGetDeviceGroupSurfacePresentModes2EXT)LoadFunc(Device, "vkGetDeviceGroupSurfacePresentModes2EXT");
#endif /*  (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))  */
#if (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))
	FuncArray->vkGetImageSubresourceLayout2EXT = (PFN_vkGetImageSubresourceLayout2EXT)LoadFunc(Device, "vkGetImageSubresourceLayout2EXT");
#endif /*  (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))  */
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
#if defined(VK_VERSION_1_0)
extern PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
extern PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
extern PFN_vkAllocateMemory vkAllocateMemory;
extern PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
extern PFN_vkBindBufferMemory vkBindBufferMemory;
extern PFN_vkBindImageMemory vkBindImageMemory;
extern PFN_vkCmdBeginQuery vkCmdBeginQuery;
extern PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;
extern PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;
extern PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
extern PFN_vkCmdBindPipeline vkCmdBindPipeline;
extern PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;
extern PFN_vkCmdBlitImage vkCmdBlitImage;
extern PFN_vkCmdClearAttachments vkCmdClearAttachments;
extern PFN_vkCmdClearColorImage vkCmdClearColorImage;
extern PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage;
extern PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
extern PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;
extern PFN_vkCmdCopyImage vkCmdCopyImage;
extern PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer;
extern PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults;
extern PFN_vkCmdDispatch vkCmdDispatch;
extern PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect;
extern PFN_vkCmdDraw vkCmdDraw;
extern PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
extern PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect;
extern PFN_vkCmdDrawIndirect vkCmdDrawIndirect;
extern PFN_vkCmdEndQuery vkCmdEndQuery;
extern PFN_vkCmdEndRenderPass vkCmdEndRenderPass;
extern PFN_vkCmdExecuteCommands vkCmdExecuteCommands;
extern PFN_vkCmdFillBuffer vkCmdFillBuffer;
extern PFN_vkCmdNextSubpass vkCmdNextSubpass;
extern PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;
extern PFN_vkCmdPushConstants vkCmdPushConstants;
extern PFN_vkCmdResetEvent vkCmdResetEvent;
extern PFN_vkCmdResetQueryPool vkCmdResetQueryPool;
extern PFN_vkCmdResolveImage vkCmdResolveImage;
extern PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants;
extern PFN_vkCmdSetDepthBias vkCmdSetDepthBias;
extern PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds;
extern PFN_vkCmdSetEvent vkCmdSetEvent;
extern PFN_vkCmdSetLineWidth vkCmdSetLineWidth;
extern PFN_vkCmdSetScissor vkCmdSetScissor;
extern PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask;
extern PFN_vkCmdSetStencilReference vkCmdSetStencilReference;
extern PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask;
extern PFN_vkCmdSetViewport vkCmdSetViewport;
extern PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer;
extern PFN_vkCmdWaitEvents vkCmdWaitEvents;
extern PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp;
extern PFN_vkCreateBuffer vkCreateBuffer;
extern PFN_vkCreateBufferView vkCreateBufferView;
extern PFN_vkCreateCommandPool vkCreateCommandPool;
extern PFN_vkCreateComputePipelines vkCreateComputePipelines;
extern PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
extern PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
extern PFN_vkCreateDevice vkCreateDevice;
extern PFN_vkCreateEvent vkCreateEvent;
extern PFN_vkCreateFence vkCreateFence;
extern PFN_vkCreateFramebuffer vkCreateFramebuffer;
extern PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
extern PFN_vkCreateImage vkCreateImage;
extern PFN_vkCreateImageView vkCreateImageView;
extern PFN_vkCreateInstance vkCreateInstance;
extern PFN_vkCreatePipelineCache vkCreatePipelineCache;
extern PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
extern PFN_vkCreateQueryPool vkCreateQueryPool;
extern PFN_vkCreateRenderPass vkCreateRenderPass;
extern PFN_vkCreateSampler vkCreateSampler;
extern PFN_vkCreateSemaphore vkCreateSemaphore;
extern PFN_vkCreateShaderModule vkCreateShaderModule;
extern PFN_vkDestroyBuffer vkDestroyBuffer;
extern PFN_vkDestroyBufferView vkDestroyBufferView;
extern PFN_vkDestroyCommandPool vkDestroyCommandPool;
extern PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;
extern PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;
extern PFN_vkDestroyDevice vkDestroyDevice;
extern PFN_vkDestroyEvent vkDestroyEvent;
extern PFN_vkDestroyFence vkDestroyFence;
extern PFN_vkDestroyFramebuffer vkDestroyFramebuffer;
extern PFN_vkDestroyImage vkDestroyImage;
extern PFN_vkDestroyImageView vkDestroyImageView;
extern PFN_vkDestroyInstance vkDestroyInstance;
extern PFN_vkDestroyPipeline vkDestroyPipeline;
extern PFN_vkDestroyPipelineCache vkDestroyPipelineCache;
extern PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;
extern PFN_vkDestroyQueryPool vkDestroyQueryPool;
extern PFN_vkDestroyRenderPass vkDestroyRenderPass;
extern PFN_vkDestroySampler vkDestroySampler;
extern PFN_vkDestroySemaphore vkDestroySemaphore;
extern PFN_vkDestroyShaderModule vkDestroyShaderModule;
extern PFN_vkDeviceWaitIdle vkDeviceWaitIdle;
extern PFN_vkEndCommandBuffer vkEndCommandBuffer;
extern PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties;
extern PFN_vkEnumerateDeviceLayerProperties vkEnumerateDeviceLayerProperties;
extern PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
extern PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
extern PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
extern PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
extern PFN_vkFreeCommandBuffers vkFreeCommandBuffers;
extern PFN_vkFreeDescriptorSets vkFreeDescriptorSets;
extern PFN_vkFreeMemory vkFreeMemory;
extern PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
extern PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment;
extern PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
extern PFN_vkGetDeviceQueue vkGetDeviceQueue;
extern PFN_vkGetEventStatus vkGetEventStatus;
extern PFN_vkGetFenceStatus vkGetFenceStatus;
extern PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
extern PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements;
extern PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout;
extern PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
extern PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
extern PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties;
extern PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties;
extern PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
extern PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
extern PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties;
extern PFN_vkGetPipelineCacheData vkGetPipelineCacheData;
extern PFN_vkGetQueryPoolResults vkGetQueryPoolResults;
extern PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity;
extern PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;
extern PFN_vkMapMemory vkMapMemory;
extern PFN_vkMergePipelineCaches vkMergePipelineCaches;
extern PFN_vkQueueBindSparse vkQueueBindSparse;
extern PFN_vkQueueSubmit vkQueueSubmit;
extern PFN_vkQueueWaitIdle vkQueueWaitIdle;
extern PFN_vkResetCommandBuffer vkResetCommandBuffer;
extern PFN_vkResetCommandPool vkResetCommandPool;
extern PFN_vkResetDescriptorPool vkResetDescriptorPool;
extern PFN_vkResetEvent vkResetEvent;
extern PFN_vkResetFences vkResetFences;
extern PFN_vkSetEvent vkSetEvent;
extern PFN_vkUnmapMemory vkUnmapMemory;
extern PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;
extern PFN_vkWaitForFences vkWaitForFences;
#endif /*  defined(VK_VERSION_1_0)  */
#if defined(VK_VERSION_1_1)
extern PFN_vkBindBufferMemory2 vkBindBufferMemory2;
extern PFN_vkBindImageMemory2 vkBindImageMemory2;
extern PFN_vkCmdDispatchBase vkCmdDispatchBase;
extern PFN_vkCmdSetDeviceMask vkCmdSetDeviceMask;
extern PFN_vkCreateDescriptorUpdateTemplate vkCreateDescriptorUpdateTemplate;
extern PFN_vkCreateSamplerYcbcrConversion vkCreateSamplerYcbcrConversion;
extern PFN_vkDestroyDescriptorUpdateTemplate vkDestroyDescriptorUpdateTemplate;
extern PFN_vkDestroySamplerYcbcrConversion vkDestroySamplerYcbcrConversion;
extern PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion;
extern PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups;
extern PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2;
extern PFN_vkGetDescriptorSetLayoutSupport vkGetDescriptorSetLayoutSupport;
extern PFN_vkGetDeviceGroupPeerMemoryFeatures vkGetDeviceGroupPeerMemoryFeatures;
extern PFN_vkGetDeviceQueue2 vkGetDeviceQueue2;
extern PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2;
extern PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2;
extern PFN_vkGetPhysicalDeviceExternalBufferProperties vkGetPhysicalDeviceExternalBufferProperties;
extern PFN_vkGetPhysicalDeviceExternalFenceProperties vkGetPhysicalDeviceExternalFenceProperties;
extern PFN_vkGetPhysicalDeviceExternalSemaphoreProperties vkGetPhysicalDeviceExternalSemaphoreProperties;
extern PFN_vkGetPhysicalDeviceFeatures2 vkGetPhysicalDeviceFeatures2;
extern PFN_vkGetPhysicalDeviceFormatProperties2 vkGetPhysicalDeviceFormatProperties2;
extern PFN_vkGetPhysicalDeviceImageFormatProperties2 vkGetPhysicalDeviceImageFormatProperties2;
extern PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2;
extern PFN_vkGetPhysicalDeviceProperties2 vkGetPhysicalDeviceProperties2;
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties2 vkGetPhysicalDeviceQueueFamilyProperties2;
extern PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2;
extern PFN_vkTrimCommandPool vkTrimCommandPool;
extern PFN_vkUpdateDescriptorSetWithTemplate vkUpdateDescriptorSetWithTemplate;
#endif /*  defined(VK_VERSION_1_1)  */
#if defined(VK_VERSION_1_2)
extern PFN_vkCmdBeginRenderPass2 vkCmdBeginRenderPass2;
extern PFN_vkCmdDrawIndexedIndirectCount vkCmdDrawIndexedIndirectCount;
extern PFN_vkCmdDrawIndirectCount vkCmdDrawIndirectCount;
extern PFN_vkCmdEndRenderPass2 vkCmdEndRenderPass2;
extern PFN_vkCmdNextSubpass2 vkCmdNextSubpass2;
extern PFN_vkCreateRenderPass2 vkCreateRenderPass2;
extern PFN_vkGetBufferDeviceAddress vkGetBufferDeviceAddress;
extern PFN_vkGetBufferOpaqueCaptureAddress vkGetBufferOpaqueCaptureAddress;
extern PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress;
extern PFN_vkGetSemaphoreCounterValue vkGetSemaphoreCounterValue;
extern PFN_vkResetQueryPool vkResetQueryPool;
extern PFN_vkSignalSemaphore vkSignalSemaphore;
extern PFN_vkWaitSemaphores vkWaitSemaphores;
#endif /*  defined(VK_VERSION_1_2)  */
#if defined(VK_VERSION_1_3)
extern PFN_vkCmdBeginRendering vkCmdBeginRendering;
extern PFN_vkCmdBindVertexBuffers2 vkCmdBindVertexBuffers2;
extern PFN_vkCmdBlitImage2 vkCmdBlitImage2;
extern PFN_vkCmdCopyBuffer2 vkCmdCopyBuffer2;
extern PFN_vkCmdCopyBufferToImage2 vkCmdCopyBufferToImage2;
extern PFN_vkCmdCopyImage2 vkCmdCopyImage2;
extern PFN_vkCmdCopyImageToBuffer2 vkCmdCopyImageToBuffer2;
extern PFN_vkCmdEndRendering vkCmdEndRendering;
extern PFN_vkCmdPipelineBarrier2 vkCmdPipelineBarrier2;
extern PFN_vkCmdResetEvent2 vkCmdResetEvent2;
extern PFN_vkCmdResolveImage2 vkCmdResolveImage2;
extern PFN_vkCmdSetCullMode vkCmdSetCullMode;
extern PFN_vkCmdSetDepthBiasEnable vkCmdSetDepthBiasEnable;
extern PFN_vkCmdSetDepthBoundsTestEnable vkCmdSetDepthBoundsTestEnable;
extern PFN_vkCmdSetDepthCompareOp vkCmdSetDepthCompareOp;
extern PFN_vkCmdSetDepthTestEnable vkCmdSetDepthTestEnable;
extern PFN_vkCmdSetDepthWriteEnable vkCmdSetDepthWriteEnable;
extern PFN_vkCmdSetEvent2 vkCmdSetEvent2;
extern PFN_vkCmdSetFrontFace vkCmdSetFrontFace;
extern PFN_vkCmdSetPrimitiveRestartEnable vkCmdSetPrimitiveRestartEnable;
extern PFN_vkCmdSetPrimitiveTopology vkCmdSetPrimitiveTopology;
extern PFN_vkCmdSetRasterizerDiscardEnable vkCmdSetRasterizerDiscardEnable;
extern PFN_vkCmdSetScissorWithCount vkCmdSetScissorWithCount;
extern PFN_vkCmdSetStencilOp vkCmdSetStencilOp;
extern PFN_vkCmdSetStencilTestEnable vkCmdSetStencilTestEnable;
extern PFN_vkCmdSetViewportWithCount vkCmdSetViewportWithCount;
extern PFN_vkCmdWaitEvents2 vkCmdWaitEvents2;
extern PFN_vkCmdWriteTimestamp2 vkCmdWriteTimestamp2;
extern PFN_vkCreatePrivateDataSlot vkCreatePrivateDataSlot;
extern PFN_vkDestroyPrivateDataSlot vkDestroyPrivateDataSlot;
extern PFN_vkGetDeviceBufferMemoryRequirements vkGetDeviceBufferMemoryRequirements;
extern PFN_vkGetDeviceImageMemoryRequirements vkGetDeviceImageMemoryRequirements;
extern PFN_vkGetDeviceImageSparseMemoryRequirements vkGetDeviceImageSparseMemoryRequirements;
extern PFN_vkGetPhysicalDeviceToolProperties vkGetPhysicalDeviceToolProperties;
extern PFN_vkGetPrivateData vkGetPrivateData;
extern PFN_vkQueueSubmit2 vkQueueSubmit2;
extern PFN_vkSetPrivateData vkSetPrivateData;
#endif /*  defined(VK_VERSION_1_3)  */
#if defined(VK_AMDX_shader_enqueue)
extern PFN_vkCmdDispatchGraphAMDX vkCmdDispatchGraphAMDX;
extern PFN_vkCmdDispatchGraphIndirectAMDX vkCmdDispatchGraphIndirectAMDX;
extern PFN_vkCmdDispatchGraphIndirectCountAMDX vkCmdDispatchGraphIndirectCountAMDX;
extern PFN_vkCmdInitializeGraphScratchMemoryAMDX vkCmdInitializeGraphScratchMemoryAMDX;
extern PFN_vkCreateExecutionGraphPipelinesAMDX vkCreateExecutionGraphPipelinesAMDX;
extern PFN_vkGetExecutionGraphPipelineNodeIndexAMDX vkGetExecutionGraphPipelineNodeIndexAMDX;
extern PFN_vkGetExecutionGraphPipelineScratchSizeAMDX vkGetExecutionGraphPipelineScratchSizeAMDX;
#endif /*  defined(VK_AMDX_shader_enqueue)  */
#if defined(VK_AMD_anti_lag)
extern PFN_vkAntiLagUpdateAMD vkAntiLagUpdateAMD;
#endif /*  defined(VK_AMD_anti_lag)  */
#if defined(VK_AMD_buffer_marker)
extern PFN_vkCmdWriteBufferMarkerAMD vkCmdWriteBufferMarkerAMD;
#endif /*  defined(VK_AMD_buffer_marker)  */
#if defined(VK_AMD_display_native_hdr)
extern PFN_vkSetLocalDimmingAMD vkSetLocalDimmingAMD;
#endif /*  defined(VK_AMD_display_native_hdr)  */
#if defined(VK_AMD_draw_indirect_count)
extern PFN_vkCmdDrawIndexedIndirectCountAMD vkCmdDrawIndexedIndirectCountAMD;
extern PFN_vkCmdDrawIndirectCountAMD vkCmdDrawIndirectCountAMD;
#endif /*  defined(VK_AMD_draw_indirect_count)  */
#if defined(VK_AMD_shader_info)
extern PFN_vkGetShaderInfoAMD vkGetShaderInfoAMD;
#endif /*  defined(VK_AMD_shader_info)  */
#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
extern PFN_vkGetAndroidHardwareBufferPropertiesANDROID vkGetAndroidHardwareBufferPropertiesANDROID;
extern PFN_vkGetMemoryAndroidHardwareBufferANDROID vkGetMemoryAndroidHardwareBufferANDROID;
#endif /*  defined(VK_ANDROID_external_memory_android_hardware_buffer)  */
#if defined(VK_EXT_acquire_drm_display)
extern PFN_vkAcquireDrmDisplayEXT vkAcquireDrmDisplayEXT;
extern PFN_vkGetDrmDisplayEXT vkGetDrmDisplayEXT;
#endif /*  defined(VK_EXT_acquire_drm_display)  */
#if defined(VK_EXT_acquire_xlib_display)
extern PFN_vkAcquireXlibDisplayEXT vkAcquireXlibDisplayEXT;
extern PFN_vkGetRandROutputDisplayEXT vkGetRandROutputDisplayEXT;
#endif /*  defined(VK_EXT_acquire_xlib_display)  */
#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
extern PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT vkCmdSetAttachmentFeedbackLoopEnableEXT;
#endif /*  defined(VK_EXT_attachment_feedback_loop_dynamic_state)  */
#if defined(VK_EXT_buffer_device_address)
extern PFN_vkGetBufferDeviceAddressEXT vkGetBufferDeviceAddressEXT;
#endif /*  defined(VK_EXT_buffer_device_address)  */
#if defined(VK_EXT_calibrated_timestamps)
extern PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT;
extern PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT;
#endif /*  defined(VK_EXT_calibrated_timestamps)  */
#if defined(VK_EXT_color_write_enable)
extern PFN_vkCmdSetColorWriteEnableEXT vkCmdSetColorWriteEnableEXT;
#endif /*  defined(VK_EXT_color_write_enable)  */
#if defined(VK_EXT_conditional_rendering)
extern PFN_vkCmdBeginConditionalRenderingEXT vkCmdBeginConditionalRenderingEXT;
extern PFN_vkCmdEndConditionalRenderingEXT vkCmdEndConditionalRenderingEXT;
#endif /*  defined(VK_EXT_conditional_rendering)  */
#if defined(VK_EXT_debug_marker)
extern PFN_vkCmdDebugMarkerBeginEXT vkCmdDebugMarkerBeginEXT;
extern PFN_vkCmdDebugMarkerEndEXT vkCmdDebugMarkerEndEXT;
extern PFN_vkCmdDebugMarkerInsertEXT vkCmdDebugMarkerInsertEXT;
extern PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectNameEXT;
extern PFN_vkDebugMarkerSetObjectTagEXT vkDebugMarkerSetObjectTagEXT;
#endif /*  defined(VK_EXT_debug_marker)  */
#if defined(VK_EXT_debug_report)
extern PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
extern PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT;
extern PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
#endif /*  defined(VK_EXT_debug_report)  */
#if defined(VK_EXT_debug_utils)
extern PFN_vkCmdBeginDebugUtilsLabelEXT vkCmdBeginDebugUtilsLabelEXT;
extern PFN_vkCmdEndDebugUtilsLabelEXT vkCmdEndDebugUtilsLabelEXT;
extern PFN_vkCmdInsertDebugUtilsLabelEXT vkCmdInsertDebugUtilsLabelEXT;
extern PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
extern PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
extern PFN_vkQueueBeginDebugUtilsLabelEXT vkQueueBeginDebugUtilsLabelEXT;
extern PFN_vkQueueEndDebugUtilsLabelEXT vkQueueEndDebugUtilsLabelEXT;
extern PFN_vkQueueInsertDebugUtilsLabelEXT vkQueueInsertDebugUtilsLabelEXT;
extern PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT;
extern PFN_vkSetDebugUtilsObjectTagEXT vkSetDebugUtilsObjectTagEXT;
extern PFN_vkSubmitDebugUtilsMessageEXT vkSubmitDebugUtilsMessageEXT;
#endif /*  defined(VK_EXT_debug_utils)  */
#if defined(VK_EXT_depth_bias_control)
extern PFN_vkCmdSetDepthBias2EXT vkCmdSetDepthBias2EXT;
#endif /*  defined(VK_EXT_depth_bias_control)  */
#if defined(VK_EXT_descriptor_buffer)
extern PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT vkCmdBindDescriptorBufferEmbeddedSamplersEXT;
extern PFN_vkCmdBindDescriptorBuffersEXT vkCmdBindDescriptorBuffersEXT;
extern PFN_vkCmdSetDescriptorBufferOffsetsEXT vkCmdSetDescriptorBufferOffsetsEXT;
extern PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT vkGetBufferOpaqueCaptureDescriptorDataEXT;
extern PFN_vkGetDescriptorEXT vkGetDescriptorEXT;
extern PFN_vkGetDescriptorSetLayoutBindingOffsetEXT vkGetDescriptorSetLayoutBindingOffsetEXT;
extern PFN_vkGetDescriptorSetLayoutSizeEXT vkGetDescriptorSetLayoutSizeEXT;
extern PFN_vkGetImageOpaqueCaptureDescriptorDataEXT vkGetImageOpaqueCaptureDescriptorDataEXT;
extern PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT vkGetImageViewOpaqueCaptureDescriptorDataEXT;
extern PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT vkGetSamplerOpaqueCaptureDescriptorDataEXT;
#endif /*  defined(VK_EXT_descriptor_buffer)  */
#if defined(VK_EXT_descriptor_buffer) && (defined(VK_KHR_acceleration_structure) || defined(VK_NV_ray_tracing))
extern PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT;
#endif /*  defined(VK_EXT_descriptor_buffer) && (defined(VK_KHR_acceleration_structure) || defined(VK_NV_ray_tracing))  */
#if defined(VK_EXT_device_fault)
extern PFN_vkGetDeviceFaultInfoEXT vkGetDeviceFaultInfoEXT;
#endif /*  defined(VK_EXT_device_fault)  */
#if defined(VK_EXT_direct_mode_display)
extern PFN_vkReleaseDisplayEXT vkReleaseDisplayEXT;
#endif /*  defined(VK_EXT_direct_mode_display)  */
#if defined(VK_EXT_directfb_surface)
extern PFN_vkCreateDirectFBSurfaceEXT vkCreateDirectFBSurfaceEXT;
extern PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT vkGetPhysicalDeviceDirectFBPresentationSupportEXT;
#endif /*  defined(VK_EXT_directfb_surface)  */
#if defined(VK_EXT_discard_rectangles)
extern PFN_vkCmdSetDiscardRectangleEXT vkCmdSetDiscardRectangleEXT;
#endif /*  defined(VK_EXT_discard_rectangles)  */
#if defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2
extern PFN_vkCmdSetDiscardRectangleEnableEXT vkCmdSetDiscardRectangleEnableEXT;
extern PFN_vkCmdSetDiscardRectangleModeEXT vkCmdSetDiscardRectangleModeEXT;
#endif /*  defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2  */
#if defined(VK_EXT_display_control)
extern PFN_vkDisplayPowerControlEXT vkDisplayPowerControlEXT;
extern PFN_vkGetSwapchainCounterEXT vkGetSwapchainCounterEXT;
extern PFN_vkRegisterDeviceEventEXT vkRegisterDeviceEventEXT;
extern PFN_vkRegisterDisplayEventEXT vkRegisterDisplayEventEXT;
#endif /*  defined(VK_EXT_display_control)  */
#if defined(VK_EXT_display_surface_counter)
extern PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT vkGetPhysicalDeviceSurfaceCapabilities2EXT;
#endif /*  defined(VK_EXT_display_surface_counter)  */
#if defined(VK_EXT_external_memory_host)
extern PFN_vkGetMemoryHostPointerPropertiesEXT vkGetMemoryHostPointerPropertiesEXT;
#endif /*  defined(VK_EXT_external_memory_host)  */
#if defined(VK_EXT_full_screen_exclusive)
extern PFN_vkAcquireFullScreenExclusiveModeEXT vkAcquireFullScreenExclusiveModeEXT;
extern PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT vkGetPhysicalDeviceSurfacePresentModes2EXT;
extern PFN_vkReleaseFullScreenExclusiveModeEXT vkReleaseFullScreenExclusiveModeEXT;
#endif /*  defined(VK_EXT_full_screen_exclusive)  */
#if defined(VK_EXT_hdr_metadata)
extern PFN_vkSetHdrMetadataEXT vkSetHdrMetadataEXT;
#endif /*  defined(VK_EXT_hdr_metadata)  */
#if defined(VK_EXT_headless_surface)
extern PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT;
#endif /*  defined(VK_EXT_headless_surface)  */
#if defined(VK_EXT_host_image_copy)
extern PFN_vkCopyImageToImageEXT vkCopyImageToImageEXT;
extern PFN_vkCopyImageToMemoryEXT vkCopyImageToMemoryEXT;
extern PFN_vkCopyMemoryToImageEXT vkCopyMemoryToImageEXT;
extern PFN_vkTransitionImageLayoutEXT vkTransitionImageLayoutEXT;
#endif /*  defined(VK_EXT_host_image_copy)  */
#if defined(VK_EXT_host_query_reset)
extern PFN_vkResetQueryPoolEXT vkResetQueryPoolEXT;
#endif /*  defined(VK_EXT_host_query_reset)  */
#if defined(VK_EXT_image_drm_format_modifier)
extern PFN_vkGetImageDrmFormatModifierPropertiesEXT vkGetImageDrmFormatModifierPropertiesEXT;
#endif /*  defined(VK_EXT_image_drm_format_modifier)  */
#if defined(VK_EXT_line_rasterization)
extern PFN_vkCmdSetLineStippleEXT vkCmdSetLineStippleEXT;
#endif /*  defined(VK_EXT_line_rasterization)  */
#if defined(VK_EXT_mesh_shader)
extern PFN_vkCmdDrawMeshTasksEXT vkCmdDrawMeshTasksEXT;
extern PFN_vkCmdDrawMeshTasksIndirectCountEXT vkCmdDrawMeshTasksIndirectCountEXT;
extern PFN_vkCmdDrawMeshTasksIndirectEXT vkCmdDrawMeshTasksIndirectEXT;
#endif /*  defined(VK_EXT_mesh_shader)  */
#if defined(VK_EXT_metal_objects)
extern PFN_vkExportMetalObjectsEXT vkExportMetalObjectsEXT;
#endif /*  defined(VK_EXT_metal_objects)  */
#if defined(VK_EXT_metal_surface)
extern PFN_vkCreateMetalSurfaceEXT vkCreateMetalSurfaceEXT;
#endif /*  defined(VK_EXT_metal_surface)  */
#if defined(VK_EXT_multi_draw)
extern PFN_vkCmdDrawMultiEXT vkCmdDrawMultiEXT;
extern PFN_vkCmdDrawMultiIndexedEXT vkCmdDrawMultiIndexedEXT;
#endif /*  defined(VK_EXT_multi_draw)  */
#if defined(VK_EXT_opacity_micromap)
extern PFN_vkBuildMicromapsEXT vkBuildMicromapsEXT;
extern PFN_vkCmdBuildMicromapsEXT vkCmdBuildMicromapsEXT;
extern PFN_vkCmdCopyMemoryToMicromapEXT vkCmdCopyMemoryToMicromapEXT;
extern PFN_vkCmdCopyMicromapEXT vkCmdCopyMicromapEXT;
extern PFN_vkCmdCopyMicromapToMemoryEXT vkCmdCopyMicromapToMemoryEXT;
extern PFN_vkCmdWriteMicromapsPropertiesEXT vkCmdWriteMicromapsPropertiesEXT;
extern PFN_vkCopyMemoryToMicromapEXT vkCopyMemoryToMicromapEXT;
extern PFN_vkCopyMicromapEXT vkCopyMicromapEXT;
extern PFN_vkCopyMicromapToMemoryEXT vkCopyMicromapToMemoryEXT;
extern PFN_vkCreateMicromapEXT vkCreateMicromapEXT;
extern PFN_vkDestroyMicromapEXT vkDestroyMicromapEXT;
extern PFN_vkGetDeviceMicromapCompatibilityEXT vkGetDeviceMicromapCompatibilityEXT;
extern PFN_vkGetMicromapBuildSizesEXT vkGetMicromapBuildSizesEXT;
extern PFN_vkWriteMicromapsPropertiesEXT vkWriteMicromapsPropertiesEXT;
#endif /*  defined(VK_EXT_opacity_micromap)  */
#if defined(VK_EXT_pageable_device_local_memory)
extern PFN_vkSetDeviceMemoryPriorityEXT vkSetDeviceMemoryPriorityEXT;
#endif /*  defined(VK_EXT_pageable_device_local_memory)  */
#if defined(VK_EXT_pipeline_properties)
extern PFN_vkGetPipelinePropertiesEXT vkGetPipelinePropertiesEXT;
#endif /*  defined(VK_EXT_pipeline_properties)  */
#if defined(VK_EXT_private_data)
extern PFN_vkCreatePrivateDataSlotEXT vkCreatePrivateDataSlotEXT;
extern PFN_vkDestroyPrivateDataSlotEXT vkDestroyPrivateDataSlotEXT;
extern PFN_vkGetPrivateDataEXT vkGetPrivateDataEXT;
extern PFN_vkSetPrivateDataEXT vkSetPrivateDataEXT;
#endif /*  defined(VK_EXT_private_data)  */
#if defined(VK_EXT_sample_locations)
extern PFN_vkCmdSetSampleLocationsEXT vkCmdSetSampleLocationsEXT;
extern PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT vkGetPhysicalDeviceMultisamplePropertiesEXT;
#endif /*  defined(VK_EXT_sample_locations)  */
#if defined(VK_EXT_shader_module_identifier)
extern PFN_vkGetShaderModuleCreateInfoIdentifierEXT vkGetShaderModuleCreateInfoIdentifierEXT;
extern PFN_vkGetShaderModuleIdentifierEXT vkGetShaderModuleIdentifierEXT;
#endif /*  defined(VK_EXT_shader_module_identifier)  */
#if defined(VK_EXT_shader_object)
extern PFN_vkCmdBindShadersEXT vkCmdBindShadersEXT;
extern PFN_vkCreateShadersEXT vkCreateShadersEXT;
extern PFN_vkDestroyShaderEXT vkDestroyShaderEXT;
extern PFN_vkGetShaderBinaryDataEXT vkGetShaderBinaryDataEXT;
#endif /*  defined(VK_EXT_shader_object)  */
#if defined(VK_EXT_swapchain_maintenance1)
extern PFN_vkReleaseSwapchainImagesEXT vkReleaseSwapchainImagesEXT;
#endif /*  defined(VK_EXT_swapchain_maintenance1)  */
#if defined(VK_EXT_tooling_info)
extern PFN_vkGetPhysicalDeviceToolPropertiesEXT vkGetPhysicalDeviceToolPropertiesEXT;
#endif /*  defined(VK_EXT_tooling_info)  */
#if defined(VK_EXT_transform_feedback)
extern PFN_vkCmdBeginQueryIndexedEXT vkCmdBeginQueryIndexedEXT;
extern PFN_vkCmdBeginTransformFeedbackEXT vkCmdBeginTransformFeedbackEXT;
extern PFN_vkCmdBindTransformFeedbackBuffersEXT vkCmdBindTransformFeedbackBuffersEXT;
extern PFN_vkCmdDrawIndirectByteCountEXT vkCmdDrawIndirectByteCountEXT;
extern PFN_vkCmdEndQueryIndexedEXT vkCmdEndQueryIndexedEXT;
extern PFN_vkCmdEndTransformFeedbackEXT vkCmdEndTransformFeedbackEXT;
#endif /*  defined(VK_EXT_transform_feedback)  */
#if defined(VK_EXT_validation_cache)
extern PFN_vkCreateValidationCacheEXT vkCreateValidationCacheEXT;
extern PFN_vkDestroyValidationCacheEXT vkDestroyValidationCacheEXT;
extern PFN_vkGetValidationCacheDataEXT vkGetValidationCacheDataEXT;
extern PFN_vkMergeValidationCachesEXT vkMergeValidationCachesEXT;
#endif /*  defined(VK_EXT_validation_cache)  */
#if defined(VK_FUCHSIA_buffer_collection)
extern PFN_vkCreateBufferCollectionFUCHSIA vkCreateBufferCollectionFUCHSIA;
extern PFN_vkDestroyBufferCollectionFUCHSIA vkDestroyBufferCollectionFUCHSIA;
extern PFN_vkGetBufferCollectionPropertiesFUCHSIA vkGetBufferCollectionPropertiesFUCHSIA;
extern PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA vkSetBufferCollectionBufferConstraintsFUCHSIA;
extern PFN_vkSetBufferCollectionImageConstraintsFUCHSIA vkSetBufferCollectionImageConstraintsFUCHSIA;
#endif /*  defined(VK_FUCHSIA_buffer_collection)  */
#if defined(VK_FUCHSIA_external_memory)
extern PFN_vkGetMemoryZirconHandleFUCHSIA vkGetMemoryZirconHandleFUCHSIA;
extern PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA vkGetMemoryZirconHandlePropertiesFUCHSIA;
#endif /*  defined(VK_FUCHSIA_external_memory)  */
#if defined(VK_FUCHSIA_external_semaphore)
extern PFN_vkGetSemaphoreZirconHandleFUCHSIA vkGetSemaphoreZirconHandleFUCHSIA;
extern PFN_vkImportSemaphoreZirconHandleFUCHSIA vkImportSemaphoreZirconHandleFUCHSIA;
#endif /*  defined(VK_FUCHSIA_external_semaphore)  */
#if defined(VK_FUCHSIA_imagepipe_surface)
extern PFN_vkCreateImagePipeSurfaceFUCHSIA vkCreateImagePipeSurfaceFUCHSIA;
#endif /*  defined(VK_FUCHSIA_imagepipe_surface)  */
#if defined(VK_GGP_stream_descriptor_surface)
extern PFN_vkCreateStreamDescriptorSurfaceGGP vkCreateStreamDescriptorSurfaceGGP;
#endif /*  defined(VK_GGP_stream_descriptor_surface)  */
#if defined(VK_GOOGLE_display_timing)
extern PFN_vkGetPastPresentationTimingGOOGLE vkGetPastPresentationTimingGOOGLE;
extern PFN_vkGetRefreshCycleDurationGOOGLE vkGetRefreshCycleDurationGOOGLE;
#endif /*  defined(VK_GOOGLE_display_timing)  */
#if defined(VK_HUAWEI_cluster_culling_shader)
extern PFN_vkCmdDrawClusterHUAWEI vkCmdDrawClusterHUAWEI;
extern PFN_vkCmdDrawClusterIndirectHUAWEI vkCmdDrawClusterIndirectHUAWEI;
#endif /*  defined(VK_HUAWEI_cluster_culling_shader)  */
#if defined(VK_HUAWEI_invocation_mask)
extern PFN_vkCmdBindInvocationMaskHUAWEI vkCmdBindInvocationMaskHUAWEI;
#endif /*  defined(VK_HUAWEI_invocation_mask)  */
#if defined(VK_HUAWEI_subpass_shading)
extern PFN_vkCmdSubpassShadingHUAWEI vkCmdSubpassShadingHUAWEI;
extern PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI;
#endif /*  defined(VK_HUAWEI_subpass_shading)  */
#if defined(VK_INTEL_performance_query)
extern PFN_vkAcquirePerformanceConfigurationINTEL vkAcquirePerformanceConfigurationINTEL;
extern PFN_vkCmdSetPerformanceMarkerINTEL vkCmdSetPerformanceMarkerINTEL;
extern PFN_vkCmdSetPerformanceOverrideINTEL vkCmdSetPerformanceOverrideINTEL;
extern PFN_vkCmdSetPerformanceStreamMarkerINTEL vkCmdSetPerformanceStreamMarkerINTEL;
extern PFN_vkGetPerformanceParameterINTEL vkGetPerformanceParameterINTEL;
extern PFN_vkInitializePerformanceApiINTEL vkInitializePerformanceApiINTEL;
extern PFN_vkQueueSetPerformanceConfigurationINTEL vkQueueSetPerformanceConfigurationINTEL;
extern PFN_vkReleasePerformanceConfigurationINTEL vkReleasePerformanceConfigurationINTEL;
extern PFN_vkUninitializePerformanceApiINTEL vkUninitializePerformanceApiINTEL;
#endif /*  defined(VK_INTEL_performance_query)  */
#if defined(VK_KHR_acceleration_structure)
extern PFN_vkBuildAccelerationStructuresKHR vkBuildAccelerationStructuresKHR;
extern PFN_vkCmdBuildAccelerationStructuresIndirectKHR vkCmdBuildAccelerationStructuresIndirectKHR;
extern PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR;
extern PFN_vkCmdCopyAccelerationStructureKHR vkCmdCopyAccelerationStructureKHR;
extern PFN_vkCmdCopyAccelerationStructureToMemoryKHR vkCmdCopyAccelerationStructureToMemoryKHR;
extern PFN_vkCmdCopyMemoryToAccelerationStructureKHR vkCmdCopyMemoryToAccelerationStructureKHR;
extern PFN_vkCmdWriteAccelerationStructuresPropertiesKHR vkCmdWriteAccelerationStructuresPropertiesKHR;
extern PFN_vkCopyAccelerationStructureKHR vkCopyAccelerationStructureKHR;
extern PFN_vkCopyAccelerationStructureToMemoryKHR vkCopyAccelerationStructureToMemoryKHR;
extern PFN_vkCopyMemoryToAccelerationStructureKHR vkCopyMemoryToAccelerationStructureKHR;
extern PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
extern PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR;
extern PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR;
extern PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
extern PFN_vkGetDeviceAccelerationStructureCompatibilityKHR vkGetDeviceAccelerationStructureCompatibilityKHR;
extern PFN_vkWriteAccelerationStructuresPropertiesKHR vkWriteAccelerationStructuresPropertiesKHR;
#endif /*  defined(VK_KHR_acceleration_structure)  */
#if defined(VK_KHR_android_surface)
extern PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
#endif /*  defined(VK_KHR_android_surface)  */
#if defined(VK_KHR_bind_memory2)
extern PFN_vkBindBufferMemory2KHR vkBindBufferMemory2KHR;
extern PFN_vkBindImageMemory2KHR vkBindImageMemory2KHR;
#endif /*  defined(VK_KHR_bind_memory2)  */
#if defined(VK_KHR_buffer_device_address)
extern PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR;
extern PFN_vkGetBufferOpaqueCaptureAddressKHR vkGetBufferOpaqueCaptureAddressKHR;
extern PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR vkGetDeviceMemoryOpaqueCaptureAddressKHR;
#endif /*  defined(VK_KHR_buffer_device_address)  */
#if defined(VK_KHR_calibrated_timestamps)
extern PFN_vkGetCalibratedTimestampsKHR vkGetCalibratedTimestampsKHR;
extern PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR vkGetPhysicalDeviceCalibrateableTimeDomainsKHR;
#endif /*  defined(VK_KHR_calibrated_timestamps)  */
#if defined(VK_KHR_cooperative_matrix)
extern PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR;
#endif /*  defined(VK_KHR_cooperative_matrix)  */
#if defined(VK_KHR_copy_commands2)
extern PFN_vkCmdBlitImage2KHR vkCmdBlitImage2KHR;
extern PFN_vkCmdCopyBuffer2KHR vkCmdCopyBuffer2KHR;
extern PFN_vkCmdCopyBufferToImage2KHR vkCmdCopyBufferToImage2KHR;
extern PFN_vkCmdCopyImage2KHR vkCmdCopyImage2KHR;
extern PFN_vkCmdCopyImageToBuffer2KHR vkCmdCopyImageToBuffer2KHR;
extern PFN_vkCmdResolveImage2KHR vkCmdResolveImage2KHR;
#endif /*  defined(VK_KHR_copy_commands2)  */
#if defined(VK_KHR_create_renderpass2)
extern PFN_vkCmdBeginRenderPass2KHR vkCmdBeginRenderPass2KHR;
extern PFN_vkCmdEndRenderPass2KHR vkCmdEndRenderPass2KHR;
extern PFN_vkCmdNextSubpass2KHR vkCmdNextSubpass2KHR;
extern PFN_vkCreateRenderPass2KHR vkCreateRenderPass2KHR;
#endif /*  defined(VK_KHR_create_renderpass2)  */
#if defined(VK_KHR_deferred_host_operations)
extern PFN_vkCreateDeferredOperationKHR vkCreateDeferredOperationKHR;
extern PFN_vkDeferredOperationJoinKHR vkDeferredOperationJoinKHR;
extern PFN_vkDestroyDeferredOperationKHR vkDestroyDeferredOperationKHR;
extern PFN_vkGetDeferredOperationMaxConcurrencyKHR vkGetDeferredOperationMaxConcurrencyKHR;
extern PFN_vkGetDeferredOperationResultKHR vkGetDeferredOperationResultKHR;
#endif /*  defined(VK_KHR_deferred_host_operations)  */
#if defined(VK_KHR_descriptor_update_template)
extern PFN_vkCreateDescriptorUpdateTemplateKHR vkCreateDescriptorUpdateTemplateKHR;
extern PFN_vkDestroyDescriptorUpdateTemplateKHR vkDestroyDescriptorUpdateTemplateKHR;
extern PFN_vkUpdateDescriptorSetWithTemplateKHR vkUpdateDescriptorSetWithTemplateKHR;
#endif /*  defined(VK_KHR_descriptor_update_template)  */
#if defined(VK_KHR_device_group)
extern PFN_vkCmdDispatchBaseKHR vkCmdDispatchBaseKHR;
extern PFN_vkCmdSetDeviceMaskKHR vkCmdSetDeviceMaskKHR;
extern PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR vkGetDeviceGroupPeerMemoryFeaturesKHR;
#endif /*  defined(VK_KHR_device_group)  */
#if defined(VK_KHR_device_group_creation)
extern PFN_vkEnumeratePhysicalDeviceGroupsKHR vkEnumeratePhysicalDeviceGroupsKHR;
#endif /*  defined(VK_KHR_device_group_creation)  */
#if defined(VK_KHR_display)
extern PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR;
extern PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR;
extern PFN_vkGetDisplayModePropertiesKHR vkGetDisplayModePropertiesKHR;
extern PFN_vkGetDisplayPlaneCapabilitiesKHR vkGetDisplayPlaneCapabilitiesKHR;
extern PFN_vkGetDisplayPlaneSupportedDisplaysKHR vkGetDisplayPlaneSupportedDisplaysKHR;
extern PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
extern PFN_vkGetPhysicalDeviceDisplayPropertiesKHR vkGetPhysicalDeviceDisplayPropertiesKHR;
#endif /*  defined(VK_KHR_display)  */
#if defined(VK_KHR_display_swapchain)
extern PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR;
#endif /*  defined(VK_KHR_display_swapchain)  */
#if defined(VK_KHR_draw_indirect_count)
extern PFN_vkCmdDrawIndexedIndirectCountKHR vkCmdDrawIndexedIndirectCountKHR;
extern PFN_vkCmdDrawIndirectCountKHR vkCmdDrawIndirectCountKHR;
#endif /*  defined(VK_KHR_draw_indirect_count)  */
#if defined(VK_KHR_dynamic_rendering)
extern PFN_vkCmdBeginRenderingKHR vkCmdBeginRenderingKHR;
extern PFN_vkCmdEndRenderingKHR vkCmdEndRenderingKHR;
#endif /*  defined(VK_KHR_dynamic_rendering)  */
#if defined(VK_KHR_dynamic_rendering_local_read)
extern PFN_vkCmdSetRenderingAttachmentLocationsKHR vkCmdSetRenderingAttachmentLocationsKHR;
extern PFN_vkCmdSetRenderingInputAttachmentIndicesKHR vkCmdSetRenderingInputAttachmentIndicesKHR;
#endif /*  defined(VK_KHR_dynamic_rendering_local_read)  */
#if defined(VK_KHR_external_fence_capabilities)
extern PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR vkGetPhysicalDeviceExternalFencePropertiesKHR;
#endif /*  defined(VK_KHR_external_fence_capabilities)  */
#if defined(VK_KHR_external_fence_fd)
extern PFN_vkGetFenceFdKHR vkGetFenceFdKHR;
extern PFN_vkImportFenceFdKHR vkImportFenceFdKHR;
#endif /*  defined(VK_KHR_external_fence_fd)  */
#if defined(VK_KHR_external_fence_win32)
extern PFN_vkGetFenceWin32HandleKHR vkGetFenceWin32HandleKHR;
extern PFN_vkImportFenceWin32HandleKHR vkImportFenceWin32HandleKHR;
#endif /*  defined(VK_KHR_external_fence_win32)  */
#if defined(VK_KHR_external_memory_capabilities)
extern PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR vkGetPhysicalDeviceExternalBufferPropertiesKHR;
#endif /*  defined(VK_KHR_external_memory_capabilities)  */
#if defined(VK_KHR_external_memory_fd)
extern PFN_vkGetMemoryFdKHR vkGetMemoryFdKHR;
extern PFN_vkGetMemoryFdPropertiesKHR vkGetMemoryFdPropertiesKHR;
#endif /*  defined(VK_KHR_external_memory_fd)  */
#if defined(VK_KHR_external_memory_win32)
extern PFN_vkGetMemoryWin32HandleKHR vkGetMemoryWin32HandleKHR;
extern PFN_vkGetMemoryWin32HandlePropertiesKHR vkGetMemoryWin32HandlePropertiesKHR;
#endif /*  defined(VK_KHR_external_memory_win32)  */
#if defined(VK_KHR_external_semaphore_capabilities)
extern PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
#endif /*  defined(VK_KHR_external_semaphore_capabilities)  */
#if defined(VK_KHR_external_semaphore_fd)
extern PFN_vkGetSemaphoreFdKHR vkGetSemaphoreFdKHR;
extern PFN_vkImportSemaphoreFdKHR vkImportSemaphoreFdKHR;
#endif /*  defined(VK_KHR_external_semaphore_fd)  */
#if defined(VK_KHR_external_semaphore_win32)
extern PFN_vkGetSemaphoreWin32HandleKHR vkGetSemaphoreWin32HandleKHR;
extern PFN_vkImportSemaphoreWin32HandleKHR vkImportSemaphoreWin32HandleKHR;
#endif /*  defined(VK_KHR_external_semaphore_win32)  */
#if defined(VK_KHR_fragment_shading_rate)
extern PFN_vkCmdSetFragmentShadingRateKHR vkCmdSetFragmentShadingRateKHR;
extern PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR vkGetPhysicalDeviceFragmentShadingRatesKHR;
#endif /*  defined(VK_KHR_fragment_shading_rate)  */
#if defined(VK_KHR_get_display_properties2)
extern PFN_vkGetDisplayModeProperties2KHR vkGetDisplayModeProperties2KHR;
extern PFN_vkGetDisplayPlaneCapabilities2KHR vkGetDisplayPlaneCapabilities2KHR;
extern PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR vkGetPhysicalDeviceDisplayPlaneProperties2KHR;
extern PFN_vkGetPhysicalDeviceDisplayProperties2KHR vkGetPhysicalDeviceDisplayProperties2KHR;
#endif /*  defined(VK_KHR_get_display_properties2)  */
#if defined(VK_KHR_get_memory_requirements2)
extern PFN_vkGetBufferMemoryRequirements2KHR vkGetBufferMemoryRequirements2KHR;
extern PFN_vkGetImageMemoryRequirements2KHR vkGetImageMemoryRequirements2KHR;
extern PFN_vkGetImageSparseMemoryRequirements2KHR vkGetImageSparseMemoryRequirements2KHR;
#endif /*  defined(VK_KHR_get_memory_requirements2)  */
#if defined(VK_KHR_get_physical_device_properties2)
extern PFN_vkGetPhysicalDeviceFeatures2KHR vkGetPhysicalDeviceFeatures2KHR;
extern PFN_vkGetPhysicalDeviceFormatProperties2KHR vkGetPhysicalDeviceFormatProperties2KHR;
extern PFN_vkGetPhysicalDeviceImageFormatProperties2KHR vkGetPhysicalDeviceImageFormatProperties2KHR;
extern PFN_vkGetPhysicalDeviceMemoryProperties2KHR vkGetPhysicalDeviceMemoryProperties2KHR;
extern PFN_vkGetPhysicalDeviceProperties2KHR vkGetPhysicalDeviceProperties2KHR;
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR vkGetPhysicalDeviceQueueFamilyProperties2KHR;
extern PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
#endif /*  defined(VK_KHR_get_physical_device_properties2)  */
#if defined(VK_KHR_get_surface_capabilities2)
extern PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR;
extern PFN_vkGetPhysicalDeviceSurfaceFormats2KHR vkGetPhysicalDeviceSurfaceFormats2KHR;
#endif /*  defined(VK_KHR_get_surface_capabilities2)  */
#if defined(VK_KHR_line_rasterization)
extern PFN_vkCmdSetLineStippleKHR vkCmdSetLineStippleKHR;
#endif /*  defined(VK_KHR_line_rasterization)  */
#if defined(VK_KHR_maintenance1)
extern PFN_vkTrimCommandPoolKHR vkTrimCommandPoolKHR;
#endif /*  defined(VK_KHR_maintenance1)  */
#if defined(VK_KHR_maintenance3)
extern PFN_vkGetDescriptorSetLayoutSupportKHR vkGetDescriptorSetLayoutSupportKHR;
#endif /*  defined(VK_KHR_maintenance3)  */
#if defined(VK_KHR_maintenance4)
extern PFN_vkGetDeviceBufferMemoryRequirementsKHR vkGetDeviceBufferMemoryRequirementsKHR;
extern PFN_vkGetDeviceImageMemoryRequirementsKHR vkGetDeviceImageMemoryRequirementsKHR;
extern PFN_vkGetDeviceImageSparseMemoryRequirementsKHR vkGetDeviceImageSparseMemoryRequirementsKHR;
#endif /*  defined(VK_KHR_maintenance4)  */
#if defined(VK_KHR_maintenance5)
extern PFN_vkCmdBindIndexBuffer2KHR vkCmdBindIndexBuffer2KHR;
extern PFN_vkGetDeviceImageSubresourceLayoutKHR vkGetDeviceImageSubresourceLayoutKHR;
extern PFN_vkGetImageSubresourceLayout2KHR vkGetImageSubresourceLayout2KHR;
extern PFN_vkGetRenderingAreaGranularityKHR vkGetRenderingAreaGranularityKHR;
#endif /*  defined(VK_KHR_maintenance5)  */
#if defined(VK_KHR_maintenance6)
extern PFN_vkCmdBindDescriptorSets2KHR vkCmdBindDescriptorSets2KHR;
extern PFN_vkCmdPushConstants2KHR vkCmdPushConstants2KHR;
#endif /*  defined(VK_KHR_maintenance6)  */
#if defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)
extern PFN_vkCmdPushDescriptorSet2KHR vkCmdPushDescriptorSet2KHR;
extern PFN_vkCmdPushDescriptorSetWithTemplate2KHR vkCmdPushDescriptorSetWithTemplate2KHR;
#endif /*  defined(VK_KHR_maintenance6) && defined(VK_KHR_push_descriptor)  */
#if defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)
extern PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT vkCmdBindDescriptorBufferEmbeddedSamplers2EXT;
extern PFN_vkCmdSetDescriptorBufferOffsets2EXT vkCmdSetDescriptorBufferOffsets2EXT;
#endif /*  defined(VK_KHR_maintenance6) && defined(VK_EXT_descriptor_buffer)  */
#if defined(VK_KHR_map_memory2)
extern PFN_vkMapMemory2KHR vkMapMemory2KHR;
extern PFN_vkUnmapMemory2KHR vkUnmapMemory2KHR;
#endif /*  defined(VK_KHR_map_memory2)  */
#if defined(VK_KHR_performance_query)
extern PFN_vkAcquireProfilingLockKHR vkAcquireProfilingLockKHR;
extern PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
extern PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
extern PFN_vkReleaseProfilingLockKHR vkReleaseProfilingLockKHR;
#endif /*  defined(VK_KHR_performance_query)  */
#if defined(VK_KHR_pipeline_executable_properties)
extern PFN_vkGetPipelineExecutableInternalRepresentationsKHR vkGetPipelineExecutableInternalRepresentationsKHR;
extern PFN_vkGetPipelineExecutablePropertiesKHR vkGetPipelineExecutablePropertiesKHR;
extern PFN_vkGetPipelineExecutableStatisticsKHR vkGetPipelineExecutableStatisticsKHR;
#endif /*  defined(VK_KHR_pipeline_executable_properties)  */
#if defined(VK_KHR_present_wait)
extern PFN_vkWaitForPresentKHR vkWaitForPresentKHR;
#endif /*  defined(VK_KHR_present_wait)  */
#if defined(VK_KHR_push_descriptor)
extern PFN_vkCmdPushDescriptorSetKHR vkCmdPushDescriptorSetKHR;
#endif /*  defined(VK_KHR_push_descriptor)  */
#if defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)
extern PFN_vkCmdTraceRaysIndirect2KHR vkCmdTraceRaysIndirect2KHR;
#endif /*  defined(VK_KHR_ray_tracing_maintenance1) && defined(VK_KHR_ray_tracing_pipeline)  */
#if defined(VK_KHR_ray_tracing_pipeline)
extern PFN_vkCmdSetRayTracingPipelineStackSizeKHR vkCmdSetRayTracingPipelineStackSizeKHR;
extern PFN_vkCmdTraceRaysIndirectKHR vkCmdTraceRaysIndirectKHR;
extern PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;
extern PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;
extern PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR;
extern PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
extern PFN_vkGetRayTracingShaderGroupStackSizeKHR vkGetRayTracingShaderGroupStackSizeKHR;
#endif /*  defined(VK_KHR_ray_tracing_pipeline)  */
#if defined(VK_KHR_sampler_ycbcr_conversion)
extern PFN_vkCreateSamplerYcbcrConversionKHR vkCreateSamplerYcbcrConversionKHR;
extern PFN_vkDestroySamplerYcbcrConversionKHR vkDestroySamplerYcbcrConversionKHR;
#endif /*  defined(VK_KHR_sampler_ycbcr_conversion)  */
#if defined(VK_KHR_shared_presentable_image)
extern PFN_vkGetSwapchainStatusKHR vkGetSwapchainStatusKHR;
#endif /*  defined(VK_KHR_shared_presentable_image)  */
#if defined(VK_KHR_surface)
extern PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
extern PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
extern PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR;
extern PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR;
extern PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
#endif /*  defined(VK_KHR_surface)  */
#if defined(VK_KHR_swapchain)
extern PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR;
extern PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
extern PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR;
extern PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;
extern PFN_vkQueuePresentKHR vkQueuePresentKHR;
#endif /*  defined(VK_KHR_swapchain)  */
#if defined(VK_KHR_synchronization2)
extern PFN_vkCmdPipelineBarrier2KHR vkCmdPipelineBarrier2KHR;
extern PFN_vkCmdResetEvent2KHR vkCmdResetEvent2KHR;
extern PFN_vkCmdSetEvent2KHR vkCmdSetEvent2KHR;
extern PFN_vkCmdWaitEvents2KHR vkCmdWaitEvents2KHR;
extern PFN_vkCmdWriteTimestamp2KHR vkCmdWriteTimestamp2KHR;
extern PFN_vkQueueSubmit2KHR vkQueueSubmit2KHR;
#endif /*  defined(VK_KHR_synchronization2)  */
#if defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)
extern PFN_vkCmdWriteBufferMarker2AMD vkCmdWriteBufferMarker2AMD;
#endif /*  defined(VK_KHR_synchronization2) && defined(VK_AMD_buffer_marker)  */
#if defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)
extern PFN_vkGetQueueCheckpointData2NV vkGetQueueCheckpointData2NV;
#endif /*  defined(VK_KHR_synchronization2) && defined(VK_NV_device_diagnostic_checkpoints)  */
#if defined(VK_KHR_timeline_semaphore)
extern PFN_vkGetSemaphoreCounterValueKHR vkGetSemaphoreCounterValueKHR;
extern PFN_vkSignalSemaphoreKHR vkSignalSemaphoreKHR;
extern PFN_vkWaitSemaphoresKHR vkWaitSemaphoresKHR;
#endif /*  defined(VK_KHR_timeline_semaphore)  */
#if defined(VK_KHR_video_decode_queue)
extern PFN_vkCmdDecodeVideoKHR vkCmdDecodeVideoKHR;
#endif /*  defined(VK_KHR_video_decode_queue)  */
#if defined(VK_KHR_video_encode_queue)
extern PFN_vkCmdEncodeVideoKHR vkCmdEncodeVideoKHR;
extern PFN_vkGetEncodedVideoSessionParametersKHR vkGetEncodedVideoSessionParametersKHR;
extern PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR;
#endif /*  defined(VK_KHR_video_encode_queue)  */
#if defined(VK_KHR_video_queue)
extern PFN_vkBindVideoSessionMemoryKHR vkBindVideoSessionMemoryKHR;
extern PFN_vkCmdBeginVideoCodingKHR vkCmdBeginVideoCodingKHR;
extern PFN_vkCmdControlVideoCodingKHR vkCmdControlVideoCodingKHR;
extern PFN_vkCmdEndVideoCodingKHR vkCmdEndVideoCodingKHR;
extern PFN_vkCreateVideoSessionKHR vkCreateVideoSessionKHR;
extern PFN_vkCreateVideoSessionParametersKHR vkCreateVideoSessionParametersKHR;
extern PFN_vkDestroyVideoSessionKHR vkDestroyVideoSessionKHR;
extern PFN_vkDestroyVideoSessionParametersKHR vkDestroyVideoSessionParametersKHR;
extern PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR vkGetPhysicalDeviceVideoCapabilitiesKHR;
extern PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR vkGetPhysicalDeviceVideoFormatPropertiesKHR;
extern PFN_vkGetVideoSessionMemoryRequirementsKHR vkGetVideoSessionMemoryRequirementsKHR;
extern PFN_vkUpdateVideoSessionParametersKHR vkUpdateVideoSessionParametersKHR;
#endif /*  defined(VK_KHR_video_queue)  */
#if defined(VK_KHR_wayland_surface)
extern PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;
extern PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif /*  defined(VK_KHR_wayland_surface)  */
#if defined(VK_KHR_win32_surface)
extern PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
extern PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR;
#endif /*  defined(VK_KHR_win32_surface)  */
#if defined(VK_KHR_xcb_surface)
extern PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR;
extern PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif /*  defined(VK_KHR_xcb_surface)  */
#if defined(VK_KHR_xlib_surface)
extern PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;
extern PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif /*  defined(VK_KHR_xlib_surface)  */
#if defined(VK_MVK_ios_surface)
extern PFN_vkCreateIOSSurfaceMVK vkCreateIOSSurfaceMVK;
#endif /*  defined(VK_MVK_ios_surface)  */
#if defined(VK_MVK_macos_surface)
extern PFN_vkCreateMacOSSurfaceMVK vkCreateMacOSSurfaceMVK;
#endif /*  defined(VK_MVK_macos_surface)  */
#if defined(VK_NN_vi_surface)
extern PFN_vkCreateViSurfaceNN vkCreateViSurfaceNN;
#endif /*  defined(VK_NN_vi_surface)  */
#if defined(VK_NVX_binary_import)
extern PFN_vkCmdCuLaunchKernelNVX vkCmdCuLaunchKernelNVX;
extern PFN_vkCreateCuFunctionNVX vkCreateCuFunctionNVX;
extern PFN_vkCreateCuModuleNVX vkCreateCuModuleNVX;
extern PFN_vkDestroyCuFunctionNVX vkDestroyCuFunctionNVX;
extern PFN_vkDestroyCuModuleNVX vkDestroyCuModuleNVX;
#endif /*  defined(VK_NVX_binary_import)  */
#if defined(VK_NVX_image_view_handle)
extern PFN_vkGetImageViewAddressNVX vkGetImageViewAddressNVX;
extern PFN_vkGetImageViewHandleNVX vkGetImageViewHandleNVX;
#endif /*  defined(VK_NVX_image_view_handle)  */
#if defined(VK_NV_acquire_winrt_display)
extern PFN_vkAcquireWinrtDisplayNV vkAcquireWinrtDisplayNV;
extern PFN_vkGetWinrtDisplayNV vkGetWinrtDisplayNV;
#endif /*  defined(VK_NV_acquire_winrt_display)  */
#if defined(VK_NV_clip_space_w_scaling)
extern PFN_vkCmdSetViewportWScalingNV vkCmdSetViewportWScalingNV;
#endif /*  defined(VK_NV_clip_space_w_scaling)  */
#if defined(VK_NV_cooperative_matrix)
extern PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV vkGetPhysicalDeviceCooperativeMatrixPropertiesNV;
#endif /*  defined(VK_NV_cooperative_matrix)  */
#if defined(VK_NV_copy_memory_indirect)
extern PFN_vkCmdCopyMemoryIndirectNV vkCmdCopyMemoryIndirectNV;
extern PFN_vkCmdCopyMemoryToImageIndirectNV vkCmdCopyMemoryToImageIndirectNV;
#endif /*  defined(VK_NV_copy_memory_indirect)  */
#if defined(VK_NV_coverage_reduction_mode)
extern PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV;
#endif /*  defined(VK_NV_coverage_reduction_mode)  */
#if defined(VK_NV_cuda_kernel_launch)
extern PFN_vkCmdCudaLaunchKernelNV vkCmdCudaLaunchKernelNV;
extern PFN_vkCreateCudaFunctionNV vkCreateCudaFunctionNV;
extern PFN_vkCreateCudaModuleNV vkCreateCudaModuleNV;
extern PFN_vkDestroyCudaFunctionNV vkDestroyCudaFunctionNV;
extern PFN_vkDestroyCudaModuleNV vkDestroyCudaModuleNV;
extern PFN_vkGetCudaModuleCacheNV vkGetCudaModuleCacheNV;
#endif /*  defined(VK_NV_cuda_kernel_launch)  */
#if defined(VK_NV_device_diagnostic_checkpoints)
extern PFN_vkCmdSetCheckpointNV vkCmdSetCheckpointNV;
extern PFN_vkGetQueueCheckpointDataNV vkGetQueueCheckpointDataNV;
#endif /*  defined(VK_NV_device_diagnostic_checkpoints)  */
#if defined(VK_NV_device_generated_commands)
extern PFN_vkCmdBindPipelineShaderGroupNV vkCmdBindPipelineShaderGroupNV;
extern PFN_vkCmdExecuteGeneratedCommandsNV vkCmdExecuteGeneratedCommandsNV;
extern PFN_vkCmdPreprocessGeneratedCommandsNV vkCmdPreprocessGeneratedCommandsNV;
extern PFN_vkCreateIndirectCommandsLayoutNV vkCreateIndirectCommandsLayoutNV;
extern PFN_vkDestroyIndirectCommandsLayoutNV vkDestroyIndirectCommandsLayoutNV;
extern PFN_vkGetGeneratedCommandsMemoryRequirementsNV vkGetGeneratedCommandsMemoryRequirementsNV;
#endif /*  defined(VK_NV_device_generated_commands)  */
#if defined(VK_NV_device_generated_commands_compute)
extern PFN_vkCmdUpdatePipelineIndirectBufferNV vkCmdUpdatePipelineIndirectBufferNV;
extern PFN_vkGetPipelineIndirectDeviceAddressNV vkGetPipelineIndirectDeviceAddressNV;
extern PFN_vkGetPipelineIndirectMemoryRequirementsNV vkGetPipelineIndirectMemoryRequirementsNV;
#endif /*  defined(VK_NV_device_generated_commands_compute)  */
#if defined(VK_NV_external_memory_capabilities)
extern PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV vkGetPhysicalDeviceExternalImageFormatPropertiesNV;
#endif /*  defined(VK_NV_external_memory_capabilities)  */
#if defined(VK_NV_external_memory_rdma)
extern PFN_vkGetMemoryRemoteAddressNV vkGetMemoryRemoteAddressNV;
#endif /*  defined(VK_NV_external_memory_rdma)  */
#if defined(VK_NV_external_memory_win32)
extern PFN_vkGetMemoryWin32HandleNV vkGetMemoryWin32HandleNV;
#endif /*  defined(VK_NV_external_memory_win32)  */
#if defined(VK_NV_fragment_shading_rate_enums)
extern PFN_vkCmdSetFragmentShadingRateEnumNV vkCmdSetFragmentShadingRateEnumNV;
#endif /*  defined(VK_NV_fragment_shading_rate_enums)  */
#if defined(VK_NV_low_latency2)
extern PFN_vkGetLatencyTimingsNV vkGetLatencyTimingsNV;
extern PFN_vkLatencySleepNV vkLatencySleepNV;
extern PFN_vkQueueNotifyOutOfBandNV vkQueueNotifyOutOfBandNV;
extern PFN_vkSetLatencyMarkerNV vkSetLatencyMarkerNV;
extern PFN_vkSetLatencySleepModeNV vkSetLatencySleepModeNV;
#endif /*  defined(VK_NV_low_latency2)  */
#if defined(VK_NV_memory_decompression)
extern PFN_vkCmdDecompressMemoryIndirectCountNV vkCmdDecompressMemoryIndirectCountNV;
extern PFN_vkCmdDecompressMemoryNV vkCmdDecompressMemoryNV;
#endif /*  defined(VK_NV_memory_decompression)  */
#if defined(VK_NV_mesh_shader)
extern PFN_vkCmdDrawMeshTasksIndirectCountNV vkCmdDrawMeshTasksIndirectCountNV;
extern PFN_vkCmdDrawMeshTasksIndirectNV vkCmdDrawMeshTasksIndirectNV;
extern PFN_vkCmdDrawMeshTasksNV vkCmdDrawMeshTasksNV;
#endif /*  defined(VK_NV_mesh_shader)  */
#if defined(VK_NV_optical_flow)
extern PFN_vkBindOpticalFlowSessionImageNV vkBindOpticalFlowSessionImageNV;
extern PFN_vkCmdOpticalFlowExecuteNV vkCmdOpticalFlowExecuteNV;
extern PFN_vkCreateOpticalFlowSessionNV vkCreateOpticalFlowSessionNV;
extern PFN_vkDestroyOpticalFlowSessionNV vkDestroyOpticalFlowSessionNV;
extern PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV vkGetPhysicalDeviceOpticalFlowImageFormatsNV;
#endif /*  defined(VK_NV_optical_flow)  */
#if defined(VK_NV_ray_tracing)
extern PFN_vkBindAccelerationStructureMemoryNV vkBindAccelerationStructureMemoryNV;
extern PFN_vkCmdBuildAccelerationStructureNV vkCmdBuildAccelerationStructureNV;
extern PFN_vkCmdCopyAccelerationStructureNV vkCmdCopyAccelerationStructureNV;
extern PFN_vkCmdTraceRaysNV vkCmdTraceRaysNV;
extern PFN_vkCmdWriteAccelerationStructuresPropertiesNV vkCmdWriteAccelerationStructuresPropertiesNV;
extern PFN_vkCompileDeferredNV vkCompileDeferredNV;
extern PFN_vkCreateAccelerationStructureNV vkCreateAccelerationStructureNV;
extern PFN_vkCreateRayTracingPipelinesNV vkCreateRayTracingPipelinesNV;
extern PFN_vkDestroyAccelerationStructureNV vkDestroyAccelerationStructureNV;
extern PFN_vkGetAccelerationStructureHandleNV vkGetAccelerationStructureHandleNV;
extern PFN_vkGetAccelerationStructureMemoryRequirementsNV vkGetAccelerationStructureMemoryRequirementsNV;
extern PFN_vkGetRayTracingShaderGroupHandlesNV vkGetRayTracingShaderGroupHandlesNV;
#endif /*  defined(VK_NV_ray_tracing)  */
#if defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2
extern PFN_vkCmdSetExclusiveScissorEnableNV vkCmdSetExclusiveScissorEnableNV;
#endif /*  defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2  */
#if defined(VK_NV_scissor_exclusive)
extern PFN_vkCmdSetExclusiveScissorNV vkCmdSetExclusiveScissorNV;
#endif /*  defined(VK_NV_scissor_exclusive)  */
#if defined(VK_NV_shading_rate_image)
extern PFN_vkCmdBindShadingRateImageNV vkCmdBindShadingRateImageNV;
extern PFN_vkCmdSetCoarseSampleOrderNV vkCmdSetCoarseSampleOrderNV;
extern PFN_vkCmdSetViewportShadingRatePaletteNV vkCmdSetViewportShadingRatePaletteNV;
#endif /*  defined(VK_NV_shading_rate_image)  */
#if defined(VK_QCOM_tile_properties)
extern PFN_vkGetDynamicRenderingTilePropertiesQCOM vkGetDynamicRenderingTilePropertiesQCOM;
extern PFN_vkGetFramebufferTilePropertiesQCOM vkGetFramebufferTilePropertiesQCOM;
#endif /*  defined(VK_QCOM_tile_properties)  */
#if defined(VK_QNX_external_memory_screen_buffer)
extern PFN_vkGetScreenBufferPropertiesQNX vkGetScreenBufferPropertiesQNX;
#endif /*  defined(VK_QNX_external_memory_screen_buffer)  */
#if defined(VK_QNX_screen_surface)
extern PFN_vkCreateScreenSurfaceQNX vkCreateScreenSurfaceQNX;
extern PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX vkGetPhysicalDeviceScreenPresentationSupportQNX;
#endif /*  defined(VK_QNX_screen_surface)  */
#if defined(VK_VALVE_descriptor_set_host_mapping)
extern PFN_vkGetDescriptorSetHostMappingVALVE vkGetDescriptorSetHostMappingVALVE;
extern PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE vkGetDescriptorSetLayoutHostMappingInfoVALVE;
#endif /*  defined(VK_VALVE_descriptor_set_host_mapping)  */
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
extern PFN_vkCmdBindVertexBuffers2EXT vkCmdBindVertexBuffers2EXT;
extern PFN_vkCmdSetCullModeEXT vkCmdSetCullModeEXT;
extern PFN_vkCmdSetDepthBoundsTestEnableEXT vkCmdSetDepthBoundsTestEnableEXT;
extern PFN_vkCmdSetDepthCompareOpEXT vkCmdSetDepthCompareOpEXT;
extern PFN_vkCmdSetDepthTestEnableEXT vkCmdSetDepthTestEnableEXT;
extern PFN_vkCmdSetDepthWriteEnableEXT vkCmdSetDepthWriteEnableEXT;
extern PFN_vkCmdSetFrontFaceEXT vkCmdSetFrontFaceEXT;
extern PFN_vkCmdSetPrimitiveTopologyEXT vkCmdSetPrimitiveTopologyEXT;
extern PFN_vkCmdSetScissorWithCountEXT vkCmdSetScissorWithCountEXT;
extern PFN_vkCmdSetStencilOpEXT vkCmdSetStencilOpEXT;
extern PFN_vkCmdSetStencilTestEnableEXT vkCmdSetStencilTestEnableEXT;
extern PFN_vkCmdSetViewportWithCountEXT vkCmdSetViewportWithCountEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
extern PFN_vkCmdSetDepthBiasEnableEXT vkCmdSetDepthBiasEnableEXT;
extern PFN_vkCmdSetLogicOpEXT vkCmdSetLogicOpEXT;
extern PFN_vkCmdSetPatchControlPointsEXT vkCmdSetPatchControlPointsEXT;
extern PFN_vkCmdSetPrimitiveRestartEnableEXT vkCmdSetPrimitiveRestartEnableEXT;
extern PFN_vkCmdSetRasterizerDiscardEnableEXT vkCmdSetRasterizerDiscardEnableEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
extern PFN_vkCmdSetAlphaToCoverageEnableEXT vkCmdSetAlphaToCoverageEnableEXT;
extern PFN_vkCmdSetAlphaToOneEnableEXT vkCmdSetAlphaToOneEnableEXT;
extern PFN_vkCmdSetColorBlendEnableEXT vkCmdSetColorBlendEnableEXT;
extern PFN_vkCmdSetColorBlendEquationEXT vkCmdSetColorBlendEquationEXT;
extern PFN_vkCmdSetColorWriteMaskEXT vkCmdSetColorWriteMaskEXT;
extern PFN_vkCmdSetDepthClampEnableEXT vkCmdSetDepthClampEnableEXT;
extern PFN_vkCmdSetLogicOpEnableEXT vkCmdSetLogicOpEnableEXT;
extern PFN_vkCmdSetPolygonModeEXT vkCmdSetPolygonModeEXT;
extern PFN_vkCmdSetRasterizationSamplesEXT vkCmdSetRasterizationSamplesEXT;
extern PFN_vkCmdSetSampleMaskEXT vkCmdSetSampleMaskEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1))) || (defined(VK_EXT_shader_object))
extern PFN_vkCmdSetTessellationDomainOriginEXT vkCmdSetTessellationDomainOriginEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && (defined(VK_KHR_maintenance2) || defined(VK_VERSION_1_1))) || (defined(VK_EXT_shader_object))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))
extern PFN_vkCmdSetRasterizationStreamEXT vkCmdSetRasterizationStreamEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_transform_feedback)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_transform_feedback))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))
extern PFN_vkCmdSetConservativeRasterizationModeEXT vkCmdSetConservativeRasterizationModeEXT;
extern PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT vkCmdSetExtraPrimitiveOverestimationSizeEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_conservative_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_conservative_rasterization))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))
extern PFN_vkCmdSetDepthClipEnableEXT vkCmdSetDepthClipEnableEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_enable)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_enable))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))
extern PFN_vkCmdSetSampleLocationsEnableEXT vkCmdSetSampleLocationsEnableEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_sample_locations)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_sample_locations))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))
extern PFN_vkCmdSetColorBlendAdvancedEXT vkCmdSetColorBlendAdvancedEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_blend_operation_advanced)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_blend_operation_advanced))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))
extern PFN_vkCmdSetProvokingVertexModeEXT vkCmdSetProvokingVertexModeEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_provoking_vertex)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_provoking_vertex))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))
extern PFN_vkCmdSetLineRasterizationModeEXT vkCmdSetLineRasterizationModeEXT;
extern PFN_vkCmdSetLineStippleEnableEXT vkCmdSetLineStippleEnableEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_line_rasterization)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_line_rasterization))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))
extern PFN_vkCmdSetDepthClipNegativeOneToOneEXT vkCmdSetDepthClipNegativeOneToOneEXT;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_EXT_depth_clip_control)) || (defined(VK_EXT_shader_object) && defined(VK_EXT_depth_clip_control))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling)) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))
extern PFN_vkCmdSetViewportWScalingEnableNV vkCmdSetViewportWScalingEnableNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_clip_space_w_scaling)) || (defined(VK_EXT_shader_object) && defined(VK_NV_clip_space_w_scaling))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle)) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))
extern PFN_vkCmdSetViewportSwizzleNV vkCmdSetViewportSwizzleNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_viewport_swizzle)) || (defined(VK_EXT_shader_object) && defined(VK_NV_viewport_swizzle))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color)) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))
extern PFN_vkCmdSetCoverageToColorEnableNV vkCmdSetCoverageToColorEnableNV;
extern PFN_vkCmdSetCoverageToColorLocationNV vkCmdSetCoverageToColorLocationNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_fragment_coverage_to_color)) || (defined(VK_EXT_shader_object) && defined(VK_NV_fragment_coverage_to_color))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples)) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))
extern PFN_vkCmdSetCoverageModulationModeNV vkCmdSetCoverageModulationModeNV;
extern PFN_vkCmdSetCoverageModulationTableEnableNV vkCmdSetCoverageModulationTableEnableNV;
extern PFN_vkCmdSetCoverageModulationTableNV vkCmdSetCoverageModulationTableNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_framebuffer_mixed_samples)) || (defined(VK_EXT_shader_object) && defined(VK_NV_framebuffer_mixed_samples))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image)) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))
extern PFN_vkCmdSetShadingRateImageEnableNV vkCmdSetShadingRateImageEnableNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_shading_rate_image)) || (defined(VK_EXT_shader_object) && defined(VK_NV_shading_rate_image))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test)) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))
extern PFN_vkCmdSetRepresentativeFragmentTestEnableNV vkCmdSetRepresentativeFragmentTestEnableNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_representative_fragment_test)) || (defined(VK_EXT_shader_object) && defined(VK_NV_representative_fragment_test))  */
#if (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode)) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))
extern PFN_vkCmdSetCoverageReductionModeNV vkCmdSetCoverageReductionModeNV;
#endif /*  (defined(VK_EXT_extended_dynamic_state3) && defined(VK_NV_coverage_reduction_mode)) || (defined(VK_EXT_shader_object) && defined(VK_NV_coverage_reduction_mode))  */
#if (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))
extern PFN_vkGetDeviceGroupSurfacePresentModes2EXT vkGetDeviceGroupSurfacePresentModes2EXT;
#endif /*  (defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1))  */
#if (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))
extern PFN_vkGetImageSubresourceLayout2EXT vkGetImageSubresourceLayout2EXT;
#endif /*  (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))  */
#if (defined(VK_EXT_shader_object)) || (defined(VK_EXT_vertex_input_dynamic_state))
extern PFN_vkCmdSetVertexInputEXT vkCmdSetVertexInputEXT;
#endif /*  (defined(VK_EXT_shader_object)) || (defined(VK_EXT_vertex_input_dynamic_state))  */
#if (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
extern PFN_vkCmdPushDescriptorSetWithTemplateKHR vkCmdPushDescriptorSetWithTemplateKHR;
#endif /*  (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))  */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
extern PFN_vkGetDeviceGroupPresentCapabilitiesKHR vkGetDeviceGroupPresentCapabilitiesKHR;
extern PFN_vkGetDeviceGroupSurfacePresentModesKHR vkGetDeviceGroupSurfacePresentModesKHR;
extern PFN_vkGetPhysicalDevicePresentRectanglesKHR vkGetPhysicalDevicePresentRectanglesKHR;
#endif /*  (defined(VK_KHR_device_group) && defined(VK_KHR_surface)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))  */
#if (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
extern PFN_vkAcquireNextImage2KHR vkAcquireNextImage2KHR;
#endif /*  (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain)) || (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))  */

#ifdef __cplusplus
}
#endif
