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

VLIB_STRUCT(mdHudColor)
u8 R, G, B, A;

VLIB_STRUCTEND(mdHudColor)

VLIB_STRUCT(mdHudCommandBuffer)
void* Commands;
st Size;
st Alloc;
st LastOpcodeSize;

VLIB_STRUCTEND(mdHudCommandBuffer)

VLIB_CABI
MDHUD_API void mdHudCreateCommandBuffer(mdHudCommandBuffer* Cmd, st DefaultSize);
MDHUD_API void mdHudDestroyCommandBuffer(mdHudCommandBuffer* Cmd);
MDHUD_API void mdHudCheckSizeCommandBuffer(mdHudCommandBuffer* Cmd);
MDHUD_API void mdHudPopLastCommandBuffer(mdHudCommandBuffer* Cmd);
MDHUD_API void mdHudDumpToStdoutCommandBuffer(mdHudCommandBuffer* Cmd);
MDHUD_API const char* mdHudOpcodeToStr(u32 Opcode);

VLIB_CABIEND

#define MD_HUD_BUTTON_OPCODE 256
VLIB_STRUCT(mdHudCmdButtonData)
u32 Opcode;
u32 Size;
mdHudColor Color;

VLIB_STRUCTEND(mdHudCmdButtonData)

//SECTION(V): Opcodes
VLIB_CABI
MDHUD_API void mdHudCmdButton(mdHudCommandBuffer* Cmd, mdHudCmdButtonData* Data);

VLIB_CABIEND
