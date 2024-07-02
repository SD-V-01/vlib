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

#include "vstr32.h"
#include "vmem.h"
#include "mderror.h"
#include "mdos.h"
#include "vhash.h"
#include "mdmath.h"
#include "system.h"
#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)
#include "time.h"

#elif defined(VLIB_PLATFORM_NT)
#include "mdsch.h"
#include "mderror.h"
#include <windows.h>

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

void mdConStateCreate(mdConState* State) {
	vset(State, 0, sizeof(State));
	State->HtAlloc = dpow2(MD_CON_STATE_DEFAULT_CAPACITY);
	State->HtPtr = (mdConVar*)vcalloc(sizeof(mdConVar), dpow2(MD_CON_STATE_DEFAULT_CAPACITY));
	if (State->HtPtr == NULL) {
		VASSERT(0, "Failed to allocate memory for mdConState ConVar buffer creation");
//        NOTE(V): Malloc failure
		return;

	}

	State->EntryAlloc = dpow2(MD_CON_STATE_DEFAULT_CAPACITY);
	State->EntryPtr = (mdConEntry*)vcalloc(sizeof(mdConEntry), dpow2(MD_CON_STATE_DEFAULT_CAPACITY));
	if (State->EntryPtr == NULL) {
		VASSERT(0, "Failed to allocate memory for mdConState entry buffer creation");
		return;

	}

}

void mdConStateDestroy(mdConState* State) {
	for (u64 v = 0; v < State->HtAlloc; v++) {
		if (State->HtPtr[v].Name != NULL) {
			vfree((void*)State->HtPtr[v].Name);

		}
		if (State->HtPtr[v].Type == mdConVarType_Str) {
			vfree((void*)State->HtPtr[v].Var.VarStr);

		}

	}

	for (u64 v = 0; v < State->EntryAlloc; v++) {
		if (State->EntryPtr[v].Message != NULL) {
			vfree((void*)State->EntryPtr[v].Message);

		}

	}

	vfree((void*)State->HtPtr);
	vfree((void*)State->EntryPtr);
	vset(State, 0, sizeof(State));

}

mdConVar* mdConStateSearchVar(mdConState* State, const char* Name) {
	u64 Hash = vfnv64std(Name, vstrlen8(Name));
	st Index = (st)(Hash & (u64)(State->HtAlloc - 1));
	while (State->HtPtr[Index].Name != NULL) {
		if (vLEGACYstrcmp(Name, State->HtPtr[Index].Name) == 0) {
			return &(State->HtPtr[Index]);

		}

		Index++;
		if (Index >= State->HtAlloc) {
			Index = 0;

		}

	}

	return NULL;

}

void mdConStateSetEntry(mdConVar* Entries, st Alloc, mdConVar* Entry, st* Length, mdConState* StatePtr) {
	u64 NewHash = vfnv64std(Entry->Name, vstrlen8(Entry->Name));
	st Index = (st)(NewHash & (u64)(Alloc - 1));
	while (Entries[Index].Name != NULL) {
		//        TODO(V): Use better string handeling
		if (vLEGACYstrcmp(Entry->Name, Entries[Index].Name) == 0) {
			Entries[Index].Var = Entry->Var;
			Entries[Index].Flags = Entry->Flags;
			Entries[Index].Type = Entry->Type;
			Entries[Index].StatePtr = StatePtr;
			return;

		}

		Index++;
		if (Index >= Alloc) {
			Index = 0;

		}

	}

	char* NewNamePtr = NULL;
	if (Length != NULL) {
		NewNamePtr = (char*)vcalloc(vstrlen8(Entry->Name) + 1, sizeof(char));
		if (NewNamePtr == NULL) {
			return;

		}
		vcpy(NewNamePtr, Entry->Name, vstrlen8(Entry->Name));
		NewNamePtr[vstrlen8(Entry->Name)] = 0;

		(*Length)++;

	}

	Entries[Index].Name = NewNamePtr;
	Entries[Index].Var = Entry->Var;
	Entries[Index].Flags = Entry->Flags;
	Entries[Index].Type = Entry->Type;
	Entries[Index].StatePtr = StatePtr;

}

