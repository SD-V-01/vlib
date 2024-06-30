////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   mdos.cpp
//  Version:     v1.00
//  Created:     11/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "mdos.h"
#include "mdmath.h"
#include "system.h"
#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)
#include "time.h"
#include "math.h"

#else
#error implement

#endif

VLIB_CABI

static const char* MDOS_ART_01 =
"__/\\\\\\________/\\\\\\________________/\\\\\\_______/\\\\\\______/\\\\\\_        \n"
" _\\/\\\\\\_______\\/\\\\\\_______________\\///\\\\\\___/\\\\\\/___/\\\\\\\\\\\\\\_       \n"
"  _\\//\\\\\\______/\\\\\\__________________\\///\\\\\\\\\\\\/____\\/////\\\\\\_      \n"
"   __\\//\\\\\\____/\\\\\\____/\\\\\\\\\\\\\\\\\\\\\\_____\\//\\\\\\\\__________\\/\\\\\\_     \n"
"    ___\\//\\\\\\__/\\\\\\____\\///////////_______\\/\\\\\\\\__________\\/\\\\\\_    \n"
"     ____\\//\\\\\\/\\\\\\________________________/\\\\\\\\\\\\_________\\/\\\\\\_   \n"
"      _____\\//\\\\\\\\\\_______________________/\\\\\\////\\\\\\_______\\/\\\\\\_  \n"
"       ______\\//\\\\\\______________________/\\\\\\/___\\///\\\\\\_____\\/\\\\\\_ \n"
"        _______\\///______________________\\///_______\\///______\\///_ \n";

static const char* MDOS_ART_02 =
"__/\\\\\\\\____________/\\\\\\\\__/\\\\\\\\\\\\\\\\\\\\\\\\_________________________________________        \n"
" _\\/\\\\\\\\\\\\________/\\\\\\\\\\\\_\\/\\\\\\////////\\\\\\_______________________________________       \n"
"  _\\/\\\\\\//\\\\\\____/\\\\\\//\\\\\\_\\/\\\\\\______\\//\\\\\\______________________________________      \n"
"   _\\/\\\\\\\\///\\\\\\/\\\\\\/_\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\_______________/\\\\\\\\\\_____/\\\\\\\\\\\\\\\\\\\\_     \n"
"    _\\/\\\\\\__\\///\\\\\\/___\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\_____________/\\\\\\///\\\\\\__\\/\\\\\\//////__    \n"
"     _\\/\\\\\\____\\///_____\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\____________/\\\\\\__\\//\\\\\\_\\/\\\\\\\\\\\\\\\\\\\\_   \n"
"      _\\/\\\\\\_____________\\/\\\\\\_\\/\\\\\\_______/\\\\\\____________\\//\\\\\\__/\\\\\\__\\////////\\\\\\_  \n"
"       _\\/\\\\\\_____________\\/\\\\\\_\\/\\\\\\\\\\\\\\\\\\\\\\\\/______________\\///\\\\\\\\\\/____/\\\\\\\\\\\\\\\\\\\\_ \n"
"        _\\///______________\\///__\\////////////__________________\\/////_____\\//////////__\n";

const char* mdosGetArt(u32 Index) {
	switch (Index) {

		case 1:
			return MDOS_ART_01;

		case 2:
			return MDOS_ART_02;

	}

	return "MDOS_ASCII_ART_ERROR";

}

void mdosPrintTermHeader() {
	vsys_writeConsoleNullStr(MDOS_ART_02);
	vsys_writeConsoleNullStr("\n   Booting Runtime OS .....\n\n\n");

}

VLIB_CABIEND

//SECTION(V): console

//TODO(V): Implement console

//SECTION(V): System time
VLIB_CABI
void mdTimeCreateStopwatch(mdTimeStopwatch* Watch) {
	mdTimeResetStopwatch(Watch);

}

void mdTimeResetStopwatch(mdTimeStopwatch* Watch) {
	Watch->StartTime = mdTimeGetMsSystemTime();

}

