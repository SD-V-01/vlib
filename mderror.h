////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   mderror.h
//  Version:     v1.00
//  Created:     10/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"

#ifndef _MDERROR_H_
#define _MDERROR_H_

#define MDASSERT(Condition, Message)

#define MDASSERT_FATAL(Condition, Message)

#define VASSERT(Condition, Message)

#define VASSERT_FATAL(Condition, Message)


VLIB_CABI

extern int v_errno;

VLIB_CABIEND

#endif

