////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   mderror.cpp
//  Version:     v1.00
//  Created:     10/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "mderror.h"
#include "system.h"

VLIB_CABI

//TODO(V): Use TLS for errno legacy implementation !!!!!!!!!!!
int v_errno = 0;

VLIB_CABIEND

//TODO(V): Implement stack backtracing

//SECTION(V): Logging

VLIB_CABI
void mderrUsrLogging(const char* LogMessage) {
//    TODO(V): Add ability to have a user callback

	vsys_writeConsoleNullStr(LogMessage);
	vsys_writeConsoleNullStr("\n");

}

VLIB_CABIEND
