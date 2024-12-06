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
		#ifdef _WIN32
		mdsoHandle Handle = mdsoOpen(MYTH_XR_LOAD_DLL, mdsoFlags_none);
		if(!Handle){
			Handle = mdsoOpen(MYTH_XR_LOAD_DLL, mdsoFlags_none);

		}

		#else
		mdsoHandle Handle = mdsoOpen(MYTH_XR_LOAD_DLL, mdsoFlags_localSymbols);
		if(!Handle){
			Handle = mdsoOpen(MYTH_XR_LOAD_DLL, mdsoFlags_localSymbols);

		}

		#endif

		//TODO(V): Add better search for openxr_loader.so, like search if steam vr is installed and use that copy

		if(!Handle){
			VERRNF("XrLoader", "Could not load OpenXR api");
			return false;

		}

		xrGetInstanceProcAddr = (PFN_xrGetInstanceProcAddr)mdsoGetFunc(Handle, "xrGetInstanceProcAddr");
		if(xrGetInstanceProcAddr == NULL){
			VERRNF("XrLoader", "Could not load OpenXR entry point");
			return false;

		}

		Libxr = Handle;
		_mythXrLoadBasic(NULL, &mythXrLoad_loadFunc);

		return true;

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

	#ifndef MYTH_XR_NO_TOSTR

	//SECTION(V): XRMYTH_SPECIAL_ENUM8_IMPL
	#if defined(XR_FB_spatial_entity)
	const char* vtostr8_XrSpaceComponentTypeFB(XrSpaceComponentTypeFB In){
		switch(In){
			case(XR_SPACE_COMPONENT_TYPE_LOCATABLE_FB):
				return "XR_SPACE_COMPONENT_TYPE_LOCATABLE_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_STORABLE_FB):
				return "XR_SPACE_COMPONENT_TYPE_STORABLE_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_SHARABLE_FB):
				return "XR_SPACE_COMPONENT_TYPE_SHARABLE_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_BOUNDED_2D_FB):
				return "XR_SPACE_COMPONENT_TYPE_BOUNDED_2D_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_BOUNDED_3D_FB):
				return "XR_SPACE_COMPONENT_TYPE_BOUNDED_3D_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_SEMANTIC_LABELS_FB):
				return "XR_SPACE_COMPONENT_TYPE_SEMANTIC_LABELS_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_ROOM_LAYOUT_FB):
				return "XR_SPACE_COMPONENT_TYPE_ROOM_LAYOUT_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_SPACE_CONTAINER_FB):
				return "XR_SPACE_COMPONENT_TYPE_SPACE_CONTAINER_FB";
				break;
			#if defined(XR_META_spatial_entity_mesh)
			case(XR_SPACE_COMPONENT_TYPE_TRIANGLE_MESH_META):
				return "XR_SPACE_COMPONENT_TYPE_TRIANGLE_MESH_META";
				break;
			#endif /*  defined(XR_META_spatial_entity_mesh)  */
			default:
				return "XrSpaceComponentTypeFB_TOSTR_ERROR";

		}

	}

	#endif

	#if defined(XR_MSFT_scene_understanding)
	const char* vtostr8_XrSceneComponentTypeMSFT(XrSceneComponentTypeMSFT In){
		switch(In){
			case(XR_SCENE_COMPONENT_TYPE_INVALID_MSFT):
				return "XR_SCENE_COMPONENT_TYPE_INVALID_MSFT";
				break;
			case(XR_SCENE_COMPONENT_TYPE_OBJECT_MSFT):
				return "XR_SCENE_COMPONENT_TYPE_OBJECT_MSFT";
				break;
			case(XR_SCENE_COMPONENT_TYPE_PLANE_MSFT):
				return "XR_SCENE_COMPONENT_TYPE_PLANE_MSFT";
				break;
			case(XR_SCENE_COMPONENT_TYPE_VISUAL_MESH_MSFT):
				return "XR_SCENE_COMPONENT_TYPE_VISUAL_MESH_MSFT";
				break;
			case(XR_SCENE_COMPONENT_TYPE_COLLIDER_MESH_MSFT):
				return "XR_SCENE_COMPONENT_TYPE_COLLIDER_MESH_MSFT";
				break;
			#if defined(XR_MSFT_scene_marker)
			case(XR_SCENE_COMPONENT_TYPE_MARKER_MSFT):
				return "XR_SCENE_COMPONENT_TYPE_MARKER_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_marker)  */
			#if defined(XR_MSFT_scene_understanding_serialization)
			case(XR_SCENE_COMPONENT_TYPE_SERIALIZED_SCENE_FRAGMENT_MSFT):
				return "XR_SCENE_COMPONENT_TYPE_SERIALIZED_SCENE_FRAGMENT_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_understanding_serialization)  */
			default:
				return "XrSceneComponentTypeMSFT_TOSTR_ERROR";

		}

	}

	#endif

	#if defined(XR_VERSION_1_0)
	const char* vtostr8_XrObjectType(XrObjectType In){
		switch(In){
			case(XR_OBJECT_TYPE_UNKNOWN):
				return "XR_OBJECT_TYPE_UNKNOWN";
				break;
			case(XR_OBJECT_TYPE_INSTANCE):
				return "XR_OBJECT_TYPE_INSTANCE";
				break;
			case(XR_OBJECT_TYPE_SESSION):
				return "XR_OBJECT_TYPE_SESSION";
				break;
			case(XR_OBJECT_TYPE_SWAPCHAIN):
				return "XR_OBJECT_TYPE_SWAPCHAIN";
				break;
			case(XR_OBJECT_TYPE_SPACE):
				return "XR_OBJECT_TYPE_SPACE";
				break;
			case(XR_OBJECT_TYPE_ACTION_SET):
				return "XR_OBJECT_TYPE_ACTION_SET";
				break;
			case(XR_OBJECT_TYPE_ACTION):
				return "XR_OBJECT_TYPE_ACTION";
				break;
			#if defined(XR_EXT_debug_utils)
			case(XR_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT):
				return "XR_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT";
				break;
			#endif /*  defined(XR_EXT_debug_utils)  */
			#if defined(XR_EXT_hand_tracking)
			case(XR_OBJECT_TYPE_HAND_TRACKER_EXT):
				return "XR_OBJECT_TYPE_HAND_TRACKER_EXT";
				break;
			#endif /*  defined(XR_EXT_hand_tracking)  */
			#if defined(XR_EXT_plane_detection)
			case(XR_OBJECT_TYPE_PLANE_DETECTOR_EXT):
				return "XR_OBJECT_TYPE_PLANE_DETECTOR_EXT";
				break;
			#endif /*  defined(XR_EXT_plane_detection)  */
			#if defined(XR_FB_body_tracking)
			case(XR_OBJECT_TYPE_BODY_TRACKER_FB):
				return "XR_OBJECT_TYPE_BODY_TRACKER_FB";
				break;
			#endif /*  defined(XR_FB_body_tracking)  */
			#if defined(XR_FB_eye_tracking_social)
			case(XR_OBJECT_TYPE_EYE_TRACKER_FB):
				return "XR_OBJECT_TYPE_EYE_TRACKER_FB";
				break;
			#endif /*  defined(XR_FB_eye_tracking_social)  */
			#if defined(XR_FB_face_tracking)
			case(XR_OBJECT_TYPE_FACE_TRACKER_FB):
				return "XR_OBJECT_TYPE_FACE_TRACKER_FB";
				break;
			#endif /*  defined(XR_FB_face_tracking)  */
			#if defined(XR_FB_face_tracking2)
			case(XR_OBJECT_TYPE_FACE_TRACKER2_FB):
				return "XR_OBJECT_TYPE_FACE_TRACKER2_FB";
				break;
			#endif /*  defined(XR_FB_face_tracking2)  */
			#if defined(XR_FB_foveation)
			case(XR_OBJECT_TYPE_FOVEATION_PROFILE_FB):
				return "XR_OBJECT_TYPE_FOVEATION_PROFILE_FB";
				break;
			#endif /*  defined(XR_FB_foveation)  */
			#if defined(XR_FB_passthrough)
			case(XR_OBJECT_TYPE_PASSTHROUGH_FB):
				return "XR_OBJECT_TYPE_PASSTHROUGH_FB";
				break;
			case(XR_OBJECT_TYPE_PASSTHROUGH_LAYER_FB):
				return "XR_OBJECT_TYPE_PASSTHROUGH_LAYER_FB";
				break;
			case(XR_OBJECT_TYPE_GEOMETRY_INSTANCE_FB):
				return "XR_OBJECT_TYPE_GEOMETRY_INSTANCE_FB";
				break;
			#endif /*  defined(XR_FB_passthrough)  */
			#if defined(XR_FB_spatial_entity_user)
			case(XR_OBJECT_TYPE_SPACE_USER_FB):
				return "XR_OBJECT_TYPE_SPACE_USER_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_user)  */
			#if defined(XR_FB_triangle_mesh)
			case(XR_OBJECT_TYPE_TRIANGLE_MESH_FB):
				return "XR_OBJECT_TYPE_TRIANGLE_MESH_FB";
				break;
			#endif /*  defined(XR_FB_triangle_mesh)  */
			#if defined(XR_HTC_body_tracking)
			case(XR_OBJECT_TYPE_BODY_TRACKER_HTC):
				return "XR_OBJECT_TYPE_BODY_TRACKER_HTC";
				break;
			#endif /*  defined(XR_HTC_body_tracking)  */
			#if defined(XR_HTC_facial_tracking)
			case(XR_OBJECT_TYPE_FACIAL_TRACKER_HTC):
				return "XR_OBJECT_TYPE_FACIAL_TRACKER_HTC";
				break;
			#endif /*  defined(XR_HTC_facial_tracking)  */
			#if defined(XR_HTC_passthrough)
			case(XR_OBJECT_TYPE_PASSTHROUGH_HTC):
				return "XR_OBJECT_TYPE_PASSTHROUGH_HTC";
				break;
			#endif /*  defined(XR_HTC_passthrough)  */
			#if defined(XR_META_environment_depth)
			case(XR_OBJECT_TYPE_ENVIRONMENT_DEPTH_PROVIDER_META):
				return "XR_OBJECT_TYPE_ENVIRONMENT_DEPTH_PROVIDER_META";
				break;
			case(XR_OBJECT_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_META):
				return "XR_OBJECT_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_META";
				break;
			#endif /*  defined(XR_META_environment_depth)  */
			#if defined(XR_META_passthrough_color_lut)
			case(XR_OBJECT_TYPE_PASSTHROUGH_COLOR_LUT_META):
				return "XR_OBJECT_TYPE_PASSTHROUGH_COLOR_LUT_META";
				break;
			#endif /*  defined(XR_META_passthrough_color_lut)  */
			#if defined(XR_META_virtual_keyboard)
			case(XR_OBJECT_TYPE_VIRTUAL_KEYBOARD_META):
				return "XR_OBJECT_TYPE_VIRTUAL_KEYBOARD_META";
				break;
			#endif /*  defined(XR_META_virtual_keyboard)  */
			#if defined(XR_ML_localization_map)
			case(XR_OBJECT_TYPE_EXPORTED_LOCALIZATION_MAP_ML):
				return "XR_OBJECT_TYPE_EXPORTED_LOCALIZATION_MAP_ML";
				break;
			#endif /*  defined(XR_ML_localization_map)  */
			#if defined(XR_ML_marker_understanding)
			case(XR_OBJECT_TYPE_MARKER_DETECTOR_ML):
				return "XR_OBJECT_TYPE_MARKER_DETECTOR_ML";
				break;
			#endif /*  defined(XR_ML_marker_understanding)  */
			#if defined(XR_ML_spatial_anchors_storage)
			case(XR_OBJECT_TYPE_SPATIAL_ANCHORS_STORAGE_ML):
				return "XR_OBJECT_TYPE_SPATIAL_ANCHORS_STORAGE_ML";
				break;
			#endif /*  defined(XR_ML_spatial_anchors_storage)  */
			#if defined(XR_ML_world_mesh_detection)
			case(XR_OBJECT_TYPE_WORLD_MESH_DETECTOR_ML):
				return "XR_OBJECT_TYPE_WORLD_MESH_DETECTOR_ML";
				break;
			#endif /*  defined(XR_ML_world_mesh_detection)  */
			#if defined(XR_MSFT_scene_understanding)
			case(XR_OBJECT_TYPE_SCENE_OBSERVER_MSFT):
				return "XR_OBJECT_TYPE_SCENE_OBSERVER_MSFT";
				break;
			case(XR_OBJECT_TYPE_SCENE_MSFT):
				return "XR_OBJECT_TYPE_SCENE_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_understanding)  */
			#if defined(XR_MSFT_spatial_anchor)
			case(XR_OBJECT_TYPE_SPATIAL_ANCHOR_MSFT):
				return "XR_OBJECT_TYPE_SPATIAL_ANCHOR_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_anchor)  */
			#if defined(XR_MSFT_spatial_anchor_persistence)
			case(XR_OBJECT_TYPE_SPATIAL_ANCHOR_STORE_CONNECTION_MSFT):
				return "XR_OBJECT_TYPE_SPATIAL_ANCHOR_STORE_CONNECTION_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_anchor_persistence)  */
			#if defined(XR_MSFT_spatial_graph_bridge)
			case(XR_OBJECT_TYPE_SPATIAL_GRAPH_NODE_BINDING_MSFT):
				return "XR_OBJECT_TYPE_SPATIAL_GRAPH_NODE_BINDING_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_graph_bridge)  */
			default:
				return "XrObjectType_TOSTR_ERROR";

		}

	}

	#endif

	const char* vtostr8_XrPassthroughLayerPurposeFB(XrPassthroughLayerPurposeFB In){
		switch(In){
			case(XR_PASSTHROUGH_LAYER_PURPOSE_RECONSTRUCTION_FB):
				return "XR_PASSTHROUGH_LAYER_PURPOSE_RECONSTRUCTION_FB";
				break;
			case(XR_PASSTHROUGH_LAYER_PURPOSE_PROJECTED_FB):
				return "XR_PASSTHROUGH_LAYER_PURPOSE_PROJECTED_FB";
				break;
			#if defined(XR_FB_passthrough_keyboard_hands)
			case(XR_PASSTHROUGH_LAYER_PURPOSE_TRACKED_KEYBOARD_HANDS_FB):
				return "XR_PASSTHROUGH_LAYER_PURPOSE_TRACKED_KEYBOARD_HANDS_FB";
				break;
			case(XR_PASSTHROUGH_LAYER_PURPOSE_TRACKED_KEYBOARD_MASKED_HANDS_FB):
				return "XR_PASSTHROUGH_LAYER_PURPOSE_TRACKED_KEYBOARD_MASKED_HANDS_FB";
				break;
			#endif /*  defined(XR_FB_passthrough_keyboard_hands)  */
			default:
				return "XrPassthroughLayerPurposeFB_TOSTR_ERROR";

		}

	}

	#if defined(XR_EXT_hand_tracking)
	const char* vtostr8_XrHandJointSetEXT(XrHandJointSetEXT In){
		switch(In){
			case(XR_HAND_JOINT_SET_DEFAULT_EXT):
				return "XR_HAND_JOINT_SET_DEFAULT_EXT";
				break;
			#if defined(XR_ULTRALEAP_hand_tracking_forearm)
			case(XR_HAND_JOINT_SET_HAND_WITH_FOREARM_ULTRALEAP):
				return "XR_HAND_JOINT_SET_HAND_WITH_FOREARM_ULTRALEAP";
				break;
			#endif /*  defined(XR_ULTRALEAP_hand_tracking_forearm)  */
			default:
				return "XrHandJointSetEXT_TOSTR_ERROR";

		}

	}

	#endif

	const char* vtostr8_XrViewConfigurationType(XrViewConfigurationType In){
		switch(In){
			case(XR_VIEW_CONFIGURATION_TYPE_PRIMARY_MONO):
				return "XR_VIEW_CONFIGURATION_TYPE_PRIMARY_MONO";
				break;
			case(XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO):
				return "XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO";
				break;
			#if defined(XR_MSFT_first_person_observer)
			case(XR_VIEW_CONFIGURATION_TYPE_SECONDARY_MONO_FIRST_PERSON_OBSERVER_MSFT):
				return "XR_VIEW_CONFIGURATION_TYPE_SECONDARY_MONO_FIRST_PERSON_OBSERVER_MSFT";
				break;
			#endif /*  defined(XR_MSFT_first_person_observer)  */
			default:
				return "XrViewConfigurationType_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrReferenceSpaceType(XrReferenceSpaceType In){
		switch(In){
			case(XR_REFERENCE_SPACE_TYPE_VIEW):
				return "XR_REFERENCE_SPACE_TYPE_VIEW";
				break;
			case(XR_REFERENCE_SPACE_TYPE_LOCAL):
				return "XR_REFERENCE_SPACE_TYPE_LOCAL";
				break;
			case(XR_REFERENCE_SPACE_TYPE_STAGE):
				return "XR_REFERENCE_SPACE_TYPE_STAGE";
				break;
			#if defined(XR_ML_localization_map)
			case(XR_REFERENCE_SPACE_TYPE_LOCALIZATION_MAP_ML):
				return "XR_REFERENCE_SPACE_TYPE_LOCALIZATION_MAP_ML";
				break;
			#endif /*  defined(XR_ML_localization_map)  */
			#if defined(XR_MSFT_unbounded_reference_space)
			case(XR_REFERENCE_SPACE_TYPE_UNBOUNDED_MSFT):
				return "XR_REFERENCE_SPACE_TYPE_UNBOUNDED_MSFT";
				break;
			#endif /*  defined(XR_MSFT_unbounded_reference_space)  */
			#if defined(XR_VARJO_foveated_rendering)
			case(XR_REFERENCE_SPACE_TYPE_COMBINED_EYE_VARJO):
				return "XR_REFERENCE_SPACE_TYPE_COMBINED_EYE_VARJO";
				break;
			#endif /*  defined(XR_VARJO_foveated_rendering)  */
			default:
				return "XrReferenceSpaceType_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrResult(XrResult In){
		switch(In){
			case(XR_SUCCESS):
				return "XR_SUCCESS";
				break;
			case(XR_TIMEOUT_EXPIRED):
				return "XR_TIMEOUT_EXPIRED";
				break;
			case(XR_SESSION_LOSS_PENDING):
				return "XR_SESSION_LOSS_PENDING";
				break;
			case(XR_EVENT_UNAVAILABLE):
				return "XR_EVENT_UNAVAILABLE";
				break;
			case(XR_SPACE_BOUNDS_UNAVAILABLE):
				return "XR_SPACE_BOUNDS_UNAVAILABLE";
				break;
			case(XR_SESSION_NOT_FOCUSED):
				return "XR_SESSION_NOT_FOCUSED";
				break;
			case(XR_FRAME_DISCARDED):
				return "XR_FRAME_DISCARDED";
				break;
			case(XR_ERROR_VALIDATION_FAILURE):
				return "XR_ERROR_VALIDATION_FAILURE";
				break;
			case(XR_ERROR_RUNTIME_FAILURE):
				return "XR_ERROR_RUNTIME_FAILURE";
				break;
			case(XR_ERROR_OUT_OF_MEMORY):
				return "XR_ERROR_OUT_OF_MEMORY";
				break;
			case(XR_ERROR_API_VERSION_UNSUPPORTED):
				return "XR_ERROR_API_VERSION_UNSUPPORTED";
				break;
			case(XR_ERROR_INITIALIZATION_FAILED):
				return "XR_ERROR_INITIALIZATION_FAILED";
				break;
			case(XR_ERROR_FUNCTION_UNSUPPORTED):
				return "XR_ERROR_FUNCTION_UNSUPPORTED";
				break;
			case(XR_ERROR_FEATURE_UNSUPPORTED):
				return "XR_ERROR_FEATURE_UNSUPPORTED";
				break;
			case(XR_ERROR_EXTENSION_NOT_PRESENT):
				return "XR_ERROR_EXTENSION_NOT_PRESENT";
				break;
			case(XR_ERROR_LIMIT_REACHED):
				return "XR_ERROR_LIMIT_REACHED";
				break;
			case(XR_ERROR_SIZE_INSUFFICIENT):
				return "XR_ERROR_SIZE_INSUFFICIENT";
				break;
			case(XR_ERROR_HANDLE_INVALID):
				return "XR_ERROR_HANDLE_INVALID";
				break;
			case(XR_ERROR_INSTANCE_LOST):
				return "XR_ERROR_INSTANCE_LOST";
				break;
			case(XR_ERROR_SESSION_RUNNING):
				return "XR_ERROR_SESSION_RUNNING";
				break;
			case(XR_ERROR_SESSION_NOT_RUNNING):
				return "XR_ERROR_SESSION_NOT_RUNNING";
				break;
			case(XR_ERROR_SESSION_LOST):
				return "XR_ERROR_SESSION_LOST";
				break;
			case(XR_ERROR_SYSTEM_INVALID):
				return "XR_ERROR_SYSTEM_INVALID";
				break;
			case(XR_ERROR_PATH_INVALID):
				return "XR_ERROR_PATH_INVALID";
				break;
			case(XR_ERROR_PATH_COUNT_EXCEEDED):
				return "XR_ERROR_PATH_COUNT_EXCEEDED";
				break;
			case(XR_ERROR_PATH_FORMAT_INVALID):
				return "XR_ERROR_PATH_FORMAT_INVALID";
				break;
			case(XR_ERROR_PATH_UNSUPPORTED):
				return "XR_ERROR_PATH_UNSUPPORTED";
				break;
			case(XR_ERROR_LAYER_INVALID):
				return "XR_ERROR_LAYER_INVALID";
				break;
			case(XR_ERROR_LAYER_LIMIT_EXCEEDED):
				return "XR_ERROR_LAYER_LIMIT_EXCEEDED";
				break;
			case(XR_ERROR_SWAPCHAIN_RECT_INVALID):
				return "XR_ERROR_SWAPCHAIN_RECT_INVALID";
				break;
			case(XR_ERROR_SWAPCHAIN_FORMAT_UNSUPPORTED):
				return "XR_ERROR_SWAPCHAIN_FORMAT_UNSUPPORTED";
				break;
			case(XR_ERROR_ACTION_TYPE_MISMATCH):
				return "XR_ERROR_ACTION_TYPE_MISMATCH";
				break;
			case(XR_ERROR_SESSION_NOT_READY):
				return "XR_ERROR_SESSION_NOT_READY";
				break;
			case(XR_ERROR_SESSION_NOT_STOPPING):
				return "XR_ERROR_SESSION_NOT_STOPPING";
				break;
			case(XR_ERROR_TIME_INVALID):
				return "XR_ERROR_TIME_INVALID";
				break;
			case(XR_ERROR_REFERENCE_SPACE_UNSUPPORTED):
				return "XR_ERROR_REFERENCE_SPACE_UNSUPPORTED";
				break;
			case(XR_ERROR_FILE_ACCESS_ERROR):
				return "XR_ERROR_FILE_ACCESS_ERROR";
				break;
			case(XR_ERROR_FILE_CONTENTS_INVALID):
				return "XR_ERROR_FILE_CONTENTS_INVALID";
				break;
			case(XR_ERROR_FORM_FACTOR_UNSUPPORTED):
				return "XR_ERROR_FORM_FACTOR_UNSUPPORTED";
				break;
			case(XR_ERROR_FORM_FACTOR_UNAVAILABLE):
				return "XR_ERROR_FORM_FACTOR_UNAVAILABLE";
				break;
			case(XR_ERROR_API_LAYER_NOT_PRESENT):
				return "XR_ERROR_API_LAYER_NOT_PRESENT";
				break;
			case(XR_ERROR_CALL_ORDER_INVALID):
				return "XR_ERROR_CALL_ORDER_INVALID";
				break;
			case(XR_ERROR_GRAPHICS_DEVICE_INVALID):
				return "XR_ERROR_GRAPHICS_DEVICE_INVALID";
				break;
			case(XR_ERROR_POSE_INVALID):
				return "XR_ERROR_POSE_INVALID";
				break;
			case(XR_ERROR_INDEX_OUT_OF_RANGE):
				return "XR_ERROR_INDEX_OUT_OF_RANGE";
				break;
			case(XR_ERROR_VIEW_CONFIGURATION_TYPE_UNSUPPORTED):
				return "XR_ERROR_VIEW_CONFIGURATION_TYPE_UNSUPPORTED";
				break;
			case(XR_ERROR_ENVIRONMENT_BLEND_MODE_UNSUPPORTED):
				return "XR_ERROR_ENVIRONMENT_BLEND_MODE_UNSUPPORTED";
				break;
			case(XR_ERROR_NAME_DUPLICATED):
				return "XR_ERROR_NAME_DUPLICATED";
				break;
			case(XR_ERROR_NAME_INVALID):
				return "XR_ERROR_NAME_INVALID";
				break;
			case(XR_ERROR_ACTIONSET_NOT_ATTACHED):
				return "XR_ERROR_ACTIONSET_NOT_ATTACHED";
				break;
			case(XR_ERROR_ACTIONSETS_ALREADY_ATTACHED):
				return "XR_ERROR_ACTIONSETS_ALREADY_ATTACHED";
				break;
			case(XR_ERROR_LOCALIZED_NAME_DUPLICATED):
				return "XR_ERROR_LOCALIZED_NAME_DUPLICATED";
				break;
			case(XR_ERROR_LOCALIZED_NAME_INVALID):
				return "XR_ERROR_LOCALIZED_NAME_INVALID";
				break;
			case(XR_ERROR_GRAPHICS_REQUIREMENTS_CALL_MISSING):
				return "XR_ERROR_GRAPHICS_REQUIREMENTS_CALL_MISSING";
				break;
			case(XR_ERROR_RUNTIME_UNAVAILABLE):
				return "XR_ERROR_RUNTIME_UNAVAILABLE";
				break;
			#if defined(XR_EXT_future)
			case(XR_ERROR_FUTURE_PENDING_EXT):
				return "XR_ERROR_FUTURE_PENDING_EXT";
				break;
			case(XR_ERROR_FUTURE_INVALID_EXT):
				return "XR_ERROR_FUTURE_INVALID_EXT";
				break;
			#endif /*  defined(XR_EXT_future)  */
			#if defined(XR_EXT_plane_detection)
			case(XR_ERROR_SPACE_NOT_LOCATABLE_EXT):
				return "XR_ERROR_SPACE_NOT_LOCATABLE_EXT";
				break;
			case(XR_ERROR_PLANE_DETECTION_PERMISSION_DENIED_EXT):
				return "XR_ERROR_PLANE_DETECTION_PERMISSION_DENIED_EXT";
				break;
			#endif /*  defined(XR_EXT_plane_detection)  */
			#if defined(XR_FB_color_space)
			case(XR_ERROR_COLOR_SPACE_UNSUPPORTED_FB):
				return "XR_ERROR_COLOR_SPACE_UNSUPPORTED_FB";
				break;
			#endif /*  defined(XR_FB_color_space)  */
			#if defined(XR_FB_display_refresh_rate)
			case(XR_ERROR_DISPLAY_REFRESH_RATE_UNSUPPORTED_FB):
				return "XR_ERROR_DISPLAY_REFRESH_RATE_UNSUPPORTED_FB";
				break;
			#endif /*  defined(XR_FB_display_refresh_rate)  */
			#if defined(XR_FB_passthrough)
			case(XR_ERROR_UNEXPECTED_STATE_PASSTHROUGH_FB):
				return "XR_ERROR_UNEXPECTED_STATE_PASSTHROUGH_FB";
				break;
			case(XR_ERROR_FEATURE_ALREADY_CREATED_PASSTHROUGH_FB):
				return "XR_ERROR_FEATURE_ALREADY_CREATED_PASSTHROUGH_FB";
				break;
			case(XR_ERROR_FEATURE_REQUIRED_PASSTHROUGH_FB):
				return "XR_ERROR_FEATURE_REQUIRED_PASSTHROUGH_FB";
				break;
			case(XR_ERROR_NOT_PERMITTED_PASSTHROUGH_FB):
				return "XR_ERROR_NOT_PERMITTED_PASSTHROUGH_FB";
				break;
			case(XR_ERROR_INSUFFICIENT_RESOURCES_PASSTHROUGH_FB):
				return "XR_ERROR_INSUFFICIENT_RESOURCES_PASSTHROUGH_FB";
				break;
			case(XR_ERROR_UNKNOWN_PASSTHROUGH_FB):
				return "XR_ERROR_UNKNOWN_PASSTHROUGH_FB";
				break;
			#endif /*  defined(XR_FB_passthrough)  */
			#if defined(XR_FB_render_model)
			case(XR_ERROR_RENDER_MODEL_KEY_INVALID_FB):
				return "XR_ERROR_RENDER_MODEL_KEY_INVALID_FB";
				break;
			case(XR_RENDER_MODEL_UNAVAILABLE_FB):
				return "XR_RENDER_MODEL_UNAVAILABLE_FB";
				break;
			#endif /*  defined(XR_FB_render_model)  */
			#if defined(XR_FB_spatial_entity)
			case(XR_ERROR_SPACE_COMPONENT_NOT_SUPPORTED_FB):
				return "XR_ERROR_SPACE_COMPONENT_NOT_SUPPORTED_FB";
				break;
			case(XR_ERROR_SPACE_COMPONENT_NOT_ENABLED_FB):
				return "XR_ERROR_SPACE_COMPONENT_NOT_ENABLED_FB";
				break;
			case(XR_ERROR_SPACE_COMPONENT_STATUS_PENDING_FB):
				return "XR_ERROR_SPACE_COMPONENT_STATUS_PENDING_FB";
				break;
			case(XR_ERROR_SPACE_COMPONENT_STATUS_ALREADY_SET_FB):
				return "XR_ERROR_SPACE_COMPONENT_STATUS_ALREADY_SET_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity)  */
			#if defined(XR_FB_spatial_entity_sharing)
			case(XR_ERROR_SPACE_MAPPING_INSUFFICIENT_FB):
				return "XR_ERROR_SPACE_MAPPING_INSUFFICIENT_FB";
				break;
			case(XR_ERROR_SPACE_LOCALIZATION_FAILED_FB):
				return "XR_ERROR_SPACE_LOCALIZATION_FAILED_FB";
				break;
			case(XR_ERROR_SPACE_NETWORK_TIMEOUT_FB):
				return "XR_ERROR_SPACE_NETWORK_TIMEOUT_FB";
				break;
			case(XR_ERROR_SPACE_NETWORK_REQUEST_FAILED_FB):
				return "XR_ERROR_SPACE_NETWORK_REQUEST_FAILED_FB";
				break;
			case(XR_ERROR_SPACE_CLOUD_STORAGE_DISABLED_FB):
				return "XR_ERROR_SPACE_CLOUD_STORAGE_DISABLED_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_sharing)  */
			#if defined(XR_HTC_anchor)
			case(XR_ERROR_NOT_AN_ANCHOR_HTC):
				return "XR_ERROR_NOT_AN_ANCHOR_HTC";
				break;
			#endif /*  defined(XR_HTC_anchor)  */
			#if defined(XR_KHR_android_thread_settings)
			case(XR_ERROR_ANDROID_THREAD_SETTINGS_ID_INVALID_KHR):
				return "XR_ERROR_ANDROID_THREAD_SETTINGS_ID_INVALID_KHR";
				break;
			case(XR_ERROR_ANDROID_THREAD_SETTINGS_FAILURE_KHR):
				return "XR_ERROR_ANDROID_THREAD_SETTINGS_FAILURE_KHR";
				break;
			#endif /*  defined(XR_KHR_android_thread_settings)  */
			#if defined(XR_META_environment_depth)
			case(XR_ENVIRONMENT_DEPTH_NOT_AVAILABLE_META):
				return "XR_ENVIRONMENT_DEPTH_NOT_AVAILABLE_META";
				break;
			#endif /*  defined(XR_META_environment_depth)  */
			#if defined(XR_META_passthrough_color_lut)
			case(XR_ERROR_PASSTHROUGH_COLOR_LUT_BUFFER_SIZE_MISMATCH_META):
				return "XR_ERROR_PASSTHROUGH_COLOR_LUT_BUFFER_SIZE_MISMATCH_META";
				break;
			#endif /*  defined(XR_META_passthrough_color_lut)  */
			#if defined(XR_ML_localization_map)
			case(XR_ERROR_LOCALIZATION_MAP_INCOMPATIBLE_ML):
				return "XR_ERROR_LOCALIZATION_MAP_INCOMPATIBLE_ML";
				break;
			case(XR_ERROR_LOCALIZATION_MAP_UNAVAILABLE_ML):
				return "XR_ERROR_LOCALIZATION_MAP_UNAVAILABLE_ML";
				break;
			case(XR_ERROR_LOCALIZATION_MAP_FAIL_ML):
				return "XR_ERROR_LOCALIZATION_MAP_FAIL_ML";
				break;
			case(XR_ERROR_LOCALIZATION_MAP_IMPORT_EXPORT_PERMISSION_DENIED_ML):
				return "XR_ERROR_LOCALIZATION_MAP_IMPORT_EXPORT_PERMISSION_DENIED_ML";
				break;
			case(XR_ERROR_LOCALIZATION_MAP_PERMISSION_DENIED_ML):
				return "XR_ERROR_LOCALIZATION_MAP_PERMISSION_DENIED_ML";
				break;
			case(XR_ERROR_LOCALIZATION_MAP_ALREADY_EXISTS_ML):
				return "XR_ERROR_LOCALIZATION_MAP_ALREADY_EXISTS_ML";
				break;
			case(XR_ERROR_LOCALIZATION_MAP_CANNOT_EXPORT_CLOUD_MAP_ML):
				return "XR_ERROR_LOCALIZATION_MAP_CANNOT_EXPORT_CLOUD_MAP_ML";
				break;
			#endif /*  defined(XR_ML_localization_map)  */
			#if defined(XR_ML_marker_understanding)
			case(XR_ERROR_MARKER_DETECTOR_PERMISSION_DENIED_ML):
				return "XR_ERROR_MARKER_DETECTOR_PERMISSION_DENIED_ML";
				break;
			case(XR_ERROR_MARKER_DETECTOR_LOCATE_FAILED_ML):
				return "XR_ERROR_MARKER_DETECTOR_LOCATE_FAILED_ML";
				break;
			case(XR_ERROR_MARKER_DETECTOR_INVALID_DATA_QUERY_ML):
				return "XR_ERROR_MARKER_DETECTOR_INVALID_DATA_QUERY_ML";
				break;
			case(XR_ERROR_MARKER_DETECTOR_INVALID_CREATE_INFO_ML):
				return "XR_ERROR_MARKER_DETECTOR_INVALID_CREATE_INFO_ML";
				break;
			case(XR_ERROR_MARKER_INVALID_ML):
				return "XR_ERROR_MARKER_INVALID_ML";
				break;
			#endif /*  defined(XR_ML_marker_understanding)  */
			#if defined(XR_ML_spatial_anchors)
			case(XR_ERROR_SPATIAL_ANCHORS_PERMISSION_DENIED_ML):
				return "XR_ERROR_SPATIAL_ANCHORS_PERMISSION_DENIED_ML";
				break;
			case(XR_ERROR_SPATIAL_ANCHORS_NOT_LOCALIZED_ML):
				return "XR_ERROR_SPATIAL_ANCHORS_NOT_LOCALIZED_ML";
				break;
			case(XR_ERROR_SPATIAL_ANCHORS_OUT_OF_MAP_BOUNDS_ML):
				return "XR_ERROR_SPATIAL_ANCHORS_OUT_OF_MAP_BOUNDS_ML";
				break;
			case(XR_ERROR_SPATIAL_ANCHORS_SPACE_NOT_LOCATABLE_ML):
				return "XR_ERROR_SPATIAL_ANCHORS_SPACE_NOT_LOCATABLE_ML";
				break;
			#endif /*  defined(XR_ML_spatial_anchors)  */
			#if defined(XR_ML_spatial_anchors_storage)
			case(XR_ERROR_SPATIAL_ANCHORS_ANCHOR_NOT_FOUND_ML):
				return "XR_ERROR_SPATIAL_ANCHORS_ANCHOR_NOT_FOUND_ML";
				break;
			#endif /*  defined(XR_ML_spatial_anchors_storage)  */
			#if defined(XR_ML_system_notifications)
			case(XR_ERROR_SYSTEM_NOTIFICATION_PERMISSION_DENIED_ML):
				return "XR_ERROR_SYSTEM_NOTIFICATION_PERMISSION_DENIED_ML";
				break;
			case(XR_ERROR_SYSTEM_NOTIFICATION_INCOMPATIBLE_SKU_ML):
				return "XR_ERROR_SYSTEM_NOTIFICATION_INCOMPATIBLE_SKU_ML";
				break;
			#endif /*  defined(XR_ML_system_notifications)  */
			#if defined(XR_ML_world_mesh_detection)
			case(XR_ERROR_WORLD_MESH_DETECTOR_PERMISSION_DENIED_ML):
				return "XR_ERROR_WORLD_MESH_DETECTOR_PERMISSION_DENIED_ML";
				break;
			case(XR_ERROR_WORLD_MESH_DETECTOR_SPACE_NOT_LOCATABLE_ML):
				return "XR_ERROR_WORLD_MESH_DETECTOR_SPACE_NOT_LOCATABLE_ML";
				break;
			#endif /*  defined(XR_ML_world_mesh_detection)  */
			#if defined(XR_MSFT_composition_layer_reprojection)
			case(XR_ERROR_REPROJECTION_MODE_UNSUPPORTED_MSFT):
				return "XR_ERROR_REPROJECTION_MODE_UNSUPPORTED_MSFT";
				break;
			#endif /*  defined(XR_MSFT_composition_layer_reprojection)  */
			#if defined(XR_MSFT_controller_model)
			case(XR_ERROR_CONTROLLER_MODEL_KEY_INVALID_MSFT):
				return "XR_ERROR_CONTROLLER_MODEL_KEY_INVALID_MSFT";
				break;
			#endif /*  defined(XR_MSFT_controller_model)  */
			#if defined(XR_MSFT_scene_marker)
			case(XR_SCENE_MARKER_DATA_NOT_STRING_MSFT):
				return "XR_SCENE_MARKER_DATA_NOT_STRING_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_marker)  */
			#if defined(XR_MSFT_scene_understanding)
			case(XR_ERROR_COMPUTE_NEW_SCENE_NOT_COMPLETED_MSFT):
				return "XR_ERROR_COMPUTE_NEW_SCENE_NOT_COMPLETED_MSFT";
				break;
			case(XR_ERROR_SCENE_COMPONENT_ID_INVALID_MSFT):
				return "XR_ERROR_SCENE_COMPONENT_ID_INVALID_MSFT";
				break;
			case(XR_ERROR_SCENE_COMPONENT_TYPE_MISMATCH_MSFT):
				return "XR_ERROR_SCENE_COMPONENT_TYPE_MISMATCH_MSFT";
				break;
			case(XR_ERROR_SCENE_MESH_BUFFER_ID_INVALID_MSFT):
				return "XR_ERROR_SCENE_MESH_BUFFER_ID_INVALID_MSFT";
				break;
			case(XR_ERROR_SCENE_COMPUTE_FEATURE_INCOMPATIBLE_MSFT):
				return "XR_ERROR_SCENE_COMPUTE_FEATURE_INCOMPATIBLE_MSFT";
				break;
			case(XR_ERROR_SCENE_COMPUTE_CONSISTENCY_MISMATCH_MSFT):
				return "XR_ERROR_SCENE_COMPUTE_CONSISTENCY_MISMATCH_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_understanding)  */
			#if defined(XR_MSFT_secondary_view_configuration)
			case(XR_ERROR_SECONDARY_VIEW_CONFIGURATION_TYPE_NOT_ENABLED_MSFT):
				return "XR_ERROR_SECONDARY_VIEW_CONFIGURATION_TYPE_NOT_ENABLED_MSFT";
				break;
			#endif /*  defined(XR_MSFT_secondary_view_configuration)  */
			#if defined(XR_MSFT_spatial_anchor)
			case(XR_ERROR_CREATE_SPATIAL_ANCHOR_FAILED_MSFT):
				return "XR_ERROR_CREATE_SPATIAL_ANCHOR_FAILED_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_anchor)  */
			#if defined(XR_MSFT_spatial_anchor_persistence)
			case(XR_ERROR_SPATIAL_ANCHOR_NAME_NOT_FOUND_MSFT):
				return "XR_ERROR_SPATIAL_ANCHOR_NAME_NOT_FOUND_MSFT";
				break;
			case(XR_ERROR_SPATIAL_ANCHOR_NAME_INVALID_MSFT):
				return "XR_ERROR_SPATIAL_ANCHOR_NAME_INVALID_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_anchor_persistence)  */
			#if defined(XR_QCOM_tracking_optimization_settings)
			case(XR_ERROR_HINT_ALREADY_SET_QCOM):
				return "XR_ERROR_HINT_ALREADY_SET_QCOM";
				break;
			#endif /*  defined(XR_QCOM_tracking_optimization_settings)  */
			#if defined(XR_VARJO_marker_tracking)
			case(XR_ERROR_MARKER_NOT_TRACKED_VARJO):
				return "XR_ERROR_MARKER_NOT_TRACKED_VARJO";
				break;
			case(XR_ERROR_MARKER_ID_INVALID_VARJO):
				return "XR_ERROR_MARKER_ID_INVALID_VARJO";
				break;
			#endif /*  defined(XR_VARJO_marker_tracking)  */
			default:
				return "XrResult_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrStructureType(XrStructureType In){
		switch(In){
			case(XR_TYPE_UNKNOWN):
				return "XR_TYPE_UNKNOWN";
				break;
			case(XR_TYPE_API_LAYER_PROPERTIES):
				return "XR_TYPE_API_LAYER_PROPERTIES";
				break;
			case(XR_TYPE_EXTENSION_PROPERTIES):
				return "XR_TYPE_EXTENSION_PROPERTIES";
				break;
			case(XR_TYPE_INSTANCE_CREATE_INFO):
				return "XR_TYPE_INSTANCE_CREATE_INFO";
				break;
			case(XR_TYPE_SYSTEM_GET_INFO):
				return "XR_TYPE_SYSTEM_GET_INFO";
				break;
			case(XR_TYPE_SYSTEM_PROPERTIES):
				return "XR_TYPE_SYSTEM_PROPERTIES";
				break;
			case(XR_TYPE_VIEW_LOCATE_INFO):
				return "XR_TYPE_VIEW_LOCATE_INFO";
				break;
			case(XR_TYPE_VIEW):
				return "XR_TYPE_VIEW";
				break;
			case(XR_TYPE_SESSION_CREATE_INFO):
				return "XR_TYPE_SESSION_CREATE_INFO";
				break;
			case(XR_TYPE_SWAPCHAIN_CREATE_INFO):
				return "XR_TYPE_SWAPCHAIN_CREATE_INFO";
				break;
			case(XR_TYPE_SESSION_BEGIN_INFO):
				return "XR_TYPE_SESSION_BEGIN_INFO";
				break;
			case(XR_TYPE_VIEW_STATE):
				return "XR_TYPE_VIEW_STATE";
				break;
			case(XR_TYPE_FRAME_END_INFO):
				return "XR_TYPE_FRAME_END_INFO";
				break;
			case(XR_TYPE_HAPTIC_VIBRATION):
				return "XR_TYPE_HAPTIC_VIBRATION";
				break;
			case(XR_TYPE_EVENT_DATA_BUFFER):
				return "XR_TYPE_EVENT_DATA_BUFFER";
				break;
			case(XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING):
				return "XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING";
				break;
			case(XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED):
				return "XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED";
				break;
			case(XR_TYPE_ACTION_STATE_BOOLEAN):
				return "XR_TYPE_ACTION_STATE_BOOLEAN";
				break;
			case(XR_TYPE_ACTION_STATE_FLOAT):
				return "XR_TYPE_ACTION_STATE_FLOAT";
				break;
			case(XR_TYPE_ACTION_STATE_VECTOR2F):
				return "XR_TYPE_ACTION_STATE_VECTOR2F";
				break;
			case(XR_TYPE_ACTION_STATE_POSE):
				return "XR_TYPE_ACTION_STATE_POSE";
				break;
			case(XR_TYPE_ACTION_SET_CREATE_INFO):
				return "XR_TYPE_ACTION_SET_CREATE_INFO";
				break;
			case(XR_TYPE_ACTION_CREATE_INFO):
				return "XR_TYPE_ACTION_CREATE_INFO";
				break;
			case(XR_TYPE_INSTANCE_PROPERTIES):
				return "XR_TYPE_INSTANCE_PROPERTIES";
				break;
			case(XR_TYPE_FRAME_WAIT_INFO):
				return "XR_TYPE_FRAME_WAIT_INFO";
				break;
			case(XR_TYPE_COMPOSITION_LAYER_PROJECTION):
				return "XR_TYPE_COMPOSITION_LAYER_PROJECTION";
				break;
			case(XR_TYPE_COMPOSITION_LAYER_QUAD):
				return "XR_TYPE_COMPOSITION_LAYER_QUAD";
				break;
			case(XR_TYPE_REFERENCE_SPACE_CREATE_INFO):
				return "XR_TYPE_REFERENCE_SPACE_CREATE_INFO";
				break;
			case(XR_TYPE_ACTION_SPACE_CREATE_INFO):
				return "XR_TYPE_ACTION_SPACE_CREATE_INFO";
				break;
			case(XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING):
				return "XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING";
				break;
			case(XR_TYPE_VIEW_CONFIGURATION_VIEW):
				return "XR_TYPE_VIEW_CONFIGURATION_VIEW";
				break;
			case(XR_TYPE_SPACE_LOCATION):
				return "XR_TYPE_SPACE_LOCATION";
				break;
			case(XR_TYPE_SPACE_VELOCITY):
				return "XR_TYPE_SPACE_VELOCITY";
				break;
			case(XR_TYPE_FRAME_STATE):
				return "XR_TYPE_FRAME_STATE";
				break;
			case(XR_TYPE_VIEW_CONFIGURATION_PROPERTIES):
				return "XR_TYPE_VIEW_CONFIGURATION_PROPERTIES";
				break;
			case(XR_TYPE_FRAME_BEGIN_INFO):
				return "XR_TYPE_FRAME_BEGIN_INFO";
				break;
			case(XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW):
				return "XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW";
				break;
			case(XR_TYPE_EVENT_DATA_EVENTS_LOST):
				return "XR_TYPE_EVENT_DATA_EVENTS_LOST";
				break;
			case(XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING):
				return "XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING";
				break;
			case(XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED):
				return "XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED";
				break;
			case(XR_TYPE_INTERACTION_PROFILE_STATE):
				return "XR_TYPE_INTERACTION_PROFILE_STATE";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO):
				return "XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO):
				return "XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO):
				return "XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO";
				break;
			case(XR_TYPE_ACTION_STATE_GET_INFO):
				return "XR_TYPE_ACTION_STATE_GET_INFO";
				break;
			case(XR_TYPE_HAPTIC_ACTION_INFO):
				return "XR_TYPE_HAPTIC_ACTION_INFO";
				break;
			case(XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO):
				return "XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO";
				break;
			case(XR_TYPE_ACTIONS_SYNC_INFO):
				return "XR_TYPE_ACTIONS_SYNC_INFO";
				break;
			case(XR_TYPE_BOUND_SOURCES_FOR_ACTION_ENUMERATE_INFO):
				return "XR_TYPE_BOUND_SOURCES_FOR_ACTION_ENUMERATE_INFO";
				break;
			case(XR_TYPE_INPUT_SOURCE_LOCALIZED_NAME_GET_INFO):
				return "XR_TYPE_INPUT_SOURCE_LOCALIZED_NAME_GET_INFO";
				break;
			#if defined(XR_ALMALENCE_digital_lens_control)
			case(XR_TYPE_DIGITAL_LENS_CONTROL_ALMALENCE):
				return "XR_TYPE_DIGITAL_LENS_CONTROL_ALMALENCE";
				break;
			#endif /*  defined(XR_ALMALENCE_digital_lens_control)  */
			#if defined(XR_EPIC_view_configuration_fov)
			case(XR_TYPE_VIEW_CONFIGURATION_VIEW_FOV_EPIC):
				return "XR_TYPE_VIEW_CONFIGURATION_VIEW_FOV_EPIC";
				break;
			#endif /*  defined(XR_EPIC_view_configuration_fov)  */
			#if defined(XR_EXTX_overlay)
			case(XR_TYPE_SESSION_CREATE_INFO_OVERLAY_EXTX):
				return "XR_TYPE_SESSION_CREATE_INFO_OVERLAY_EXTX";
				break;
			case(XR_TYPE_EVENT_DATA_MAIN_SESSION_VISIBILITY_CHANGED_EXTX):
				return "XR_TYPE_EVENT_DATA_MAIN_SESSION_VISIBILITY_CHANGED_EXTX";
				break;
			#endif /*  defined(XR_EXTX_overlay)  */
			#if defined(XR_EXT_active_action_set_priority)
			case(XR_TYPE_ACTIVE_ACTION_SET_PRIORITIES_EXT):
				return "XR_TYPE_ACTIVE_ACTION_SET_PRIORITIES_EXT";
				break;
			#endif /*  defined(XR_EXT_active_action_set_priority)  */
			#if defined(XR_EXT_debug_utils)
			case(XR_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT):
				return "XR_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT";
				break;
			case(XR_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT):
				return "XR_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT";
				break;
			case(XR_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT):
				return "XR_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT";
				break;
			case(XR_TYPE_DEBUG_UTILS_LABEL_EXT):
				return "XR_TYPE_DEBUG_UTILS_LABEL_EXT";
				break;
			#endif /*  defined(XR_EXT_debug_utils)  */
			#if defined(XR_EXT_dpad_binding)
			case(XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT):
				return "XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT";
				break;
			#endif /*  defined(XR_EXT_dpad_binding)  */
			#if defined(XR_EXT_eye_gaze_interaction)
			case(XR_TYPE_SYSTEM_EYE_GAZE_INTERACTION_PROPERTIES_EXT):
				return "XR_TYPE_SYSTEM_EYE_GAZE_INTERACTION_PROPERTIES_EXT";
				break;
			case(XR_TYPE_EYE_GAZE_SAMPLE_TIME_EXT):
				return "XR_TYPE_EYE_GAZE_SAMPLE_TIME_EXT";
				break;
			#endif /*  defined(XR_EXT_eye_gaze_interaction)  */
			#if defined(XR_EXT_future)
			case(XR_TYPE_FUTURE_CANCEL_INFO_EXT):
				return "XR_TYPE_FUTURE_CANCEL_INFO_EXT";
				break;
			case(XR_TYPE_FUTURE_POLL_INFO_EXT):
				return "XR_TYPE_FUTURE_POLL_INFO_EXT";
				break;
			case(XR_TYPE_FUTURE_COMPLETION_EXT):
				return "XR_TYPE_FUTURE_COMPLETION_EXT";
				break;
			case(XR_TYPE_FUTURE_POLL_RESULT_EXT):
				return "XR_TYPE_FUTURE_POLL_RESULT_EXT";
				break;
			#endif /*  defined(XR_EXT_future)  */
			#if defined(XR_EXT_hand_joints_motion_range)
			case(XR_TYPE_HAND_JOINTS_MOTION_RANGE_INFO_EXT):
				return "XR_TYPE_HAND_JOINTS_MOTION_RANGE_INFO_EXT";
				break;
			#endif /*  defined(XR_EXT_hand_joints_motion_range)  */
			#if defined(XR_EXT_hand_tracking)
			case(XR_TYPE_SYSTEM_HAND_TRACKING_PROPERTIES_EXT):
				return "XR_TYPE_SYSTEM_HAND_TRACKING_PROPERTIES_EXT";
				break;
			case(XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT):
				return "XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT";
				break;
			case(XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT):
				return "XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT";
				break;
			case(XR_TYPE_HAND_JOINT_LOCATIONS_EXT):
				return "XR_TYPE_HAND_JOINT_LOCATIONS_EXT";
				break;
			case(XR_TYPE_HAND_JOINT_VELOCITIES_EXT):
				return "XR_TYPE_HAND_JOINT_VELOCITIES_EXT";
				break;
			#endif /*  defined(XR_EXT_hand_tracking)  */
			#if defined(XR_EXT_hand_tracking_data_source)
			case(XR_TYPE_HAND_TRACKING_DATA_SOURCE_INFO_EXT):
				return "XR_TYPE_HAND_TRACKING_DATA_SOURCE_INFO_EXT";
				break;
			case(XR_TYPE_HAND_TRACKING_DATA_SOURCE_STATE_EXT):
				return "XR_TYPE_HAND_TRACKING_DATA_SOURCE_STATE_EXT";
				break;
			#endif /*  defined(XR_EXT_hand_tracking_data_source)  */
			#if defined(XR_EXT_performance_settings)
			case(XR_TYPE_EVENT_DATA_PERF_SETTINGS_EXT):
				return "XR_TYPE_EVENT_DATA_PERF_SETTINGS_EXT";
				break;
			#endif /*  defined(XR_EXT_performance_settings)  */
			#if defined(XR_EXT_plane_detection)
			case(XR_TYPE_PLANE_DETECTOR_CREATE_INFO_EXT):
				return "XR_TYPE_PLANE_DETECTOR_CREATE_INFO_EXT";
				break;
			case(XR_TYPE_PLANE_DETECTOR_BEGIN_INFO_EXT):
				return "XR_TYPE_PLANE_DETECTOR_BEGIN_INFO_EXT";
				break;
			case(XR_TYPE_PLANE_DETECTOR_GET_INFO_EXT):
				return "XR_TYPE_PLANE_DETECTOR_GET_INFO_EXT";
				break;
			case(XR_TYPE_PLANE_DETECTOR_LOCATIONS_EXT):
				return "XR_TYPE_PLANE_DETECTOR_LOCATIONS_EXT";
				break;
			case(XR_TYPE_PLANE_DETECTOR_LOCATION_EXT):
				return "XR_TYPE_PLANE_DETECTOR_LOCATION_EXT";
				break;
			case(XR_TYPE_PLANE_DETECTOR_POLYGON_BUFFER_EXT):
				return "XR_TYPE_PLANE_DETECTOR_POLYGON_BUFFER_EXT";
				break;
			case(XR_TYPE_SYSTEM_PLANE_DETECTION_PROPERTIES_EXT):
				return "XR_TYPE_SYSTEM_PLANE_DETECTION_PROPERTIES_EXT";
				break;
			#endif /*  defined(XR_EXT_plane_detection)  */
			#if defined(XR_EXT_user_presence)
			case(XR_TYPE_EVENT_DATA_USER_PRESENCE_CHANGED_EXT):
				return "XR_TYPE_EVENT_DATA_USER_PRESENCE_CHANGED_EXT";
				break;
			case(XR_TYPE_SYSTEM_USER_PRESENCE_PROPERTIES_EXT):
				return "XR_TYPE_SYSTEM_USER_PRESENCE_PROPERTIES_EXT";
				break;
			#endif /*  defined(XR_EXT_user_presence)  */
			#if defined(XR_EXT_view_configuration_depth_range)
			case(XR_TYPE_VIEW_CONFIGURATION_DEPTH_RANGE_EXT):
				return "XR_TYPE_VIEW_CONFIGURATION_DEPTH_RANGE_EXT";
				break;
			#endif /*  defined(XR_EXT_view_configuration_depth_range)  */
			#if defined(XR_FB_android_surface_swapchain_create)
			case(XR_TYPE_ANDROID_SURFACE_SWAPCHAIN_CREATE_INFO_FB):
				return "XR_TYPE_ANDROID_SURFACE_SWAPCHAIN_CREATE_INFO_FB";
				break;
			#endif /*  defined(XR_FB_android_surface_swapchain_create)  */
			#if defined(XR_FB_body_tracking)
			case(XR_TYPE_BODY_TRACKER_CREATE_INFO_FB):
				return "XR_TYPE_BODY_TRACKER_CREATE_INFO_FB";
				break;
			case(XR_TYPE_BODY_JOINTS_LOCATE_INFO_FB):
				return "XR_TYPE_BODY_JOINTS_LOCATE_INFO_FB";
				break;
			case(XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_FB):
				return "XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_FB";
				break;
			case(XR_TYPE_BODY_JOINT_LOCATIONS_FB):
				return "XR_TYPE_BODY_JOINT_LOCATIONS_FB";
				break;
			case(XR_TYPE_BODY_SKELETON_FB):
				return "XR_TYPE_BODY_SKELETON_FB";
				break;
			#endif /*  defined(XR_FB_body_tracking)  */
			#if defined(XR_FB_color_space)
			case(XR_TYPE_SYSTEM_COLOR_SPACE_PROPERTIES_FB):
				return "XR_TYPE_SYSTEM_COLOR_SPACE_PROPERTIES_FB";
				break;
			#endif /*  defined(XR_FB_color_space)  */
			#if defined(XR_FB_composition_layer_alpha_blend)
			case(XR_TYPE_COMPOSITION_LAYER_ALPHA_BLEND_FB):
				return "XR_TYPE_COMPOSITION_LAYER_ALPHA_BLEND_FB";
				break;
			#endif /*  defined(XR_FB_composition_layer_alpha_blend)  */
			#if defined(XR_FB_composition_layer_depth_test)
			case(XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_FB):
				return "XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_FB";
				break;
			#endif /*  defined(XR_FB_composition_layer_depth_test)  */
			#if defined(XR_FB_composition_layer_image_layout)
			case(XR_TYPE_COMPOSITION_LAYER_IMAGE_LAYOUT_FB):
				return "XR_TYPE_COMPOSITION_LAYER_IMAGE_LAYOUT_FB";
				break;
			#endif /*  defined(XR_FB_composition_layer_image_layout)  */
			#if defined(XR_FB_composition_layer_secure_content)
			case(XR_TYPE_COMPOSITION_LAYER_SECURE_CONTENT_FB):
				return "XR_TYPE_COMPOSITION_LAYER_SECURE_CONTENT_FB";
				break;
			#endif /*  defined(XR_FB_composition_layer_secure_content)  */
			#if defined(XR_FB_composition_layer_settings)
			case(XR_TYPE_COMPOSITION_LAYER_SETTINGS_FB):
				return "XR_TYPE_COMPOSITION_LAYER_SETTINGS_FB";
				break;
			#endif /*  defined(XR_FB_composition_layer_settings)  */
			#if defined(XR_FB_display_refresh_rate)
			case(XR_TYPE_EVENT_DATA_DISPLAY_REFRESH_RATE_CHANGED_FB):
				return "XR_TYPE_EVENT_DATA_DISPLAY_REFRESH_RATE_CHANGED_FB";
				break;
			#endif /*  defined(XR_FB_display_refresh_rate)  */
			#if defined(XR_FB_eye_tracking_social)
			case(XR_TYPE_EYE_TRACKER_CREATE_INFO_FB):
				return "XR_TYPE_EYE_TRACKER_CREATE_INFO_FB";
				break;
			case(XR_TYPE_EYE_GAZES_INFO_FB):
				return "XR_TYPE_EYE_GAZES_INFO_FB";
				break;
			case(XR_TYPE_EYE_GAZES_FB):
				return "XR_TYPE_EYE_GAZES_FB";
				break;
			case(XR_TYPE_SYSTEM_EYE_TRACKING_PROPERTIES_FB):
				return "XR_TYPE_SYSTEM_EYE_TRACKING_PROPERTIES_FB";
				break;
			#endif /*  defined(XR_FB_eye_tracking_social)  */
			#if defined(XR_FB_face_tracking)
			case(XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES_FB):
				return "XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES_FB";
				break;
			case(XR_TYPE_FACE_TRACKER_CREATE_INFO_FB):
				return "XR_TYPE_FACE_TRACKER_CREATE_INFO_FB";
				break;
			case(XR_TYPE_FACE_EXPRESSION_INFO_FB):
				return "XR_TYPE_FACE_EXPRESSION_INFO_FB";
				break;
			case(XR_TYPE_FACE_EXPRESSION_WEIGHTS_FB):
				return "XR_TYPE_FACE_EXPRESSION_WEIGHTS_FB";
				break;
			#endif /*  defined(XR_FB_face_tracking)  */
			#if defined(XR_FB_face_tracking2)
			case(XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES2_FB):
				return "XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES2_FB";
				break;
			case(XR_TYPE_FACE_TRACKER_CREATE_INFO2_FB):
				return "XR_TYPE_FACE_TRACKER_CREATE_INFO2_FB";
				break;
			case(XR_TYPE_FACE_EXPRESSION_INFO2_FB):
				return "XR_TYPE_FACE_EXPRESSION_INFO2_FB";
				break;
			case(XR_TYPE_FACE_EXPRESSION_WEIGHTS2_FB):
				return "XR_TYPE_FACE_EXPRESSION_WEIGHTS2_FB";
				break;
			#endif /*  defined(XR_FB_face_tracking2)  */
			#if defined(XR_FB_foveation)
			case(XR_TYPE_FOVEATION_PROFILE_CREATE_INFO_FB):
				return "XR_TYPE_FOVEATION_PROFILE_CREATE_INFO_FB";
				break;
			case(XR_TYPE_SWAPCHAIN_CREATE_INFO_FOVEATION_FB):
				return "XR_TYPE_SWAPCHAIN_CREATE_INFO_FOVEATION_FB";
				break;
			case(XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB):
				return "XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB";
				break;
			#endif /*  defined(XR_FB_foveation)  */
			#if defined(XR_FB_foveation_configuration)
			case(XR_TYPE_FOVEATION_LEVEL_PROFILE_CREATE_INFO_FB):
				return "XR_TYPE_FOVEATION_LEVEL_PROFILE_CREATE_INFO_FB";
				break;
			#endif /*  defined(XR_FB_foveation_configuration)  */
			#if defined(XR_FB_foveation_vulkan)
			case(XR_TYPE_SWAPCHAIN_IMAGE_FOVEATION_VULKAN_FB):
				return "XR_TYPE_SWAPCHAIN_IMAGE_FOVEATION_VULKAN_FB";
				break;
			#endif /*  defined(XR_FB_foveation_vulkan)  */
			#if defined(XR_FB_hand_tracking_aim)
			case(XR_TYPE_HAND_TRACKING_AIM_STATE_FB):
				return "XR_TYPE_HAND_TRACKING_AIM_STATE_FB";
				break;
			#endif /*  defined(XR_FB_hand_tracking_aim)  */
			#if defined(XR_FB_hand_tracking_capsules)
			case(XR_TYPE_HAND_TRACKING_CAPSULES_STATE_FB):
				return "XR_TYPE_HAND_TRACKING_CAPSULES_STATE_FB";
				break;
			#endif /*  defined(XR_FB_hand_tracking_capsules)  */
			#if defined(XR_FB_hand_tracking_mesh)
			case(XR_TYPE_HAND_TRACKING_MESH_FB):
				return "XR_TYPE_HAND_TRACKING_MESH_FB";
				break;
			case(XR_TYPE_HAND_TRACKING_SCALE_FB):
				return "XR_TYPE_HAND_TRACKING_SCALE_FB";
				break;
			#endif /*  defined(XR_FB_hand_tracking_mesh)  */
			#if defined(XR_FB_haptic_amplitude_envelope)
			case(XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB):
				return "XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB";
				break;
			#endif /*  defined(XR_FB_haptic_amplitude_envelope)  */
			#if defined(XR_FB_haptic_pcm)
			case(XR_TYPE_HAPTIC_PCM_VIBRATION_FB):
				return "XR_TYPE_HAPTIC_PCM_VIBRATION_FB";
				break;
			case(XR_TYPE_DEVICE_PCM_SAMPLE_RATE_STATE_FB):
				return "XR_TYPE_DEVICE_PCM_SAMPLE_RATE_STATE_FB";
				break;
			#endif /*  defined(XR_FB_haptic_pcm)  */
			#if defined(XR_FB_keyboard_tracking)
			case(XR_TYPE_KEYBOARD_SPACE_CREATE_INFO_FB):
				return "XR_TYPE_KEYBOARD_SPACE_CREATE_INFO_FB";
				break;
			case(XR_TYPE_KEYBOARD_TRACKING_QUERY_FB):
				return "XR_TYPE_KEYBOARD_TRACKING_QUERY_FB";
				break;
			case(XR_TYPE_SYSTEM_KEYBOARD_TRACKING_PROPERTIES_FB):
				return "XR_TYPE_SYSTEM_KEYBOARD_TRACKING_PROPERTIES_FB";
				break;
			#endif /*  defined(XR_FB_keyboard_tracking)  */
			#if defined(XR_FB_passthrough)
			case(XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES_FB):
				return "XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES_FB";
				break;
			case(XR_TYPE_PASSTHROUGH_CREATE_INFO_FB):
				return "XR_TYPE_PASSTHROUGH_CREATE_INFO_FB";
				break;
			case(XR_TYPE_PASSTHROUGH_LAYER_CREATE_INFO_FB):
				return "XR_TYPE_PASSTHROUGH_LAYER_CREATE_INFO_FB";
				break;
			case(XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB):
				return "XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB";
				break;
			case(XR_TYPE_GEOMETRY_INSTANCE_CREATE_INFO_FB):
				return "XR_TYPE_GEOMETRY_INSTANCE_CREATE_INFO_FB";
				break;
			case(XR_TYPE_GEOMETRY_INSTANCE_TRANSFORM_FB):
				return "XR_TYPE_GEOMETRY_INSTANCE_TRANSFORM_FB";
				break;
			case(XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES2_FB):
				return "XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES2_FB";
				break;
			case(XR_TYPE_PASSTHROUGH_STYLE_FB):
				return "XR_TYPE_PASSTHROUGH_STYLE_FB";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_TO_RGBA_FB):
				return "XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_TO_RGBA_FB";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_TO_MONO_FB):
				return "XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_TO_MONO_FB";
				break;
			case(XR_TYPE_PASSTHROUGH_BRIGHTNESS_CONTRAST_SATURATION_FB):
				return "XR_TYPE_PASSTHROUGH_BRIGHTNESS_CONTRAST_SATURATION_FB";
				break;
			case(XR_TYPE_EVENT_DATA_PASSTHROUGH_STATE_CHANGED_FB):
				return "XR_TYPE_EVENT_DATA_PASSTHROUGH_STATE_CHANGED_FB";
				break;
			#endif /*  defined(XR_FB_passthrough)  */
			#if defined(XR_FB_passthrough_keyboard_hands)
			case(XR_TYPE_PASSTHROUGH_KEYBOARD_HANDS_INTENSITY_FB):
				return "XR_TYPE_PASSTHROUGH_KEYBOARD_HANDS_INTENSITY_FB";
				break;
			#endif /*  defined(XR_FB_passthrough_keyboard_hands)  */
			#if defined(XR_FB_render_model)
			case(XR_TYPE_RENDER_MODEL_PATH_INFO_FB):
				return "XR_TYPE_RENDER_MODEL_PATH_INFO_FB";
				break;
			case(XR_TYPE_RENDER_MODEL_PROPERTIES_FB):
				return "XR_TYPE_RENDER_MODEL_PROPERTIES_FB";
				break;
			case(XR_TYPE_RENDER_MODEL_BUFFER_FB):
				return "XR_TYPE_RENDER_MODEL_BUFFER_FB";
				break;
			case(XR_TYPE_RENDER_MODEL_LOAD_INFO_FB):
				return "XR_TYPE_RENDER_MODEL_LOAD_INFO_FB";
				break;
			case(XR_TYPE_SYSTEM_RENDER_MODEL_PROPERTIES_FB):
				return "XR_TYPE_SYSTEM_RENDER_MODEL_PROPERTIES_FB";
				break;
			case(XR_TYPE_RENDER_MODEL_CAPABILITIES_REQUEST_FB):
				return "XR_TYPE_RENDER_MODEL_CAPABILITIES_REQUEST_FB";
				break;
			#endif /*  defined(XR_FB_render_model)  */
			#if defined(XR_FB_scene)
			case(XR_TYPE_SEMANTIC_LABELS_FB):
				return "XR_TYPE_SEMANTIC_LABELS_FB";
				break;
			case(XR_TYPE_ROOM_LAYOUT_FB):
				return "XR_TYPE_ROOM_LAYOUT_FB";
				break;
			case(XR_TYPE_BOUNDARY_2D_FB):
				return "XR_TYPE_BOUNDARY_2D_FB";
				break;
			case(XR_TYPE_SEMANTIC_LABELS_SUPPORT_INFO_FB):
				return "XR_TYPE_SEMANTIC_LABELS_SUPPORT_INFO_FB";
				break;
			#endif /*  defined(XR_FB_scene)  */
			#if defined(XR_FB_scene_capture)
			case(XR_TYPE_EVENT_DATA_SCENE_CAPTURE_COMPLETE_FB):
				return "XR_TYPE_EVENT_DATA_SCENE_CAPTURE_COMPLETE_FB";
				break;
			case(XR_TYPE_SCENE_CAPTURE_REQUEST_INFO_FB):
				return "XR_TYPE_SCENE_CAPTURE_REQUEST_INFO_FB";
				break;
			#endif /*  defined(XR_FB_scene_capture)  */
			#if defined(XR_FB_space_warp)
			case(XR_TYPE_COMPOSITION_LAYER_SPACE_WARP_INFO_FB):
				return "XR_TYPE_COMPOSITION_LAYER_SPACE_WARP_INFO_FB";
				break;
			case(XR_TYPE_SYSTEM_SPACE_WARP_PROPERTIES_FB):
				return "XR_TYPE_SYSTEM_SPACE_WARP_PROPERTIES_FB";
				break;
			#endif /*  defined(XR_FB_space_warp)  */
			#if defined(XR_FB_spatial_entity)
			case(XR_TYPE_SYSTEM_SPATIAL_ENTITY_PROPERTIES_FB):
				return "XR_TYPE_SYSTEM_SPATIAL_ENTITY_PROPERTIES_FB";
				break;
			case(XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_FB):
				return "XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_FB";
				break;
			case(XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB):
				return "XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB";
				break;
			case(XR_TYPE_SPACE_COMPONENT_STATUS_FB):
				return "XR_TYPE_SPACE_COMPONENT_STATUS_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPATIAL_ANCHOR_CREATE_COMPLETE_FB):
				return "XR_TYPE_EVENT_DATA_SPATIAL_ANCHOR_CREATE_COMPLETE_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_SET_STATUS_COMPLETE_FB):
				return "XR_TYPE_EVENT_DATA_SPACE_SET_STATUS_COMPLETE_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity)  */
			#if defined(XR_FB_spatial_entity_container)
			case(XR_TYPE_SPACE_CONTAINER_FB):
				return "XR_TYPE_SPACE_CONTAINER_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_container)  */
			#if defined(XR_FB_spatial_entity_query)
			case(XR_TYPE_SPACE_QUERY_INFO_FB):
				return "XR_TYPE_SPACE_QUERY_INFO_FB";
				break;
			case(XR_TYPE_SPACE_QUERY_RESULTS_FB):
				return "XR_TYPE_SPACE_QUERY_RESULTS_FB";
				break;
			case(XR_TYPE_SPACE_STORAGE_LOCATION_FILTER_INFO_FB):
				return "XR_TYPE_SPACE_STORAGE_LOCATION_FILTER_INFO_FB";
				break;
			case(XR_TYPE_SPACE_UUID_FILTER_INFO_FB):
				return "XR_TYPE_SPACE_UUID_FILTER_INFO_FB";
				break;
			case(XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB):
				return "XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_QUERY_RESULTS_AVAILABLE_FB):
				return "XR_TYPE_EVENT_DATA_SPACE_QUERY_RESULTS_AVAILABLE_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_QUERY_COMPLETE_FB):
				return "XR_TYPE_EVENT_DATA_SPACE_QUERY_COMPLETE_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_query)  */
			#if defined(XR_FB_spatial_entity_sharing)
			case(XR_TYPE_SPACE_SHARE_INFO_FB):
				return "XR_TYPE_SPACE_SHARE_INFO_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_SHARE_COMPLETE_FB):
				return "XR_TYPE_EVENT_DATA_SPACE_SHARE_COMPLETE_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_sharing)  */
			#if defined(XR_FB_spatial_entity_storage)
			case(XR_TYPE_SPACE_SAVE_INFO_FB):
				return "XR_TYPE_SPACE_SAVE_INFO_FB";
				break;
			case(XR_TYPE_SPACE_ERASE_INFO_FB):
				return "XR_TYPE_SPACE_ERASE_INFO_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_SAVE_COMPLETE_FB):
				return "XR_TYPE_EVENT_DATA_SPACE_SAVE_COMPLETE_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_ERASE_COMPLETE_FB):
				return "XR_TYPE_EVENT_DATA_SPACE_ERASE_COMPLETE_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_storage)  */
			#if defined(XR_FB_spatial_entity_storage_batch)
			case(XR_TYPE_SPACE_LIST_SAVE_INFO_FB):
				return "XR_TYPE_SPACE_LIST_SAVE_INFO_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_LIST_SAVE_COMPLETE_FB):
				return "XR_TYPE_EVENT_DATA_SPACE_LIST_SAVE_COMPLETE_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_storage_batch)  */
			#if defined(XR_FB_spatial_entity_user)
			case(XR_TYPE_SPACE_USER_CREATE_INFO_FB):
				return "XR_TYPE_SPACE_USER_CREATE_INFO_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_user)  */
			#if defined(XR_FB_swapchain_update_state_android_surface)
			case(XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB):
				return "XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB";
				break;
			#endif /*  defined(XR_FB_swapchain_update_state_android_surface)  */
			#if defined(XR_FB_swapchain_update_state_opengl_es)
			case(XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB):
				return "XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB";
				break;
			#endif /*  defined(XR_FB_swapchain_update_state_opengl_es)  */
			#if defined(XR_FB_swapchain_update_state_vulkan)
			case(XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB):
				return "XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB";
				break;
			#endif /*  defined(XR_FB_swapchain_update_state_vulkan)  */
			#if defined(XR_FB_triangle_mesh)
			case(XR_TYPE_TRIANGLE_MESH_CREATE_INFO_FB):
				return "XR_TYPE_TRIANGLE_MESH_CREATE_INFO_FB";
				break;
			#endif /*  defined(XR_FB_triangle_mesh)  */
			#if defined(XR_HTCX_vive_tracker_interaction)
			case(XR_TYPE_VIVE_TRACKER_PATHS_HTCX):
				return "XR_TYPE_VIVE_TRACKER_PATHS_HTCX";
				break;
			case(XR_TYPE_EVENT_DATA_VIVE_TRACKER_CONNECTED_HTCX):
				return "XR_TYPE_EVENT_DATA_VIVE_TRACKER_CONNECTED_HTCX";
				break;
			#endif /*  defined(XR_HTCX_vive_tracker_interaction)  */
			#if defined(XR_HTC_anchor)
			case(XR_TYPE_SYSTEM_ANCHOR_PROPERTIES_HTC):
				return "XR_TYPE_SYSTEM_ANCHOR_PROPERTIES_HTC";
				break;
			case(XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_HTC):
				return "XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_HTC";
				break;
			#endif /*  defined(XR_HTC_anchor)  */
			#if defined(XR_HTC_body_tracking)
			case(XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_HTC):
				return "XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_HTC";
				break;
			case(XR_TYPE_BODY_TRACKER_CREATE_INFO_HTC):
				return "XR_TYPE_BODY_TRACKER_CREATE_INFO_HTC";
				break;
			case(XR_TYPE_BODY_JOINTS_LOCATE_INFO_HTC):
				return "XR_TYPE_BODY_JOINTS_LOCATE_INFO_HTC";
				break;
			case(XR_TYPE_BODY_JOINT_LOCATIONS_HTC):
				return "XR_TYPE_BODY_JOINT_LOCATIONS_HTC";
				break;
			case(XR_TYPE_BODY_SKELETON_HTC):
				return "XR_TYPE_BODY_SKELETON_HTC";
				break;
			#endif /*  defined(XR_HTC_body_tracking)  */
			#if defined(XR_HTC_facial_tracking)
			case(XR_TYPE_SYSTEM_FACIAL_TRACKING_PROPERTIES_HTC):
				return "XR_TYPE_SYSTEM_FACIAL_TRACKING_PROPERTIES_HTC";
				break;
			case(XR_TYPE_FACIAL_TRACKER_CREATE_INFO_HTC):
				return "XR_TYPE_FACIAL_TRACKER_CREATE_INFO_HTC";
				break;
			case(XR_TYPE_FACIAL_EXPRESSIONS_HTC):
				return "XR_TYPE_FACIAL_EXPRESSIONS_HTC";
				break;
			#endif /*  defined(XR_HTC_facial_tracking)  */
			#if defined(XR_HTC_foveation)
			case(XR_TYPE_FOVEATION_APPLY_INFO_HTC):
				return "XR_TYPE_FOVEATION_APPLY_INFO_HTC";
				break;
			case(XR_TYPE_FOVEATION_DYNAMIC_MODE_INFO_HTC):
				return "XR_TYPE_FOVEATION_DYNAMIC_MODE_INFO_HTC";
				break;
			case(XR_TYPE_FOVEATION_CUSTOM_MODE_INFO_HTC):
				return "XR_TYPE_FOVEATION_CUSTOM_MODE_INFO_HTC";
				break;
			#endif /*  defined(XR_HTC_foveation)  */
			#if defined(XR_HTC_passthrough)
			case(XR_TYPE_PASSTHROUGH_CREATE_INFO_HTC):
				return "XR_TYPE_PASSTHROUGH_CREATE_INFO_HTC";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_HTC):
				return "XR_TYPE_PASSTHROUGH_COLOR_HTC";
				break;
			case(XR_TYPE_PASSTHROUGH_MESH_TRANSFORM_INFO_HTC):
				return "XR_TYPE_PASSTHROUGH_MESH_TRANSFORM_INFO_HTC";
				break;
			case(XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_HTC):
				return "XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_HTC";
				break;
			#endif /*  defined(XR_HTC_passthrough)  */
			#if defined(XR_KHR_D3D11_enable)
			case(XR_TYPE_GRAPHICS_BINDING_D3D11_KHR):
				return "XR_TYPE_GRAPHICS_BINDING_D3D11_KHR";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR):
				return "XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR";
				break;
			case(XR_TYPE_GRAPHICS_REQUIREMENTS_D3D11_KHR):
				return "XR_TYPE_GRAPHICS_REQUIREMENTS_D3D11_KHR";
				break;
			#endif /*  defined(XR_KHR_D3D11_enable)  */
			#if defined(XR_KHR_D3D12_enable)
			case(XR_TYPE_GRAPHICS_BINDING_D3D12_KHR):
				return "XR_TYPE_GRAPHICS_BINDING_D3D12_KHR";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR):
				return "XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR";
				break;
			case(XR_TYPE_GRAPHICS_REQUIREMENTS_D3D12_KHR):
				return "XR_TYPE_GRAPHICS_REQUIREMENTS_D3D12_KHR";
				break;
			#endif /*  defined(XR_KHR_D3D12_enable)  */
			#if defined(XR_KHR_android_create_instance)
			case(XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR):
				return "XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR";
				break;
			#endif /*  defined(XR_KHR_android_create_instance)  */
			#if defined(XR_KHR_binding_modification)
			case(XR_TYPE_BINDING_MODIFICATIONS_KHR):
				return "XR_TYPE_BINDING_MODIFICATIONS_KHR";
				break;
			#endif /*  defined(XR_KHR_binding_modification)  */
			#if defined(XR_KHR_composition_layer_color_scale_bias)
			case(XR_TYPE_COMPOSITION_LAYER_COLOR_SCALE_BIAS_KHR):
				return "XR_TYPE_COMPOSITION_LAYER_COLOR_SCALE_BIAS_KHR";
				break;
			#endif /*  defined(XR_KHR_composition_layer_color_scale_bias)  */
			#if defined(XR_KHR_composition_layer_cube)
			case(XR_TYPE_COMPOSITION_LAYER_CUBE_KHR):
				return "XR_TYPE_COMPOSITION_LAYER_CUBE_KHR";
				break;
			#endif /*  defined(XR_KHR_composition_layer_cube)  */
			#if defined(XR_KHR_composition_layer_cylinder)
			case(XR_TYPE_COMPOSITION_LAYER_CYLINDER_KHR):
				return "XR_TYPE_COMPOSITION_LAYER_CYLINDER_KHR";
				break;
			#endif /*  defined(XR_KHR_composition_layer_cylinder)  */
			#if defined(XR_KHR_composition_layer_depth)
			case(XR_TYPE_COMPOSITION_LAYER_DEPTH_INFO_KHR):
				return "XR_TYPE_COMPOSITION_LAYER_DEPTH_INFO_KHR";
				break;
			#endif /*  defined(XR_KHR_composition_layer_depth)  */
			#if defined(XR_KHR_composition_layer_equirect)
			case(XR_TYPE_COMPOSITION_LAYER_EQUIRECT_KHR):
				return "XR_TYPE_COMPOSITION_LAYER_EQUIRECT_KHR";
				break;
			#endif /*  defined(XR_KHR_composition_layer_equirect)  */
			#if defined(XR_KHR_composition_layer_equirect2)
			case(XR_TYPE_COMPOSITION_LAYER_EQUIRECT2_KHR):
				return "XR_TYPE_COMPOSITION_LAYER_EQUIRECT2_KHR";
				break;
			#endif /*  defined(XR_KHR_composition_layer_equirect2)  */
			#if defined(XR_KHR_loader_init_android)
			case(XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR):
				return "XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR";
				break;
			#endif /*  defined(XR_KHR_loader_init_android)  */
			#if defined(XR_KHR_metal_enable)
			case(XR_TYPE_GRAPHICS_BINDING_METAL_KHR):
				return "XR_TYPE_GRAPHICS_BINDING_METAL_KHR";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR):
				return "XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR";
				break;
			case(XR_TYPE_GRAPHICS_REQUIREMENTS_METAL_KHR):
				return "XR_TYPE_GRAPHICS_REQUIREMENTS_METAL_KHR";
				break;
			#endif /*  defined(XR_KHR_metal_enable)  */
			#if defined(XR_KHR_opengl_enable)
			case(XR_TYPE_GRAPHICS_BINDING_OPENGL_WIN32_KHR):
				return "XR_TYPE_GRAPHICS_BINDING_OPENGL_WIN32_KHR";
				break;
			case(XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR):
				return "XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR";
				break;
			case(XR_TYPE_GRAPHICS_BINDING_OPENGL_XCB_KHR):
				return "XR_TYPE_GRAPHICS_BINDING_OPENGL_XCB_KHR";
				break;
			case(XR_TYPE_GRAPHICS_BINDING_OPENGL_WAYLAND_KHR):
				return "XR_TYPE_GRAPHICS_BINDING_OPENGL_WAYLAND_KHR";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR):
				return "XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR";
				break;
			case(XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR):
				return "XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR";
				break;
			#endif /*  defined(XR_KHR_opengl_enable)  */
			#if defined(XR_KHR_opengl_es_enable)
			case(XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR):
				return "XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR):
				return "XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR";
				break;
			case(XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR):
				return "XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR";
				break;
			#endif /*  defined(XR_KHR_opengl_es_enable)  */
			#if defined(XR_KHR_visibility_mask)
			case(XR_TYPE_VISIBILITY_MASK_KHR):
				return "XR_TYPE_VISIBILITY_MASK_KHR";
				break;
			case(XR_TYPE_EVENT_DATA_VISIBILITY_MASK_CHANGED_KHR):
				return "XR_TYPE_EVENT_DATA_VISIBILITY_MASK_CHANGED_KHR";
				break;
			#endif /*  defined(XR_KHR_visibility_mask)  */
			#if defined(XR_KHR_vulkan_enable)
			case(XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR):
				return "XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR):
				return "XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR";
				break;
			case(XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN_KHR):
				return "XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN_KHR";
				break;
			#endif /*  defined(XR_KHR_vulkan_enable)  */
			#if defined(XR_KHR_vulkan_enable2)
			case(XR_TYPE_VULKAN_INSTANCE_CREATE_INFO_KHR):
				return "XR_TYPE_VULKAN_INSTANCE_CREATE_INFO_KHR";
				break;
			case(XR_TYPE_VULKAN_DEVICE_CREATE_INFO_KHR):
				return "XR_TYPE_VULKAN_DEVICE_CREATE_INFO_KHR";
				break;
			case(XR_TYPE_VULKAN_GRAPHICS_DEVICE_GET_INFO_KHR):
				return "XR_TYPE_VULKAN_GRAPHICS_DEVICE_GET_INFO_KHR";
				break;
			#endif /*  defined(XR_KHR_vulkan_enable2)  */
			#if defined(XR_KHR_vulkan_swapchain_format_list)
			case(XR_TYPE_VULKAN_SWAPCHAIN_FORMAT_LIST_CREATE_INFO_KHR):
				return "XR_TYPE_VULKAN_SWAPCHAIN_FORMAT_LIST_CREATE_INFO_KHR";
				break;
			#endif /*  defined(XR_KHR_vulkan_swapchain_format_list)  */
			#if defined(XR_META_environment_depth)
			case(XR_TYPE_ENVIRONMENT_DEPTH_PROVIDER_CREATE_INFO_META):
				return "XR_TYPE_ENVIRONMENT_DEPTH_PROVIDER_CREATE_INFO_META";
				break;
			case(XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_CREATE_INFO_META):
				return "XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_CREATE_INFO_META";
				break;
			case(XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_STATE_META):
				return "XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_STATE_META";
				break;
			case(XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_ACQUIRE_INFO_META):
				return "XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_ACQUIRE_INFO_META";
				break;
			case(XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_VIEW_META):
				return "XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_VIEW_META";
				break;
			case(XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_META):
				return "XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_META";
				break;
			case(XR_TYPE_ENVIRONMENT_DEPTH_HAND_REMOVAL_SET_INFO_META):
				return "XR_TYPE_ENVIRONMENT_DEPTH_HAND_REMOVAL_SET_INFO_META";
				break;
			case(XR_TYPE_SYSTEM_ENVIRONMENT_DEPTH_PROPERTIES_META):
				return "XR_TYPE_SYSTEM_ENVIRONMENT_DEPTH_PROPERTIES_META";
				break;
			#endif /*  defined(XR_META_environment_depth)  */
			#if defined(XR_META_foveation_eye_tracked)
			case(XR_TYPE_FOVEATION_EYE_TRACKED_PROFILE_CREATE_INFO_META):
				return "XR_TYPE_FOVEATION_EYE_TRACKED_PROFILE_CREATE_INFO_META";
				break;
			case(XR_TYPE_FOVEATION_EYE_TRACKED_STATE_META):
				return "XR_TYPE_FOVEATION_EYE_TRACKED_STATE_META";
				break;
			case(XR_TYPE_SYSTEM_FOVEATION_EYE_TRACKED_PROPERTIES_META):
				return "XR_TYPE_SYSTEM_FOVEATION_EYE_TRACKED_PROPERTIES_META";
				break;
			#endif /*  defined(XR_META_foveation_eye_tracked)  */
			#if defined(XR_META_headset_id)
			case(XR_TYPE_SYSTEM_HEADSET_ID_PROPERTIES_META):
				return "XR_TYPE_SYSTEM_HEADSET_ID_PROPERTIES_META";
				break;
			#endif /*  defined(XR_META_headset_id)  */
			#if defined(XR_META_local_dimming)
			case(XR_TYPE_LOCAL_DIMMING_FRAME_END_INFO_META):
				return "XR_TYPE_LOCAL_DIMMING_FRAME_END_INFO_META";
				break;
			#endif /*  defined(XR_META_local_dimming)  */
			#if defined(XR_META_passthrough_color_lut)
			case(XR_TYPE_SYSTEM_PASSTHROUGH_COLOR_LUT_PROPERTIES_META):
				return "XR_TYPE_SYSTEM_PASSTHROUGH_COLOR_LUT_PROPERTIES_META";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_LUT_CREATE_INFO_META):
				return "XR_TYPE_PASSTHROUGH_COLOR_LUT_CREATE_INFO_META";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_LUT_UPDATE_INFO_META):
				return "XR_TYPE_PASSTHROUGH_COLOR_LUT_UPDATE_INFO_META";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_MAP_LUT_META):
				return "XR_TYPE_PASSTHROUGH_COLOR_MAP_LUT_META";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_MAP_INTERPOLATED_LUT_META):
				return "XR_TYPE_PASSTHROUGH_COLOR_MAP_INTERPOLATED_LUT_META";
				break;
			#endif /*  defined(XR_META_passthrough_color_lut)  */
			#if defined(XR_META_passthrough_preferences)
			case(XR_TYPE_PASSTHROUGH_PREFERENCES_META):
				return "XR_TYPE_PASSTHROUGH_PREFERENCES_META";
				break;
			#endif /*  defined(XR_META_passthrough_preferences)  */
			#if defined(XR_META_performance_metrics)
			case(XR_TYPE_PERFORMANCE_METRICS_STATE_META):
				return "XR_TYPE_PERFORMANCE_METRICS_STATE_META";
				break;
			case(XR_TYPE_PERFORMANCE_METRICS_COUNTER_META):
				return "XR_TYPE_PERFORMANCE_METRICS_COUNTER_META";
				break;
			#endif /*  defined(XR_META_performance_metrics)  */
			#if defined(XR_META_recommended_layer_resolution)
			case(XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_META):
				return "XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_META";
				break;
			case(XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_GET_INFO_META):
				return "XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_GET_INFO_META";
				break;
			#endif /*  defined(XR_META_recommended_layer_resolution)  */
			#if defined(XR_META_spatial_entity_mesh)
			case(XR_TYPE_SPACE_TRIANGLE_MESH_GET_INFO_META):
				return "XR_TYPE_SPACE_TRIANGLE_MESH_GET_INFO_META";
				break;
			case(XR_TYPE_SPACE_TRIANGLE_MESH_META):
				return "XR_TYPE_SPACE_TRIANGLE_MESH_META";
				break;
			#endif /*  defined(XR_META_spatial_entity_mesh)  */
			#if defined(XR_META_virtual_keyboard)
			case(XR_TYPE_SYSTEM_VIRTUAL_KEYBOARD_PROPERTIES_META):
				return "XR_TYPE_SYSTEM_VIRTUAL_KEYBOARD_PROPERTIES_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_CREATE_INFO_META):
				return "XR_TYPE_VIRTUAL_KEYBOARD_CREATE_INFO_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_SPACE_CREATE_INFO_META):
				return "XR_TYPE_VIRTUAL_KEYBOARD_SPACE_CREATE_INFO_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_LOCATION_INFO_META):
				return "XR_TYPE_VIRTUAL_KEYBOARD_LOCATION_INFO_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_MODEL_VISIBILITY_SET_INFO_META):
				return "XR_TYPE_VIRTUAL_KEYBOARD_MODEL_VISIBILITY_SET_INFO_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_ANIMATION_STATE_META):
				return "XR_TYPE_VIRTUAL_KEYBOARD_ANIMATION_STATE_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_MODEL_ANIMATION_STATES_META):
				return "XR_TYPE_VIRTUAL_KEYBOARD_MODEL_ANIMATION_STATES_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_TEXTURE_DATA_META):
				return "XR_TYPE_VIRTUAL_KEYBOARD_TEXTURE_DATA_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_INPUT_INFO_META):
				return "XR_TYPE_VIRTUAL_KEYBOARD_INPUT_INFO_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_TEXT_CONTEXT_CHANGE_INFO_META):
				return "XR_TYPE_VIRTUAL_KEYBOARD_TEXT_CONTEXT_CHANGE_INFO_META";
				break;
			case(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_COMMIT_TEXT_META):
				return "XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_COMMIT_TEXT_META";
				break;
			case(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_BACKSPACE_META):
				return "XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_BACKSPACE_META";
				break;
			case(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_ENTER_META):
				return "XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_ENTER_META";
				break;
			case(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_SHOWN_META):
				return "XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_SHOWN_META";
				break;
			case(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_HIDDEN_META):
				return "XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_HIDDEN_META";
				break;
			#endif /*  defined(XR_META_virtual_keyboard)  */
			#if defined(XR_META_vulkan_swapchain_create_info)
			case(XR_TYPE_VULKAN_SWAPCHAIN_CREATE_INFO_META):
				return "XR_TYPE_VULKAN_SWAPCHAIN_CREATE_INFO_META";
				break;
			#endif /*  defined(XR_META_vulkan_swapchain_create_info)  */
			#if defined(XR_ML_compat)
			case(XR_TYPE_COORDINATE_SPACE_CREATE_INFO_ML):
				return "XR_TYPE_COORDINATE_SPACE_CREATE_INFO_ML";
				break;
			#endif /*  defined(XR_ML_compat)  */
			#if defined(XR_ML_frame_end_info)
			case(XR_TYPE_FRAME_END_INFO_ML):
				return "XR_TYPE_FRAME_END_INFO_ML";
				break;
			#endif /*  defined(XR_ML_frame_end_info)  */
			#if defined(XR_ML_global_dimmer)
			case(XR_TYPE_GLOBAL_DIMMER_FRAME_END_INFO_ML):
				return "XR_TYPE_GLOBAL_DIMMER_FRAME_END_INFO_ML";
				break;
			#endif /*  defined(XR_ML_global_dimmer)  */
			#if defined(XR_ML_localization_map)
			case(XR_TYPE_LOCALIZATION_MAP_ML):
				return "XR_TYPE_LOCALIZATION_MAP_ML";
				break;
			case(XR_TYPE_EVENT_DATA_LOCALIZATION_CHANGED_ML):
				return "XR_TYPE_EVENT_DATA_LOCALIZATION_CHANGED_ML";
				break;
			case(XR_TYPE_MAP_LOCALIZATION_REQUEST_INFO_ML):
				return "XR_TYPE_MAP_LOCALIZATION_REQUEST_INFO_ML";
				break;
			case(XR_TYPE_LOCALIZATION_MAP_IMPORT_INFO_ML):
				return "XR_TYPE_LOCALIZATION_MAP_IMPORT_INFO_ML";
				break;
			case(XR_TYPE_LOCALIZATION_ENABLE_EVENTS_INFO_ML):
				return "XR_TYPE_LOCALIZATION_ENABLE_EVENTS_INFO_ML";
				break;
			#endif /*  defined(XR_ML_localization_map)  */
			#if defined(XR_ML_marker_understanding)
			case(XR_TYPE_SYSTEM_MARKER_UNDERSTANDING_PROPERTIES_ML):
				return "XR_TYPE_SYSTEM_MARKER_UNDERSTANDING_PROPERTIES_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_CREATE_INFO_ML):
				return "XR_TYPE_MARKER_DETECTOR_CREATE_INFO_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_ARUCO_INFO_ML):
				return "XR_TYPE_MARKER_DETECTOR_ARUCO_INFO_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_SIZE_INFO_ML):
				return "XR_TYPE_MARKER_DETECTOR_SIZE_INFO_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_APRIL_TAG_INFO_ML):
				return "XR_TYPE_MARKER_DETECTOR_APRIL_TAG_INFO_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_CUSTOM_PROFILE_INFO_ML):
				return "XR_TYPE_MARKER_DETECTOR_CUSTOM_PROFILE_INFO_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_SNAPSHOT_INFO_ML):
				return "XR_TYPE_MARKER_DETECTOR_SNAPSHOT_INFO_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_STATE_ML):
				return "XR_TYPE_MARKER_DETECTOR_STATE_ML";
				break;
			case(XR_TYPE_MARKER_SPACE_CREATE_INFO_ML):
				return "XR_TYPE_MARKER_SPACE_CREATE_INFO_ML";
				break;
			#endif /*  defined(XR_ML_marker_understanding)  */
			#if defined(XR_ML_spatial_anchors)
			case(XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML";
				break;
			case(XR_TYPE_CREATE_SPATIAL_ANCHORS_COMPLETION_ML):
				return "XR_TYPE_CREATE_SPATIAL_ANCHORS_COMPLETION_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHOR_STATE_ML):
				return "XR_TYPE_SPATIAL_ANCHOR_STATE_ML";
				break;
			#endif /*  defined(XR_ML_spatial_anchors)  */
			#if defined(XR_ML_spatial_anchors_storage)
			case(XR_TYPE_SPATIAL_ANCHORS_CREATE_STORAGE_INFO_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_CREATE_STORAGE_INFO_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_QUERY_COMPLETION_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_QUERY_COMPLETION_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_PUBLISH_INFO_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_PUBLISH_INFO_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_DELETE_INFO_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_DELETE_INFO_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_INFO_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_INFO_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_DETAILS_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_DETAILS_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_DETAILS_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_DETAILS_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_DETAILS_ML):
				return "XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_DETAILS_ML";
				break;
			#endif /*  defined(XR_ML_spatial_anchors_storage)  */
			#if defined(XR_ML_system_notifications)
			case(XR_TYPE_SYSTEM_NOTIFICATIONS_SET_INFO_ML):
				return "XR_TYPE_SYSTEM_NOTIFICATIONS_SET_INFO_ML";
				break;
			#endif /*  defined(XR_ML_system_notifications)  */
			#if defined(XR_ML_user_calibration)
			case(XR_TYPE_EVENT_DATA_HEADSET_FIT_CHANGED_ML):
				return "XR_TYPE_EVENT_DATA_HEADSET_FIT_CHANGED_ML";
				break;
			case(XR_TYPE_EVENT_DATA_EYE_CALIBRATION_CHANGED_ML):
				return "XR_TYPE_EVENT_DATA_EYE_CALIBRATION_CHANGED_ML";
				break;
			case(XR_TYPE_USER_CALIBRATION_ENABLE_EVENTS_INFO_ML):
				return "XR_TYPE_USER_CALIBRATION_ENABLE_EVENTS_INFO_ML";
				break;
			#endif /*  defined(XR_ML_user_calibration)  */
			#if defined(XR_ML_world_mesh_detection)
			case(XR_TYPE_WORLD_MESH_DETECTOR_CREATE_INFO_ML):
				return "XR_TYPE_WORLD_MESH_DETECTOR_CREATE_INFO_ML";
				break;
			case(XR_TYPE_WORLD_MESH_STATE_REQUEST_INFO_ML):
				return "XR_TYPE_WORLD_MESH_STATE_REQUEST_INFO_ML";
				break;
			case(XR_TYPE_WORLD_MESH_BLOCK_STATE_ML):
				return "XR_TYPE_WORLD_MESH_BLOCK_STATE_ML";
				break;
			case(XR_TYPE_WORLD_MESH_STATE_REQUEST_COMPLETION_ML):
				return "XR_TYPE_WORLD_MESH_STATE_REQUEST_COMPLETION_ML";
				break;
			case(XR_TYPE_WORLD_MESH_BUFFER_RECOMMENDED_SIZE_INFO_ML):
				return "XR_TYPE_WORLD_MESH_BUFFER_RECOMMENDED_SIZE_INFO_ML";
				break;
			case(XR_TYPE_WORLD_MESH_BUFFER_SIZE_ML):
				return "XR_TYPE_WORLD_MESH_BUFFER_SIZE_ML";
				break;
			case(XR_TYPE_WORLD_MESH_BUFFER_ML):
				return "XR_TYPE_WORLD_MESH_BUFFER_ML";
				break;
			case(XR_TYPE_WORLD_MESH_BLOCK_REQUEST_ML):
				return "XR_TYPE_WORLD_MESH_BLOCK_REQUEST_ML";
				break;
			case(XR_TYPE_WORLD_MESH_GET_INFO_ML):
				return "XR_TYPE_WORLD_MESH_GET_INFO_ML";
				break;
			case(XR_TYPE_WORLD_MESH_BLOCK_ML):
				return "XR_TYPE_WORLD_MESH_BLOCK_ML";
				break;
			case(XR_TYPE_WORLD_MESH_REQUEST_COMPLETION_ML):
				return "XR_TYPE_WORLD_MESH_REQUEST_COMPLETION_ML";
				break;
			case(XR_TYPE_WORLD_MESH_REQUEST_COMPLETION_INFO_ML):
				return "XR_TYPE_WORLD_MESH_REQUEST_COMPLETION_INFO_ML";
				break;
			#endif /*  defined(XR_ML_world_mesh_detection)  */
			#if defined(XR_MNDX_egl_enable)
			case(XR_TYPE_GRAPHICS_BINDING_EGL_MNDX):
				return "XR_TYPE_GRAPHICS_BINDING_EGL_MNDX";
				break;
			#endif /*  defined(XR_MNDX_egl_enable)  */
			#if defined(XR_MNDX_force_feedback_curl)
			case(XR_TYPE_SYSTEM_FORCE_FEEDBACK_CURL_PROPERTIES_MNDX):
				return "XR_TYPE_SYSTEM_FORCE_FEEDBACK_CURL_PROPERTIES_MNDX";
				break;
			case(XR_TYPE_FORCE_FEEDBACK_CURL_APPLY_LOCATIONS_MNDX):
				return "XR_TYPE_FORCE_FEEDBACK_CURL_APPLY_LOCATIONS_MNDX";
				break;
			#endif /*  defined(XR_MNDX_force_feedback_curl)  */
			#if defined(XR_MSFT_composition_layer_reprojection)
			case(XR_TYPE_COMPOSITION_LAYER_REPROJECTION_INFO_MSFT):
				return "XR_TYPE_COMPOSITION_LAYER_REPROJECTION_INFO_MSFT";
				break;
			case(XR_TYPE_COMPOSITION_LAYER_REPROJECTION_PLANE_OVERRIDE_MSFT):
				return "XR_TYPE_COMPOSITION_LAYER_REPROJECTION_PLANE_OVERRIDE_MSFT";
				break;
			#endif /*  defined(XR_MSFT_composition_layer_reprojection)  */
			#if defined(XR_MSFT_controller_model)
			case(XR_TYPE_CONTROLLER_MODEL_KEY_STATE_MSFT):
				return "XR_TYPE_CONTROLLER_MODEL_KEY_STATE_MSFT";
				break;
			case(XR_TYPE_CONTROLLER_MODEL_NODE_PROPERTIES_MSFT):
				return "XR_TYPE_CONTROLLER_MODEL_NODE_PROPERTIES_MSFT";
				break;
			case(XR_TYPE_CONTROLLER_MODEL_PROPERTIES_MSFT):
				return "XR_TYPE_CONTROLLER_MODEL_PROPERTIES_MSFT";
				break;
			case(XR_TYPE_CONTROLLER_MODEL_NODE_STATE_MSFT):
				return "XR_TYPE_CONTROLLER_MODEL_NODE_STATE_MSFT";
				break;
			case(XR_TYPE_CONTROLLER_MODEL_STATE_MSFT):
				return "XR_TYPE_CONTROLLER_MODEL_STATE_MSFT";
				break;
			#endif /*  defined(XR_MSFT_controller_model)  */
			#if defined(XR_MSFT_hand_tracking_mesh)
			case(XR_TYPE_SYSTEM_HAND_TRACKING_MESH_PROPERTIES_MSFT):
				return "XR_TYPE_SYSTEM_HAND_TRACKING_MESH_PROPERTIES_MSFT";
				break;
			case(XR_TYPE_HAND_MESH_SPACE_CREATE_INFO_MSFT):
				return "XR_TYPE_HAND_MESH_SPACE_CREATE_INFO_MSFT";
				break;
			case(XR_TYPE_HAND_MESH_UPDATE_INFO_MSFT):
				return "XR_TYPE_HAND_MESH_UPDATE_INFO_MSFT";
				break;
			case(XR_TYPE_HAND_MESH_MSFT):
				return "XR_TYPE_HAND_MESH_MSFT";
				break;
			case(XR_TYPE_HAND_POSE_TYPE_INFO_MSFT):
				return "XR_TYPE_HAND_POSE_TYPE_INFO_MSFT";
				break;
			#endif /*  defined(XR_MSFT_hand_tracking_mesh)  */
			#if defined(XR_MSFT_holographic_window_attachment)
			case(XR_TYPE_HOLOGRAPHIC_WINDOW_ATTACHMENT_MSFT):
				return "XR_TYPE_HOLOGRAPHIC_WINDOW_ATTACHMENT_MSFT";
				break;
			#endif /*  defined(XR_MSFT_holographic_window_attachment)  */
			#if defined(XR_MSFT_scene_marker)
			case(XR_TYPE_SCENE_MARKERS_MSFT):
				return "XR_TYPE_SCENE_MARKERS_MSFT";
				break;
			case(XR_TYPE_SCENE_MARKER_TYPE_FILTER_MSFT):
				return "XR_TYPE_SCENE_MARKER_TYPE_FILTER_MSFT";
				break;
			case(XR_TYPE_SCENE_MARKER_QR_CODES_MSFT):
				return "XR_TYPE_SCENE_MARKER_QR_CODES_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_marker)  */
			#if defined(XR_MSFT_scene_understanding)
			case(XR_TYPE_SCENE_OBSERVER_CREATE_INFO_MSFT):
				return "XR_TYPE_SCENE_OBSERVER_CREATE_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_CREATE_INFO_MSFT):
				return "XR_TYPE_SCENE_CREATE_INFO_MSFT";
				break;
			case(XR_TYPE_NEW_SCENE_COMPUTE_INFO_MSFT):
				return "XR_TYPE_NEW_SCENE_COMPUTE_INFO_MSFT";
				break;
			case(XR_TYPE_VISUAL_MESH_COMPUTE_LOD_INFO_MSFT):
				return "XR_TYPE_VISUAL_MESH_COMPUTE_LOD_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_COMPONENTS_MSFT):
				return "XR_TYPE_SCENE_COMPONENTS_MSFT";
				break;
			case(XR_TYPE_SCENE_COMPONENTS_GET_INFO_MSFT):
				return "XR_TYPE_SCENE_COMPONENTS_GET_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_COMPONENT_LOCATIONS_MSFT):
				return "XR_TYPE_SCENE_COMPONENT_LOCATIONS_MSFT";
				break;
			case(XR_TYPE_SCENE_COMPONENTS_LOCATE_INFO_MSFT):
				return "XR_TYPE_SCENE_COMPONENTS_LOCATE_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_OBJECTS_MSFT):
				return "XR_TYPE_SCENE_OBJECTS_MSFT";
				break;
			case(XR_TYPE_SCENE_COMPONENT_PARENT_FILTER_INFO_MSFT):
				return "XR_TYPE_SCENE_COMPONENT_PARENT_FILTER_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_OBJECT_TYPES_FILTER_INFO_MSFT):
				return "XR_TYPE_SCENE_OBJECT_TYPES_FILTER_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_PLANES_MSFT):
				return "XR_TYPE_SCENE_PLANES_MSFT";
				break;
			case(XR_TYPE_SCENE_PLANE_ALIGNMENT_FILTER_INFO_MSFT):
				return "XR_TYPE_SCENE_PLANE_ALIGNMENT_FILTER_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_MESHES_MSFT):
				return "XR_TYPE_SCENE_MESHES_MSFT";
				break;
			case(XR_TYPE_SCENE_MESH_BUFFERS_GET_INFO_MSFT):
				return "XR_TYPE_SCENE_MESH_BUFFERS_GET_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_MESH_BUFFERS_MSFT):
				return "XR_TYPE_SCENE_MESH_BUFFERS_MSFT";
				break;
			case(XR_TYPE_SCENE_MESH_VERTEX_BUFFER_MSFT):
				return "XR_TYPE_SCENE_MESH_VERTEX_BUFFER_MSFT";
				break;
			case(XR_TYPE_SCENE_MESH_INDICES_UINT32_MSFT):
				return "XR_TYPE_SCENE_MESH_INDICES_UINT32_MSFT";
				break;
			case(XR_TYPE_SCENE_MESH_INDICES_UINT16_MSFT):
				return "XR_TYPE_SCENE_MESH_INDICES_UINT16_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_understanding)  */
			#if defined(XR_MSFT_scene_understanding_serialization)
			case(XR_TYPE_SERIALIZED_SCENE_FRAGMENT_DATA_GET_INFO_MSFT):
				return "XR_TYPE_SERIALIZED_SCENE_FRAGMENT_DATA_GET_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_DESERIALIZE_INFO_MSFT):
				return "XR_TYPE_SCENE_DESERIALIZE_INFO_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_understanding_serialization)  */
			#if defined(XR_MSFT_secondary_view_configuration)
			case(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SESSION_BEGIN_INFO_MSFT):
				return "XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SESSION_BEGIN_INFO_MSFT";
				break;
			case(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_STATE_MSFT):
				return "XR_TYPE_SECONDARY_VIEW_CONFIGURATION_STATE_MSFT";
				break;
			case(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_FRAME_STATE_MSFT):
				return "XR_TYPE_SECONDARY_VIEW_CONFIGURATION_FRAME_STATE_MSFT";
				break;
			case(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_FRAME_END_INFO_MSFT):
				return "XR_TYPE_SECONDARY_VIEW_CONFIGURATION_FRAME_END_INFO_MSFT";
				break;
			case(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_LAYER_INFO_MSFT):
				return "XR_TYPE_SECONDARY_VIEW_CONFIGURATION_LAYER_INFO_MSFT";
				break;
			case(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SWAPCHAIN_CREATE_INFO_MSFT):
				return "XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SWAPCHAIN_CREATE_INFO_MSFT";
				break;
			#endif /*  defined(XR_MSFT_secondary_view_configuration)  */
			#if defined(XR_MSFT_spatial_anchor)
			case(XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_MSFT):
				return "XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_MSFT";
				break;
			case(XR_TYPE_SPATIAL_ANCHOR_SPACE_CREATE_INFO_MSFT):
				return "XR_TYPE_SPATIAL_ANCHOR_SPACE_CREATE_INFO_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_anchor)  */
			#if defined(XR_MSFT_spatial_anchor_persistence)
			case(XR_TYPE_SPATIAL_ANCHOR_PERSISTENCE_INFO_MSFT):
				return "XR_TYPE_SPATIAL_ANCHOR_PERSISTENCE_INFO_MSFT";
				break;
			case(XR_TYPE_SPATIAL_ANCHOR_FROM_PERSISTED_ANCHOR_CREATE_INFO_MSFT):
				return "XR_TYPE_SPATIAL_ANCHOR_FROM_PERSISTED_ANCHOR_CREATE_INFO_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_anchor_persistence)  */
			#if defined(XR_MSFT_spatial_graph_bridge)
			case(XR_TYPE_SPATIAL_GRAPH_NODE_SPACE_CREATE_INFO_MSFT):
				return "XR_TYPE_SPATIAL_GRAPH_NODE_SPACE_CREATE_INFO_MSFT";
				break;
			case(XR_TYPE_SPATIAL_GRAPH_STATIC_NODE_BINDING_CREATE_INFO_MSFT):
				return "XR_TYPE_SPATIAL_GRAPH_STATIC_NODE_BINDING_CREATE_INFO_MSFT";
				break;
			case(XR_TYPE_SPATIAL_GRAPH_NODE_BINDING_PROPERTIES_GET_INFO_MSFT):
				return "XR_TYPE_SPATIAL_GRAPH_NODE_BINDING_PROPERTIES_GET_INFO_MSFT";
				break;
			case(XR_TYPE_SPATIAL_GRAPH_NODE_BINDING_PROPERTIES_MSFT):
				return "XR_TYPE_SPATIAL_GRAPH_NODE_BINDING_PROPERTIES_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_graph_bridge)  */
			#if defined(XR_OCULUS_external_camera)
			case(XR_TYPE_EXTERNAL_CAMERA_OCULUS):
				return "XR_TYPE_EXTERNAL_CAMERA_OCULUS";
				break;
			#endif /*  defined(XR_OCULUS_external_camera)  */
			#if defined(XR_VALVE_analog_threshold)
			case(XR_TYPE_INTERACTION_PROFILE_ANALOG_THRESHOLD_VALVE):
				return "XR_TYPE_INTERACTION_PROFILE_ANALOG_THRESHOLD_VALVE";
				break;
			#endif /*  defined(XR_VALVE_analog_threshold)  */
			#if defined(XR_VARJO_composition_layer_depth_test)
			case(XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_VARJO):
				return "XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_VARJO";
				break;
			#endif /*  defined(XR_VARJO_composition_layer_depth_test)  */
			#if defined(XR_VARJO_foveated_rendering)
			case(XR_TYPE_VIEW_LOCATE_FOVEATED_RENDERING_VARJO):
				return "XR_TYPE_VIEW_LOCATE_FOVEATED_RENDERING_VARJO";
				break;
			case(XR_TYPE_FOVEATED_VIEW_CONFIGURATION_VIEW_VARJO):
				return "XR_TYPE_FOVEATED_VIEW_CONFIGURATION_VIEW_VARJO";
				break;
			case(XR_TYPE_SYSTEM_FOVEATED_RENDERING_PROPERTIES_VARJO):
				return "XR_TYPE_SYSTEM_FOVEATED_RENDERING_PROPERTIES_VARJO";
				break;
			#endif /*  defined(XR_VARJO_foveated_rendering)  */
			#if defined(XR_VARJO_marker_tracking)
			case(XR_TYPE_SYSTEM_MARKER_TRACKING_PROPERTIES_VARJO):
				return "XR_TYPE_SYSTEM_MARKER_TRACKING_PROPERTIES_VARJO";
				break;
			case(XR_TYPE_EVENT_DATA_MARKER_TRACKING_UPDATE_VARJO):
				return "XR_TYPE_EVENT_DATA_MARKER_TRACKING_UPDATE_VARJO";
				break;
			case(XR_TYPE_MARKER_SPACE_CREATE_INFO_VARJO):
				return "XR_TYPE_MARKER_SPACE_CREATE_INFO_VARJO";
				break;
			#endif /*  defined(XR_VARJO_marker_tracking)  */
			default:
				return "XrStructureType_TOSTR_ERROR";

		}

	}

	#if defined(XR_MSFT_scene_understanding)
	const char* vtostr8_XrSceneComputeFeatureMSFT(XrSceneComputeFeatureMSFT In){
		switch(In){
			case(XR_SCENE_COMPUTE_FEATURE_PLANE_MSFT):
				return "XR_SCENE_COMPUTE_FEATURE_PLANE_MSFT";
				break;
			case(XR_SCENE_COMPUTE_FEATURE_PLANE_MESH_MSFT):
				return "XR_SCENE_COMPUTE_FEATURE_PLANE_MESH_MSFT";
				break;
			case(XR_SCENE_COMPUTE_FEATURE_VISUAL_MESH_MSFT):
				return "XR_SCENE_COMPUTE_FEATURE_VISUAL_MESH_MSFT";
				break;
			case(XR_SCENE_COMPUTE_FEATURE_COLLIDER_MESH_MSFT):
				return "XR_SCENE_COMPUTE_FEATURE_COLLIDER_MESH_MSFT";
				break;
			#if defined(XR_MSFT_scene_marker)
			case(XR_SCENE_COMPUTE_FEATURE_MARKER_MSFT):
				return "XR_SCENE_COMPUTE_FEATURE_MARKER_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_marker)  */
			#if defined(XR_MSFT_scene_understanding_serialization)
			case(XR_SCENE_COMPUTE_FEATURE_SERIALIZE_SCENE_MSFT):
				return "XR_SCENE_COMPUTE_FEATURE_SERIALIZE_SCENE_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_understanding_serialization)  */
			default:
				return "XrSceneComputeFeatureMSFT_TOSTR_ERROR";

		}

	}

	#endif


	//SECTION(V): XRMYTH_SPECIAL_ENUM32_IMPL
	#if defined(XR_FB_spatial_entity)
	const vchar* vtostr32_XrSpaceComponentTypeFB(XrSpaceComponentTypeFB In){
		switch(In){
			case(XR_SPACE_COMPONENT_TYPE_LOCATABLE_FB):
				return U"XR_SPACE_COMPONENT_TYPE_LOCATABLE_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_STORABLE_FB):
				return U"XR_SPACE_COMPONENT_TYPE_STORABLE_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_SHARABLE_FB):
				return U"XR_SPACE_COMPONENT_TYPE_SHARABLE_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_BOUNDED_2D_FB):
				return U"XR_SPACE_COMPONENT_TYPE_BOUNDED_2D_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_BOUNDED_3D_FB):
				return U"XR_SPACE_COMPONENT_TYPE_BOUNDED_3D_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_SEMANTIC_LABELS_FB):
				return U"XR_SPACE_COMPONENT_TYPE_SEMANTIC_LABELS_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_ROOM_LAYOUT_FB):
				return U"XR_SPACE_COMPONENT_TYPE_ROOM_LAYOUT_FB";
				break;
			case(XR_SPACE_COMPONENT_TYPE_SPACE_CONTAINER_FB):
				return U"XR_SPACE_COMPONENT_TYPE_SPACE_CONTAINER_FB";
				break;
			#if defined(XR_META_spatial_entity_mesh)
			case(XR_SPACE_COMPONENT_TYPE_TRIANGLE_MESH_META):
				return U"XR_SPACE_COMPONENT_TYPE_TRIANGLE_MESH_META";
				break;
			#endif /*  defined(XR_META_spatial_entity_mesh)  */
			default:
				return U"XrSpaceComponentTypeFB_TOSTR_ERROR";

		}

	}

	#endif

	#if defined(XR_MSFT_scene_understanding)
	const vchar* vtostr32_XrSceneComponentTypeMSFT(XrSceneComponentTypeMSFT In){
		switch(In){
			case(XR_SCENE_COMPONENT_TYPE_INVALID_MSFT):
				return U"XR_SCENE_COMPONENT_TYPE_INVALID_MSFT";
				break;
			case(XR_SCENE_COMPONENT_TYPE_OBJECT_MSFT):
				return U"XR_SCENE_COMPONENT_TYPE_OBJECT_MSFT";
				break;
			case(XR_SCENE_COMPONENT_TYPE_PLANE_MSFT):
				return U"XR_SCENE_COMPONENT_TYPE_PLANE_MSFT";
				break;
			case(XR_SCENE_COMPONENT_TYPE_VISUAL_MESH_MSFT):
				return U"XR_SCENE_COMPONENT_TYPE_VISUAL_MESH_MSFT";
				break;
			case(XR_SCENE_COMPONENT_TYPE_COLLIDER_MESH_MSFT):
				return U"XR_SCENE_COMPONENT_TYPE_COLLIDER_MESH_MSFT";
				break;
			#if defined(XR_MSFT_scene_marker)
			case(XR_SCENE_COMPONENT_TYPE_MARKER_MSFT):
				return U"XR_SCENE_COMPONENT_TYPE_MARKER_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_marker)  */
			#if defined(XR_MSFT_scene_understanding_serialization)
			case(XR_SCENE_COMPONENT_TYPE_SERIALIZED_SCENE_FRAGMENT_MSFT):
				return U"XR_SCENE_COMPONENT_TYPE_SERIALIZED_SCENE_FRAGMENT_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_understanding_serialization)  */
			default:
				return U"XrSceneComponentTypeMSFT_TOSTR_ERROR";

		}

	}

	#endif

	#if defined(XR_VERSION_1_0)
	const vchar* vtostr32_XrObjectType(XrObjectType In){
		switch(In){
			case(XR_OBJECT_TYPE_UNKNOWN):
				return U"XR_OBJECT_TYPE_UNKNOWN";
				break;
			case(XR_OBJECT_TYPE_INSTANCE):
				return U"XR_OBJECT_TYPE_INSTANCE";
				break;
			case(XR_OBJECT_TYPE_SESSION):
				return U"XR_OBJECT_TYPE_SESSION";
				break;
			case(XR_OBJECT_TYPE_SWAPCHAIN):
				return U"XR_OBJECT_TYPE_SWAPCHAIN";
				break;
			case(XR_OBJECT_TYPE_SPACE):
				return U"XR_OBJECT_TYPE_SPACE";
				break;
			case(XR_OBJECT_TYPE_ACTION_SET):
				return U"XR_OBJECT_TYPE_ACTION_SET";
				break;
			case(XR_OBJECT_TYPE_ACTION):
				return U"XR_OBJECT_TYPE_ACTION";
				break;
			#if defined(XR_EXT_debug_utils)
			case(XR_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT):
				return U"XR_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT";
				break;
			#endif /*  defined(XR_EXT_debug_utils)  */
			#if defined(XR_EXT_hand_tracking)
			case(XR_OBJECT_TYPE_HAND_TRACKER_EXT):
				return U"XR_OBJECT_TYPE_HAND_TRACKER_EXT";
				break;
			#endif /*  defined(XR_EXT_hand_tracking)  */
			#if defined(XR_EXT_plane_detection)
			case(XR_OBJECT_TYPE_PLANE_DETECTOR_EXT):
				return U"XR_OBJECT_TYPE_PLANE_DETECTOR_EXT";
				break;
			#endif /*  defined(XR_EXT_plane_detection)  */
			#if defined(XR_FB_body_tracking)
			case(XR_OBJECT_TYPE_BODY_TRACKER_FB):
				return U"XR_OBJECT_TYPE_BODY_TRACKER_FB";
				break;
			#endif /*  defined(XR_FB_body_tracking)  */
			#if defined(XR_FB_eye_tracking_social)
			case(XR_OBJECT_TYPE_EYE_TRACKER_FB):
				return U"XR_OBJECT_TYPE_EYE_TRACKER_FB";
				break;
			#endif /*  defined(XR_FB_eye_tracking_social)  */
			#if defined(XR_FB_face_tracking)
			case(XR_OBJECT_TYPE_FACE_TRACKER_FB):
				return U"XR_OBJECT_TYPE_FACE_TRACKER_FB";
				break;
			#endif /*  defined(XR_FB_face_tracking)  */
			#if defined(XR_FB_face_tracking2)
			case(XR_OBJECT_TYPE_FACE_TRACKER2_FB):
				return U"XR_OBJECT_TYPE_FACE_TRACKER2_FB";
				break;
			#endif /*  defined(XR_FB_face_tracking2)  */
			#if defined(XR_FB_foveation)
			case(XR_OBJECT_TYPE_FOVEATION_PROFILE_FB):
				return U"XR_OBJECT_TYPE_FOVEATION_PROFILE_FB";
				break;
			#endif /*  defined(XR_FB_foveation)  */
			#if defined(XR_FB_passthrough)
			case(XR_OBJECT_TYPE_PASSTHROUGH_FB):
				return U"XR_OBJECT_TYPE_PASSTHROUGH_FB";
				break;
			case(XR_OBJECT_TYPE_PASSTHROUGH_LAYER_FB):
				return U"XR_OBJECT_TYPE_PASSTHROUGH_LAYER_FB";
				break;
			case(XR_OBJECT_TYPE_GEOMETRY_INSTANCE_FB):
				return U"XR_OBJECT_TYPE_GEOMETRY_INSTANCE_FB";
				break;
			#endif /*  defined(XR_FB_passthrough)  */
			#if defined(XR_FB_spatial_entity_user)
			case(XR_OBJECT_TYPE_SPACE_USER_FB):
				return U"XR_OBJECT_TYPE_SPACE_USER_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_user)  */
			#if defined(XR_FB_triangle_mesh)
			case(XR_OBJECT_TYPE_TRIANGLE_MESH_FB):
				return U"XR_OBJECT_TYPE_TRIANGLE_MESH_FB";
				break;
			#endif /*  defined(XR_FB_triangle_mesh)  */
			#if defined(XR_HTC_body_tracking)
			case(XR_OBJECT_TYPE_BODY_TRACKER_HTC):
				return U"XR_OBJECT_TYPE_BODY_TRACKER_HTC";
				break;
			#endif /*  defined(XR_HTC_body_tracking)  */
			#if defined(XR_HTC_facial_tracking)
			case(XR_OBJECT_TYPE_FACIAL_TRACKER_HTC):
				return U"XR_OBJECT_TYPE_FACIAL_TRACKER_HTC";
				break;
			#endif /*  defined(XR_HTC_facial_tracking)  */
			#if defined(XR_HTC_passthrough)
			case(XR_OBJECT_TYPE_PASSTHROUGH_HTC):
				return U"XR_OBJECT_TYPE_PASSTHROUGH_HTC";
				break;
			#endif /*  defined(XR_HTC_passthrough)  */
			#if defined(XR_META_environment_depth)
			case(XR_OBJECT_TYPE_ENVIRONMENT_DEPTH_PROVIDER_META):
				return U"XR_OBJECT_TYPE_ENVIRONMENT_DEPTH_PROVIDER_META";
				break;
			case(XR_OBJECT_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_META):
				return U"XR_OBJECT_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_META";
				break;
			#endif /*  defined(XR_META_environment_depth)  */
			#if defined(XR_META_passthrough_color_lut)
			case(XR_OBJECT_TYPE_PASSTHROUGH_COLOR_LUT_META):
				return U"XR_OBJECT_TYPE_PASSTHROUGH_COLOR_LUT_META";
				break;
			#endif /*  defined(XR_META_passthrough_color_lut)  */
			#if defined(XR_META_virtual_keyboard)
			case(XR_OBJECT_TYPE_VIRTUAL_KEYBOARD_META):
				return U"XR_OBJECT_TYPE_VIRTUAL_KEYBOARD_META";
				break;
			#endif /*  defined(XR_META_virtual_keyboard)  */
			#if defined(XR_ML_localization_map)
			case(XR_OBJECT_TYPE_EXPORTED_LOCALIZATION_MAP_ML):
				return U"XR_OBJECT_TYPE_EXPORTED_LOCALIZATION_MAP_ML";
				break;
			#endif /*  defined(XR_ML_localization_map)  */
			#if defined(XR_ML_marker_understanding)
			case(XR_OBJECT_TYPE_MARKER_DETECTOR_ML):
				return U"XR_OBJECT_TYPE_MARKER_DETECTOR_ML";
				break;
			#endif /*  defined(XR_ML_marker_understanding)  */
			#if defined(XR_ML_spatial_anchors_storage)
			case(XR_OBJECT_TYPE_SPATIAL_ANCHORS_STORAGE_ML):
				return U"XR_OBJECT_TYPE_SPATIAL_ANCHORS_STORAGE_ML";
				break;
			#endif /*  defined(XR_ML_spatial_anchors_storage)  */
			#if defined(XR_ML_world_mesh_detection)
			case(XR_OBJECT_TYPE_WORLD_MESH_DETECTOR_ML):
				return U"XR_OBJECT_TYPE_WORLD_MESH_DETECTOR_ML";
				break;
			#endif /*  defined(XR_ML_world_mesh_detection)  */
			#if defined(XR_MSFT_scene_understanding)
			case(XR_OBJECT_TYPE_SCENE_OBSERVER_MSFT):
				return U"XR_OBJECT_TYPE_SCENE_OBSERVER_MSFT";
				break;
			case(XR_OBJECT_TYPE_SCENE_MSFT):
				return U"XR_OBJECT_TYPE_SCENE_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_understanding)  */
			#if defined(XR_MSFT_spatial_anchor)
			case(XR_OBJECT_TYPE_SPATIAL_ANCHOR_MSFT):
				return U"XR_OBJECT_TYPE_SPATIAL_ANCHOR_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_anchor)  */
			#if defined(XR_MSFT_spatial_anchor_persistence)
			case(XR_OBJECT_TYPE_SPATIAL_ANCHOR_STORE_CONNECTION_MSFT):
				return U"XR_OBJECT_TYPE_SPATIAL_ANCHOR_STORE_CONNECTION_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_anchor_persistence)  */
			#if defined(XR_MSFT_spatial_graph_bridge)
			case(XR_OBJECT_TYPE_SPATIAL_GRAPH_NODE_BINDING_MSFT):
				return U"XR_OBJECT_TYPE_SPATIAL_GRAPH_NODE_BINDING_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_graph_bridge)  */
			default:
				return U"XrObjectType_TOSTR_ERROR";

		}

	}

	#endif

	const vchar* vtostr32_XrPassthroughLayerPurposeFB(XrPassthroughLayerPurposeFB In){
		switch(In){
			case(XR_PASSTHROUGH_LAYER_PURPOSE_RECONSTRUCTION_FB):
				return U"XR_PASSTHROUGH_LAYER_PURPOSE_RECONSTRUCTION_FB";
				break;
			case(XR_PASSTHROUGH_LAYER_PURPOSE_PROJECTED_FB):
				return U"XR_PASSTHROUGH_LAYER_PURPOSE_PROJECTED_FB";
				break;
			#if defined(XR_FB_passthrough_keyboard_hands)
			case(XR_PASSTHROUGH_LAYER_PURPOSE_TRACKED_KEYBOARD_HANDS_FB):
				return U"XR_PASSTHROUGH_LAYER_PURPOSE_TRACKED_KEYBOARD_HANDS_FB";
				break;
			case(XR_PASSTHROUGH_LAYER_PURPOSE_TRACKED_KEYBOARD_MASKED_HANDS_FB):
				return U"XR_PASSTHROUGH_LAYER_PURPOSE_TRACKED_KEYBOARD_MASKED_HANDS_FB";
				break;
			#endif /*  defined(XR_FB_passthrough_keyboard_hands)  */
			default:
				return U"XrPassthroughLayerPurposeFB_TOSTR_ERROR";

		}

	}

	#if defined(XR_EXT_hand_tracking)
	const vchar* vtostr32_XrHandJointSetEXT(XrHandJointSetEXT In){
		switch(In){
			case(XR_HAND_JOINT_SET_DEFAULT_EXT):
				return U"XR_HAND_JOINT_SET_DEFAULT_EXT";
				break;
			#if defined(XR_ULTRALEAP_hand_tracking_forearm)
			case(XR_HAND_JOINT_SET_HAND_WITH_FOREARM_ULTRALEAP):
				return U"XR_HAND_JOINT_SET_HAND_WITH_FOREARM_ULTRALEAP";
				break;
			#endif /*  defined(XR_ULTRALEAP_hand_tracking_forearm)  */
			default:
				return U"XrHandJointSetEXT_TOSTR_ERROR";

		}

	}

	#endif

	const vchar* vtostr32_XrViewConfigurationType(XrViewConfigurationType In){
		switch(In){
			case(XR_VIEW_CONFIGURATION_TYPE_PRIMARY_MONO):
				return U"XR_VIEW_CONFIGURATION_TYPE_PRIMARY_MONO";
				break;
			case(XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO):
				return U"XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO";
				break;
			#if defined(XR_MSFT_first_person_observer)
			case(XR_VIEW_CONFIGURATION_TYPE_SECONDARY_MONO_FIRST_PERSON_OBSERVER_MSFT):
				return U"XR_VIEW_CONFIGURATION_TYPE_SECONDARY_MONO_FIRST_PERSON_OBSERVER_MSFT";
				break;
			#endif /*  defined(XR_MSFT_first_person_observer)  */
			default:
				return U"XrViewConfigurationType_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrReferenceSpaceType(XrReferenceSpaceType In){
		switch(In){
			case(XR_REFERENCE_SPACE_TYPE_VIEW):
				return U"XR_REFERENCE_SPACE_TYPE_VIEW";
				break;
			case(XR_REFERENCE_SPACE_TYPE_LOCAL):
				return U"XR_REFERENCE_SPACE_TYPE_LOCAL";
				break;
			case(XR_REFERENCE_SPACE_TYPE_STAGE):
				return U"XR_REFERENCE_SPACE_TYPE_STAGE";
				break;
			#if defined(XR_ML_localization_map)
			case(XR_REFERENCE_SPACE_TYPE_LOCALIZATION_MAP_ML):
				return U"XR_REFERENCE_SPACE_TYPE_LOCALIZATION_MAP_ML";
				break;
			#endif /*  defined(XR_ML_localization_map)  */
			#if defined(XR_MSFT_unbounded_reference_space)
			case(XR_REFERENCE_SPACE_TYPE_UNBOUNDED_MSFT):
				return U"XR_REFERENCE_SPACE_TYPE_UNBOUNDED_MSFT";
				break;
			#endif /*  defined(XR_MSFT_unbounded_reference_space)  */
			#if defined(XR_VARJO_foveated_rendering)
			case(XR_REFERENCE_SPACE_TYPE_COMBINED_EYE_VARJO):
				return U"XR_REFERENCE_SPACE_TYPE_COMBINED_EYE_VARJO";
				break;
			#endif /*  defined(XR_VARJO_foveated_rendering)  */
			default:
				return U"XrReferenceSpaceType_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrResult(XrResult In){
		switch(In){
			case(XR_SUCCESS):
				return U"XR_SUCCESS";
				break;
			case(XR_TIMEOUT_EXPIRED):
				return U"XR_TIMEOUT_EXPIRED";
				break;
			case(XR_SESSION_LOSS_PENDING):
				return U"XR_SESSION_LOSS_PENDING";
				break;
			case(XR_EVENT_UNAVAILABLE):
				return U"XR_EVENT_UNAVAILABLE";
				break;
			case(XR_SPACE_BOUNDS_UNAVAILABLE):
				return U"XR_SPACE_BOUNDS_UNAVAILABLE";
				break;
			case(XR_SESSION_NOT_FOCUSED):
				return U"XR_SESSION_NOT_FOCUSED";
				break;
			case(XR_FRAME_DISCARDED):
				return U"XR_FRAME_DISCARDED";
				break;
			case(XR_ERROR_VALIDATION_FAILURE):
				return U"XR_ERROR_VALIDATION_FAILURE";
				break;
			case(XR_ERROR_RUNTIME_FAILURE):
				return U"XR_ERROR_RUNTIME_FAILURE";
				break;
			case(XR_ERROR_OUT_OF_MEMORY):
				return U"XR_ERROR_OUT_OF_MEMORY";
				break;
			case(XR_ERROR_API_VERSION_UNSUPPORTED):
				return U"XR_ERROR_API_VERSION_UNSUPPORTED";
				break;
			case(XR_ERROR_INITIALIZATION_FAILED):
				return U"XR_ERROR_INITIALIZATION_FAILED";
				break;
			case(XR_ERROR_FUNCTION_UNSUPPORTED):
				return U"XR_ERROR_FUNCTION_UNSUPPORTED";
				break;
			case(XR_ERROR_FEATURE_UNSUPPORTED):
				return U"XR_ERROR_FEATURE_UNSUPPORTED";
				break;
			case(XR_ERROR_EXTENSION_NOT_PRESENT):
				return U"XR_ERROR_EXTENSION_NOT_PRESENT";
				break;
			case(XR_ERROR_LIMIT_REACHED):
				return U"XR_ERROR_LIMIT_REACHED";
				break;
			case(XR_ERROR_SIZE_INSUFFICIENT):
				return U"XR_ERROR_SIZE_INSUFFICIENT";
				break;
			case(XR_ERROR_HANDLE_INVALID):
				return U"XR_ERROR_HANDLE_INVALID";
				break;
			case(XR_ERROR_INSTANCE_LOST):
				return U"XR_ERROR_INSTANCE_LOST";
				break;
			case(XR_ERROR_SESSION_RUNNING):
				return U"XR_ERROR_SESSION_RUNNING";
				break;
			case(XR_ERROR_SESSION_NOT_RUNNING):
				return U"XR_ERROR_SESSION_NOT_RUNNING";
				break;
			case(XR_ERROR_SESSION_LOST):
				return U"XR_ERROR_SESSION_LOST";
				break;
			case(XR_ERROR_SYSTEM_INVALID):
				return U"XR_ERROR_SYSTEM_INVALID";
				break;
			case(XR_ERROR_PATH_INVALID):
				return U"XR_ERROR_PATH_INVALID";
				break;
			case(XR_ERROR_PATH_COUNT_EXCEEDED):
				return U"XR_ERROR_PATH_COUNT_EXCEEDED";
				break;
			case(XR_ERROR_PATH_FORMAT_INVALID):
				return U"XR_ERROR_PATH_FORMAT_INVALID";
				break;
			case(XR_ERROR_PATH_UNSUPPORTED):
				return U"XR_ERROR_PATH_UNSUPPORTED";
				break;
			case(XR_ERROR_LAYER_INVALID):
				return U"XR_ERROR_LAYER_INVALID";
				break;
			case(XR_ERROR_LAYER_LIMIT_EXCEEDED):
				return U"XR_ERROR_LAYER_LIMIT_EXCEEDED";
				break;
			case(XR_ERROR_SWAPCHAIN_RECT_INVALID):
				return U"XR_ERROR_SWAPCHAIN_RECT_INVALID";
				break;
			case(XR_ERROR_SWAPCHAIN_FORMAT_UNSUPPORTED):
				return U"XR_ERROR_SWAPCHAIN_FORMAT_UNSUPPORTED";
				break;
			case(XR_ERROR_ACTION_TYPE_MISMATCH):
				return U"XR_ERROR_ACTION_TYPE_MISMATCH";
				break;
			case(XR_ERROR_SESSION_NOT_READY):
				return U"XR_ERROR_SESSION_NOT_READY";
				break;
			case(XR_ERROR_SESSION_NOT_STOPPING):
				return U"XR_ERROR_SESSION_NOT_STOPPING";
				break;
			case(XR_ERROR_TIME_INVALID):
				return U"XR_ERROR_TIME_INVALID";
				break;
			case(XR_ERROR_REFERENCE_SPACE_UNSUPPORTED):
				return U"XR_ERROR_REFERENCE_SPACE_UNSUPPORTED";
				break;
			case(XR_ERROR_FILE_ACCESS_ERROR):
				return U"XR_ERROR_FILE_ACCESS_ERROR";
				break;
			case(XR_ERROR_FILE_CONTENTS_INVALID):
				return U"XR_ERROR_FILE_CONTENTS_INVALID";
				break;
			case(XR_ERROR_FORM_FACTOR_UNSUPPORTED):
				return U"XR_ERROR_FORM_FACTOR_UNSUPPORTED";
				break;
			case(XR_ERROR_FORM_FACTOR_UNAVAILABLE):
				return U"XR_ERROR_FORM_FACTOR_UNAVAILABLE";
				break;
			case(XR_ERROR_API_LAYER_NOT_PRESENT):
				return U"XR_ERROR_API_LAYER_NOT_PRESENT";
				break;
			case(XR_ERROR_CALL_ORDER_INVALID):
				return U"XR_ERROR_CALL_ORDER_INVALID";
				break;
			case(XR_ERROR_GRAPHICS_DEVICE_INVALID):
				return U"XR_ERROR_GRAPHICS_DEVICE_INVALID";
				break;
			case(XR_ERROR_POSE_INVALID):
				return U"XR_ERROR_POSE_INVALID";
				break;
			case(XR_ERROR_INDEX_OUT_OF_RANGE):
				return U"XR_ERROR_INDEX_OUT_OF_RANGE";
				break;
			case(XR_ERROR_VIEW_CONFIGURATION_TYPE_UNSUPPORTED):
				return U"XR_ERROR_VIEW_CONFIGURATION_TYPE_UNSUPPORTED";
				break;
			case(XR_ERROR_ENVIRONMENT_BLEND_MODE_UNSUPPORTED):
				return U"XR_ERROR_ENVIRONMENT_BLEND_MODE_UNSUPPORTED";
				break;
			case(XR_ERROR_NAME_DUPLICATED):
				return U"XR_ERROR_NAME_DUPLICATED";
				break;
			case(XR_ERROR_NAME_INVALID):
				return U"XR_ERROR_NAME_INVALID";
				break;
			case(XR_ERROR_ACTIONSET_NOT_ATTACHED):
				return U"XR_ERROR_ACTIONSET_NOT_ATTACHED";
				break;
			case(XR_ERROR_ACTIONSETS_ALREADY_ATTACHED):
				return U"XR_ERROR_ACTIONSETS_ALREADY_ATTACHED";
				break;
			case(XR_ERROR_LOCALIZED_NAME_DUPLICATED):
				return U"XR_ERROR_LOCALIZED_NAME_DUPLICATED";
				break;
			case(XR_ERROR_LOCALIZED_NAME_INVALID):
				return U"XR_ERROR_LOCALIZED_NAME_INVALID";
				break;
			case(XR_ERROR_GRAPHICS_REQUIREMENTS_CALL_MISSING):
				return U"XR_ERROR_GRAPHICS_REQUIREMENTS_CALL_MISSING";
				break;
			case(XR_ERROR_RUNTIME_UNAVAILABLE):
				return U"XR_ERROR_RUNTIME_UNAVAILABLE";
				break;
			#if defined(XR_EXT_future)
			case(XR_ERROR_FUTURE_PENDING_EXT):
				return U"XR_ERROR_FUTURE_PENDING_EXT";
				break;
			case(XR_ERROR_FUTURE_INVALID_EXT):
				return U"XR_ERROR_FUTURE_INVALID_EXT";
				break;
			#endif /*  defined(XR_EXT_future)  */
			#if defined(XR_EXT_plane_detection)
			case(XR_ERROR_SPACE_NOT_LOCATABLE_EXT):
				return U"XR_ERROR_SPACE_NOT_LOCATABLE_EXT";
				break;
			case(XR_ERROR_PLANE_DETECTION_PERMISSION_DENIED_EXT):
				return U"XR_ERROR_PLANE_DETECTION_PERMISSION_DENIED_EXT";
				break;
			#endif /*  defined(XR_EXT_plane_detection)  */
			#if defined(XR_FB_color_space)
			case(XR_ERROR_COLOR_SPACE_UNSUPPORTED_FB):
				return U"XR_ERROR_COLOR_SPACE_UNSUPPORTED_FB";
				break;
			#endif /*  defined(XR_FB_color_space)  */
			#if defined(XR_FB_display_refresh_rate)
			case(XR_ERROR_DISPLAY_REFRESH_RATE_UNSUPPORTED_FB):
				return U"XR_ERROR_DISPLAY_REFRESH_RATE_UNSUPPORTED_FB";
				break;
			#endif /*  defined(XR_FB_display_refresh_rate)  */
			#if defined(XR_FB_passthrough)
			case(XR_ERROR_UNEXPECTED_STATE_PASSTHROUGH_FB):
				return U"XR_ERROR_UNEXPECTED_STATE_PASSTHROUGH_FB";
				break;
			case(XR_ERROR_FEATURE_ALREADY_CREATED_PASSTHROUGH_FB):
				return U"XR_ERROR_FEATURE_ALREADY_CREATED_PASSTHROUGH_FB";
				break;
			case(XR_ERROR_FEATURE_REQUIRED_PASSTHROUGH_FB):
				return U"XR_ERROR_FEATURE_REQUIRED_PASSTHROUGH_FB";
				break;
			case(XR_ERROR_NOT_PERMITTED_PASSTHROUGH_FB):
				return U"XR_ERROR_NOT_PERMITTED_PASSTHROUGH_FB";
				break;
			case(XR_ERROR_INSUFFICIENT_RESOURCES_PASSTHROUGH_FB):
				return U"XR_ERROR_INSUFFICIENT_RESOURCES_PASSTHROUGH_FB";
				break;
			case(XR_ERROR_UNKNOWN_PASSTHROUGH_FB):
				return U"XR_ERROR_UNKNOWN_PASSTHROUGH_FB";
				break;
			#endif /*  defined(XR_FB_passthrough)  */
			#if defined(XR_FB_render_model)
			case(XR_ERROR_RENDER_MODEL_KEY_INVALID_FB):
				return U"XR_ERROR_RENDER_MODEL_KEY_INVALID_FB";
				break;
			case(XR_RENDER_MODEL_UNAVAILABLE_FB):
				return U"XR_RENDER_MODEL_UNAVAILABLE_FB";
				break;
			#endif /*  defined(XR_FB_render_model)  */
			#if defined(XR_FB_spatial_entity)
			case(XR_ERROR_SPACE_COMPONENT_NOT_SUPPORTED_FB):
				return U"XR_ERROR_SPACE_COMPONENT_NOT_SUPPORTED_FB";
				break;
			case(XR_ERROR_SPACE_COMPONENT_NOT_ENABLED_FB):
				return U"XR_ERROR_SPACE_COMPONENT_NOT_ENABLED_FB";
				break;
			case(XR_ERROR_SPACE_COMPONENT_STATUS_PENDING_FB):
				return U"XR_ERROR_SPACE_COMPONENT_STATUS_PENDING_FB";
				break;
			case(XR_ERROR_SPACE_COMPONENT_STATUS_ALREADY_SET_FB):
				return U"XR_ERROR_SPACE_COMPONENT_STATUS_ALREADY_SET_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity)  */
			#if defined(XR_FB_spatial_entity_sharing)
			case(XR_ERROR_SPACE_MAPPING_INSUFFICIENT_FB):
				return U"XR_ERROR_SPACE_MAPPING_INSUFFICIENT_FB";
				break;
			case(XR_ERROR_SPACE_LOCALIZATION_FAILED_FB):
				return U"XR_ERROR_SPACE_LOCALIZATION_FAILED_FB";
				break;
			case(XR_ERROR_SPACE_NETWORK_TIMEOUT_FB):
				return U"XR_ERROR_SPACE_NETWORK_TIMEOUT_FB";
				break;
			case(XR_ERROR_SPACE_NETWORK_REQUEST_FAILED_FB):
				return U"XR_ERROR_SPACE_NETWORK_REQUEST_FAILED_FB";
				break;
			case(XR_ERROR_SPACE_CLOUD_STORAGE_DISABLED_FB):
				return U"XR_ERROR_SPACE_CLOUD_STORAGE_DISABLED_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_sharing)  */
			#if defined(XR_HTC_anchor)
			case(XR_ERROR_NOT_AN_ANCHOR_HTC):
				return U"XR_ERROR_NOT_AN_ANCHOR_HTC";
				break;
			#endif /*  defined(XR_HTC_anchor)  */
			#if defined(XR_KHR_android_thread_settings)
			case(XR_ERROR_ANDROID_THREAD_SETTINGS_ID_INVALID_KHR):
				return U"XR_ERROR_ANDROID_THREAD_SETTINGS_ID_INVALID_KHR";
				break;
			case(XR_ERROR_ANDROID_THREAD_SETTINGS_FAILURE_KHR):
				return U"XR_ERROR_ANDROID_THREAD_SETTINGS_FAILURE_KHR";
				break;
			#endif /*  defined(XR_KHR_android_thread_settings)  */
			#if defined(XR_META_environment_depth)
			case(XR_ENVIRONMENT_DEPTH_NOT_AVAILABLE_META):
				return U"XR_ENVIRONMENT_DEPTH_NOT_AVAILABLE_META";
				break;
			#endif /*  defined(XR_META_environment_depth)  */
			#if defined(XR_META_passthrough_color_lut)
			case(XR_ERROR_PASSTHROUGH_COLOR_LUT_BUFFER_SIZE_MISMATCH_META):
				return U"XR_ERROR_PASSTHROUGH_COLOR_LUT_BUFFER_SIZE_MISMATCH_META";
				break;
			#endif /*  defined(XR_META_passthrough_color_lut)  */
			#if defined(XR_ML_localization_map)
			case(XR_ERROR_LOCALIZATION_MAP_INCOMPATIBLE_ML):
				return U"XR_ERROR_LOCALIZATION_MAP_INCOMPATIBLE_ML";
				break;
			case(XR_ERROR_LOCALIZATION_MAP_UNAVAILABLE_ML):
				return U"XR_ERROR_LOCALIZATION_MAP_UNAVAILABLE_ML";
				break;
			case(XR_ERROR_LOCALIZATION_MAP_FAIL_ML):
				return U"XR_ERROR_LOCALIZATION_MAP_FAIL_ML";
				break;
			case(XR_ERROR_LOCALIZATION_MAP_IMPORT_EXPORT_PERMISSION_DENIED_ML):
				return U"XR_ERROR_LOCALIZATION_MAP_IMPORT_EXPORT_PERMISSION_DENIED_ML";
				break;
			case(XR_ERROR_LOCALIZATION_MAP_PERMISSION_DENIED_ML):
				return U"XR_ERROR_LOCALIZATION_MAP_PERMISSION_DENIED_ML";
				break;
			case(XR_ERROR_LOCALIZATION_MAP_ALREADY_EXISTS_ML):
				return U"XR_ERROR_LOCALIZATION_MAP_ALREADY_EXISTS_ML";
				break;
			case(XR_ERROR_LOCALIZATION_MAP_CANNOT_EXPORT_CLOUD_MAP_ML):
				return U"XR_ERROR_LOCALIZATION_MAP_CANNOT_EXPORT_CLOUD_MAP_ML";
				break;
			#endif /*  defined(XR_ML_localization_map)  */
			#if defined(XR_ML_marker_understanding)
			case(XR_ERROR_MARKER_DETECTOR_PERMISSION_DENIED_ML):
				return U"XR_ERROR_MARKER_DETECTOR_PERMISSION_DENIED_ML";
				break;
			case(XR_ERROR_MARKER_DETECTOR_LOCATE_FAILED_ML):
				return U"XR_ERROR_MARKER_DETECTOR_LOCATE_FAILED_ML";
				break;
			case(XR_ERROR_MARKER_DETECTOR_INVALID_DATA_QUERY_ML):
				return U"XR_ERROR_MARKER_DETECTOR_INVALID_DATA_QUERY_ML";
				break;
			case(XR_ERROR_MARKER_DETECTOR_INVALID_CREATE_INFO_ML):
				return U"XR_ERROR_MARKER_DETECTOR_INVALID_CREATE_INFO_ML";
				break;
			case(XR_ERROR_MARKER_INVALID_ML):
				return U"XR_ERROR_MARKER_INVALID_ML";
				break;
			#endif /*  defined(XR_ML_marker_understanding)  */
			#if defined(XR_ML_spatial_anchors)
			case(XR_ERROR_SPATIAL_ANCHORS_PERMISSION_DENIED_ML):
				return U"XR_ERROR_SPATIAL_ANCHORS_PERMISSION_DENIED_ML";
				break;
			case(XR_ERROR_SPATIAL_ANCHORS_NOT_LOCALIZED_ML):
				return U"XR_ERROR_SPATIAL_ANCHORS_NOT_LOCALIZED_ML";
				break;
			case(XR_ERROR_SPATIAL_ANCHORS_OUT_OF_MAP_BOUNDS_ML):
				return U"XR_ERROR_SPATIAL_ANCHORS_OUT_OF_MAP_BOUNDS_ML";
				break;
			case(XR_ERROR_SPATIAL_ANCHORS_SPACE_NOT_LOCATABLE_ML):
				return U"XR_ERROR_SPATIAL_ANCHORS_SPACE_NOT_LOCATABLE_ML";
				break;
			#endif /*  defined(XR_ML_spatial_anchors)  */
			#if defined(XR_ML_spatial_anchors_storage)
			case(XR_ERROR_SPATIAL_ANCHORS_ANCHOR_NOT_FOUND_ML):
				return U"XR_ERROR_SPATIAL_ANCHORS_ANCHOR_NOT_FOUND_ML";
				break;
			#endif /*  defined(XR_ML_spatial_anchors_storage)  */
			#if defined(XR_ML_system_notifications)
			case(XR_ERROR_SYSTEM_NOTIFICATION_PERMISSION_DENIED_ML):
				return U"XR_ERROR_SYSTEM_NOTIFICATION_PERMISSION_DENIED_ML";
				break;
			case(XR_ERROR_SYSTEM_NOTIFICATION_INCOMPATIBLE_SKU_ML):
				return U"XR_ERROR_SYSTEM_NOTIFICATION_INCOMPATIBLE_SKU_ML";
				break;
			#endif /*  defined(XR_ML_system_notifications)  */
			#if defined(XR_ML_world_mesh_detection)
			case(XR_ERROR_WORLD_MESH_DETECTOR_PERMISSION_DENIED_ML):
				return U"XR_ERROR_WORLD_MESH_DETECTOR_PERMISSION_DENIED_ML";
				break;
			case(XR_ERROR_WORLD_MESH_DETECTOR_SPACE_NOT_LOCATABLE_ML):
				return U"XR_ERROR_WORLD_MESH_DETECTOR_SPACE_NOT_LOCATABLE_ML";
				break;
			#endif /*  defined(XR_ML_world_mesh_detection)  */
			#if defined(XR_MSFT_composition_layer_reprojection)
			case(XR_ERROR_REPROJECTION_MODE_UNSUPPORTED_MSFT):
				return U"XR_ERROR_REPROJECTION_MODE_UNSUPPORTED_MSFT";
				break;
			#endif /*  defined(XR_MSFT_composition_layer_reprojection)  */
			#if defined(XR_MSFT_controller_model)
			case(XR_ERROR_CONTROLLER_MODEL_KEY_INVALID_MSFT):
				return U"XR_ERROR_CONTROLLER_MODEL_KEY_INVALID_MSFT";
				break;
			#endif /*  defined(XR_MSFT_controller_model)  */
			#if defined(XR_MSFT_scene_marker)
			case(XR_SCENE_MARKER_DATA_NOT_STRING_MSFT):
				return U"XR_SCENE_MARKER_DATA_NOT_STRING_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_marker)  */
			#if defined(XR_MSFT_scene_understanding)
			case(XR_ERROR_COMPUTE_NEW_SCENE_NOT_COMPLETED_MSFT):
				return U"XR_ERROR_COMPUTE_NEW_SCENE_NOT_COMPLETED_MSFT";
				break;
			case(XR_ERROR_SCENE_COMPONENT_ID_INVALID_MSFT):
				return U"XR_ERROR_SCENE_COMPONENT_ID_INVALID_MSFT";
				break;
			case(XR_ERROR_SCENE_COMPONENT_TYPE_MISMATCH_MSFT):
				return U"XR_ERROR_SCENE_COMPONENT_TYPE_MISMATCH_MSFT";
				break;
			case(XR_ERROR_SCENE_MESH_BUFFER_ID_INVALID_MSFT):
				return U"XR_ERROR_SCENE_MESH_BUFFER_ID_INVALID_MSFT";
				break;
			case(XR_ERROR_SCENE_COMPUTE_FEATURE_INCOMPATIBLE_MSFT):
				return U"XR_ERROR_SCENE_COMPUTE_FEATURE_INCOMPATIBLE_MSFT";
				break;
			case(XR_ERROR_SCENE_COMPUTE_CONSISTENCY_MISMATCH_MSFT):
				return U"XR_ERROR_SCENE_COMPUTE_CONSISTENCY_MISMATCH_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_understanding)  */
			#if defined(XR_MSFT_secondary_view_configuration)
			case(XR_ERROR_SECONDARY_VIEW_CONFIGURATION_TYPE_NOT_ENABLED_MSFT):
				return U"XR_ERROR_SECONDARY_VIEW_CONFIGURATION_TYPE_NOT_ENABLED_MSFT";
				break;
			#endif /*  defined(XR_MSFT_secondary_view_configuration)  */
			#if defined(XR_MSFT_spatial_anchor)
			case(XR_ERROR_CREATE_SPATIAL_ANCHOR_FAILED_MSFT):
				return U"XR_ERROR_CREATE_SPATIAL_ANCHOR_FAILED_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_anchor)  */
			#if defined(XR_MSFT_spatial_anchor_persistence)
			case(XR_ERROR_SPATIAL_ANCHOR_NAME_NOT_FOUND_MSFT):
				return U"XR_ERROR_SPATIAL_ANCHOR_NAME_NOT_FOUND_MSFT";
				break;
			case(XR_ERROR_SPATIAL_ANCHOR_NAME_INVALID_MSFT):
				return U"XR_ERROR_SPATIAL_ANCHOR_NAME_INVALID_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_anchor_persistence)  */
			#if defined(XR_QCOM_tracking_optimization_settings)
			case(XR_ERROR_HINT_ALREADY_SET_QCOM):
				return U"XR_ERROR_HINT_ALREADY_SET_QCOM";
				break;
			#endif /*  defined(XR_QCOM_tracking_optimization_settings)  */
			#if defined(XR_VARJO_marker_tracking)
			case(XR_ERROR_MARKER_NOT_TRACKED_VARJO):
				return U"XR_ERROR_MARKER_NOT_TRACKED_VARJO";
				break;
			case(XR_ERROR_MARKER_ID_INVALID_VARJO):
				return U"XR_ERROR_MARKER_ID_INVALID_VARJO";
				break;
			#endif /*  defined(XR_VARJO_marker_tracking)  */
			default:
				return U"XrResult_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrStructureType(XrStructureType In){
		switch(In){
			case(XR_TYPE_UNKNOWN):
				return U"XR_TYPE_UNKNOWN";
				break;
			case(XR_TYPE_API_LAYER_PROPERTIES):
				return U"XR_TYPE_API_LAYER_PROPERTIES";
				break;
			case(XR_TYPE_EXTENSION_PROPERTIES):
				return U"XR_TYPE_EXTENSION_PROPERTIES";
				break;
			case(XR_TYPE_INSTANCE_CREATE_INFO):
				return U"XR_TYPE_INSTANCE_CREATE_INFO";
				break;
			case(XR_TYPE_SYSTEM_GET_INFO):
				return U"XR_TYPE_SYSTEM_GET_INFO";
				break;
			case(XR_TYPE_SYSTEM_PROPERTIES):
				return U"XR_TYPE_SYSTEM_PROPERTIES";
				break;
			case(XR_TYPE_VIEW_LOCATE_INFO):
				return U"XR_TYPE_VIEW_LOCATE_INFO";
				break;
			case(XR_TYPE_VIEW):
				return U"XR_TYPE_VIEW";
				break;
			case(XR_TYPE_SESSION_CREATE_INFO):
				return U"XR_TYPE_SESSION_CREATE_INFO";
				break;
			case(XR_TYPE_SWAPCHAIN_CREATE_INFO):
				return U"XR_TYPE_SWAPCHAIN_CREATE_INFO";
				break;
			case(XR_TYPE_SESSION_BEGIN_INFO):
				return U"XR_TYPE_SESSION_BEGIN_INFO";
				break;
			case(XR_TYPE_VIEW_STATE):
				return U"XR_TYPE_VIEW_STATE";
				break;
			case(XR_TYPE_FRAME_END_INFO):
				return U"XR_TYPE_FRAME_END_INFO";
				break;
			case(XR_TYPE_HAPTIC_VIBRATION):
				return U"XR_TYPE_HAPTIC_VIBRATION";
				break;
			case(XR_TYPE_EVENT_DATA_BUFFER):
				return U"XR_TYPE_EVENT_DATA_BUFFER";
				break;
			case(XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING):
				return U"XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING";
				break;
			case(XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED):
				return U"XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED";
				break;
			case(XR_TYPE_ACTION_STATE_BOOLEAN):
				return U"XR_TYPE_ACTION_STATE_BOOLEAN";
				break;
			case(XR_TYPE_ACTION_STATE_FLOAT):
				return U"XR_TYPE_ACTION_STATE_FLOAT";
				break;
			case(XR_TYPE_ACTION_STATE_VECTOR2F):
				return U"XR_TYPE_ACTION_STATE_VECTOR2F";
				break;
			case(XR_TYPE_ACTION_STATE_POSE):
				return U"XR_TYPE_ACTION_STATE_POSE";
				break;
			case(XR_TYPE_ACTION_SET_CREATE_INFO):
				return U"XR_TYPE_ACTION_SET_CREATE_INFO";
				break;
			case(XR_TYPE_ACTION_CREATE_INFO):
				return U"XR_TYPE_ACTION_CREATE_INFO";
				break;
			case(XR_TYPE_INSTANCE_PROPERTIES):
				return U"XR_TYPE_INSTANCE_PROPERTIES";
				break;
			case(XR_TYPE_FRAME_WAIT_INFO):
				return U"XR_TYPE_FRAME_WAIT_INFO";
				break;
			case(XR_TYPE_COMPOSITION_LAYER_PROJECTION):
				return U"XR_TYPE_COMPOSITION_LAYER_PROJECTION";
				break;
			case(XR_TYPE_COMPOSITION_LAYER_QUAD):
				return U"XR_TYPE_COMPOSITION_LAYER_QUAD";
				break;
			case(XR_TYPE_REFERENCE_SPACE_CREATE_INFO):
				return U"XR_TYPE_REFERENCE_SPACE_CREATE_INFO";
				break;
			case(XR_TYPE_ACTION_SPACE_CREATE_INFO):
				return U"XR_TYPE_ACTION_SPACE_CREATE_INFO";
				break;
			case(XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING):
				return U"XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING";
				break;
			case(XR_TYPE_VIEW_CONFIGURATION_VIEW):
				return U"XR_TYPE_VIEW_CONFIGURATION_VIEW";
				break;
			case(XR_TYPE_SPACE_LOCATION):
				return U"XR_TYPE_SPACE_LOCATION";
				break;
			case(XR_TYPE_SPACE_VELOCITY):
				return U"XR_TYPE_SPACE_VELOCITY";
				break;
			case(XR_TYPE_FRAME_STATE):
				return U"XR_TYPE_FRAME_STATE";
				break;
			case(XR_TYPE_VIEW_CONFIGURATION_PROPERTIES):
				return U"XR_TYPE_VIEW_CONFIGURATION_PROPERTIES";
				break;
			case(XR_TYPE_FRAME_BEGIN_INFO):
				return U"XR_TYPE_FRAME_BEGIN_INFO";
				break;
			case(XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW):
				return U"XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW";
				break;
			case(XR_TYPE_EVENT_DATA_EVENTS_LOST):
				return U"XR_TYPE_EVENT_DATA_EVENTS_LOST";
				break;
			case(XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING):
				return U"XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING";
				break;
			case(XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED):
				return U"XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED";
				break;
			case(XR_TYPE_INTERACTION_PROFILE_STATE):
				return U"XR_TYPE_INTERACTION_PROFILE_STATE";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO):
				return U"XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO):
				return U"XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO):
				return U"XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO";
				break;
			case(XR_TYPE_ACTION_STATE_GET_INFO):
				return U"XR_TYPE_ACTION_STATE_GET_INFO";
				break;
			case(XR_TYPE_HAPTIC_ACTION_INFO):
				return U"XR_TYPE_HAPTIC_ACTION_INFO";
				break;
			case(XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO):
				return U"XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO";
				break;
			case(XR_TYPE_ACTIONS_SYNC_INFO):
				return U"XR_TYPE_ACTIONS_SYNC_INFO";
				break;
			case(XR_TYPE_BOUND_SOURCES_FOR_ACTION_ENUMERATE_INFO):
				return U"XR_TYPE_BOUND_SOURCES_FOR_ACTION_ENUMERATE_INFO";
				break;
			case(XR_TYPE_INPUT_SOURCE_LOCALIZED_NAME_GET_INFO):
				return U"XR_TYPE_INPUT_SOURCE_LOCALIZED_NAME_GET_INFO";
				break;
			#if defined(XR_ALMALENCE_digital_lens_control)
			case(XR_TYPE_DIGITAL_LENS_CONTROL_ALMALENCE):
				return U"XR_TYPE_DIGITAL_LENS_CONTROL_ALMALENCE";
				break;
			#endif /*  defined(XR_ALMALENCE_digital_lens_control)  */
			#if defined(XR_EPIC_view_configuration_fov)
			case(XR_TYPE_VIEW_CONFIGURATION_VIEW_FOV_EPIC):
				return U"XR_TYPE_VIEW_CONFIGURATION_VIEW_FOV_EPIC";
				break;
			#endif /*  defined(XR_EPIC_view_configuration_fov)  */
			#if defined(XR_EXTX_overlay)
			case(XR_TYPE_SESSION_CREATE_INFO_OVERLAY_EXTX):
				return U"XR_TYPE_SESSION_CREATE_INFO_OVERLAY_EXTX";
				break;
			case(XR_TYPE_EVENT_DATA_MAIN_SESSION_VISIBILITY_CHANGED_EXTX):
				return U"XR_TYPE_EVENT_DATA_MAIN_SESSION_VISIBILITY_CHANGED_EXTX";
				break;
			#endif /*  defined(XR_EXTX_overlay)  */
			#if defined(XR_EXT_active_action_set_priority)
			case(XR_TYPE_ACTIVE_ACTION_SET_PRIORITIES_EXT):
				return U"XR_TYPE_ACTIVE_ACTION_SET_PRIORITIES_EXT";
				break;
			#endif /*  defined(XR_EXT_active_action_set_priority)  */
			#if defined(XR_EXT_debug_utils)
			case(XR_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT):
				return U"XR_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT";
				break;
			case(XR_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT):
				return U"XR_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT";
				break;
			case(XR_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT):
				return U"XR_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT";
				break;
			case(XR_TYPE_DEBUG_UTILS_LABEL_EXT):
				return U"XR_TYPE_DEBUG_UTILS_LABEL_EXT";
				break;
			#endif /*  defined(XR_EXT_debug_utils)  */
			#if defined(XR_EXT_dpad_binding)
			case(XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT):
				return U"XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT";
				break;
			#endif /*  defined(XR_EXT_dpad_binding)  */
			#if defined(XR_EXT_eye_gaze_interaction)
			case(XR_TYPE_SYSTEM_EYE_GAZE_INTERACTION_PROPERTIES_EXT):
				return U"XR_TYPE_SYSTEM_EYE_GAZE_INTERACTION_PROPERTIES_EXT";
				break;
			case(XR_TYPE_EYE_GAZE_SAMPLE_TIME_EXT):
				return U"XR_TYPE_EYE_GAZE_SAMPLE_TIME_EXT";
				break;
			#endif /*  defined(XR_EXT_eye_gaze_interaction)  */
			#if defined(XR_EXT_future)
			case(XR_TYPE_FUTURE_CANCEL_INFO_EXT):
				return U"XR_TYPE_FUTURE_CANCEL_INFO_EXT";
				break;
			case(XR_TYPE_FUTURE_POLL_INFO_EXT):
				return U"XR_TYPE_FUTURE_POLL_INFO_EXT";
				break;
			case(XR_TYPE_FUTURE_COMPLETION_EXT):
				return U"XR_TYPE_FUTURE_COMPLETION_EXT";
				break;
			case(XR_TYPE_FUTURE_POLL_RESULT_EXT):
				return U"XR_TYPE_FUTURE_POLL_RESULT_EXT";
				break;
			#endif /*  defined(XR_EXT_future)  */
			#if defined(XR_EXT_hand_joints_motion_range)
			case(XR_TYPE_HAND_JOINTS_MOTION_RANGE_INFO_EXT):
				return U"XR_TYPE_HAND_JOINTS_MOTION_RANGE_INFO_EXT";
				break;
			#endif /*  defined(XR_EXT_hand_joints_motion_range)  */
			#if defined(XR_EXT_hand_tracking)
			case(XR_TYPE_SYSTEM_HAND_TRACKING_PROPERTIES_EXT):
				return U"XR_TYPE_SYSTEM_HAND_TRACKING_PROPERTIES_EXT";
				break;
			case(XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT):
				return U"XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT";
				break;
			case(XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT):
				return U"XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT";
				break;
			case(XR_TYPE_HAND_JOINT_LOCATIONS_EXT):
				return U"XR_TYPE_HAND_JOINT_LOCATIONS_EXT";
				break;
			case(XR_TYPE_HAND_JOINT_VELOCITIES_EXT):
				return U"XR_TYPE_HAND_JOINT_VELOCITIES_EXT";
				break;
			#endif /*  defined(XR_EXT_hand_tracking)  */
			#if defined(XR_EXT_hand_tracking_data_source)
			case(XR_TYPE_HAND_TRACKING_DATA_SOURCE_INFO_EXT):
				return U"XR_TYPE_HAND_TRACKING_DATA_SOURCE_INFO_EXT";
				break;
			case(XR_TYPE_HAND_TRACKING_DATA_SOURCE_STATE_EXT):
				return U"XR_TYPE_HAND_TRACKING_DATA_SOURCE_STATE_EXT";
				break;
			#endif /*  defined(XR_EXT_hand_tracking_data_source)  */
			#if defined(XR_EXT_performance_settings)
			case(XR_TYPE_EVENT_DATA_PERF_SETTINGS_EXT):
				return U"XR_TYPE_EVENT_DATA_PERF_SETTINGS_EXT";
				break;
			#endif /*  defined(XR_EXT_performance_settings)  */
			#if defined(XR_EXT_plane_detection)
			case(XR_TYPE_PLANE_DETECTOR_CREATE_INFO_EXT):
				return U"XR_TYPE_PLANE_DETECTOR_CREATE_INFO_EXT";
				break;
			case(XR_TYPE_PLANE_DETECTOR_BEGIN_INFO_EXT):
				return U"XR_TYPE_PLANE_DETECTOR_BEGIN_INFO_EXT";
				break;
			case(XR_TYPE_PLANE_DETECTOR_GET_INFO_EXT):
				return U"XR_TYPE_PLANE_DETECTOR_GET_INFO_EXT";
				break;
			case(XR_TYPE_PLANE_DETECTOR_LOCATIONS_EXT):
				return U"XR_TYPE_PLANE_DETECTOR_LOCATIONS_EXT";
				break;
			case(XR_TYPE_PLANE_DETECTOR_LOCATION_EXT):
				return U"XR_TYPE_PLANE_DETECTOR_LOCATION_EXT";
				break;
			case(XR_TYPE_PLANE_DETECTOR_POLYGON_BUFFER_EXT):
				return U"XR_TYPE_PLANE_DETECTOR_POLYGON_BUFFER_EXT";
				break;
			case(XR_TYPE_SYSTEM_PLANE_DETECTION_PROPERTIES_EXT):
				return U"XR_TYPE_SYSTEM_PLANE_DETECTION_PROPERTIES_EXT";
				break;
			#endif /*  defined(XR_EXT_plane_detection)  */
			#if defined(XR_EXT_user_presence)
			case(XR_TYPE_EVENT_DATA_USER_PRESENCE_CHANGED_EXT):
				return U"XR_TYPE_EVENT_DATA_USER_PRESENCE_CHANGED_EXT";
				break;
			case(XR_TYPE_SYSTEM_USER_PRESENCE_PROPERTIES_EXT):
				return U"XR_TYPE_SYSTEM_USER_PRESENCE_PROPERTIES_EXT";
				break;
			#endif /*  defined(XR_EXT_user_presence)  */
			#if defined(XR_EXT_view_configuration_depth_range)
			case(XR_TYPE_VIEW_CONFIGURATION_DEPTH_RANGE_EXT):
				return U"XR_TYPE_VIEW_CONFIGURATION_DEPTH_RANGE_EXT";
				break;
			#endif /*  defined(XR_EXT_view_configuration_depth_range)  */
			#if defined(XR_FB_android_surface_swapchain_create)
			case(XR_TYPE_ANDROID_SURFACE_SWAPCHAIN_CREATE_INFO_FB):
				return U"XR_TYPE_ANDROID_SURFACE_SWAPCHAIN_CREATE_INFO_FB";
				break;
			#endif /*  defined(XR_FB_android_surface_swapchain_create)  */
			#if defined(XR_FB_body_tracking)
			case(XR_TYPE_BODY_TRACKER_CREATE_INFO_FB):
				return U"XR_TYPE_BODY_TRACKER_CREATE_INFO_FB";
				break;
			case(XR_TYPE_BODY_JOINTS_LOCATE_INFO_FB):
				return U"XR_TYPE_BODY_JOINTS_LOCATE_INFO_FB";
				break;
			case(XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_FB):
				return U"XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_FB";
				break;
			case(XR_TYPE_BODY_JOINT_LOCATIONS_FB):
				return U"XR_TYPE_BODY_JOINT_LOCATIONS_FB";
				break;
			case(XR_TYPE_BODY_SKELETON_FB):
				return U"XR_TYPE_BODY_SKELETON_FB";
				break;
			#endif /*  defined(XR_FB_body_tracking)  */
			#if defined(XR_FB_color_space)
			case(XR_TYPE_SYSTEM_COLOR_SPACE_PROPERTIES_FB):
				return U"XR_TYPE_SYSTEM_COLOR_SPACE_PROPERTIES_FB";
				break;
			#endif /*  defined(XR_FB_color_space)  */
			#if defined(XR_FB_composition_layer_alpha_blend)
			case(XR_TYPE_COMPOSITION_LAYER_ALPHA_BLEND_FB):
				return U"XR_TYPE_COMPOSITION_LAYER_ALPHA_BLEND_FB";
				break;
			#endif /*  defined(XR_FB_composition_layer_alpha_blend)  */
			#if defined(XR_FB_composition_layer_depth_test)
			case(XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_FB):
				return U"XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_FB";
				break;
			#endif /*  defined(XR_FB_composition_layer_depth_test)  */
			#if defined(XR_FB_composition_layer_image_layout)
			case(XR_TYPE_COMPOSITION_LAYER_IMAGE_LAYOUT_FB):
				return U"XR_TYPE_COMPOSITION_LAYER_IMAGE_LAYOUT_FB";
				break;
			#endif /*  defined(XR_FB_composition_layer_image_layout)  */
			#if defined(XR_FB_composition_layer_secure_content)
			case(XR_TYPE_COMPOSITION_LAYER_SECURE_CONTENT_FB):
				return U"XR_TYPE_COMPOSITION_LAYER_SECURE_CONTENT_FB";
				break;
			#endif /*  defined(XR_FB_composition_layer_secure_content)  */
			#if defined(XR_FB_composition_layer_settings)
			case(XR_TYPE_COMPOSITION_LAYER_SETTINGS_FB):
				return U"XR_TYPE_COMPOSITION_LAYER_SETTINGS_FB";
				break;
			#endif /*  defined(XR_FB_composition_layer_settings)  */
			#if defined(XR_FB_display_refresh_rate)
			case(XR_TYPE_EVENT_DATA_DISPLAY_REFRESH_RATE_CHANGED_FB):
				return U"XR_TYPE_EVENT_DATA_DISPLAY_REFRESH_RATE_CHANGED_FB";
				break;
			#endif /*  defined(XR_FB_display_refresh_rate)  */
			#if defined(XR_FB_eye_tracking_social)
			case(XR_TYPE_EYE_TRACKER_CREATE_INFO_FB):
				return U"XR_TYPE_EYE_TRACKER_CREATE_INFO_FB";
				break;
			case(XR_TYPE_EYE_GAZES_INFO_FB):
				return U"XR_TYPE_EYE_GAZES_INFO_FB";
				break;
			case(XR_TYPE_EYE_GAZES_FB):
				return U"XR_TYPE_EYE_GAZES_FB";
				break;
			case(XR_TYPE_SYSTEM_EYE_TRACKING_PROPERTIES_FB):
				return U"XR_TYPE_SYSTEM_EYE_TRACKING_PROPERTIES_FB";
				break;
			#endif /*  defined(XR_FB_eye_tracking_social)  */
			#if defined(XR_FB_face_tracking)
			case(XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES_FB):
				return U"XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES_FB";
				break;
			case(XR_TYPE_FACE_TRACKER_CREATE_INFO_FB):
				return U"XR_TYPE_FACE_TRACKER_CREATE_INFO_FB";
				break;
			case(XR_TYPE_FACE_EXPRESSION_INFO_FB):
				return U"XR_TYPE_FACE_EXPRESSION_INFO_FB";
				break;
			case(XR_TYPE_FACE_EXPRESSION_WEIGHTS_FB):
				return U"XR_TYPE_FACE_EXPRESSION_WEIGHTS_FB";
				break;
			#endif /*  defined(XR_FB_face_tracking)  */
			#if defined(XR_FB_face_tracking2)
			case(XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES2_FB):
				return U"XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES2_FB";
				break;
			case(XR_TYPE_FACE_TRACKER_CREATE_INFO2_FB):
				return U"XR_TYPE_FACE_TRACKER_CREATE_INFO2_FB";
				break;
			case(XR_TYPE_FACE_EXPRESSION_INFO2_FB):
				return U"XR_TYPE_FACE_EXPRESSION_INFO2_FB";
				break;
			case(XR_TYPE_FACE_EXPRESSION_WEIGHTS2_FB):
				return U"XR_TYPE_FACE_EXPRESSION_WEIGHTS2_FB";
				break;
			#endif /*  defined(XR_FB_face_tracking2)  */
			#if defined(XR_FB_foveation)
			case(XR_TYPE_FOVEATION_PROFILE_CREATE_INFO_FB):
				return U"XR_TYPE_FOVEATION_PROFILE_CREATE_INFO_FB";
				break;
			case(XR_TYPE_SWAPCHAIN_CREATE_INFO_FOVEATION_FB):
				return U"XR_TYPE_SWAPCHAIN_CREATE_INFO_FOVEATION_FB";
				break;
			case(XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB):
				return U"XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB";
				break;
			#endif /*  defined(XR_FB_foveation)  */
			#if defined(XR_FB_foveation_configuration)
			case(XR_TYPE_FOVEATION_LEVEL_PROFILE_CREATE_INFO_FB):
				return U"XR_TYPE_FOVEATION_LEVEL_PROFILE_CREATE_INFO_FB";
				break;
			#endif /*  defined(XR_FB_foveation_configuration)  */
			#if defined(XR_FB_foveation_vulkan)
			case(XR_TYPE_SWAPCHAIN_IMAGE_FOVEATION_VULKAN_FB):
				return U"XR_TYPE_SWAPCHAIN_IMAGE_FOVEATION_VULKAN_FB";
				break;
			#endif /*  defined(XR_FB_foveation_vulkan)  */
			#if defined(XR_FB_hand_tracking_aim)
			case(XR_TYPE_HAND_TRACKING_AIM_STATE_FB):
				return U"XR_TYPE_HAND_TRACKING_AIM_STATE_FB";
				break;
			#endif /*  defined(XR_FB_hand_tracking_aim)  */
			#if defined(XR_FB_hand_tracking_capsules)
			case(XR_TYPE_HAND_TRACKING_CAPSULES_STATE_FB):
				return U"XR_TYPE_HAND_TRACKING_CAPSULES_STATE_FB";
				break;
			#endif /*  defined(XR_FB_hand_tracking_capsules)  */
			#if defined(XR_FB_hand_tracking_mesh)
			case(XR_TYPE_HAND_TRACKING_MESH_FB):
				return U"XR_TYPE_HAND_TRACKING_MESH_FB";
				break;
			case(XR_TYPE_HAND_TRACKING_SCALE_FB):
				return U"XR_TYPE_HAND_TRACKING_SCALE_FB";
				break;
			#endif /*  defined(XR_FB_hand_tracking_mesh)  */
			#if defined(XR_FB_haptic_amplitude_envelope)
			case(XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB):
				return U"XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB";
				break;
			#endif /*  defined(XR_FB_haptic_amplitude_envelope)  */
			#if defined(XR_FB_haptic_pcm)
			case(XR_TYPE_HAPTIC_PCM_VIBRATION_FB):
				return U"XR_TYPE_HAPTIC_PCM_VIBRATION_FB";
				break;
			case(XR_TYPE_DEVICE_PCM_SAMPLE_RATE_STATE_FB):
				return U"XR_TYPE_DEVICE_PCM_SAMPLE_RATE_STATE_FB";
				break;
			#endif /*  defined(XR_FB_haptic_pcm)  */
			#if defined(XR_FB_keyboard_tracking)
			case(XR_TYPE_KEYBOARD_SPACE_CREATE_INFO_FB):
				return U"XR_TYPE_KEYBOARD_SPACE_CREATE_INFO_FB";
				break;
			case(XR_TYPE_KEYBOARD_TRACKING_QUERY_FB):
				return U"XR_TYPE_KEYBOARD_TRACKING_QUERY_FB";
				break;
			case(XR_TYPE_SYSTEM_KEYBOARD_TRACKING_PROPERTIES_FB):
				return U"XR_TYPE_SYSTEM_KEYBOARD_TRACKING_PROPERTIES_FB";
				break;
			#endif /*  defined(XR_FB_keyboard_tracking)  */
			#if defined(XR_FB_passthrough)
			case(XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES_FB):
				return U"XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES_FB";
				break;
			case(XR_TYPE_PASSTHROUGH_CREATE_INFO_FB):
				return U"XR_TYPE_PASSTHROUGH_CREATE_INFO_FB";
				break;
			case(XR_TYPE_PASSTHROUGH_LAYER_CREATE_INFO_FB):
				return U"XR_TYPE_PASSTHROUGH_LAYER_CREATE_INFO_FB";
				break;
			case(XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB):
				return U"XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB";
				break;
			case(XR_TYPE_GEOMETRY_INSTANCE_CREATE_INFO_FB):
				return U"XR_TYPE_GEOMETRY_INSTANCE_CREATE_INFO_FB";
				break;
			case(XR_TYPE_GEOMETRY_INSTANCE_TRANSFORM_FB):
				return U"XR_TYPE_GEOMETRY_INSTANCE_TRANSFORM_FB";
				break;
			case(XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES2_FB):
				return U"XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES2_FB";
				break;
			case(XR_TYPE_PASSTHROUGH_STYLE_FB):
				return U"XR_TYPE_PASSTHROUGH_STYLE_FB";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_TO_RGBA_FB):
				return U"XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_TO_RGBA_FB";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_TO_MONO_FB):
				return U"XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_TO_MONO_FB";
				break;
			case(XR_TYPE_PASSTHROUGH_BRIGHTNESS_CONTRAST_SATURATION_FB):
				return U"XR_TYPE_PASSTHROUGH_BRIGHTNESS_CONTRAST_SATURATION_FB";
				break;
			case(XR_TYPE_EVENT_DATA_PASSTHROUGH_STATE_CHANGED_FB):
				return U"XR_TYPE_EVENT_DATA_PASSTHROUGH_STATE_CHANGED_FB";
				break;
			#endif /*  defined(XR_FB_passthrough)  */
			#if defined(XR_FB_passthrough_keyboard_hands)
			case(XR_TYPE_PASSTHROUGH_KEYBOARD_HANDS_INTENSITY_FB):
				return U"XR_TYPE_PASSTHROUGH_KEYBOARD_HANDS_INTENSITY_FB";
				break;
			#endif /*  defined(XR_FB_passthrough_keyboard_hands)  */
			#if defined(XR_FB_render_model)
			case(XR_TYPE_RENDER_MODEL_PATH_INFO_FB):
				return U"XR_TYPE_RENDER_MODEL_PATH_INFO_FB";
				break;
			case(XR_TYPE_RENDER_MODEL_PROPERTIES_FB):
				return U"XR_TYPE_RENDER_MODEL_PROPERTIES_FB";
				break;
			case(XR_TYPE_RENDER_MODEL_BUFFER_FB):
				return U"XR_TYPE_RENDER_MODEL_BUFFER_FB";
				break;
			case(XR_TYPE_RENDER_MODEL_LOAD_INFO_FB):
				return U"XR_TYPE_RENDER_MODEL_LOAD_INFO_FB";
				break;
			case(XR_TYPE_SYSTEM_RENDER_MODEL_PROPERTIES_FB):
				return U"XR_TYPE_SYSTEM_RENDER_MODEL_PROPERTIES_FB";
				break;
			case(XR_TYPE_RENDER_MODEL_CAPABILITIES_REQUEST_FB):
				return U"XR_TYPE_RENDER_MODEL_CAPABILITIES_REQUEST_FB";
				break;
			#endif /*  defined(XR_FB_render_model)  */
			#if defined(XR_FB_scene)
			case(XR_TYPE_SEMANTIC_LABELS_FB):
				return U"XR_TYPE_SEMANTIC_LABELS_FB";
				break;
			case(XR_TYPE_ROOM_LAYOUT_FB):
				return U"XR_TYPE_ROOM_LAYOUT_FB";
				break;
			case(XR_TYPE_BOUNDARY_2D_FB):
				return U"XR_TYPE_BOUNDARY_2D_FB";
				break;
			case(XR_TYPE_SEMANTIC_LABELS_SUPPORT_INFO_FB):
				return U"XR_TYPE_SEMANTIC_LABELS_SUPPORT_INFO_FB";
				break;
			#endif /*  defined(XR_FB_scene)  */
			#if defined(XR_FB_scene_capture)
			case(XR_TYPE_EVENT_DATA_SCENE_CAPTURE_COMPLETE_FB):
				return U"XR_TYPE_EVENT_DATA_SCENE_CAPTURE_COMPLETE_FB";
				break;
			case(XR_TYPE_SCENE_CAPTURE_REQUEST_INFO_FB):
				return U"XR_TYPE_SCENE_CAPTURE_REQUEST_INFO_FB";
				break;
			#endif /*  defined(XR_FB_scene_capture)  */
			#if defined(XR_FB_space_warp)
			case(XR_TYPE_COMPOSITION_LAYER_SPACE_WARP_INFO_FB):
				return U"XR_TYPE_COMPOSITION_LAYER_SPACE_WARP_INFO_FB";
				break;
			case(XR_TYPE_SYSTEM_SPACE_WARP_PROPERTIES_FB):
				return U"XR_TYPE_SYSTEM_SPACE_WARP_PROPERTIES_FB";
				break;
			#endif /*  defined(XR_FB_space_warp)  */
			#if defined(XR_FB_spatial_entity)
			case(XR_TYPE_SYSTEM_SPATIAL_ENTITY_PROPERTIES_FB):
				return U"XR_TYPE_SYSTEM_SPATIAL_ENTITY_PROPERTIES_FB";
				break;
			case(XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_FB):
				return U"XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_FB";
				break;
			case(XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB):
				return U"XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB";
				break;
			case(XR_TYPE_SPACE_COMPONENT_STATUS_FB):
				return U"XR_TYPE_SPACE_COMPONENT_STATUS_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPATIAL_ANCHOR_CREATE_COMPLETE_FB):
				return U"XR_TYPE_EVENT_DATA_SPATIAL_ANCHOR_CREATE_COMPLETE_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_SET_STATUS_COMPLETE_FB):
				return U"XR_TYPE_EVENT_DATA_SPACE_SET_STATUS_COMPLETE_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity)  */
			#if defined(XR_FB_spatial_entity_container)
			case(XR_TYPE_SPACE_CONTAINER_FB):
				return U"XR_TYPE_SPACE_CONTAINER_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_container)  */
			#if defined(XR_FB_spatial_entity_query)
			case(XR_TYPE_SPACE_QUERY_INFO_FB):
				return U"XR_TYPE_SPACE_QUERY_INFO_FB";
				break;
			case(XR_TYPE_SPACE_QUERY_RESULTS_FB):
				return U"XR_TYPE_SPACE_QUERY_RESULTS_FB";
				break;
			case(XR_TYPE_SPACE_STORAGE_LOCATION_FILTER_INFO_FB):
				return U"XR_TYPE_SPACE_STORAGE_LOCATION_FILTER_INFO_FB";
				break;
			case(XR_TYPE_SPACE_UUID_FILTER_INFO_FB):
				return U"XR_TYPE_SPACE_UUID_FILTER_INFO_FB";
				break;
			case(XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB):
				return U"XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_QUERY_RESULTS_AVAILABLE_FB):
				return U"XR_TYPE_EVENT_DATA_SPACE_QUERY_RESULTS_AVAILABLE_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_QUERY_COMPLETE_FB):
				return U"XR_TYPE_EVENT_DATA_SPACE_QUERY_COMPLETE_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_query)  */
			#if defined(XR_FB_spatial_entity_sharing)
			case(XR_TYPE_SPACE_SHARE_INFO_FB):
				return U"XR_TYPE_SPACE_SHARE_INFO_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_SHARE_COMPLETE_FB):
				return U"XR_TYPE_EVENT_DATA_SPACE_SHARE_COMPLETE_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_sharing)  */
			#if defined(XR_FB_spatial_entity_storage)
			case(XR_TYPE_SPACE_SAVE_INFO_FB):
				return U"XR_TYPE_SPACE_SAVE_INFO_FB";
				break;
			case(XR_TYPE_SPACE_ERASE_INFO_FB):
				return U"XR_TYPE_SPACE_ERASE_INFO_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_SAVE_COMPLETE_FB):
				return U"XR_TYPE_EVENT_DATA_SPACE_SAVE_COMPLETE_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_ERASE_COMPLETE_FB):
				return U"XR_TYPE_EVENT_DATA_SPACE_ERASE_COMPLETE_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_storage)  */
			#if defined(XR_FB_spatial_entity_storage_batch)
			case(XR_TYPE_SPACE_LIST_SAVE_INFO_FB):
				return U"XR_TYPE_SPACE_LIST_SAVE_INFO_FB";
				break;
			case(XR_TYPE_EVENT_DATA_SPACE_LIST_SAVE_COMPLETE_FB):
				return U"XR_TYPE_EVENT_DATA_SPACE_LIST_SAVE_COMPLETE_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_storage_batch)  */
			#if defined(XR_FB_spatial_entity_user)
			case(XR_TYPE_SPACE_USER_CREATE_INFO_FB):
				return U"XR_TYPE_SPACE_USER_CREATE_INFO_FB";
				break;
			#endif /*  defined(XR_FB_spatial_entity_user)  */
			#if defined(XR_FB_swapchain_update_state_android_surface)
			case(XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB):
				return U"XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB";
				break;
			#endif /*  defined(XR_FB_swapchain_update_state_android_surface)  */
			#if defined(XR_FB_swapchain_update_state_opengl_es)
			case(XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB):
				return U"XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB";
				break;
			#endif /*  defined(XR_FB_swapchain_update_state_opengl_es)  */
			#if defined(XR_FB_swapchain_update_state_vulkan)
			case(XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB):
				return U"XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB";
				break;
			#endif /*  defined(XR_FB_swapchain_update_state_vulkan)  */
			#if defined(XR_FB_triangle_mesh)
			case(XR_TYPE_TRIANGLE_MESH_CREATE_INFO_FB):
				return U"XR_TYPE_TRIANGLE_MESH_CREATE_INFO_FB";
				break;
			#endif /*  defined(XR_FB_triangle_mesh)  */
			#if defined(XR_HTCX_vive_tracker_interaction)
			case(XR_TYPE_VIVE_TRACKER_PATHS_HTCX):
				return U"XR_TYPE_VIVE_TRACKER_PATHS_HTCX";
				break;
			case(XR_TYPE_EVENT_DATA_VIVE_TRACKER_CONNECTED_HTCX):
				return U"XR_TYPE_EVENT_DATA_VIVE_TRACKER_CONNECTED_HTCX";
				break;
			#endif /*  defined(XR_HTCX_vive_tracker_interaction)  */
			#if defined(XR_HTC_anchor)
			case(XR_TYPE_SYSTEM_ANCHOR_PROPERTIES_HTC):
				return U"XR_TYPE_SYSTEM_ANCHOR_PROPERTIES_HTC";
				break;
			case(XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_HTC):
				return U"XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_HTC";
				break;
			#endif /*  defined(XR_HTC_anchor)  */
			#if defined(XR_HTC_body_tracking)
			case(XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_HTC):
				return U"XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_HTC";
				break;
			case(XR_TYPE_BODY_TRACKER_CREATE_INFO_HTC):
				return U"XR_TYPE_BODY_TRACKER_CREATE_INFO_HTC";
				break;
			case(XR_TYPE_BODY_JOINTS_LOCATE_INFO_HTC):
				return U"XR_TYPE_BODY_JOINTS_LOCATE_INFO_HTC";
				break;
			case(XR_TYPE_BODY_JOINT_LOCATIONS_HTC):
				return U"XR_TYPE_BODY_JOINT_LOCATIONS_HTC";
				break;
			case(XR_TYPE_BODY_SKELETON_HTC):
				return U"XR_TYPE_BODY_SKELETON_HTC";
				break;
			#endif /*  defined(XR_HTC_body_tracking)  */
			#if defined(XR_HTC_facial_tracking)
			case(XR_TYPE_SYSTEM_FACIAL_TRACKING_PROPERTIES_HTC):
				return U"XR_TYPE_SYSTEM_FACIAL_TRACKING_PROPERTIES_HTC";
				break;
			case(XR_TYPE_FACIAL_TRACKER_CREATE_INFO_HTC):
				return U"XR_TYPE_FACIAL_TRACKER_CREATE_INFO_HTC";
				break;
			case(XR_TYPE_FACIAL_EXPRESSIONS_HTC):
				return U"XR_TYPE_FACIAL_EXPRESSIONS_HTC";
				break;
			#endif /*  defined(XR_HTC_facial_tracking)  */
			#if defined(XR_HTC_foveation)
			case(XR_TYPE_FOVEATION_APPLY_INFO_HTC):
				return U"XR_TYPE_FOVEATION_APPLY_INFO_HTC";
				break;
			case(XR_TYPE_FOVEATION_DYNAMIC_MODE_INFO_HTC):
				return U"XR_TYPE_FOVEATION_DYNAMIC_MODE_INFO_HTC";
				break;
			case(XR_TYPE_FOVEATION_CUSTOM_MODE_INFO_HTC):
				return U"XR_TYPE_FOVEATION_CUSTOM_MODE_INFO_HTC";
				break;
			#endif /*  defined(XR_HTC_foveation)  */
			#if defined(XR_HTC_passthrough)
			case(XR_TYPE_PASSTHROUGH_CREATE_INFO_HTC):
				return U"XR_TYPE_PASSTHROUGH_CREATE_INFO_HTC";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_HTC):
				return U"XR_TYPE_PASSTHROUGH_COLOR_HTC";
				break;
			case(XR_TYPE_PASSTHROUGH_MESH_TRANSFORM_INFO_HTC):
				return U"XR_TYPE_PASSTHROUGH_MESH_TRANSFORM_INFO_HTC";
				break;
			case(XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_HTC):
				return U"XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_HTC";
				break;
			#endif /*  defined(XR_HTC_passthrough)  */
			#if defined(XR_KHR_D3D11_enable)
			case(XR_TYPE_GRAPHICS_BINDING_D3D11_KHR):
				return U"XR_TYPE_GRAPHICS_BINDING_D3D11_KHR";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR):
				return U"XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR";
				break;
			case(XR_TYPE_GRAPHICS_REQUIREMENTS_D3D11_KHR):
				return U"XR_TYPE_GRAPHICS_REQUIREMENTS_D3D11_KHR";
				break;
			#endif /*  defined(XR_KHR_D3D11_enable)  */
			#if defined(XR_KHR_D3D12_enable)
			case(XR_TYPE_GRAPHICS_BINDING_D3D12_KHR):
				return U"XR_TYPE_GRAPHICS_BINDING_D3D12_KHR";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR):
				return U"XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR";
				break;
			case(XR_TYPE_GRAPHICS_REQUIREMENTS_D3D12_KHR):
				return U"XR_TYPE_GRAPHICS_REQUIREMENTS_D3D12_KHR";
				break;
			#endif /*  defined(XR_KHR_D3D12_enable)  */
			#if defined(XR_KHR_android_create_instance)
			case(XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR):
				return U"XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR";
				break;
			#endif /*  defined(XR_KHR_android_create_instance)  */
			#if defined(XR_KHR_binding_modification)
			case(XR_TYPE_BINDING_MODIFICATIONS_KHR):
				return U"XR_TYPE_BINDING_MODIFICATIONS_KHR";
				break;
			#endif /*  defined(XR_KHR_binding_modification)  */
			#if defined(XR_KHR_composition_layer_color_scale_bias)
			case(XR_TYPE_COMPOSITION_LAYER_COLOR_SCALE_BIAS_KHR):
				return U"XR_TYPE_COMPOSITION_LAYER_COLOR_SCALE_BIAS_KHR";
				break;
			#endif /*  defined(XR_KHR_composition_layer_color_scale_bias)  */
			#if defined(XR_KHR_composition_layer_cube)
			case(XR_TYPE_COMPOSITION_LAYER_CUBE_KHR):
				return U"XR_TYPE_COMPOSITION_LAYER_CUBE_KHR";
				break;
			#endif /*  defined(XR_KHR_composition_layer_cube)  */
			#if defined(XR_KHR_composition_layer_cylinder)
			case(XR_TYPE_COMPOSITION_LAYER_CYLINDER_KHR):
				return U"XR_TYPE_COMPOSITION_LAYER_CYLINDER_KHR";
				break;
			#endif /*  defined(XR_KHR_composition_layer_cylinder)  */
			#if defined(XR_KHR_composition_layer_depth)
			case(XR_TYPE_COMPOSITION_LAYER_DEPTH_INFO_KHR):
				return U"XR_TYPE_COMPOSITION_LAYER_DEPTH_INFO_KHR";
				break;
			#endif /*  defined(XR_KHR_composition_layer_depth)  */
			#if defined(XR_KHR_composition_layer_equirect)
			case(XR_TYPE_COMPOSITION_LAYER_EQUIRECT_KHR):
				return U"XR_TYPE_COMPOSITION_LAYER_EQUIRECT_KHR";
				break;
			#endif /*  defined(XR_KHR_composition_layer_equirect)  */
			#if defined(XR_KHR_composition_layer_equirect2)
			case(XR_TYPE_COMPOSITION_LAYER_EQUIRECT2_KHR):
				return U"XR_TYPE_COMPOSITION_LAYER_EQUIRECT2_KHR";
				break;
			#endif /*  defined(XR_KHR_composition_layer_equirect2)  */
			#if defined(XR_KHR_loader_init_android)
			case(XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR):
				return U"XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR";
				break;
			#endif /*  defined(XR_KHR_loader_init_android)  */
			#if defined(XR_KHR_metal_enable)
			case(XR_TYPE_GRAPHICS_BINDING_METAL_KHR):
				return U"XR_TYPE_GRAPHICS_BINDING_METAL_KHR";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR):
				return U"XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR";
				break;
			case(XR_TYPE_GRAPHICS_REQUIREMENTS_METAL_KHR):
				return U"XR_TYPE_GRAPHICS_REQUIREMENTS_METAL_KHR";
				break;
			#endif /*  defined(XR_KHR_metal_enable)  */
			#if defined(XR_KHR_opengl_enable)
			case(XR_TYPE_GRAPHICS_BINDING_OPENGL_WIN32_KHR):
				return U"XR_TYPE_GRAPHICS_BINDING_OPENGL_WIN32_KHR";
				break;
			case(XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR):
				return U"XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR";
				break;
			case(XR_TYPE_GRAPHICS_BINDING_OPENGL_XCB_KHR):
				return U"XR_TYPE_GRAPHICS_BINDING_OPENGL_XCB_KHR";
				break;
			case(XR_TYPE_GRAPHICS_BINDING_OPENGL_WAYLAND_KHR):
				return U"XR_TYPE_GRAPHICS_BINDING_OPENGL_WAYLAND_KHR";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR):
				return U"XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR";
				break;
			case(XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR):
				return U"XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR";
				break;
			#endif /*  defined(XR_KHR_opengl_enable)  */
			#if defined(XR_KHR_opengl_es_enable)
			case(XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR):
				return U"XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR):
				return U"XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR";
				break;
			case(XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR):
				return U"XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR";
				break;
			#endif /*  defined(XR_KHR_opengl_es_enable)  */
			#if defined(XR_KHR_visibility_mask)
			case(XR_TYPE_VISIBILITY_MASK_KHR):
				return U"XR_TYPE_VISIBILITY_MASK_KHR";
				break;
			case(XR_TYPE_EVENT_DATA_VISIBILITY_MASK_CHANGED_KHR):
				return U"XR_TYPE_EVENT_DATA_VISIBILITY_MASK_CHANGED_KHR";
				break;
			#endif /*  defined(XR_KHR_visibility_mask)  */
			#if defined(XR_KHR_vulkan_enable)
			case(XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR):
				return U"XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR";
				break;
			case(XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR):
				return U"XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR";
				break;
			case(XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN_KHR):
				return U"XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN_KHR";
				break;
			#endif /*  defined(XR_KHR_vulkan_enable)  */
			#if defined(XR_KHR_vulkan_enable2)
			case(XR_TYPE_VULKAN_INSTANCE_CREATE_INFO_KHR):
				return U"XR_TYPE_VULKAN_INSTANCE_CREATE_INFO_KHR";
				break;
			case(XR_TYPE_VULKAN_DEVICE_CREATE_INFO_KHR):
				return U"XR_TYPE_VULKAN_DEVICE_CREATE_INFO_KHR";
				break;
			case(XR_TYPE_VULKAN_GRAPHICS_DEVICE_GET_INFO_KHR):
				return U"XR_TYPE_VULKAN_GRAPHICS_DEVICE_GET_INFO_KHR";
				break;
			#endif /*  defined(XR_KHR_vulkan_enable2)  */
			#if defined(XR_KHR_vulkan_swapchain_format_list)
			case(XR_TYPE_VULKAN_SWAPCHAIN_FORMAT_LIST_CREATE_INFO_KHR):
				return U"XR_TYPE_VULKAN_SWAPCHAIN_FORMAT_LIST_CREATE_INFO_KHR";
				break;
			#endif /*  defined(XR_KHR_vulkan_swapchain_format_list)  */
			#if defined(XR_META_environment_depth)
			case(XR_TYPE_ENVIRONMENT_DEPTH_PROVIDER_CREATE_INFO_META):
				return U"XR_TYPE_ENVIRONMENT_DEPTH_PROVIDER_CREATE_INFO_META";
				break;
			case(XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_CREATE_INFO_META):
				return U"XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_CREATE_INFO_META";
				break;
			case(XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_STATE_META):
				return U"XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_STATE_META";
				break;
			case(XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_ACQUIRE_INFO_META):
				return U"XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_ACQUIRE_INFO_META";
				break;
			case(XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_VIEW_META):
				return U"XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_VIEW_META";
				break;
			case(XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_META):
				return U"XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_META";
				break;
			case(XR_TYPE_ENVIRONMENT_DEPTH_HAND_REMOVAL_SET_INFO_META):
				return U"XR_TYPE_ENVIRONMENT_DEPTH_HAND_REMOVAL_SET_INFO_META";
				break;
			case(XR_TYPE_SYSTEM_ENVIRONMENT_DEPTH_PROPERTIES_META):
				return U"XR_TYPE_SYSTEM_ENVIRONMENT_DEPTH_PROPERTIES_META";
				break;
			#endif /*  defined(XR_META_environment_depth)  */
			#if defined(XR_META_foveation_eye_tracked)
			case(XR_TYPE_FOVEATION_EYE_TRACKED_PROFILE_CREATE_INFO_META):
				return U"XR_TYPE_FOVEATION_EYE_TRACKED_PROFILE_CREATE_INFO_META";
				break;
			case(XR_TYPE_FOVEATION_EYE_TRACKED_STATE_META):
				return U"XR_TYPE_FOVEATION_EYE_TRACKED_STATE_META";
				break;
			case(XR_TYPE_SYSTEM_FOVEATION_EYE_TRACKED_PROPERTIES_META):
				return U"XR_TYPE_SYSTEM_FOVEATION_EYE_TRACKED_PROPERTIES_META";
				break;
			#endif /*  defined(XR_META_foveation_eye_tracked)  */
			#if defined(XR_META_headset_id)
			case(XR_TYPE_SYSTEM_HEADSET_ID_PROPERTIES_META):
				return U"XR_TYPE_SYSTEM_HEADSET_ID_PROPERTIES_META";
				break;
			#endif /*  defined(XR_META_headset_id)  */
			#if defined(XR_META_local_dimming)
			case(XR_TYPE_LOCAL_DIMMING_FRAME_END_INFO_META):
				return U"XR_TYPE_LOCAL_DIMMING_FRAME_END_INFO_META";
				break;
			#endif /*  defined(XR_META_local_dimming)  */
			#if defined(XR_META_passthrough_color_lut)
			case(XR_TYPE_SYSTEM_PASSTHROUGH_COLOR_LUT_PROPERTIES_META):
				return U"XR_TYPE_SYSTEM_PASSTHROUGH_COLOR_LUT_PROPERTIES_META";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_LUT_CREATE_INFO_META):
				return U"XR_TYPE_PASSTHROUGH_COLOR_LUT_CREATE_INFO_META";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_LUT_UPDATE_INFO_META):
				return U"XR_TYPE_PASSTHROUGH_COLOR_LUT_UPDATE_INFO_META";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_MAP_LUT_META):
				return U"XR_TYPE_PASSTHROUGH_COLOR_MAP_LUT_META";
				break;
			case(XR_TYPE_PASSTHROUGH_COLOR_MAP_INTERPOLATED_LUT_META):
				return U"XR_TYPE_PASSTHROUGH_COLOR_MAP_INTERPOLATED_LUT_META";
				break;
			#endif /*  defined(XR_META_passthrough_color_lut)  */
			#if defined(XR_META_passthrough_preferences)
			case(XR_TYPE_PASSTHROUGH_PREFERENCES_META):
				return U"XR_TYPE_PASSTHROUGH_PREFERENCES_META";
				break;
			#endif /*  defined(XR_META_passthrough_preferences)  */
			#if defined(XR_META_performance_metrics)
			case(XR_TYPE_PERFORMANCE_METRICS_STATE_META):
				return U"XR_TYPE_PERFORMANCE_METRICS_STATE_META";
				break;
			case(XR_TYPE_PERFORMANCE_METRICS_COUNTER_META):
				return U"XR_TYPE_PERFORMANCE_METRICS_COUNTER_META";
				break;
			#endif /*  defined(XR_META_performance_metrics)  */
			#if defined(XR_META_recommended_layer_resolution)
			case(XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_META):
				return U"XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_META";
				break;
			case(XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_GET_INFO_META):
				return U"XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_GET_INFO_META";
				break;
			#endif /*  defined(XR_META_recommended_layer_resolution)  */
			#if defined(XR_META_spatial_entity_mesh)
			case(XR_TYPE_SPACE_TRIANGLE_MESH_GET_INFO_META):
				return U"XR_TYPE_SPACE_TRIANGLE_MESH_GET_INFO_META";
				break;
			case(XR_TYPE_SPACE_TRIANGLE_MESH_META):
				return U"XR_TYPE_SPACE_TRIANGLE_MESH_META";
				break;
			#endif /*  defined(XR_META_spatial_entity_mesh)  */
			#if defined(XR_META_virtual_keyboard)
			case(XR_TYPE_SYSTEM_VIRTUAL_KEYBOARD_PROPERTIES_META):
				return U"XR_TYPE_SYSTEM_VIRTUAL_KEYBOARD_PROPERTIES_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_CREATE_INFO_META):
				return U"XR_TYPE_VIRTUAL_KEYBOARD_CREATE_INFO_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_SPACE_CREATE_INFO_META):
				return U"XR_TYPE_VIRTUAL_KEYBOARD_SPACE_CREATE_INFO_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_LOCATION_INFO_META):
				return U"XR_TYPE_VIRTUAL_KEYBOARD_LOCATION_INFO_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_MODEL_VISIBILITY_SET_INFO_META):
				return U"XR_TYPE_VIRTUAL_KEYBOARD_MODEL_VISIBILITY_SET_INFO_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_ANIMATION_STATE_META):
				return U"XR_TYPE_VIRTUAL_KEYBOARD_ANIMATION_STATE_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_MODEL_ANIMATION_STATES_META):
				return U"XR_TYPE_VIRTUAL_KEYBOARD_MODEL_ANIMATION_STATES_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_TEXTURE_DATA_META):
				return U"XR_TYPE_VIRTUAL_KEYBOARD_TEXTURE_DATA_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_INPUT_INFO_META):
				return U"XR_TYPE_VIRTUAL_KEYBOARD_INPUT_INFO_META";
				break;
			case(XR_TYPE_VIRTUAL_KEYBOARD_TEXT_CONTEXT_CHANGE_INFO_META):
				return U"XR_TYPE_VIRTUAL_KEYBOARD_TEXT_CONTEXT_CHANGE_INFO_META";
				break;
			case(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_COMMIT_TEXT_META):
				return U"XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_COMMIT_TEXT_META";
				break;
			case(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_BACKSPACE_META):
				return U"XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_BACKSPACE_META";
				break;
			case(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_ENTER_META):
				return U"XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_ENTER_META";
				break;
			case(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_SHOWN_META):
				return U"XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_SHOWN_META";
				break;
			case(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_HIDDEN_META):
				return U"XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_HIDDEN_META";
				break;
			#endif /*  defined(XR_META_virtual_keyboard)  */
			#if defined(XR_META_vulkan_swapchain_create_info)
			case(XR_TYPE_VULKAN_SWAPCHAIN_CREATE_INFO_META):
				return U"XR_TYPE_VULKAN_SWAPCHAIN_CREATE_INFO_META";
				break;
			#endif /*  defined(XR_META_vulkan_swapchain_create_info)  */
			#if defined(XR_ML_compat)
			case(XR_TYPE_COORDINATE_SPACE_CREATE_INFO_ML):
				return U"XR_TYPE_COORDINATE_SPACE_CREATE_INFO_ML";
				break;
			#endif /*  defined(XR_ML_compat)  */
			#if defined(XR_ML_frame_end_info)
			case(XR_TYPE_FRAME_END_INFO_ML):
				return U"XR_TYPE_FRAME_END_INFO_ML";
				break;
			#endif /*  defined(XR_ML_frame_end_info)  */
			#if defined(XR_ML_global_dimmer)
			case(XR_TYPE_GLOBAL_DIMMER_FRAME_END_INFO_ML):
				return U"XR_TYPE_GLOBAL_DIMMER_FRAME_END_INFO_ML";
				break;
			#endif /*  defined(XR_ML_global_dimmer)  */
			#if defined(XR_ML_localization_map)
			case(XR_TYPE_LOCALIZATION_MAP_ML):
				return U"XR_TYPE_LOCALIZATION_MAP_ML";
				break;
			case(XR_TYPE_EVENT_DATA_LOCALIZATION_CHANGED_ML):
				return U"XR_TYPE_EVENT_DATA_LOCALIZATION_CHANGED_ML";
				break;
			case(XR_TYPE_MAP_LOCALIZATION_REQUEST_INFO_ML):
				return U"XR_TYPE_MAP_LOCALIZATION_REQUEST_INFO_ML";
				break;
			case(XR_TYPE_LOCALIZATION_MAP_IMPORT_INFO_ML):
				return U"XR_TYPE_LOCALIZATION_MAP_IMPORT_INFO_ML";
				break;
			case(XR_TYPE_LOCALIZATION_ENABLE_EVENTS_INFO_ML):
				return U"XR_TYPE_LOCALIZATION_ENABLE_EVENTS_INFO_ML";
				break;
			#endif /*  defined(XR_ML_localization_map)  */
			#if defined(XR_ML_marker_understanding)
			case(XR_TYPE_SYSTEM_MARKER_UNDERSTANDING_PROPERTIES_ML):
				return U"XR_TYPE_SYSTEM_MARKER_UNDERSTANDING_PROPERTIES_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_CREATE_INFO_ML):
				return U"XR_TYPE_MARKER_DETECTOR_CREATE_INFO_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_ARUCO_INFO_ML):
				return U"XR_TYPE_MARKER_DETECTOR_ARUCO_INFO_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_SIZE_INFO_ML):
				return U"XR_TYPE_MARKER_DETECTOR_SIZE_INFO_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_APRIL_TAG_INFO_ML):
				return U"XR_TYPE_MARKER_DETECTOR_APRIL_TAG_INFO_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_CUSTOM_PROFILE_INFO_ML):
				return U"XR_TYPE_MARKER_DETECTOR_CUSTOM_PROFILE_INFO_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_SNAPSHOT_INFO_ML):
				return U"XR_TYPE_MARKER_DETECTOR_SNAPSHOT_INFO_ML";
				break;
			case(XR_TYPE_MARKER_DETECTOR_STATE_ML):
				return U"XR_TYPE_MARKER_DETECTOR_STATE_ML";
				break;
			case(XR_TYPE_MARKER_SPACE_CREATE_INFO_ML):
				return U"XR_TYPE_MARKER_SPACE_CREATE_INFO_ML";
				break;
			#endif /*  defined(XR_ML_marker_understanding)  */
			#if defined(XR_ML_spatial_anchors)
			case(XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML";
				break;
			case(XR_TYPE_CREATE_SPATIAL_ANCHORS_COMPLETION_ML):
				return U"XR_TYPE_CREATE_SPATIAL_ANCHORS_COMPLETION_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHOR_STATE_ML):
				return U"XR_TYPE_SPATIAL_ANCHOR_STATE_ML";
				break;
			#endif /*  defined(XR_ML_spatial_anchors)  */
			#if defined(XR_ML_spatial_anchors_storage)
			case(XR_TYPE_SPATIAL_ANCHORS_CREATE_STORAGE_INFO_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_CREATE_STORAGE_INFO_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_QUERY_COMPLETION_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_QUERY_COMPLETION_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_PUBLISH_INFO_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_PUBLISH_INFO_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_DELETE_INFO_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_DELETE_INFO_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_INFO_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_INFO_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_DETAILS_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_DETAILS_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_DETAILS_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_DETAILS_ML";
				break;
			case(XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_DETAILS_ML):
				return U"XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_DETAILS_ML";
				break;
			#endif /*  defined(XR_ML_spatial_anchors_storage)  */
			#if defined(XR_ML_system_notifications)
			case(XR_TYPE_SYSTEM_NOTIFICATIONS_SET_INFO_ML):
				return U"XR_TYPE_SYSTEM_NOTIFICATIONS_SET_INFO_ML";
				break;
			#endif /*  defined(XR_ML_system_notifications)  */
			#if defined(XR_ML_user_calibration)
			case(XR_TYPE_EVENT_DATA_HEADSET_FIT_CHANGED_ML):
				return U"XR_TYPE_EVENT_DATA_HEADSET_FIT_CHANGED_ML";
				break;
			case(XR_TYPE_EVENT_DATA_EYE_CALIBRATION_CHANGED_ML):
				return U"XR_TYPE_EVENT_DATA_EYE_CALIBRATION_CHANGED_ML";
				break;
			case(XR_TYPE_USER_CALIBRATION_ENABLE_EVENTS_INFO_ML):
				return U"XR_TYPE_USER_CALIBRATION_ENABLE_EVENTS_INFO_ML";
				break;
			#endif /*  defined(XR_ML_user_calibration)  */
			#if defined(XR_ML_world_mesh_detection)
			case(XR_TYPE_WORLD_MESH_DETECTOR_CREATE_INFO_ML):
				return U"XR_TYPE_WORLD_MESH_DETECTOR_CREATE_INFO_ML";
				break;
			case(XR_TYPE_WORLD_MESH_STATE_REQUEST_INFO_ML):
				return U"XR_TYPE_WORLD_MESH_STATE_REQUEST_INFO_ML";
				break;
			case(XR_TYPE_WORLD_MESH_BLOCK_STATE_ML):
				return U"XR_TYPE_WORLD_MESH_BLOCK_STATE_ML";
				break;
			case(XR_TYPE_WORLD_MESH_STATE_REQUEST_COMPLETION_ML):
				return U"XR_TYPE_WORLD_MESH_STATE_REQUEST_COMPLETION_ML";
				break;
			case(XR_TYPE_WORLD_MESH_BUFFER_RECOMMENDED_SIZE_INFO_ML):
				return U"XR_TYPE_WORLD_MESH_BUFFER_RECOMMENDED_SIZE_INFO_ML";
				break;
			case(XR_TYPE_WORLD_MESH_BUFFER_SIZE_ML):
				return U"XR_TYPE_WORLD_MESH_BUFFER_SIZE_ML";
				break;
			case(XR_TYPE_WORLD_MESH_BUFFER_ML):
				return U"XR_TYPE_WORLD_MESH_BUFFER_ML";
				break;
			case(XR_TYPE_WORLD_MESH_BLOCK_REQUEST_ML):
				return U"XR_TYPE_WORLD_MESH_BLOCK_REQUEST_ML";
				break;
			case(XR_TYPE_WORLD_MESH_GET_INFO_ML):
				return U"XR_TYPE_WORLD_MESH_GET_INFO_ML";
				break;
			case(XR_TYPE_WORLD_MESH_BLOCK_ML):
				return U"XR_TYPE_WORLD_MESH_BLOCK_ML";
				break;
			case(XR_TYPE_WORLD_MESH_REQUEST_COMPLETION_ML):
				return U"XR_TYPE_WORLD_MESH_REQUEST_COMPLETION_ML";
				break;
			case(XR_TYPE_WORLD_MESH_REQUEST_COMPLETION_INFO_ML):
				return U"XR_TYPE_WORLD_MESH_REQUEST_COMPLETION_INFO_ML";
				break;
			#endif /*  defined(XR_ML_world_mesh_detection)  */
			#if defined(XR_MNDX_egl_enable)
			case(XR_TYPE_GRAPHICS_BINDING_EGL_MNDX):
				return U"XR_TYPE_GRAPHICS_BINDING_EGL_MNDX";
				break;
			#endif /*  defined(XR_MNDX_egl_enable)  */
			#if defined(XR_MNDX_force_feedback_curl)
			case(XR_TYPE_SYSTEM_FORCE_FEEDBACK_CURL_PROPERTIES_MNDX):
				return U"XR_TYPE_SYSTEM_FORCE_FEEDBACK_CURL_PROPERTIES_MNDX";
				break;
			case(XR_TYPE_FORCE_FEEDBACK_CURL_APPLY_LOCATIONS_MNDX):
				return U"XR_TYPE_FORCE_FEEDBACK_CURL_APPLY_LOCATIONS_MNDX";
				break;
			#endif /*  defined(XR_MNDX_force_feedback_curl)  */
			#if defined(XR_MSFT_composition_layer_reprojection)
			case(XR_TYPE_COMPOSITION_LAYER_REPROJECTION_INFO_MSFT):
				return U"XR_TYPE_COMPOSITION_LAYER_REPROJECTION_INFO_MSFT";
				break;
			case(XR_TYPE_COMPOSITION_LAYER_REPROJECTION_PLANE_OVERRIDE_MSFT):
				return U"XR_TYPE_COMPOSITION_LAYER_REPROJECTION_PLANE_OVERRIDE_MSFT";
				break;
			#endif /*  defined(XR_MSFT_composition_layer_reprojection)  */
			#if defined(XR_MSFT_controller_model)
			case(XR_TYPE_CONTROLLER_MODEL_KEY_STATE_MSFT):
				return U"XR_TYPE_CONTROLLER_MODEL_KEY_STATE_MSFT";
				break;
			case(XR_TYPE_CONTROLLER_MODEL_NODE_PROPERTIES_MSFT):
				return U"XR_TYPE_CONTROLLER_MODEL_NODE_PROPERTIES_MSFT";
				break;
			case(XR_TYPE_CONTROLLER_MODEL_PROPERTIES_MSFT):
				return U"XR_TYPE_CONTROLLER_MODEL_PROPERTIES_MSFT";
				break;
			case(XR_TYPE_CONTROLLER_MODEL_NODE_STATE_MSFT):
				return U"XR_TYPE_CONTROLLER_MODEL_NODE_STATE_MSFT";
				break;
			case(XR_TYPE_CONTROLLER_MODEL_STATE_MSFT):
				return U"XR_TYPE_CONTROLLER_MODEL_STATE_MSFT";
				break;
			#endif /*  defined(XR_MSFT_controller_model)  */
			#if defined(XR_MSFT_hand_tracking_mesh)
			case(XR_TYPE_SYSTEM_HAND_TRACKING_MESH_PROPERTIES_MSFT):
				return U"XR_TYPE_SYSTEM_HAND_TRACKING_MESH_PROPERTIES_MSFT";
				break;
			case(XR_TYPE_HAND_MESH_SPACE_CREATE_INFO_MSFT):
				return U"XR_TYPE_HAND_MESH_SPACE_CREATE_INFO_MSFT";
				break;
			case(XR_TYPE_HAND_MESH_UPDATE_INFO_MSFT):
				return U"XR_TYPE_HAND_MESH_UPDATE_INFO_MSFT";
				break;
			case(XR_TYPE_HAND_MESH_MSFT):
				return U"XR_TYPE_HAND_MESH_MSFT";
				break;
			case(XR_TYPE_HAND_POSE_TYPE_INFO_MSFT):
				return U"XR_TYPE_HAND_POSE_TYPE_INFO_MSFT";
				break;
			#endif /*  defined(XR_MSFT_hand_tracking_mesh)  */
			#if defined(XR_MSFT_holographic_window_attachment)
			case(XR_TYPE_HOLOGRAPHIC_WINDOW_ATTACHMENT_MSFT):
				return U"XR_TYPE_HOLOGRAPHIC_WINDOW_ATTACHMENT_MSFT";
				break;
			#endif /*  defined(XR_MSFT_holographic_window_attachment)  */
			#if defined(XR_MSFT_scene_marker)
			case(XR_TYPE_SCENE_MARKERS_MSFT):
				return U"XR_TYPE_SCENE_MARKERS_MSFT";
				break;
			case(XR_TYPE_SCENE_MARKER_TYPE_FILTER_MSFT):
				return U"XR_TYPE_SCENE_MARKER_TYPE_FILTER_MSFT";
				break;
			case(XR_TYPE_SCENE_MARKER_QR_CODES_MSFT):
				return U"XR_TYPE_SCENE_MARKER_QR_CODES_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_marker)  */
			#if defined(XR_MSFT_scene_understanding)
			case(XR_TYPE_SCENE_OBSERVER_CREATE_INFO_MSFT):
				return U"XR_TYPE_SCENE_OBSERVER_CREATE_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_CREATE_INFO_MSFT):
				return U"XR_TYPE_SCENE_CREATE_INFO_MSFT";
				break;
			case(XR_TYPE_NEW_SCENE_COMPUTE_INFO_MSFT):
				return U"XR_TYPE_NEW_SCENE_COMPUTE_INFO_MSFT";
				break;
			case(XR_TYPE_VISUAL_MESH_COMPUTE_LOD_INFO_MSFT):
				return U"XR_TYPE_VISUAL_MESH_COMPUTE_LOD_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_COMPONENTS_MSFT):
				return U"XR_TYPE_SCENE_COMPONENTS_MSFT";
				break;
			case(XR_TYPE_SCENE_COMPONENTS_GET_INFO_MSFT):
				return U"XR_TYPE_SCENE_COMPONENTS_GET_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_COMPONENT_LOCATIONS_MSFT):
				return U"XR_TYPE_SCENE_COMPONENT_LOCATIONS_MSFT";
				break;
			case(XR_TYPE_SCENE_COMPONENTS_LOCATE_INFO_MSFT):
				return U"XR_TYPE_SCENE_COMPONENTS_LOCATE_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_OBJECTS_MSFT):
				return U"XR_TYPE_SCENE_OBJECTS_MSFT";
				break;
			case(XR_TYPE_SCENE_COMPONENT_PARENT_FILTER_INFO_MSFT):
				return U"XR_TYPE_SCENE_COMPONENT_PARENT_FILTER_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_OBJECT_TYPES_FILTER_INFO_MSFT):
				return U"XR_TYPE_SCENE_OBJECT_TYPES_FILTER_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_PLANES_MSFT):
				return U"XR_TYPE_SCENE_PLANES_MSFT";
				break;
			case(XR_TYPE_SCENE_PLANE_ALIGNMENT_FILTER_INFO_MSFT):
				return U"XR_TYPE_SCENE_PLANE_ALIGNMENT_FILTER_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_MESHES_MSFT):
				return U"XR_TYPE_SCENE_MESHES_MSFT";
				break;
			case(XR_TYPE_SCENE_MESH_BUFFERS_GET_INFO_MSFT):
				return U"XR_TYPE_SCENE_MESH_BUFFERS_GET_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_MESH_BUFFERS_MSFT):
				return U"XR_TYPE_SCENE_MESH_BUFFERS_MSFT";
				break;
			case(XR_TYPE_SCENE_MESH_VERTEX_BUFFER_MSFT):
				return U"XR_TYPE_SCENE_MESH_VERTEX_BUFFER_MSFT";
				break;
			case(XR_TYPE_SCENE_MESH_INDICES_UINT32_MSFT):
				return U"XR_TYPE_SCENE_MESH_INDICES_UINT32_MSFT";
				break;
			case(XR_TYPE_SCENE_MESH_INDICES_UINT16_MSFT):
				return U"XR_TYPE_SCENE_MESH_INDICES_UINT16_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_understanding)  */
			#if defined(XR_MSFT_scene_understanding_serialization)
			case(XR_TYPE_SERIALIZED_SCENE_FRAGMENT_DATA_GET_INFO_MSFT):
				return U"XR_TYPE_SERIALIZED_SCENE_FRAGMENT_DATA_GET_INFO_MSFT";
				break;
			case(XR_TYPE_SCENE_DESERIALIZE_INFO_MSFT):
				return U"XR_TYPE_SCENE_DESERIALIZE_INFO_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_understanding_serialization)  */
			#if defined(XR_MSFT_secondary_view_configuration)
			case(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SESSION_BEGIN_INFO_MSFT):
				return U"XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SESSION_BEGIN_INFO_MSFT";
				break;
			case(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_STATE_MSFT):
				return U"XR_TYPE_SECONDARY_VIEW_CONFIGURATION_STATE_MSFT";
				break;
			case(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_FRAME_STATE_MSFT):
				return U"XR_TYPE_SECONDARY_VIEW_CONFIGURATION_FRAME_STATE_MSFT";
				break;
			case(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_FRAME_END_INFO_MSFT):
				return U"XR_TYPE_SECONDARY_VIEW_CONFIGURATION_FRAME_END_INFO_MSFT";
				break;
			case(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_LAYER_INFO_MSFT):
				return U"XR_TYPE_SECONDARY_VIEW_CONFIGURATION_LAYER_INFO_MSFT";
				break;
			case(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SWAPCHAIN_CREATE_INFO_MSFT):
				return U"XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SWAPCHAIN_CREATE_INFO_MSFT";
				break;
			#endif /*  defined(XR_MSFT_secondary_view_configuration)  */
			#if defined(XR_MSFT_spatial_anchor)
			case(XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_MSFT):
				return U"XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_MSFT";
				break;
			case(XR_TYPE_SPATIAL_ANCHOR_SPACE_CREATE_INFO_MSFT):
				return U"XR_TYPE_SPATIAL_ANCHOR_SPACE_CREATE_INFO_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_anchor)  */
			#if defined(XR_MSFT_spatial_anchor_persistence)
			case(XR_TYPE_SPATIAL_ANCHOR_PERSISTENCE_INFO_MSFT):
				return U"XR_TYPE_SPATIAL_ANCHOR_PERSISTENCE_INFO_MSFT";
				break;
			case(XR_TYPE_SPATIAL_ANCHOR_FROM_PERSISTED_ANCHOR_CREATE_INFO_MSFT):
				return U"XR_TYPE_SPATIAL_ANCHOR_FROM_PERSISTED_ANCHOR_CREATE_INFO_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_anchor_persistence)  */
			#if defined(XR_MSFT_spatial_graph_bridge)
			case(XR_TYPE_SPATIAL_GRAPH_NODE_SPACE_CREATE_INFO_MSFT):
				return U"XR_TYPE_SPATIAL_GRAPH_NODE_SPACE_CREATE_INFO_MSFT";
				break;
			case(XR_TYPE_SPATIAL_GRAPH_STATIC_NODE_BINDING_CREATE_INFO_MSFT):
				return U"XR_TYPE_SPATIAL_GRAPH_STATIC_NODE_BINDING_CREATE_INFO_MSFT";
				break;
			case(XR_TYPE_SPATIAL_GRAPH_NODE_BINDING_PROPERTIES_GET_INFO_MSFT):
				return U"XR_TYPE_SPATIAL_GRAPH_NODE_BINDING_PROPERTIES_GET_INFO_MSFT";
				break;
			case(XR_TYPE_SPATIAL_GRAPH_NODE_BINDING_PROPERTIES_MSFT):
				return U"XR_TYPE_SPATIAL_GRAPH_NODE_BINDING_PROPERTIES_MSFT";
				break;
			#endif /*  defined(XR_MSFT_spatial_graph_bridge)  */
			#if defined(XR_OCULUS_external_camera)
			case(XR_TYPE_EXTERNAL_CAMERA_OCULUS):
				return U"XR_TYPE_EXTERNAL_CAMERA_OCULUS";
				break;
			#endif /*  defined(XR_OCULUS_external_camera)  */
			#if defined(XR_VALVE_analog_threshold)
			case(XR_TYPE_INTERACTION_PROFILE_ANALOG_THRESHOLD_VALVE):
				return U"XR_TYPE_INTERACTION_PROFILE_ANALOG_THRESHOLD_VALVE";
				break;
			#endif /*  defined(XR_VALVE_analog_threshold)  */
			#if defined(XR_VARJO_composition_layer_depth_test)
			case(XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_VARJO):
				return U"XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_VARJO";
				break;
			#endif /*  defined(XR_VARJO_composition_layer_depth_test)  */
			#if defined(XR_VARJO_foveated_rendering)
			case(XR_TYPE_VIEW_LOCATE_FOVEATED_RENDERING_VARJO):
				return U"XR_TYPE_VIEW_LOCATE_FOVEATED_RENDERING_VARJO";
				break;
			case(XR_TYPE_FOVEATED_VIEW_CONFIGURATION_VIEW_VARJO):
				return U"XR_TYPE_FOVEATED_VIEW_CONFIGURATION_VIEW_VARJO";
				break;
			case(XR_TYPE_SYSTEM_FOVEATED_RENDERING_PROPERTIES_VARJO):
				return U"XR_TYPE_SYSTEM_FOVEATED_RENDERING_PROPERTIES_VARJO";
				break;
			#endif /*  defined(XR_VARJO_foveated_rendering)  */
			#if defined(XR_VARJO_marker_tracking)
			case(XR_TYPE_SYSTEM_MARKER_TRACKING_PROPERTIES_VARJO):
				return U"XR_TYPE_SYSTEM_MARKER_TRACKING_PROPERTIES_VARJO";
				break;
			case(XR_TYPE_EVENT_DATA_MARKER_TRACKING_UPDATE_VARJO):
				return U"XR_TYPE_EVENT_DATA_MARKER_TRACKING_UPDATE_VARJO";
				break;
			case(XR_TYPE_MARKER_SPACE_CREATE_INFO_VARJO):
				return U"XR_TYPE_MARKER_SPACE_CREATE_INFO_VARJO";
				break;
			#endif /*  defined(XR_VARJO_marker_tracking)  */
			default:
				return U"XrStructureType_TOSTR_ERROR";

		}

	}

	#if defined(XR_MSFT_scene_understanding)
	const vchar* vtostr32_XrSceneComputeFeatureMSFT(XrSceneComputeFeatureMSFT In){
		switch(In){
			case(XR_SCENE_COMPUTE_FEATURE_PLANE_MSFT):
				return U"XR_SCENE_COMPUTE_FEATURE_PLANE_MSFT";
				break;
			case(XR_SCENE_COMPUTE_FEATURE_PLANE_MESH_MSFT):
				return U"XR_SCENE_COMPUTE_FEATURE_PLANE_MESH_MSFT";
				break;
			case(XR_SCENE_COMPUTE_FEATURE_VISUAL_MESH_MSFT):
				return U"XR_SCENE_COMPUTE_FEATURE_VISUAL_MESH_MSFT";
				break;
			case(XR_SCENE_COMPUTE_FEATURE_COLLIDER_MESH_MSFT):
				return U"XR_SCENE_COMPUTE_FEATURE_COLLIDER_MESH_MSFT";
				break;
			#if defined(XR_MSFT_scene_marker)
			case(XR_SCENE_COMPUTE_FEATURE_MARKER_MSFT):
				return U"XR_SCENE_COMPUTE_FEATURE_MARKER_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_marker)  */
			#if defined(XR_MSFT_scene_understanding_serialization)
			case(XR_SCENE_COMPUTE_FEATURE_SERIALIZE_SCENE_MSFT):
				return U"XR_SCENE_COMPUTE_FEATURE_SERIALIZE_SCENE_MSFT";
				break;
			#endif /*  defined(XR_MSFT_scene_understanding_serialization)  */
			default:
				return U"XrSceneComputeFeatureMSFT_TOSTR_ERROR";

		}

	}

	#endif


	//SECTION(V): XRMYTH_TOSTR8_IMPL
	#if defined(XR_EXT_future)
	const char* vtostr8_XrFutureStateEXT(XrFutureStateEXT In){
		switch(In){

			case(XR_FUTURE_STATE_PENDING_EXT):
				return "XR_FUTURE_STATE_PENDING_EXT";
				break;
			case(XR_FUTURE_STATE_READY_EXT):
				return "XR_FUTURE_STATE_READY_EXT";
				break;
			default:
				return "XrFutureStateEXT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_EXT_future)  */
	#if defined(XR_EXT_hand_joints_motion_range)
	const char* vtostr8_XrHandJointsMotionRangeEXT(XrHandJointsMotionRangeEXT In){
		switch(In){

			case(XR_HAND_JOINTS_MOTION_RANGE_UNOBSTRUCTED_EXT):
				return "XR_HAND_JOINTS_MOTION_RANGE_UNOBSTRUCTED_EXT";
				break;
			case(XR_HAND_JOINTS_MOTION_RANGE_CONFORMING_TO_CONTROLLER_EXT):
				return "XR_HAND_JOINTS_MOTION_RANGE_CONFORMING_TO_CONTROLLER_EXT";
				break;
			default:
				return "XrHandJointsMotionRangeEXT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_EXT_hand_joints_motion_range)  */
	#if defined(XR_EXT_hand_tracking)
	const char* vtostr8_XrHandEXT(XrHandEXT In){
		switch(In){

			case(XR_HAND_LEFT_EXT):
				return "XR_HAND_LEFT_EXT";
				break;
			case(XR_HAND_RIGHT_EXT):
				return "XR_HAND_RIGHT_EXT";
				break;
			default:
				return "XrHandEXT_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrHandJointEXT(XrHandJointEXT In){
		switch(In){

			case(XR_HAND_JOINT_PALM_EXT):
				return "XR_HAND_JOINT_PALM_EXT";
				break;
			case(XR_HAND_JOINT_WRIST_EXT):
				return "XR_HAND_JOINT_WRIST_EXT";
				break;
			case(XR_HAND_JOINT_THUMB_METACARPAL_EXT):
				return "XR_HAND_JOINT_THUMB_METACARPAL_EXT";
				break;
			case(XR_HAND_JOINT_THUMB_PROXIMAL_EXT):
				return "XR_HAND_JOINT_THUMB_PROXIMAL_EXT";
				break;
			case(XR_HAND_JOINT_THUMB_DISTAL_EXT):
				return "XR_HAND_JOINT_THUMB_DISTAL_EXT";
				break;
			case(XR_HAND_JOINT_THUMB_TIP_EXT):
				return "XR_HAND_JOINT_THUMB_TIP_EXT";
				break;
			case(XR_HAND_JOINT_INDEX_METACARPAL_EXT):
				return "XR_HAND_JOINT_INDEX_METACARPAL_EXT";
				break;
			case(XR_HAND_JOINT_INDEX_PROXIMAL_EXT):
				return "XR_HAND_JOINT_INDEX_PROXIMAL_EXT";
				break;
			case(XR_HAND_JOINT_INDEX_INTERMEDIATE_EXT):
				return "XR_HAND_JOINT_INDEX_INTERMEDIATE_EXT";
				break;
			case(XR_HAND_JOINT_INDEX_DISTAL_EXT):
				return "XR_HAND_JOINT_INDEX_DISTAL_EXT";
				break;
			case(XR_HAND_JOINT_INDEX_TIP_EXT):
				return "XR_HAND_JOINT_INDEX_TIP_EXT";
				break;
			case(XR_HAND_JOINT_MIDDLE_METACARPAL_EXT):
				return "XR_HAND_JOINT_MIDDLE_METACARPAL_EXT";
				break;
			case(XR_HAND_JOINT_MIDDLE_PROXIMAL_EXT):
				return "XR_HAND_JOINT_MIDDLE_PROXIMAL_EXT";
				break;
			case(XR_HAND_JOINT_MIDDLE_INTERMEDIATE_EXT):
				return "XR_HAND_JOINT_MIDDLE_INTERMEDIATE_EXT";
				break;
			case(XR_HAND_JOINT_MIDDLE_DISTAL_EXT):
				return "XR_HAND_JOINT_MIDDLE_DISTAL_EXT";
				break;
			case(XR_HAND_JOINT_MIDDLE_TIP_EXT):
				return "XR_HAND_JOINT_MIDDLE_TIP_EXT";
				break;
			case(XR_HAND_JOINT_RING_METACARPAL_EXT):
				return "XR_HAND_JOINT_RING_METACARPAL_EXT";
				break;
			case(XR_HAND_JOINT_RING_PROXIMAL_EXT):
				return "XR_HAND_JOINT_RING_PROXIMAL_EXT";
				break;
			case(XR_HAND_JOINT_RING_INTERMEDIATE_EXT):
				return "XR_HAND_JOINT_RING_INTERMEDIATE_EXT";
				break;
			case(XR_HAND_JOINT_RING_DISTAL_EXT):
				return "XR_HAND_JOINT_RING_DISTAL_EXT";
				break;
			case(XR_HAND_JOINT_RING_TIP_EXT):
				return "XR_HAND_JOINT_RING_TIP_EXT";
				break;
			case(XR_HAND_JOINT_LITTLE_METACARPAL_EXT):
				return "XR_HAND_JOINT_LITTLE_METACARPAL_EXT";
				break;
			case(XR_HAND_JOINT_LITTLE_PROXIMAL_EXT):
				return "XR_HAND_JOINT_LITTLE_PROXIMAL_EXT";
				break;
			case(XR_HAND_JOINT_LITTLE_INTERMEDIATE_EXT):
				return "XR_HAND_JOINT_LITTLE_INTERMEDIATE_EXT";
				break;
			case(XR_HAND_JOINT_LITTLE_DISTAL_EXT):
				return "XR_HAND_JOINT_LITTLE_DISTAL_EXT";
				break;
			case(XR_HAND_JOINT_LITTLE_TIP_EXT):
				return "XR_HAND_JOINT_LITTLE_TIP_EXT";
				break;
			default:
				return "XrHandJointEXT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_EXT_hand_tracking)  */
	#if defined(XR_EXT_hand_tracking_data_source)
	const char* vtostr8_XrHandTrackingDataSourceEXT(XrHandTrackingDataSourceEXT In){
		switch(In){

			case(XR_HAND_TRACKING_DATA_SOURCE_UNOBSTRUCTED_EXT):
				return "XR_HAND_TRACKING_DATA_SOURCE_UNOBSTRUCTED_EXT";
				break;
			case(XR_HAND_TRACKING_DATA_SOURCE_CONTROLLER_EXT):
				return "XR_HAND_TRACKING_DATA_SOURCE_CONTROLLER_EXT";
				break;
			default:
				return "XrHandTrackingDataSourceEXT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_EXT_hand_tracking_data_source)  */
	#if defined(XR_EXT_performance_settings)
	const char* vtostr8_XrPerfSettingsDomainEXT(XrPerfSettingsDomainEXT In){
		switch(In){

			case(XR_PERF_SETTINGS_DOMAIN_CPU_EXT):
				return "XR_PERF_SETTINGS_DOMAIN_CPU_EXT";
				break;
			case(XR_PERF_SETTINGS_DOMAIN_GPU_EXT):
				return "XR_PERF_SETTINGS_DOMAIN_GPU_EXT";
				break;
			default:
				return "XrPerfSettingsDomainEXT_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrPerfSettingsSubDomainEXT(XrPerfSettingsSubDomainEXT In){
		switch(In){

			case(XR_PERF_SETTINGS_SUB_DOMAIN_COMPOSITING_EXT):
				return "XR_PERF_SETTINGS_SUB_DOMAIN_COMPOSITING_EXT";
				break;
			case(XR_PERF_SETTINGS_SUB_DOMAIN_RENDERING_EXT):
				return "XR_PERF_SETTINGS_SUB_DOMAIN_RENDERING_EXT";
				break;
			case(XR_PERF_SETTINGS_SUB_DOMAIN_THERMAL_EXT):
				return "XR_PERF_SETTINGS_SUB_DOMAIN_THERMAL_EXT";
				break;
			default:
				return "XrPerfSettingsSubDomainEXT_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrPerfSettingsLevelEXT(XrPerfSettingsLevelEXT In){
		switch(In){

			case(XR_PERF_SETTINGS_LEVEL_POWER_SAVINGS_EXT):
				return "XR_PERF_SETTINGS_LEVEL_POWER_SAVINGS_EXT";
				break;
			case(XR_PERF_SETTINGS_LEVEL_SUSTAINED_LOW_EXT):
				return "XR_PERF_SETTINGS_LEVEL_SUSTAINED_LOW_EXT";
				break;
			case(XR_PERF_SETTINGS_LEVEL_SUSTAINED_HIGH_EXT):
				return "XR_PERF_SETTINGS_LEVEL_SUSTAINED_HIGH_EXT";
				break;
			case(XR_PERF_SETTINGS_LEVEL_BOOST_EXT):
				return "XR_PERF_SETTINGS_LEVEL_BOOST_EXT";
				break;
			default:
				return "XrPerfSettingsLevelEXT_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrPerfSettingsNotificationLevelEXT(XrPerfSettingsNotificationLevelEXT In){
		switch(In){

			case(XR_PERF_SETTINGS_NOTIF_LEVEL_NORMAL_EXT):
				return "XR_PERF_SETTINGS_NOTIF_LEVEL_NORMAL_EXT";
				break;
			case(XR_PERF_SETTINGS_NOTIF_LEVEL_WARNING_EXT):
				return "XR_PERF_SETTINGS_NOTIF_LEVEL_WARNING_EXT";
				break;
			case(XR_PERF_SETTINGS_NOTIF_LEVEL_IMPAIRED_EXT):
				return "XR_PERF_SETTINGS_NOTIF_LEVEL_IMPAIRED_EXT";
				break;
			default:
				return "XrPerfSettingsNotificationLevelEXT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_EXT_performance_settings)  */
	#if defined(XR_EXT_plane_detection)
	const char* vtostr8_XrPlaneDetectionStateEXT(XrPlaneDetectionStateEXT In){
		switch(In){

			case(XR_PLANE_DETECTION_STATE_NONE_EXT):
				return "XR_PLANE_DETECTION_STATE_NONE_EXT";
				break;
			case(XR_PLANE_DETECTION_STATE_PENDING_EXT):
				return "XR_PLANE_DETECTION_STATE_PENDING_EXT";
				break;
			case(XR_PLANE_DETECTION_STATE_DONE_EXT):
				return "XR_PLANE_DETECTION_STATE_DONE_EXT";
				break;
			case(XR_PLANE_DETECTION_STATE_ERROR_EXT):
				return "XR_PLANE_DETECTION_STATE_ERROR_EXT";
				break;
			case(XR_PLANE_DETECTION_STATE_FATAL_EXT):
				return "XR_PLANE_DETECTION_STATE_FATAL_EXT";
				break;
			default:
				return "XrPlaneDetectionStateEXT_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrPlaneDetectorSemanticTypeEXT(XrPlaneDetectorSemanticTypeEXT In){
		switch(In){

			case(XR_PLANE_DETECTOR_SEMANTIC_TYPE_UNDEFINED_EXT):
				return "XR_PLANE_DETECTOR_SEMANTIC_TYPE_UNDEFINED_EXT";
				break;
			case(XR_PLANE_DETECTOR_SEMANTIC_TYPE_CEILING_EXT):
				return "XR_PLANE_DETECTOR_SEMANTIC_TYPE_CEILING_EXT";
				break;
			case(XR_PLANE_DETECTOR_SEMANTIC_TYPE_FLOOR_EXT):
				return "XR_PLANE_DETECTOR_SEMANTIC_TYPE_FLOOR_EXT";
				break;
			case(XR_PLANE_DETECTOR_SEMANTIC_TYPE_WALL_EXT):
				return "XR_PLANE_DETECTOR_SEMANTIC_TYPE_WALL_EXT";
				break;
			case(XR_PLANE_DETECTOR_SEMANTIC_TYPE_PLATFORM_EXT):
				return "XR_PLANE_DETECTOR_SEMANTIC_TYPE_PLATFORM_EXT";
				break;
			default:
				return "XrPlaneDetectorSemanticTypeEXT_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrPlaneDetectorOrientationEXT(XrPlaneDetectorOrientationEXT In){
		switch(In){

			case(XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_UPWARD_EXT):
				return "XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_UPWARD_EXT";
				break;
			case(XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_DOWNWARD_EXT):
				return "XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_DOWNWARD_EXT";
				break;
			case(XR_PLANE_DETECTOR_ORIENTATION_VERTICAL_EXT):
				return "XR_PLANE_DETECTOR_ORIENTATION_VERTICAL_EXT";
				break;
			case(XR_PLANE_DETECTOR_ORIENTATION_ARBITRARY_EXT):
				return "XR_PLANE_DETECTOR_ORIENTATION_ARBITRARY_EXT";
				break;
			default:
				return "XrPlaneDetectorOrientationEXT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_EXT_plane_detection)  */
	#if defined(XR_EXT_thermal_query)
	/*
		const char* vtostr8_XrPerfSettingsDomainEXT(XrPerfSettingsDomainEXT In){
		switch(In){

		case(XR_PERF_SETTINGS_DOMAIN_CPU_EXT):
        return "XR_PERF_SETTINGS_DOMAIN_CPU_EXT";
        break;
		case(XR_PERF_SETTINGS_DOMAIN_GPU_EXT):
        return "XR_PERF_SETTINGS_DOMAIN_GPU_EXT";
        break;
		default:
        return "XrPerfSettingsDomainEXT_TOSTR_ERROR";

		}

		}

		const char* vtostr8_XrPerfSettingsNotificationLevelEXT(XrPerfSettingsNotificationLevelEXT In){
		switch(In){

		case(XR_PERF_SETTINGS_NOTIF_LEVEL_NORMAL_EXT):
        return "XR_PERF_SETTINGS_NOTIF_LEVEL_NORMAL_EXT";
        break;
		case(XR_PERF_SETTINGS_NOTIF_LEVEL_WARNING_EXT):
        return "XR_PERF_SETTINGS_NOTIF_LEVEL_WARNING_EXT";
        break;
		case(XR_PERF_SETTINGS_NOTIF_LEVEL_IMPAIRED_EXT):
        return "XR_PERF_SETTINGS_NOTIF_LEVEL_IMPAIRED_EXT";
        break;
		default:
        return "XrPerfSettingsNotificationLevelEXT_TOSTR_ERROR";

		}

		}*/

	#endif /*  defined(XR_EXT_thermal_query)  */
	#if defined(XR_FB_body_tracking)
	const char* vtostr8_XrBodyJointFB(XrBodyJointFB In){
		switch(In){

			case(XR_BODY_JOINT_ROOT_FB):
				return "XR_BODY_JOINT_ROOT_FB";
				break;
			case(XR_BODY_JOINT_HIPS_FB):
				return "XR_BODY_JOINT_HIPS_FB";
				break;
			case(XR_BODY_JOINT_SPINE_LOWER_FB):
				return "XR_BODY_JOINT_SPINE_LOWER_FB";
				break;
			case(XR_BODY_JOINT_SPINE_MIDDLE_FB):
				return "XR_BODY_JOINT_SPINE_MIDDLE_FB";
				break;
			case(XR_BODY_JOINT_SPINE_UPPER_FB):
				return "XR_BODY_JOINT_SPINE_UPPER_FB";
				break;
			case(XR_BODY_JOINT_CHEST_FB):
				return "XR_BODY_JOINT_CHEST_FB";
				break;
			case(XR_BODY_JOINT_NECK_FB):
				return "XR_BODY_JOINT_NECK_FB";
				break;
			case(XR_BODY_JOINT_HEAD_FB):
				return "XR_BODY_JOINT_HEAD_FB";
				break;
			case(XR_BODY_JOINT_LEFT_SHOULDER_FB):
				return "XR_BODY_JOINT_LEFT_SHOULDER_FB";
				break;
			case(XR_BODY_JOINT_LEFT_SCAPULA_FB):
				return "XR_BODY_JOINT_LEFT_SCAPULA_FB";
				break;
			case(XR_BODY_JOINT_LEFT_ARM_UPPER_FB):
				return "XR_BODY_JOINT_LEFT_ARM_UPPER_FB";
				break;
			case(XR_BODY_JOINT_LEFT_ARM_LOWER_FB):
				return "XR_BODY_JOINT_LEFT_ARM_LOWER_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_WRIST_TWIST_FB):
				return "XR_BODY_JOINT_LEFT_HAND_WRIST_TWIST_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_SHOULDER_FB):
				return "XR_BODY_JOINT_RIGHT_SHOULDER_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_SCAPULA_FB):
				return "XR_BODY_JOINT_RIGHT_SCAPULA_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_ARM_UPPER_FB):
				return "XR_BODY_JOINT_RIGHT_ARM_UPPER_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_ARM_LOWER_FB):
				return "XR_BODY_JOINT_RIGHT_ARM_LOWER_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_WRIST_TWIST_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_WRIST_TWIST_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_PALM_FB):
				return "XR_BODY_JOINT_LEFT_HAND_PALM_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_WRIST_FB):
				return "XR_BODY_JOINT_LEFT_HAND_WRIST_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_THUMB_METACARPAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_THUMB_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_THUMB_PROXIMAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_THUMB_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_THUMB_DISTAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_THUMB_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_THUMB_TIP_FB):
				return "XR_BODY_JOINT_LEFT_HAND_THUMB_TIP_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_INDEX_METACARPAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_INDEX_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_INDEX_PROXIMAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_INDEX_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_INDEX_INTERMEDIATE_FB):
				return "XR_BODY_JOINT_LEFT_HAND_INDEX_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_INDEX_DISTAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_INDEX_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_INDEX_TIP_FB):
				return "XR_BODY_JOINT_LEFT_HAND_INDEX_TIP_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_METACARPAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_MIDDLE_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_PROXIMAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_MIDDLE_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_INTERMEDIATE_FB):
				return "XR_BODY_JOINT_LEFT_HAND_MIDDLE_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_DISTAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_MIDDLE_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_TIP_FB):
				return "XR_BODY_JOINT_LEFT_HAND_MIDDLE_TIP_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_RING_METACARPAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_RING_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_RING_PROXIMAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_RING_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_RING_INTERMEDIATE_FB):
				return "XR_BODY_JOINT_LEFT_HAND_RING_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_RING_DISTAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_RING_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_RING_TIP_FB):
				return "XR_BODY_JOINT_LEFT_HAND_RING_TIP_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_LITTLE_METACARPAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_LITTLE_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_LITTLE_PROXIMAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_LITTLE_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_LITTLE_INTERMEDIATE_FB):
				return "XR_BODY_JOINT_LEFT_HAND_LITTLE_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_LITTLE_DISTAL_FB):
				return "XR_BODY_JOINT_LEFT_HAND_LITTLE_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_LITTLE_TIP_FB):
				return "XR_BODY_JOINT_LEFT_HAND_LITTLE_TIP_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_PALM_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_PALM_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_WRIST_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_WRIST_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_THUMB_METACARPAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_THUMB_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_THUMB_PROXIMAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_THUMB_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_THUMB_DISTAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_THUMB_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_THUMB_TIP_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_THUMB_TIP_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_INDEX_METACARPAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_INDEX_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_INDEX_PROXIMAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_INDEX_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_INDEX_INTERMEDIATE_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_INDEX_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_INDEX_DISTAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_INDEX_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_INDEX_TIP_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_INDEX_TIP_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_METACARPAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_MIDDLE_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_PROXIMAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_MIDDLE_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_INTERMEDIATE_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_MIDDLE_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_DISTAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_MIDDLE_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_TIP_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_MIDDLE_TIP_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_RING_METACARPAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_RING_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_RING_PROXIMAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_RING_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_RING_INTERMEDIATE_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_RING_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_RING_DISTAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_RING_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_RING_TIP_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_RING_TIP_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_METACARPAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_LITTLE_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_PROXIMAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_LITTLE_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_INTERMEDIATE_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_LITTLE_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_DISTAL_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_LITTLE_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_TIP_FB):
				return "XR_BODY_JOINT_RIGHT_HAND_LITTLE_TIP_FB";
				break;
			case(XR_BODY_JOINT_COUNT_FB):
				return "XR_BODY_JOINT_COUNT_FB";
				break;
			case(XR_BODY_JOINT_NONE_FB):
				return "XR_BODY_JOINT_NONE_FB";
				break;
			default:
				return "XrBodyJointFB_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrBodyJointSetFB(XrBodyJointSetFB In){
		switch(In){

			case(XR_BODY_JOINT_SET_DEFAULT_FB):
				return "XR_BODY_JOINT_SET_DEFAULT_FB";
				break;
			default:
				return "XrBodyJointSetFB_TOSTR_ERROR";

		}

	}

	/*
		const char* vtostr8_XrBodyJointFB(XrBodyJointFB In){
		switch(In){

		case(XR_BODY_JOINT_ROOT_FB):
        return "XR_BODY_JOINT_ROOT_FB";
        break;
		case(XR_BODY_JOINT_HIPS_FB):
        return "XR_BODY_JOINT_HIPS_FB";
        break;
		case(XR_BODY_JOINT_SPINE_LOWER_FB):
        return "XR_BODY_JOINT_SPINE_LOWER_FB";
        break;
		case(XR_BODY_JOINT_SPINE_MIDDLE_FB):
        return "XR_BODY_JOINT_SPINE_MIDDLE_FB";
        break;
		case(XR_BODY_JOINT_SPINE_UPPER_FB):
        return "XR_BODY_JOINT_SPINE_UPPER_FB";
        break;
		case(XR_BODY_JOINT_CHEST_FB):
        return "XR_BODY_JOINT_CHEST_FB";
        break;
		case(XR_BODY_JOINT_NECK_FB):
        return "XR_BODY_JOINT_NECK_FB";
        break;
		case(XR_BODY_JOINT_HEAD_FB):
        return "XR_BODY_JOINT_HEAD_FB";
        break;
		case(XR_BODY_JOINT_LEFT_SHOULDER_FB):
        return "XR_BODY_JOINT_LEFT_SHOULDER_FB";
        break;
		case(XR_BODY_JOINT_LEFT_SCAPULA_FB):
        return "XR_BODY_JOINT_LEFT_SCAPULA_FB";
        break;
		case(XR_BODY_JOINT_LEFT_ARM_UPPER_FB):
        return "XR_BODY_JOINT_LEFT_ARM_UPPER_FB";
        break;
		case(XR_BODY_JOINT_LEFT_ARM_LOWER_FB):
        return "XR_BODY_JOINT_LEFT_ARM_LOWER_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_WRIST_TWIST_FB):
        return "XR_BODY_JOINT_LEFT_HAND_WRIST_TWIST_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_SHOULDER_FB):
        return "XR_BODY_JOINT_RIGHT_SHOULDER_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_SCAPULA_FB):
        return "XR_BODY_JOINT_RIGHT_SCAPULA_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_ARM_UPPER_FB):
        return "XR_BODY_JOINT_RIGHT_ARM_UPPER_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_ARM_LOWER_FB):
        return "XR_BODY_JOINT_RIGHT_ARM_LOWER_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_WRIST_TWIST_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_WRIST_TWIST_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_PALM_FB):
        return "XR_BODY_JOINT_LEFT_HAND_PALM_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_WRIST_FB):
        return "XR_BODY_JOINT_LEFT_HAND_WRIST_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_THUMB_METACARPAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_THUMB_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_THUMB_PROXIMAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_THUMB_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_THUMB_DISTAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_THUMB_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_THUMB_TIP_FB):
        return "XR_BODY_JOINT_LEFT_HAND_THUMB_TIP_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_INDEX_METACARPAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_INDEX_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_INDEX_PROXIMAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_INDEX_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_INDEX_INTERMEDIATE_FB):
        return "XR_BODY_JOINT_LEFT_HAND_INDEX_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_INDEX_DISTAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_INDEX_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_INDEX_TIP_FB):
        return "XR_BODY_JOINT_LEFT_HAND_INDEX_TIP_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_METACARPAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_MIDDLE_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_PROXIMAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_MIDDLE_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_INTERMEDIATE_FB):
        return "XR_BODY_JOINT_LEFT_HAND_MIDDLE_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_DISTAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_MIDDLE_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_TIP_FB):
        return "XR_BODY_JOINT_LEFT_HAND_MIDDLE_TIP_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_RING_METACARPAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_RING_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_RING_PROXIMAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_RING_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_RING_INTERMEDIATE_FB):
        return "XR_BODY_JOINT_LEFT_HAND_RING_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_RING_DISTAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_RING_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_RING_TIP_FB):
        return "XR_BODY_JOINT_LEFT_HAND_RING_TIP_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_LITTLE_METACARPAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_LITTLE_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_LITTLE_PROXIMAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_LITTLE_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_LITTLE_INTERMEDIATE_FB):
        return "XR_BODY_JOINT_LEFT_HAND_LITTLE_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_LITTLE_DISTAL_FB):
        return "XR_BODY_JOINT_LEFT_HAND_LITTLE_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_LITTLE_TIP_FB):
        return "XR_BODY_JOINT_LEFT_HAND_LITTLE_TIP_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_PALM_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_PALM_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_WRIST_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_WRIST_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_THUMB_METACARPAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_THUMB_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_THUMB_PROXIMAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_THUMB_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_THUMB_DISTAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_THUMB_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_THUMB_TIP_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_THUMB_TIP_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_INDEX_METACARPAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_INDEX_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_INDEX_PROXIMAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_INDEX_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_INDEX_INTERMEDIATE_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_INDEX_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_INDEX_DISTAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_INDEX_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_INDEX_TIP_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_INDEX_TIP_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_METACARPAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_MIDDLE_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_PROXIMAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_MIDDLE_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_INTERMEDIATE_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_MIDDLE_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_DISTAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_MIDDLE_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_TIP_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_MIDDLE_TIP_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_RING_METACARPAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_RING_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_RING_PROXIMAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_RING_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_RING_INTERMEDIATE_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_RING_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_RING_DISTAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_RING_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_RING_TIP_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_RING_TIP_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_METACARPAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_LITTLE_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_PROXIMAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_LITTLE_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_INTERMEDIATE_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_LITTLE_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_DISTAL_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_LITTLE_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_TIP_FB):
        return "XR_BODY_JOINT_RIGHT_HAND_LITTLE_TIP_FB";
        break;
		case(XR_BODY_JOINT_COUNT_FB):
        return "XR_BODY_JOINT_COUNT_FB";
        break;
		case(XR_BODY_JOINT_NONE_FB):
        return "XR_BODY_JOINT_NONE_FB";
        break;
		default:
        return "XrBodyJointFB_TOSTR_ERROR";

		}

		}*/

	#endif /*  defined(XR_FB_body_tracking)  */
	#if defined(XR_FB_color_space)
	const char* vtostr8_XrColorSpaceFB(XrColorSpaceFB In){
		switch(In){

			case(XR_COLOR_SPACE_UNMANAGED_FB):
				return "XR_COLOR_SPACE_UNMANAGED_FB";
				break;
			case(XR_COLOR_SPACE_REC2020_FB):
				return "XR_COLOR_SPACE_REC2020_FB";
				break;
			case(XR_COLOR_SPACE_REC709_FB):
				return "XR_COLOR_SPACE_REC709_FB";
				break;
			case(XR_COLOR_SPACE_RIFT_CV1_FB):
				return "XR_COLOR_SPACE_RIFT_CV1_FB";
				break;
			case(XR_COLOR_SPACE_RIFT_S_FB):
				return "XR_COLOR_SPACE_RIFT_S_FB";
				break;
			case(XR_COLOR_SPACE_QUEST_FB):
				return "XR_COLOR_SPACE_QUEST_FB";
				break;
			case(XR_COLOR_SPACE_P3_FB):
				return "XR_COLOR_SPACE_P3_FB";
				break;
			case(XR_COLOR_SPACE_ADOBE_RGB_FB):
				return "XR_COLOR_SPACE_ADOBE_RGB_FB";
				break;
			default:
				return "XrColorSpaceFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_color_space)  */
	#if defined(XR_FB_composition_layer_alpha_blend)
	const char* vtostr8_XrBlendFactorFB(XrBlendFactorFB In){
		switch(In){

			case(XR_BLEND_FACTOR_ZERO_FB):
				return "XR_BLEND_FACTOR_ZERO_FB";
				break;
			case(XR_BLEND_FACTOR_ONE_FB):
				return "XR_BLEND_FACTOR_ONE_FB";
				break;
			case(XR_BLEND_FACTOR_SRC_ALPHA_FB):
				return "XR_BLEND_FACTOR_SRC_ALPHA_FB";
				break;
			case(XR_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA_FB):
				return "XR_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA_FB";
				break;
			case(XR_BLEND_FACTOR_DST_ALPHA_FB):
				return "XR_BLEND_FACTOR_DST_ALPHA_FB";
				break;
			case(XR_BLEND_FACTOR_ONE_MINUS_DST_ALPHA_FB):
				return "XR_BLEND_FACTOR_ONE_MINUS_DST_ALPHA_FB";
				break;
			default:
				return "XrBlendFactorFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_composition_layer_alpha_blend)  */
	#if defined(XR_FB_composition_layer_depth_test)
	const char* vtostr8_XrCompareOpFB(XrCompareOpFB In){
		switch(In){

			case(XR_COMPARE_OP_NEVER_FB):
				return "XR_COMPARE_OP_NEVER_FB";
				break;
			case(XR_COMPARE_OP_LESS_FB):
				return "XR_COMPARE_OP_LESS_FB";
				break;
			case(XR_COMPARE_OP_EQUAL_FB):
				return "XR_COMPARE_OP_EQUAL_FB";
				break;
			case(XR_COMPARE_OP_LESS_OR_EQUAL_FB):
				return "XR_COMPARE_OP_LESS_OR_EQUAL_FB";
				break;
			case(XR_COMPARE_OP_GREATER_FB):
				return "XR_COMPARE_OP_GREATER_FB";
				break;
			case(XR_COMPARE_OP_NOT_EQUAL_FB):
				return "XR_COMPARE_OP_NOT_EQUAL_FB";
				break;
			case(XR_COMPARE_OP_GREATER_OR_EQUAL_FB):
				return "XR_COMPARE_OP_GREATER_OR_EQUAL_FB";
				break;
			case(XR_COMPARE_OP_ALWAYS_FB):
				return "XR_COMPARE_OP_ALWAYS_FB";
				break;
			default:
				return "XrCompareOpFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_composition_layer_depth_test)  */
	#if defined(XR_FB_eye_tracking_social)
	const char* vtostr8_XrEyePositionFB(XrEyePositionFB In){
		switch(In){

			case(XR_EYE_POSITION_LEFT_FB):
				return "XR_EYE_POSITION_LEFT_FB";
				break;
			case(XR_EYE_POSITION_RIGHT_FB):
				return "XR_EYE_POSITION_RIGHT_FB";
				break;
			case(XR_EYE_POSITION_COUNT_FB):
				return "XR_EYE_POSITION_COUNT_FB";
				break;
			default:
				return "XrEyePositionFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_eye_tracking_social)  */
	#if defined(XR_FB_face_tracking)
	const char* vtostr8_XrFaceExpressionFB(XrFaceExpressionFB In){
		switch(In){

			case(XR_FACE_EXPRESSION_BROW_LOWERER_L_FB):
				return "XR_FACE_EXPRESSION_BROW_LOWERER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_BROW_LOWERER_R_FB):
				return "XR_FACE_EXPRESSION_BROW_LOWERER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_CHEEK_PUFF_L_FB):
				return "XR_FACE_EXPRESSION_CHEEK_PUFF_L_FB";
				break;
			case(XR_FACE_EXPRESSION_CHEEK_PUFF_R_FB):
				return "XR_FACE_EXPRESSION_CHEEK_PUFF_R_FB";
				break;
			case(XR_FACE_EXPRESSION_CHEEK_RAISER_L_FB):
				return "XR_FACE_EXPRESSION_CHEEK_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_CHEEK_RAISER_R_FB):
				return "XR_FACE_EXPRESSION_CHEEK_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_CHEEK_SUCK_L_FB):
				return "XR_FACE_EXPRESSION_CHEEK_SUCK_L_FB";
				break;
			case(XR_FACE_EXPRESSION_CHEEK_SUCK_R_FB):
				return "XR_FACE_EXPRESSION_CHEEK_SUCK_R_FB";
				break;
			case(XR_FACE_EXPRESSION_CHIN_RAISER_B_FB):
				return "XR_FACE_EXPRESSION_CHIN_RAISER_B_FB";
				break;
			case(XR_FACE_EXPRESSION_CHIN_RAISER_T_FB):
				return "XR_FACE_EXPRESSION_CHIN_RAISER_T_FB";
				break;
			case(XR_FACE_EXPRESSION_DIMPLER_L_FB):
				return "XR_FACE_EXPRESSION_DIMPLER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_DIMPLER_R_FB):
				return "XR_FACE_EXPRESSION_DIMPLER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_CLOSED_L_FB):
				return "XR_FACE_EXPRESSION_EYES_CLOSED_L_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_CLOSED_R_FB):
				return "XR_FACE_EXPRESSION_EYES_CLOSED_R_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_DOWN_L_FB):
				return "XR_FACE_EXPRESSION_EYES_LOOK_DOWN_L_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_DOWN_R_FB):
				return "XR_FACE_EXPRESSION_EYES_LOOK_DOWN_R_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_LEFT_L_FB):
				return "XR_FACE_EXPRESSION_EYES_LOOK_LEFT_L_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_LEFT_R_FB):
				return "XR_FACE_EXPRESSION_EYES_LOOK_LEFT_R_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_RIGHT_L_FB):
				return "XR_FACE_EXPRESSION_EYES_LOOK_RIGHT_L_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_RIGHT_R_FB):
				return "XR_FACE_EXPRESSION_EYES_LOOK_RIGHT_R_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_UP_L_FB):
				return "XR_FACE_EXPRESSION_EYES_LOOK_UP_L_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_UP_R_FB):
				return "XR_FACE_EXPRESSION_EYES_LOOK_UP_R_FB";
				break;
			case(XR_FACE_EXPRESSION_INNER_BROW_RAISER_L_FB):
				return "XR_FACE_EXPRESSION_INNER_BROW_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_INNER_BROW_RAISER_R_FB):
				return "XR_FACE_EXPRESSION_INNER_BROW_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_JAW_DROP_FB):
				return "XR_FACE_EXPRESSION_JAW_DROP_FB";
				break;
			case(XR_FACE_EXPRESSION_JAW_SIDEWAYS_LEFT_FB):
				return "XR_FACE_EXPRESSION_JAW_SIDEWAYS_LEFT_FB";
				break;
			case(XR_FACE_EXPRESSION_JAW_SIDEWAYS_RIGHT_FB):
				return "XR_FACE_EXPRESSION_JAW_SIDEWAYS_RIGHT_FB";
				break;
			case(XR_FACE_EXPRESSION_JAW_THRUST_FB):
				return "XR_FACE_EXPRESSION_JAW_THRUST_FB";
				break;
			case(XR_FACE_EXPRESSION_LID_TIGHTENER_L_FB):
				return "XR_FACE_EXPRESSION_LID_TIGHTENER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LID_TIGHTENER_R_FB):
				return "XR_FACE_EXPRESSION_LID_TIGHTENER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_CORNER_DEPRESSOR_L_FB):
				return "XR_FACE_EXPRESSION_LIP_CORNER_DEPRESSOR_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_CORNER_DEPRESSOR_R_FB):
				return "XR_FACE_EXPRESSION_LIP_CORNER_DEPRESSOR_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_CORNER_PULLER_L_FB):
				return "XR_FACE_EXPRESSION_LIP_CORNER_PULLER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_CORNER_PULLER_R_FB):
				return "XR_FACE_EXPRESSION_LIP_CORNER_PULLER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_FUNNELER_LB_FB):
				return "XR_FACE_EXPRESSION_LIP_FUNNELER_LB_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_FUNNELER_LT_FB):
				return "XR_FACE_EXPRESSION_LIP_FUNNELER_LT_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_FUNNELER_RB_FB):
				return "XR_FACE_EXPRESSION_LIP_FUNNELER_RB_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_FUNNELER_RT_FB):
				return "XR_FACE_EXPRESSION_LIP_FUNNELER_RT_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_PRESSOR_L_FB):
				return "XR_FACE_EXPRESSION_LIP_PRESSOR_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_PRESSOR_R_FB):
				return "XR_FACE_EXPRESSION_LIP_PRESSOR_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_PUCKER_L_FB):
				return "XR_FACE_EXPRESSION_LIP_PUCKER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_PUCKER_R_FB):
				return "XR_FACE_EXPRESSION_LIP_PUCKER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_STRETCHER_L_FB):
				return "XR_FACE_EXPRESSION_LIP_STRETCHER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_STRETCHER_R_FB):
				return "XR_FACE_EXPRESSION_LIP_STRETCHER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_SUCK_LB_FB):
				return "XR_FACE_EXPRESSION_LIP_SUCK_LB_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_SUCK_LT_FB):
				return "XR_FACE_EXPRESSION_LIP_SUCK_LT_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_SUCK_RB_FB):
				return "XR_FACE_EXPRESSION_LIP_SUCK_RB_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_SUCK_RT_FB):
				return "XR_FACE_EXPRESSION_LIP_SUCK_RT_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_TIGHTENER_L_FB):
				return "XR_FACE_EXPRESSION_LIP_TIGHTENER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_TIGHTENER_R_FB):
				return "XR_FACE_EXPRESSION_LIP_TIGHTENER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIPS_TOWARD_FB):
				return "XR_FACE_EXPRESSION_LIPS_TOWARD_FB";
				break;
			case(XR_FACE_EXPRESSION_LOWER_LIP_DEPRESSOR_L_FB):
				return "XR_FACE_EXPRESSION_LOWER_LIP_DEPRESSOR_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LOWER_LIP_DEPRESSOR_R_FB):
				return "XR_FACE_EXPRESSION_LOWER_LIP_DEPRESSOR_R_FB";
				break;
			case(XR_FACE_EXPRESSION_MOUTH_LEFT_FB):
				return "XR_FACE_EXPRESSION_MOUTH_LEFT_FB";
				break;
			case(XR_FACE_EXPRESSION_MOUTH_RIGHT_FB):
				return "XR_FACE_EXPRESSION_MOUTH_RIGHT_FB";
				break;
			case(XR_FACE_EXPRESSION_NOSE_WRINKLER_L_FB):
				return "XR_FACE_EXPRESSION_NOSE_WRINKLER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_NOSE_WRINKLER_R_FB):
				return "XR_FACE_EXPRESSION_NOSE_WRINKLER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_OUTER_BROW_RAISER_L_FB):
				return "XR_FACE_EXPRESSION_OUTER_BROW_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_OUTER_BROW_RAISER_R_FB):
				return "XR_FACE_EXPRESSION_OUTER_BROW_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_UPPER_LID_RAISER_L_FB):
				return "XR_FACE_EXPRESSION_UPPER_LID_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_UPPER_LID_RAISER_R_FB):
				return "XR_FACE_EXPRESSION_UPPER_LID_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_UPPER_LIP_RAISER_L_FB):
				return "XR_FACE_EXPRESSION_UPPER_LIP_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_UPPER_LIP_RAISER_R_FB):
				return "XR_FACE_EXPRESSION_UPPER_LIP_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_COUNT_FB):
				return "XR_FACE_EXPRESSION_COUNT_FB";
				break;
			default:
				return "XrFaceExpressionFB_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrFaceExpressionSetFB(XrFaceExpressionSetFB In){
		switch(In){

			case(XR_FACE_EXPRESSION_SET_DEFAULT_FB):
				return "XR_FACE_EXPRESSION_SET_DEFAULT_FB";
				break;
			default:
				return "XrFaceExpressionSetFB_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrFaceConfidenceFB(XrFaceConfidenceFB In){
		switch(In){

			case(XR_FACE_CONFIDENCE_LOWER_FACE_FB):
				return "XR_FACE_CONFIDENCE_LOWER_FACE_FB";
				break;
			case(XR_FACE_CONFIDENCE_UPPER_FACE_FB):
				return "XR_FACE_CONFIDENCE_UPPER_FACE_FB";
				break;
			case(XR_FACE_CONFIDENCE_COUNT_FB):
				return "XR_FACE_CONFIDENCE_COUNT_FB";
				break;
			default:
				return "XrFaceConfidenceFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_face_tracking)  */
	#if defined(XR_FB_face_tracking2)
	const char* vtostr8_XrFaceExpression2FB(XrFaceExpression2FB In){
		switch(In){

			case(XR_FACE_EXPRESSION2_BROW_LOWERER_L_FB):
				return "XR_FACE_EXPRESSION2_BROW_LOWERER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_BROW_LOWERER_R_FB):
				return "XR_FACE_EXPRESSION2_BROW_LOWERER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHEEK_PUFF_L_FB):
				return "XR_FACE_EXPRESSION2_CHEEK_PUFF_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHEEK_PUFF_R_FB):
				return "XR_FACE_EXPRESSION2_CHEEK_PUFF_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHEEK_RAISER_L_FB):
				return "XR_FACE_EXPRESSION2_CHEEK_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHEEK_RAISER_R_FB):
				return "XR_FACE_EXPRESSION2_CHEEK_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHEEK_SUCK_L_FB):
				return "XR_FACE_EXPRESSION2_CHEEK_SUCK_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHEEK_SUCK_R_FB):
				return "XR_FACE_EXPRESSION2_CHEEK_SUCK_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHIN_RAISER_B_FB):
				return "XR_FACE_EXPRESSION2_CHIN_RAISER_B_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHIN_RAISER_T_FB):
				return "XR_FACE_EXPRESSION2_CHIN_RAISER_T_FB";
				break;
			case(XR_FACE_EXPRESSION2_DIMPLER_L_FB):
				return "XR_FACE_EXPRESSION2_DIMPLER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_DIMPLER_R_FB):
				return "XR_FACE_EXPRESSION2_DIMPLER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_CLOSED_L_FB):
				return "XR_FACE_EXPRESSION2_EYES_CLOSED_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_CLOSED_R_FB):
				return "XR_FACE_EXPRESSION2_EYES_CLOSED_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_DOWN_L_FB):
				return "XR_FACE_EXPRESSION2_EYES_LOOK_DOWN_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_DOWN_R_FB):
				return "XR_FACE_EXPRESSION2_EYES_LOOK_DOWN_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_LEFT_L_FB):
				return "XR_FACE_EXPRESSION2_EYES_LOOK_LEFT_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_LEFT_R_FB):
				return "XR_FACE_EXPRESSION2_EYES_LOOK_LEFT_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_RIGHT_L_FB):
				return "XR_FACE_EXPRESSION2_EYES_LOOK_RIGHT_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_RIGHT_R_FB):
				return "XR_FACE_EXPRESSION2_EYES_LOOK_RIGHT_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_UP_L_FB):
				return "XR_FACE_EXPRESSION2_EYES_LOOK_UP_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_UP_R_FB):
				return "XR_FACE_EXPRESSION2_EYES_LOOK_UP_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_INNER_BROW_RAISER_L_FB):
				return "XR_FACE_EXPRESSION2_INNER_BROW_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_INNER_BROW_RAISER_R_FB):
				return "XR_FACE_EXPRESSION2_INNER_BROW_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_JAW_DROP_FB):
				return "XR_FACE_EXPRESSION2_JAW_DROP_FB";
				break;
			case(XR_FACE_EXPRESSION2_JAW_SIDEWAYS_LEFT_FB):
				return "XR_FACE_EXPRESSION2_JAW_SIDEWAYS_LEFT_FB";
				break;
			case(XR_FACE_EXPRESSION2_JAW_SIDEWAYS_RIGHT_FB):
				return "XR_FACE_EXPRESSION2_JAW_SIDEWAYS_RIGHT_FB";
				break;
			case(XR_FACE_EXPRESSION2_JAW_THRUST_FB):
				return "XR_FACE_EXPRESSION2_JAW_THRUST_FB";
				break;
			case(XR_FACE_EXPRESSION2_LID_TIGHTENER_L_FB):
				return "XR_FACE_EXPRESSION2_LID_TIGHTENER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LID_TIGHTENER_R_FB):
				return "XR_FACE_EXPRESSION2_LID_TIGHTENER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_CORNER_DEPRESSOR_L_FB):
				return "XR_FACE_EXPRESSION2_LIP_CORNER_DEPRESSOR_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_CORNER_DEPRESSOR_R_FB):
				return "XR_FACE_EXPRESSION2_LIP_CORNER_DEPRESSOR_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_CORNER_PULLER_L_FB):
				return "XR_FACE_EXPRESSION2_LIP_CORNER_PULLER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_CORNER_PULLER_R_FB):
				return "XR_FACE_EXPRESSION2_LIP_CORNER_PULLER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_FUNNELER_LB_FB):
				return "XR_FACE_EXPRESSION2_LIP_FUNNELER_LB_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_FUNNELER_LT_FB):
				return "XR_FACE_EXPRESSION2_LIP_FUNNELER_LT_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_FUNNELER_RB_FB):
				return "XR_FACE_EXPRESSION2_LIP_FUNNELER_RB_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_FUNNELER_RT_FB):
				return "XR_FACE_EXPRESSION2_LIP_FUNNELER_RT_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_PRESSOR_L_FB):
				return "XR_FACE_EXPRESSION2_LIP_PRESSOR_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_PRESSOR_R_FB):
				return "XR_FACE_EXPRESSION2_LIP_PRESSOR_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_PUCKER_L_FB):
				return "XR_FACE_EXPRESSION2_LIP_PUCKER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_PUCKER_R_FB):
				return "XR_FACE_EXPRESSION2_LIP_PUCKER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_STRETCHER_L_FB):
				return "XR_FACE_EXPRESSION2_LIP_STRETCHER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_STRETCHER_R_FB):
				return "XR_FACE_EXPRESSION2_LIP_STRETCHER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_SUCK_LB_FB):
				return "XR_FACE_EXPRESSION2_LIP_SUCK_LB_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_SUCK_LT_FB):
				return "XR_FACE_EXPRESSION2_LIP_SUCK_LT_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_SUCK_RB_FB):
				return "XR_FACE_EXPRESSION2_LIP_SUCK_RB_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_SUCK_RT_FB):
				return "XR_FACE_EXPRESSION2_LIP_SUCK_RT_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_TIGHTENER_L_FB):
				return "XR_FACE_EXPRESSION2_LIP_TIGHTENER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_TIGHTENER_R_FB):
				return "XR_FACE_EXPRESSION2_LIP_TIGHTENER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIPS_TOWARD_FB):
				return "XR_FACE_EXPRESSION2_LIPS_TOWARD_FB";
				break;
			case(XR_FACE_EXPRESSION2_LOWER_LIP_DEPRESSOR_L_FB):
				return "XR_FACE_EXPRESSION2_LOWER_LIP_DEPRESSOR_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LOWER_LIP_DEPRESSOR_R_FB):
				return "XR_FACE_EXPRESSION2_LOWER_LIP_DEPRESSOR_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_MOUTH_LEFT_FB):
				return "XR_FACE_EXPRESSION2_MOUTH_LEFT_FB";
				break;
			case(XR_FACE_EXPRESSION2_MOUTH_RIGHT_FB):
				return "XR_FACE_EXPRESSION2_MOUTH_RIGHT_FB";
				break;
			case(XR_FACE_EXPRESSION2_NOSE_WRINKLER_L_FB):
				return "XR_FACE_EXPRESSION2_NOSE_WRINKLER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_NOSE_WRINKLER_R_FB):
				return "XR_FACE_EXPRESSION2_NOSE_WRINKLER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_OUTER_BROW_RAISER_L_FB):
				return "XR_FACE_EXPRESSION2_OUTER_BROW_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_OUTER_BROW_RAISER_R_FB):
				return "XR_FACE_EXPRESSION2_OUTER_BROW_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_UPPER_LID_RAISER_L_FB):
				return "XR_FACE_EXPRESSION2_UPPER_LID_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_UPPER_LID_RAISER_R_FB):
				return "XR_FACE_EXPRESSION2_UPPER_LID_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_UPPER_LIP_RAISER_L_FB):
				return "XR_FACE_EXPRESSION2_UPPER_LIP_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_UPPER_LIP_RAISER_R_FB):
				return "XR_FACE_EXPRESSION2_UPPER_LIP_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_TIP_INTERDENTAL_FB):
				return "XR_FACE_EXPRESSION2_TONGUE_TIP_INTERDENTAL_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_TIP_ALVEOLAR_FB):
				return "XR_FACE_EXPRESSION2_TONGUE_TIP_ALVEOLAR_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_FRONT_DORSAL_PALATE_FB):
				return "XR_FACE_EXPRESSION2_TONGUE_FRONT_DORSAL_PALATE_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_MID_DORSAL_PALATE_FB):
				return "XR_FACE_EXPRESSION2_TONGUE_MID_DORSAL_PALATE_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_BACK_DORSAL_VELAR_FB):
				return "XR_FACE_EXPRESSION2_TONGUE_BACK_DORSAL_VELAR_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_OUT_FB):
				return "XR_FACE_EXPRESSION2_TONGUE_OUT_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_RETREAT_FB):
				return "XR_FACE_EXPRESSION2_TONGUE_RETREAT_FB";
				break;
			case(XR_FACE_EXPRESSION2_COUNT_FB):
				return "XR_FACE_EXPRESSION2_COUNT_FB";
				break;
			default:
				return "XrFaceExpression2FB_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrFaceExpressionSet2FB(XrFaceExpressionSet2FB In){
		switch(In){

			case(XR_FACE_EXPRESSION_SET2_DEFAULT_FB):
				return "XR_FACE_EXPRESSION_SET2_DEFAULT_FB";
				break;
			default:
				return "XrFaceExpressionSet2FB_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrFaceTrackingDataSource2FB(XrFaceTrackingDataSource2FB In){
		switch(In){

			case(XR_FACE_TRACKING_DATA_SOURCE2_VISUAL_FB):
				return "XR_FACE_TRACKING_DATA_SOURCE2_VISUAL_FB";
				break;
			case(XR_FACE_TRACKING_DATA_SOURCE2_AUDIO_FB):
				return "XR_FACE_TRACKING_DATA_SOURCE2_AUDIO_FB";
				break;
			default:
				return "XrFaceTrackingDataSource2FB_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrFaceConfidence2FB(XrFaceConfidence2FB In){
		switch(In){

			case(XR_FACE_CONFIDENCE2_LOWER_FACE_FB):
				return "XR_FACE_CONFIDENCE2_LOWER_FACE_FB";
				break;
			case(XR_FACE_CONFIDENCE2_UPPER_FACE_FB):
				return "XR_FACE_CONFIDENCE2_UPPER_FACE_FB";
				break;
			case(XR_FACE_CONFIDENCE2_COUNT_FB):
				return "XR_FACE_CONFIDENCE2_COUNT_FB";
				break;
			default:
				return "XrFaceConfidence2FB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_face_tracking2)  */
	#if defined(XR_FB_foveation_configuration)
	const char* vtostr8_XrFoveationLevelFB(XrFoveationLevelFB In){
		switch(In){

			case(XR_FOVEATION_LEVEL_NONE_FB):
				return "XR_FOVEATION_LEVEL_NONE_FB";
				break;
			case(XR_FOVEATION_LEVEL_LOW_FB):
				return "XR_FOVEATION_LEVEL_LOW_FB";
				break;
			case(XR_FOVEATION_LEVEL_MEDIUM_FB):
				return "XR_FOVEATION_LEVEL_MEDIUM_FB";
				break;
			case(XR_FOVEATION_LEVEL_HIGH_FB):
				return "XR_FOVEATION_LEVEL_HIGH_FB";
				break;
			default:
				return "XrFoveationLevelFB_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrFoveationDynamicFB(XrFoveationDynamicFB In){
		switch(In){

			case(XR_FOVEATION_DYNAMIC_DISABLED_FB):
				return "XR_FOVEATION_DYNAMIC_DISABLED_FB";
				break;
			case(XR_FOVEATION_DYNAMIC_LEVEL_ENABLED_FB):
				return "XR_FOVEATION_DYNAMIC_LEVEL_ENABLED_FB";
				break;
			default:
				return "XrFoveationDynamicFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_foveation_configuration)  */
	#if defined(XR_FB_spatial_entity_query)
	const char* vtostr8_XrSpaceQueryActionFB(XrSpaceQueryActionFB In){
		switch(In){

			case(XR_SPACE_QUERY_ACTION_LOAD_FB):
				return "XR_SPACE_QUERY_ACTION_LOAD_FB";
				break;
			default:
				return "XrSpaceQueryActionFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_spatial_entity_query)  */
	#if defined(XR_FB_spatial_entity_storage)
	const char* vtostr8_XrSpaceStorageLocationFB(XrSpaceStorageLocationFB In){
		switch(In){

			case(XR_SPACE_STORAGE_LOCATION_INVALID_FB):
				return "XR_SPACE_STORAGE_LOCATION_INVALID_FB";
				break;
			case(XR_SPACE_STORAGE_LOCATION_LOCAL_FB):
				return "XR_SPACE_STORAGE_LOCATION_LOCAL_FB";
				break;
			case(XR_SPACE_STORAGE_LOCATION_CLOUD_FB):
				return "XR_SPACE_STORAGE_LOCATION_CLOUD_FB";
				break;
			default:
				return "XrSpaceStorageLocationFB_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrSpacePersistenceModeFB(XrSpacePersistenceModeFB In){
		switch(In){

			case(XR_SPACE_PERSISTENCE_MODE_INVALID_FB):
				return "XR_SPACE_PERSISTENCE_MODE_INVALID_FB";
				break;
			case(XR_SPACE_PERSISTENCE_MODE_INDEFINITE_FB):
				return "XR_SPACE_PERSISTENCE_MODE_INDEFINITE_FB";
				break;
			default:
				return "XrSpacePersistenceModeFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_spatial_entity_storage)  */
	#if defined(XR_FB_triangle_mesh)
	const char* vtostr8_XrWindingOrderFB(XrWindingOrderFB In){
		switch(In){

			case(XR_WINDING_ORDER_UNKNOWN_FB):
				return "XR_WINDING_ORDER_UNKNOWN_FB";
				break;
			case(XR_WINDING_ORDER_CW_FB):
				return "XR_WINDING_ORDER_CW_FB";
				break;
			case(XR_WINDING_ORDER_CCW_FB):
				return "XR_WINDING_ORDER_CCW_FB";
				break;
			default:
				return "XrWindingOrderFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_triangle_mesh)  */
	#if defined(XR_HTC_body_tracking)
	const char* vtostr8_XrBodyJointHTC(XrBodyJointHTC In){
		switch(In){

			case(XR_BODY_JOINT_PELVIS_HTC):
				return "XR_BODY_JOINT_PELVIS_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_HIP_HTC):
				return "XR_BODY_JOINT_LEFT_HIP_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_KNEE_HTC):
				return "XR_BODY_JOINT_LEFT_KNEE_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_ANKLE_HTC):
				return "XR_BODY_JOINT_LEFT_ANKLE_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_FEET_HTC):
				return "XR_BODY_JOINT_LEFT_FEET_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_HIP_HTC):
				return "XR_BODY_JOINT_RIGHT_HIP_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_KNEE_HTC):
				return "XR_BODY_JOINT_RIGHT_KNEE_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_ANKLE_HTC):
				return "XR_BODY_JOINT_RIGHT_ANKLE_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_FEET_HTC):
				return "XR_BODY_JOINT_RIGHT_FEET_HTC";
				break;
			case(XR_BODY_JOINT_WAIST_HTC):
				return "XR_BODY_JOINT_WAIST_HTC";
				break;
			case(XR_BODY_JOINT_SPINE_LOWER_HTC):
				return "XR_BODY_JOINT_SPINE_LOWER_HTC";
				break;
			case(XR_BODY_JOINT_SPINE_MIDDLE_HTC):
				return "XR_BODY_JOINT_SPINE_MIDDLE_HTC";
				break;
			case(XR_BODY_JOINT_SPINE_HIGH_HTC):
				return "XR_BODY_JOINT_SPINE_HIGH_HTC";
				break;
			case(XR_BODY_JOINT_CHEST_HTC):
				return "XR_BODY_JOINT_CHEST_HTC";
				break;
			case(XR_BODY_JOINT_NECK_HTC):
				return "XR_BODY_JOINT_NECK_HTC";
				break;
			case(XR_BODY_JOINT_HEAD_HTC):
				return "XR_BODY_JOINT_HEAD_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_CLAVICLE_HTC):
				return "XR_BODY_JOINT_LEFT_CLAVICLE_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_SCAPULA_HTC):
				return "XR_BODY_JOINT_LEFT_SCAPULA_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_ARM_HTC):
				return "XR_BODY_JOINT_LEFT_ARM_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_ELBOW_HTC):
				return "XR_BODY_JOINT_LEFT_ELBOW_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_WRIST_HTC):
				return "XR_BODY_JOINT_LEFT_WRIST_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_CLAVICLE_HTC):
				return "XR_BODY_JOINT_RIGHT_CLAVICLE_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_SCAPULA_HTC):
				return "XR_BODY_JOINT_RIGHT_SCAPULA_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_ARM_HTC):
				return "XR_BODY_JOINT_RIGHT_ARM_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_ELBOW_HTC):
				return "XR_BODY_JOINT_RIGHT_ELBOW_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_WRIST_HTC):
				return "XR_BODY_JOINT_RIGHT_WRIST_HTC";
				break;
			default:
				return "XrBodyJointHTC_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrBodyJointSetHTC(XrBodyJointSetHTC In){
		switch(In){

			case(XR_BODY_JOINT_SET_FULL_HTC):
				return "XR_BODY_JOINT_SET_FULL_HTC";
				break;
			default:
				return "XrBodyJointSetHTC_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrBodyJointConfidenceHTC(XrBodyJointConfidenceHTC In){
		switch(In){

			case(XR_BODY_JOINT_CONFIDENCE_NONE_HTC):
				return "XR_BODY_JOINT_CONFIDENCE_NONE_HTC";
				break;
			case(XR_BODY_JOINT_CONFIDENCE_LOW_HTC):
				return "XR_BODY_JOINT_CONFIDENCE_LOW_HTC";
				break;
			case(XR_BODY_JOINT_CONFIDENCE_HIGH_HTC):
				return "XR_BODY_JOINT_CONFIDENCE_HIGH_HTC";
				break;
			default:
				return "XrBodyJointConfidenceHTC_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_HTC_body_tracking)  */
	#if defined(XR_HTC_facial_tracking)
	const char* vtostr8_XrEyeExpressionHTC(XrEyeExpressionHTC In){
		switch(In){

			case(XR_EYE_EXPRESSION_LEFT_BLINK_HTC):
				return "XR_EYE_EXPRESSION_LEFT_BLINK_HTC";
				break;
			case(XR_EYE_EXPRESSION_LEFT_WIDE_HTC):
				return "XR_EYE_EXPRESSION_LEFT_WIDE_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_BLINK_HTC):
				return "XR_EYE_EXPRESSION_RIGHT_BLINK_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_WIDE_HTC):
				return "XR_EYE_EXPRESSION_RIGHT_WIDE_HTC";
				break;
			case(XR_EYE_EXPRESSION_LEFT_SQUEEZE_HTC):
				return "XR_EYE_EXPRESSION_LEFT_SQUEEZE_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_SQUEEZE_HTC):
				return "XR_EYE_EXPRESSION_RIGHT_SQUEEZE_HTC";
				break;
			case(XR_EYE_EXPRESSION_LEFT_DOWN_HTC):
				return "XR_EYE_EXPRESSION_LEFT_DOWN_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_DOWN_HTC):
				return "XR_EYE_EXPRESSION_RIGHT_DOWN_HTC";
				break;
			case(XR_EYE_EXPRESSION_LEFT_OUT_HTC):
				return "XR_EYE_EXPRESSION_LEFT_OUT_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_IN_HTC):
				return "XR_EYE_EXPRESSION_RIGHT_IN_HTC";
				break;
			case(XR_EYE_EXPRESSION_LEFT_IN_HTC):
				return "XR_EYE_EXPRESSION_LEFT_IN_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_OUT_HTC):
				return "XR_EYE_EXPRESSION_RIGHT_OUT_HTC";
				break;
			case(XR_EYE_EXPRESSION_LEFT_UP_HTC):
				return "XR_EYE_EXPRESSION_LEFT_UP_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_UP_HTC):
				return "XR_EYE_EXPRESSION_RIGHT_UP_HTC";
				break;
			default:
				return "XrEyeExpressionHTC_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrLipExpressionHTC(XrLipExpressionHTC In){
		switch(In){

			case(XR_LIP_EXPRESSION_JAW_RIGHT_HTC):
				return "XR_LIP_EXPRESSION_JAW_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_JAW_LEFT_HTC):
				return "XR_LIP_EXPRESSION_JAW_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_JAW_FORWARD_HTC):
				return "XR_LIP_EXPRESSION_JAW_FORWARD_HTC";
				break;
			case(XR_LIP_EXPRESSION_JAW_OPEN_HTC):
				return "XR_LIP_EXPRESSION_JAW_OPEN_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_APE_SHAPE_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_APE_SHAPE_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_UPPER_RIGHT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_UPPER_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_UPPER_LEFT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_UPPER_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_RIGHT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_LOWER_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_LEFT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_LOWER_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_UPPER_OVERTURN_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_UPPER_OVERTURN_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_OVERTURN_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_LOWER_OVERTURN_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_POUT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_POUT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_RAISER_RIGHT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_RAISER_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_RAISER_LEFT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_RAISER_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_STRETCHER_RIGHT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_STRETCHER_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_STRETCHER_LEFT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_STRETCHER_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_CHEEK_PUFF_RIGHT_HTC):
				return "XR_LIP_EXPRESSION_CHEEK_PUFF_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_CHEEK_PUFF_LEFT_HTC):
				return "XR_LIP_EXPRESSION_CHEEK_PUFF_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_CHEEK_SUCK_HTC):
				return "XR_LIP_EXPRESSION_CHEEK_SUCK_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_UPPER_UPRIGHT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_UPPER_UPRIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_UPPER_UPLEFT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_UPPER_UPLEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_DOWNRIGHT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_LOWER_DOWNRIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_DOWNLEFT_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_LOWER_DOWNLEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_UPPER_INSIDE_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_UPPER_INSIDE_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_INSIDE_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_LOWER_INSIDE_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_OVERLAY_HTC):
				return "XR_LIP_EXPRESSION_MOUTH_LOWER_OVERLAY_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_LONGSTEP1_HTC):
				return "XR_LIP_EXPRESSION_TONGUE_LONGSTEP1_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_LEFT_HTC):
				return "XR_LIP_EXPRESSION_TONGUE_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_RIGHT_HTC):
				return "XR_LIP_EXPRESSION_TONGUE_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_UP_HTC):
				return "XR_LIP_EXPRESSION_TONGUE_UP_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_DOWN_HTC):
				return "XR_LIP_EXPRESSION_TONGUE_DOWN_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_ROLL_HTC):
				return "XR_LIP_EXPRESSION_TONGUE_ROLL_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_LONGSTEP2_HTC):
				return "XR_LIP_EXPRESSION_TONGUE_LONGSTEP2_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_UPRIGHT_MORPH_HTC):
				return "XR_LIP_EXPRESSION_TONGUE_UPRIGHT_MORPH_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_UPLEFT_MORPH_HTC):
				return "XR_LIP_EXPRESSION_TONGUE_UPLEFT_MORPH_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_DOWNRIGHT_MORPH_HTC):
				return "XR_LIP_EXPRESSION_TONGUE_DOWNRIGHT_MORPH_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_DOWNLEFT_MORPH_HTC):
				return "XR_LIP_EXPRESSION_TONGUE_DOWNLEFT_MORPH_HTC";
				break;
			default:
				return "XrLipExpressionHTC_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrFacialTrackingTypeHTC(XrFacialTrackingTypeHTC In){
		switch(In){

			case(XR_FACIAL_TRACKING_TYPE_EYE_DEFAULT_HTC):
				return "XR_FACIAL_TRACKING_TYPE_EYE_DEFAULT_HTC";
				break;
			case(XR_FACIAL_TRACKING_TYPE_LIP_DEFAULT_HTC):
				return "XR_FACIAL_TRACKING_TYPE_LIP_DEFAULT_HTC";
				break;
			default:
				return "XrFacialTrackingTypeHTC_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_HTC_facial_tracking)  */
	#if defined(XR_HTC_foveation)
	const char* vtostr8_XrFoveationModeHTC(XrFoveationModeHTC In){
		switch(In){

			case(XR_FOVEATION_MODE_DISABLE_HTC):
				return "XR_FOVEATION_MODE_DISABLE_HTC";
				break;
			case(XR_FOVEATION_MODE_FIXED_HTC):
				return "XR_FOVEATION_MODE_FIXED_HTC";
				break;
			case(XR_FOVEATION_MODE_DYNAMIC_HTC):
				return "XR_FOVEATION_MODE_DYNAMIC_HTC";
				break;
			case(XR_FOVEATION_MODE_CUSTOM_HTC):
				return "XR_FOVEATION_MODE_CUSTOM_HTC";
				break;
			default:
				return "XrFoveationModeHTC_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrFoveationLevelHTC(XrFoveationLevelHTC In){
		switch(In){

			case(XR_FOVEATION_LEVEL_NONE_HTC):
				return "XR_FOVEATION_LEVEL_NONE_HTC";
				break;
			case(XR_FOVEATION_LEVEL_LOW_HTC):
				return "XR_FOVEATION_LEVEL_LOW_HTC";
				break;
			case(XR_FOVEATION_LEVEL_MEDIUM_HTC):
				return "XR_FOVEATION_LEVEL_MEDIUM_HTC";
				break;
			case(XR_FOVEATION_LEVEL_HIGH_HTC):
				return "XR_FOVEATION_LEVEL_HIGH_HTC";
				break;
			default:
				return "XrFoveationLevelHTC_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_HTC_foveation)  */
	#if defined(XR_HTC_passthrough)
	const char* vtostr8_XrPassthroughFormHTC(XrPassthroughFormHTC In){
		switch(In){

			case(XR_PASSTHROUGH_FORM_PLANAR_HTC):
				return "XR_PASSTHROUGH_FORM_PLANAR_HTC";
				break;
			case(XR_PASSTHROUGH_FORM_PROJECTED_HTC):
				return "XR_PASSTHROUGH_FORM_PROJECTED_HTC";
				break;
			default:
				return "XrPassthroughFormHTC_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_HTC_passthrough)  */
	#if defined(XR_KHR_android_thread_settings)
	const char* vtostr8_XrAndroidThreadTypeKHR(XrAndroidThreadTypeKHR In){
		switch(In){

			case(XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR):
				return "XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR";
				break;
			case(XR_ANDROID_THREAD_TYPE_APPLICATION_WORKER_KHR):
				return "XR_ANDROID_THREAD_TYPE_APPLICATION_WORKER_KHR";
				break;
			case(XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR):
				return "XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR";
				break;
			case(XR_ANDROID_THREAD_TYPE_RENDERER_WORKER_KHR):
				return "XR_ANDROID_THREAD_TYPE_RENDERER_WORKER_KHR";
				break;
			default:
				return "XrAndroidThreadTypeKHR_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_KHR_android_thread_settings)  */
	#if defined(XR_KHR_visibility_mask)
	const char* vtostr8_XrVisibilityMaskTypeKHR(XrVisibilityMaskTypeKHR In){
		switch(In){

			case(XR_VISIBILITY_MASK_TYPE_HIDDEN_TRIANGLE_MESH_KHR):
				return "XR_VISIBILITY_MASK_TYPE_HIDDEN_TRIANGLE_MESH_KHR";
				break;
			case(XR_VISIBILITY_MASK_TYPE_VISIBLE_TRIANGLE_MESH_KHR):
				return "XR_VISIBILITY_MASK_TYPE_VISIBLE_TRIANGLE_MESH_KHR";
				break;
			case(XR_VISIBILITY_MASK_TYPE_LINE_LOOP_KHR):
				return "XR_VISIBILITY_MASK_TYPE_LINE_LOOP_KHR";
				break;
			default:
				return "XrVisibilityMaskTypeKHR_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_KHR_visibility_mask)  */
	#if defined(XR_META_local_dimming)
	const char* vtostr8_XrLocalDimmingModeMETA(XrLocalDimmingModeMETA In){
		switch(In){

			case(XR_LOCAL_DIMMING_MODE_OFF_META):
				return "XR_LOCAL_DIMMING_MODE_OFF_META";
				break;
			case(XR_LOCAL_DIMMING_MODE_ON_META):
				return "XR_LOCAL_DIMMING_MODE_ON_META";
				break;
			default:
				return "XrLocalDimmingModeMETA_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_META_local_dimming)  */
	#if defined(XR_META_performance_metrics)
	const char* vtostr8_XrPerformanceMetricsCounterUnitMETA(XrPerformanceMetricsCounterUnitMETA In){
		switch(In){

			case(XR_PERFORMANCE_METRICS_COUNTER_UNIT_GENERIC_META):
				return "XR_PERFORMANCE_METRICS_COUNTER_UNIT_GENERIC_META";
				break;
			case(XR_PERFORMANCE_METRICS_COUNTER_UNIT_PERCENTAGE_META):
				return "XR_PERFORMANCE_METRICS_COUNTER_UNIT_PERCENTAGE_META";
				break;
			case(XR_PERFORMANCE_METRICS_COUNTER_UNIT_MILLISECONDS_META):
				return "XR_PERFORMANCE_METRICS_COUNTER_UNIT_MILLISECONDS_META";
				break;
			case(XR_PERFORMANCE_METRICS_COUNTER_UNIT_BYTES_META):
				return "XR_PERFORMANCE_METRICS_COUNTER_UNIT_BYTES_META";
				break;
			case(XR_PERFORMANCE_METRICS_COUNTER_UNIT_HERTZ_META):
				return "XR_PERFORMANCE_METRICS_COUNTER_UNIT_HERTZ_META";
				break;
			default:
				return "XrPerformanceMetricsCounterUnitMETA_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_META_performance_metrics)  */
	#if defined(XR_META_virtual_keyboard)
	const char* vtostr8_XrVirtualKeyboardLocationTypeMETA(XrVirtualKeyboardLocationTypeMETA In){
		switch(In){

			case(XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_CUSTOM_META):
				return "XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_CUSTOM_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_FAR_META):
				return "XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_FAR_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_DIRECT_META):
				return "XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_DIRECT_META";
				break;
			default:
				return "XrVirtualKeyboardLocationTypeMETA_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrVirtualKeyboardInputSourceMETA(XrVirtualKeyboardInputSourceMETA In){
		switch(In){

			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_RAY_LEFT_META):
				return "XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_RAY_LEFT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_RAY_RIGHT_META):
				return "XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_RAY_RIGHT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_RAY_LEFT_META):
				return "XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_RAY_LEFT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_RAY_RIGHT_META):
				return "XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_RAY_RIGHT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_DIRECT_LEFT_META):
				return "XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_DIRECT_LEFT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_DIRECT_RIGHT_META):
				return "XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_DIRECT_RIGHT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_DIRECT_INDEX_TIP_LEFT_META):
				return "XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_DIRECT_INDEX_TIP_LEFT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_DIRECT_INDEX_TIP_RIGHT_META):
				return "XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_DIRECT_INDEX_TIP_RIGHT_META";
				break;
			default:
				return "XrVirtualKeyboardInputSourceMETA_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_META_virtual_keyboard)  */
	#if defined(XR_ML_localization_map)
	const char* vtostr8_XrLocalizationMapStateML(XrLocalizationMapStateML In){
		switch(In){

			case(XR_LOCALIZATION_MAP_STATE_NOT_LOCALIZED_ML):
				return "XR_LOCALIZATION_MAP_STATE_NOT_LOCALIZED_ML";
				break;
			case(XR_LOCALIZATION_MAP_STATE_LOCALIZED_ML):
				return "XR_LOCALIZATION_MAP_STATE_LOCALIZED_ML";
				break;
			case(XR_LOCALIZATION_MAP_STATE_LOCALIZATION_PENDING_ML):
				return "XR_LOCALIZATION_MAP_STATE_LOCALIZATION_PENDING_ML";
				break;
			case(XR_LOCALIZATION_MAP_STATE_LOCALIZATION_SLEEPING_BEFORE_RETRY_ML):
				return "XR_LOCALIZATION_MAP_STATE_LOCALIZATION_SLEEPING_BEFORE_RETRY_ML";
				break;
			default:
				return "XrLocalizationMapStateML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrLocalizationMapTypeML(XrLocalizationMapTypeML In){
		switch(In){

			case(XR_LOCALIZATION_MAP_TYPE_ON_DEVICE_ML):
				return "XR_LOCALIZATION_MAP_TYPE_ON_DEVICE_ML";
				break;
			case(XR_LOCALIZATION_MAP_TYPE_CLOUD_ML):
				return "XR_LOCALIZATION_MAP_TYPE_CLOUD_ML";
				break;
			default:
				return "XrLocalizationMapTypeML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrLocalizationMapConfidenceML(XrLocalizationMapConfidenceML In){
		switch(In){

			case(XR_LOCALIZATION_MAP_CONFIDENCE_POOR_ML):
				return "XR_LOCALIZATION_MAP_CONFIDENCE_POOR_ML";
				break;
			case(XR_LOCALIZATION_MAP_CONFIDENCE_FAIR_ML):
				return "XR_LOCALIZATION_MAP_CONFIDENCE_FAIR_ML";
				break;
			case(XR_LOCALIZATION_MAP_CONFIDENCE_GOOD_ML):
				return "XR_LOCALIZATION_MAP_CONFIDENCE_GOOD_ML";
				break;
			case(XR_LOCALIZATION_MAP_CONFIDENCE_EXCELLENT_ML):
				return "XR_LOCALIZATION_MAP_CONFIDENCE_EXCELLENT_ML";
				break;
			default:
				return "XrLocalizationMapConfidenceML_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_ML_localization_map)  */
	#if defined(XR_ML_marker_understanding)
	const char* vtostr8_XrMarkerDetectorProfileML(XrMarkerDetectorProfileML In){
		switch(In){

			case(XR_MARKER_DETECTOR_PROFILE_DEFAULT_ML):
				return "XR_MARKER_DETECTOR_PROFILE_DEFAULT_ML";
				break;
			case(XR_MARKER_DETECTOR_PROFILE_SPEED_ML):
				return "XR_MARKER_DETECTOR_PROFILE_SPEED_ML";
				break;
			case(XR_MARKER_DETECTOR_PROFILE_ACCURACY_ML):
				return "XR_MARKER_DETECTOR_PROFILE_ACCURACY_ML";
				break;
			case(XR_MARKER_DETECTOR_PROFILE_SMALL_TARGETS_ML):
				return "XR_MARKER_DETECTOR_PROFILE_SMALL_TARGETS_ML";
				break;
			case(XR_MARKER_DETECTOR_PROFILE_LARGE_FOV_ML):
				return "XR_MARKER_DETECTOR_PROFILE_LARGE_FOV_ML";
				break;
			case(XR_MARKER_DETECTOR_PROFILE_CUSTOM_ML):
				return "XR_MARKER_DETECTOR_PROFILE_CUSTOM_ML";
				break;
			default:
				return "XrMarkerDetectorProfileML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrMarkerTypeML(XrMarkerTypeML In){
		switch(In){

			case(XR_MARKER_TYPE_ARUCO_ML):
				return "XR_MARKER_TYPE_ARUCO_ML";
				break;
			case(XR_MARKER_TYPE_APRIL_TAG_ML):
				return "XR_MARKER_TYPE_APRIL_TAG_ML";
				break;
			case(XR_MARKER_TYPE_QR_ML):
				return "XR_MARKER_TYPE_QR_ML";
				break;
			case(XR_MARKER_TYPE_EAN_13_ML):
				return "XR_MARKER_TYPE_EAN_13_ML";
				break;
			case(XR_MARKER_TYPE_UPC_A_ML):
				return "XR_MARKER_TYPE_UPC_A_ML";
				break;
			case(XR_MARKER_TYPE_CODE_128_ML):
				return "XR_MARKER_TYPE_CODE_128_ML";
				break;
			default:
				return "XrMarkerTypeML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrMarkerArucoDictML(XrMarkerArucoDictML In){
		switch(In){

			case(XR_MARKER_ARUCO_DICT_4X4_50_ML):
				return "XR_MARKER_ARUCO_DICT_4X4_50_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_4X4_100_ML):
				return "XR_MARKER_ARUCO_DICT_4X4_100_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_4X4_250_ML):
				return "XR_MARKER_ARUCO_DICT_4X4_250_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_4X4_1000_ML):
				return "XR_MARKER_ARUCO_DICT_4X4_1000_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_5X5_50_ML):
				return "XR_MARKER_ARUCO_DICT_5X5_50_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_5X5_100_ML):
				return "XR_MARKER_ARUCO_DICT_5X5_100_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_5X5_250_ML):
				return "XR_MARKER_ARUCO_DICT_5X5_250_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_5X5_1000_ML):
				return "XR_MARKER_ARUCO_DICT_5X5_1000_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_6X6_50_ML):
				return "XR_MARKER_ARUCO_DICT_6X6_50_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_6X6_100_ML):
				return "XR_MARKER_ARUCO_DICT_6X6_100_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_6X6_250_ML):
				return "XR_MARKER_ARUCO_DICT_6X6_250_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_6X6_1000_ML):
				return "XR_MARKER_ARUCO_DICT_6X6_1000_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_7X7_50_ML):
				return "XR_MARKER_ARUCO_DICT_7X7_50_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_7X7_100_ML):
				return "XR_MARKER_ARUCO_DICT_7X7_100_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_7X7_250_ML):
				return "XR_MARKER_ARUCO_DICT_7X7_250_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_7X7_1000_ML):
				return "XR_MARKER_ARUCO_DICT_7X7_1000_ML";
				break;
			default:
				return "XrMarkerArucoDictML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrMarkerAprilTagDictML(XrMarkerAprilTagDictML In){
		switch(In){

			case(XR_MARKER_APRIL_TAG_DICT_16H5_ML):
				return "XR_MARKER_APRIL_TAG_DICT_16H5_ML";
				break;
			case(XR_MARKER_APRIL_TAG_DICT_25H9_ML):
				return "XR_MARKER_APRIL_TAG_DICT_25H9_ML";
				break;
			case(XR_MARKER_APRIL_TAG_DICT_36H10_ML):
				return "XR_MARKER_APRIL_TAG_DICT_36H10_ML";
				break;
			case(XR_MARKER_APRIL_TAG_DICT_36H11_ML):
				return "XR_MARKER_APRIL_TAG_DICT_36H11_ML";
				break;
			default:
				return "XrMarkerAprilTagDictML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrMarkerDetectorFpsML(XrMarkerDetectorFpsML In){
		switch(In){

			case(XR_MARKER_DETECTOR_FPS_LOW_ML):
				return "XR_MARKER_DETECTOR_FPS_LOW_ML";
				break;
			case(XR_MARKER_DETECTOR_FPS_MEDIUM_ML):
				return "XR_MARKER_DETECTOR_FPS_MEDIUM_ML";
				break;
			case(XR_MARKER_DETECTOR_FPS_HIGH_ML):
				return "XR_MARKER_DETECTOR_FPS_HIGH_ML";
				break;
			case(XR_MARKER_DETECTOR_FPS_MAX_ML):
				return "XR_MARKER_DETECTOR_FPS_MAX_ML";
				break;
			default:
				return "XrMarkerDetectorFpsML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrMarkerDetectorResolutionML(XrMarkerDetectorResolutionML In){
		switch(In){

			case(XR_MARKER_DETECTOR_RESOLUTION_LOW_ML):
				return "XR_MARKER_DETECTOR_RESOLUTION_LOW_ML";
				break;
			case(XR_MARKER_DETECTOR_RESOLUTION_MEDIUM_ML):
				return "XR_MARKER_DETECTOR_RESOLUTION_MEDIUM_ML";
				break;
			case(XR_MARKER_DETECTOR_RESOLUTION_HIGH_ML):
				return "XR_MARKER_DETECTOR_RESOLUTION_HIGH_ML";
				break;
			default:
				return "XrMarkerDetectorResolutionML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrMarkerDetectorCameraML(XrMarkerDetectorCameraML In){
		switch(In){

			case(XR_MARKER_DETECTOR_CAMERA_RGB_CAMERA_ML):
				return "XR_MARKER_DETECTOR_CAMERA_RGB_CAMERA_ML";
				break;
			case(XR_MARKER_DETECTOR_CAMERA_WORLD_CAMERAS_ML):
				return "XR_MARKER_DETECTOR_CAMERA_WORLD_CAMERAS_ML";
				break;
			default:
				return "XrMarkerDetectorCameraML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrMarkerDetectorCornerRefineMethodML(XrMarkerDetectorCornerRefineMethodML In){
		switch(In){

			case(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_NONE_ML):
				return "XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_NONE_ML";
				break;
			case(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_SUBPIX_ML):
				return "XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_SUBPIX_ML";
				break;
			case(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_CONTOUR_ML):
				return "XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_CONTOUR_ML";
				break;
			case(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_APRIL_TAG_ML):
				return "XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_APRIL_TAG_ML";
				break;
			default:
				return "XrMarkerDetectorCornerRefineMethodML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrMarkerDetectorFullAnalysisIntervalML(XrMarkerDetectorFullAnalysisIntervalML In){
		switch(In){

			case(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MAX_ML):
				return "XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MAX_ML";
				break;
			case(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_FAST_ML):
				return "XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_FAST_ML";
				break;
			case(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MEDIUM_ML):
				return "XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MEDIUM_ML";
				break;
			case(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_SLOW_ML):
				return "XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_SLOW_ML";
				break;
			default:
				return "XrMarkerDetectorFullAnalysisIntervalML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrMarkerDetectorStatusML(XrMarkerDetectorStatusML In){
		switch(In){

			case(XR_MARKER_DETECTOR_STATUS_PENDING_ML):
				return "XR_MARKER_DETECTOR_STATUS_PENDING_ML";
				break;
			case(XR_MARKER_DETECTOR_STATUS_READY_ML):
				return "XR_MARKER_DETECTOR_STATUS_READY_ML";
				break;
			case(XR_MARKER_DETECTOR_STATUS_ERROR_ML):
				return "XR_MARKER_DETECTOR_STATUS_ERROR_ML";
				break;
			default:
				return "XrMarkerDetectorStatusML_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_ML_marker_understanding)  */
	#if defined(XR_ML_spatial_anchors)
	const char* vtostr8_XrSpatialAnchorConfidenceML(XrSpatialAnchorConfidenceML In){
		switch(In){

			case(XR_SPATIAL_ANCHOR_CONFIDENCE_LOW_ML):
				return "XR_SPATIAL_ANCHOR_CONFIDENCE_LOW_ML";
				break;
			case(XR_SPATIAL_ANCHOR_CONFIDENCE_MEDIUM_ML):
				return "XR_SPATIAL_ANCHOR_CONFIDENCE_MEDIUM_ML";
				break;
			case(XR_SPATIAL_ANCHOR_CONFIDENCE_HIGH_ML):
				return "XR_SPATIAL_ANCHOR_CONFIDENCE_HIGH_ML";
				break;
			default:
				return "XrSpatialAnchorConfidenceML_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_ML_spatial_anchors)  */
	#if defined(XR_ML_user_calibration)
	const char* vtostr8_XrHeadsetFitStatusML(XrHeadsetFitStatusML In){
		switch(In){

			case(XR_HEADSET_FIT_STATUS_UNKNOWN_ML):
				return "XR_HEADSET_FIT_STATUS_UNKNOWN_ML";
				break;
			case(XR_HEADSET_FIT_STATUS_NOT_WORN_ML):
				return "XR_HEADSET_FIT_STATUS_NOT_WORN_ML";
				break;
			case(XR_HEADSET_FIT_STATUS_GOOD_FIT_ML):
				return "XR_HEADSET_FIT_STATUS_GOOD_FIT_ML";
				break;
			case(XR_HEADSET_FIT_STATUS_BAD_FIT_ML):
				return "XR_HEADSET_FIT_STATUS_BAD_FIT_ML";
				break;
			default:
				return "XrHeadsetFitStatusML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrEyeCalibrationStatusML(XrEyeCalibrationStatusML In){
		switch(In){

			case(XR_EYE_CALIBRATION_STATUS_UNKNOWN_ML):
				return "XR_EYE_CALIBRATION_STATUS_UNKNOWN_ML";
				break;
			case(XR_EYE_CALIBRATION_STATUS_NONE_ML):
				return "XR_EYE_CALIBRATION_STATUS_NONE_ML";
				break;
			case(XR_EYE_CALIBRATION_STATUS_COARSE_ML):
				return "XR_EYE_CALIBRATION_STATUS_COARSE_ML";
				break;
			case(XR_EYE_CALIBRATION_STATUS_FINE_ML):
				return "XR_EYE_CALIBRATION_STATUS_FINE_ML";
				break;
			default:
				return "XrEyeCalibrationStatusML_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_ML_user_calibration)  */
	#if defined(XR_ML_world_mesh_detection)
	const char* vtostr8_XrWorldMeshDetectorLodML(XrWorldMeshDetectorLodML In){
		switch(In){

			case(XR_WORLD_MESH_DETECTOR_LOD_MINIMUM_ML):
				return "XR_WORLD_MESH_DETECTOR_LOD_MINIMUM_ML";
				break;
			case(XR_WORLD_MESH_DETECTOR_LOD_MEDIUM_ML):
				return "XR_WORLD_MESH_DETECTOR_LOD_MEDIUM_ML";
				break;
			case(XR_WORLD_MESH_DETECTOR_LOD_MAXIMUM_ML):
				return "XR_WORLD_MESH_DETECTOR_LOD_MAXIMUM_ML";
				break;
			default:
				return "XrWorldMeshDetectorLodML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrWorldMeshBlockStatusML(XrWorldMeshBlockStatusML In){
		switch(In){

			case(XR_WORLD_MESH_BLOCK_STATUS_NEW_ML):
				return "XR_WORLD_MESH_BLOCK_STATUS_NEW_ML";
				break;
			case(XR_WORLD_MESH_BLOCK_STATUS_UPDATED_ML):
				return "XR_WORLD_MESH_BLOCK_STATUS_UPDATED_ML";
				break;
			case(XR_WORLD_MESH_BLOCK_STATUS_DELETED_ML):
				return "XR_WORLD_MESH_BLOCK_STATUS_DELETED_ML";
				break;
			case(XR_WORLD_MESH_BLOCK_STATUS_UNCHANGED_ML):
				return "XR_WORLD_MESH_BLOCK_STATUS_UNCHANGED_ML";
				break;
			default:
				return "XrWorldMeshBlockStatusML_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrWorldMeshBlockResultML(XrWorldMeshBlockResultML In){
		switch(In){

			case(XR_WORLD_MESH_BLOCK_RESULT_SUCCESS_ML):
				return "XR_WORLD_MESH_BLOCK_RESULT_SUCCESS_ML";
				break;
			case(XR_WORLD_MESH_BLOCK_RESULT_FAILED_ML):
				return "XR_WORLD_MESH_BLOCK_RESULT_FAILED_ML";
				break;
			case(XR_WORLD_MESH_BLOCK_RESULT_PENDING_ML):
				return "XR_WORLD_MESH_BLOCK_RESULT_PENDING_ML";
				break;
			case(XR_WORLD_MESH_BLOCK_RESULT_PARTIAL_UPDATE_ML):
				return "XR_WORLD_MESH_BLOCK_RESULT_PARTIAL_UPDATE_ML";
				break;
			default:
				return "XrWorldMeshBlockResultML_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_ML_world_mesh_detection)  */
	#if defined(XR_MNDX_force_feedback_curl)
	const char* vtostr8_XrForceFeedbackCurlLocationMNDX(XrForceFeedbackCurlLocationMNDX In){
		switch(In){

			case(XR_FORCE_FEEDBACK_CURL_LOCATION_THUMB_CURL_MNDX):
				return "XR_FORCE_FEEDBACK_CURL_LOCATION_THUMB_CURL_MNDX";
				break;
			case(XR_FORCE_FEEDBACK_CURL_LOCATION_INDEX_CURL_MNDX):
				return "XR_FORCE_FEEDBACK_CURL_LOCATION_INDEX_CURL_MNDX";
				break;
			case(XR_FORCE_FEEDBACK_CURL_LOCATION_MIDDLE_CURL_MNDX):
				return "XR_FORCE_FEEDBACK_CURL_LOCATION_MIDDLE_CURL_MNDX";
				break;
			case(XR_FORCE_FEEDBACK_CURL_LOCATION_RING_CURL_MNDX):
				return "XR_FORCE_FEEDBACK_CURL_LOCATION_RING_CURL_MNDX";
				break;
			case(XR_FORCE_FEEDBACK_CURL_LOCATION_LITTLE_CURL_MNDX):
				return "XR_FORCE_FEEDBACK_CURL_LOCATION_LITTLE_CURL_MNDX";
				break;
			default:
				return "XrForceFeedbackCurlLocationMNDX_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_MNDX_force_feedback_curl)  */
	#if defined(XR_MSFT_composition_layer_reprojection)
	const char* vtostr8_XrReprojectionModeMSFT(XrReprojectionModeMSFT In){
		switch(In){

			case(XR_REPROJECTION_MODE_DEPTH_MSFT):
				return "XR_REPROJECTION_MODE_DEPTH_MSFT";
				break;
			case(XR_REPROJECTION_MODE_PLANAR_FROM_DEPTH_MSFT):
				return "XR_REPROJECTION_MODE_PLANAR_FROM_DEPTH_MSFT";
				break;
			case(XR_REPROJECTION_MODE_PLANAR_MANUAL_MSFT):
				return "XR_REPROJECTION_MODE_PLANAR_MANUAL_MSFT";
				break;
			case(XR_REPROJECTION_MODE_ORIENTATION_ONLY_MSFT):
				return "XR_REPROJECTION_MODE_ORIENTATION_ONLY_MSFT";
				break;
			default:
				return "XrReprojectionModeMSFT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_MSFT_composition_layer_reprojection)  */
	#if defined(XR_MSFT_hand_tracking_mesh)
	const char* vtostr8_XrHandPoseTypeMSFT(XrHandPoseTypeMSFT In){
		switch(In){

			case(XR_HAND_POSE_TYPE_TRACKED_MSFT):
				return "XR_HAND_POSE_TYPE_TRACKED_MSFT";
				break;
			case(XR_HAND_POSE_TYPE_REFERENCE_OPEN_PALM_MSFT):
				return "XR_HAND_POSE_TYPE_REFERENCE_OPEN_PALM_MSFT";
				break;
			default:
				return "XrHandPoseTypeMSFT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_MSFT_hand_tracking_mesh)  */
	#if defined(XR_MSFT_scene_marker)
	const char* vtostr8_XrSceneMarkerTypeMSFT(XrSceneMarkerTypeMSFT In){
		switch(In){

			case(XR_SCENE_MARKER_TYPE_QR_CODE_MSFT):
				return "XR_SCENE_MARKER_TYPE_QR_CODE_MSFT";
				break;
			default:
				return "XrSceneMarkerTypeMSFT_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrSceneMarkerQRCodeSymbolTypeMSFT(XrSceneMarkerQRCodeSymbolTypeMSFT In){
		switch(In){

			case(XR_SCENE_MARKER_QR_CODE_SYMBOL_TYPE_QR_CODE_MSFT):
				return "XR_SCENE_MARKER_QR_CODE_SYMBOL_TYPE_QR_CODE_MSFT";
				break;
			case(XR_SCENE_MARKER_QR_CODE_SYMBOL_TYPE_MICRO_QR_CODE_MSFT):
				return "XR_SCENE_MARKER_QR_CODE_SYMBOL_TYPE_MICRO_QR_CODE_MSFT";
				break;
			default:
				return "XrSceneMarkerQRCodeSymbolTypeMSFT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_MSFT_scene_marker)  */
	#if defined(XR_MSFT_scene_understanding)
	const char* vtostr8_XrSceneObjectTypeMSFT(XrSceneObjectTypeMSFT In){
		switch(In){

			case(XR_SCENE_OBJECT_TYPE_UNCATEGORIZED_MSFT):
				return "XR_SCENE_OBJECT_TYPE_UNCATEGORIZED_MSFT";
				break;
			case(XR_SCENE_OBJECT_TYPE_BACKGROUND_MSFT):
				return "XR_SCENE_OBJECT_TYPE_BACKGROUND_MSFT";
				break;
			case(XR_SCENE_OBJECT_TYPE_WALL_MSFT):
				return "XR_SCENE_OBJECT_TYPE_WALL_MSFT";
				break;
			case(XR_SCENE_OBJECT_TYPE_FLOOR_MSFT):
				return "XR_SCENE_OBJECT_TYPE_FLOOR_MSFT";
				break;
			case(XR_SCENE_OBJECT_TYPE_CEILING_MSFT):
				return "XR_SCENE_OBJECT_TYPE_CEILING_MSFT";
				break;
			case(XR_SCENE_OBJECT_TYPE_PLATFORM_MSFT):
				return "XR_SCENE_OBJECT_TYPE_PLATFORM_MSFT";
				break;
			case(XR_SCENE_OBJECT_TYPE_INFERRED_MSFT):
				return "XR_SCENE_OBJECT_TYPE_INFERRED_MSFT";
				break;
			default:
				return "XrSceneObjectTypeMSFT_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrScenePlaneAlignmentTypeMSFT(XrScenePlaneAlignmentTypeMSFT In){
		switch(In){

			case(XR_SCENE_PLANE_ALIGNMENT_TYPE_NON_ORTHOGONAL_MSFT):
				return "XR_SCENE_PLANE_ALIGNMENT_TYPE_NON_ORTHOGONAL_MSFT";
				break;
			case(XR_SCENE_PLANE_ALIGNMENT_TYPE_HORIZONTAL_MSFT):
				return "XR_SCENE_PLANE_ALIGNMENT_TYPE_HORIZONTAL_MSFT";
				break;
			case(XR_SCENE_PLANE_ALIGNMENT_TYPE_VERTICAL_MSFT):
				return "XR_SCENE_PLANE_ALIGNMENT_TYPE_VERTICAL_MSFT";
				break;
			default:
				return "XrScenePlaneAlignmentTypeMSFT_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrSceneComputeStateMSFT(XrSceneComputeStateMSFT In){
		switch(In){

			case(XR_SCENE_COMPUTE_STATE_NONE_MSFT):
				return "XR_SCENE_COMPUTE_STATE_NONE_MSFT";
				break;
			case(XR_SCENE_COMPUTE_STATE_UPDATING_MSFT):
				return "XR_SCENE_COMPUTE_STATE_UPDATING_MSFT";
				break;
			case(XR_SCENE_COMPUTE_STATE_COMPLETED_MSFT):
				return "XR_SCENE_COMPUTE_STATE_COMPLETED_MSFT";
				break;
			case(XR_SCENE_COMPUTE_STATE_COMPLETED_WITH_ERROR_MSFT):
				return "XR_SCENE_COMPUTE_STATE_COMPLETED_WITH_ERROR_MSFT";
				break;
			default:
				return "XrSceneComputeStateMSFT_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrSceneComputeConsistencyMSFT(XrSceneComputeConsistencyMSFT In){
		switch(In){

			case(XR_SCENE_COMPUTE_CONSISTENCY_SNAPSHOT_COMPLETE_MSFT):
				return "XR_SCENE_COMPUTE_CONSISTENCY_SNAPSHOT_COMPLETE_MSFT";
				break;
			case(XR_SCENE_COMPUTE_CONSISTENCY_SNAPSHOT_INCOMPLETE_FAST_MSFT):
				return "XR_SCENE_COMPUTE_CONSISTENCY_SNAPSHOT_INCOMPLETE_FAST_MSFT";
				break;
			case(XR_SCENE_COMPUTE_CONSISTENCY_OCCLUSION_OPTIMIZED_MSFT):
				return "XR_SCENE_COMPUTE_CONSISTENCY_OCCLUSION_OPTIMIZED_MSFT";
				break;
			default:
				return "XrSceneComputeConsistencyMSFT_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrMeshComputeLodMSFT(XrMeshComputeLodMSFT In){
		switch(In){

			case(XR_MESH_COMPUTE_LOD_COARSE_MSFT):
				return "XR_MESH_COMPUTE_LOD_COARSE_MSFT";
				break;
			case(XR_MESH_COMPUTE_LOD_MEDIUM_MSFT):
				return "XR_MESH_COMPUTE_LOD_MEDIUM_MSFT";
				break;
			case(XR_MESH_COMPUTE_LOD_FINE_MSFT):
				return "XR_MESH_COMPUTE_LOD_FINE_MSFT";
				break;
			case(XR_MESH_COMPUTE_LOD_UNLIMITED_MSFT):
				return "XR_MESH_COMPUTE_LOD_UNLIMITED_MSFT";
				break;
			default:
				return "XrMeshComputeLodMSFT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_MSFT_scene_understanding)  */
	#if defined(XR_MSFT_spatial_graph_bridge)
	const char* vtostr8_XrSpatialGraphNodeTypeMSFT(XrSpatialGraphNodeTypeMSFT In){
		switch(In){

			case(XR_SPATIAL_GRAPH_NODE_TYPE_STATIC_MSFT):
				return "XR_SPATIAL_GRAPH_NODE_TYPE_STATIC_MSFT";
				break;
			case(XR_SPATIAL_GRAPH_NODE_TYPE_DYNAMIC_MSFT):
				return "XR_SPATIAL_GRAPH_NODE_TYPE_DYNAMIC_MSFT";
				break;
			default:
				return "XrSpatialGraphNodeTypeMSFT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_MSFT_spatial_graph_bridge)  */
	#if defined(XR_OCULUS_external_camera)
	const char* vtostr8_XrExternalCameraAttachedToDeviceOCULUS(XrExternalCameraAttachedToDeviceOCULUS In){
		switch(In){

			case(XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_NONE_OCULUS):
				return "XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_NONE_OCULUS";
				break;
			case(XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_HMD_OCULUS):
				return "XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_HMD_OCULUS";
				break;
			case(XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_LTOUCH_OCULUS):
				return "XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_LTOUCH_OCULUS";
				break;
			case(XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_RTOUCH_OCULUS):
				return "XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_RTOUCH_OCULUS";
				break;
			default:
				return "XrExternalCameraAttachedToDeviceOCULUS_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_OCULUS_external_camera)  */
	#if defined(XR_QCOM_tracking_optimization_settings)
	const char* vtostr8_XrTrackingOptimizationSettingsDomainQCOM(XrTrackingOptimizationSettingsDomainQCOM In){
		switch(In){

			case(XR_TRACKING_OPTIMIZATION_SETTINGS_DOMAIN_ALL_QCOM):
				return "XR_TRACKING_OPTIMIZATION_SETTINGS_DOMAIN_ALL_QCOM";
				break;
			default:
				return "XrTrackingOptimizationSettingsDomainQCOM_TOSTR_ERROR";

		}

	}

	const char* vtostr8_XrTrackingOptimizationSettingsHintQCOM(XrTrackingOptimizationSettingsHintQCOM In){
		switch(In){

			case(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_NONE_QCOM):
				return "XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_NONE_QCOM";
				break;
			case(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_LONG_RANGE_PRIORIZATION_QCOM):
				return "XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_LONG_RANGE_PRIORIZATION_QCOM";
				break;
			case(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_CLOSE_RANGE_PRIORIZATION_QCOM):
				return "XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_CLOSE_RANGE_PRIORIZATION_QCOM";
				break;
			case(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_LOW_POWER_PRIORIZATION_QCOM):
				return "XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_LOW_POWER_PRIORIZATION_QCOM";
				break;
			case(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_HIGH_POWER_PRIORIZATION_QCOM):
				return "XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_HIGH_POWER_PRIORIZATION_QCOM";
				break;
			default:
				return "XrTrackingOptimizationSettingsHintQCOM_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_QCOM_tracking_optimization_settings)  */
	#if defined(XR_ULTRALEAP_hand_tracking_forearm)
	const char* vtostr8_XrHandForearmJointULTRALEAP(XrHandForearmJointULTRALEAP In){
		switch(In){

			case(XR_HAND_FOREARM_JOINT_PALM_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_PALM_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_WRIST_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_WRIST_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_THUMB_METACARPAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_THUMB_METACARPAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_THUMB_PROXIMAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_THUMB_PROXIMAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_THUMB_DISTAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_THUMB_DISTAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_THUMB_TIP_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_THUMB_TIP_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_INDEX_METACARPAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_INDEX_METACARPAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_INDEX_PROXIMAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_INDEX_PROXIMAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_INDEX_INTERMEDIATE_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_INDEX_INTERMEDIATE_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_INDEX_DISTAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_INDEX_DISTAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_INDEX_TIP_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_INDEX_TIP_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_MIDDLE_METACARPAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_MIDDLE_METACARPAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_MIDDLE_PROXIMAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_MIDDLE_PROXIMAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_MIDDLE_INTERMEDIATE_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_MIDDLE_INTERMEDIATE_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_MIDDLE_DISTAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_MIDDLE_DISTAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_MIDDLE_TIP_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_MIDDLE_TIP_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_RING_METACARPAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_RING_METACARPAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_RING_PROXIMAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_RING_PROXIMAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_RING_INTERMEDIATE_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_RING_INTERMEDIATE_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_RING_DISTAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_RING_DISTAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_RING_TIP_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_RING_TIP_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_LITTLE_METACARPAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_LITTLE_METACARPAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_LITTLE_PROXIMAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_LITTLE_PROXIMAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_LITTLE_INTERMEDIATE_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_LITTLE_INTERMEDIATE_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_LITTLE_DISTAL_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_LITTLE_DISTAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_LITTLE_TIP_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_LITTLE_TIP_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_ELBOW_ULTRALEAP):
				return "XR_HAND_FOREARM_JOINT_ELBOW_ULTRALEAP";
				break;
			default:
				return "XrHandForearmJointULTRALEAP_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_ULTRALEAP_hand_tracking_forearm)  */

	//SECTION(V): XRMYTH_TOSTR32_IMPL
	#if defined(XR_EXT_future)
	const vchar* vtostr32_XrFutureStateEXT(XrFutureStateEXT In){
		switch(In){

			case(XR_FUTURE_STATE_PENDING_EXT):
				return U"XR_FUTURE_STATE_PENDING_EXT";
				break;
			case(XR_FUTURE_STATE_READY_EXT):
				return U"XR_FUTURE_STATE_READY_EXT";
				break;
			default:
				return U"XrFutureStateEXT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_EXT_future)  */
	#if defined(XR_EXT_hand_joints_motion_range)
	const vchar* vtostr32_XrHandJointsMotionRangeEXT(XrHandJointsMotionRangeEXT In){
		switch(In){

			case(XR_HAND_JOINTS_MOTION_RANGE_UNOBSTRUCTED_EXT):
				return U"XR_HAND_JOINTS_MOTION_RANGE_UNOBSTRUCTED_EXT";
				break;
			case(XR_HAND_JOINTS_MOTION_RANGE_CONFORMING_TO_CONTROLLER_EXT):
				return U"XR_HAND_JOINTS_MOTION_RANGE_CONFORMING_TO_CONTROLLER_EXT";
				break;
			default:
				return U"XrHandJointsMotionRangeEXT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_EXT_hand_joints_motion_range)  */
	#if defined(XR_EXT_hand_tracking)
	const vchar* vtostr32_XrHandEXT(XrHandEXT In){
		switch(In){

			case(XR_HAND_LEFT_EXT):
				return U"XR_HAND_LEFT_EXT";
				break;
			case(XR_HAND_RIGHT_EXT):
				return U"XR_HAND_RIGHT_EXT";
				break;
			default:
				return U"XrHandEXT_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrHandJointEXT(XrHandJointEXT In){
		switch(In){

			case(XR_HAND_JOINT_PALM_EXT):
				return U"XR_HAND_JOINT_PALM_EXT";
				break;
			case(XR_HAND_JOINT_WRIST_EXT):
				return U"XR_HAND_JOINT_WRIST_EXT";
				break;
			case(XR_HAND_JOINT_THUMB_METACARPAL_EXT):
				return U"XR_HAND_JOINT_THUMB_METACARPAL_EXT";
				break;
			case(XR_HAND_JOINT_THUMB_PROXIMAL_EXT):
				return U"XR_HAND_JOINT_THUMB_PROXIMAL_EXT";
				break;
			case(XR_HAND_JOINT_THUMB_DISTAL_EXT):
				return U"XR_HAND_JOINT_THUMB_DISTAL_EXT";
				break;
			case(XR_HAND_JOINT_THUMB_TIP_EXT):
				return U"XR_HAND_JOINT_THUMB_TIP_EXT";
				break;
			case(XR_HAND_JOINT_INDEX_METACARPAL_EXT):
				return U"XR_HAND_JOINT_INDEX_METACARPAL_EXT";
				break;
			case(XR_HAND_JOINT_INDEX_PROXIMAL_EXT):
				return U"XR_HAND_JOINT_INDEX_PROXIMAL_EXT";
				break;
			case(XR_HAND_JOINT_INDEX_INTERMEDIATE_EXT):
				return U"XR_HAND_JOINT_INDEX_INTERMEDIATE_EXT";
				break;
			case(XR_HAND_JOINT_INDEX_DISTAL_EXT):
				return U"XR_HAND_JOINT_INDEX_DISTAL_EXT";
				break;
			case(XR_HAND_JOINT_INDEX_TIP_EXT):
				return U"XR_HAND_JOINT_INDEX_TIP_EXT";
				break;
			case(XR_HAND_JOINT_MIDDLE_METACARPAL_EXT):
				return U"XR_HAND_JOINT_MIDDLE_METACARPAL_EXT";
				break;
			case(XR_HAND_JOINT_MIDDLE_PROXIMAL_EXT):
				return U"XR_HAND_JOINT_MIDDLE_PROXIMAL_EXT";
				break;
			case(XR_HAND_JOINT_MIDDLE_INTERMEDIATE_EXT):
				return U"XR_HAND_JOINT_MIDDLE_INTERMEDIATE_EXT";
				break;
			case(XR_HAND_JOINT_MIDDLE_DISTAL_EXT):
				return U"XR_HAND_JOINT_MIDDLE_DISTAL_EXT";
				break;
			case(XR_HAND_JOINT_MIDDLE_TIP_EXT):
				return U"XR_HAND_JOINT_MIDDLE_TIP_EXT";
				break;
			case(XR_HAND_JOINT_RING_METACARPAL_EXT):
				return U"XR_HAND_JOINT_RING_METACARPAL_EXT";
				break;
			case(XR_HAND_JOINT_RING_PROXIMAL_EXT):
				return U"XR_HAND_JOINT_RING_PROXIMAL_EXT";
				break;
			case(XR_HAND_JOINT_RING_INTERMEDIATE_EXT):
				return U"XR_HAND_JOINT_RING_INTERMEDIATE_EXT";
				break;
			case(XR_HAND_JOINT_RING_DISTAL_EXT):
				return U"XR_HAND_JOINT_RING_DISTAL_EXT";
				break;
			case(XR_HAND_JOINT_RING_TIP_EXT):
				return U"XR_HAND_JOINT_RING_TIP_EXT";
				break;
			case(XR_HAND_JOINT_LITTLE_METACARPAL_EXT):
				return U"XR_HAND_JOINT_LITTLE_METACARPAL_EXT";
				break;
			case(XR_HAND_JOINT_LITTLE_PROXIMAL_EXT):
				return U"XR_HAND_JOINT_LITTLE_PROXIMAL_EXT";
				break;
			case(XR_HAND_JOINT_LITTLE_INTERMEDIATE_EXT):
				return U"XR_HAND_JOINT_LITTLE_INTERMEDIATE_EXT";
				break;
			case(XR_HAND_JOINT_LITTLE_DISTAL_EXT):
				return U"XR_HAND_JOINT_LITTLE_DISTAL_EXT";
				break;
			case(XR_HAND_JOINT_LITTLE_TIP_EXT):
				return U"XR_HAND_JOINT_LITTLE_TIP_EXT";
				break;
			default:
				return U"XrHandJointEXT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_EXT_hand_tracking)  */
	#if defined(XR_EXT_hand_tracking_data_source)
	const vchar* vtostr32_XrHandTrackingDataSourceEXT(XrHandTrackingDataSourceEXT In){
		switch(In){

			case(XR_HAND_TRACKING_DATA_SOURCE_UNOBSTRUCTED_EXT):
				return U"XR_HAND_TRACKING_DATA_SOURCE_UNOBSTRUCTED_EXT";
				break;
			case(XR_HAND_TRACKING_DATA_SOURCE_CONTROLLER_EXT):
				return U"XR_HAND_TRACKING_DATA_SOURCE_CONTROLLER_EXT";
				break;
			default:
				return U"XrHandTrackingDataSourceEXT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_EXT_hand_tracking_data_source)  */
	#if defined(XR_EXT_performance_settings)
	/*
		const vchar* vtostr32_XrPerfSettingsDomainEXT(XrPerfSettingsDomainEXT In){
		switch(In){

		case(XR_PERF_SETTINGS_DOMAIN_CPU_EXT):
        return U"XR_PERF_SETTINGS_DOMAIN_CPU_EXT";
        break;
		case(XR_PERF_SETTINGS_DOMAIN_GPU_EXT):
        return U"XR_PERF_SETTINGS_DOMAIN_GPU_EXT";
        break;
		default:
        return U"XrPerfSettingsDomainEXT_TOSTR_ERROR";

		}

		}*/

	const vchar* vtostr32_XrPerfSettingsSubDomainEXT(XrPerfSettingsSubDomainEXT In){
		switch(In){

			case(XR_PERF_SETTINGS_SUB_DOMAIN_COMPOSITING_EXT):
				return U"XR_PERF_SETTINGS_SUB_DOMAIN_COMPOSITING_EXT";
				break;
			case(XR_PERF_SETTINGS_SUB_DOMAIN_RENDERING_EXT):
				return U"XR_PERF_SETTINGS_SUB_DOMAIN_RENDERING_EXT";
				break;
			case(XR_PERF_SETTINGS_SUB_DOMAIN_THERMAL_EXT):
				return U"XR_PERF_SETTINGS_SUB_DOMAIN_THERMAL_EXT";
				break;
			default:
				return U"XrPerfSettingsSubDomainEXT_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrPerfSettingsLevelEXT(XrPerfSettingsLevelEXT In){
		switch(In){

			case(XR_PERF_SETTINGS_LEVEL_POWER_SAVINGS_EXT):
				return U"XR_PERF_SETTINGS_LEVEL_POWER_SAVINGS_EXT";
				break;
			case(XR_PERF_SETTINGS_LEVEL_SUSTAINED_LOW_EXT):
				return U"XR_PERF_SETTINGS_LEVEL_SUSTAINED_LOW_EXT";
				break;
			case(XR_PERF_SETTINGS_LEVEL_SUSTAINED_HIGH_EXT):
				return U"XR_PERF_SETTINGS_LEVEL_SUSTAINED_HIGH_EXT";
				break;
			case(XR_PERF_SETTINGS_LEVEL_BOOST_EXT):
				return U"XR_PERF_SETTINGS_LEVEL_BOOST_EXT";
				break;
			default:
				return U"XrPerfSettingsLevelEXT_TOSTR_ERROR";

		}

	}
	/*
		const vchar* vtostr32_XrPerfSettingsNotificationLevelEXT(XrPerfSettingsNotificationLevelEXT In){
		switch(In){

		case(XR_PERF_SETTINGS_NOTIF_LEVEL_NORMAL_EXT):
        return U"XR_PERF_SETTINGS_NOTIF_LEVEL_NORMAL_EXT";
        break;
		case(XR_PERF_SETTINGS_NOTIF_LEVEL_WARNING_EXT):
        return U"XR_PERF_SETTINGS_NOTIF_LEVEL_WARNING_EXT";
        break;
		case(XR_PERF_SETTINGS_NOTIF_LEVEL_IMPAIRED_EXT):
        return U"XR_PERF_SETTINGS_NOTIF_LEVEL_IMPAIRED_EXT";
        break;
		default:
        return U"XrPerfSettingsNotificationLevelEXT_TOSTR_ERROR";

		}

		}*/

	#endif /*  defined(XR_EXT_performance_settings)  */
	#if defined(XR_EXT_plane_detection)
	const vchar* vtostr32_XrPlaneDetectionStateEXT(XrPlaneDetectionStateEXT In){
		switch(In){

			case(XR_PLANE_DETECTION_STATE_NONE_EXT):
				return U"XR_PLANE_DETECTION_STATE_NONE_EXT";
				break;
			case(XR_PLANE_DETECTION_STATE_PENDING_EXT):
				return U"XR_PLANE_DETECTION_STATE_PENDING_EXT";
				break;
			case(XR_PLANE_DETECTION_STATE_DONE_EXT):
				return U"XR_PLANE_DETECTION_STATE_DONE_EXT";
				break;
			case(XR_PLANE_DETECTION_STATE_ERROR_EXT):
				return U"XR_PLANE_DETECTION_STATE_ERROR_EXT";
				break;
			case(XR_PLANE_DETECTION_STATE_FATAL_EXT):
				return U"XR_PLANE_DETECTION_STATE_FATAL_EXT";
				break;
			default:
				return U"XrPlaneDetectionStateEXT_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrPlaneDetectorSemanticTypeEXT(XrPlaneDetectorSemanticTypeEXT In){
		switch(In){

			case(XR_PLANE_DETECTOR_SEMANTIC_TYPE_UNDEFINED_EXT):
				return U"XR_PLANE_DETECTOR_SEMANTIC_TYPE_UNDEFINED_EXT";
				break;
			case(XR_PLANE_DETECTOR_SEMANTIC_TYPE_CEILING_EXT):
				return U"XR_PLANE_DETECTOR_SEMANTIC_TYPE_CEILING_EXT";
				break;
			case(XR_PLANE_DETECTOR_SEMANTIC_TYPE_FLOOR_EXT):
				return U"XR_PLANE_DETECTOR_SEMANTIC_TYPE_FLOOR_EXT";
				break;
			case(XR_PLANE_DETECTOR_SEMANTIC_TYPE_WALL_EXT):
				return U"XR_PLANE_DETECTOR_SEMANTIC_TYPE_WALL_EXT";
				break;
			case(XR_PLANE_DETECTOR_SEMANTIC_TYPE_PLATFORM_EXT):
				return U"XR_PLANE_DETECTOR_SEMANTIC_TYPE_PLATFORM_EXT";
				break;
			default:
				return U"XrPlaneDetectorSemanticTypeEXT_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrPlaneDetectorOrientationEXT(XrPlaneDetectorOrientationEXT In){
		switch(In){

			case(XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_UPWARD_EXT):
				return U"XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_UPWARD_EXT";
				break;
			case(XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_DOWNWARD_EXT):
				return U"XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_DOWNWARD_EXT";
				break;
			case(XR_PLANE_DETECTOR_ORIENTATION_VERTICAL_EXT):
				return U"XR_PLANE_DETECTOR_ORIENTATION_VERTICAL_EXT";
				break;
			case(XR_PLANE_DETECTOR_ORIENTATION_ARBITRARY_EXT):
				return U"XR_PLANE_DETECTOR_ORIENTATION_ARBITRARY_EXT";
				break;
			default:
				return U"XrPlaneDetectorOrientationEXT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_EXT_plane_detection)  */
	#if defined(XR_EXT_thermal_query)
	const vchar* vtostr32_XrPerfSettingsDomainEXT(XrPerfSettingsDomainEXT In){
		switch(In){

			case(XR_PERF_SETTINGS_DOMAIN_CPU_EXT):
				return U"XR_PERF_SETTINGS_DOMAIN_CPU_EXT";
				break;
			case(XR_PERF_SETTINGS_DOMAIN_GPU_EXT):
				return U"XR_PERF_SETTINGS_DOMAIN_GPU_EXT";
				break;
			default:
				return U"XrPerfSettingsDomainEXT_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrPerfSettingsNotificationLevelEXT(XrPerfSettingsNotificationLevelEXT In){
		switch(In){

			case(XR_PERF_SETTINGS_NOTIF_LEVEL_NORMAL_EXT):
				return U"XR_PERF_SETTINGS_NOTIF_LEVEL_NORMAL_EXT";
				break;
			case(XR_PERF_SETTINGS_NOTIF_LEVEL_WARNING_EXT):
				return U"XR_PERF_SETTINGS_NOTIF_LEVEL_WARNING_EXT";
				break;
			case(XR_PERF_SETTINGS_NOTIF_LEVEL_IMPAIRED_EXT):
				return U"XR_PERF_SETTINGS_NOTIF_LEVEL_IMPAIRED_EXT";
				break;
			default:
				return U"XrPerfSettingsNotificationLevelEXT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_EXT_thermal_query)  */
	#if defined(XR_FB_body_tracking)
	const vchar* vtostr32_XrBodyJointFB(XrBodyJointFB In){
		switch(In){

			case(XR_BODY_JOINT_ROOT_FB):
				return U"XR_BODY_JOINT_ROOT_FB";
				break;
			case(XR_BODY_JOINT_HIPS_FB):
				return U"XR_BODY_JOINT_HIPS_FB";
				break;
			case(XR_BODY_JOINT_SPINE_LOWER_FB):
				return U"XR_BODY_JOINT_SPINE_LOWER_FB";
				break;
			case(XR_BODY_JOINT_SPINE_MIDDLE_FB):
				return U"XR_BODY_JOINT_SPINE_MIDDLE_FB";
				break;
			case(XR_BODY_JOINT_SPINE_UPPER_FB):
				return U"XR_BODY_JOINT_SPINE_UPPER_FB";
				break;
			case(XR_BODY_JOINT_CHEST_FB):
				return U"XR_BODY_JOINT_CHEST_FB";
				break;
			case(XR_BODY_JOINT_NECK_FB):
				return U"XR_BODY_JOINT_NECK_FB";
				break;
			case(XR_BODY_JOINT_HEAD_FB):
				return U"XR_BODY_JOINT_HEAD_FB";
				break;
			case(XR_BODY_JOINT_LEFT_SHOULDER_FB):
				return U"XR_BODY_JOINT_LEFT_SHOULDER_FB";
				break;
			case(XR_BODY_JOINT_LEFT_SCAPULA_FB):
				return U"XR_BODY_JOINT_LEFT_SCAPULA_FB";
				break;
			case(XR_BODY_JOINT_LEFT_ARM_UPPER_FB):
				return U"XR_BODY_JOINT_LEFT_ARM_UPPER_FB";
				break;
			case(XR_BODY_JOINT_LEFT_ARM_LOWER_FB):
				return U"XR_BODY_JOINT_LEFT_ARM_LOWER_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_WRIST_TWIST_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_WRIST_TWIST_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_SHOULDER_FB):
				return U"XR_BODY_JOINT_RIGHT_SHOULDER_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_SCAPULA_FB):
				return U"XR_BODY_JOINT_RIGHT_SCAPULA_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_ARM_UPPER_FB):
				return U"XR_BODY_JOINT_RIGHT_ARM_UPPER_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_ARM_LOWER_FB):
				return U"XR_BODY_JOINT_RIGHT_ARM_LOWER_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_WRIST_TWIST_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_WRIST_TWIST_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_PALM_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_PALM_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_WRIST_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_WRIST_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_THUMB_METACARPAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_THUMB_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_THUMB_PROXIMAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_THUMB_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_THUMB_DISTAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_THUMB_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_THUMB_TIP_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_THUMB_TIP_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_INDEX_METACARPAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_INDEX_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_INDEX_PROXIMAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_INDEX_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_INDEX_INTERMEDIATE_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_INDEX_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_INDEX_DISTAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_INDEX_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_INDEX_TIP_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_INDEX_TIP_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_METACARPAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_MIDDLE_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_PROXIMAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_MIDDLE_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_INTERMEDIATE_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_MIDDLE_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_DISTAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_MIDDLE_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_TIP_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_MIDDLE_TIP_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_RING_METACARPAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_RING_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_RING_PROXIMAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_RING_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_RING_INTERMEDIATE_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_RING_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_RING_DISTAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_RING_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_RING_TIP_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_RING_TIP_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_LITTLE_METACARPAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_LITTLE_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_LITTLE_PROXIMAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_LITTLE_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_LITTLE_INTERMEDIATE_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_LITTLE_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_LITTLE_DISTAL_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_LITTLE_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_LEFT_HAND_LITTLE_TIP_FB):
				return U"XR_BODY_JOINT_LEFT_HAND_LITTLE_TIP_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_PALM_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_PALM_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_WRIST_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_WRIST_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_THUMB_METACARPAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_THUMB_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_THUMB_PROXIMAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_THUMB_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_THUMB_DISTAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_THUMB_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_THUMB_TIP_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_THUMB_TIP_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_INDEX_METACARPAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_INDEX_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_INDEX_PROXIMAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_INDEX_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_INDEX_INTERMEDIATE_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_INDEX_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_INDEX_DISTAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_INDEX_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_INDEX_TIP_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_INDEX_TIP_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_METACARPAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_MIDDLE_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_PROXIMAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_MIDDLE_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_INTERMEDIATE_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_MIDDLE_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_DISTAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_MIDDLE_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_TIP_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_MIDDLE_TIP_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_RING_METACARPAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_RING_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_RING_PROXIMAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_RING_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_RING_INTERMEDIATE_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_RING_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_RING_DISTAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_RING_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_RING_TIP_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_RING_TIP_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_METACARPAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_LITTLE_METACARPAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_PROXIMAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_LITTLE_PROXIMAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_INTERMEDIATE_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_LITTLE_INTERMEDIATE_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_DISTAL_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_LITTLE_DISTAL_FB";
				break;
			case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_TIP_FB):
				return U"XR_BODY_JOINT_RIGHT_HAND_LITTLE_TIP_FB";
				break;
			case(XR_BODY_JOINT_COUNT_FB):
				return U"XR_BODY_JOINT_COUNT_FB";
				break;
			case(XR_BODY_JOINT_NONE_FB):
				return U"XR_BODY_JOINT_NONE_FB";
				break;
			default:
				return U"XrBodyJointFB_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrBodyJointSetFB(XrBodyJointSetFB In){
		switch(In){

			case(XR_BODY_JOINT_SET_DEFAULT_FB):
				return U"XR_BODY_JOINT_SET_DEFAULT_FB";
				break;
			default:
				return U"XrBodyJointSetFB_TOSTR_ERROR";

		}

	}
	/*
		const vchar* vtostr32_XrBodyJointFB(XrBodyJointFB In){
		switch(In){

		case(XR_BODY_JOINT_ROOT_FB):
        return U"XR_BODY_JOINT_ROOT_FB";
        break;
		case(XR_BODY_JOINT_HIPS_FB):
        return U"XR_BODY_JOINT_HIPS_FB";
        break;
		case(XR_BODY_JOINT_SPINE_LOWER_FB):
        return U"XR_BODY_JOINT_SPINE_LOWER_FB";
        break;
		case(XR_BODY_JOINT_SPINE_MIDDLE_FB):
        return U"XR_BODY_JOINT_SPINE_MIDDLE_FB";
        break;
		case(XR_BODY_JOINT_SPINE_UPPER_FB):
        return U"XR_BODY_JOINT_SPINE_UPPER_FB";
        break;
		case(XR_BODY_JOINT_CHEST_FB):
        return U"XR_BODY_JOINT_CHEST_FB";
        break;
		case(XR_BODY_JOINT_NECK_FB):
        return U"XR_BODY_JOINT_NECK_FB";
        break;
		case(XR_BODY_JOINT_HEAD_FB):
        return U"XR_BODY_JOINT_HEAD_FB";
        break;
		case(XR_BODY_JOINT_LEFT_SHOULDER_FB):
        return U"XR_BODY_JOINT_LEFT_SHOULDER_FB";
        break;
		case(XR_BODY_JOINT_LEFT_SCAPULA_FB):
        return U"XR_BODY_JOINT_LEFT_SCAPULA_FB";
        break;
		case(XR_BODY_JOINT_LEFT_ARM_UPPER_FB):
        return U"XR_BODY_JOINT_LEFT_ARM_UPPER_FB";
        break;
		case(XR_BODY_JOINT_LEFT_ARM_LOWER_FB):
        return U"XR_BODY_JOINT_LEFT_ARM_LOWER_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_WRIST_TWIST_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_WRIST_TWIST_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_SHOULDER_FB):
        return U"XR_BODY_JOINT_RIGHT_SHOULDER_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_SCAPULA_FB):
        return U"XR_BODY_JOINT_RIGHT_SCAPULA_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_ARM_UPPER_FB):
        return U"XR_BODY_JOINT_RIGHT_ARM_UPPER_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_ARM_LOWER_FB):
        return U"XR_BODY_JOINT_RIGHT_ARM_LOWER_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_WRIST_TWIST_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_WRIST_TWIST_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_PALM_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_PALM_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_WRIST_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_WRIST_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_THUMB_METACARPAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_THUMB_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_THUMB_PROXIMAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_THUMB_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_THUMB_DISTAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_THUMB_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_THUMB_TIP_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_THUMB_TIP_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_INDEX_METACARPAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_INDEX_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_INDEX_PROXIMAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_INDEX_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_INDEX_INTERMEDIATE_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_INDEX_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_INDEX_DISTAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_INDEX_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_INDEX_TIP_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_INDEX_TIP_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_METACARPAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_MIDDLE_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_PROXIMAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_MIDDLE_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_INTERMEDIATE_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_MIDDLE_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_DISTAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_MIDDLE_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_MIDDLE_TIP_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_MIDDLE_TIP_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_RING_METACARPAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_RING_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_RING_PROXIMAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_RING_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_RING_INTERMEDIATE_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_RING_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_RING_DISTAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_RING_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_RING_TIP_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_RING_TIP_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_LITTLE_METACARPAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_LITTLE_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_LITTLE_PROXIMAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_LITTLE_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_LITTLE_INTERMEDIATE_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_LITTLE_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_LITTLE_DISTAL_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_LITTLE_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_LEFT_HAND_LITTLE_TIP_FB):
        return U"XR_BODY_JOINT_LEFT_HAND_LITTLE_TIP_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_PALM_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_PALM_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_WRIST_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_WRIST_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_THUMB_METACARPAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_THUMB_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_THUMB_PROXIMAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_THUMB_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_THUMB_DISTAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_THUMB_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_THUMB_TIP_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_THUMB_TIP_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_INDEX_METACARPAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_INDEX_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_INDEX_PROXIMAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_INDEX_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_INDEX_INTERMEDIATE_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_INDEX_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_INDEX_DISTAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_INDEX_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_INDEX_TIP_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_INDEX_TIP_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_METACARPAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_MIDDLE_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_PROXIMAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_MIDDLE_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_INTERMEDIATE_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_MIDDLE_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_DISTAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_MIDDLE_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_TIP_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_MIDDLE_TIP_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_RING_METACARPAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_RING_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_RING_PROXIMAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_RING_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_RING_INTERMEDIATE_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_RING_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_RING_DISTAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_RING_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_RING_TIP_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_RING_TIP_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_METACARPAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_LITTLE_METACARPAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_PROXIMAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_LITTLE_PROXIMAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_INTERMEDIATE_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_LITTLE_INTERMEDIATE_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_DISTAL_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_LITTLE_DISTAL_FB";
        break;
		case(XR_BODY_JOINT_RIGHT_HAND_LITTLE_TIP_FB):
        return U"XR_BODY_JOINT_RIGHT_HAND_LITTLE_TIP_FB";
        break;
		case(XR_BODY_JOINT_COUNT_FB):
        return U"XR_BODY_JOINT_COUNT_FB";
        break;
		case(XR_BODY_JOINT_NONE_FB):
        return U"XR_BODY_JOINT_NONE_FB";
        break;
		default:
        return U"XrBodyJointFB_TOSTR_ERROR";

		}

		}*/

	#endif /*  defined(XR_FB_body_tracking)  */
	#if defined(XR_FB_color_space)
	const vchar* vtostr32_XrColorSpaceFB(XrColorSpaceFB In){
		switch(In){

			case(XR_COLOR_SPACE_UNMANAGED_FB):
				return U"XR_COLOR_SPACE_UNMANAGED_FB";
				break;
			case(XR_COLOR_SPACE_REC2020_FB):
				return U"XR_COLOR_SPACE_REC2020_FB";
				break;
			case(XR_COLOR_SPACE_REC709_FB):
				return U"XR_COLOR_SPACE_REC709_FB";
				break;
			case(XR_COLOR_SPACE_RIFT_CV1_FB):
				return U"XR_COLOR_SPACE_RIFT_CV1_FB";
				break;
			case(XR_COLOR_SPACE_RIFT_S_FB):
				return U"XR_COLOR_SPACE_RIFT_S_FB";
				break;
			case(XR_COLOR_SPACE_QUEST_FB):
				return U"XR_COLOR_SPACE_QUEST_FB";
				break;
			case(XR_COLOR_SPACE_P3_FB):
				return U"XR_COLOR_SPACE_P3_FB";
				break;
			case(XR_COLOR_SPACE_ADOBE_RGB_FB):
				return U"XR_COLOR_SPACE_ADOBE_RGB_FB";
				break;
			default:
				return U"XrColorSpaceFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_color_space)  */
	#if defined(XR_FB_composition_layer_alpha_blend)
	const vchar* vtostr32_XrBlendFactorFB(XrBlendFactorFB In){
		switch(In){

			case(XR_BLEND_FACTOR_ZERO_FB):
				return U"XR_BLEND_FACTOR_ZERO_FB";
				break;
			case(XR_BLEND_FACTOR_ONE_FB):
				return U"XR_BLEND_FACTOR_ONE_FB";
				break;
			case(XR_BLEND_FACTOR_SRC_ALPHA_FB):
				return U"XR_BLEND_FACTOR_SRC_ALPHA_FB";
				break;
			case(XR_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA_FB):
				return U"XR_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA_FB";
				break;
			case(XR_BLEND_FACTOR_DST_ALPHA_FB):
				return U"XR_BLEND_FACTOR_DST_ALPHA_FB";
				break;
			case(XR_BLEND_FACTOR_ONE_MINUS_DST_ALPHA_FB):
				return U"XR_BLEND_FACTOR_ONE_MINUS_DST_ALPHA_FB";
				break;
			default:
				return U"XrBlendFactorFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_composition_layer_alpha_blend)  */
	#if defined(XR_FB_composition_layer_depth_test)
	const vchar* vtostr32_XrCompareOpFB(XrCompareOpFB In){
		switch(In){

			case(XR_COMPARE_OP_NEVER_FB):
				return U"XR_COMPARE_OP_NEVER_FB";
				break;
			case(XR_COMPARE_OP_LESS_FB):
				return U"XR_COMPARE_OP_LESS_FB";
				break;
			case(XR_COMPARE_OP_EQUAL_FB):
				return U"XR_COMPARE_OP_EQUAL_FB";
				break;
			case(XR_COMPARE_OP_LESS_OR_EQUAL_FB):
				return U"XR_COMPARE_OP_LESS_OR_EQUAL_FB";
				break;
			case(XR_COMPARE_OP_GREATER_FB):
				return U"XR_COMPARE_OP_GREATER_FB";
				break;
			case(XR_COMPARE_OP_NOT_EQUAL_FB):
				return U"XR_COMPARE_OP_NOT_EQUAL_FB";
				break;
			case(XR_COMPARE_OP_GREATER_OR_EQUAL_FB):
				return U"XR_COMPARE_OP_GREATER_OR_EQUAL_FB";
				break;
			case(XR_COMPARE_OP_ALWAYS_FB):
				return U"XR_COMPARE_OP_ALWAYS_FB";
				break;
			default:
				return U"XrCompareOpFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_composition_layer_depth_test)  */
	#if defined(XR_FB_eye_tracking_social)
	const vchar* vtostr32_XrEyePositionFB(XrEyePositionFB In){
		switch(In){

			case(XR_EYE_POSITION_LEFT_FB):
				return U"XR_EYE_POSITION_LEFT_FB";
				break;
			case(XR_EYE_POSITION_RIGHT_FB):
				return U"XR_EYE_POSITION_RIGHT_FB";
				break;
			case(XR_EYE_POSITION_COUNT_FB):
				return U"XR_EYE_POSITION_COUNT_FB";
				break;
			default:
				return U"XrEyePositionFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_eye_tracking_social)  */
	#if defined(XR_FB_face_tracking)
	const vchar* vtostr32_XrFaceExpressionFB(XrFaceExpressionFB In){
		switch(In){

			case(XR_FACE_EXPRESSION_BROW_LOWERER_L_FB):
				return U"XR_FACE_EXPRESSION_BROW_LOWERER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_BROW_LOWERER_R_FB):
				return U"XR_FACE_EXPRESSION_BROW_LOWERER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_CHEEK_PUFF_L_FB):
				return U"XR_FACE_EXPRESSION_CHEEK_PUFF_L_FB";
				break;
			case(XR_FACE_EXPRESSION_CHEEK_PUFF_R_FB):
				return U"XR_FACE_EXPRESSION_CHEEK_PUFF_R_FB";
				break;
			case(XR_FACE_EXPRESSION_CHEEK_RAISER_L_FB):
				return U"XR_FACE_EXPRESSION_CHEEK_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_CHEEK_RAISER_R_FB):
				return U"XR_FACE_EXPRESSION_CHEEK_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_CHEEK_SUCK_L_FB):
				return U"XR_FACE_EXPRESSION_CHEEK_SUCK_L_FB";
				break;
			case(XR_FACE_EXPRESSION_CHEEK_SUCK_R_FB):
				return U"XR_FACE_EXPRESSION_CHEEK_SUCK_R_FB";
				break;
			case(XR_FACE_EXPRESSION_CHIN_RAISER_B_FB):
				return U"XR_FACE_EXPRESSION_CHIN_RAISER_B_FB";
				break;
			case(XR_FACE_EXPRESSION_CHIN_RAISER_T_FB):
				return U"XR_FACE_EXPRESSION_CHIN_RAISER_T_FB";
				break;
			case(XR_FACE_EXPRESSION_DIMPLER_L_FB):
				return U"XR_FACE_EXPRESSION_DIMPLER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_DIMPLER_R_FB):
				return U"XR_FACE_EXPRESSION_DIMPLER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_CLOSED_L_FB):
				return U"XR_FACE_EXPRESSION_EYES_CLOSED_L_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_CLOSED_R_FB):
				return U"XR_FACE_EXPRESSION_EYES_CLOSED_R_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_DOWN_L_FB):
				return U"XR_FACE_EXPRESSION_EYES_LOOK_DOWN_L_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_DOWN_R_FB):
				return U"XR_FACE_EXPRESSION_EYES_LOOK_DOWN_R_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_LEFT_L_FB):
				return U"XR_FACE_EXPRESSION_EYES_LOOK_LEFT_L_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_LEFT_R_FB):
				return U"XR_FACE_EXPRESSION_EYES_LOOK_LEFT_R_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_RIGHT_L_FB):
				return U"XR_FACE_EXPRESSION_EYES_LOOK_RIGHT_L_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_RIGHT_R_FB):
				return U"XR_FACE_EXPRESSION_EYES_LOOK_RIGHT_R_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_UP_L_FB):
				return U"XR_FACE_EXPRESSION_EYES_LOOK_UP_L_FB";
				break;
			case(XR_FACE_EXPRESSION_EYES_LOOK_UP_R_FB):
				return U"XR_FACE_EXPRESSION_EYES_LOOK_UP_R_FB";
				break;
			case(XR_FACE_EXPRESSION_INNER_BROW_RAISER_L_FB):
				return U"XR_FACE_EXPRESSION_INNER_BROW_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_INNER_BROW_RAISER_R_FB):
				return U"XR_FACE_EXPRESSION_INNER_BROW_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_JAW_DROP_FB):
				return U"XR_FACE_EXPRESSION_JAW_DROP_FB";
				break;
			case(XR_FACE_EXPRESSION_JAW_SIDEWAYS_LEFT_FB):
				return U"XR_FACE_EXPRESSION_JAW_SIDEWAYS_LEFT_FB";
				break;
			case(XR_FACE_EXPRESSION_JAW_SIDEWAYS_RIGHT_FB):
				return U"XR_FACE_EXPRESSION_JAW_SIDEWAYS_RIGHT_FB";
				break;
			case(XR_FACE_EXPRESSION_JAW_THRUST_FB):
				return U"XR_FACE_EXPRESSION_JAW_THRUST_FB";
				break;
			case(XR_FACE_EXPRESSION_LID_TIGHTENER_L_FB):
				return U"XR_FACE_EXPRESSION_LID_TIGHTENER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LID_TIGHTENER_R_FB):
				return U"XR_FACE_EXPRESSION_LID_TIGHTENER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_CORNER_DEPRESSOR_L_FB):
				return U"XR_FACE_EXPRESSION_LIP_CORNER_DEPRESSOR_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_CORNER_DEPRESSOR_R_FB):
				return U"XR_FACE_EXPRESSION_LIP_CORNER_DEPRESSOR_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_CORNER_PULLER_L_FB):
				return U"XR_FACE_EXPRESSION_LIP_CORNER_PULLER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_CORNER_PULLER_R_FB):
				return U"XR_FACE_EXPRESSION_LIP_CORNER_PULLER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_FUNNELER_LB_FB):
				return U"XR_FACE_EXPRESSION_LIP_FUNNELER_LB_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_FUNNELER_LT_FB):
				return U"XR_FACE_EXPRESSION_LIP_FUNNELER_LT_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_FUNNELER_RB_FB):
				return U"XR_FACE_EXPRESSION_LIP_FUNNELER_RB_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_FUNNELER_RT_FB):
				return U"XR_FACE_EXPRESSION_LIP_FUNNELER_RT_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_PRESSOR_L_FB):
				return U"XR_FACE_EXPRESSION_LIP_PRESSOR_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_PRESSOR_R_FB):
				return U"XR_FACE_EXPRESSION_LIP_PRESSOR_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_PUCKER_L_FB):
				return U"XR_FACE_EXPRESSION_LIP_PUCKER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_PUCKER_R_FB):
				return U"XR_FACE_EXPRESSION_LIP_PUCKER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_STRETCHER_L_FB):
				return U"XR_FACE_EXPRESSION_LIP_STRETCHER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_STRETCHER_R_FB):
				return U"XR_FACE_EXPRESSION_LIP_STRETCHER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_SUCK_LB_FB):
				return U"XR_FACE_EXPRESSION_LIP_SUCK_LB_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_SUCK_LT_FB):
				return U"XR_FACE_EXPRESSION_LIP_SUCK_LT_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_SUCK_RB_FB):
				return U"XR_FACE_EXPRESSION_LIP_SUCK_RB_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_SUCK_RT_FB):
				return U"XR_FACE_EXPRESSION_LIP_SUCK_RT_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_TIGHTENER_L_FB):
				return U"XR_FACE_EXPRESSION_LIP_TIGHTENER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LIP_TIGHTENER_R_FB):
				return U"XR_FACE_EXPRESSION_LIP_TIGHTENER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_LIPS_TOWARD_FB):
				return U"XR_FACE_EXPRESSION_LIPS_TOWARD_FB";
				break;
			case(XR_FACE_EXPRESSION_LOWER_LIP_DEPRESSOR_L_FB):
				return U"XR_FACE_EXPRESSION_LOWER_LIP_DEPRESSOR_L_FB";
				break;
			case(XR_FACE_EXPRESSION_LOWER_LIP_DEPRESSOR_R_FB):
				return U"XR_FACE_EXPRESSION_LOWER_LIP_DEPRESSOR_R_FB";
				break;
			case(XR_FACE_EXPRESSION_MOUTH_LEFT_FB):
				return U"XR_FACE_EXPRESSION_MOUTH_LEFT_FB";
				break;
			case(XR_FACE_EXPRESSION_MOUTH_RIGHT_FB):
				return U"XR_FACE_EXPRESSION_MOUTH_RIGHT_FB";
				break;
			case(XR_FACE_EXPRESSION_NOSE_WRINKLER_L_FB):
				return U"XR_FACE_EXPRESSION_NOSE_WRINKLER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_NOSE_WRINKLER_R_FB):
				return U"XR_FACE_EXPRESSION_NOSE_WRINKLER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_OUTER_BROW_RAISER_L_FB):
				return U"XR_FACE_EXPRESSION_OUTER_BROW_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_OUTER_BROW_RAISER_R_FB):
				return U"XR_FACE_EXPRESSION_OUTER_BROW_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_UPPER_LID_RAISER_L_FB):
				return U"XR_FACE_EXPRESSION_UPPER_LID_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_UPPER_LID_RAISER_R_FB):
				return U"XR_FACE_EXPRESSION_UPPER_LID_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_UPPER_LIP_RAISER_L_FB):
				return U"XR_FACE_EXPRESSION_UPPER_LIP_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION_UPPER_LIP_RAISER_R_FB):
				return U"XR_FACE_EXPRESSION_UPPER_LIP_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION_COUNT_FB):
				return U"XR_FACE_EXPRESSION_COUNT_FB";
				break;
			default:
				return U"XrFaceExpressionFB_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrFaceExpressionSetFB(XrFaceExpressionSetFB In){
		switch(In){

			case(XR_FACE_EXPRESSION_SET_DEFAULT_FB):
				return U"XR_FACE_EXPRESSION_SET_DEFAULT_FB";
				break;
			default:
				return U"XrFaceExpressionSetFB_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrFaceConfidenceFB(XrFaceConfidenceFB In){
		switch(In){

			case(XR_FACE_CONFIDENCE_LOWER_FACE_FB):
				return U"XR_FACE_CONFIDENCE_LOWER_FACE_FB";
				break;
			case(XR_FACE_CONFIDENCE_UPPER_FACE_FB):
				return U"XR_FACE_CONFIDENCE_UPPER_FACE_FB";
				break;
			case(XR_FACE_CONFIDENCE_COUNT_FB):
				return U"XR_FACE_CONFIDENCE_COUNT_FB";
				break;
			default:
				return U"XrFaceConfidenceFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_face_tracking)  */
	#if defined(XR_FB_face_tracking2)
	const vchar* vtostr32_XrFaceExpression2FB(XrFaceExpression2FB In){
		switch(In){

			case(XR_FACE_EXPRESSION2_BROW_LOWERER_L_FB):
				return U"XR_FACE_EXPRESSION2_BROW_LOWERER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_BROW_LOWERER_R_FB):
				return U"XR_FACE_EXPRESSION2_BROW_LOWERER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHEEK_PUFF_L_FB):
				return U"XR_FACE_EXPRESSION2_CHEEK_PUFF_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHEEK_PUFF_R_FB):
				return U"XR_FACE_EXPRESSION2_CHEEK_PUFF_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHEEK_RAISER_L_FB):
				return U"XR_FACE_EXPRESSION2_CHEEK_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHEEK_RAISER_R_FB):
				return U"XR_FACE_EXPRESSION2_CHEEK_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHEEK_SUCK_L_FB):
				return U"XR_FACE_EXPRESSION2_CHEEK_SUCK_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHEEK_SUCK_R_FB):
				return U"XR_FACE_EXPRESSION2_CHEEK_SUCK_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHIN_RAISER_B_FB):
				return U"XR_FACE_EXPRESSION2_CHIN_RAISER_B_FB";
				break;
			case(XR_FACE_EXPRESSION2_CHIN_RAISER_T_FB):
				return U"XR_FACE_EXPRESSION2_CHIN_RAISER_T_FB";
				break;
			case(XR_FACE_EXPRESSION2_DIMPLER_L_FB):
				return U"XR_FACE_EXPRESSION2_DIMPLER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_DIMPLER_R_FB):
				return U"XR_FACE_EXPRESSION2_DIMPLER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_CLOSED_L_FB):
				return U"XR_FACE_EXPRESSION2_EYES_CLOSED_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_CLOSED_R_FB):
				return U"XR_FACE_EXPRESSION2_EYES_CLOSED_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_DOWN_L_FB):
				return U"XR_FACE_EXPRESSION2_EYES_LOOK_DOWN_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_DOWN_R_FB):
				return U"XR_FACE_EXPRESSION2_EYES_LOOK_DOWN_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_LEFT_L_FB):
				return U"XR_FACE_EXPRESSION2_EYES_LOOK_LEFT_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_LEFT_R_FB):
				return U"XR_FACE_EXPRESSION2_EYES_LOOK_LEFT_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_RIGHT_L_FB):
				return U"XR_FACE_EXPRESSION2_EYES_LOOK_RIGHT_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_RIGHT_R_FB):
				return U"XR_FACE_EXPRESSION2_EYES_LOOK_RIGHT_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_UP_L_FB):
				return U"XR_FACE_EXPRESSION2_EYES_LOOK_UP_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_EYES_LOOK_UP_R_FB):
				return U"XR_FACE_EXPRESSION2_EYES_LOOK_UP_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_INNER_BROW_RAISER_L_FB):
				return U"XR_FACE_EXPRESSION2_INNER_BROW_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_INNER_BROW_RAISER_R_FB):
				return U"XR_FACE_EXPRESSION2_INNER_BROW_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_JAW_DROP_FB):
				return U"XR_FACE_EXPRESSION2_JAW_DROP_FB";
				break;
			case(XR_FACE_EXPRESSION2_JAW_SIDEWAYS_LEFT_FB):
				return U"XR_FACE_EXPRESSION2_JAW_SIDEWAYS_LEFT_FB";
				break;
			case(XR_FACE_EXPRESSION2_JAW_SIDEWAYS_RIGHT_FB):
				return U"XR_FACE_EXPRESSION2_JAW_SIDEWAYS_RIGHT_FB";
				break;
			case(XR_FACE_EXPRESSION2_JAW_THRUST_FB):
				return U"XR_FACE_EXPRESSION2_JAW_THRUST_FB";
				break;
			case(XR_FACE_EXPRESSION2_LID_TIGHTENER_L_FB):
				return U"XR_FACE_EXPRESSION2_LID_TIGHTENER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LID_TIGHTENER_R_FB):
				return U"XR_FACE_EXPRESSION2_LID_TIGHTENER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_CORNER_DEPRESSOR_L_FB):
				return U"XR_FACE_EXPRESSION2_LIP_CORNER_DEPRESSOR_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_CORNER_DEPRESSOR_R_FB):
				return U"XR_FACE_EXPRESSION2_LIP_CORNER_DEPRESSOR_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_CORNER_PULLER_L_FB):
				return U"XR_FACE_EXPRESSION2_LIP_CORNER_PULLER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_CORNER_PULLER_R_FB):
				return U"XR_FACE_EXPRESSION2_LIP_CORNER_PULLER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_FUNNELER_LB_FB):
				return U"XR_FACE_EXPRESSION2_LIP_FUNNELER_LB_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_FUNNELER_LT_FB):
				return U"XR_FACE_EXPRESSION2_LIP_FUNNELER_LT_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_FUNNELER_RB_FB):
				return U"XR_FACE_EXPRESSION2_LIP_FUNNELER_RB_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_FUNNELER_RT_FB):
				return U"XR_FACE_EXPRESSION2_LIP_FUNNELER_RT_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_PRESSOR_L_FB):
				return U"XR_FACE_EXPRESSION2_LIP_PRESSOR_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_PRESSOR_R_FB):
				return U"XR_FACE_EXPRESSION2_LIP_PRESSOR_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_PUCKER_L_FB):
				return U"XR_FACE_EXPRESSION2_LIP_PUCKER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_PUCKER_R_FB):
				return U"XR_FACE_EXPRESSION2_LIP_PUCKER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_STRETCHER_L_FB):
				return U"XR_FACE_EXPRESSION2_LIP_STRETCHER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_STRETCHER_R_FB):
				return U"XR_FACE_EXPRESSION2_LIP_STRETCHER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_SUCK_LB_FB):
				return U"XR_FACE_EXPRESSION2_LIP_SUCK_LB_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_SUCK_LT_FB):
				return U"XR_FACE_EXPRESSION2_LIP_SUCK_LT_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_SUCK_RB_FB):
				return U"XR_FACE_EXPRESSION2_LIP_SUCK_RB_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_SUCK_RT_FB):
				return U"XR_FACE_EXPRESSION2_LIP_SUCK_RT_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_TIGHTENER_L_FB):
				return U"XR_FACE_EXPRESSION2_LIP_TIGHTENER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIP_TIGHTENER_R_FB):
				return U"XR_FACE_EXPRESSION2_LIP_TIGHTENER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_LIPS_TOWARD_FB):
				return U"XR_FACE_EXPRESSION2_LIPS_TOWARD_FB";
				break;
			case(XR_FACE_EXPRESSION2_LOWER_LIP_DEPRESSOR_L_FB):
				return U"XR_FACE_EXPRESSION2_LOWER_LIP_DEPRESSOR_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_LOWER_LIP_DEPRESSOR_R_FB):
				return U"XR_FACE_EXPRESSION2_LOWER_LIP_DEPRESSOR_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_MOUTH_LEFT_FB):
				return U"XR_FACE_EXPRESSION2_MOUTH_LEFT_FB";
				break;
			case(XR_FACE_EXPRESSION2_MOUTH_RIGHT_FB):
				return U"XR_FACE_EXPRESSION2_MOUTH_RIGHT_FB";
				break;
			case(XR_FACE_EXPRESSION2_NOSE_WRINKLER_L_FB):
				return U"XR_FACE_EXPRESSION2_NOSE_WRINKLER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_NOSE_WRINKLER_R_FB):
				return U"XR_FACE_EXPRESSION2_NOSE_WRINKLER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_OUTER_BROW_RAISER_L_FB):
				return U"XR_FACE_EXPRESSION2_OUTER_BROW_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_OUTER_BROW_RAISER_R_FB):
				return U"XR_FACE_EXPRESSION2_OUTER_BROW_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_UPPER_LID_RAISER_L_FB):
				return U"XR_FACE_EXPRESSION2_UPPER_LID_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_UPPER_LID_RAISER_R_FB):
				return U"XR_FACE_EXPRESSION2_UPPER_LID_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_UPPER_LIP_RAISER_L_FB):
				return U"XR_FACE_EXPRESSION2_UPPER_LIP_RAISER_L_FB";
				break;
			case(XR_FACE_EXPRESSION2_UPPER_LIP_RAISER_R_FB):
				return U"XR_FACE_EXPRESSION2_UPPER_LIP_RAISER_R_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_TIP_INTERDENTAL_FB):
				return U"XR_FACE_EXPRESSION2_TONGUE_TIP_INTERDENTAL_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_TIP_ALVEOLAR_FB):
				return U"XR_FACE_EXPRESSION2_TONGUE_TIP_ALVEOLAR_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_FRONT_DORSAL_PALATE_FB):
				return U"XR_FACE_EXPRESSION2_TONGUE_FRONT_DORSAL_PALATE_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_MID_DORSAL_PALATE_FB):
				return U"XR_FACE_EXPRESSION2_TONGUE_MID_DORSAL_PALATE_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_BACK_DORSAL_VELAR_FB):
				return U"XR_FACE_EXPRESSION2_TONGUE_BACK_DORSAL_VELAR_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_OUT_FB):
				return U"XR_FACE_EXPRESSION2_TONGUE_OUT_FB";
				break;
			case(XR_FACE_EXPRESSION2_TONGUE_RETREAT_FB):
				return U"XR_FACE_EXPRESSION2_TONGUE_RETREAT_FB";
				break;
			case(XR_FACE_EXPRESSION2_COUNT_FB):
				return U"XR_FACE_EXPRESSION2_COUNT_FB";
				break;
			default:
				return U"XrFaceExpression2FB_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrFaceExpressionSet2FB(XrFaceExpressionSet2FB In){
		switch(In){

			case(XR_FACE_EXPRESSION_SET2_DEFAULT_FB):
				return U"XR_FACE_EXPRESSION_SET2_DEFAULT_FB";
				break;
			default:
				return U"XrFaceExpressionSet2FB_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrFaceTrackingDataSource2FB(XrFaceTrackingDataSource2FB In){
		switch(In){

			case(XR_FACE_TRACKING_DATA_SOURCE2_VISUAL_FB):
				return U"XR_FACE_TRACKING_DATA_SOURCE2_VISUAL_FB";
				break;
			case(XR_FACE_TRACKING_DATA_SOURCE2_AUDIO_FB):
				return U"XR_FACE_TRACKING_DATA_SOURCE2_AUDIO_FB";
				break;
			default:
				return U"XrFaceTrackingDataSource2FB_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrFaceConfidence2FB(XrFaceConfidence2FB In){
		switch(In){

			case(XR_FACE_CONFIDENCE2_LOWER_FACE_FB):
				return U"XR_FACE_CONFIDENCE2_LOWER_FACE_FB";
				break;
			case(XR_FACE_CONFIDENCE2_UPPER_FACE_FB):
				return U"XR_FACE_CONFIDENCE2_UPPER_FACE_FB";
				break;
			case(XR_FACE_CONFIDENCE2_COUNT_FB):
				return U"XR_FACE_CONFIDENCE2_COUNT_FB";
				break;
			default:
				return U"XrFaceConfidence2FB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_face_tracking2)  */
	#if defined(XR_FB_foveation_configuration)
	const vchar* vtostr32_XrFoveationLevelFB(XrFoveationLevelFB In){
		switch(In){

			case(XR_FOVEATION_LEVEL_NONE_FB):
				return U"XR_FOVEATION_LEVEL_NONE_FB";
				break;
			case(XR_FOVEATION_LEVEL_LOW_FB):
				return U"XR_FOVEATION_LEVEL_LOW_FB";
				break;
			case(XR_FOVEATION_LEVEL_MEDIUM_FB):
				return U"XR_FOVEATION_LEVEL_MEDIUM_FB";
				break;
			case(XR_FOVEATION_LEVEL_HIGH_FB):
				return U"XR_FOVEATION_LEVEL_HIGH_FB";
				break;
			default:
				return U"XrFoveationLevelFB_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrFoveationDynamicFB(XrFoveationDynamicFB In){
		switch(In){

			case(XR_FOVEATION_DYNAMIC_DISABLED_FB):
				return U"XR_FOVEATION_DYNAMIC_DISABLED_FB";
				break;
			case(XR_FOVEATION_DYNAMIC_LEVEL_ENABLED_FB):
				return U"XR_FOVEATION_DYNAMIC_LEVEL_ENABLED_FB";
				break;
			default:
				return U"XrFoveationDynamicFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_foveation_configuration)  */
	#if defined(XR_FB_spatial_entity_query)
	const vchar* vtostr32_XrSpaceQueryActionFB(XrSpaceQueryActionFB In){
		switch(In){

			case(XR_SPACE_QUERY_ACTION_LOAD_FB):
				return U"XR_SPACE_QUERY_ACTION_LOAD_FB";
				break;
			default:
				return U"XrSpaceQueryActionFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_spatial_entity_query)  */
	#if defined(XR_FB_spatial_entity_storage)
	const vchar* vtostr32_XrSpaceStorageLocationFB(XrSpaceStorageLocationFB In){
		switch(In){

			case(XR_SPACE_STORAGE_LOCATION_INVALID_FB):
				return U"XR_SPACE_STORAGE_LOCATION_INVALID_FB";
				break;
			case(XR_SPACE_STORAGE_LOCATION_LOCAL_FB):
				return U"XR_SPACE_STORAGE_LOCATION_LOCAL_FB";
				break;
			case(XR_SPACE_STORAGE_LOCATION_CLOUD_FB):
				return U"XR_SPACE_STORAGE_LOCATION_CLOUD_FB";
				break;
			default:
				return U"XrSpaceStorageLocationFB_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrSpacePersistenceModeFB(XrSpacePersistenceModeFB In){
		switch(In){

			case(XR_SPACE_PERSISTENCE_MODE_INVALID_FB):
				return U"XR_SPACE_PERSISTENCE_MODE_INVALID_FB";
				break;
			case(XR_SPACE_PERSISTENCE_MODE_INDEFINITE_FB):
				return U"XR_SPACE_PERSISTENCE_MODE_INDEFINITE_FB";
				break;
			default:
				return U"XrSpacePersistenceModeFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_spatial_entity_storage)  */
	#if defined(XR_FB_triangle_mesh)
	const vchar* vtostr32_XrWindingOrderFB(XrWindingOrderFB In){
		switch(In){

			case(XR_WINDING_ORDER_UNKNOWN_FB):
				return U"XR_WINDING_ORDER_UNKNOWN_FB";
				break;
			case(XR_WINDING_ORDER_CW_FB):
				return U"XR_WINDING_ORDER_CW_FB";
				break;
			case(XR_WINDING_ORDER_CCW_FB):
				return U"XR_WINDING_ORDER_CCW_FB";
				break;
			default:
				return U"XrWindingOrderFB_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_FB_triangle_mesh)  */
	#if defined(XR_HTC_body_tracking)
	const vchar* vtostr32_XrBodyJointHTC(XrBodyJointHTC In){
		switch(In){

			case(XR_BODY_JOINT_PELVIS_HTC):
				return U"XR_BODY_JOINT_PELVIS_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_HIP_HTC):
				return U"XR_BODY_JOINT_LEFT_HIP_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_KNEE_HTC):
				return U"XR_BODY_JOINT_LEFT_KNEE_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_ANKLE_HTC):
				return U"XR_BODY_JOINT_LEFT_ANKLE_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_FEET_HTC):
				return U"XR_BODY_JOINT_LEFT_FEET_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_HIP_HTC):
				return U"XR_BODY_JOINT_RIGHT_HIP_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_KNEE_HTC):
				return U"XR_BODY_JOINT_RIGHT_KNEE_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_ANKLE_HTC):
				return U"XR_BODY_JOINT_RIGHT_ANKLE_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_FEET_HTC):
				return U"XR_BODY_JOINT_RIGHT_FEET_HTC";
				break;
			case(XR_BODY_JOINT_WAIST_HTC):
				return U"XR_BODY_JOINT_WAIST_HTC";
				break;
			case(XR_BODY_JOINT_SPINE_LOWER_HTC):
				return U"XR_BODY_JOINT_SPINE_LOWER_HTC";
				break;
			case(XR_BODY_JOINT_SPINE_MIDDLE_HTC):
				return U"XR_BODY_JOINT_SPINE_MIDDLE_HTC";
				break;
			case(XR_BODY_JOINT_SPINE_HIGH_HTC):
				return U"XR_BODY_JOINT_SPINE_HIGH_HTC";
				break;
			case(XR_BODY_JOINT_CHEST_HTC):
				return U"XR_BODY_JOINT_CHEST_HTC";
				break;
			case(XR_BODY_JOINT_NECK_HTC):
				return U"XR_BODY_JOINT_NECK_HTC";
				break;
			case(XR_BODY_JOINT_HEAD_HTC):
				return U"XR_BODY_JOINT_HEAD_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_CLAVICLE_HTC):
				return U"XR_BODY_JOINT_LEFT_CLAVICLE_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_SCAPULA_HTC):
				return U"XR_BODY_JOINT_LEFT_SCAPULA_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_ARM_HTC):
				return U"XR_BODY_JOINT_LEFT_ARM_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_ELBOW_HTC):
				return U"XR_BODY_JOINT_LEFT_ELBOW_HTC";
				break;
			case(XR_BODY_JOINT_LEFT_WRIST_HTC):
				return U"XR_BODY_JOINT_LEFT_WRIST_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_CLAVICLE_HTC):
				return U"XR_BODY_JOINT_RIGHT_CLAVICLE_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_SCAPULA_HTC):
				return U"XR_BODY_JOINT_RIGHT_SCAPULA_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_ARM_HTC):
				return U"XR_BODY_JOINT_RIGHT_ARM_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_ELBOW_HTC):
				return U"XR_BODY_JOINT_RIGHT_ELBOW_HTC";
				break;
			case(XR_BODY_JOINT_RIGHT_WRIST_HTC):
				return U"XR_BODY_JOINT_RIGHT_WRIST_HTC";
				break;
			default:
				return U"XrBodyJointHTC_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrBodyJointSetHTC(XrBodyJointSetHTC In){
		switch(In){

			case(XR_BODY_JOINT_SET_FULL_HTC):
				return U"XR_BODY_JOINT_SET_FULL_HTC";
				break;
			default:
				return U"XrBodyJointSetHTC_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrBodyJointConfidenceHTC(XrBodyJointConfidenceHTC In){
		switch(In){

			case(XR_BODY_JOINT_CONFIDENCE_NONE_HTC):
				return U"XR_BODY_JOINT_CONFIDENCE_NONE_HTC";
				break;
			case(XR_BODY_JOINT_CONFIDENCE_LOW_HTC):
				return U"XR_BODY_JOINT_CONFIDENCE_LOW_HTC";
				break;
			case(XR_BODY_JOINT_CONFIDENCE_HIGH_HTC):
				return U"XR_BODY_JOINT_CONFIDENCE_HIGH_HTC";
				break;
			default:
				return U"XrBodyJointConfidenceHTC_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_HTC_body_tracking)  */
	#if defined(XR_HTC_facial_tracking)
	const vchar* vtostr32_XrEyeExpressionHTC(XrEyeExpressionHTC In){
		switch(In){

			case(XR_EYE_EXPRESSION_LEFT_BLINK_HTC):
				return U"XR_EYE_EXPRESSION_LEFT_BLINK_HTC";
				break;
			case(XR_EYE_EXPRESSION_LEFT_WIDE_HTC):
				return U"XR_EYE_EXPRESSION_LEFT_WIDE_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_BLINK_HTC):
				return U"XR_EYE_EXPRESSION_RIGHT_BLINK_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_WIDE_HTC):
				return U"XR_EYE_EXPRESSION_RIGHT_WIDE_HTC";
				break;
			case(XR_EYE_EXPRESSION_LEFT_SQUEEZE_HTC):
				return U"XR_EYE_EXPRESSION_LEFT_SQUEEZE_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_SQUEEZE_HTC):
				return U"XR_EYE_EXPRESSION_RIGHT_SQUEEZE_HTC";
				break;
			case(XR_EYE_EXPRESSION_LEFT_DOWN_HTC):
				return U"XR_EYE_EXPRESSION_LEFT_DOWN_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_DOWN_HTC):
				return U"XR_EYE_EXPRESSION_RIGHT_DOWN_HTC";
				break;
			case(XR_EYE_EXPRESSION_LEFT_OUT_HTC):
				return U"XR_EYE_EXPRESSION_LEFT_OUT_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_IN_HTC):
				return U"XR_EYE_EXPRESSION_RIGHT_IN_HTC";
				break;
			case(XR_EYE_EXPRESSION_LEFT_IN_HTC):
				return U"XR_EYE_EXPRESSION_LEFT_IN_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_OUT_HTC):
				return U"XR_EYE_EXPRESSION_RIGHT_OUT_HTC";
				break;
			case(XR_EYE_EXPRESSION_LEFT_UP_HTC):
				return U"XR_EYE_EXPRESSION_LEFT_UP_HTC";
				break;
			case(XR_EYE_EXPRESSION_RIGHT_UP_HTC):
				return U"XR_EYE_EXPRESSION_RIGHT_UP_HTC";
				break;
			default:
				return U"XrEyeExpressionHTC_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrLipExpressionHTC(XrLipExpressionHTC In){
		switch(In){

			case(XR_LIP_EXPRESSION_JAW_RIGHT_HTC):
				return U"XR_LIP_EXPRESSION_JAW_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_JAW_LEFT_HTC):
				return U"XR_LIP_EXPRESSION_JAW_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_JAW_FORWARD_HTC):
				return U"XR_LIP_EXPRESSION_JAW_FORWARD_HTC";
				break;
			case(XR_LIP_EXPRESSION_JAW_OPEN_HTC):
				return U"XR_LIP_EXPRESSION_JAW_OPEN_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_APE_SHAPE_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_APE_SHAPE_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_UPPER_RIGHT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_UPPER_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_UPPER_LEFT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_UPPER_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_RIGHT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_LOWER_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_LEFT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_LOWER_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_UPPER_OVERTURN_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_UPPER_OVERTURN_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_OVERTURN_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_LOWER_OVERTURN_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_POUT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_POUT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_RAISER_RIGHT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_RAISER_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_RAISER_LEFT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_RAISER_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_STRETCHER_RIGHT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_STRETCHER_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_STRETCHER_LEFT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_STRETCHER_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_CHEEK_PUFF_RIGHT_HTC):
				return U"XR_LIP_EXPRESSION_CHEEK_PUFF_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_CHEEK_PUFF_LEFT_HTC):
				return U"XR_LIP_EXPRESSION_CHEEK_PUFF_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_CHEEK_SUCK_HTC):
				return U"XR_LIP_EXPRESSION_CHEEK_SUCK_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_UPPER_UPRIGHT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_UPPER_UPRIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_UPPER_UPLEFT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_UPPER_UPLEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_DOWNRIGHT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_LOWER_DOWNRIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_DOWNLEFT_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_LOWER_DOWNLEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_UPPER_INSIDE_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_UPPER_INSIDE_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_INSIDE_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_LOWER_INSIDE_HTC";
				break;
			case(XR_LIP_EXPRESSION_MOUTH_LOWER_OVERLAY_HTC):
				return U"XR_LIP_EXPRESSION_MOUTH_LOWER_OVERLAY_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_LONGSTEP1_HTC):
				return U"XR_LIP_EXPRESSION_TONGUE_LONGSTEP1_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_LEFT_HTC):
				return U"XR_LIP_EXPRESSION_TONGUE_LEFT_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_RIGHT_HTC):
				return U"XR_LIP_EXPRESSION_TONGUE_RIGHT_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_UP_HTC):
				return U"XR_LIP_EXPRESSION_TONGUE_UP_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_DOWN_HTC):
				return U"XR_LIP_EXPRESSION_TONGUE_DOWN_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_ROLL_HTC):
				return U"XR_LIP_EXPRESSION_TONGUE_ROLL_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_LONGSTEP2_HTC):
				return U"XR_LIP_EXPRESSION_TONGUE_LONGSTEP2_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_UPRIGHT_MORPH_HTC):
				return U"XR_LIP_EXPRESSION_TONGUE_UPRIGHT_MORPH_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_UPLEFT_MORPH_HTC):
				return U"XR_LIP_EXPRESSION_TONGUE_UPLEFT_MORPH_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_DOWNRIGHT_MORPH_HTC):
				return U"XR_LIP_EXPRESSION_TONGUE_DOWNRIGHT_MORPH_HTC";
				break;
			case(XR_LIP_EXPRESSION_TONGUE_DOWNLEFT_MORPH_HTC):
				return U"XR_LIP_EXPRESSION_TONGUE_DOWNLEFT_MORPH_HTC";
				break;
			default:
				return U"XrLipExpressionHTC_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrFacialTrackingTypeHTC(XrFacialTrackingTypeHTC In){
		switch(In){

			case(XR_FACIAL_TRACKING_TYPE_EYE_DEFAULT_HTC):
				return U"XR_FACIAL_TRACKING_TYPE_EYE_DEFAULT_HTC";
				break;
			case(XR_FACIAL_TRACKING_TYPE_LIP_DEFAULT_HTC):
				return U"XR_FACIAL_TRACKING_TYPE_LIP_DEFAULT_HTC";
				break;
			default:
				return U"XrFacialTrackingTypeHTC_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_HTC_facial_tracking)  */
	#if defined(XR_HTC_foveation)
	const vchar* vtostr32_XrFoveationModeHTC(XrFoveationModeHTC In){
		switch(In){

			case(XR_FOVEATION_MODE_DISABLE_HTC):
				return U"XR_FOVEATION_MODE_DISABLE_HTC";
				break;
			case(XR_FOVEATION_MODE_FIXED_HTC):
				return U"XR_FOVEATION_MODE_FIXED_HTC";
				break;
			case(XR_FOVEATION_MODE_DYNAMIC_HTC):
				return U"XR_FOVEATION_MODE_DYNAMIC_HTC";
				break;
			case(XR_FOVEATION_MODE_CUSTOM_HTC):
				return U"XR_FOVEATION_MODE_CUSTOM_HTC";
				break;
			default:
				return U"XrFoveationModeHTC_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrFoveationLevelHTC(XrFoveationLevelHTC In){
		switch(In){

			case(XR_FOVEATION_LEVEL_NONE_HTC):
				return U"XR_FOVEATION_LEVEL_NONE_HTC";
				break;
			case(XR_FOVEATION_LEVEL_LOW_HTC):
				return U"XR_FOVEATION_LEVEL_LOW_HTC";
				break;
			case(XR_FOVEATION_LEVEL_MEDIUM_HTC):
				return U"XR_FOVEATION_LEVEL_MEDIUM_HTC";
				break;
			case(XR_FOVEATION_LEVEL_HIGH_HTC):
				return U"XR_FOVEATION_LEVEL_HIGH_HTC";
				break;
			default:
				return U"XrFoveationLevelHTC_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_HTC_foveation)  */
	#if defined(XR_HTC_passthrough)
	const vchar* vtostr32_XrPassthroughFormHTC(XrPassthroughFormHTC In){
		switch(In){

			case(XR_PASSTHROUGH_FORM_PLANAR_HTC):
				return U"XR_PASSTHROUGH_FORM_PLANAR_HTC";
				break;
			case(XR_PASSTHROUGH_FORM_PROJECTED_HTC):
				return U"XR_PASSTHROUGH_FORM_PROJECTED_HTC";
				break;
			default:
				return U"XrPassthroughFormHTC_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_HTC_passthrough)  */
	#if defined(XR_KHR_android_thread_settings)
	const vchar* vtostr32_XrAndroidThreadTypeKHR(XrAndroidThreadTypeKHR In){
		switch(In){

			case(XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR):
				return U"XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR";
				break;
			case(XR_ANDROID_THREAD_TYPE_APPLICATION_WORKER_KHR):
				return U"XR_ANDROID_THREAD_TYPE_APPLICATION_WORKER_KHR";
				break;
			case(XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR):
				return U"XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR";
				break;
			case(XR_ANDROID_THREAD_TYPE_RENDERER_WORKER_KHR):
				return U"XR_ANDROID_THREAD_TYPE_RENDERER_WORKER_KHR";
				break;
			default:
				return U"XrAndroidThreadTypeKHR_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_KHR_android_thread_settings)  */
	#if defined(XR_KHR_visibility_mask)
	const vchar* vtostr32_XrVisibilityMaskTypeKHR(XrVisibilityMaskTypeKHR In){
		switch(In){

			case(XR_VISIBILITY_MASK_TYPE_HIDDEN_TRIANGLE_MESH_KHR):
				return U"XR_VISIBILITY_MASK_TYPE_HIDDEN_TRIANGLE_MESH_KHR";
				break;
			case(XR_VISIBILITY_MASK_TYPE_VISIBLE_TRIANGLE_MESH_KHR):
				return U"XR_VISIBILITY_MASK_TYPE_VISIBLE_TRIANGLE_MESH_KHR";
				break;
			case(XR_VISIBILITY_MASK_TYPE_LINE_LOOP_KHR):
				return U"XR_VISIBILITY_MASK_TYPE_LINE_LOOP_KHR";
				break;
			default:
				return U"XrVisibilityMaskTypeKHR_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_KHR_visibility_mask)  */
	#if defined(XR_META_local_dimming)
	const vchar* vtostr32_XrLocalDimmingModeMETA(XrLocalDimmingModeMETA In){
		switch(In){

			case(XR_LOCAL_DIMMING_MODE_OFF_META):
				return U"XR_LOCAL_DIMMING_MODE_OFF_META";
				break;
			case(XR_LOCAL_DIMMING_MODE_ON_META):
				return U"XR_LOCAL_DIMMING_MODE_ON_META";
				break;
			default:
				return U"XrLocalDimmingModeMETA_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_META_local_dimming)  */
	#if defined(XR_META_performance_metrics)
	const vchar* vtostr32_XrPerformanceMetricsCounterUnitMETA(XrPerformanceMetricsCounterUnitMETA In){
		switch(In){

			case(XR_PERFORMANCE_METRICS_COUNTER_UNIT_GENERIC_META):
				return U"XR_PERFORMANCE_METRICS_COUNTER_UNIT_GENERIC_META";
				break;
			case(XR_PERFORMANCE_METRICS_COUNTER_UNIT_PERCENTAGE_META):
				return U"XR_PERFORMANCE_METRICS_COUNTER_UNIT_PERCENTAGE_META";
				break;
			case(XR_PERFORMANCE_METRICS_COUNTER_UNIT_MILLISECONDS_META):
				return U"XR_PERFORMANCE_METRICS_COUNTER_UNIT_MILLISECONDS_META";
				break;
			case(XR_PERFORMANCE_METRICS_COUNTER_UNIT_BYTES_META):
				return U"XR_PERFORMANCE_METRICS_COUNTER_UNIT_BYTES_META";
				break;
			case(XR_PERFORMANCE_METRICS_COUNTER_UNIT_HERTZ_META):
				return U"XR_PERFORMANCE_METRICS_COUNTER_UNIT_HERTZ_META";
				break;
			default:
				return U"XrPerformanceMetricsCounterUnitMETA_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_META_performance_metrics)  */
	#if defined(XR_META_virtual_keyboard)
	const vchar* vtostr32_XrVirtualKeyboardLocationTypeMETA(XrVirtualKeyboardLocationTypeMETA In){
		switch(In){

			case(XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_CUSTOM_META):
				return U"XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_CUSTOM_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_FAR_META):
				return U"XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_FAR_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_DIRECT_META):
				return U"XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_DIRECT_META";
				break;
			default:
				return U"XrVirtualKeyboardLocationTypeMETA_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrVirtualKeyboardInputSourceMETA(XrVirtualKeyboardInputSourceMETA In){
		switch(In){

			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_RAY_LEFT_META):
				return U"XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_RAY_LEFT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_RAY_RIGHT_META):
				return U"XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_RAY_RIGHT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_RAY_LEFT_META):
				return U"XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_RAY_LEFT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_RAY_RIGHT_META):
				return U"XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_RAY_RIGHT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_DIRECT_LEFT_META):
				return U"XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_DIRECT_LEFT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_DIRECT_RIGHT_META):
				return U"XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_DIRECT_RIGHT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_DIRECT_INDEX_TIP_LEFT_META):
				return U"XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_DIRECT_INDEX_TIP_LEFT_META";
				break;
			case(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_DIRECT_INDEX_TIP_RIGHT_META):
				return U"XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_DIRECT_INDEX_TIP_RIGHT_META";
				break;
			default:
				return U"XrVirtualKeyboardInputSourceMETA_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_META_virtual_keyboard)  */
	#if defined(XR_ML_localization_map)
	const vchar* vtostr32_XrLocalizationMapStateML(XrLocalizationMapStateML In){
		switch(In){

			case(XR_LOCALIZATION_MAP_STATE_NOT_LOCALIZED_ML):
				return U"XR_LOCALIZATION_MAP_STATE_NOT_LOCALIZED_ML";
				break;
			case(XR_LOCALIZATION_MAP_STATE_LOCALIZED_ML):
				return U"XR_LOCALIZATION_MAP_STATE_LOCALIZED_ML";
				break;
			case(XR_LOCALIZATION_MAP_STATE_LOCALIZATION_PENDING_ML):
				return U"XR_LOCALIZATION_MAP_STATE_LOCALIZATION_PENDING_ML";
				break;
			case(XR_LOCALIZATION_MAP_STATE_LOCALIZATION_SLEEPING_BEFORE_RETRY_ML):
				return U"XR_LOCALIZATION_MAP_STATE_LOCALIZATION_SLEEPING_BEFORE_RETRY_ML";
				break;
			default:
				return U"XrLocalizationMapStateML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrLocalizationMapTypeML(XrLocalizationMapTypeML In){
		switch(In){

			case(XR_LOCALIZATION_MAP_TYPE_ON_DEVICE_ML):
				return U"XR_LOCALIZATION_MAP_TYPE_ON_DEVICE_ML";
				break;
			case(XR_LOCALIZATION_MAP_TYPE_CLOUD_ML):
				return U"XR_LOCALIZATION_MAP_TYPE_CLOUD_ML";
				break;
			default:
				return U"XrLocalizationMapTypeML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrLocalizationMapConfidenceML(XrLocalizationMapConfidenceML In){
		switch(In){

			case(XR_LOCALIZATION_MAP_CONFIDENCE_POOR_ML):
				return U"XR_LOCALIZATION_MAP_CONFIDENCE_POOR_ML";
				break;
			case(XR_LOCALIZATION_MAP_CONFIDENCE_FAIR_ML):
				return U"XR_LOCALIZATION_MAP_CONFIDENCE_FAIR_ML";
				break;
			case(XR_LOCALIZATION_MAP_CONFIDENCE_GOOD_ML):
				return U"XR_LOCALIZATION_MAP_CONFIDENCE_GOOD_ML";
				break;
			case(XR_LOCALIZATION_MAP_CONFIDENCE_EXCELLENT_ML):
				return U"XR_LOCALIZATION_MAP_CONFIDENCE_EXCELLENT_ML";
				break;
			default:
				return U"XrLocalizationMapConfidenceML_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_ML_localization_map)  */
	#if defined(XR_ML_marker_understanding)
	const vchar* vtostr32_XrMarkerDetectorProfileML(XrMarkerDetectorProfileML In){
		switch(In){

			case(XR_MARKER_DETECTOR_PROFILE_DEFAULT_ML):
				return U"XR_MARKER_DETECTOR_PROFILE_DEFAULT_ML";
				break;
			case(XR_MARKER_DETECTOR_PROFILE_SPEED_ML):
				return U"XR_MARKER_DETECTOR_PROFILE_SPEED_ML";
				break;
			case(XR_MARKER_DETECTOR_PROFILE_ACCURACY_ML):
				return U"XR_MARKER_DETECTOR_PROFILE_ACCURACY_ML";
				break;
			case(XR_MARKER_DETECTOR_PROFILE_SMALL_TARGETS_ML):
				return U"XR_MARKER_DETECTOR_PROFILE_SMALL_TARGETS_ML";
				break;
			case(XR_MARKER_DETECTOR_PROFILE_LARGE_FOV_ML):
				return U"XR_MARKER_DETECTOR_PROFILE_LARGE_FOV_ML";
				break;
			case(XR_MARKER_DETECTOR_PROFILE_CUSTOM_ML):
				return U"XR_MARKER_DETECTOR_PROFILE_CUSTOM_ML";
				break;
			default:
				return U"XrMarkerDetectorProfileML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrMarkerTypeML(XrMarkerTypeML In){
		switch(In){

			case(XR_MARKER_TYPE_ARUCO_ML):
				return U"XR_MARKER_TYPE_ARUCO_ML";
				break;
			case(XR_MARKER_TYPE_APRIL_TAG_ML):
				return U"XR_MARKER_TYPE_APRIL_TAG_ML";
				break;
			case(XR_MARKER_TYPE_QR_ML):
				return U"XR_MARKER_TYPE_QR_ML";
				break;
			case(XR_MARKER_TYPE_EAN_13_ML):
				return U"XR_MARKER_TYPE_EAN_13_ML";
				break;
			case(XR_MARKER_TYPE_UPC_A_ML):
				return U"XR_MARKER_TYPE_UPC_A_ML";
				break;
			case(XR_MARKER_TYPE_CODE_128_ML):
				return U"XR_MARKER_TYPE_CODE_128_ML";
				break;
			default:
				return U"XrMarkerTypeML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrMarkerArucoDictML(XrMarkerArucoDictML In){
		switch(In){

			case(XR_MARKER_ARUCO_DICT_4X4_50_ML):
				return U"XR_MARKER_ARUCO_DICT_4X4_50_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_4X4_100_ML):
				return U"XR_MARKER_ARUCO_DICT_4X4_100_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_4X4_250_ML):
				return U"XR_MARKER_ARUCO_DICT_4X4_250_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_4X4_1000_ML):
				return U"XR_MARKER_ARUCO_DICT_4X4_1000_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_5X5_50_ML):
				return U"XR_MARKER_ARUCO_DICT_5X5_50_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_5X5_100_ML):
				return U"XR_MARKER_ARUCO_DICT_5X5_100_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_5X5_250_ML):
				return U"XR_MARKER_ARUCO_DICT_5X5_250_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_5X5_1000_ML):
				return U"XR_MARKER_ARUCO_DICT_5X5_1000_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_6X6_50_ML):
				return U"XR_MARKER_ARUCO_DICT_6X6_50_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_6X6_100_ML):
				return U"XR_MARKER_ARUCO_DICT_6X6_100_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_6X6_250_ML):
				return U"XR_MARKER_ARUCO_DICT_6X6_250_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_6X6_1000_ML):
				return U"XR_MARKER_ARUCO_DICT_6X6_1000_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_7X7_50_ML):
				return U"XR_MARKER_ARUCO_DICT_7X7_50_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_7X7_100_ML):
				return U"XR_MARKER_ARUCO_DICT_7X7_100_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_7X7_250_ML):
				return U"XR_MARKER_ARUCO_DICT_7X7_250_ML";
				break;
			case(XR_MARKER_ARUCO_DICT_7X7_1000_ML):
				return U"XR_MARKER_ARUCO_DICT_7X7_1000_ML";
				break;
			default:
				return U"XrMarkerArucoDictML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrMarkerAprilTagDictML(XrMarkerAprilTagDictML In){
		switch(In){

			case(XR_MARKER_APRIL_TAG_DICT_16H5_ML):
				return U"XR_MARKER_APRIL_TAG_DICT_16H5_ML";
				break;
			case(XR_MARKER_APRIL_TAG_DICT_25H9_ML):
				return U"XR_MARKER_APRIL_TAG_DICT_25H9_ML";
				break;
			case(XR_MARKER_APRIL_TAG_DICT_36H10_ML):
				return U"XR_MARKER_APRIL_TAG_DICT_36H10_ML";
				break;
			case(XR_MARKER_APRIL_TAG_DICT_36H11_ML):
				return U"XR_MARKER_APRIL_TAG_DICT_36H11_ML";
				break;
			default:
				return U"XrMarkerAprilTagDictML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrMarkerDetectorFpsML(XrMarkerDetectorFpsML In){
		switch(In){

			case(XR_MARKER_DETECTOR_FPS_LOW_ML):
				return U"XR_MARKER_DETECTOR_FPS_LOW_ML";
				break;
			case(XR_MARKER_DETECTOR_FPS_MEDIUM_ML):
				return U"XR_MARKER_DETECTOR_FPS_MEDIUM_ML";
				break;
			case(XR_MARKER_DETECTOR_FPS_HIGH_ML):
				return U"XR_MARKER_DETECTOR_FPS_HIGH_ML";
				break;
			case(XR_MARKER_DETECTOR_FPS_MAX_ML):
				return U"XR_MARKER_DETECTOR_FPS_MAX_ML";
				break;
			default:
				return U"XrMarkerDetectorFpsML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrMarkerDetectorResolutionML(XrMarkerDetectorResolutionML In){
		switch(In){

			case(XR_MARKER_DETECTOR_RESOLUTION_LOW_ML):
				return U"XR_MARKER_DETECTOR_RESOLUTION_LOW_ML";
				break;
			case(XR_MARKER_DETECTOR_RESOLUTION_MEDIUM_ML):
				return U"XR_MARKER_DETECTOR_RESOLUTION_MEDIUM_ML";
				break;
			case(XR_MARKER_DETECTOR_RESOLUTION_HIGH_ML):
				return U"XR_MARKER_DETECTOR_RESOLUTION_HIGH_ML";
				break;
			default:
				return U"XrMarkerDetectorResolutionML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrMarkerDetectorCameraML(XrMarkerDetectorCameraML In){
		switch(In){

			case(XR_MARKER_DETECTOR_CAMERA_RGB_CAMERA_ML):
				return U"XR_MARKER_DETECTOR_CAMERA_RGB_CAMERA_ML";
				break;
			case(XR_MARKER_DETECTOR_CAMERA_WORLD_CAMERAS_ML):
				return U"XR_MARKER_DETECTOR_CAMERA_WORLD_CAMERAS_ML";
				break;
			default:
				return U"XrMarkerDetectorCameraML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrMarkerDetectorCornerRefineMethodML(XrMarkerDetectorCornerRefineMethodML In){
		switch(In){

			case(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_NONE_ML):
				return U"XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_NONE_ML";
				break;
			case(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_SUBPIX_ML):
				return U"XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_SUBPIX_ML";
				break;
			case(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_CONTOUR_ML):
				return U"XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_CONTOUR_ML";
				break;
			case(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_APRIL_TAG_ML):
				return U"XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_APRIL_TAG_ML";
				break;
			default:
				return U"XrMarkerDetectorCornerRefineMethodML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrMarkerDetectorFullAnalysisIntervalML(XrMarkerDetectorFullAnalysisIntervalML In){
		switch(In){

			case(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MAX_ML):
				return U"XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MAX_ML";
				break;
			case(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_FAST_ML):
				return U"XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_FAST_ML";
				break;
			case(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MEDIUM_ML):
				return U"XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MEDIUM_ML";
				break;
			case(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_SLOW_ML):
				return U"XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_SLOW_ML";
				break;
			default:
				return U"XrMarkerDetectorFullAnalysisIntervalML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrMarkerDetectorStatusML(XrMarkerDetectorStatusML In){
		switch(In){

			case(XR_MARKER_DETECTOR_STATUS_PENDING_ML):
				return U"XR_MARKER_DETECTOR_STATUS_PENDING_ML";
				break;
			case(XR_MARKER_DETECTOR_STATUS_READY_ML):
				return U"XR_MARKER_DETECTOR_STATUS_READY_ML";
				break;
			case(XR_MARKER_DETECTOR_STATUS_ERROR_ML):
				return U"XR_MARKER_DETECTOR_STATUS_ERROR_ML";
				break;
			default:
				return U"XrMarkerDetectorStatusML_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_ML_marker_understanding)  */
	#if defined(XR_ML_spatial_anchors)
	const vchar* vtostr32_XrSpatialAnchorConfidenceML(XrSpatialAnchorConfidenceML In){
		switch(In){

			case(XR_SPATIAL_ANCHOR_CONFIDENCE_LOW_ML):
				return U"XR_SPATIAL_ANCHOR_CONFIDENCE_LOW_ML";
				break;
			case(XR_SPATIAL_ANCHOR_CONFIDENCE_MEDIUM_ML):
				return U"XR_SPATIAL_ANCHOR_CONFIDENCE_MEDIUM_ML";
				break;
			case(XR_SPATIAL_ANCHOR_CONFIDENCE_HIGH_ML):
				return U"XR_SPATIAL_ANCHOR_CONFIDENCE_HIGH_ML";
				break;
			default:
				return U"XrSpatialAnchorConfidenceML_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_ML_spatial_anchors)  */
	#if defined(XR_ML_user_calibration)
	const vchar* vtostr32_XrHeadsetFitStatusML(XrHeadsetFitStatusML In){
		switch(In){

			case(XR_HEADSET_FIT_STATUS_UNKNOWN_ML):
				return U"XR_HEADSET_FIT_STATUS_UNKNOWN_ML";
				break;
			case(XR_HEADSET_FIT_STATUS_NOT_WORN_ML):
				return U"XR_HEADSET_FIT_STATUS_NOT_WORN_ML";
				break;
			case(XR_HEADSET_FIT_STATUS_GOOD_FIT_ML):
				return U"XR_HEADSET_FIT_STATUS_GOOD_FIT_ML";
				break;
			case(XR_HEADSET_FIT_STATUS_BAD_FIT_ML):
				return U"XR_HEADSET_FIT_STATUS_BAD_FIT_ML";
				break;
			default:
				return U"XrHeadsetFitStatusML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrEyeCalibrationStatusML(XrEyeCalibrationStatusML In){
		switch(In){

			case(XR_EYE_CALIBRATION_STATUS_UNKNOWN_ML):
				return U"XR_EYE_CALIBRATION_STATUS_UNKNOWN_ML";
				break;
			case(XR_EYE_CALIBRATION_STATUS_NONE_ML):
				return U"XR_EYE_CALIBRATION_STATUS_NONE_ML";
				break;
			case(XR_EYE_CALIBRATION_STATUS_COARSE_ML):
				return U"XR_EYE_CALIBRATION_STATUS_COARSE_ML";
				break;
			case(XR_EYE_CALIBRATION_STATUS_FINE_ML):
				return U"XR_EYE_CALIBRATION_STATUS_FINE_ML";
				break;
			default:
				return U"XrEyeCalibrationStatusML_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_ML_user_calibration)  */
	#if defined(XR_ML_world_mesh_detection)
	const vchar* vtostr32_XrWorldMeshDetectorLodML(XrWorldMeshDetectorLodML In){
		switch(In){

			case(XR_WORLD_MESH_DETECTOR_LOD_MINIMUM_ML):
				return U"XR_WORLD_MESH_DETECTOR_LOD_MINIMUM_ML";
				break;
			case(XR_WORLD_MESH_DETECTOR_LOD_MEDIUM_ML):
				return U"XR_WORLD_MESH_DETECTOR_LOD_MEDIUM_ML";
				break;
			case(XR_WORLD_MESH_DETECTOR_LOD_MAXIMUM_ML):
				return U"XR_WORLD_MESH_DETECTOR_LOD_MAXIMUM_ML";
				break;
			default:
				return U"XrWorldMeshDetectorLodML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrWorldMeshBlockStatusML(XrWorldMeshBlockStatusML In){
		switch(In){

			case(XR_WORLD_MESH_BLOCK_STATUS_NEW_ML):
				return U"XR_WORLD_MESH_BLOCK_STATUS_NEW_ML";
				break;
			case(XR_WORLD_MESH_BLOCK_STATUS_UPDATED_ML):
				return U"XR_WORLD_MESH_BLOCK_STATUS_UPDATED_ML";
				break;
			case(XR_WORLD_MESH_BLOCK_STATUS_DELETED_ML):
				return U"XR_WORLD_MESH_BLOCK_STATUS_DELETED_ML";
				break;
			case(XR_WORLD_MESH_BLOCK_STATUS_UNCHANGED_ML):
				return U"XR_WORLD_MESH_BLOCK_STATUS_UNCHANGED_ML";
				break;
			default:
				return U"XrWorldMeshBlockStatusML_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrWorldMeshBlockResultML(XrWorldMeshBlockResultML In){
		switch(In){

			case(XR_WORLD_MESH_BLOCK_RESULT_SUCCESS_ML):
				return U"XR_WORLD_MESH_BLOCK_RESULT_SUCCESS_ML";
				break;
			case(XR_WORLD_MESH_BLOCK_RESULT_FAILED_ML):
				return U"XR_WORLD_MESH_BLOCK_RESULT_FAILED_ML";
				break;
			case(XR_WORLD_MESH_BLOCK_RESULT_PENDING_ML):
				return U"XR_WORLD_MESH_BLOCK_RESULT_PENDING_ML";
				break;
			case(XR_WORLD_MESH_BLOCK_RESULT_PARTIAL_UPDATE_ML):
				return U"XR_WORLD_MESH_BLOCK_RESULT_PARTIAL_UPDATE_ML";
				break;
			default:
				return U"XrWorldMeshBlockResultML_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_ML_world_mesh_detection)  */
	#if defined(XR_MNDX_force_feedback_curl)
	const vchar* vtostr32_XrForceFeedbackCurlLocationMNDX(XrForceFeedbackCurlLocationMNDX In){
		switch(In){

			case(XR_FORCE_FEEDBACK_CURL_LOCATION_THUMB_CURL_MNDX):
				return U"XR_FORCE_FEEDBACK_CURL_LOCATION_THUMB_CURL_MNDX";
				break;
			case(XR_FORCE_FEEDBACK_CURL_LOCATION_INDEX_CURL_MNDX):
				return U"XR_FORCE_FEEDBACK_CURL_LOCATION_INDEX_CURL_MNDX";
				break;
			case(XR_FORCE_FEEDBACK_CURL_LOCATION_MIDDLE_CURL_MNDX):
				return U"XR_FORCE_FEEDBACK_CURL_LOCATION_MIDDLE_CURL_MNDX";
				break;
			case(XR_FORCE_FEEDBACK_CURL_LOCATION_RING_CURL_MNDX):
				return U"XR_FORCE_FEEDBACK_CURL_LOCATION_RING_CURL_MNDX";
				break;
			case(XR_FORCE_FEEDBACK_CURL_LOCATION_LITTLE_CURL_MNDX):
				return U"XR_FORCE_FEEDBACK_CURL_LOCATION_LITTLE_CURL_MNDX";
				break;
			default:
				return U"XrForceFeedbackCurlLocationMNDX_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_MNDX_force_feedback_curl)  */
	#if defined(XR_MSFT_composition_layer_reprojection)
	const vchar* vtostr32_XrReprojectionModeMSFT(XrReprojectionModeMSFT In){
		switch(In){

			case(XR_REPROJECTION_MODE_DEPTH_MSFT):
				return U"XR_REPROJECTION_MODE_DEPTH_MSFT";
				break;
			case(XR_REPROJECTION_MODE_PLANAR_FROM_DEPTH_MSFT):
				return U"XR_REPROJECTION_MODE_PLANAR_FROM_DEPTH_MSFT";
				break;
			case(XR_REPROJECTION_MODE_PLANAR_MANUAL_MSFT):
				return U"XR_REPROJECTION_MODE_PLANAR_MANUAL_MSFT";
				break;
			case(XR_REPROJECTION_MODE_ORIENTATION_ONLY_MSFT):
				return U"XR_REPROJECTION_MODE_ORIENTATION_ONLY_MSFT";
				break;
			default:
				return U"XrReprojectionModeMSFT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_MSFT_composition_layer_reprojection)  */
	#if defined(XR_MSFT_hand_tracking_mesh)
	const vchar* vtostr32_XrHandPoseTypeMSFT(XrHandPoseTypeMSFT In){
		switch(In){

			case(XR_HAND_POSE_TYPE_TRACKED_MSFT):
				return U"XR_HAND_POSE_TYPE_TRACKED_MSFT";
				break;
			case(XR_HAND_POSE_TYPE_REFERENCE_OPEN_PALM_MSFT):
				return U"XR_HAND_POSE_TYPE_REFERENCE_OPEN_PALM_MSFT";
				break;
			default:
				return U"XrHandPoseTypeMSFT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_MSFT_hand_tracking_mesh)  */
	#if defined(XR_MSFT_scene_marker)
	const vchar* vtostr32_XrSceneMarkerTypeMSFT(XrSceneMarkerTypeMSFT In){
		switch(In){

			case(XR_SCENE_MARKER_TYPE_QR_CODE_MSFT):
				return U"XR_SCENE_MARKER_TYPE_QR_CODE_MSFT";
				break;
			default:
				return U"XrSceneMarkerTypeMSFT_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrSceneMarkerQRCodeSymbolTypeMSFT(XrSceneMarkerQRCodeSymbolTypeMSFT In){
		switch(In){

			case(XR_SCENE_MARKER_QR_CODE_SYMBOL_TYPE_QR_CODE_MSFT):
				return U"XR_SCENE_MARKER_QR_CODE_SYMBOL_TYPE_QR_CODE_MSFT";
				break;
			case(XR_SCENE_MARKER_QR_CODE_SYMBOL_TYPE_MICRO_QR_CODE_MSFT):
				return U"XR_SCENE_MARKER_QR_CODE_SYMBOL_TYPE_MICRO_QR_CODE_MSFT";
				break;
			default:
				return U"XrSceneMarkerQRCodeSymbolTypeMSFT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_MSFT_scene_marker)  */
	#if defined(XR_MSFT_scene_understanding)
	const vchar* vtostr32_XrSceneObjectTypeMSFT(XrSceneObjectTypeMSFT In){
		switch(In){

			case(XR_SCENE_OBJECT_TYPE_UNCATEGORIZED_MSFT):
				return U"XR_SCENE_OBJECT_TYPE_UNCATEGORIZED_MSFT";
				break;
			case(XR_SCENE_OBJECT_TYPE_BACKGROUND_MSFT):
				return U"XR_SCENE_OBJECT_TYPE_BACKGROUND_MSFT";
				break;
			case(XR_SCENE_OBJECT_TYPE_WALL_MSFT):
				return U"XR_SCENE_OBJECT_TYPE_WALL_MSFT";
				break;
			case(XR_SCENE_OBJECT_TYPE_FLOOR_MSFT):
				return U"XR_SCENE_OBJECT_TYPE_FLOOR_MSFT";
				break;
			case(XR_SCENE_OBJECT_TYPE_CEILING_MSFT):
				return U"XR_SCENE_OBJECT_TYPE_CEILING_MSFT";
				break;
			case(XR_SCENE_OBJECT_TYPE_PLATFORM_MSFT):
				return U"XR_SCENE_OBJECT_TYPE_PLATFORM_MSFT";
				break;
			case(XR_SCENE_OBJECT_TYPE_INFERRED_MSFT):
				return U"XR_SCENE_OBJECT_TYPE_INFERRED_MSFT";
				break;
			default:
				return U"XrSceneObjectTypeMSFT_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrScenePlaneAlignmentTypeMSFT(XrScenePlaneAlignmentTypeMSFT In){
		switch(In){

			case(XR_SCENE_PLANE_ALIGNMENT_TYPE_NON_ORTHOGONAL_MSFT):
				return U"XR_SCENE_PLANE_ALIGNMENT_TYPE_NON_ORTHOGONAL_MSFT";
				break;
			case(XR_SCENE_PLANE_ALIGNMENT_TYPE_HORIZONTAL_MSFT):
				return U"XR_SCENE_PLANE_ALIGNMENT_TYPE_HORIZONTAL_MSFT";
				break;
			case(XR_SCENE_PLANE_ALIGNMENT_TYPE_VERTICAL_MSFT):
				return U"XR_SCENE_PLANE_ALIGNMENT_TYPE_VERTICAL_MSFT";
				break;
			default:
				return U"XrScenePlaneAlignmentTypeMSFT_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrSceneComputeStateMSFT(XrSceneComputeStateMSFT In){
		switch(In){

			case(XR_SCENE_COMPUTE_STATE_NONE_MSFT):
				return U"XR_SCENE_COMPUTE_STATE_NONE_MSFT";
				break;
			case(XR_SCENE_COMPUTE_STATE_UPDATING_MSFT):
				return U"XR_SCENE_COMPUTE_STATE_UPDATING_MSFT";
				break;
			case(XR_SCENE_COMPUTE_STATE_COMPLETED_MSFT):
				return U"XR_SCENE_COMPUTE_STATE_COMPLETED_MSFT";
				break;
			case(XR_SCENE_COMPUTE_STATE_COMPLETED_WITH_ERROR_MSFT):
				return U"XR_SCENE_COMPUTE_STATE_COMPLETED_WITH_ERROR_MSFT";
				break;
			default:
				return U"XrSceneComputeStateMSFT_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrSceneComputeConsistencyMSFT(XrSceneComputeConsistencyMSFT In){
		switch(In){

			case(XR_SCENE_COMPUTE_CONSISTENCY_SNAPSHOT_COMPLETE_MSFT):
				return U"XR_SCENE_COMPUTE_CONSISTENCY_SNAPSHOT_COMPLETE_MSFT";
				break;
			case(XR_SCENE_COMPUTE_CONSISTENCY_SNAPSHOT_INCOMPLETE_FAST_MSFT):
				return U"XR_SCENE_COMPUTE_CONSISTENCY_SNAPSHOT_INCOMPLETE_FAST_MSFT";
				break;
			case(XR_SCENE_COMPUTE_CONSISTENCY_OCCLUSION_OPTIMIZED_MSFT):
				return U"XR_SCENE_COMPUTE_CONSISTENCY_OCCLUSION_OPTIMIZED_MSFT";
				break;
			default:
				return U"XrSceneComputeConsistencyMSFT_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrMeshComputeLodMSFT(XrMeshComputeLodMSFT In){
		switch(In){

			case(XR_MESH_COMPUTE_LOD_COARSE_MSFT):
				return U"XR_MESH_COMPUTE_LOD_COARSE_MSFT";
				break;
			case(XR_MESH_COMPUTE_LOD_MEDIUM_MSFT):
				return U"XR_MESH_COMPUTE_LOD_MEDIUM_MSFT";
				break;
			case(XR_MESH_COMPUTE_LOD_FINE_MSFT):
				return U"XR_MESH_COMPUTE_LOD_FINE_MSFT";
				break;
			case(XR_MESH_COMPUTE_LOD_UNLIMITED_MSFT):
				return U"XR_MESH_COMPUTE_LOD_UNLIMITED_MSFT";
				break;
			default:
				return U"XrMeshComputeLodMSFT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_MSFT_scene_understanding)  */
	#if defined(XR_MSFT_spatial_graph_bridge)
	const vchar* vtostr32_XrSpatialGraphNodeTypeMSFT(XrSpatialGraphNodeTypeMSFT In){
		switch(In){

			case(XR_SPATIAL_GRAPH_NODE_TYPE_STATIC_MSFT):
				return U"XR_SPATIAL_GRAPH_NODE_TYPE_STATIC_MSFT";
				break;
			case(XR_SPATIAL_GRAPH_NODE_TYPE_DYNAMIC_MSFT):
				return U"XR_SPATIAL_GRAPH_NODE_TYPE_DYNAMIC_MSFT";
				break;
			default:
				return U"XrSpatialGraphNodeTypeMSFT_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_MSFT_spatial_graph_bridge)  */
	#if defined(XR_OCULUS_external_camera)
	const vchar* vtostr32_XrExternalCameraAttachedToDeviceOCULUS(XrExternalCameraAttachedToDeviceOCULUS In){
		switch(In){

			case(XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_NONE_OCULUS):
				return U"XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_NONE_OCULUS";
				break;
			case(XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_HMD_OCULUS):
				return U"XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_HMD_OCULUS";
				break;
			case(XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_LTOUCH_OCULUS):
				return U"XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_LTOUCH_OCULUS";
				break;
			case(XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_RTOUCH_OCULUS):
				return U"XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_RTOUCH_OCULUS";
				break;
			default:
				return U"XrExternalCameraAttachedToDeviceOCULUS_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_OCULUS_external_camera)  */
	#if defined(XR_QCOM_tracking_optimization_settings)
	const vchar* vtostr32_XrTrackingOptimizationSettingsDomainQCOM(XrTrackingOptimizationSettingsDomainQCOM In){
		switch(In){

			case(XR_TRACKING_OPTIMIZATION_SETTINGS_DOMAIN_ALL_QCOM):
				return U"XR_TRACKING_OPTIMIZATION_SETTINGS_DOMAIN_ALL_QCOM";
				break;
			default:
				return U"XrTrackingOptimizationSettingsDomainQCOM_TOSTR_ERROR";

		}

	}

	const vchar* vtostr32_XrTrackingOptimizationSettingsHintQCOM(XrTrackingOptimizationSettingsHintQCOM In){
		switch(In){

			case(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_NONE_QCOM):
				return U"XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_NONE_QCOM";
				break;
			case(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_LONG_RANGE_PRIORIZATION_QCOM):
				return U"XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_LONG_RANGE_PRIORIZATION_QCOM";
				break;
			case(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_CLOSE_RANGE_PRIORIZATION_QCOM):
				return U"XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_CLOSE_RANGE_PRIORIZATION_QCOM";
				break;
			case(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_LOW_POWER_PRIORIZATION_QCOM):
				return U"XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_LOW_POWER_PRIORIZATION_QCOM";
				break;
			case(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_HIGH_POWER_PRIORIZATION_QCOM):
				return U"XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_HIGH_POWER_PRIORIZATION_QCOM";
				break;
			default:
				return U"XrTrackingOptimizationSettingsHintQCOM_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_QCOM_tracking_optimization_settings)  */
	#if defined(XR_ULTRALEAP_hand_tracking_forearm)
	const vchar* vtostr32_XrHandForearmJointULTRALEAP(XrHandForearmJointULTRALEAP In){
		switch(In){

			case(XR_HAND_FOREARM_JOINT_PALM_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_PALM_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_WRIST_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_WRIST_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_THUMB_METACARPAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_THUMB_METACARPAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_THUMB_PROXIMAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_THUMB_PROXIMAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_THUMB_DISTAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_THUMB_DISTAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_THUMB_TIP_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_THUMB_TIP_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_INDEX_METACARPAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_INDEX_METACARPAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_INDEX_PROXIMAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_INDEX_PROXIMAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_INDEX_INTERMEDIATE_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_INDEX_INTERMEDIATE_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_INDEX_DISTAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_INDEX_DISTAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_INDEX_TIP_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_INDEX_TIP_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_MIDDLE_METACARPAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_MIDDLE_METACARPAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_MIDDLE_PROXIMAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_MIDDLE_PROXIMAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_MIDDLE_INTERMEDIATE_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_MIDDLE_INTERMEDIATE_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_MIDDLE_DISTAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_MIDDLE_DISTAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_MIDDLE_TIP_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_MIDDLE_TIP_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_RING_METACARPAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_RING_METACARPAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_RING_PROXIMAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_RING_PROXIMAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_RING_INTERMEDIATE_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_RING_INTERMEDIATE_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_RING_DISTAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_RING_DISTAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_RING_TIP_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_RING_TIP_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_LITTLE_METACARPAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_LITTLE_METACARPAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_LITTLE_PROXIMAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_LITTLE_PROXIMAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_LITTLE_INTERMEDIATE_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_LITTLE_INTERMEDIATE_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_LITTLE_DISTAL_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_LITTLE_DISTAL_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_LITTLE_TIP_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_LITTLE_TIP_ULTRALEAP";
				break;
			case(XR_HAND_FOREARM_JOINT_ELBOW_ULTRALEAP):
				return U"XR_HAND_FOREARM_JOINT_ELBOW_ULTRALEAP";
				break;
			default:
				return U"XrHandForearmJointULTRALEAP_TOSTR_ERROR";

		}

	}

	#endif /*  defined(XR_ULTRALEAP_hand_tracking_forearm)  */

	#endif

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
		#if defined(XR_HTC_body_tracking)
		xrCreateBodyTrackerHTC = (PFN_xrCreateBodyTrackerHTC)LoadFunc(Instance, "xrCreateBodyTrackerHTC");
		xrDestroyBodyTrackerHTC = (PFN_xrDestroyBodyTrackerHTC)LoadFunc(Instance, "xrDestroyBodyTrackerHTC");
		xrGetBodySkeletonHTC = (PFN_xrGetBodySkeletonHTC)LoadFunc(Instance, "xrGetBodySkeletonHTC");
		xrLocateBodyJointsHTC = (PFN_xrLocateBodyJointsHTC)LoadFunc(Instance, "xrLocateBodyJointsHTC");
		#endif /*  defined(XR_HTC_body_tracking)   */
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
		#if defined(XR_KHR_metal_enable)
		xrGetMetalGraphicsRequirementsKHR = (PFN_xrGetMetalGraphicsRequirementsKHR)LoadFunc(Instance, "xrGetMetalGraphicsRequirementsKHR");
		#endif /*  defined(XR_KHR_metal_enable)   */
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
		#if defined(XR_ML_spatial_anchors)
		xrCreateSpatialAnchorsAsyncML = (PFN_xrCreateSpatialAnchorsAsyncML)LoadFunc(Instance, "xrCreateSpatialAnchorsAsyncML");
		xrCreateSpatialAnchorsCompleteML = (PFN_xrCreateSpatialAnchorsCompleteML)LoadFunc(Instance, "xrCreateSpatialAnchorsCompleteML");
		xrGetSpatialAnchorStateML = (PFN_xrGetSpatialAnchorStateML)LoadFunc(Instance, "xrGetSpatialAnchorStateML");
		#endif /*  defined(XR_ML_spatial_anchors)   */
		#if defined(XR_ML_spatial_anchors_storage)
		xrCreateSpatialAnchorsStorageML = (PFN_xrCreateSpatialAnchorsStorageML)LoadFunc(Instance, "xrCreateSpatialAnchorsStorageML");
		xrDeleteSpatialAnchorsAsyncML = (PFN_xrDeleteSpatialAnchorsAsyncML)LoadFunc(Instance, "xrDeleteSpatialAnchorsAsyncML");
		xrDeleteSpatialAnchorsCompleteML = (PFN_xrDeleteSpatialAnchorsCompleteML)LoadFunc(Instance, "xrDeleteSpatialAnchorsCompleteML");
		xrDestroySpatialAnchorsStorageML = (PFN_xrDestroySpatialAnchorsStorageML)LoadFunc(Instance, "xrDestroySpatialAnchorsStorageML");
		xrPublishSpatialAnchorsAsyncML = (PFN_xrPublishSpatialAnchorsAsyncML)LoadFunc(Instance, "xrPublishSpatialAnchorsAsyncML");
		xrPublishSpatialAnchorsCompleteML = (PFN_xrPublishSpatialAnchorsCompleteML)LoadFunc(Instance, "xrPublishSpatialAnchorsCompleteML");
		xrQuerySpatialAnchorsAsyncML = (PFN_xrQuerySpatialAnchorsAsyncML)LoadFunc(Instance, "xrQuerySpatialAnchorsAsyncML");
		xrQuerySpatialAnchorsCompleteML = (PFN_xrQuerySpatialAnchorsCompleteML)LoadFunc(Instance, "xrQuerySpatialAnchorsCompleteML");
		xrUpdateSpatialAnchorsExpirationAsyncML = (PFN_xrUpdateSpatialAnchorsExpirationAsyncML)LoadFunc(Instance, "xrUpdateSpatialAnchorsExpirationAsyncML");
		xrUpdateSpatialAnchorsExpirationCompleteML = (PFN_xrUpdateSpatialAnchorsExpirationCompleteML)LoadFunc(Instance, "xrUpdateSpatialAnchorsExpirationCompleteML");
		#endif /*  defined(XR_ML_spatial_anchors_storage)   */
		#if defined(XR_ML_system_notifications)
		xrSetSystemNotificationsML = (PFN_xrSetSystemNotificationsML)LoadFunc(Instance, "xrSetSystemNotificationsML");
		#endif /*  defined(XR_ML_system_notifications)   */
		#if defined(XR_ML_user_calibration)
		xrEnableUserCalibrationEventsML = (PFN_xrEnableUserCalibrationEventsML)LoadFunc(Instance, "xrEnableUserCalibrationEventsML");
		#endif /*  defined(XR_ML_user_calibration)   */
		#if defined(XR_ML_world_mesh_detection)
		xrAllocateWorldMeshBufferML = (PFN_xrAllocateWorldMeshBufferML)LoadFunc(Instance, "xrAllocateWorldMeshBufferML");
		xrCreateWorldMeshDetectorML = (PFN_xrCreateWorldMeshDetectorML)LoadFunc(Instance, "xrCreateWorldMeshDetectorML");
		xrDestroyWorldMeshDetectorML = (PFN_xrDestroyWorldMeshDetectorML)LoadFunc(Instance, "xrDestroyWorldMeshDetectorML");
		xrFreeWorldMeshBufferML = (PFN_xrFreeWorldMeshBufferML)LoadFunc(Instance, "xrFreeWorldMeshBufferML");
		xrGetWorldMeshBufferRecommendSizeML = (PFN_xrGetWorldMeshBufferRecommendSizeML)LoadFunc(Instance, "xrGetWorldMeshBufferRecommendSizeML");
		xrRequestWorldMeshAsyncML = (PFN_xrRequestWorldMeshAsyncML)LoadFunc(Instance, "xrRequestWorldMeshAsyncML");
		xrRequestWorldMeshCompleteML = (PFN_xrRequestWorldMeshCompleteML)LoadFunc(Instance, "xrRequestWorldMeshCompleteML");
		xrRequestWorldMeshStateAsyncML = (PFN_xrRequestWorldMeshStateAsyncML)LoadFunc(Instance, "xrRequestWorldMeshStateAsyncML");
		xrRequestWorldMeshStateCompleteML = (PFN_xrRequestWorldMeshStateCompleteML)LoadFunc(Instance, "xrRequestWorldMeshStateCompleteML");
		#endif /*  defined(XR_ML_world_mesh_detection)   */
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
	#if defined(XR_HTC_body_tracking)
	PFN_xrCreateBodyTrackerHTC xrCreateBodyTrackerHTC;
	PFN_xrDestroyBodyTrackerHTC xrDestroyBodyTrackerHTC;
	PFN_xrGetBodySkeletonHTC xrGetBodySkeletonHTC;
	PFN_xrLocateBodyJointsHTC xrLocateBodyJointsHTC;
	#endif /*  defined(XR_HTC_body_tracking)   */
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
	#if defined(XR_KHR_metal_enable)
	PFN_xrGetMetalGraphicsRequirementsKHR xrGetMetalGraphicsRequirementsKHR;
	#endif /*  defined(XR_KHR_metal_enable)   */
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
	#if defined(XR_ML_spatial_anchors)
	PFN_xrCreateSpatialAnchorsAsyncML xrCreateSpatialAnchorsAsyncML;
	PFN_xrCreateSpatialAnchorsCompleteML xrCreateSpatialAnchorsCompleteML;
	PFN_xrGetSpatialAnchorStateML xrGetSpatialAnchorStateML;
	#endif /*  defined(XR_ML_spatial_anchors)   */
	#if defined(XR_ML_spatial_anchors_storage)
	PFN_xrCreateSpatialAnchorsStorageML xrCreateSpatialAnchorsStorageML;
	PFN_xrDeleteSpatialAnchorsAsyncML xrDeleteSpatialAnchorsAsyncML;
	PFN_xrDeleteSpatialAnchorsCompleteML xrDeleteSpatialAnchorsCompleteML;
	PFN_xrDestroySpatialAnchorsStorageML xrDestroySpatialAnchorsStorageML;
	PFN_xrPublishSpatialAnchorsAsyncML xrPublishSpatialAnchorsAsyncML;
	PFN_xrPublishSpatialAnchorsCompleteML xrPublishSpatialAnchorsCompleteML;
	PFN_xrQuerySpatialAnchorsAsyncML xrQuerySpatialAnchorsAsyncML;
	PFN_xrQuerySpatialAnchorsCompleteML xrQuerySpatialAnchorsCompleteML;
	PFN_xrUpdateSpatialAnchorsExpirationAsyncML xrUpdateSpatialAnchorsExpirationAsyncML;
	PFN_xrUpdateSpatialAnchorsExpirationCompleteML xrUpdateSpatialAnchorsExpirationCompleteML;
	#endif /*  defined(XR_ML_spatial_anchors_storage)   */
	#if defined(XR_ML_system_notifications)
	PFN_xrSetSystemNotificationsML xrSetSystemNotificationsML;
	#endif /*  defined(XR_ML_system_notifications)   */
	#if defined(XR_ML_user_calibration)
	PFN_xrEnableUserCalibrationEventsML xrEnableUserCalibrationEventsML;
	#endif /*  defined(XR_ML_user_calibration)   */
	#if defined(XR_ML_world_mesh_detection)
	PFN_xrAllocateWorldMeshBufferML xrAllocateWorldMeshBufferML;
	PFN_xrCreateWorldMeshDetectorML xrCreateWorldMeshDetectorML;
	PFN_xrDestroyWorldMeshDetectorML xrDestroyWorldMeshDetectorML;
	PFN_xrFreeWorldMeshBufferML xrFreeWorldMeshBufferML;
	PFN_xrGetWorldMeshBufferRecommendSizeML xrGetWorldMeshBufferRecommendSizeML;
	PFN_xrRequestWorldMeshAsyncML xrRequestWorldMeshAsyncML;
	PFN_xrRequestWorldMeshCompleteML xrRequestWorldMeshCompleteML;
	PFN_xrRequestWorldMeshStateAsyncML xrRequestWorldMeshStateAsyncML;
	PFN_xrRequestWorldMeshStateCompleteML xrRequestWorldMeshStateCompleteML;
	#endif /*  defined(XR_ML_world_mesh_detection)   */
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
