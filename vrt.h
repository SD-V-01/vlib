////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   vrt.h
//  Version:     v1.00
//  Created:     03/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"

#ifndef _VRT_H_
#define _VRT_H_

VLIBPP_START

VLIB_STRUCT(vrt_sysArgs)


VLIB_STRUCTEND(vrt_sysArgs)

void vrt_usrCode(vrt_sysArgs* Args);

void vrt_CoreMemInit();

VLIBPP_END

#endif
