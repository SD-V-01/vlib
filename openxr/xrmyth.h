////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   xrmyth.h
//  Version:     v1.00
//  Created:     31/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#ifndef MTYH_XR_LOADER_H
#define MTYH_XR_LOADER_H

#include "base_types.h"

#if defined(OPENXR_H_) && !defined(XR_NO_PROTOTYPES)
#error Please define XR_NO_PROTOTYPES before including any openxr headers !!

#endif

#if !defined(OPENXR_H_) && defined(MYTH_XR_LOAD_OPENXR_H_CUSTOM_PATH)
#include MYTH_XR_LOAD_OPENXR_H_CUSTOM_PATH


#elif !defined(OPENXR_H_) && !defined(MYTH_XR_LOAD_OPENXR_H_CUSTOM_PATH)

#ifndef XR_NO_PROTOTYPES
#define XR_NO_PROTOTYPES
#endif

#if defined(VLIB_PLATFORM_NT)

#ifndef MYTH_XR_NO_PLATFORM_DEFINES

#elif defined(VLIB_PLATFORM_LINUX)
#define XR_USE_PLATFORM_WIN32

#endif

#define XR_USE_GRAPHICS_API_VULKAN

#ifdef VLIB_ANDROID
#define XR_USE_PLATFORM_ANDROID

#endif

#endif

#include "openxr/openxr.h"
#include "openxr/openxr_platform.h"

#endif

#ifdef VLIB_PLATFORM_NT
#define MYTH_XR_LOAD_DLL "openxr_loader.dll"
#define MYTH_XR_LOAD_DLL_BACKUP "openxr_loader.dll"

#elif defined(VLIB_PLATFORM_LINUX) || defined(__unix__)
#define MYTH_XR_LOAD_DLL "libopenxr_loader.so.1"
#define MYTH_XR_LOAD_DLL_BACKUP "libopenxr_loader.so"

#elif defined(__APPLE__)
#error Why are you even trying this

#else
#error Impleemnt platform

#endif

#define MYTH_XR_LOAD_API

