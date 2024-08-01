////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   xrmyth.c
//  Version:     v1.00
//  Created:     31/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "xrmyth.h"
#include "../mdos.h"

#ifdef __cplusplus
extern "C"{
#endif

mdsoHandle Libxr = mdsoNullHandle;

static PFN_xrVoidFunction mythXrLoad_loadFunc(XrInstance Instance, const char* Name){
	PFN_xrVoidFunction Func = NULL;
	XrResult XRes = xrGetInstanceProcAddr(Instance, Name, &Func);
	if((Func == NULL) || (XRes != XR_SUCCESS)){
		VWARN("XrLoader", "Could not load Base OpenXR Function {cstr} with error \"{xr}\" instance {ptr}",
				Name, XRes, Instance);
				Func = NULL;

	}

	return Func;

}

bool mythXrLoad(){
	mdsoHandle Handle = mdsoOpen(MYTH_XR_LOAD_DLL, mdsoFlags_localSymbols);
	if(!Handle){
		Handle = mdsoOpen(MYTH_XR_LOAD_DLL, mdsoFlags_localSymbols);

	}

	//TODO(V): Add better search for openxr_loader.so, like search if steam vr is installed and use that copy

	if(!Handle){
		VERRNF("XrLoader", "Could not load OpenXR api");
		return false;

	}

	xrGetInstanceProcAddr = (PFN_xrGetInstanceProcAddr)mdsoGetFunc(Handle, "xrGetInstanceProcAddr");
	Libxr = Handle;
	_mythXrLoadBasic(NULL, &mythXrLoad_loadFunc);

}

static PFN_xrVoidFunction mythXrNullifyInstanceFuncPtr(XrInstance Instance, const char* Name){
	(void)Instance;
	(void)Name;
	return NULL;

}

void mythXrExit(){
	if(Libxr){
		mdsoClose(Libxr);

	}

	xrGetInstanceProcAddr = NULL;
	_mythXrLoadBasic(NULL, &mythXrNullifyInstanceFuncPtr);
	_mythXrLoadInstance(NULL, &mythXrNullifyInstanceFuncPtr);

}

static PFN_xrVoidFunction mythXrLoadInstance_loadFunc(XrInstance Instance, const char* Name){
	PFN_xrVoidFunction Func = NULL;
	XrResult XRes = xrGetInstanceProcAddr(Instance, Name, &Func);
	if((Func == NULL) || (XRes != XR_SUCCESS)){
		VWARN("XrLoader", "Could not load Instance OpenXR Function {cstr} with error \"{xr}\" instance {ptr}",
				Name, XRes, Instance);
				Func = NULL;

	}

	return Func;

}

void mythXrLoadInstance(XrInstance Instance){
	_mythXrLoadInstance(Instance, &mythXrLoadInstance_loadFunc);

}


//SECTION(V): XRMYTH_TOSTR8_IMPL

//SECTION(V): XRMYTH_TOSTR32_IMPL

void _mythXrLoadBasic(XrInstance Instance, loadFuncPtr LoadFunc){

//SECTION(V): XRMYTH_LOAD_BASIC
#if defined(XR_VERSION_1_0)
    xrCreateInstance = (PFN_xrCreateInstance)LoadFunc(Instance, "xrCreateInstance");
    xrEnumerateApiLayerProperties = (PFN_xrEnumerateApiLayerProperties)LoadFunc(Instance, "xrEnumerateApiLayerProperties");
    xrEnumerateInstanceExtensionProperties = (PFN_xrEnumerateInstanceExtensionProperties)LoadFunc(Instance, "xrEnumerateInstanceExtensionProperties");
#endif /*  defined(XR_VERSION_1_0)   */

}

void _mythXrLoadInstance(XrInstance Instance, loadFuncPtr LoadFunc){

//SECTION(V): XRMYTH_LOAD_INSTANCE
#if defined(XR_VERSION_1_0)
    xrAcquireSwapchainImage = (PFN_xrAcquireSwapchainImage)LoadFunc(Instance, "xrAcquireSwapchainImage");
    xrApplyHapticFeedback = (PFN_xrApplyHapticFeedback)LoadFunc(Instance, "xrApplyHapticFeedback");
    xrAttachSessionActionSets = (PFN_xrAttachSessionActionSets)LoadFunc(Instance, "xrAttachSessionActionSets");
    xrBeginFrame = (PFN_xrBeginFrame)LoadFunc(Instance, "xrBeginFrame");
    xrBeginSession = (PFN_xrBeginSession)LoadFunc(Instance, "xrBeginSession");
    xrCreateAction = (PFN_xrCreateAction)LoadFunc(Instance, "xrCreateAction");
    xrCreateActionSet = (PFN_xrCreateActionSet)LoadFunc(Instance, "xrCreateActionSet");
    xrCreateActionSpace = (PFN_xrCreateActionSpace)LoadFunc(Instance, "xrCreateActionSpace");
    xrCreateReferenceSpace = (PFN_xrCreateReferenceSpace)LoadFunc(Instance, "xrCreateReferenceSpace");
    xrCreateSession = (PFN_xrCreateSession)LoadFunc(Instance, "xrCreateSession");
    xrCreateSwapchain = (PFN_xrCreateSwapchain)LoadFunc(Instance, "xrCreateSwapchain");
    xrDestroyAction = (PFN_xrDestroyAction)LoadFunc(Instance, "xrDestroyAction");
    xrDestroyActionSet = (PFN_xrDestroyActionSet)LoadFunc(Instance, "xrDestroyActionSet");
    xrDestroyInstance = (PFN_xrDestroyInstance)LoadFunc(Instance, "xrDestroyInstance");
    xrDestroySession = (PFN_xrDestroySession)LoadFunc(Instance, "xrDestroySession");
    xrDestroySpace = (PFN_xrDestroySpace)LoadFunc(Instance, "xrDestroySpace");
    xrDestroySwapchain = (PFN_xrDestroySwapchain)LoadFunc(Instance, "xrDestroySwapchain");
    xrEndFrame = (PFN_xrEndFrame)LoadFunc(Instance, "xrEndFrame");
    xrEndSession = (PFN_xrEndSession)LoadFunc(Instance, "xrEndSession");
    xrEnumerateBoundSourcesForAction = (PFN_xrEnumerateBoundSourcesForAction)LoadFunc(Instance, "xrEnumerateBoundSourcesForAction");
    xrEnumerateEnvironmentBlendModes = (PFN_xrEnumerateEnvironmentBlendModes)LoadFunc(Instance, "xrEnumerateEnvironmentBlendModes");
    xrEnumerateReferenceSpaces = (PFN_xrEnumerateReferenceSpaces)LoadFunc(Instance, "xrEnumerateReferenceSpaces");
    xrEnumerateSwapchainFormats = (PFN_xrEnumerateSwapchainFormats)LoadFunc(Instance, "xrEnumerateSwapchainFormats");
    xrEnumerateSwapchainImages = (PFN_xrEnumerateSwapchainImages)LoadFunc(Instance, "xrEnumerateSwapchainImages");
    xrEnumerateViewConfigurationViews = (PFN_xrEnumerateViewConfigurationViews)LoadFunc(Instance, "xrEnumerateViewConfigurationViews");
    xrEnumerateViewConfigurations = (PFN_xrEnumerateViewConfigurations)LoadFunc(Instance, "xrEnumerateViewConfigurations");
    xrGetActionStateBoolean = (PFN_xrGetActionStateBoolean)LoadFunc(Instance, "xrGetActionStateBoolean");
    xrGetActionStateFloat = (PFN_xrGetActionStateFloat)LoadFunc(Instance, "xrGetActionStateFloat");
    xrGetActionStatePose = (PFN_xrGetActionStatePose)LoadFunc(Instance, "xrGetActionStatePose");
    xrGetActionStateVector2f = (PFN_xrGetActionStateVector2f)LoadFunc(Instance, "xrGetActionStateVector2f");
    xrGetCurrentInteractionProfile = (PFN_xrGetCurrentInteractionProfile)LoadFunc(Instance, "xrGetCurrentInteractionProfile");
    xrGetInputSourceLocalizedName = (PFN_xrGetInputSourceLocalizedName)LoadFunc(Instance, "xrGetInputSourceLocalizedName");
    xrGetInstanceProperties = (PFN_xrGetInstanceProperties)LoadFunc(Instance, "xrGetInstanceProperties");
    xrGetReferenceSpaceBoundsRect = (PFN_xrGetReferenceSpaceBoundsRect)LoadFunc(Instance, "xrGetReferenceSpaceBoundsRect");
    xrGetSystem = (PFN_xrGetSystem)LoadFunc(Instance, "xrGetSystem");
    xrGetSystemProperties = (PFN_xrGetSystemProperties)LoadFunc(Instance, "xrGetSystemProperties");
    xrGetViewConfigurationProperties = (PFN_xrGetViewConfigurationProperties)LoadFunc(Instance, "xrGetViewConfigurationProperties");
    xrLocateSpace = (PFN_xrLocateSpace)LoadFunc(Instance, "xrLocateSpace");
    xrLocateViews = (PFN_xrLocateViews)LoadFunc(Instance, "xrLocateViews");
    xrPathToString = (PFN_xrPathToString)LoadFunc(Instance, "xrPathToString");
    xrPollEvent = (PFN_xrPollEvent)LoadFunc(Instance, "xrPollEvent");
    xrReleaseSwapchainImage = (PFN_xrReleaseSwapchainImage)LoadFunc(Instance, "xrReleaseSwapchainImage");
    xrRequestExitSession = (PFN_xrRequestExitSession)LoadFunc(Instance, "xrRequestExitSession");
    xrResultToString = (PFN_xrResultToString)LoadFunc(Instance, "xrResultToString");
    xrStopHapticFeedback = (PFN_xrStopHapticFeedback)LoadFunc(Instance, "xrStopHapticFeedback");
    xrStringToPath = (PFN_xrStringToPath)LoadFunc(Instance, "xrStringToPath");
    xrStructureTypeToString = (PFN_xrStructureTypeToString)LoadFunc(Instance, "xrStructureTypeToString");
    xrSuggestInteractionProfileBindings = (PFN_xrSuggestInteractionProfileBindings)LoadFunc(Instance, "xrSuggestInteractionProfileBindings");
    xrSyncActions = (PFN_xrSyncActions)LoadFunc(Instance, "xrSyncActions");
    xrWaitFrame = (PFN_xrWaitFrame)LoadFunc(Instance, "xrWaitFrame");
    xrWaitSwapchainImage = (PFN_xrWaitSwapchainImage)LoadFunc(Instance, "xrWaitSwapchainImage");
#endif /*  defined(XR_VERSION_1_0)   */
#if defined(XR_LOADER_VERSION_1_0)
    xrCreateApiLayerInstance = (PFN_xrCreateApiLayerInstance)LoadFunc(Instance, "xrCreateApiLayerInstance");
    xrNegotiateLoaderApiLayerInterface = (PFN_xrNegotiateLoaderApiLayerInterface)LoadFunc(Instance, "xrNegotiateLoaderApiLayerInterface");
    xrNegotiateLoaderRuntimeInterface = (PFN_xrNegotiateLoaderRuntimeInterface)LoadFunc(Instance, "xrNegotiateLoaderRuntimeInterface");
#endif /*  defined(XR_LOADER_VERSION_1_0)   */
#if defined(XR_VERSION_1_1)
    xrLocateSpaces = (PFN_xrLocateSpaces)LoadFunc(Instance, "xrLocateSpaces");
#endif /*  defined(XR_VERSION_1_1)   */
#if defined(XR_ALMALENCE_digital_lens_control)
    xrSetDigitalLensControlALMALENCE = (PFN_xrSetDigitalLensControlALMALENCE)LoadFunc(Instance, "xrSetDigitalLensControlALMALENCE");
#endif /*  defined(XR_ALMALENCE_digital_lens_control)   */
#if defined(XR_EXT_conformance_automation)
    xrSetInputDeviceActiveEXT = (PFN_xrSetInputDeviceActiveEXT)LoadFunc(Instance, "xrSetInputDeviceActiveEXT");
    xrSetInputDeviceLocationEXT = (PFN_xrSetInputDeviceLocationEXT)LoadFunc(Instance, "xrSetInputDeviceLocationEXT");
    xrSetInputDeviceStateBoolEXT = (PFN_xrSetInputDeviceStateBoolEXT)LoadFunc(Instance, "xrSetInputDeviceStateBoolEXT");
    xrSetInputDeviceStateFloatEXT = (PFN_xrSetInputDeviceStateFloatEXT)LoadFunc(Instance, "xrSetInputDeviceStateFloatEXT");
    xrSetInputDeviceStateVector2fEXT = (PFN_xrSetInputDeviceStateVector2fEXT)LoadFunc(Instance, "xrSetInputDeviceStateVector2fEXT");
#endif /*  defined(XR_EXT_conformance_automation)   */
#if defined(XR_EXT_debug_utils)
    xrCreateDebugUtilsMessengerEXT = (PFN_xrCreateDebugUtilsMessengerEXT)LoadFunc(Instance, "xrCreateDebugUtilsMessengerEXT");
    xrDestroyDebugUtilsMessengerEXT = (PFN_xrDestroyDebugUtilsMessengerEXT)LoadFunc(Instance, "xrDestroyDebugUtilsMessengerEXT");
    xrSessionBeginDebugUtilsLabelRegionEXT = (PFN_xrSessionBeginDebugUtilsLabelRegionEXT)LoadFunc(Instance, "xrSessionBeginDebugUtilsLabelRegionEXT");
    xrSessionEndDebugUtilsLabelRegionEXT = (PFN_xrSessionEndDebugUtilsLabelRegionEXT)LoadFunc(Instance, "xrSessionEndDebugUtilsLabelRegionEXT");
    xrSessionInsertDebugUtilsLabelEXT = (PFN_xrSessionInsertDebugUtilsLabelEXT)LoadFunc(Instance, "xrSessionInsertDebugUtilsLabelEXT");
    xrSetDebugUtilsObjectNameEXT = (PFN_xrSetDebugUtilsObjectNameEXT)LoadFunc(Instance, "xrSetDebugUtilsObjectNameEXT");
    xrSubmitDebugUtilsMessageEXT = (PFN_xrSubmitDebugUtilsMessageEXT)LoadFunc(Instance, "xrSubmitDebugUtilsMessageEXT");
#endif /*  defined(XR_EXT_debug_utils)   */
#if defined(XR_EXT_future)
    xrCancelFutureEXT = (PFN_xrCancelFutureEXT)LoadFunc(Instance, "xrCancelFutureEXT");
    xrPollFutureEXT = (PFN_xrPollFutureEXT)LoadFunc(Instance, "xrPollFutureEXT");
#endif /*  defined(XR_EXT_future)   */
#if defined(XR_EXT_hand_tracking)
    xrCreateHandTrackerEXT = (PFN_xrCreateHandTrackerEXT)LoadFunc(Instance, "xrCreateHandTrackerEXT");
    xrDestroyHandTrackerEXT = (PFN_xrDestroyHandTrackerEXT)LoadFunc(Instance, "xrDestroyHandTrackerEXT");
    xrLocateHandJointsEXT = (PFN_xrLocateHandJointsEXT)LoadFunc(Instance, "xrLocateHandJointsEXT");
#endif /*  defined(XR_EXT_hand_tracking)   */
#if defined(XR_EXT_performance_settings)
    xrPerfSettingsSetPerformanceLevelEXT = (PFN_xrPerfSettingsSetPerformanceLevelEXT)LoadFunc(Instance, "xrPerfSettingsSetPerformanceLevelEXT");
#endif /*  defined(XR_EXT_performance_settings)   */
#if defined(XR_EXT_plane_detection)
    xrBeginPlaneDetectionEXT = (PFN_xrBeginPlaneDetectionEXT)LoadFunc(Instance, "xrBeginPlaneDetectionEXT");
    xrCreatePlaneDetectorEXT = (PFN_xrCreatePlaneDetectorEXT)LoadFunc(Instance, "xrCreatePlaneDetectorEXT");
    xrDestroyPlaneDetectorEXT = (PFN_xrDestroyPlaneDetectorEXT)LoadFunc(Instance, "xrDestroyPlaneDetectorEXT");
    xrGetPlaneDetectionStateEXT = (PFN_xrGetPlaneDetectionStateEXT)LoadFunc(Instance, "xrGetPlaneDetectionStateEXT");
    xrGetPlaneDetectionsEXT = (PFN_xrGetPlaneDetectionsEXT)LoadFunc(Instance, "xrGetPlaneDetectionsEXT");
    xrGetPlanePolygonBufferEXT = (PFN_xrGetPlanePolygonBufferEXT)LoadFunc(Instance, "xrGetPlanePolygonBufferEXT");
#endif /*  defined(XR_EXT_plane_detection)   */
#if defined(XR_EXT_thermal_query)
    xrThermalGetTemperatureTrendEXT = (PFN_xrThermalGetTemperatureTrendEXT)LoadFunc(Instance, "xrThermalGetTemperatureTrendEXT");
#endif /*  defined(XR_EXT_thermal_query)   */
#if defined(XR_FB_body_tracking)
    xrCreateBodyTrackerFB = (PFN_xrCreateBodyTrackerFB)LoadFunc(Instance, "xrCreateBodyTrackerFB");
    xrDestroyBodyTrackerFB = (PFN_xrDestroyBodyTrackerFB)LoadFunc(Instance, "xrDestroyBodyTrackerFB");
    xrGetBodySkeletonFB = (PFN_xrGetBodySkeletonFB)LoadFunc(Instance, "xrGetBodySkeletonFB");
    xrLocateBodyJointsFB = (PFN_xrLocateBodyJointsFB)LoadFunc(Instance, "xrLocateBodyJointsFB");
#endif /*  defined(XR_FB_body_tracking)   */
#if defined(XR_FB_color_space)
    xrEnumerateColorSpacesFB = (PFN_xrEnumerateColorSpacesFB)LoadFunc(Instance, "xrEnumerateColorSpacesFB");
    xrSetColorSpaceFB = (PFN_xrSetColorSpaceFB)LoadFunc(Instance, "xrSetColorSpaceFB");
#endif /*  defined(XR_FB_color_space)   */
#if defined(XR_FB_display_refresh_rate)
    xrEnumerateDisplayRefreshRatesFB = (PFN_xrEnumerateDisplayRefreshRatesFB)LoadFunc(Instance, "xrEnumerateDisplayRefreshRatesFB");
    xrGetDisplayRefreshRateFB = (PFN_xrGetDisplayRefreshRateFB)LoadFunc(Instance, "xrGetDisplayRefreshRateFB");
    xrRequestDisplayRefreshRateFB = (PFN_xrRequestDisplayRefreshRateFB)LoadFunc(Instance, "xrRequestDisplayRefreshRateFB");
#endif /*  defined(XR_FB_display_refresh_rate)   */
#if defined(XR_FB_eye_tracking_social)
    xrCreateEyeTrackerFB = (PFN_xrCreateEyeTrackerFB)LoadFunc(Instance, "xrCreateEyeTrackerFB");
    xrDestroyEyeTrackerFB = (PFN_xrDestroyEyeTrackerFB)LoadFunc(Instance, "xrDestroyEyeTrackerFB");
    xrGetEyeGazesFB = (PFN_xrGetEyeGazesFB)LoadFunc(Instance, "xrGetEyeGazesFB");
#endif /*  defined(XR_FB_eye_tracking_social)   */
#if defined(XR_FB_face_tracking)
    xrCreateFaceTrackerFB = (PFN_xrCreateFaceTrackerFB)LoadFunc(Instance, "xrCreateFaceTrackerFB");
    xrDestroyFaceTrackerFB = (PFN_xrDestroyFaceTrackerFB)LoadFunc(Instance, "xrDestroyFaceTrackerFB");
    xrGetFaceExpressionWeightsFB = (PFN_xrGetFaceExpressionWeightsFB)LoadFunc(Instance, "xrGetFaceExpressionWeightsFB");
#endif /*  defined(XR_FB_face_tracking)   */
#if defined(XR_FB_face_tracking2)
    xrCreateFaceTracker2FB = (PFN_xrCreateFaceTracker2FB)LoadFunc(Instance, "xrCreateFaceTracker2FB");
    xrDestroyFaceTracker2FB = (PFN_xrDestroyFaceTracker2FB)LoadFunc(Instance, "xrDestroyFaceTracker2FB");
    xrGetFaceExpressionWeights2FB = (PFN_xrGetFaceExpressionWeights2FB)LoadFunc(Instance, "xrGetFaceExpressionWeights2FB");
#endif /*  defined(XR_FB_face_tracking2)   */
#if defined(XR_FB_foveation)
    xrCreateFoveationProfileFB = (PFN_xrCreateFoveationProfileFB)LoadFunc(Instance, "xrCreateFoveationProfileFB");
    xrDestroyFoveationProfileFB = (PFN_xrDestroyFoveationProfileFB)LoadFunc(Instance, "xrDestroyFoveationProfileFB");
#endif /*  defined(XR_FB_foveation)   */
#if defined(XR_FB_hand_tracking_mesh)
    xrGetHandMeshFB = (PFN_xrGetHandMeshFB)LoadFunc(Instance, "xrGetHandMeshFB");
#endif /*  defined(XR_FB_hand_tracking_mesh)   */
#if defined(XR_FB_haptic_pcm)
    xrGetDeviceSampleRateFB = (PFN_xrGetDeviceSampleRateFB)LoadFunc(Instance, "xrGetDeviceSampleRateFB");
#endif /*  defined(XR_FB_haptic_pcm)   */
#if defined(XR_FB_keyboard_tracking)
    xrCreateKeyboardSpaceFB = (PFN_xrCreateKeyboardSpaceFB)LoadFunc(Instance, "xrCreateKeyboardSpaceFB");
    xrQuerySystemTrackedKeyboardFB = (PFN_xrQuerySystemTrackedKeyboardFB)LoadFunc(Instance, "xrQuerySystemTrackedKeyboardFB");
#endif /*  defined(XR_FB_keyboard_tracking)   */
#if defined(XR_FB_passthrough)
    xrCreateGeometryInstanceFB = (PFN_xrCreateGeometryInstanceFB)LoadFunc(Instance, "xrCreateGeometryInstanceFB");
    xrCreatePassthroughFB = (PFN_xrCreatePassthroughFB)LoadFunc(Instance, "xrCreatePassthroughFB");
    xrCreatePassthroughLayerFB = (PFN_xrCreatePassthroughLayerFB)LoadFunc(Instance, "xrCreatePassthroughLayerFB");
    xrDestroyGeometryInstanceFB = (PFN_xrDestroyGeometryInstanceFB)LoadFunc(Instance, "xrDestroyGeometryInstanceFB");
    xrDestroyPassthroughFB = (PFN_xrDestroyPassthroughFB)LoadFunc(Instance, "xrDestroyPassthroughFB");
    xrDestroyPassthroughLayerFB = (PFN_xrDestroyPassthroughLayerFB)LoadFunc(Instance, "xrDestroyPassthroughLayerFB");
    xrGeometryInstanceSetTransformFB = (PFN_xrGeometryInstanceSetTransformFB)LoadFunc(Instance, "xrGeometryInstanceSetTransformFB");
    xrPassthroughLayerPauseFB = (PFN_xrPassthroughLayerPauseFB)LoadFunc(Instance, "xrPassthroughLayerPauseFB");
    xrPassthroughLayerResumeFB = (PFN_xrPassthroughLayerResumeFB)LoadFunc(Instance, "xrPassthroughLayerResumeFB");
    xrPassthroughLayerSetStyleFB = (PFN_xrPassthroughLayerSetStyleFB)LoadFunc(Instance, "xrPassthroughLayerSetStyleFB");
    xrPassthroughPauseFB = (PFN_xrPassthroughPauseFB)LoadFunc(Instance, "xrPassthroughPauseFB");
    xrPassthroughStartFB = (PFN_xrPassthroughStartFB)LoadFunc(Instance, "xrPassthroughStartFB");
#endif /*  defined(XR_FB_passthrough)   */
#if defined(XR_FB_passthrough_keyboard_hands)
    xrPassthroughLayerSetKeyboardHandsIntensityFB = (PFN_xrPassthroughLayerSetKeyboardHandsIntensityFB)LoadFunc(Instance, "xrPassthroughLayerSetKeyboardHandsIntensityFB");
#endif /*  defined(XR_FB_passthrough_keyboard_hands)   */
#if defined(XR_FB_render_model)
    xrEnumerateRenderModelPathsFB = (PFN_xrEnumerateRenderModelPathsFB)LoadFunc(Instance, "xrEnumerateRenderModelPathsFB");
    xrGetRenderModelPropertiesFB = (PFN_xrGetRenderModelPropertiesFB)LoadFunc(Instance, "xrGetRenderModelPropertiesFB");
    xrLoadRenderModelFB = (PFN_xrLoadRenderModelFB)LoadFunc(Instance, "xrLoadRenderModelFB");
#endif /*  defined(XR_FB_render_model)   */
#if defined(XR_FB_scene)
    xrGetSpaceBoundary2DFB = (PFN_xrGetSpaceBoundary2DFB)LoadFunc(Instance, "xrGetSpaceBoundary2DFB");
    xrGetSpaceBoundingBox2DFB = (PFN_xrGetSpaceBoundingBox2DFB)LoadFunc(Instance, "xrGetSpaceBoundingBox2DFB");
    xrGetSpaceBoundingBox3DFB = (PFN_xrGetSpaceBoundingBox3DFB)LoadFunc(Instance, "xrGetSpaceBoundingBox3DFB");
    xrGetSpaceRoomLayoutFB = (PFN_xrGetSpaceRoomLayoutFB)LoadFunc(Instance, "xrGetSpaceRoomLayoutFB");
    xrGetSpaceSemanticLabelsFB = (PFN_xrGetSpaceSemanticLabelsFB)LoadFunc(Instance, "xrGetSpaceSemanticLabelsFB");
#endif /*  defined(XR_FB_scene)   */
#if defined(XR_FB_scene_capture)
    xrRequestSceneCaptureFB = (PFN_xrRequestSceneCaptureFB)LoadFunc(Instance, "xrRequestSceneCaptureFB");
#endif /*  defined(XR_FB_scene_capture)   */
#if defined(XR_FB_spatial_entity)
    xrCreateSpatialAnchorFB = (PFN_xrCreateSpatialAnchorFB)LoadFunc(Instance, "xrCreateSpatialAnchorFB");
    xrEnumerateSpaceSupportedComponentsFB = (PFN_xrEnumerateSpaceSupportedComponentsFB)LoadFunc(Instance, "xrEnumerateSpaceSupportedComponentsFB");
    xrGetSpaceComponentStatusFB = (PFN_xrGetSpaceComponentStatusFB)LoadFunc(Instance, "xrGetSpaceComponentStatusFB");
    xrGetSpaceUuidFB = (PFN_xrGetSpaceUuidFB)LoadFunc(Instance, "xrGetSpaceUuidFB");
    xrSetSpaceComponentStatusFB = (PFN_xrSetSpaceComponentStatusFB)LoadFunc(Instance, "xrSetSpaceComponentStatusFB");
#endif /*  defined(XR_FB_spatial_entity)   */
#if defined(XR_FB_spatial_entity_container)
    xrGetSpaceContainerFB = (PFN_xrGetSpaceContainerFB)LoadFunc(Instance, "xrGetSpaceContainerFB");
#endif /*  defined(XR_FB_spatial_entity_container)   */
#if defined(XR_FB_spatial_entity_query)
    xrQuerySpacesFB = (PFN_xrQuerySpacesFB)LoadFunc(Instance, "xrQuerySpacesFB");
    xrRetrieveSpaceQueryResultsFB = (PFN_xrRetrieveSpaceQueryResultsFB)LoadFunc(Instance, "xrRetrieveSpaceQueryResultsFB");
#endif /*  defined(XR_FB_spatial_entity_query)   */
#if defined(XR_FB_spatial_entity_sharing)
    xrShareSpacesFB = (PFN_xrShareSpacesFB)LoadFunc(Instance, "xrShareSpacesFB");
#endif /*  defined(XR_FB_spatial_entity_sharing)   */
#if defined(XR_FB_spatial_entity_storage)
    xrEraseSpaceFB = (PFN_xrEraseSpaceFB)LoadFunc(Instance, "xrEraseSpaceFB");
    xrSaveSpaceFB = (PFN_xrSaveSpaceFB)LoadFunc(Instance, "xrSaveSpaceFB");
#endif /*  defined(XR_FB_spatial_entity_storage)   */
#if defined(XR_FB_spatial_entity_storage_batch)
    xrSaveSpaceListFB = (PFN_xrSaveSpaceListFB)LoadFunc(Instance, "xrSaveSpaceListFB");
#endif /*  defined(XR_FB_spatial_entity_storage_batch)   */
#if defined(XR_FB_spatial_entity_user)
    xrCreateSpaceUserFB = (PFN_xrCreateSpaceUserFB)LoadFunc(Instance, "xrCreateSpaceUserFB");
    xrDestroySpaceUserFB = (PFN_xrDestroySpaceUserFB)LoadFunc(Instance, "xrDestroySpaceUserFB");
    xrGetSpaceUserIdFB = (PFN_xrGetSpaceUserIdFB)LoadFunc(Instance, "xrGetSpaceUserIdFB");
#endif /*  defined(XR_FB_spatial_entity_user)   */
#if defined(XR_FB_swapchain_update_state)
    xrGetSwapchainStateFB = (PFN_xrGetSwapchainStateFB)LoadFunc(Instance, "xrGetSwapchainStateFB");
    xrUpdateSwapchainFB = (PFN_xrUpdateSwapchainFB)LoadFunc(Instance, "xrUpdateSwapchainFB");
#endif /*  defined(XR_FB_swapchain_update_state)   */
#if defined(XR_FB_triangle_mesh)
    xrCreateTriangleMeshFB = (PFN_xrCreateTriangleMeshFB)LoadFunc(Instance, "xrCreateTriangleMeshFB");
    xrDestroyTriangleMeshFB = (PFN_xrDestroyTriangleMeshFB)LoadFunc(Instance, "xrDestroyTriangleMeshFB");
    xrTriangleMeshBeginUpdateFB = (PFN_xrTriangleMeshBeginUpdateFB)LoadFunc(Instance, "xrTriangleMeshBeginUpdateFB");
    xrTriangleMeshBeginVertexBufferUpdateFB = (PFN_xrTriangleMeshBeginVertexBufferUpdateFB)LoadFunc(Instance, "xrTriangleMeshBeginVertexBufferUpdateFB");
    xrTriangleMeshEndUpdateFB = (PFN_xrTriangleMeshEndUpdateFB)LoadFunc(Instance, "xrTriangleMeshEndUpdateFB");
    xrTriangleMeshEndVertexBufferUpdateFB = (PFN_xrTriangleMeshEndVertexBufferUpdateFB)LoadFunc(Instance, "xrTriangleMeshEndVertexBufferUpdateFB");
    xrTriangleMeshGetIndexBufferFB = (PFN_xrTriangleMeshGetIndexBufferFB)LoadFunc(Instance, "xrTriangleMeshGetIndexBufferFB");
    xrTriangleMeshGetVertexBufferFB = (PFN_xrTriangleMeshGetVertexBufferFB)LoadFunc(Instance, "xrTriangleMeshGetVertexBufferFB");
#endif /*  defined(XR_FB_triangle_mesh)   */
#if defined(XR_HTCX_vive_tracker_interaction)
    xrEnumerateViveTrackerPathsHTCX = (PFN_xrEnumerateViveTrackerPathsHTCX)LoadFunc(Instance, "xrEnumerateViveTrackerPathsHTCX");
#endif /*  defined(XR_HTCX_vive_tracker_interaction)   */
#if defined(XR_HTC_anchor)
    xrCreateSpatialAnchorHTC = (PFN_xrCreateSpatialAnchorHTC)LoadFunc(Instance, "xrCreateSpatialAnchorHTC");
    xrGetSpatialAnchorNameHTC = (PFN_xrGetSpatialAnchorNameHTC)LoadFunc(Instance, "xrGetSpatialAnchorNameHTC");
#endif /*  defined(XR_HTC_anchor)   */
#if defined(XR_HTC_facial_tracking)
    xrCreateFacialTrackerHTC = (PFN_xrCreateFacialTrackerHTC)LoadFunc(Instance, "xrCreateFacialTrackerHTC");
    xrDestroyFacialTrackerHTC = (PFN_xrDestroyFacialTrackerHTC)LoadFunc(Instance, "xrDestroyFacialTrackerHTC");
    xrGetFacialExpressionsHTC = (PFN_xrGetFacialExpressionsHTC)LoadFunc(Instance, "xrGetFacialExpressionsHTC");
#endif /*  defined(XR_HTC_facial_tracking)   */
#if defined(XR_HTC_foveation)
    xrApplyFoveationHTC = (PFN_xrApplyFoveationHTC)LoadFunc(Instance, "xrApplyFoveationHTC");
#endif /*  defined(XR_HTC_foveation)   */
#if defined(XR_HTC_passthrough)
    xrCreatePassthroughHTC = (PFN_xrCreatePassthroughHTC)LoadFunc(Instance, "xrCreatePassthroughHTC");
    xrDestroyPassthroughHTC = (PFN_xrDestroyPassthroughHTC)LoadFunc(Instance, "xrDestroyPassthroughHTC");
#endif /*  defined(XR_HTC_passthrough)   */
#if defined(XR_KHR_D3D11_enable)
    xrGetD3D11GraphicsRequirementsKHR = (PFN_xrGetD3D11GraphicsRequirementsKHR)LoadFunc(Instance, "xrGetD3D11GraphicsRequirementsKHR");
#endif /*  defined(XR_KHR_D3D11_enable)   */
#if defined(XR_KHR_D3D12_enable)
    xrGetD3D12GraphicsRequirementsKHR = (PFN_xrGetD3D12GraphicsRequirementsKHR)LoadFunc(Instance, "xrGetD3D12GraphicsRequirementsKHR");
#endif /*  defined(XR_KHR_D3D12_enable)   */
#if defined(XR_KHR_android_surface_swapchain)
    xrCreateSwapchainAndroidSurfaceKHR = (PFN_xrCreateSwapchainAndroidSurfaceKHR)LoadFunc(Instance, "xrCreateSwapchainAndroidSurfaceKHR");
#endif /*  defined(XR_KHR_android_surface_swapchain)   */
#if defined(XR_KHR_android_thread_settings)
    xrSetAndroidApplicationThreadKHR = (PFN_xrSetAndroidApplicationThreadKHR)LoadFunc(Instance, "xrSetAndroidApplicationThreadKHR");
#endif /*  defined(XR_KHR_android_thread_settings)   */
#if defined(XR_KHR_convert_timespec_time)
    xrConvertTimeToTimespecTimeKHR = (PFN_xrConvertTimeToTimespecTimeKHR)LoadFunc(Instance, "xrConvertTimeToTimespecTimeKHR");
    xrConvertTimespecTimeToTimeKHR = (PFN_xrConvertTimespecTimeToTimeKHR)LoadFunc(Instance, "xrConvertTimespecTimeToTimeKHR");
#endif /*  defined(XR_KHR_convert_timespec_time)   */
#if defined(XR_KHR_loader_init)
    xrInitializeLoaderKHR = (PFN_xrInitializeLoaderKHR)LoadFunc(Instance, "xrInitializeLoaderKHR");
#endif /*  defined(XR_KHR_loader_init)   */
#if defined(XR_KHR_locate_spaces)
    xrLocateSpacesKHR = (PFN_xrLocateSpacesKHR)LoadFunc(Instance, "xrLocateSpacesKHR");
#endif /*  defined(XR_KHR_locate_spaces)   */
#if defined(XR_KHR_opengl_enable)
    xrGetOpenGLGraphicsRequirementsKHR = (PFN_xrGetOpenGLGraphicsRequirementsKHR)LoadFunc(Instance, "xrGetOpenGLGraphicsRequirementsKHR");
#endif /*  defined(XR_KHR_opengl_enable)   */
#if defined(XR_KHR_opengl_es_enable)
    xrGetOpenGLESGraphicsRequirementsKHR = (PFN_xrGetOpenGLESGraphicsRequirementsKHR)LoadFunc(Instance, "xrGetOpenGLESGraphicsRequirementsKHR");
#endif /*  defined(XR_KHR_opengl_es_enable)   */
#if defined(XR_KHR_visibility_mask)
    xrGetVisibilityMaskKHR = (PFN_xrGetVisibilityMaskKHR)LoadFunc(Instance, "xrGetVisibilityMaskKHR");
#endif /*  defined(XR_KHR_visibility_mask)   */
#if defined(XR_KHR_vulkan_enable)
    xrGetVulkanDeviceExtensionsKHR = (PFN_xrGetVulkanDeviceExtensionsKHR)LoadFunc(Instance, "xrGetVulkanDeviceExtensionsKHR");
    xrGetVulkanGraphicsDeviceKHR = (PFN_xrGetVulkanGraphicsDeviceKHR)LoadFunc(Instance, "xrGetVulkanGraphicsDeviceKHR");
    xrGetVulkanGraphicsRequirementsKHR = (PFN_xrGetVulkanGraphicsRequirementsKHR)LoadFunc(Instance, "xrGetVulkanGraphicsRequirementsKHR");
    xrGetVulkanInstanceExtensionsKHR = (PFN_xrGetVulkanInstanceExtensionsKHR)LoadFunc(Instance, "xrGetVulkanInstanceExtensionsKHR");
#endif /*  defined(XR_KHR_vulkan_enable)   */
#if defined(XR_KHR_vulkan_enable2)
    xrCreateVulkanDeviceKHR = (PFN_xrCreateVulkanDeviceKHR)LoadFunc(Instance, "xrCreateVulkanDeviceKHR");
    xrCreateVulkanInstanceKHR = (PFN_xrCreateVulkanInstanceKHR)LoadFunc(Instance, "xrCreateVulkanInstanceKHR");
    xrGetVulkanGraphicsDevice2KHR = (PFN_xrGetVulkanGraphicsDevice2KHR)LoadFunc(Instance, "xrGetVulkanGraphicsDevice2KHR");
    xrGetVulkanGraphicsRequirements2KHR = (PFN_xrGetVulkanGraphicsRequirements2KHR)LoadFunc(Instance, "xrGetVulkanGraphicsRequirements2KHR");
#endif /*  defined(XR_KHR_vulkan_enable2)   */
#if defined(XR_KHR_win32_convert_performance_counter_time)
    xrConvertTimeToWin32PerformanceCounterKHR = (PFN_xrConvertTimeToWin32PerformanceCounterKHR)LoadFunc(Instance, "xrConvertTimeToWin32PerformanceCounterKHR");
    xrConvertWin32PerformanceCounterToTimeKHR = (PFN_xrConvertWin32PerformanceCounterToTimeKHR)LoadFunc(Instance, "xrConvertWin32PerformanceCounterToTimeKHR");
#endif /*  defined(XR_KHR_win32_convert_performance_counter_time)   */
#if defined(XR_META_environment_depth)
    xrAcquireEnvironmentDepthImageMETA = (PFN_xrAcquireEnvironmentDepthImageMETA)LoadFunc(Instance, "xrAcquireEnvironmentDepthImageMETA");
    xrCreateEnvironmentDepthProviderMETA = (PFN_xrCreateEnvironmentDepthProviderMETA)LoadFunc(Instance, "xrCreateEnvironmentDepthProviderMETA");
    xrCreateEnvironmentDepthSwapchainMETA = (PFN_xrCreateEnvironmentDepthSwapchainMETA)LoadFunc(Instance, "xrCreateEnvironmentDepthSwapchainMETA");
    xrDestroyEnvironmentDepthProviderMETA = (PFN_xrDestroyEnvironmentDepthProviderMETA)LoadFunc(Instance, "xrDestroyEnvironmentDepthProviderMETA");
    xrDestroyEnvironmentDepthSwapchainMETA = (PFN_xrDestroyEnvironmentDepthSwapchainMETA)LoadFunc(Instance, "xrDestroyEnvironmentDepthSwapchainMETA");
    xrEnumerateEnvironmentDepthSwapchainImagesMETA = (PFN_xrEnumerateEnvironmentDepthSwapchainImagesMETA)LoadFunc(Instance, "xrEnumerateEnvironmentDepthSwapchainImagesMETA");
    xrGetEnvironmentDepthSwapchainStateMETA = (PFN_xrGetEnvironmentDepthSwapchainStateMETA)LoadFunc(Instance, "xrGetEnvironmentDepthSwapchainStateMETA");
    xrSetEnvironmentDepthHandRemovalMETA = (PFN_xrSetEnvironmentDepthHandRemovalMETA)LoadFunc(Instance, "xrSetEnvironmentDepthHandRemovalMETA");
    xrStartEnvironmentDepthProviderMETA = (PFN_xrStartEnvironmentDepthProviderMETA)LoadFunc(Instance, "xrStartEnvironmentDepthProviderMETA");
    xrStopEnvironmentDepthProviderMETA = (PFN_xrStopEnvironmentDepthProviderMETA)LoadFunc(Instance, "xrStopEnvironmentDepthProviderMETA");
#endif /*  defined(XR_META_environment_depth)   */
#if defined(XR_META_foveation_eye_tracked)
    xrGetFoveationEyeTrackedStateMETA = (PFN_xrGetFoveationEyeTrackedStateMETA)LoadFunc(Instance, "xrGetFoveationEyeTrackedStateMETA");
#endif /*  defined(XR_META_foveation_eye_tracked)   */
#if defined(XR_META_passthrough_color_lut)
    xrCreatePassthroughColorLutMETA = (PFN_xrCreatePassthroughColorLutMETA)LoadFunc(Instance, "xrCreatePassthroughColorLutMETA");
    xrDestroyPassthroughColorLutMETA = (PFN_xrDestroyPassthroughColorLutMETA)LoadFunc(Instance, "xrDestroyPassthroughColorLutMETA");
    xrUpdatePassthroughColorLutMETA = (PFN_xrUpdatePassthroughColorLutMETA)LoadFunc(Instance, "xrUpdatePassthroughColorLutMETA");
#endif /*  defined(XR_META_passthrough_color_lut)   */
#if defined(XR_META_passthrough_preferences)
    xrGetPassthroughPreferencesMETA = (PFN_xrGetPassthroughPreferencesMETA)LoadFunc(Instance, "xrGetPassthroughPreferencesMETA");
#endif /*  defined(XR_META_passthrough_preferences)   */
#if defined(XR_META_performance_metrics)
    xrEnumeratePerformanceMetricsCounterPathsMETA = (PFN_xrEnumeratePerformanceMetricsCounterPathsMETA)LoadFunc(Instance, "xrEnumeratePerformanceMetricsCounterPathsMETA");
    xrGetPerformanceMetricsStateMETA = (PFN_xrGetPerformanceMetricsStateMETA)LoadFunc(Instance, "xrGetPerformanceMetricsStateMETA");
    xrQueryPerformanceMetricsCounterMETA = (PFN_xrQueryPerformanceMetricsCounterMETA)LoadFunc(Instance, "xrQueryPerformanceMetricsCounterMETA");
    xrSetPerformanceMetricsStateMETA = (PFN_xrSetPerformanceMetricsStateMETA)LoadFunc(Instance, "xrSetPerformanceMetricsStateMETA");
#endif /*  defined(XR_META_performance_metrics)   */
#if defined(XR_META_recommended_layer_resolution)
    xrGetRecommendedLayerResolutionMETA = (PFN_xrGetRecommendedLayerResolutionMETA)LoadFunc(Instance, "xrGetRecommendedLayerResolutionMETA");
#endif /*  defined(XR_META_recommended_layer_resolution)   */
#if defined(XR_META_spatial_entity_mesh)
    xrGetSpaceTriangleMeshMETA = (PFN_xrGetSpaceTriangleMeshMETA)LoadFunc(Instance, "xrGetSpaceTriangleMeshMETA");
#endif /*  defined(XR_META_spatial_entity_mesh)   */
#if defined(XR_META_virtual_keyboard)
    xrChangeVirtualKeyboardTextContextMETA = (PFN_xrChangeVirtualKeyboardTextContextMETA)LoadFunc(Instance, "xrChangeVirtualKeyboardTextContextMETA");
    xrCreateVirtualKeyboardMETA = (PFN_xrCreateVirtualKeyboardMETA)LoadFunc(Instance, "xrCreateVirtualKeyboardMETA");
    xrCreateVirtualKeyboardSpaceMETA = (PFN_xrCreateVirtualKeyboardSpaceMETA)LoadFunc(Instance, "xrCreateVirtualKeyboardSpaceMETA");
    xrDestroyVirtualKeyboardMETA = (PFN_xrDestroyVirtualKeyboardMETA)LoadFunc(Instance, "xrDestroyVirtualKeyboardMETA");
    xrGetVirtualKeyboardDirtyTexturesMETA = (PFN_xrGetVirtualKeyboardDirtyTexturesMETA)LoadFunc(Instance, "xrGetVirtualKeyboardDirtyTexturesMETA");
    xrGetVirtualKeyboardModelAnimationStatesMETA = (PFN_xrGetVirtualKeyboardModelAnimationStatesMETA)LoadFunc(Instance, "xrGetVirtualKeyboardModelAnimationStatesMETA");
    xrGetVirtualKeyboardScaleMETA = (PFN_xrGetVirtualKeyboardScaleMETA)LoadFunc(Instance, "xrGetVirtualKeyboardScaleMETA");
    xrGetVirtualKeyboardTextureDataMETA = (PFN_xrGetVirtualKeyboardTextureDataMETA)LoadFunc(Instance, "xrGetVirtualKeyboardTextureDataMETA");
    xrSendVirtualKeyboardInputMETA = (PFN_xrSendVirtualKeyboardInputMETA)LoadFunc(Instance, "xrSendVirtualKeyboardInputMETA");
    xrSetVirtualKeyboardModelVisibilityMETA = (PFN_xrSetVirtualKeyboardModelVisibilityMETA)LoadFunc(Instance, "xrSetVirtualKeyboardModelVisibilityMETA");
    xrSuggestVirtualKeyboardLocationMETA = (PFN_xrSuggestVirtualKeyboardLocationMETA)LoadFunc(Instance, "xrSuggestVirtualKeyboardLocationMETA");
#endif /*  defined(XR_META_virtual_keyboard)   */
#if defined(XR_ML_compat)
    xrCreateSpaceFromCoordinateFrameUIDML = (PFN_xrCreateSpaceFromCoordinateFrameUIDML)LoadFunc(Instance, "xrCreateSpaceFromCoordinateFrameUIDML");
#endif /*  defined(XR_ML_compat)   */
#if defined(XR_ML_localization_map)
    xrCreateExportedLocalizationMapML = (PFN_xrCreateExportedLocalizationMapML)LoadFunc(Instance, "xrCreateExportedLocalizationMapML");
    xrDestroyExportedLocalizationMapML = (PFN_xrDestroyExportedLocalizationMapML)LoadFunc(Instance, "xrDestroyExportedLocalizationMapML");
    xrEnableLocalizationEventsML = (PFN_xrEnableLocalizationEventsML)LoadFunc(Instance, "xrEnableLocalizationEventsML");
    xrGetExportedLocalizationMapDataML = (PFN_xrGetExportedLocalizationMapDataML)LoadFunc(Instance, "xrGetExportedLocalizationMapDataML");
    xrImportLocalizationMapML = (PFN_xrImportLocalizationMapML)LoadFunc(Instance, "xrImportLocalizationMapML");
    xrQueryLocalizationMapsML = (PFN_xrQueryLocalizationMapsML)LoadFunc(Instance, "xrQueryLocalizationMapsML");
    xrRequestMapLocalizationML = (PFN_xrRequestMapLocalizationML)LoadFunc(Instance, "xrRequestMapLocalizationML");
#endif /*  defined(XR_ML_localization_map)   */
#if defined(XR_ML_marker_understanding)
    xrCreateMarkerDetectorML = (PFN_xrCreateMarkerDetectorML)LoadFunc(Instance, "xrCreateMarkerDetectorML");
    xrCreateMarkerSpaceML = (PFN_xrCreateMarkerSpaceML)LoadFunc(Instance, "xrCreateMarkerSpaceML");
    xrDestroyMarkerDetectorML = (PFN_xrDestroyMarkerDetectorML)LoadFunc(Instance, "xrDestroyMarkerDetectorML");
    xrGetMarkerDetectorStateML = (PFN_xrGetMarkerDetectorStateML)LoadFunc(Instance, "xrGetMarkerDetectorStateML");
    xrGetMarkerLengthML = (PFN_xrGetMarkerLengthML)LoadFunc(Instance, "xrGetMarkerLengthML");
    xrGetMarkerNumberML = (PFN_xrGetMarkerNumberML)LoadFunc(Instance, "xrGetMarkerNumberML");
    xrGetMarkerReprojectionErrorML = (PFN_xrGetMarkerReprojectionErrorML)LoadFunc(Instance, "xrGetMarkerReprojectionErrorML");
    xrGetMarkerStringML = (PFN_xrGetMarkerStringML)LoadFunc(Instance, "xrGetMarkerStringML");
    xrGetMarkersML = (PFN_xrGetMarkersML)LoadFunc(Instance, "xrGetMarkersML");
    xrSnapshotMarkerDetectorML = (PFN_xrSnapshotMarkerDetectorML)LoadFunc(Instance, "xrSnapshotMarkerDetectorML");
#endif /*  defined(XR_ML_marker_understanding)   */
#if defined(XR_ML_user_calibration)
    xrEnableUserCalibrationEventsML = (PFN_xrEnableUserCalibrationEventsML)LoadFunc(Instance, "xrEnableUserCalibrationEventsML");
#endif /*  defined(XR_ML_user_calibration)   */
#if defined(XR_MNDX_force_feedback_curl)
    xrApplyForceFeedbackCurlMNDX = (PFN_xrApplyForceFeedbackCurlMNDX)LoadFunc(Instance, "xrApplyForceFeedbackCurlMNDX");
#endif /*  defined(XR_MNDX_force_feedback_curl)   */
#if defined(XR_MSFT_composition_layer_reprojection)
    xrEnumerateReprojectionModesMSFT = (PFN_xrEnumerateReprojectionModesMSFT)LoadFunc(Instance, "xrEnumerateReprojectionModesMSFT");
#endif /*  defined(XR_MSFT_composition_layer_reprojection)   */
#if defined(XR_MSFT_controller_model)
    xrGetControllerModelKeyMSFT = (PFN_xrGetControllerModelKeyMSFT)LoadFunc(Instance, "xrGetControllerModelKeyMSFT");
    xrGetControllerModelPropertiesMSFT = (PFN_xrGetControllerModelPropertiesMSFT)LoadFunc(Instance, "xrGetControllerModelPropertiesMSFT");
    xrGetControllerModelStateMSFT = (PFN_xrGetControllerModelStateMSFT)LoadFunc(Instance, "xrGetControllerModelStateMSFT");
    xrLoadControllerModelMSFT = (PFN_xrLoadControllerModelMSFT)LoadFunc(Instance, "xrLoadControllerModelMSFT");
#endif /*  defined(XR_MSFT_controller_model)   */
#if defined(XR_MSFT_hand_tracking_mesh)
    xrCreateHandMeshSpaceMSFT = (PFN_xrCreateHandMeshSpaceMSFT)LoadFunc(Instance, "xrCreateHandMeshSpaceMSFT");
    xrUpdateHandMeshMSFT = (PFN_xrUpdateHandMeshMSFT)LoadFunc(Instance, "xrUpdateHandMeshMSFT");
#endif /*  defined(XR_MSFT_hand_tracking_mesh)   */
#if defined(XR_MSFT_perception_anchor_interop)
    xrCreateSpatialAnchorFromPerceptionAnchorMSFT = (PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT)LoadFunc(Instance, "xrCreateSpatialAnchorFromPerceptionAnchorMSFT");
    xrTryGetPerceptionAnchorFromSpatialAnchorMSFT = (PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT)LoadFunc(Instance, "xrTryGetPerceptionAnchorFromSpatialAnchorMSFT");
#endif /*  defined(XR_MSFT_perception_anchor_interop)   */
#if defined(XR_MSFT_scene_marker)
    xrGetSceneMarkerDecodedStringMSFT = (PFN_xrGetSceneMarkerDecodedStringMSFT)LoadFunc(Instance, "xrGetSceneMarkerDecodedStringMSFT");
    xrGetSceneMarkerRawDataMSFT = (PFN_xrGetSceneMarkerRawDataMSFT)LoadFunc(Instance, "xrGetSceneMarkerRawDataMSFT");
#endif /*  defined(XR_MSFT_scene_marker)   */
#if defined(XR_MSFT_scene_understanding)
    xrComputeNewSceneMSFT = (PFN_xrComputeNewSceneMSFT)LoadFunc(Instance, "xrComputeNewSceneMSFT");
    xrCreateSceneMSFT = (PFN_xrCreateSceneMSFT)LoadFunc(Instance, "xrCreateSceneMSFT");
    xrCreateSceneObserverMSFT = (PFN_xrCreateSceneObserverMSFT)LoadFunc(Instance, "xrCreateSceneObserverMSFT");
    xrDestroySceneMSFT = (PFN_xrDestroySceneMSFT)LoadFunc(Instance, "xrDestroySceneMSFT");
    xrDestroySceneObserverMSFT = (PFN_xrDestroySceneObserverMSFT)LoadFunc(Instance, "xrDestroySceneObserverMSFT");
    xrEnumerateSceneComputeFeaturesMSFT = (PFN_xrEnumerateSceneComputeFeaturesMSFT)LoadFunc(Instance, "xrEnumerateSceneComputeFeaturesMSFT");
    xrGetSceneComponentsMSFT = (PFN_xrGetSceneComponentsMSFT)LoadFunc(Instance, "xrGetSceneComponentsMSFT");
    xrGetSceneComputeStateMSFT = (PFN_xrGetSceneComputeStateMSFT)LoadFunc(Instance, "xrGetSceneComputeStateMSFT");
    xrGetSceneMeshBuffersMSFT = (PFN_xrGetSceneMeshBuffersMSFT)LoadFunc(Instance, "xrGetSceneMeshBuffersMSFT");
    xrLocateSceneComponentsMSFT = (PFN_xrLocateSceneComponentsMSFT)LoadFunc(Instance, "xrLocateSceneComponentsMSFT");
#endif /*  defined(XR_MSFT_scene_understanding)   */
#if defined(XR_MSFT_scene_understanding_serialization)
    xrDeserializeSceneMSFT = (PFN_xrDeserializeSceneMSFT)LoadFunc(Instance, "xrDeserializeSceneMSFT");
    xrGetSerializedSceneFragmentDataMSFT = (PFN_xrGetSerializedSceneFragmentDataMSFT)LoadFunc(Instance, "xrGetSerializedSceneFragmentDataMSFT");
#endif /*  defined(XR_MSFT_scene_understanding_serialization)   */
#if defined(XR_MSFT_spatial_anchor)
    xrCreateSpatialAnchorMSFT = (PFN_xrCreateSpatialAnchorMSFT)LoadFunc(Instance, "xrCreateSpatialAnchorMSFT");
    xrCreateSpatialAnchorSpaceMSFT = (PFN_xrCreateSpatialAnchorSpaceMSFT)LoadFunc(Instance, "xrCreateSpatialAnchorSpaceMSFT");
    xrDestroySpatialAnchorMSFT = (PFN_xrDestroySpatialAnchorMSFT)LoadFunc(Instance, "xrDestroySpatialAnchorMSFT");
#endif /*  defined(XR_MSFT_spatial_anchor)   */
#if defined(XR_MSFT_spatial_anchor_persistence)
    xrClearSpatialAnchorStoreMSFT = (PFN_xrClearSpatialAnchorStoreMSFT)LoadFunc(Instance, "xrClearSpatialAnchorStoreMSFT");
    xrCreateSpatialAnchorFromPersistedNameMSFT = (PFN_xrCreateSpatialAnchorFromPersistedNameMSFT)LoadFunc(Instance, "xrCreateSpatialAnchorFromPersistedNameMSFT");
    xrCreateSpatialAnchorStoreConnectionMSFT = (PFN_xrCreateSpatialAnchorStoreConnectionMSFT)LoadFunc(Instance, "xrCreateSpatialAnchorStoreConnectionMSFT");
    xrDestroySpatialAnchorStoreConnectionMSFT = (PFN_xrDestroySpatialAnchorStoreConnectionMSFT)LoadFunc(Instance, "xrDestroySpatialAnchorStoreConnectionMSFT");
    xrEnumeratePersistedSpatialAnchorNamesMSFT = (PFN_xrEnumeratePersistedSpatialAnchorNamesMSFT)LoadFunc(Instance, "xrEnumeratePersistedSpatialAnchorNamesMSFT");
    xrPersistSpatialAnchorMSFT = (PFN_xrPersistSpatialAnchorMSFT)LoadFunc(Instance, "xrPersistSpatialAnchorMSFT");
    xrUnpersistSpatialAnchorMSFT = (PFN_xrUnpersistSpatialAnchorMSFT)LoadFunc(Instance, "xrUnpersistSpatialAnchorMSFT");
#endif /*  defined(XR_MSFT_spatial_anchor_persistence)   */
#if defined(XR_MSFT_spatial_graph_bridge)
    xrCreateSpatialGraphNodeSpaceMSFT = (PFN_xrCreateSpatialGraphNodeSpaceMSFT)LoadFunc(Instance, "xrCreateSpatialGraphNodeSpaceMSFT");
    xrDestroySpatialGraphNodeBindingMSFT = (PFN_xrDestroySpatialGraphNodeBindingMSFT)LoadFunc(Instance, "xrDestroySpatialGraphNodeBindingMSFT");
    xrGetSpatialGraphNodeBindingPropertiesMSFT = (PFN_xrGetSpatialGraphNodeBindingPropertiesMSFT)LoadFunc(Instance, "xrGetSpatialGraphNodeBindingPropertiesMSFT");
    xrTryCreateSpatialGraphStaticNodeBindingMSFT = (PFN_xrTryCreateSpatialGraphStaticNodeBindingMSFT)LoadFunc(Instance, "xrTryCreateSpatialGraphStaticNodeBindingMSFT");
#endif /*  defined(XR_MSFT_spatial_graph_bridge)   */
#if defined(XR_OCULUS_audio_device_guid)
    xrGetAudioInputDeviceGuidOculus = (PFN_xrGetAudioInputDeviceGuidOculus)LoadFunc(Instance, "xrGetAudioInputDeviceGuidOculus");
    xrGetAudioOutputDeviceGuidOculus = (PFN_xrGetAudioOutputDeviceGuidOculus)LoadFunc(Instance, "xrGetAudioOutputDeviceGuidOculus");
#endif /*  defined(XR_OCULUS_audio_device_guid)   */
#if defined(XR_OCULUS_external_camera)
    xrEnumerateExternalCamerasOCULUS = (PFN_xrEnumerateExternalCamerasOCULUS)LoadFunc(Instance, "xrEnumerateExternalCamerasOCULUS");
#endif /*  defined(XR_OCULUS_external_camera)   */
#if defined(XR_QCOM_tracking_optimization_settings)
    xrSetTrackingOptimizationSettingsHintQCOM = (PFN_xrSetTrackingOptimizationSettingsHintQCOM)LoadFunc(Instance, "xrSetTrackingOptimizationSettingsHintQCOM");
#endif /*  defined(XR_QCOM_tracking_optimization_settings)   */
#if defined(XR_VARJO_environment_depth_estimation)
    xrSetEnvironmentDepthEstimationVARJO = (PFN_xrSetEnvironmentDepthEstimationVARJO)LoadFunc(Instance, "xrSetEnvironmentDepthEstimationVARJO");
#endif /*  defined(XR_VARJO_environment_depth_estimation)   */
#if defined(XR_VARJO_marker_tracking)
    xrCreateMarkerSpaceVARJO = (PFN_xrCreateMarkerSpaceVARJO)LoadFunc(Instance, "xrCreateMarkerSpaceVARJO");
    xrGetMarkerSizeVARJO = (PFN_xrGetMarkerSizeVARJO)LoadFunc(Instance, "xrGetMarkerSizeVARJO");
    xrSetMarkerTrackingPredictionVARJO = (PFN_xrSetMarkerTrackingPredictionVARJO)LoadFunc(Instance, "xrSetMarkerTrackingPredictionVARJO");
    xrSetMarkerTrackingTimeoutVARJO = (PFN_xrSetMarkerTrackingTimeoutVARJO)LoadFunc(Instance, "xrSetMarkerTrackingTimeoutVARJO");
    xrSetMarkerTrackingVARJO = (PFN_xrSetMarkerTrackingVARJO)LoadFunc(Instance, "xrSetMarkerTrackingVARJO");
#endif /*  defined(XR_VARJO_marker_tracking)   */
#if defined(XR_VARJO_view_offset)
    xrSetViewOffsetVARJO = (PFN_xrSetViewOffsetVARJO)LoadFunc(Instance, "xrSetViewOffsetVARJO");
#endif /*  defined(XR_VARJO_view_offset)   */


}

//SECTION(V): XRMYTH_PROTOTYPE_IMPL
#if defined(XR_VERSION_1_0)
PFN_xrAcquireSwapchainImage xrAcquireSwapchainImage;
PFN_xrApplyHapticFeedback xrApplyHapticFeedback;
PFN_xrAttachSessionActionSets xrAttachSessionActionSets;
PFN_xrBeginFrame xrBeginFrame;
PFN_xrBeginSession xrBeginSession;
PFN_xrCreateAction xrCreateAction;
PFN_xrCreateActionSet xrCreateActionSet;
PFN_xrCreateActionSpace xrCreateActionSpace;
PFN_xrCreateInstance xrCreateInstance;
PFN_xrCreateReferenceSpace xrCreateReferenceSpace;
PFN_xrCreateSession xrCreateSession;
PFN_xrCreateSwapchain xrCreateSwapchain;
PFN_xrDestroyAction xrDestroyAction;
PFN_xrDestroyActionSet xrDestroyActionSet;
PFN_xrDestroyInstance xrDestroyInstance;
PFN_xrDestroySession xrDestroySession;
PFN_xrDestroySpace xrDestroySpace;
PFN_xrDestroySwapchain xrDestroySwapchain;
PFN_xrEndFrame xrEndFrame;
PFN_xrEndSession xrEndSession;
PFN_xrEnumerateApiLayerProperties xrEnumerateApiLayerProperties;
PFN_xrEnumerateBoundSourcesForAction xrEnumerateBoundSourcesForAction;
PFN_xrEnumerateEnvironmentBlendModes xrEnumerateEnvironmentBlendModes;
PFN_xrEnumerateInstanceExtensionProperties xrEnumerateInstanceExtensionProperties;
PFN_xrEnumerateReferenceSpaces xrEnumerateReferenceSpaces;
PFN_xrEnumerateSwapchainFormats xrEnumerateSwapchainFormats;
PFN_xrEnumerateSwapchainImages xrEnumerateSwapchainImages;
PFN_xrEnumerateViewConfigurationViews xrEnumerateViewConfigurationViews;
PFN_xrEnumerateViewConfigurations xrEnumerateViewConfigurations;
PFN_xrGetActionStateBoolean xrGetActionStateBoolean;
PFN_xrGetActionStateFloat xrGetActionStateFloat;
PFN_xrGetActionStatePose xrGetActionStatePose;
PFN_xrGetActionStateVector2f xrGetActionStateVector2f;
PFN_xrGetCurrentInteractionProfile xrGetCurrentInteractionProfile;
PFN_xrGetInputSourceLocalizedName xrGetInputSourceLocalizedName;
PFN_xrGetInstanceProcAddr xrGetInstanceProcAddr;
PFN_xrGetInstanceProperties xrGetInstanceProperties;
PFN_xrGetReferenceSpaceBoundsRect xrGetReferenceSpaceBoundsRect;
PFN_xrGetSystem xrGetSystem;
PFN_xrGetSystemProperties xrGetSystemProperties;
PFN_xrGetViewConfigurationProperties xrGetViewConfigurationProperties;
PFN_xrLocateSpace xrLocateSpace;
PFN_xrLocateViews xrLocateViews;
PFN_xrPathToString xrPathToString;
PFN_xrPollEvent xrPollEvent;
PFN_xrReleaseSwapchainImage xrReleaseSwapchainImage;
PFN_xrRequestExitSession xrRequestExitSession;
PFN_xrResultToString xrResultToString;
PFN_xrStopHapticFeedback xrStopHapticFeedback;
PFN_xrStringToPath xrStringToPath;
PFN_xrStructureTypeToString xrStructureTypeToString;
PFN_xrSuggestInteractionProfileBindings xrSuggestInteractionProfileBindings;
PFN_xrSyncActions xrSyncActions;
PFN_xrWaitFrame xrWaitFrame;
PFN_xrWaitSwapchainImage xrWaitSwapchainImage;
#endif /*  defined(XR_VERSION_1_0)   */
#if defined(XR_LOADER_VERSION_1_0)
PFN_xrCreateApiLayerInstance xrCreateApiLayerInstance;
PFN_xrNegotiateLoaderApiLayerInterface xrNegotiateLoaderApiLayerInterface;
PFN_xrNegotiateLoaderRuntimeInterface xrNegotiateLoaderRuntimeInterface;
#endif /*  defined(XR_LOADER_VERSION_1_0)   */
#if defined(XR_VERSION_1_1)
PFN_xrLocateSpaces xrLocateSpaces;
#endif /*  defined(XR_VERSION_1_1)   */
#if defined(XR_ALMALENCE_digital_lens_control)
PFN_xrSetDigitalLensControlALMALENCE xrSetDigitalLensControlALMALENCE;
#endif /*  defined(XR_ALMALENCE_digital_lens_control)   */
#if defined(XR_EXT_conformance_automation)
PFN_xrSetInputDeviceActiveEXT xrSetInputDeviceActiveEXT;
PFN_xrSetInputDeviceLocationEXT xrSetInputDeviceLocationEXT;
PFN_xrSetInputDeviceStateBoolEXT xrSetInputDeviceStateBoolEXT;
PFN_xrSetInputDeviceStateFloatEXT xrSetInputDeviceStateFloatEXT;
PFN_xrSetInputDeviceStateVector2fEXT xrSetInputDeviceStateVector2fEXT;
#endif /*  defined(XR_EXT_conformance_automation)   */
#if defined(XR_EXT_debug_utils)
PFN_xrCreateDebugUtilsMessengerEXT xrCreateDebugUtilsMessengerEXT;
PFN_xrDestroyDebugUtilsMessengerEXT xrDestroyDebugUtilsMessengerEXT;
PFN_xrSessionBeginDebugUtilsLabelRegionEXT xrSessionBeginDebugUtilsLabelRegionEXT;
PFN_xrSessionEndDebugUtilsLabelRegionEXT xrSessionEndDebugUtilsLabelRegionEXT;
PFN_xrSessionInsertDebugUtilsLabelEXT xrSessionInsertDebugUtilsLabelEXT;
PFN_xrSetDebugUtilsObjectNameEXT xrSetDebugUtilsObjectNameEXT;
PFN_xrSubmitDebugUtilsMessageEXT xrSubmitDebugUtilsMessageEXT;
#endif /*  defined(XR_EXT_debug_utils)   */
#if defined(XR_EXT_future)
PFN_xrCancelFutureEXT xrCancelFutureEXT;
PFN_xrPollFutureEXT xrPollFutureEXT;
#endif /*  defined(XR_EXT_future)   */
#if defined(XR_EXT_hand_tracking)
PFN_xrCreateHandTrackerEXT xrCreateHandTrackerEXT;
PFN_xrDestroyHandTrackerEXT xrDestroyHandTrackerEXT;
PFN_xrLocateHandJointsEXT xrLocateHandJointsEXT;
#endif /*  defined(XR_EXT_hand_tracking)   */
#if defined(XR_EXT_performance_settings)
PFN_xrPerfSettingsSetPerformanceLevelEXT xrPerfSettingsSetPerformanceLevelEXT;
#endif /*  defined(XR_EXT_performance_settings)   */
#if defined(XR_EXT_plane_detection)
PFN_xrBeginPlaneDetectionEXT xrBeginPlaneDetectionEXT;
PFN_xrCreatePlaneDetectorEXT xrCreatePlaneDetectorEXT;
PFN_xrDestroyPlaneDetectorEXT xrDestroyPlaneDetectorEXT;
PFN_xrGetPlaneDetectionStateEXT xrGetPlaneDetectionStateEXT;
PFN_xrGetPlaneDetectionsEXT xrGetPlaneDetectionsEXT;
PFN_xrGetPlanePolygonBufferEXT xrGetPlanePolygonBufferEXT;
#endif /*  defined(XR_EXT_plane_detection)   */
#if defined(XR_EXT_thermal_query)
PFN_xrThermalGetTemperatureTrendEXT xrThermalGetTemperatureTrendEXT;
#endif /*  defined(XR_EXT_thermal_query)   */
#if defined(XR_FB_body_tracking)
PFN_xrCreateBodyTrackerFB xrCreateBodyTrackerFB;
PFN_xrDestroyBodyTrackerFB xrDestroyBodyTrackerFB;
PFN_xrGetBodySkeletonFB xrGetBodySkeletonFB;
PFN_xrLocateBodyJointsFB xrLocateBodyJointsFB;
#endif /*  defined(XR_FB_body_tracking)   */
#if defined(XR_FB_color_space)
PFN_xrEnumerateColorSpacesFB xrEnumerateColorSpacesFB;
PFN_xrSetColorSpaceFB xrSetColorSpaceFB;
#endif /*  defined(XR_FB_color_space)   */
#if defined(XR_FB_display_refresh_rate)
PFN_xrEnumerateDisplayRefreshRatesFB xrEnumerateDisplayRefreshRatesFB;
PFN_xrGetDisplayRefreshRateFB xrGetDisplayRefreshRateFB;
PFN_xrRequestDisplayRefreshRateFB xrRequestDisplayRefreshRateFB;
#endif /*  defined(XR_FB_display_refresh_rate)   */
#if defined(XR_FB_eye_tracking_social)
PFN_xrCreateEyeTrackerFB xrCreateEyeTrackerFB;
PFN_xrDestroyEyeTrackerFB xrDestroyEyeTrackerFB;
PFN_xrGetEyeGazesFB xrGetEyeGazesFB;
#endif /*  defined(XR_FB_eye_tracking_social)   */
#if defined(XR_FB_face_tracking)
PFN_xrCreateFaceTrackerFB xrCreateFaceTrackerFB;
PFN_xrDestroyFaceTrackerFB xrDestroyFaceTrackerFB;
PFN_xrGetFaceExpressionWeightsFB xrGetFaceExpressionWeightsFB;
#endif /*  defined(XR_FB_face_tracking)   */
#if defined(XR_FB_face_tracking2)
PFN_xrCreateFaceTracker2FB xrCreateFaceTracker2FB;
PFN_xrDestroyFaceTracker2FB xrDestroyFaceTracker2FB;
PFN_xrGetFaceExpressionWeights2FB xrGetFaceExpressionWeights2FB;
#endif /*  defined(XR_FB_face_tracking2)   */
#if defined(XR_FB_foveation)
PFN_xrCreateFoveationProfileFB xrCreateFoveationProfileFB;
PFN_xrDestroyFoveationProfileFB xrDestroyFoveationProfileFB;
#endif /*  defined(XR_FB_foveation)   */
#if defined(XR_FB_hand_tracking_mesh)
PFN_xrGetHandMeshFB xrGetHandMeshFB;
#endif /*  defined(XR_FB_hand_tracking_mesh)   */
#if defined(XR_FB_haptic_pcm)
PFN_xrGetDeviceSampleRateFB xrGetDeviceSampleRateFB;
#endif /*  defined(XR_FB_haptic_pcm)   */
#if defined(XR_FB_keyboard_tracking)
PFN_xrCreateKeyboardSpaceFB xrCreateKeyboardSpaceFB;
PFN_xrQuerySystemTrackedKeyboardFB xrQuerySystemTrackedKeyboardFB;
#endif /*  defined(XR_FB_keyboard_tracking)   */
#if defined(XR_FB_passthrough)
PFN_xrCreateGeometryInstanceFB xrCreateGeometryInstanceFB;
PFN_xrCreatePassthroughFB xrCreatePassthroughFB;
PFN_xrCreatePassthroughLayerFB xrCreatePassthroughLayerFB;
PFN_xrDestroyGeometryInstanceFB xrDestroyGeometryInstanceFB;
PFN_xrDestroyPassthroughFB xrDestroyPassthroughFB;
PFN_xrDestroyPassthroughLayerFB xrDestroyPassthroughLayerFB;
PFN_xrGeometryInstanceSetTransformFB xrGeometryInstanceSetTransformFB;
PFN_xrPassthroughLayerPauseFB xrPassthroughLayerPauseFB;
PFN_xrPassthroughLayerResumeFB xrPassthroughLayerResumeFB;
PFN_xrPassthroughLayerSetStyleFB xrPassthroughLayerSetStyleFB;
PFN_xrPassthroughPauseFB xrPassthroughPauseFB;
PFN_xrPassthroughStartFB xrPassthroughStartFB;
#endif /*  defined(XR_FB_passthrough)   */
#if defined(XR_FB_passthrough_keyboard_hands)
PFN_xrPassthroughLayerSetKeyboardHandsIntensityFB xrPassthroughLayerSetKeyboardHandsIntensityFB;
#endif /*  defined(XR_FB_passthrough_keyboard_hands)   */
#if defined(XR_FB_render_model)
PFN_xrEnumerateRenderModelPathsFB xrEnumerateRenderModelPathsFB;
PFN_xrGetRenderModelPropertiesFB xrGetRenderModelPropertiesFB;
PFN_xrLoadRenderModelFB xrLoadRenderModelFB;
#endif /*  defined(XR_FB_render_model)   */
#if defined(XR_FB_scene)
PFN_xrGetSpaceBoundary2DFB xrGetSpaceBoundary2DFB;
PFN_xrGetSpaceBoundingBox2DFB xrGetSpaceBoundingBox2DFB;
PFN_xrGetSpaceBoundingBox3DFB xrGetSpaceBoundingBox3DFB;
PFN_xrGetSpaceRoomLayoutFB xrGetSpaceRoomLayoutFB;
PFN_xrGetSpaceSemanticLabelsFB xrGetSpaceSemanticLabelsFB;
#endif /*  defined(XR_FB_scene)   */
#if defined(XR_FB_scene_capture)
PFN_xrRequestSceneCaptureFB xrRequestSceneCaptureFB;
#endif /*  defined(XR_FB_scene_capture)   */
#if defined(XR_FB_spatial_entity)
PFN_xrCreateSpatialAnchorFB xrCreateSpatialAnchorFB;
PFN_xrEnumerateSpaceSupportedComponentsFB xrEnumerateSpaceSupportedComponentsFB;
PFN_xrGetSpaceComponentStatusFB xrGetSpaceComponentStatusFB;
PFN_xrGetSpaceUuidFB xrGetSpaceUuidFB;
PFN_xrSetSpaceComponentStatusFB xrSetSpaceComponentStatusFB;
#endif /*  defined(XR_FB_spatial_entity)   */
#if defined(XR_FB_spatial_entity_container)
PFN_xrGetSpaceContainerFB xrGetSpaceContainerFB;
#endif /*  defined(XR_FB_spatial_entity_container)   */
#if defined(XR_FB_spatial_entity_query)
PFN_xrQuerySpacesFB xrQuerySpacesFB;
PFN_xrRetrieveSpaceQueryResultsFB xrRetrieveSpaceQueryResultsFB;
#endif /*  defined(XR_FB_spatial_entity_query)   */
#if defined(XR_FB_spatial_entity_sharing)
PFN_xrShareSpacesFB xrShareSpacesFB;
#endif /*  defined(XR_FB_spatial_entity_sharing)   */
#if defined(XR_FB_spatial_entity_storage)
PFN_xrEraseSpaceFB xrEraseSpaceFB;
PFN_xrSaveSpaceFB xrSaveSpaceFB;
#endif /*  defined(XR_FB_spatial_entity_storage)   */
#if defined(XR_FB_spatial_entity_storage_batch)
PFN_xrSaveSpaceListFB xrSaveSpaceListFB;
#endif /*  defined(XR_FB_spatial_entity_storage_batch)   */
#if defined(XR_FB_spatial_entity_user)
PFN_xrCreateSpaceUserFB xrCreateSpaceUserFB;
PFN_xrDestroySpaceUserFB xrDestroySpaceUserFB;
PFN_xrGetSpaceUserIdFB xrGetSpaceUserIdFB;
#endif /*  defined(XR_FB_spatial_entity_user)   */
#if defined(XR_FB_swapchain_update_state)
PFN_xrGetSwapchainStateFB xrGetSwapchainStateFB;
PFN_xrUpdateSwapchainFB xrUpdateSwapchainFB;
#endif /*  defined(XR_FB_swapchain_update_state)   */
#if defined(XR_FB_triangle_mesh)
PFN_xrCreateTriangleMeshFB xrCreateTriangleMeshFB;
PFN_xrDestroyTriangleMeshFB xrDestroyTriangleMeshFB;
PFN_xrTriangleMeshBeginUpdateFB xrTriangleMeshBeginUpdateFB;
PFN_xrTriangleMeshBeginVertexBufferUpdateFB xrTriangleMeshBeginVertexBufferUpdateFB;
PFN_xrTriangleMeshEndUpdateFB xrTriangleMeshEndUpdateFB;
PFN_xrTriangleMeshEndVertexBufferUpdateFB xrTriangleMeshEndVertexBufferUpdateFB;
PFN_xrTriangleMeshGetIndexBufferFB xrTriangleMeshGetIndexBufferFB;
PFN_xrTriangleMeshGetVertexBufferFB xrTriangleMeshGetVertexBufferFB;
#endif /*  defined(XR_FB_triangle_mesh)   */
#if defined(XR_HTCX_vive_tracker_interaction)
PFN_xrEnumerateViveTrackerPathsHTCX xrEnumerateViveTrackerPathsHTCX;
#endif /*  defined(XR_HTCX_vive_tracker_interaction)   */
#if defined(XR_HTC_anchor)
PFN_xrCreateSpatialAnchorHTC xrCreateSpatialAnchorHTC;
PFN_xrGetSpatialAnchorNameHTC xrGetSpatialAnchorNameHTC;
#endif /*  defined(XR_HTC_anchor)   */
#if defined(XR_HTC_facial_tracking)
PFN_xrCreateFacialTrackerHTC xrCreateFacialTrackerHTC;
PFN_xrDestroyFacialTrackerHTC xrDestroyFacialTrackerHTC;
PFN_xrGetFacialExpressionsHTC xrGetFacialExpressionsHTC;
#endif /*  defined(XR_HTC_facial_tracking)   */
#if defined(XR_HTC_foveation)
PFN_xrApplyFoveationHTC xrApplyFoveationHTC;
#endif /*  defined(XR_HTC_foveation)   */
#if defined(XR_HTC_passthrough)
PFN_xrCreatePassthroughHTC xrCreatePassthroughHTC;
PFN_xrDestroyPassthroughHTC xrDestroyPassthroughHTC;
#endif /*  defined(XR_HTC_passthrough)   */
#if defined(XR_KHR_D3D11_enable)
PFN_xrGetD3D11GraphicsRequirementsKHR xrGetD3D11GraphicsRequirementsKHR;
#endif /*  defined(XR_KHR_D3D11_enable)   */
#if defined(XR_KHR_D3D12_enable)
PFN_xrGetD3D12GraphicsRequirementsKHR xrGetD3D12GraphicsRequirementsKHR;
#endif /*  defined(XR_KHR_D3D12_enable)   */
#if defined(XR_KHR_android_surface_swapchain)
PFN_xrCreateSwapchainAndroidSurfaceKHR xrCreateSwapchainAndroidSurfaceKHR;
#endif /*  defined(XR_KHR_android_surface_swapchain)   */
#if defined(XR_KHR_android_thread_settings)
PFN_xrSetAndroidApplicationThreadKHR xrSetAndroidApplicationThreadKHR;
#endif /*  defined(XR_KHR_android_thread_settings)   */
#if defined(XR_KHR_convert_timespec_time)
PFN_xrConvertTimeToTimespecTimeKHR xrConvertTimeToTimespecTimeKHR;
PFN_xrConvertTimespecTimeToTimeKHR xrConvertTimespecTimeToTimeKHR;
#endif /*  defined(XR_KHR_convert_timespec_time)   */
#if defined(XR_KHR_loader_init)
PFN_xrInitializeLoaderKHR xrInitializeLoaderKHR;
#endif /*  defined(XR_KHR_loader_init)   */
#if defined(XR_KHR_locate_spaces)
PFN_xrLocateSpacesKHR xrLocateSpacesKHR;
#endif /*  defined(XR_KHR_locate_spaces)   */
#if defined(XR_KHR_opengl_enable)
PFN_xrGetOpenGLGraphicsRequirementsKHR xrGetOpenGLGraphicsRequirementsKHR;
#endif /*  defined(XR_KHR_opengl_enable)   */
#if defined(XR_KHR_opengl_es_enable)
PFN_xrGetOpenGLESGraphicsRequirementsKHR xrGetOpenGLESGraphicsRequirementsKHR;
#endif /*  defined(XR_KHR_opengl_es_enable)   */
#if defined(XR_KHR_visibility_mask)
PFN_xrGetVisibilityMaskKHR xrGetVisibilityMaskKHR;
#endif /*  defined(XR_KHR_visibility_mask)   */
#if defined(XR_KHR_vulkan_enable)
PFN_xrGetVulkanDeviceExtensionsKHR xrGetVulkanDeviceExtensionsKHR;
PFN_xrGetVulkanGraphicsDeviceKHR xrGetVulkanGraphicsDeviceKHR;
PFN_xrGetVulkanGraphicsRequirementsKHR xrGetVulkanGraphicsRequirementsKHR;
PFN_xrGetVulkanInstanceExtensionsKHR xrGetVulkanInstanceExtensionsKHR;
#endif /*  defined(XR_KHR_vulkan_enable)   */
#if defined(XR_KHR_vulkan_enable2)
PFN_xrCreateVulkanDeviceKHR xrCreateVulkanDeviceKHR;
PFN_xrCreateVulkanInstanceKHR xrCreateVulkanInstanceKHR;
PFN_xrGetVulkanGraphicsDevice2KHR xrGetVulkanGraphicsDevice2KHR;
PFN_xrGetVulkanGraphicsRequirements2KHR xrGetVulkanGraphicsRequirements2KHR;
#endif /*  defined(XR_KHR_vulkan_enable2)   */
#if defined(XR_KHR_win32_convert_performance_counter_time)
PFN_xrConvertTimeToWin32PerformanceCounterKHR xrConvertTimeToWin32PerformanceCounterKHR;
PFN_xrConvertWin32PerformanceCounterToTimeKHR xrConvertWin32PerformanceCounterToTimeKHR;
#endif /*  defined(XR_KHR_win32_convert_performance_counter_time)   */
#if defined(XR_META_environment_depth)
PFN_xrAcquireEnvironmentDepthImageMETA xrAcquireEnvironmentDepthImageMETA;
PFN_xrCreateEnvironmentDepthProviderMETA xrCreateEnvironmentDepthProviderMETA;
PFN_xrCreateEnvironmentDepthSwapchainMETA xrCreateEnvironmentDepthSwapchainMETA;
PFN_xrDestroyEnvironmentDepthProviderMETA xrDestroyEnvironmentDepthProviderMETA;
PFN_xrDestroyEnvironmentDepthSwapchainMETA xrDestroyEnvironmentDepthSwapchainMETA;
PFN_xrEnumerateEnvironmentDepthSwapchainImagesMETA xrEnumerateEnvironmentDepthSwapchainImagesMETA;
PFN_xrGetEnvironmentDepthSwapchainStateMETA xrGetEnvironmentDepthSwapchainStateMETA;
PFN_xrSetEnvironmentDepthHandRemovalMETA xrSetEnvironmentDepthHandRemovalMETA;
PFN_xrStartEnvironmentDepthProviderMETA xrStartEnvironmentDepthProviderMETA;
PFN_xrStopEnvironmentDepthProviderMETA xrStopEnvironmentDepthProviderMETA;
#endif /*  defined(XR_META_environment_depth)   */
#if defined(XR_META_foveation_eye_tracked)
PFN_xrGetFoveationEyeTrackedStateMETA xrGetFoveationEyeTrackedStateMETA;
#endif /*  defined(XR_META_foveation_eye_tracked)   */
#if defined(XR_META_passthrough_color_lut)
PFN_xrCreatePassthroughColorLutMETA xrCreatePassthroughColorLutMETA;
PFN_xrDestroyPassthroughColorLutMETA xrDestroyPassthroughColorLutMETA;
PFN_xrUpdatePassthroughColorLutMETA xrUpdatePassthroughColorLutMETA;
#endif /*  defined(XR_META_passthrough_color_lut)   */
#if defined(XR_META_passthrough_preferences)
PFN_xrGetPassthroughPreferencesMETA xrGetPassthroughPreferencesMETA;
#endif /*  defined(XR_META_passthrough_preferences)   */
#if defined(XR_META_performance_metrics)
PFN_xrEnumeratePerformanceMetricsCounterPathsMETA xrEnumeratePerformanceMetricsCounterPathsMETA;
PFN_xrGetPerformanceMetricsStateMETA xrGetPerformanceMetricsStateMETA;
PFN_xrQueryPerformanceMetricsCounterMETA xrQueryPerformanceMetricsCounterMETA;
PFN_xrSetPerformanceMetricsStateMETA xrSetPerformanceMetricsStateMETA;
#endif /*  defined(XR_META_performance_metrics)   */
#if defined(XR_META_recommended_layer_resolution)
PFN_xrGetRecommendedLayerResolutionMETA xrGetRecommendedLayerResolutionMETA;
#endif /*  defined(XR_META_recommended_layer_resolution)   */
#if defined(XR_META_spatial_entity_mesh)
PFN_xrGetSpaceTriangleMeshMETA xrGetSpaceTriangleMeshMETA;
#endif /*  defined(XR_META_spatial_entity_mesh)   */
#if defined(XR_META_virtual_keyboard)
PFN_xrChangeVirtualKeyboardTextContextMETA xrChangeVirtualKeyboardTextContextMETA;
PFN_xrCreateVirtualKeyboardMETA xrCreateVirtualKeyboardMETA;
PFN_xrCreateVirtualKeyboardSpaceMETA xrCreateVirtualKeyboardSpaceMETA;
PFN_xrDestroyVirtualKeyboardMETA xrDestroyVirtualKeyboardMETA;
PFN_xrGetVirtualKeyboardDirtyTexturesMETA xrGetVirtualKeyboardDirtyTexturesMETA;
PFN_xrGetVirtualKeyboardModelAnimationStatesMETA xrGetVirtualKeyboardModelAnimationStatesMETA;
PFN_xrGetVirtualKeyboardScaleMETA xrGetVirtualKeyboardScaleMETA;
PFN_xrGetVirtualKeyboardTextureDataMETA xrGetVirtualKeyboardTextureDataMETA;
PFN_xrSendVirtualKeyboardInputMETA xrSendVirtualKeyboardInputMETA;
PFN_xrSetVirtualKeyboardModelVisibilityMETA xrSetVirtualKeyboardModelVisibilityMETA;
PFN_xrSuggestVirtualKeyboardLocationMETA xrSuggestVirtualKeyboardLocationMETA;
#endif /*  defined(XR_META_virtual_keyboard)   */
#if defined(XR_ML_compat)
PFN_xrCreateSpaceFromCoordinateFrameUIDML xrCreateSpaceFromCoordinateFrameUIDML;
#endif /*  defined(XR_ML_compat)   */
#if defined(XR_ML_localization_map)
PFN_xrCreateExportedLocalizationMapML xrCreateExportedLocalizationMapML;
PFN_xrDestroyExportedLocalizationMapML xrDestroyExportedLocalizationMapML;
PFN_xrEnableLocalizationEventsML xrEnableLocalizationEventsML;
PFN_xrGetExportedLocalizationMapDataML xrGetExportedLocalizationMapDataML;
PFN_xrImportLocalizationMapML xrImportLocalizationMapML;
PFN_xrQueryLocalizationMapsML xrQueryLocalizationMapsML;
PFN_xrRequestMapLocalizationML xrRequestMapLocalizationML;
#endif /*  defined(XR_ML_localization_map)   */
#if defined(XR_ML_marker_understanding)
PFN_xrCreateMarkerDetectorML xrCreateMarkerDetectorML;
PFN_xrCreateMarkerSpaceML xrCreateMarkerSpaceML;
PFN_xrDestroyMarkerDetectorML xrDestroyMarkerDetectorML;
PFN_xrGetMarkerDetectorStateML xrGetMarkerDetectorStateML;
PFN_xrGetMarkerLengthML xrGetMarkerLengthML;
PFN_xrGetMarkerNumberML xrGetMarkerNumberML;
PFN_xrGetMarkerReprojectionErrorML xrGetMarkerReprojectionErrorML;
PFN_xrGetMarkerStringML xrGetMarkerStringML;
PFN_xrGetMarkersML xrGetMarkersML;
PFN_xrSnapshotMarkerDetectorML xrSnapshotMarkerDetectorML;
#endif /*  defined(XR_ML_marker_understanding)   */
#if defined(XR_ML_user_calibration)
PFN_xrEnableUserCalibrationEventsML xrEnableUserCalibrationEventsML;
#endif /*  defined(XR_ML_user_calibration)   */
#if defined(XR_MNDX_force_feedback_curl)
PFN_xrApplyForceFeedbackCurlMNDX xrApplyForceFeedbackCurlMNDX;
#endif /*  defined(XR_MNDX_force_feedback_curl)   */
#if defined(XR_MSFT_composition_layer_reprojection)
PFN_xrEnumerateReprojectionModesMSFT xrEnumerateReprojectionModesMSFT;
#endif /*  defined(XR_MSFT_composition_layer_reprojection)   */
#if defined(XR_MSFT_controller_model)
PFN_xrGetControllerModelKeyMSFT xrGetControllerModelKeyMSFT;
PFN_xrGetControllerModelPropertiesMSFT xrGetControllerModelPropertiesMSFT;
PFN_xrGetControllerModelStateMSFT xrGetControllerModelStateMSFT;
PFN_xrLoadControllerModelMSFT xrLoadControllerModelMSFT;
#endif /*  defined(XR_MSFT_controller_model)   */
#if defined(XR_MSFT_hand_tracking_mesh)
PFN_xrCreateHandMeshSpaceMSFT xrCreateHandMeshSpaceMSFT;
PFN_xrUpdateHandMeshMSFT xrUpdateHandMeshMSFT;
#endif /*  defined(XR_MSFT_hand_tracking_mesh)   */
#if defined(XR_MSFT_perception_anchor_interop)
PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT xrCreateSpatialAnchorFromPerceptionAnchorMSFT;
PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT xrTryGetPerceptionAnchorFromSpatialAnchorMSFT;
#endif /*  defined(XR_MSFT_perception_anchor_interop)   */
#if defined(XR_MSFT_scene_marker)
PFN_xrGetSceneMarkerDecodedStringMSFT xrGetSceneMarkerDecodedStringMSFT;
PFN_xrGetSceneMarkerRawDataMSFT xrGetSceneMarkerRawDataMSFT;
#endif /*  defined(XR_MSFT_scene_marker)   */
#if defined(XR_MSFT_scene_understanding)
PFN_xrComputeNewSceneMSFT xrComputeNewSceneMSFT;
PFN_xrCreateSceneMSFT xrCreateSceneMSFT;
PFN_xrCreateSceneObserverMSFT xrCreateSceneObserverMSFT;
PFN_xrDestroySceneMSFT xrDestroySceneMSFT;
PFN_xrDestroySceneObserverMSFT xrDestroySceneObserverMSFT;
PFN_xrEnumerateSceneComputeFeaturesMSFT xrEnumerateSceneComputeFeaturesMSFT;
PFN_xrGetSceneComponentsMSFT xrGetSceneComponentsMSFT;
PFN_xrGetSceneComputeStateMSFT xrGetSceneComputeStateMSFT;
PFN_xrGetSceneMeshBuffersMSFT xrGetSceneMeshBuffersMSFT;
PFN_xrLocateSceneComponentsMSFT xrLocateSceneComponentsMSFT;
#endif /*  defined(XR_MSFT_scene_understanding)   */
#if defined(XR_MSFT_scene_understanding_serialization)
PFN_xrDeserializeSceneMSFT xrDeserializeSceneMSFT;
PFN_xrGetSerializedSceneFragmentDataMSFT xrGetSerializedSceneFragmentDataMSFT;
#endif /*  defined(XR_MSFT_scene_understanding_serialization)   */
#if defined(XR_MSFT_spatial_anchor)
PFN_xrCreateSpatialAnchorMSFT xrCreateSpatialAnchorMSFT;
PFN_xrCreateSpatialAnchorSpaceMSFT xrCreateSpatialAnchorSpaceMSFT;
PFN_xrDestroySpatialAnchorMSFT xrDestroySpatialAnchorMSFT;
#endif /*  defined(XR_MSFT_spatial_anchor)   */
#if defined(XR_MSFT_spatial_anchor_persistence)
PFN_xrClearSpatialAnchorStoreMSFT xrClearSpatialAnchorStoreMSFT;
PFN_xrCreateSpatialAnchorFromPersistedNameMSFT xrCreateSpatialAnchorFromPersistedNameMSFT;
PFN_xrCreateSpatialAnchorStoreConnectionMSFT xrCreateSpatialAnchorStoreConnectionMSFT;
PFN_xrDestroySpatialAnchorStoreConnectionMSFT xrDestroySpatialAnchorStoreConnectionMSFT;
PFN_xrEnumeratePersistedSpatialAnchorNamesMSFT xrEnumeratePersistedSpatialAnchorNamesMSFT;
PFN_xrPersistSpatialAnchorMSFT xrPersistSpatialAnchorMSFT;
PFN_xrUnpersistSpatialAnchorMSFT xrUnpersistSpatialAnchorMSFT;
#endif /*  defined(XR_MSFT_spatial_anchor_persistence)   */
#if defined(XR_MSFT_spatial_graph_bridge)
PFN_xrCreateSpatialGraphNodeSpaceMSFT xrCreateSpatialGraphNodeSpaceMSFT;
PFN_xrDestroySpatialGraphNodeBindingMSFT xrDestroySpatialGraphNodeBindingMSFT;
PFN_xrGetSpatialGraphNodeBindingPropertiesMSFT xrGetSpatialGraphNodeBindingPropertiesMSFT;
PFN_xrTryCreateSpatialGraphStaticNodeBindingMSFT xrTryCreateSpatialGraphStaticNodeBindingMSFT;
#endif /*  defined(XR_MSFT_spatial_graph_bridge)   */
#if defined(XR_OCULUS_audio_device_guid)
PFN_xrGetAudioInputDeviceGuidOculus xrGetAudioInputDeviceGuidOculus;
PFN_xrGetAudioOutputDeviceGuidOculus xrGetAudioOutputDeviceGuidOculus;
#endif /*  defined(XR_OCULUS_audio_device_guid)   */
#if defined(XR_OCULUS_external_camera)
PFN_xrEnumerateExternalCamerasOCULUS xrEnumerateExternalCamerasOCULUS;
#endif /*  defined(XR_OCULUS_external_camera)   */
#if defined(XR_QCOM_tracking_optimization_settings)
PFN_xrSetTrackingOptimizationSettingsHintQCOM xrSetTrackingOptimizationSettingsHintQCOM;
#endif /*  defined(XR_QCOM_tracking_optimization_settings)   */
#if defined(XR_VARJO_environment_depth_estimation)
PFN_xrSetEnvironmentDepthEstimationVARJO xrSetEnvironmentDepthEstimationVARJO;
#endif /*  defined(XR_VARJO_environment_depth_estimation)   */
#if defined(XR_VARJO_marker_tracking)
PFN_xrCreateMarkerSpaceVARJO xrCreateMarkerSpaceVARJO;
PFN_xrGetMarkerSizeVARJO xrGetMarkerSizeVARJO;
PFN_xrSetMarkerTrackingPredictionVARJO xrSetMarkerTrackingPredictionVARJO;
PFN_xrSetMarkerTrackingTimeoutVARJO xrSetMarkerTrackingTimeoutVARJO;
PFN_xrSetMarkerTrackingVARJO xrSetMarkerTrackingVARJO;
#endif /*  defined(XR_VARJO_marker_tracking)   */
#if defined(XR_VARJO_view_offset)
PFN_xrSetViewOffsetVARJO xrSetViewOffsetVARJO;
#endif /*  defined(XR_VARJO_view_offset)   */

#ifdef __cplusplus
}
#endif
