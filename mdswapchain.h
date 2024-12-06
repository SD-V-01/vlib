////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   mdswapchain.h v1.00
//  Created:     17/06/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef VLIB_EXPERIMENTAL

#include "base_types.h"

typedef enum MDSC_BACKEND{
	MDSC_UNKNOWN = 0,
	MDSC_XENON = 1,
	MDSC_X11,
	MDSC_WAYLAND,
	MDSC_WIN32,
	MDSC_MACOS,
	MDSC_ANDROID,
	MDSC_TERM,

} MDSC_BACKEND;

typedef enum MDSC_ERROR {
	MDSC_ERROR_UNKNOWN,
	MDSC_ERROR_SUCCESS = 1,

} MDSC_ERROR;

MDSC_ERROR mdscTestWayland();
MDSC_ERROR mdscTestTerm();
MDSC_ERROR mdscGetBestSwapchainBackend(MDSC_BACKEND* Result);

#endif
