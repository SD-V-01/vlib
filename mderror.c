////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   mderror.c v1.00
//  Created:     10/05/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

#include "mderror.h"
#include "system.h"
#include "mdos.h"

VLIB_CABI
void mderrorDebugTrap(const char* Message, const char* Position, st Line){
	mdConLogInternFmt_DO_NOT_USE("Engine", "Failed \"{cstr}\" at line {st} file \"{cstr}\"", mdConSeverity_assert, Message, Line, Position);
	mdConFlush();
	vsys_breakpoint();

}

VLIB_CABIEND

//TODO(V): Implement stack backtracing
//NOTE(V): I don't know if its possible on windows, is it ??
