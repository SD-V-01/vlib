////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   mderror.h v1.00
//  Created:     10/05/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"

#ifndef _MDERROR_H_
#define _MDERROR_H_

#define VASSERT(Condition, Message) { \
if (!(Condition)) { \
mderrorDebugTrap(Message, __FILE__, __LINE__); }}

#define VASSERTNF(Condition) { \
if (!(Condition)) { \
mderrorDebugTrap("Unknown error", __FILE__, __LINE__); }}

#define VASSERT_FATAL(Condition, Message) { \
if (!(Condition)) { \
mderrorDebugTrap(Message, __FILE__, __LINE__); }}


VLIB_CABI
void mderrorDebugTrap(const char* Message, const char* Position, st Line);

VLIB_CABIEND

#endif