#ifdef __cplusplus
extern "C"{
#endif

MYTH_XR_LOAD_API bool mythXrLoad();
MYTH_XR_LOAD_API void mythXrExit();
MYTH_XR_LOAD_API void mythXrLoadInstance(XrInstance Instance);

typedef PFN_xrVoidFunction (*loadFuncPtr)(XrInstance Instance, const char* Name);

MYTH_XR_LOAD_API void _mythXrLoadBasic(XrInstance Instance, loadFuncPtr LoadFunc);
MYTH_XR_LOAD_API void _mythXrLoadInstance(XrInstance Instance, loadFuncPtr LoadFunc);

//SECTION(V): XRMYTH_TOSTR8_PROTO

//SECTION(V): XRMYTH_TOSTR32_PROTO

#if defined(TEX_PARSER) || defined(IDE_PARSER)

//SECTION(V): TEX_PARSER_XR_PROTOTYPES
#if defined(XR_VERSION_1_0)
extern PFN_xrAcquireSwapchainImage xrAcquireSwapchainImage;
extern PFN_xrApplyHapticFeedback xrApplyHapticFeedback;
extern PFN_xrAttachSessionActionSets xrAttachSessionActionSets;
extern PFN_xrBeginFrame xrBeginFrame;
extern PFN_xrBeginSession xrBeginSession;
extern PFN_xrCreateAction xrCreateAction;
extern PFN_xrCreateActionSet xrCreateActionSet;
extern PFN_xrCreateActionSpace xrCreateActionSpace;
extern PFN_xrCreateInstance xrCreateInstance;
extern PFN_xrCreateReferenceSpace xrCreateReferenceSpace;
extern PFN_xrCreateSession xrCreateSession;
extern PFN_xrCreateSwapchain xrCreateSwapchain;
extern PFN_xrDestroyAction xrDestroyAction;
extern PFN_xrDestroyActionSet xrDestroyActionSet;
extern PFN_xrDestroyInstance xrDestroyInstance;
extern PFN_xrDestroySession xrDestroySession;
extern PFN_xrDestroySpace xrDestroySpace;
extern PFN_xrDestroySwapchain xrDestroySwapchain;
extern PFN_xrEndFrame xrEndFrame;
extern PFN_xrEndSession xrEndSession;
extern PFN_xrEnumerateApiLayerProperties xrEnumerateApiLayerProperties;
extern PFN_xrEnumerateBoundSourcesForAction xrEnumerateBoundSourcesForAction;
extern PFN_xrEnumerateEnvironmentBlendModes xrEnumerateEnvironmentBlendModes;
extern PFN_xrEnumerateInstanceExtensionProperties xrEnumerateInstanceExtensionProperties;
extern PFN_xrEnumerateReferenceSpaces xrEnumerateReferenceSpaces;
extern PFN_xrEnumerateSwapchainFormats xrEnumerateSwapchainFormats;
extern PFN_xrEnumerateSwapchainImages xrEnumerateSwapchainImages;
extern PFN_xrEnumerateViewConfigurationViews xrEnumerateViewConfigurationViews;
extern PFN_xrEnumerateViewConfigurations xrEnumerateViewConfigurations;
extern PFN_xrGetActionStateBoolean xrGetActionStateBoolean;
extern PFN_xrGetActionStateFloat xrGetActionStateFloat;
extern PFN_xrGetActionStatePose xrGetActionStatePose;
extern PFN_xrGetActionStateVector2f xrGetActionStateVector2f;
extern PFN_xrGetCurrentInteractionProfile xrGetCurrentInteractionProfile;
extern PFN_xrGetInputSourceLocalizedName xrGetInputSourceLocalizedName;
extern PFN_xrGetInstanceProcAddr xrGetInstanceProcAddr;
extern PFN_xrGetInstanceProperties xrGetInstanceProperties;
extern PFN_xrGetReferenceSpaceBoundsRect xrGetReferenceSpaceBoundsRect;
extern PFN_xrGetSystem xrGetSystem;
extern PFN_xrGetSystemProperties xrGetSystemProperties;
extern PFN_xrGetViewConfigurationProperties xrGetViewConfigurationProperties;
extern PFN_xrLocateSpace xrLocateSpace;
extern PFN_xrLocateViews xrLocateViews;
extern PFN_xrPathToString xrPathToString;
extern PFN_xrPollEvent xrPollEvent;
extern PFN_xrReleaseSwapchainImage xrReleaseSwapchainImage;
extern PFN_xrRequestExitSession xrRequestExitSession;
extern PFN_xrResultToString xrResultToString;
extern PFN_xrStopHapticFeedback xrStopHapticFeedback;
extern PFN_xrStringToPath xrStringToPath;
extern PFN_xrStructureTypeToString xrStructureTypeToString;
extern PFN_xrSuggestInteractionProfileBindings xrSuggestInteractionProfileBindings;
extern PFN_xrSyncActions xrSyncActions;
extern PFN_xrWaitFrame xrWaitFrame;
extern PFN_xrWaitSwapchainImage xrWaitSwapchainImage;
#endif /*  defined(XR_VERSION_1_0)   */
#if defined(XR_LOADER_VERSION_1_0)
extern PFN_xrCreateApiLayerInstance xrCreateApiLayerInstance;
extern PFN_xrNegotiateLoaderApiLayerInterface xrNegotiateLoaderApiLayerInterface;
extern PFN_xrNegotiateLoaderRuntimeInterface xrNegotiateLoaderRuntimeInterface;
#endif /*  defined(XR_LOADER_VERSION_1_0)   */
#if defined(XR_VERSION_1_1)
extern PFN_xrLocateSpaces xrLocateSpaces;
#endif /*  defined(XR_VERSION_1_1)   */
#if defined(XR_ALMALENCE_digital_lens_control)
extern PFN_xrSetDigitalLensControlALMALENCE xrSetDigitalLensControlALMALENCE;
#endif /*  defined(XR_ALMALENCE_digital_lens_control)   */
#if defined(XR_EXT_conformance_automation)
extern PFN_xrSetInputDeviceActiveEXT xrSetInputDeviceActiveEXT;
extern PFN_xrSetInputDeviceLocationEXT xrSetInputDeviceLocationEXT;
extern PFN_xrSetInputDeviceStateBoolEXT xrSetInputDeviceStateBoolEXT;
extern PFN_xrSetInputDeviceStateFloatEXT xrSetInputDeviceStateFloatEXT;
extern PFN_xrSetInputDeviceStateVector2fEXT xrSetInputDeviceStateVector2fEXT;
#endif /*  defined(XR_EXT_conformance_automation)   */
#if defined(XR_EXT_debug_utils)
extern PFN_xrCreateDebugUtilsMessengerEXT xrCreateDebugUtilsMessengerEXT;
extern PFN_xrDestroyDebugUtilsMessengerEXT xrDestroyDebugUtilsMessengerEXT;
extern PFN_xrSessionBeginDebugUtilsLabelRegionEXT xrSessionBeginDebugUtilsLabelRegionEXT;
extern PFN_xrSessionEndDebugUtilsLabelRegionEXT xrSessionEndDebugUtilsLabelRegionEXT;
extern PFN_xrSessionInsertDebugUtilsLabelEXT xrSessionInsertDebugUtilsLabelEXT;
extern PFN_xrSetDebugUtilsObjectNameEXT xrSetDebugUtilsObjectNameEXT;
extern PFN_xrSubmitDebugUtilsMessageEXT xrSubmitDebugUtilsMessageEXT;
#endif /*  defined(XR_EXT_debug_utils)   */
#if defined(XR_EXT_future)
extern PFN_xrCancelFutureEXT xrCancelFutureEXT;
extern PFN_xrPollFutureEXT xrPollFutureEXT;
#endif /*  defined(XR_EXT_future)   */
#if defined(XR_EXT_hand_tracking)
extern PFN_xrCreateHandTrackerEXT xrCreateHandTrackerEXT;
extern PFN_xrDestroyHandTrackerEXT xrDestroyHandTrackerEXT;
extern PFN_xrLocateHandJointsEXT xrLocateHandJointsEXT;
#endif /*  defined(XR_EXT_hand_tracking)   */
#if defined(XR_EXT_performance_settings)
extern PFN_xrPerfSettingsSetPerformanceLevelEXT xrPerfSettingsSetPerformanceLevelEXT;
#endif /*  defined(XR_EXT_performance_settings)   */
#if defined(XR_EXT_plane_detection)
extern PFN_xrBeginPlaneDetectionEXT xrBeginPlaneDetectionEXT;
extern PFN_xrCreatePlaneDetectorEXT xrCreatePlaneDetectorEXT;
extern PFN_xrDestroyPlaneDetectorEXT xrDestroyPlaneDetectorEXT;
extern PFN_xrGetPlaneDetectionStateEXT xrGetPlaneDetectionStateEXT;
extern PFN_xrGetPlaneDetectionsEXT xrGetPlaneDetectionsEXT;
extern PFN_xrGetPlanePolygonBufferEXT xrGetPlanePolygonBufferEXT;
#endif /*  defined(XR_EXT_plane_detection)   */
#if defined(XR_EXT_thermal_query)
extern PFN_xrThermalGetTemperatureTrendEXT xrThermalGetTemperatureTrendEXT;
#endif /*  defined(XR_EXT_thermal_query)   */
#if defined(XR_FB_body_tracking)
extern PFN_xrCreateBodyTrackerFB xrCreateBodyTrackerFB;
extern PFN_xrDestroyBodyTrackerFB xrDestroyBodyTrackerFB;
extern PFN_xrGetBodySkeletonFB xrGetBodySkeletonFB;
extern PFN_xrLocateBodyJointsFB xrLocateBodyJointsFB;
#endif /*  defined(XR_FB_body_tracking)   */
#if defined(XR_FB_color_space)
extern PFN_xrEnumerateColorSpacesFB xrEnumerateColorSpacesFB;
extern PFN_xrSetColorSpaceFB xrSetColorSpaceFB;
#endif /*  defined(XR_FB_color_space)   */
#if defined(XR_FB_display_refresh_rate)
extern PFN_xrEnumerateDisplayRefreshRatesFB xrEnumerateDisplayRefreshRatesFB;
extern PFN_xrGetDisplayRefreshRateFB xrGetDisplayRefreshRateFB;
extern PFN_xrRequestDisplayRefreshRateFB xrRequestDisplayRefreshRateFB;
#endif /*  defined(XR_FB_display_refresh_rate)   */
#if defined(XR_FB_eye_tracking_social)
extern PFN_xrCreateEyeTrackerFB xrCreateEyeTrackerFB;
extern PFN_xrDestroyEyeTrackerFB xrDestroyEyeTrackerFB;
extern PFN_xrGetEyeGazesFB xrGetEyeGazesFB;
#endif /*  defined(XR_FB_eye_tracking_social)   */
#if defined(XR_FB_face_tracking)
extern PFN_xrCreateFaceTrackerFB xrCreateFaceTrackerFB;
extern PFN_xrDestroyFaceTrackerFB xrDestroyFaceTrackerFB;
extern PFN_xrGetFaceExpressionWeightsFB xrGetFaceExpressionWeightsFB;
#endif /*  defined(XR_FB_face_tracking)   */
#if defined(XR_FB_face_tracking2)
extern PFN_xrCreateFaceTracker2FB xrCreateFaceTracker2FB;
extern PFN_xrDestroyFaceTracker2FB xrDestroyFaceTracker2FB;
extern PFN_xrGetFaceExpressionWeights2FB xrGetFaceExpressionWeights2FB;
#endif /*  defined(XR_FB_face_tracking2)   */
#if defined(XR_FB_foveation)
extern PFN_xrCreateFoveationProfileFB xrCreateFoveationProfileFB;
extern PFN_xrDestroyFoveationProfileFB xrDestroyFoveationProfileFB;
#endif /*  defined(XR_FB_foveation)   */
#if defined(XR_FB_hand_tracking_mesh)
extern PFN_xrGetHandMeshFB xrGetHandMeshFB;
#endif /*  defined(XR_FB_hand_tracking_mesh)   */
#if defined(XR_FB_haptic_pcm)
extern PFN_xrGetDeviceSampleRateFB xrGetDeviceSampleRateFB;
#endif /*  defined(XR_FB_haptic_pcm)   */
#if defined(XR_FB_keyboard_tracking)
extern PFN_xrCreateKeyboardSpaceFB xrCreateKeyboardSpaceFB;
extern PFN_xrQuerySystemTrackedKeyboardFB xrQuerySystemTrackedKeyboardFB;
#endif /*  defined(XR_FB_keyboard_tracking)   */
#if defined(XR_FB_passthrough)
extern PFN_xrCreateGeometryInstanceFB xrCreateGeometryInstanceFB;
extern PFN_xrCreatePassthroughFB xrCreatePassthroughFB;
extern PFN_xrCreatePassthroughLayerFB xrCreatePassthroughLayerFB;
extern PFN_xrDestroyGeometryInstanceFB xrDestroyGeometryInstanceFB;
extern PFN_xrDestroyPassthroughFB xrDestroyPassthroughFB;
extern PFN_xrDestroyPassthroughLayerFB xrDestroyPassthroughLayerFB;
extern PFN_xrGeometryInstanceSetTransformFB xrGeometryInstanceSetTransformFB;
extern PFN_xrPassthroughLayerPauseFB xrPassthroughLayerPauseFB;
extern PFN_xrPassthroughLayerResumeFB xrPassthroughLayerResumeFB;
extern PFN_xrPassthroughLayerSetStyleFB xrPassthroughLayerSetStyleFB;
extern PFN_xrPassthroughPauseFB xrPassthroughPauseFB;
extern PFN_xrPassthroughStartFB xrPassthroughStartFB;
#endif /*  defined(XR_FB_passthrough)   */
#if defined(XR_FB_passthrough_keyboard_hands)
extern PFN_xrPassthroughLayerSetKeyboardHandsIntensityFB xrPassthroughLayerSetKeyboardHandsIntensityFB;
#endif /*  defined(XR_FB_passthrough_keyboard_hands)   */
#if defined(XR_FB_render_model)
extern PFN_xrEnumerateRenderModelPathsFB xrEnumerateRenderModelPathsFB;
extern PFN_xrGetRenderModelPropertiesFB xrGetRenderModelPropertiesFB;
extern PFN_xrLoadRenderModelFB xrLoadRenderModelFB;
#endif /*  defined(XR_FB_render_model)   */
#if defined(XR_FB_scene)
extern PFN_xrGetSpaceBoundary2DFB xrGetSpaceBoundary2DFB;
extern PFN_xrGetSpaceBoundingBox2DFB xrGetSpaceBoundingBox2DFB;
extern PFN_xrGetSpaceBoundingBox3DFB xrGetSpaceBoundingBox3DFB;
extern PFN_xrGetSpaceRoomLayoutFB xrGetSpaceRoomLayoutFB;
extern PFN_xrGetSpaceSemanticLabelsFB xrGetSpaceSemanticLabelsFB;
#endif /*  defined(XR_FB_scene)   */
#if defined(XR_FB_scene_capture)
extern PFN_xrRequestSceneCaptureFB xrRequestSceneCaptureFB;
#endif /*  defined(XR_FB_scene_capture)   */
#if defined(XR_FB_spatial_entity)
extern PFN_xrCreateSpatialAnchorFB xrCreateSpatialAnchorFB;
extern PFN_xrEnumerateSpaceSupportedComponentsFB xrEnumerateSpaceSupportedComponentsFB;
extern PFN_xrGetSpaceComponentStatusFB xrGetSpaceComponentStatusFB;
extern PFN_xrGetSpaceUuidFB xrGetSpaceUuidFB;
extern PFN_xrSetSpaceComponentStatusFB xrSetSpaceComponentStatusFB;
#endif /*  defined(XR_FB_spatial_entity)   */
#if defined(XR_FB_spatial_entity_container)
extern PFN_xrGetSpaceContainerFB xrGetSpaceContainerFB;
#endif /*  defined(XR_FB_spatial_entity_container)   */
#if defined(XR_FB_spatial_entity_query)
extern PFN_xrQuerySpacesFB xrQuerySpacesFB;
extern PFN_xrRetrieveSpaceQueryResultsFB xrRetrieveSpaceQueryResultsFB;
#endif /*  defined(XR_FB_spatial_entity_query)   */
#if defined(XR_FB_spatial_entity_sharing)
extern PFN_xrShareSpacesFB xrShareSpacesFB;
#endif /*  defined(XR_FB_spatial_entity_sharing)   */
#if defined(XR_FB_spatial_entity_storage)
extern PFN_xrEraseSpaceFB xrEraseSpaceFB;
extern PFN_xrSaveSpaceFB xrSaveSpaceFB;
#endif /*  defined(XR_FB_spatial_entity_storage)   */
#if defined(XR_FB_spatial_entity_storage_batch)
extern PFN_xrSaveSpaceListFB xrSaveSpaceListFB;
#endif /*  defined(XR_FB_spatial_entity_storage_batch)   */
#if defined(XR_FB_spatial_entity_user)
extern PFN_xrCreateSpaceUserFB xrCreateSpaceUserFB;
extern PFN_xrDestroySpaceUserFB xrDestroySpaceUserFB;
extern PFN_xrGetSpaceUserIdFB xrGetSpaceUserIdFB;
#endif /*  defined(XR_FB_spatial_entity_user)   */
#if defined(XR_FB_swapchain_update_state)
extern PFN_xrGetSwapchainStateFB xrGetSwapchainStateFB;
extern PFN_xrUpdateSwapchainFB xrUpdateSwapchainFB;
#endif /*  defined(XR_FB_swapchain_update_state)   */
#if defined(XR_FB_triangle_mesh)
extern PFN_xrCreateTriangleMeshFB xrCreateTriangleMeshFB;
extern PFN_xrDestroyTriangleMeshFB xrDestroyTriangleMeshFB;
extern PFN_xrTriangleMeshBeginUpdateFB xrTriangleMeshBeginUpdateFB;
extern PFN_xrTriangleMeshBeginVertexBufferUpdateFB xrTriangleMeshBeginVertexBufferUpdateFB;
extern PFN_xrTriangleMeshEndUpdateFB xrTriangleMeshEndUpdateFB;
extern PFN_xrTriangleMeshEndVertexBufferUpdateFB xrTriangleMeshEndVertexBufferUpdateFB;
extern PFN_xrTriangleMeshGetIndexBufferFB xrTriangleMeshGetIndexBufferFB;
extern PFN_xrTriangleMeshGetVertexBufferFB xrTriangleMeshGetVertexBufferFB;
#endif /*  defined(XR_FB_triangle_mesh)   */
#if defined(XR_HTCX_vive_tracker_interaction)
extern PFN_xrEnumerateViveTrackerPathsHTCX xrEnumerateViveTrackerPathsHTCX;
#endif /*  defined(XR_HTCX_vive_tracker_interaction)   */
#if defined(XR_HTC_anchor)
extern PFN_xrCreateSpatialAnchorHTC xrCreateSpatialAnchorHTC;
extern PFN_xrGetSpatialAnchorNameHTC xrGetSpatialAnchorNameHTC;
#endif /*  defined(XR_HTC_anchor)   */
#if defined(XR_HTC_facial_tracking)
extern PFN_xrCreateFacialTrackerHTC xrCreateFacialTrackerHTC;
extern PFN_xrDestroyFacialTrackerHTC xrDestroyFacialTrackerHTC;
extern PFN_xrGetFacialExpressionsHTC xrGetFacialExpressionsHTC;
#endif /*  defined(XR_HTC_facial_tracking)   */
#if defined(XR_HTC_foveation)
extern PFN_xrApplyFoveationHTC xrApplyFoveationHTC;
#endif /*  defined(XR_HTC_foveation)   */
#if defined(XR_HTC_passthrough)
extern PFN_xrCreatePassthroughHTC xrCreatePassthroughHTC;
extern PFN_xrDestroyPassthroughHTC xrDestroyPassthroughHTC;
#endif /*  defined(XR_HTC_passthrough)   */
#if defined(XR_KHR_D3D11_enable)
extern PFN_xrGetD3D11GraphicsRequirementsKHR xrGetD3D11GraphicsRequirementsKHR;
#endif /*  defined(XR_KHR_D3D11_enable)   */
#if defined(XR_KHR_D3D12_enable)
extern PFN_xrGetD3D12GraphicsRequirementsKHR xrGetD3D12GraphicsRequirementsKHR;
#endif /*  defined(XR_KHR_D3D12_enable)   */
#if defined(XR_KHR_android_surface_swapchain)
extern PFN_xrCreateSwapchainAndroidSurfaceKHR xrCreateSwapchainAndroidSurfaceKHR;
#endif /*  defined(XR_KHR_android_surface_swapchain)   */
#if defined(XR_KHR_android_thread_settings)
extern PFN_xrSetAndroidApplicationThreadKHR xrSetAndroidApplicationThreadKHR;
#endif /*  defined(XR_KHR_android_thread_settings)   */
#if defined(XR_KHR_convert_timespec_time)
extern PFN_xrConvertTimeToTimespecTimeKHR xrConvertTimeToTimespecTimeKHR;
extern PFN_xrConvertTimespecTimeToTimeKHR xrConvertTimespecTimeToTimeKHR;
#endif /*  defined(XR_KHR_convert_timespec_time)   */
#if defined(XR_KHR_loader_init)
extern PFN_xrInitializeLoaderKHR xrInitializeLoaderKHR;
#endif /*  defined(XR_KHR_loader_init)   */
#if defined(XR_KHR_locate_spaces)
extern PFN_xrLocateSpacesKHR xrLocateSpacesKHR;
#endif /*  defined(XR_KHR_locate_spaces)   */
#if defined(XR_KHR_opengl_enable)
extern PFN_xrGetOpenGLGraphicsRequirementsKHR xrGetOpenGLGraphicsRequirementsKHR;
#endif /*  defined(XR_KHR_opengl_enable)   */
#if defined(XR_KHR_opengl_es_enable)
extern PFN_xrGetOpenGLESGraphicsRequirementsKHR xrGetOpenGLESGraphicsRequirementsKHR;
#endif /*  defined(XR_KHR_opengl_es_enable)   */
#if defined(XR_KHR_visibility_mask)
extern PFN_xrGetVisibilityMaskKHR xrGetVisibilityMaskKHR;
#endif /*  defined(XR_KHR_visibility_mask)   */
#if defined(XR_KHR_vulkan_enable)
extern PFN_xrGetVulkanDeviceExtensionsKHR xrGetVulkanDeviceExtensionsKHR;
extern PFN_xrGetVulkanGraphicsDeviceKHR xrGetVulkanGraphicsDeviceKHR;
extern PFN_xrGetVulkanGraphicsRequirementsKHR xrGetVulkanGraphicsRequirementsKHR;
extern PFN_xrGetVulkanInstanceExtensionsKHR xrGetVulkanInstanceExtensionsKHR;
#endif /*  defined(XR_KHR_vulkan_enable)   */
#if defined(XR_KHR_vulkan_enable2)
extern PFN_xrCreateVulkanDeviceKHR xrCreateVulkanDeviceKHR;
extern PFN_xrCreateVulkanInstanceKHR xrCreateVulkanInstanceKHR;
extern PFN_xrGetVulkanGraphicsDevice2KHR xrGetVulkanGraphicsDevice2KHR;
extern PFN_xrGetVulkanGraphicsRequirements2KHR xrGetVulkanGraphicsRequirements2KHR;
#endif /*  defined(XR_KHR_vulkan_enable2)   */
#if defined(XR_KHR_win32_convert_performance_counter_time)
extern PFN_xrConvertTimeToWin32PerformanceCounterKHR xrConvertTimeToWin32PerformanceCounterKHR;
extern PFN_xrConvertWin32PerformanceCounterToTimeKHR xrConvertWin32PerformanceCounterToTimeKHR;
#endif /*  defined(XR_KHR_win32_convert_performance_counter_time)   */
#if defined(XR_META_environment_depth)
extern PFN_xrAcquireEnvironmentDepthImageMETA xrAcquireEnvironmentDepthImageMETA;
extern PFN_xrCreateEnvironmentDepthProviderMETA xrCreateEnvironmentDepthProviderMETA;
extern PFN_xrCreateEnvironmentDepthSwapchainMETA xrCreateEnvironmentDepthSwapchainMETA;
extern PFN_xrDestroyEnvironmentDepthProviderMETA xrDestroyEnvironmentDepthProviderMETA;
extern PFN_xrDestroyEnvironmentDepthSwapchainMETA xrDestroyEnvironmentDepthSwapchainMETA;
extern PFN_xrEnumerateEnvironmentDepthSwapchainImagesMETA xrEnumerateEnvironmentDepthSwapchainImagesMETA;
extern PFN_xrGetEnvironmentDepthSwapchainStateMETA xrGetEnvironmentDepthSwapchainStateMETA;
extern PFN_xrSetEnvironmentDepthHandRemovalMETA xrSetEnvironmentDepthHandRemovalMETA;
extern PFN_xrStartEnvironmentDepthProviderMETA xrStartEnvironmentDepthProviderMETA;
extern PFN_xrStopEnvironmentDepthProviderMETA xrStopEnvironmentDepthProviderMETA;
#endif /*  defined(XR_META_environment_depth)   */
#if defined(XR_META_foveation_eye_tracked)
extern PFN_xrGetFoveationEyeTrackedStateMETA xrGetFoveationEyeTrackedStateMETA;
#endif /*  defined(XR_META_foveation_eye_tracked)   */
#if defined(XR_META_passthrough_color_lut)
extern PFN_xrCreatePassthroughColorLutMETA xrCreatePassthroughColorLutMETA;
extern PFN_xrDestroyPassthroughColorLutMETA xrDestroyPassthroughColorLutMETA;
extern PFN_xrUpdatePassthroughColorLutMETA xrUpdatePassthroughColorLutMETA;
#endif /*  defined(XR_META_passthrough_color_lut)   */
#if defined(XR_META_passthrough_preferences)
extern PFN_xrGetPassthroughPreferencesMETA xrGetPassthroughPreferencesMETA;
#endif /*  defined(XR_META_passthrough_preferences)   */
#if defined(XR_META_performance_metrics)
extern PFN_xrEnumeratePerformanceMetricsCounterPathsMETA xrEnumeratePerformanceMetricsCounterPathsMETA;
extern PFN_xrGetPerformanceMetricsStateMETA xrGetPerformanceMetricsStateMETA;
extern PFN_xrQueryPerformanceMetricsCounterMETA xrQueryPerformanceMetricsCounterMETA;
extern PFN_xrSetPerformanceMetricsStateMETA xrSetPerformanceMetricsStateMETA;
#endif /*  defined(XR_META_performance_metrics)   */
#if defined(XR_META_recommended_layer_resolution)
extern PFN_xrGetRecommendedLayerResolutionMETA xrGetRecommendedLayerResolutionMETA;
#endif /*  defined(XR_META_recommended_layer_resolution)   */
#if defined(XR_META_spatial_entity_mesh)
extern PFN_xrGetSpaceTriangleMeshMETA xrGetSpaceTriangleMeshMETA;
#endif /*  defined(XR_META_spatial_entity_mesh)   */
#if defined(XR_META_virtual_keyboard)
extern PFN_xrChangeVirtualKeyboardTextContextMETA xrChangeVirtualKeyboardTextContextMETA;
extern PFN_xrCreateVirtualKeyboardMETA xrCreateVirtualKeyboardMETA;
extern PFN_xrCreateVirtualKeyboardSpaceMETA xrCreateVirtualKeyboardSpaceMETA;
extern PFN_xrDestroyVirtualKeyboardMETA xrDestroyVirtualKeyboardMETA;
extern PFN_xrGetVirtualKeyboardDirtyTexturesMETA xrGetVirtualKeyboardDirtyTexturesMETA;
extern PFN_xrGetVirtualKeyboardModelAnimationStatesMETA xrGetVirtualKeyboardModelAnimationStatesMETA;
extern PFN_xrGetVirtualKeyboardScaleMETA xrGetVirtualKeyboardScaleMETA;
extern PFN_xrGetVirtualKeyboardTextureDataMETA xrGetVirtualKeyboardTextureDataMETA;
extern PFN_xrSendVirtualKeyboardInputMETA xrSendVirtualKeyboardInputMETA;
extern PFN_xrSetVirtualKeyboardModelVisibilityMETA xrSetVirtualKeyboardModelVisibilityMETA;
extern PFN_xrSuggestVirtualKeyboardLocationMETA xrSuggestVirtualKeyboardLocationMETA;
#endif /*  defined(XR_META_virtual_keyboard)   */
#if defined(XR_ML_compat)
extern PFN_xrCreateSpaceFromCoordinateFrameUIDML xrCreateSpaceFromCoordinateFrameUIDML;
#endif /*  defined(XR_ML_compat)   */
#if defined(XR_ML_localization_map)
extern PFN_xrCreateExportedLocalizationMapML xrCreateExportedLocalizationMapML;
extern PFN_xrDestroyExportedLocalizationMapML xrDestroyExportedLocalizationMapML;
extern PFN_xrEnableLocalizationEventsML xrEnableLocalizationEventsML;
extern PFN_xrGetExportedLocalizationMapDataML xrGetExportedLocalizationMapDataML;
extern PFN_xrImportLocalizationMapML xrImportLocalizationMapML;
extern PFN_xrQueryLocalizationMapsML xrQueryLocalizationMapsML;
extern PFN_xrRequestMapLocalizationML xrRequestMapLocalizationML;
#endif /*  defined(XR_ML_localization_map)   */
#if defined(XR_ML_marker_understanding)
extern PFN_xrCreateMarkerDetectorML xrCreateMarkerDetectorML;
extern PFN_xrCreateMarkerSpaceML xrCreateMarkerSpaceML;
extern PFN_xrDestroyMarkerDetectorML xrDestroyMarkerDetectorML;
extern PFN_xrGetMarkerDetectorStateML xrGetMarkerDetectorStateML;
extern PFN_xrGetMarkerLengthML xrGetMarkerLengthML;
extern PFN_xrGetMarkerNumberML xrGetMarkerNumberML;
extern PFN_xrGetMarkerReprojectionErrorML xrGetMarkerReprojectionErrorML;
extern PFN_xrGetMarkerStringML xrGetMarkerStringML;
extern PFN_xrGetMarkersML xrGetMarkersML;
extern PFN_xrSnapshotMarkerDetectorML xrSnapshotMarkerDetectorML;
#endif /*  defined(XR_ML_marker_understanding)   */
#if defined(XR_ML_user_calibration)
extern PFN_xrEnableUserCalibrationEventsML xrEnableUserCalibrationEventsML;
#endif /*  defined(XR_ML_user_calibration)   */
#if defined(XR_MNDX_force_feedback_curl)
extern PFN_xrApplyForceFeedbackCurlMNDX xrApplyForceFeedbackCurlMNDX;
#endif /*  defined(XR_MNDX_force_feedback_curl)   */
#if defined(XR_MSFT_composition_layer_reprojection)
extern PFN_xrEnumerateReprojectionModesMSFT xrEnumerateReprojectionModesMSFT;
#endif /*  defined(XR_MSFT_composition_layer_reprojection)   */
#if defined(XR_MSFT_controller_model)
extern PFN_xrGetControllerModelKeyMSFT xrGetControllerModelKeyMSFT;
extern PFN_xrGetControllerModelPropertiesMSFT xrGetControllerModelPropertiesMSFT;
extern PFN_xrGetControllerModelStateMSFT xrGetControllerModelStateMSFT;
extern PFN_xrLoadControllerModelMSFT xrLoadControllerModelMSFT;
#endif /*  defined(XR_MSFT_controller_model)   */
#if defined(XR_MSFT_hand_tracking_mesh)
extern PFN_xrCreateHandMeshSpaceMSFT xrCreateHandMeshSpaceMSFT;
extern PFN_xrUpdateHandMeshMSFT xrUpdateHandMeshMSFT;
#endif /*  defined(XR_MSFT_hand_tracking_mesh)   */
#if defined(XR_MSFT_perception_anchor_interop)
extern PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT xrCreateSpatialAnchorFromPerceptionAnchorMSFT;
extern PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT xrTryGetPerceptionAnchorFromSpatialAnchorMSFT;
#endif /*  defined(XR_MSFT_perception_anchor_interop)   */
#if defined(XR_MSFT_scene_marker)
extern PFN_xrGetSceneMarkerDecodedStringMSFT xrGetSceneMarkerDecodedStringMSFT;
extern PFN_xrGetSceneMarkerRawDataMSFT xrGetSceneMarkerRawDataMSFT;
#endif /*  defined(XR_MSFT_scene_marker)   */
#if defined(XR_MSFT_scene_understanding)
extern PFN_xrComputeNewSceneMSFT xrComputeNewSceneMSFT;
extern PFN_xrCreateSceneMSFT xrCreateSceneMSFT;
extern PFN_xrCreateSceneObserverMSFT xrCreateSceneObserverMSFT;
extern PFN_xrDestroySceneMSFT xrDestroySceneMSFT;
extern PFN_xrDestroySceneObserverMSFT xrDestroySceneObserverMSFT;
extern PFN_xrEnumerateSceneComputeFeaturesMSFT xrEnumerateSceneComputeFeaturesMSFT;
extern PFN_xrGetSceneComponentsMSFT xrGetSceneComponentsMSFT;
extern PFN_xrGetSceneComputeStateMSFT xrGetSceneComputeStateMSFT;
extern PFN_xrGetSceneMeshBuffersMSFT xrGetSceneMeshBuffersMSFT;
extern PFN_xrLocateSceneComponentsMSFT xrLocateSceneComponentsMSFT;
#endif /*  defined(XR_MSFT_scene_understanding)   */
#if defined(XR_MSFT_scene_understanding_serialization)
extern PFN_xrDeserializeSceneMSFT xrDeserializeSceneMSFT;
extern PFN_xrGetSerializedSceneFragmentDataMSFT xrGetSerializedSceneFragmentDataMSFT;
#endif /*  defined(XR_MSFT_scene_understanding_serialization)   */
#if defined(XR_MSFT_spatial_anchor)
extern PFN_xrCreateSpatialAnchorMSFT xrCreateSpatialAnchorMSFT;
extern PFN_xrCreateSpatialAnchorSpaceMSFT xrCreateSpatialAnchorSpaceMSFT;
extern PFN_xrDestroySpatialAnchorMSFT xrDestroySpatialAnchorMSFT;
#endif /*  defined(XR_MSFT_spatial_anchor)   */
#if defined(XR_MSFT_spatial_anchor_persistence)
extern PFN_xrClearSpatialAnchorStoreMSFT xrClearSpatialAnchorStoreMSFT;
extern PFN_xrCreateSpatialAnchorFromPersistedNameMSFT xrCreateSpatialAnchorFromPersistedNameMSFT;
extern PFN_xrCreateSpatialAnchorStoreConnectionMSFT xrCreateSpatialAnchorStoreConnectionMSFT;
extern PFN_xrDestroySpatialAnchorStoreConnectionMSFT xrDestroySpatialAnchorStoreConnectionMSFT;
extern PFN_xrEnumeratePersistedSpatialAnchorNamesMSFT xrEnumeratePersistedSpatialAnchorNamesMSFT;
extern PFN_xrPersistSpatialAnchorMSFT xrPersistSpatialAnchorMSFT;
extern PFN_xrUnpersistSpatialAnchorMSFT xrUnpersistSpatialAnchorMSFT;
#endif /*  defined(XR_MSFT_spatial_anchor_persistence)   */
#if defined(XR_MSFT_spatial_graph_bridge)
extern PFN_xrCreateSpatialGraphNodeSpaceMSFT xrCreateSpatialGraphNodeSpaceMSFT;
extern PFN_xrDestroySpatialGraphNodeBindingMSFT xrDestroySpatialGraphNodeBindingMSFT;
extern PFN_xrGetSpatialGraphNodeBindingPropertiesMSFT xrGetSpatialGraphNodeBindingPropertiesMSFT;
extern PFN_xrTryCreateSpatialGraphStaticNodeBindingMSFT xrTryCreateSpatialGraphStaticNodeBindingMSFT;
#endif /*  defined(XR_MSFT_spatial_graph_bridge)   */
#if defined(XR_OCULUS_audio_device_guid)
extern PFN_xrGetAudioInputDeviceGuidOculus xrGetAudioInputDeviceGuidOculus;
extern PFN_xrGetAudioOutputDeviceGuidOculus xrGetAudioOutputDeviceGuidOculus;
#endif /*  defined(XR_OCULUS_audio_device_guid)   */
#if defined(XR_OCULUS_external_camera)
extern PFN_xrEnumerateExternalCamerasOCULUS xrEnumerateExternalCamerasOCULUS;
#endif /*  defined(XR_OCULUS_external_camera)   */
#if defined(XR_QCOM_tracking_optimization_settings)
extern PFN_xrSetTrackingOptimizationSettingsHintQCOM xrSetTrackingOptimizationSettingsHintQCOM;
#endif /*  defined(XR_QCOM_tracking_optimization_settings)   */
#if defined(XR_VARJO_environment_depth_estimation)
extern PFN_xrSetEnvironmentDepthEstimationVARJO xrSetEnvironmentDepthEstimationVARJO;
#endif /*  defined(XR_VARJO_environment_depth_estimation)   */
#if defined(XR_VARJO_marker_tracking)
extern PFN_xrCreateMarkerSpaceVARJO xrCreateMarkerSpaceVARJO;
extern PFN_xrGetMarkerSizeVARJO xrGetMarkerSizeVARJO;
extern PFN_xrSetMarkerTrackingPredictionVARJO xrSetMarkerTrackingPredictionVARJO;
extern PFN_xrSetMarkerTrackingTimeoutVARJO xrSetMarkerTrackingTimeoutVARJO;
extern PFN_xrSetMarkerTrackingVARJO xrSetMarkerTrackingVARJO;
#endif /*  defined(XR_VARJO_marker_tracking)   */
#if defined(XR_VARJO_view_offset)
extern PFN_xrSetViewOffsetVARJO xrSetViewOffsetVARJO;
#endif /*  defined(XR_VARJO_view_offset)   */

#else

//SECTION(V): XR_PROTOTYPE_HEADER
#if defined(XR_VERSION_1_0)
extern PFN_xrAcquireSwapchainImage xrAcquireSwapchainImage;
extern PFN_xrApplyHapticFeedback xrApplyHapticFeedback;
extern PFN_xrAttachSessionActionSets xrAttachSessionActionSets;
extern PFN_xrBeginFrame xrBeginFrame;
extern PFN_xrBeginSession xrBeginSession;
extern PFN_xrCreateAction xrCreateAction;
extern PFN_xrCreateActionSet xrCreateActionSet;
extern PFN_xrCreateActionSpace xrCreateActionSpace;
extern PFN_xrCreateInstance xrCreateInstance;
extern PFN_xrCreateReferenceSpace xrCreateReferenceSpace;
extern PFN_xrCreateSession xrCreateSession;
extern PFN_xrCreateSwapchain xrCreateSwapchain;
extern PFN_xrDestroyAction xrDestroyAction;
extern PFN_xrDestroyActionSet xrDestroyActionSet;
extern PFN_xrDestroyInstance xrDestroyInstance;
extern PFN_xrDestroySession xrDestroySession;
extern PFN_xrDestroySpace xrDestroySpace;
extern PFN_xrDestroySwapchain xrDestroySwapchain;
extern PFN_xrEndFrame xrEndFrame;
extern PFN_xrEndSession xrEndSession;
extern PFN_xrEnumerateApiLayerProperties xrEnumerateApiLayerProperties;
extern PFN_xrEnumerateBoundSourcesForAction xrEnumerateBoundSourcesForAction;
extern PFN_xrEnumerateEnvironmentBlendModes xrEnumerateEnvironmentBlendModes;
extern PFN_xrEnumerateInstanceExtensionProperties xrEnumerateInstanceExtensionProperties;
extern PFN_xrEnumerateReferenceSpaces xrEnumerateReferenceSpaces;
extern PFN_xrEnumerateSwapchainFormats xrEnumerateSwapchainFormats;
extern PFN_xrEnumerateSwapchainImages xrEnumerateSwapchainImages;
extern PFN_xrEnumerateViewConfigurationViews xrEnumerateViewConfigurationViews;
extern PFN_xrEnumerateViewConfigurations xrEnumerateViewConfigurations;
extern PFN_xrGetActionStateBoolean xrGetActionStateBoolean;
extern PFN_xrGetActionStateFloat xrGetActionStateFloat;
extern PFN_xrGetActionStatePose xrGetActionStatePose;
extern PFN_xrGetActionStateVector2f xrGetActionStateVector2f;
extern PFN_xrGetCurrentInteractionProfile xrGetCurrentInteractionProfile;
extern PFN_xrGetInputSourceLocalizedName xrGetInputSourceLocalizedName;
extern PFN_xrGetInstanceProcAddr xrGetInstanceProcAddr;
extern PFN_xrGetInstanceProperties xrGetInstanceProperties;
extern PFN_xrGetReferenceSpaceBoundsRect xrGetReferenceSpaceBoundsRect;
extern PFN_xrGetSystem xrGetSystem;
extern PFN_xrGetSystemProperties xrGetSystemProperties;
extern PFN_xrGetViewConfigurationProperties xrGetViewConfigurationProperties;
extern PFN_xrLocateSpace xrLocateSpace;
extern PFN_xrLocateViews xrLocateViews;
extern PFN_xrPathToString xrPathToString;
extern PFN_xrPollEvent xrPollEvent;
extern PFN_xrReleaseSwapchainImage xrReleaseSwapchainImage;
extern PFN_xrRequestExitSession xrRequestExitSession;
extern PFN_xrResultToString xrResultToString;
extern PFN_xrStopHapticFeedback xrStopHapticFeedback;
extern PFN_xrStringToPath xrStringToPath;
extern PFN_xrStructureTypeToString xrStructureTypeToString;
extern PFN_xrSuggestInteractionProfileBindings xrSuggestInteractionProfileBindings;
extern PFN_xrSyncActions xrSyncActions;
extern PFN_xrWaitFrame xrWaitFrame;
extern PFN_xrWaitSwapchainImage xrWaitSwapchainImage;
#endif /*  defined(XR_VERSION_1_0)   */
#if defined(XR_LOADER_VERSION_1_0)
extern PFN_xrCreateApiLayerInstance xrCreateApiLayerInstance;
extern PFN_xrNegotiateLoaderApiLayerInterface xrNegotiateLoaderApiLayerInterface;
extern PFN_xrNegotiateLoaderRuntimeInterface xrNegotiateLoaderRuntimeInterface;
#endif /*  defined(XR_LOADER_VERSION_1_0)   */
#if defined(XR_VERSION_1_1)
extern PFN_xrLocateSpaces xrLocateSpaces;
#endif /*  defined(XR_VERSION_1_1)   */
#if defined(XR_ALMALENCE_digital_lens_control)
extern PFN_xrSetDigitalLensControlALMALENCE xrSetDigitalLensControlALMALENCE;
#endif /*  defined(XR_ALMALENCE_digital_lens_control)   */
#if defined(XR_EXT_conformance_automation)
extern PFN_xrSetInputDeviceActiveEXT xrSetInputDeviceActiveEXT;
extern PFN_xrSetInputDeviceLocationEXT xrSetInputDeviceLocationEXT;
extern PFN_xrSetInputDeviceStateBoolEXT xrSetInputDeviceStateBoolEXT;
extern PFN_xrSetInputDeviceStateFloatEXT xrSetInputDeviceStateFloatEXT;
extern PFN_xrSetInputDeviceStateVector2fEXT xrSetInputDeviceStateVector2fEXT;
#endif /*  defined(XR_EXT_conformance_automation)   */
#if defined(XR_EXT_debug_utils)
extern PFN_xrCreateDebugUtilsMessengerEXT xrCreateDebugUtilsMessengerEXT;
extern PFN_xrDestroyDebugUtilsMessengerEXT xrDestroyDebugUtilsMessengerEXT;
extern PFN_xrSessionBeginDebugUtilsLabelRegionEXT xrSessionBeginDebugUtilsLabelRegionEXT;
extern PFN_xrSessionEndDebugUtilsLabelRegionEXT xrSessionEndDebugUtilsLabelRegionEXT;
extern PFN_xrSessionInsertDebugUtilsLabelEXT xrSessionInsertDebugUtilsLabelEXT;
extern PFN_xrSetDebugUtilsObjectNameEXT xrSetDebugUtilsObjectNameEXT;
extern PFN_xrSubmitDebugUtilsMessageEXT xrSubmitDebugUtilsMessageEXT;
#endif /*  defined(XR_EXT_debug_utils)   */
#if defined(XR_EXT_future)
extern PFN_xrCancelFutureEXT xrCancelFutureEXT;
extern PFN_xrPollFutureEXT xrPollFutureEXT;
#endif /*  defined(XR_EXT_future)   */
#if defined(XR_EXT_hand_tracking)
extern PFN_xrCreateHandTrackerEXT xrCreateHandTrackerEXT;
extern PFN_xrDestroyHandTrackerEXT xrDestroyHandTrackerEXT;
extern PFN_xrLocateHandJointsEXT xrLocateHandJointsEXT;
#endif /*  defined(XR_EXT_hand_tracking)   */
#if defined(XR_EXT_performance_settings)
extern PFN_xrPerfSettingsSetPerformanceLevelEXT xrPerfSettingsSetPerformanceLevelEXT;
#endif /*  defined(XR_EXT_performance_settings)   */
#if defined(XR_EXT_plane_detection)
extern PFN_xrBeginPlaneDetectionEXT xrBeginPlaneDetectionEXT;
extern PFN_xrCreatePlaneDetectorEXT xrCreatePlaneDetectorEXT;
extern PFN_xrDestroyPlaneDetectorEXT xrDestroyPlaneDetectorEXT;
extern PFN_xrGetPlaneDetectionStateEXT xrGetPlaneDetectionStateEXT;
extern PFN_xrGetPlaneDetectionsEXT xrGetPlaneDetectionsEXT;
extern PFN_xrGetPlanePolygonBufferEXT xrGetPlanePolygonBufferEXT;
#endif /*  defined(XR_EXT_plane_detection)   */
#if defined(XR_EXT_thermal_query)
extern PFN_xrThermalGetTemperatureTrendEXT xrThermalGetTemperatureTrendEXT;
#endif /*  defined(XR_EXT_thermal_query)   */
#if defined(XR_FB_body_tracking)
extern PFN_xrCreateBodyTrackerFB xrCreateBodyTrackerFB;
extern PFN_xrDestroyBodyTrackerFB xrDestroyBodyTrackerFB;
extern PFN_xrGetBodySkeletonFB xrGetBodySkeletonFB;
extern PFN_xrLocateBodyJointsFB xrLocateBodyJointsFB;
#endif /*  defined(XR_FB_body_tracking)   */
#if defined(XR_FB_color_space)
extern PFN_xrEnumerateColorSpacesFB xrEnumerateColorSpacesFB;
extern PFN_xrSetColorSpaceFB xrSetColorSpaceFB;
#endif /*  defined(XR_FB_color_space)   */
#if defined(XR_FB_display_refresh_rate)
extern PFN_xrEnumerateDisplayRefreshRatesFB xrEnumerateDisplayRefreshRatesFB;
extern PFN_xrGetDisplayRefreshRateFB xrGetDisplayRefreshRateFB;
extern PFN_xrRequestDisplayRefreshRateFB xrRequestDisplayRefreshRateFB;
#endif /*  defined(XR_FB_display_refresh_rate)   */
#if defined(XR_FB_eye_tracking_social)
extern PFN_xrCreateEyeTrackerFB xrCreateEyeTrackerFB;
extern PFN_xrDestroyEyeTrackerFB xrDestroyEyeTrackerFB;
extern PFN_xrGetEyeGazesFB xrGetEyeGazesFB;
#endif /*  defined(XR_FB_eye_tracking_social)   */
#if defined(XR_FB_face_tracking)
extern PFN_xrCreateFaceTrackerFB xrCreateFaceTrackerFB;
extern PFN_xrDestroyFaceTrackerFB xrDestroyFaceTrackerFB;
extern PFN_xrGetFaceExpressionWeightsFB xrGetFaceExpressionWeightsFB;
#endif /*  defined(XR_FB_face_tracking)   */
#if defined(XR_FB_face_tracking2)
extern PFN_xrCreateFaceTracker2FB xrCreateFaceTracker2FB;
extern PFN_xrDestroyFaceTracker2FB xrDestroyFaceTracker2FB;
extern PFN_xrGetFaceExpressionWeights2FB xrGetFaceExpressionWeights2FB;
#endif /*  defined(XR_FB_face_tracking2)   */
#if defined(XR_FB_foveation)
extern PFN_xrCreateFoveationProfileFB xrCreateFoveationProfileFB;
extern PFN_xrDestroyFoveationProfileFB xrDestroyFoveationProfileFB;
#endif /*  defined(XR_FB_foveation)   */
#if defined(XR_FB_hand_tracking_mesh)
extern PFN_xrGetHandMeshFB xrGetHandMeshFB;
#endif /*  defined(XR_FB_hand_tracking_mesh)   */
#if defined(XR_FB_haptic_pcm)
extern PFN_xrGetDeviceSampleRateFB xrGetDeviceSampleRateFB;
#endif /*  defined(XR_FB_haptic_pcm)   */
#if defined(XR_FB_keyboard_tracking)
extern PFN_xrCreateKeyboardSpaceFB xrCreateKeyboardSpaceFB;
extern PFN_xrQuerySystemTrackedKeyboardFB xrQuerySystemTrackedKeyboardFB;
#endif /*  defined(XR_FB_keyboard_tracking)   */
#if defined(XR_FB_passthrough)
extern PFN_xrCreateGeometryInstanceFB xrCreateGeometryInstanceFB;
extern PFN_xrCreatePassthroughFB xrCreatePassthroughFB;
extern PFN_xrCreatePassthroughLayerFB xrCreatePassthroughLayerFB;
extern PFN_xrDestroyGeometryInstanceFB xrDestroyGeometryInstanceFB;
extern PFN_xrDestroyPassthroughFB xrDestroyPassthroughFB;
extern PFN_xrDestroyPassthroughLayerFB xrDestroyPassthroughLayerFB;
extern PFN_xrGeometryInstanceSetTransformFB xrGeometryInstanceSetTransformFB;
extern PFN_xrPassthroughLayerPauseFB xrPassthroughLayerPauseFB;
extern PFN_xrPassthroughLayerResumeFB xrPassthroughLayerResumeFB;
extern PFN_xrPassthroughLayerSetStyleFB xrPassthroughLayerSetStyleFB;
extern PFN_xrPassthroughPauseFB xrPassthroughPauseFB;
extern PFN_xrPassthroughStartFB xrPassthroughStartFB;
#endif /*  defined(XR_FB_passthrough)   */
#if defined(XR_FB_passthrough_keyboard_hands)
extern PFN_xrPassthroughLayerSetKeyboardHandsIntensityFB xrPassthroughLayerSetKeyboardHandsIntensityFB;
#endif /*  defined(XR_FB_passthrough_keyboard_hands)   */
#if defined(XR_FB_render_model)
extern PFN_xrEnumerateRenderModelPathsFB xrEnumerateRenderModelPathsFB;
extern PFN_xrGetRenderModelPropertiesFB xrGetRenderModelPropertiesFB;
extern PFN_xrLoadRenderModelFB xrLoadRenderModelFB;
#endif /*  defined(XR_FB_render_model)   */
#if defined(XR_FB_scene)
extern PFN_xrGetSpaceBoundary2DFB xrGetSpaceBoundary2DFB;
extern PFN_xrGetSpaceBoundingBox2DFB xrGetSpaceBoundingBox2DFB;
extern PFN_xrGetSpaceBoundingBox3DFB xrGetSpaceBoundingBox3DFB;
extern PFN_xrGetSpaceRoomLayoutFB xrGetSpaceRoomLayoutFB;
extern PFN_xrGetSpaceSemanticLabelsFB xrGetSpaceSemanticLabelsFB;
#endif /*  defined(XR_FB_scene)   */
#if defined(XR_FB_scene_capture)
extern PFN_xrRequestSceneCaptureFB xrRequestSceneCaptureFB;
#endif /*  defined(XR_FB_scene_capture)   */
#if defined(XR_FB_spatial_entity)
extern PFN_xrCreateSpatialAnchorFB xrCreateSpatialAnchorFB;
extern PFN_xrEnumerateSpaceSupportedComponentsFB xrEnumerateSpaceSupportedComponentsFB;
extern PFN_xrGetSpaceComponentStatusFB xrGetSpaceComponentStatusFB;
extern PFN_xrGetSpaceUuidFB xrGetSpaceUuidFB;
extern PFN_xrSetSpaceComponentStatusFB xrSetSpaceComponentStatusFB;
#endif /*  defined(XR_FB_spatial_entity)   */
#if defined(XR_FB_spatial_entity_container)
extern PFN_xrGetSpaceContainerFB xrGetSpaceContainerFB;
#endif /*  defined(XR_FB_spatial_entity_container)   */
#if defined(XR_FB_spatial_entity_query)
extern PFN_xrQuerySpacesFB xrQuerySpacesFB;
extern PFN_xrRetrieveSpaceQueryResultsFB xrRetrieveSpaceQueryResultsFB;
#endif /*  defined(XR_FB_spatial_entity_query)   */
#if defined(XR_FB_spatial_entity_sharing)
extern PFN_xrShareSpacesFB xrShareSpacesFB;
#endif /*  defined(XR_FB_spatial_entity_sharing)   */
#if defined(XR_FB_spatial_entity_storage)
extern PFN_xrEraseSpaceFB xrEraseSpaceFB;
extern PFN_xrSaveSpaceFB xrSaveSpaceFB;
#endif /*  defined(XR_FB_spatial_entity_storage)   */
#if defined(XR_FB_spatial_entity_storage_batch)
extern PFN_xrSaveSpaceListFB xrSaveSpaceListFB;
#endif /*  defined(XR_FB_spatial_entity_storage_batch)   */
#if defined(XR_FB_spatial_entity_user)
extern PFN_xrCreateSpaceUserFB xrCreateSpaceUserFB;
extern PFN_xrDestroySpaceUserFB xrDestroySpaceUserFB;
extern PFN_xrGetSpaceUserIdFB xrGetSpaceUserIdFB;
#endif /*  defined(XR_FB_spatial_entity_user)   */
#if defined(XR_FB_swapchain_update_state)
extern PFN_xrGetSwapchainStateFB xrGetSwapchainStateFB;
extern PFN_xrUpdateSwapchainFB xrUpdateSwapchainFB;
#endif /*  defined(XR_FB_swapchain_update_state)   */
#if defined(XR_FB_triangle_mesh)
extern PFN_xrCreateTriangleMeshFB xrCreateTriangleMeshFB;
extern PFN_xrDestroyTriangleMeshFB xrDestroyTriangleMeshFB;
extern PFN_xrTriangleMeshBeginUpdateFB xrTriangleMeshBeginUpdateFB;
extern PFN_xrTriangleMeshBeginVertexBufferUpdateFB xrTriangleMeshBeginVertexBufferUpdateFB;
extern PFN_xrTriangleMeshEndUpdateFB xrTriangleMeshEndUpdateFB;
extern PFN_xrTriangleMeshEndVertexBufferUpdateFB xrTriangleMeshEndVertexBufferUpdateFB;
extern PFN_xrTriangleMeshGetIndexBufferFB xrTriangleMeshGetIndexBufferFB;
extern PFN_xrTriangleMeshGetVertexBufferFB xrTriangleMeshGetVertexBufferFB;
#endif /*  defined(XR_FB_triangle_mesh)   */
#if defined(XR_HTCX_vive_tracker_interaction)
extern PFN_xrEnumerateViveTrackerPathsHTCX xrEnumerateViveTrackerPathsHTCX;
#endif /*  defined(XR_HTCX_vive_tracker_interaction)   */
#if defined(XR_HTC_anchor)
extern PFN_xrCreateSpatialAnchorHTC xrCreateSpatialAnchorHTC;
extern PFN_xrGetSpatialAnchorNameHTC xrGetSpatialAnchorNameHTC;
#endif /*  defined(XR_HTC_anchor)   */
#if defined(XR_HTC_facial_tracking)
extern PFN_xrCreateFacialTrackerHTC xrCreateFacialTrackerHTC;
extern PFN_xrDestroyFacialTrackerHTC xrDestroyFacialTrackerHTC;
extern PFN_xrGetFacialExpressionsHTC xrGetFacialExpressionsHTC;
#endif /*  defined(XR_HTC_facial_tracking)   */
#if defined(XR_HTC_foveation)
extern PFN_xrApplyFoveationHTC xrApplyFoveationHTC;
#endif /*  defined(XR_HTC_foveation)   */
#if defined(XR_HTC_passthrough)
extern PFN_xrCreatePassthroughHTC xrCreatePassthroughHTC;
extern PFN_xrDestroyPassthroughHTC xrDestroyPassthroughHTC;
#endif /*  defined(XR_HTC_passthrough)   */
#if defined(XR_KHR_D3D11_enable)
extern PFN_xrGetD3D11GraphicsRequirementsKHR xrGetD3D11GraphicsRequirementsKHR;
#endif /*  defined(XR_KHR_D3D11_enable)   */
#if defined(XR_KHR_D3D12_enable)
extern PFN_xrGetD3D12GraphicsRequirementsKHR xrGetD3D12GraphicsRequirementsKHR;
#endif /*  defined(XR_KHR_D3D12_enable)   */
#if defined(XR_KHR_android_surface_swapchain)
extern PFN_xrCreateSwapchainAndroidSurfaceKHR xrCreateSwapchainAndroidSurfaceKHR;
#endif /*  defined(XR_KHR_android_surface_swapchain)   */
#if defined(XR_KHR_android_thread_settings)
extern PFN_xrSetAndroidApplicationThreadKHR xrSetAndroidApplicationThreadKHR;
#endif /*  defined(XR_KHR_android_thread_settings)   */
#if defined(XR_KHR_convert_timespec_time)
extern PFN_xrConvertTimeToTimespecTimeKHR xrConvertTimeToTimespecTimeKHR;
extern PFN_xrConvertTimespecTimeToTimeKHR xrConvertTimespecTimeToTimeKHR;
#endif /*  defined(XR_KHR_convert_timespec_time)   */
#if defined(XR_KHR_loader_init)
extern PFN_xrInitializeLoaderKHR xrInitializeLoaderKHR;
#endif /*  defined(XR_KHR_loader_init)   */
#if defined(XR_KHR_locate_spaces)
extern PFN_xrLocateSpacesKHR xrLocateSpacesKHR;
#endif /*  defined(XR_KHR_locate_spaces)   */
#if defined(XR_KHR_opengl_enable)
extern PFN_xrGetOpenGLGraphicsRequirementsKHR xrGetOpenGLGraphicsRequirementsKHR;
#endif /*  defined(XR_KHR_opengl_enable)   */
#if defined(XR_KHR_opengl_es_enable)
extern PFN_xrGetOpenGLESGraphicsRequirementsKHR xrGetOpenGLESGraphicsRequirementsKHR;
#endif /*  defined(XR_KHR_opengl_es_enable)   */
#if defined(XR_KHR_visibility_mask)
extern PFN_xrGetVisibilityMaskKHR xrGetVisibilityMaskKHR;
#endif /*  defined(XR_KHR_visibility_mask)   */
#if defined(XR_KHR_vulkan_enable)
extern PFN_xrGetVulkanDeviceExtensionsKHR xrGetVulkanDeviceExtensionsKHR;
extern PFN_xrGetVulkanGraphicsDeviceKHR xrGetVulkanGraphicsDeviceKHR;
extern PFN_xrGetVulkanGraphicsRequirementsKHR xrGetVulkanGraphicsRequirementsKHR;
extern PFN_xrGetVulkanInstanceExtensionsKHR xrGetVulkanInstanceExtensionsKHR;
#endif /*  defined(XR_KHR_vulkan_enable)   */
#if defined(XR_KHR_vulkan_enable2)
extern PFN_xrCreateVulkanDeviceKHR xrCreateVulkanDeviceKHR;
extern PFN_xrCreateVulkanInstanceKHR xrCreateVulkanInstanceKHR;
extern PFN_xrGetVulkanGraphicsDevice2KHR xrGetVulkanGraphicsDevice2KHR;
extern PFN_xrGetVulkanGraphicsRequirements2KHR xrGetVulkanGraphicsRequirements2KHR;
#endif /*  defined(XR_KHR_vulkan_enable2)   */
#if defined(XR_KHR_win32_convert_performance_counter_time)
extern PFN_xrConvertTimeToWin32PerformanceCounterKHR xrConvertTimeToWin32PerformanceCounterKHR;
extern PFN_xrConvertWin32PerformanceCounterToTimeKHR xrConvertWin32PerformanceCounterToTimeKHR;
#endif /*  defined(XR_KHR_win32_convert_performance_counter_time)   */
#if defined(XR_META_environment_depth)
extern PFN_xrAcquireEnvironmentDepthImageMETA xrAcquireEnvironmentDepthImageMETA;
extern PFN_xrCreateEnvironmentDepthProviderMETA xrCreateEnvironmentDepthProviderMETA;
extern PFN_xrCreateEnvironmentDepthSwapchainMETA xrCreateEnvironmentDepthSwapchainMETA;
extern PFN_xrDestroyEnvironmentDepthProviderMETA xrDestroyEnvironmentDepthProviderMETA;
extern PFN_xrDestroyEnvironmentDepthSwapchainMETA xrDestroyEnvironmentDepthSwapchainMETA;
extern PFN_xrEnumerateEnvironmentDepthSwapchainImagesMETA xrEnumerateEnvironmentDepthSwapchainImagesMETA;
extern PFN_xrGetEnvironmentDepthSwapchainStateMETA xrGetEnvironmentDepthSwapchainStateMETA;
extern PFN_xrSetEnvironmentDepthHandRemovalMETA xrSetEnvironmentDepthHandRemovalMETA;
extern PFN_xrStartEnvironmentDepthProviderMETA xrStartEnvironmentDepthProviderMETA;
extern PFN_xrStopEnvironmentDepthProviderMETA xrStopEnvironmentDepthProviderMETA;
#endif /*  defined(XR_META_environment_depth)   */
#if defined(XR_META_foveation_eye_tracked)
extern PFN_xrGetFoveationEyeTrackedStateMETA xrGetFoveationEyeTrackedStateMETA;
#endif /*  defined(XR_META_foveation_eye_tracked)   */
#if defined(XR_META_passthrough_color_lut)
extern PFN_xrCreatePassthroughColorLutMETA xrCreatePassthroughColorLutMETA;
extern PFN_xrDestroyPassthroughColorLutMETA xrDestroyPassthroughColorLutMETA;
extern PFN_xrUpdatePassthroughColorLutMETA xrUpdatePassthroughColorLutMETA;
#endif /*  defined(XR_META_passthrough_color_lut)   */
#if defined(XR_META_passthrough_preferences)
extern PFN_xrGetPassthroughPreferencesMETA xrGetPassthroughPreferencesMETA;
#endif /*  defined(XR_META_passthrough_preferences)   */
#if defined(XR_META_performance_metrics)
extern PFN_xrEnumeratePerformanceMetricsCounterPathsMETA xrEnumeratePerformanceMetricsCounterPathsMETA;
extern PFN_xrGetPerformanceMetricsStateMETA xrGetPerformanceMetricsStateMETA;
extern PFN_xrQueryPerformanceMetricsCounterMETA xrQueryPerformanceMetricsCounterMETA;
extern PFN_xrSetPerformanceMetricsStateMETA xrSetPerformanceMetricsStateMETA;
#endif /*  defined(XR_META_performance_metrics)   */
#if defined(XR_META_recommended_layer_resolution)
extern PFN_xrGetRecommendedLayerResolutionMETA xrGetRecommendedLayerResolutionMETA;
#endif /*  defined(XR_META_recommended_layer_resolution)   */
#if defined(XR_META_spatial_entity_mesh)
extern PFN_xrGetSpaceTriangleMeshMETA xrGetSpaceTriangleMeshMETA;
#endif /*  defined(XR_META_spatial_entity_mesh)   */
#if defined(XR_META_virtual_keyboard)
extern PFN_xrChangeVirtualKeyboardTextContextMETA xrChangeVirtualKeyboardTextContextMETA;
extern PFN_xrCreateVirtualKeyboardMETA xrCreateVirtualKeyboardMETA;
extern PFN_xrCreateVirtualKeyboardSpaceMETA xrCreateVirtualKeyboardSpaceMETA;
extern PFN_xrDestroyVirtualKeyboardMETA xrDestroyVirtualKeyboardMETA;
extern PFN_xrGetVirtualKeyboardDirtyTexturesMETA xrGetVirtualKeyboardDirtyTexturesMETA;
extern PFN_xrGetVirtualKeyboardModelAnimationStatesMETA xrGetVirtualKeyboardModelAnimationStatesMETA;
extern PFN_xrGetVirtualKeyboardScaleMETA xrGetVirtualKeyboardScaleMETA;
extern PFN_xrGetVirtualKeyboardTextureDataMETA xrGetVirtualKeyboardTextureDataMETA;
extern PFN_xrSendVirtualKeyboardInputMETA xrSendVirtualKeyboardInputMETA;
extern PFN_xrSetVirtualKeyboardModelVisibilityMETA xrSetVirtualKeyboardModelVisibilityMETA;
extern PFN_xrSuggestVirtualKeyboardLocationMETA xrSuggestVirtualKeyboardLocationMETA;
#endif /*  defined(XR_META_virtual_keyboard)   */
#if defined(XR_ML_compat)
extern PFN_xrCreateSpaceFromCoordinateFrameUIDML xrCreateSpaceFromCoordinateFrameUIDML;
#endif /*  defined(XR_ML_compat)   */
#if defined(XR_ML_localization_map)
extern PFN_xrCreateExportedLocalizationMapML xrCreateExportedLocalizationMapML;
extern PFN_xrDestroyExportedLocalizationMapML xrDestroyExportedLocalizationMapML;
extern PFN_xrEnableLocalizationEventsML xrEnableLocalizationEventsML;
extern PFN_xrGetExportedLocalizationMapDataML xrGetExportedLocalizationMapDataML;
extern PFN_xrImportLocalizationMapML xrImportLocalizationMapML;
extern PFN_xrQueryLocalizationMapsML xrQueryLocalizationMapsML;
extern PFN_xrRequestMapLocalizationML xrRequestMapLocalizationML;
#endif /*  defined(XR_ML_localization_map)   */
#if defined(XR_ML_marker_understanding)
extern PFN_xrCreateMarkerDetectorML xrCreateMarkerDetectorML;
extern PFN_xrCreateMarkerSpaceML xrCreateMarkerSpaceML;
extern PFN_xrDestroyMarkerDetectorML xrDestroyMarkerDetectorML;
extern PFN_xrGetMarkerDetectorStateML xrGetMarkerDetectorStateML;
extern PFN_xrGetMarkerLengthML xrGetMarkerLengthML;
extern PFN_xrGetMarkerNumberML xrGetMarkerNumberML;
extern PFN_xrGetMarkerReprojectionErrorML xrGetMarkerReprojectionErrorML;
extern PFN_xrGetMarkerStringML xrGetMarkerStringML;
extern PFN_xrGetMarkersML xrGetMarkersML;
extern PFN_xrSnapshotMarkerDetectorML xrSnapshotMarkerDetectorML;
#endif /*  defined(XR_ML_marker_understanding)   */
#if defined(XR_ML_user_calibration)
extern PFN_xrEnableUserCalibrationEventsML xrEnableUserCalibrationEventsML;
#endif /*  defined(XR_ML_user_calibration)   */
#if defined(XR_MNDX_force_feedback_curl)
extern PFN_xrApplyForceFeedbackCurlMNDX xrApplyForceFeedbackCurlMNDX;
#endif /*  defined(XR_MNDX_force_feedback_curl)   */
#if defined(XR_MSFT_composition_layer_reprojection)
extern PFN_xrEnumerateReprojectionModesMSFT xrEnumerateReprojectionModesMSFT;
#endif /*  defined(XR_MSFT_composition_layer_reprojection)   */
#if defined(XR_MSFT_controller_model)
extern PFN_xrGetControllerModelKeyMSFT xrGetControllerModelKeyMSFT;
extern PFN_xrGetControllerModelPropertiesMSFT xrGetControllerModelPropertiesMSFT;
extern PFN_xrGetControllerModelStateMSFT xrGetControllerModelStateMSFT;
extern PFN_xrLoadControllerModelMSFT xrLoadControllerModelMSFT;
#endif /*  defined(XR_MSFT_controller_model)   */
#if defined(XR_MSFT_hand_tracking_mesh)
extern PFN_xrCreateHandMeshSpaceMSFT xrCreateHandMeshSpaceMSFT;
extern PFN_xrUpdateHandMeshMSFT xrUpdateHandMeshMSFT;
#endif /*  defined(XR_MSFT_hand_tracking_mesh)   */
#if defined(XR_MSFT_perception_anchor_interop)
extern PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT xrCreateSpatialAnchorFromPerceptionAnchorMSFT;
extern PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT xrTryGetPerceptionAnchorFromSpatialAnchorMSFT;
#endif /*  defined(XR_MSFT_perception_anchor_interop)   */
#if defined(XR_MSFT_scene_marker)
extern PFN_xrGetSceneMarkerDecodedStringMSFT xrGetSceneMarkerDecodedStringMSFT;
extern PFN_xrGetSceneMarkerRawDataMSFT xrGetSceneMarkerRawDataMSFT;
#endif /*  defined(XR_MSFT_scene_marker)   */
#if defined(XR_MSFT_scene_understanding)
extern PFN_xrComputeNewSceneMSFT xrComputeNewSceneMSFT;
extern PFN_xrCreateSceneMSFT xrCreateSceneMSFT;
extern PFN_xrCreateSceneObserverMSFT xrCreateSceneObserverMSFT;
extern PFN_xrDestroySceneMSFT xrDestroySceneMSFT;
extern PFN_xrDestroySceneObserverMSFT xrDestroySceneObserverMSFT;
extern PFN_xrEnumerateSceneComputeFeaturesMSFT xrEnumerateSceneComputeFeaturesMSFT;
extern PFN_xrGetSceneComponentsMSFT xrGetSceneComponentsMSFT;
extern PFN_xrGetSceneComputeStateMSFT xrGetSceneComputeStateMSFT;
extern PFN_xrGetSceneMeshBuffersMSFT xrGetSceneMeshBuffersMSFT;
extern PFN_xrLocateSceneComponentsMSFT xrLocateSceneComponentsMSFT;
#endif /*  defined(XR_MSFT_scene_understanding)   */
#if defined(XR_MSFT_scene_understanding_serialization)
extern PFN_xrDeserializeSceneMSFT xrDeserializeSceneMSFT;
extern PFN_xrGetSerializedSceneFragmentDataMSFT xrGetSerializedSceneFragmentDataMSFT;
#endif /*  defined(XR_MSFT_scene_understanding_serialization)   */
#if defined(XR_MSFT_spatial_anchor)
extern PFN_xrCreateSpatialAnchorMSFT xrCreateSpatialAnchorMSFT;
extern PFN_xrCreateSpatialAnchorSpaceMSFT xrCreateSpatialAnchorSpaceMSFT;
extern PFN_xrDestroySpatialAnchorMSFT xrDestroySpatialAnchorMSFT;
#endif /*  defined(XR_MSFT_spatial_anchor)   */
#if defined(XR_MSFT_spatial_anchor_persistence)
extern PFN_xrClearSpatialAnchorStoreMSFT xrClearSpatialAnchorStoreMSFT;
extern PFN_xrCreateSpatialAnchorFromPersistedNameMSFT xrCreateSpatialAnchorFromPersistedNameMSFT;
extern PFN_xrCreateSpatialAnchorStoreConnectionMSFT xrCreateSpatialAnchorStoreConnectionMSFT;
extern PFN_xrDestroySpatialAnchorStoreConnectionMSFT xrDestroySpatialAnchorStoreConnectionMSFT;
extern PFN_xrEnumeratePersistedSpatialAnchorNamesMSFT xrEnumeratePersistedSpatialAnchorNamesMSFT;
extern PFN_xrPersistSpatialAnchorMSFT xrPersistSpatialAnchorMSFT;
extern PFN_xrUnpersistSpatialAnchorMSFT xrUnpersistSpatialAnchorMSFT;
#endif /*  defined(XR_MSFT_spatial_anchor_persistence)   */
#if defined(XR_MSFT_spatial_graph_bridge)
extern PFN_xrCreateSpatialGraphNodeSpaceMSFT xrCreateSpatialGraphNodeSpaceMSFT;
extern PFN_xrDestroySpatialGraphNodeBindingMSFT xrDestroySpatialGraphNodeBindingMSFT;
extern PFN_xrGetSpatialGraphNodeBindingPropertiesMSFT xrGetSpatialGraphNodeBindingPropertiesMSFT;
extern PFN_xrTryCreateSpatialGraphStaticNodeBindingMSFT xrTryCreateSpatialGraphStaticNodeBindingMSFT;
#endif /*  defined(XR_MSFT_spatial_graph_bridge)   */
#if defined(XR_OCULUS_audio_device_guid)
extern PFN_xrGetAudioInputDeviceGuidOculus xrGetAudioInputDeviceGuidOculus;
extern PFN_xrGetAudioOutputDeviceGuidOculus xrGetAudioOutputDeviceGuidOculus;
#endif /*  defined(XR_OCULUS_audio_device_guid)   */
#if defined(XR_OCULUS_external_camera)
extern PFN_xrEnumerateExternalCamerasOCULUS xrEnumerateExternalCamerasOCULUS;
#endif /*  defined(XR_OCULUS_external_camera)   */
#if defined(XR_QCOM_tracking_optimization_settings)
extern PFN_xrSetTrackingOptimizationSettingsHintQCOM xrSetTrackingOptimizationSettingsHintQCOM;
#endif /*  defined(XR_QCOM_tracking_optimization_settings)   */
#if defined(XR_VARJO_environment_depth_estimation)
extern PFN_xrSetEnvironmentDepthEstimationVARJO xrSetEnvironmentDepthEstimationVARJO;
#endif /*  defined(XR_VARJO_environment_depth_estimation)   */
#if defined(XR_VARJO_marker_tracking)
extern PFN_xrCreateMarkerSpaceVARJO xrCreateMarkerSpaceVARJO;
extern PFN_xrGetMarkerSizeVARJO xrGetMarkerSizeVARJO;
extern PFN_xrSetMarkerTrackingPredictionVARJO xrSetMarkerTrackingPredictionVARJO;
extern PFN_xrSetMarkerTrackingTimeoutVARJO xrSetMarkerTrackingTimeoutVARJO;
extern PFN_xrSetMarkerTrackingVARJO xrSetMarkerTrackingVARJO;
#endif /*  defined(XR_VARJO_marker_tracking)   */
#if defined(XR_VARJO_view_offset)
extern PFN_xrSetViewOffsetVARJO xrSetViewOffsetVARJO;
#endif /*  defined(XR_VARJO_view_offset)   */

#endif

#ifdef __cplusplus
}
#endif

#endif
