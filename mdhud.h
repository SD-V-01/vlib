////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mdhud.h
//  Version:     v1.00
//  Created:     02/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "base_types.h"

#define MDHUD_API

//SECTION(V): General

VLIB_STRUCT(mdHudColor)
u8 R, G, B, A;

VLIB_STRUCTEND(mdHudColor)

VLIB_STRUCT(mdHudRect)
float X, Y, Z;
float A, B, G;

VLIB_STRUCTEND(mdHudRect)

//SECTION(V): Command buffer

VLIB_STRUCT(mdHudCommandBuffer)
void* Commands;
st Size;
st Alloc;
st LastOpcodeSize;

VLIB_STRUCTEND(mdHudCommandBuffer)

VLIB_CABI
#define MD_HUD_COMMAND_BUFFER_DEFAULT_SIZE 512
MDHUD_API void mdHudCreateCommandBuffer(mdHudCommandBuffer* Cmd, st DefaultSize);
MDHUD_API void mdHudDestroyCommandBuffer(mdHudCommandBuffer* Cmd);
MDHUD_API void mdHudCheckSizeCommandBuffer(mdHudCommandBuffer* Cmd, st NewSize);
MDHUD_API void mdHudPopLastCommandBuffer(mdHudCommandBuffer* Cmd);
MDHUD_API void mdHudDumpToStdoutCommandBuffer(mdHudCommandBuffer* Cmd);
MDHUD_API void mdHudAppendCommandCommandBuffer(mdHudCommandBuffer* Buf, void* Command, st Size);
MDHUD_API void mdHudClearCommandBuffer(mdHudCommandBuffer* Cmd);
MDHUD_API const char* mdHudOpcodeToStr(u32 Opcode);

//TODO(V): Do mdHudCmd stuff for drawing
//MDHUD_API void mdHudCmdRect(

VLIB_CABIEND

//SECTION(V): Input

typedef enum mdHudInputDevice {
	mdHudInputDevice_none = 0,
	mdHudInputDevice_keyboard,
	mdHudInputDevice_mouse,
	mdHudInputDevice_vr,

	mdHudInputDevice_COUNT

} mdHudInputDevice;

typedef enum mdHudInputEventType {
	mdHudInputEvent_none = 0,

//    NOTE(V): VR controlls
	mdHudInputEvent_vrButton,
	mdHudInputEvent_vrTrackpad,
	mdHudInputEvent_vrHand,

//    NOTE(V): Mouse
	mdHudInputEvent_mouseButton,
	mdHudInputEvent_mousePos,
	mdHudInputEvent_mouseWhele,

//    NOTE(V): Keyboard
	mdHudInputEvent_kb,
	mdHudInputEvent_text,

//    NOTE(V): Os stuff
	mdHudInputEvent_focus,

	mdHudInputEvent_COUNT

} mdHudInputEventType;

typedef enum mdHudMouseType {
	mdHudMouseType_none = 0,
	mdHudMouseType_pen,
	mdHudMouseType_mouse,
	mdHudMouseType_touchScreen,

	mdHudMouseType_COUNT

} mdHudMouseType;

typedef enum mdHudKey {
	mdHudKey_none = 0,
//    TODO(V): Implement

	mdHudKey_COUNT,

} mdHudKey;

VLIB_STRUCT(mdHudVrButtonInputData)
u32 Id;
bool State;

VLIB_STRUCTEND(mdHudVrButtonInputData)

VLIB_STRUCT(mdHudVrTrackpadInputData)
u32 Id;
float XPosition, YPosition;

VLIB_STRUCTEND(mdHudVrTrackpadInputData)

VLIB_STRUCT(mdHudVrHandInputData)
//TODO(V): Implement

VLIB_STRUCTEND(mdHudVrHandInputData)

VLIB_STRUCT(mdHudMouseButtonInputData)
u32 Id;
bool State;
mdHudMouseType Type;

VLIB_STRUCTEND(mdHudMouseButtonInputData)

VLIB_STRUCT(mdHudMousePosInputData)
float XPosition, YPosition;
mdHudMouseType Type;

VLIB_STRUCTEND(mdHudMousePosInputData)

VLIB_STRUCT(mdHudMouseWheleInputData)
float XWhele, YWhele;
mdHudMouseType Type;

VLIB_STRUCTEND(mdHudMouseWheleInputData)

VLIB_STRUCT(mdHudKeyInputData)
mdHudKey Key;
bool State;
float Analog;

VLIB_STRUCTEND(mdHudKeyInputData)

VLIB_STRUCT(mdHudTextInputData)
vchar Char;

VLIB_STRUCTEND(mdHudTextInputData)

VLIB_STRUCT(mdHudFocusInputData)
bool State;

VLIB_STRUCTEND(mdHudFocusInputData)

VLIB_STRUCT(mdHudInputEvent)
mdHudInputDevice Device;
mdHudInputEventType Type;
u32 Id;

union {
	mdHudVrButtonInputData VrButton;
	mdHudVrTrackpadInputData VrTrackpad;
	mdHudVrHandInputData VrHand;
	mdHudMouseButtonInputData MouseButton;
	mdHudMousePosInputData MousePos;
	mdHudMouseWheleInputData MouseWhele;
	mdHudKeyInputData Key;
	mdHudTextInputData Text;
	mdHudFocusInputData Focus;

};

VLIB_STRUCTEND(mdHudInputEvent)
