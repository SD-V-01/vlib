////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mdhud.c
//  Version:     v1.00
//  Created:     02/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "mdhud.h"
#include "vmem.h"
#include "mderror.h"
#include "system.h"

VLIB_CABI

#define MD_HUD_CREATE_COMMAND_BUFFER_FALLBACK_SIZE 512

void mdHudCreateCommandBuffer(mdHudCommandBuffer* Cmd, st DefaultSize){
	VASSERT(Cmd, "Cmd pointer passed to mdHudCreateCommandBuffer is invalid");
	VASSERT(DefaultSize != 0, "Default size passed to mdHudCreateCommandBuffer cannot be 0");
	if (DefaultSize == 0) {
		DefaultSize = 512;

	}

	vset(Cmd, 0, sizeof(mdHudCommandBuffer));
	const st Size = dpow2(DefaultSize);
	Cmd->Commands = valloc(Size);
	VASSERT(Cmd->Commands, "Valloc failed to allocate new command buffer");
	Cmd->Size = 0;
	Cmd->Alloc = Size;

}

void mdHudDestroyCommandBuffer(mdHudCommandBuffer* Cmd) {
	VASSERT(Cmd, "Cmd pointer passed to mdHudDestroyCommandBuffer is invalid");
	if (Cmd->Commands) {
		vfree(Cmd->Commands);

	}
	vset(Cmd, 0, sizeof(mdHudCommandBuffer));

}

void mdHudCheckSizeCommandBuffer(mdHudCommandBuffer* Cmd, st NewSize) {
	VASSERT(Cmd, "Cmd pointer passed to mdHudCheckSizeCommandBuffer is invalid");
	if (Cmd->Size < NewSize) {
		NewSize = dpow2(NewSize);
		Cmd->Commands = vrealloc(Cmd->Commands, NewSize);
		VASSERT(Cmd->Commands, "Failed to allocate memory for command buffer resize");
		Cmd->Alloc = NewSize;

	}

}

//    TODO(V): Make a better function that allows more than just the last opcode to be removed
void mdHudPopLastCommandBuffer(mdHudCommandBuffer* Cmd) {
	VASSERT(Cmd, "mdHudCommandBuffer pointer passed to mdHudPopLastCommandBuffer is invalid");
	if (Cmd->LastOpcodeSize == 0) {
		VASSERT(0, "Cannot pop more than the last opcode that was added");
		return;

	}

	const st Offset = Cmd->Size - Cmd->LastOpcodeSize;
	char* CharPtr = (char*)Cmd->Commands;
	vset((void*)(CharPtr + Offset), 0, Cmd->LastOpcodeSize);
	Cmd->Size -= Cmd->LastOpcodeSize;
	Cmd->LastOpcodeSize = 0;

}

void mdHudDumpToStdoutCommandBuffer(mdHudCommandBuffer* Cmd) {
	vsys_writeConsoleNullStr("\n");
	char* WorkPtr = (char*)Cmd->Commands;

	while (1) {
		u32* OpCheck = (u32 *)WorkPtr;
		if ((*OpCheck) != 0) {
			const char* DisplayName = mdHudOpcodeToStr(*OpCheck);
			vsys_writeConsoleNullStr(DisplayName);
			vsys_writeConsoleNullStr("\n");
			OpCheck++;
			u32 CommandSizeOffset = *OpCheck;
			WorkPtr += CommandSizeOffset;

		}

		u32* EndCheck = (u32 *)WorkPtr;
		if (*EndCheck == 0) {
			vsys_writeConsoleNullStr("End of command buffer");
			vsys_writeConsoleNullStr("\n");
			break;

		}

	}

}

const char* mdHudOpcodeToStr(u32 Opcode) {
	switch (Opcode) {
		case MD_HUD_BUTTON_OPCODE:
			return "mdHud_opcode_button";

		default:
			return "mdHud_opcode_tostrerror";

	}

}

VLIB_CABIEND

//SECTION(V): Opcodes
VLIB_CABI
void mdHudCmdButton(mdHudCommandBuffer* Cmd, mdHudCmdButtonData* Data) {
	VASSERT(Data->Opcode == MD_HUD_BUTTON_OPCODE, "Bad opcode passed to mdHudCmdButton");
	if (Data->Size != sizeof(mdHudCmdButtonData)) {
		VASSERT(0, "Bad size for fixed size command passed to mdHudCmdButton");
		Data->Size = sizeof(mdHudCmdButtonData);

	}

	static st Size = sizeof(mdHudCmdButtonData);
	mdHudCheckSizeCommandBuffer(Cmd, Size + Cmd->Size);
	char* CharPtr = (char*)Cmd->Commands;
	mdHudCmdButtonData* TargetMem = (mdHudCmdButtonData*)(CharPtr + Cmd->Size);
	(*TargetMem) = *Data;
	Cmd->Size += Size;
	Cmd->LastOpcodeSize = Size;

}

VLIB_CABIEND