void mdConStateResize(mdConState* State) {
	const st OldSize = State->HtAlloc;
	st NewSize = dpow2(State->HtAlloc + 1);
	if (NewSize < State->HtAlloc) {
		return;

	}

	mdConVar* NewVars = (mdConVar*)vcalloc(sizeof(mdConVar), NewSize);
	if (NewVars == NULL) {
		return;

	}

	for (st v = 0; v < OldSize; v++) {
		mdConVar OldVar = State->HtPtr[v];
		if (OldVar.Name != NULL) {
			mdConStateSetEntry(NewVars, NewSize, &OldVar, NULL, State);

		}

	}

	vfree((void*)State->HtPtr);
	State->HtPtr = NewVars;
	State->HtAlloc = NewSize;
	return;

}

void mdConStateSet(mdConState* State, mdConVar* Var) {
	VASSERT(State != NULL, "State ptr passed to mdConStateSet is NULL");
	VASSERT(Var != NULL, "Var ptr passed to mdConStateSet is NULL");
	VASSERT(Var->Name != NULL, "Var->Name passed to mdConStateSet is NULL");

	if ((State == NULL) || (Var == NULL)) {
		return;

	}

	if (State->HtAlloc >= State->HtSize) {
		mdConStateResize(State);

	}

	mdConStateSetEntry(State->HtPtr, State->HtAlloc, Var, &State->HtSize, State);

}

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

VLIB_CABI
i64 mdTimeInt64MulDiv(i64 Val, i64 Num, i64 Denom) {
	i64 Q = Val / Denom;
	i64 R = Val % Denom;
	return Q * Num + R * Num / Denom;

}

VLIB_CABIEND

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

u32 mdTimeGetUnixTime() {
	return (u32)time(NULL);

}

i64 mdTimeGetTimerFreq() {
	return 1000000LL;

}

#elif defined(VLIB_PLATFORM_NT)
static mdCallOnceGuard CallOnceTime = MD_CALL_ONCE_GUARD_CREATE;
static i64 HighResTimerFreq = 0;
static i64 HighResTimerStart = 0;

static i64 TimeGCD(i64 A, i64 B) {
	return (A == 0) ? B : TimeGCD(B % A, A);

}

static bool AllwaysSimpleMulDiv = false;
static i64 TimerToUsecMul = 0;
static i64 TimerToUSecDiv = 0;

static void mdTimeInitIngernal() {
	LARGE_INTEGER Freq;
	BOOL QpcResult = QueryPerformanceFrequency(&Freq);
	VASSERT(QpcResult, "Failed to get performance counter frequency");
	if (QpcResult) {
		HighResTimerFreq = Freq.QuadPart;

	}
	else {
		HighResTimerFreq = 1000LL;

	}

	LARGE_INTEGER Counter;
	QpcResult = QueryPerformanceCounter(&Counter);
	VASSERT(QpcResult, "Failed to query performance counter");
	if (QpcResult) {
		HighResTimerStart = Counter.QuadPart;

	}
	else {
		HighResTimerStart = 0;

	}

	TimerToUSecDiv = (i64)1e6;
	TimerToUsecMul = HighResTimerFreq;
	const i64 Divisor = TimeGCD(TimerToUsecMul, TimerToUSecDiv);
	TimerToUSecDiv /= Divisor;
	TimerToUsecMul /= Divisor;

	AllwaysSimpleMulDiv = (TimerToUsecMul == 1) || (TimerToUSecDiv == 1);

}

static void mdTimeInit() {
	mdCallOnce(CallOnceTime, mdTimeInitIngernal);

}

u32 mdTimeGetMsSystemTime() {
	return (u32)timeGetTime();

}

i64 mdTimeGetMicroSystemTime() {
	mdTimeInit();

	LARGE_INTEGER Counter;
	BOOL QpcResult = QueryPerformanceCounter(&Counter);
	VASSERT(QpcResult, "Could not querry performance counter for mdTimeGetMicroSystemTime()");
	Counter.QuadPart -= HighResTimerStart;
	if (AllwaysSimpleMulDiv) {
		return Counter.QuadPart * TimerToUsecMul / TimerToUSecDiv;

	}
	else {
		return mdTimeInt64MulDiv(Counter.QuadPart, TimerToUsecMul, TimerToUSecDiv);

	}

}

i64 mdTimeGetTimerFreq() {
	mdTimeInit();
	return HighResTimerFreq;

}

#else
#error Implement platform

#endif
VLIB_CABIEND
