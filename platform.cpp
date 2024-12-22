////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   platform.cpp v1.00
//  Created:     03/12/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

//NOTE(V): This is to make fastbuild rebuild this file every time
#line 1 "missing.c"

#include "platform.h"
#include "vstr32.h"

const char* DisruptBuildDate = __DATE__ " " __TIME__ "\0";

const char* disruptPlatformToStr(DisruptPlatform In) {
	switch (In) {
		case DisruptPlatform_Any:
			return "AllPlatforms";

		case DisruptPlatform_Win32:
			return "win32";

		case DisruptPlatform_Win64:
			return "win64";

		case DisruptPlatform_Xenon:
			return "x360";

		case DisruptPlatform_PS3:
			return "ps3";

		case DisruptPlatform_WiiU:
			return "cafe";

		case DisruptPlatform_Durango:
			return "durango";

		case DisruptPlatform_Orbis:
			return "orbis";

		case DisruptPlatform_Scarlett:
			return "scarlett";

		case DisruptPlatform_Prospero:
			return "prospero";

		case DisruptPlatform_Yeti:
			return "yeti";

		case DisruptPlatform_Deckard:
			return "deckard";

		case DisruptPlatform_Roy:
			return "roy";

		default:
			return "UNKNOWN_PLATFORM";

	}

}

const char* disruptPlatformDataFolder(DisruptPlatform In) {
	switch (In) {
		case DisruptPlatform_Any:
			return "data_agnostic";

		case DisruptPlatform_Win32:
			return "data_win32";

		case DisruptPlatform_Win64:
			return "data_win64";

		case DisruptPlatform_Xenon:
			return "data_xenon";

		case DisruptPlatform_PS3:
			return "data_ps3";

		case DisruptPlatform_WiiU:
			return "";

		case DisruptPlatform_Durango:
			return "data_durango";

		case DisruptPlatform_Orbis:
			return "data_orbis";

		case DisruptPlatform_Scarlett:
			return "data_scarlett";

		case DisruptPlatform_Prospero:
			return "data_prospero";

		case DisruptPlatform_Yeti:
			return "data_yeti";

		case DisruptPlatform_Deckard:
			return "data_deckard";

		case DisruptPlatform_Roy:
			return "data_roy";

		default:
			return "data_unknown";

	}

}

DisruptPlatform disruptGetCurrentPlatform() {
	#ifdef VLIB_PLATFORM_NT
	return DisruptPlatform_Win64;

	#elif defined(VLIB_PLATFORM_LINUX) && !defined(VLIB_ANDROID)
	return DisruptPlatform_Deckard;

	#elif defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ANDROID)
	return DisruptPlatform_Roy;

	#endif

}