u32 mdTimeFromStopwatch(mdTimeStopwatch* Watch) {
	const u32 CurrentTime = mdTimeGetMsSystemTime();
	const u32 Elapsed = CurrentTime - Watch->StartTime;
	return Elapsed;

}

#ifdef VPP
void mdTimeStopwatch::create() {
	mdTimeCreateStopwatch(this);

}

void mdTimeStopwatch::reset() {
	mdTimeResetStopwatch(this);

}

u32 mdTimeStopwatch::getTime() {
	return mdTimeFromStopwatch(this);

}

#endif

void mdTimeCreatePrecisewatch(mdTimePrecisewatch* Watch) {
	*Watch = (mdTimePrecisewatch) { 0 };
	mdTimeResetPresicewatch(Watch);

}

i64 mdTimeGetMicroFromPresicewatch(mdTimePrecisewatch* Watch) {
	const i64 CurrentTime = mdTimeGetMicroSystemTime();
	i64 ElapsedTime = CurrentTime - Watch->StartTime;
	if (ElapsedTime < 0) {
		ElapsedTime = 0;

	}

	Watch->Hystory[Watch->HistoryIndex] = ElapsedTime;
	Watch->HistoryIndex = (Watch->HistoryIndex + 1) % mdTimePrecisewatch_MAX_HISTORY;

	return ElapsedTime;

}

i64 mdTimeGetMicroAverageFromPresicewatch(mdTimePrecisewatch* Watch) {
	i64 ElapsedTime = 0;
	for (u32 v = 0; v < mdTimePrecisewatch_MAX_HISTORY; v++) {
		ElapsedTime += Watch->Hystory[v];

	}

	ElapsedTime /= mdTimePrecisewatch_MAX_HISTORY;
	if (ElapsedTime < 0) {
		ElapsedTime = 0;

	}

	return ElapsedTime;

}

float mdTimeGetSecondFromPresicewatch(mdTimePrecisewatch* Watch) {
	return (float)(mdTimeGetMicroFromPresicewatch(Watch) / 1e6);

}

float mdTimeGetSecondAverageFromPresicewatch(mdTimePrecisewatch* Watch) {
	return (float)(mdTimeGetMicroAverageFromPresicewatch(Watch));

}

void mdTimeResetPresicewatch(mdTimePrecisewatch* Watch) {
	Watch->StartTime = mdTimeGetMicroSystemTime();

}

#ifdef VPP
void mdTimePrecisewatch::create() {
	mdTimeCreatePrecisewatch(this);

}

i64 mdTimePrecisewatch::getMicro() {
	return mdTimeGetMicroFromPresicewatch(this);

}

i64 mdTimePrecisewatch::getAverageMicro() {
	return mdTimeGetMicroAverageFromPresicewatch(this);

}

float mdTimePrecisewatch::getSecond() {
	return mdTimeGetSecondFromPresicewatch(this);

}

float mdTimePrecisewatch::getAverageSecond() {
	return mdTimeGetSecondAverageFromPresicewatch(this);

}

void mdTimePrecisewatch::reset() {
	mdTimeResetPresicewatch(this);

}

#endif

#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)
u32 mdTimeGetMsSystemTime() {
	u32 Ms;
	time_t S;
	struct timespec Spec;
	clock_gettime(CLOCK_REALTIME, &Spec);
	S = Spec.tv_sec;
	Ms = vround64(Spec.tv_nsec / 1.0e6);
	Ms += S * 1000;
	return Ms;

}

i64 mdTimeGetMicroSystemTime() {
	struct timespec Ts;
	clock_gettime(CLOCK_REALTIME, &Ts);
	i64 Us = (Ts.tv_nsec / 1000);
	Us += Ts.tv_sec * 1e6;
	return Us;

}

u32 mdTimeGetTimeSinceStartup() {
	return (u32)time(NULL);

}

i64 mdTimeGetTimerFreq() {
	return 1000000LL;

}

#else
#error Implement platform

#endif
VLIB_CABIEND
