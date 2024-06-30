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

VLIB_CABI

//TODO(V): Use TLS for errno legacy implementation !!!!!!!!!!!
int v_errno = 0;

VLIB_CABIEND
