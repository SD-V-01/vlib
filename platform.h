////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   platform.h v1.00
//  Created:     03/12/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "version.h"

extern const char* DisruptBuildDate;

enum DisruptPlatform{
	DisruptPlatform_Any = 0,
	DisruptPlatform_Win32, // data_win32 *UNUSED*
	DisruptPlatform_Win64, // data_win64
	DisruptPlatform_Xenon, // no platform directory : Xbox 360
	DisruptPlatform_PS3, // data_ps3
	DisruptPlatform_WiiU, // no platform directory : Wii U
	DisruptPlatform_Durango, // data_durango : Xbox 1
	DisruptPlatform_Orbis, // data_orbis : PS4
	DisruptPlatform_Scarlett, // data_scarlett : Xbox Series X
	DisruptPlatform_Prospero, // data_prospero : PS5
	DisruptPlatform_Yeti, // data_yeti : Stadia
	DisruptPlatform_Deckard, // data_deckard : Linux arm

};

const char* disruptPlatformToStr(DisruptPlatform In);
const char* disruptPlatformDataFolder(DisruptPlatform In);
DisruptPlatform disruptGetCurrentPlatform();

#endif
