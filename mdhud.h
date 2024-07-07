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

VLIB_CABIEND
