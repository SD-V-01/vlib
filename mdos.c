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
#include "errno.h"
#include "string.h"
#include "sys/sysinfo.h"
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


static const char* MDOS_ART_02_1 = "__/\\\\\\\\____________/\\\\\\\\__/\\\\\\\\\\\\\\\\\\\\\\\\_________________________________________        ";
static const char* MDOS_ART_02_2 = " _\\/\\\\\\\\\\\\________/\\\\\\\\\\\\_\\/\\\\\\////////\\\\\\_______________________________________       ";
static const char* MDOS_ART_02_3 = "  _\\/\\\\\\//\\\\\\____/\\\\\\//\\\\\\_\\/\\\\\\______\\//\\\\\\______________________________________      ";
static const char* MDOS_ART_02_4 = "   _\\/\\\\\\\\///\\\\\\/\\\\\\/_\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\_______________/\\\\\\\\\\_____/\\\\\\\\\\\\\\\\\\\\_     ";
static const char* MDOS_ART_02_5 = "    _\\/\\\\\\__\\///\\\\\\/___\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\_____________/\\\\\\///\\\\\\__\\/\\\\\\//////__    ";
static const char* MDOS_ART_02_6 = "     _\\/\\\\\\____\\///_____\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\____________/\\\\\\__\\//\\\\\\_\\/\\\\\\\\\\\\\\\\\\\\_   ";
static const char* MDOS_ART_02_7 = "      _\\/\\\\\\_____________\\/\\\\\\_\\/\\\\\\_______/\\\\\\____________\\//\\\\\\__/\\\\\\__\\////////\\\\\\_  ";
static const char* MDOS_ART_02_8 = "       _\\/\\\\\\_____________\\/\\\\\\_\\/\\\\\\\\\\\\\\\\\\\\\\\\/______________\\///\\\\\\\\\\/____/\\\\\\\\\\\\\\\\\\\\_ ";
static const char* MDOS_ART_02_9 = "        _\\///______________\\///__\\////////////__________________\\/////_____\\//////////__";

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
	//vsys_writeConsoleNullStr(MDOS_ART_02);
	//vsys_writeConsoleNullStr("\n   Booting Runtime OS .....\n\n\n");

	//VLOG("mdOS", "\n\n{cstr}\n", MDOS_ART_02);
	VLOGNF("mdOS", MDOS_ART_02_1);
	VLOGNF("mdOS", MDOS_ART_02_2);
	VLOGNF("mdOS", MDOS_ART_02_3);
	VLOGNF("mdOS", MDOS_ART_02_4);
	VLOGNF("mdOS", MDOS_ART_02_5);
	VLOGNF("mdOS", MDOS_ART_02_6);
	VLOGNF("mdOS", MDOS_ART_02_7);
	VLOGNF("mdOS", MDOS_ART_02_8);
	VLOGNF("mdOS", MDOS_ART_02_9);
	VLOGNF("mdOS", "    Booting Runtime OS ......");

}

VLIB_CABIEND

//SECTION(V): console
VLIB_CABI
const char* mdConSeverityGetUserStr(mdConSeverity In) {
	switch (In) {
		case mdConSeverity_none:
			return "none";

		case mdConSeverity_verbose:
			return "VERBOSE";

		case mdConSeverity_info:
			return "INFO";

		case mdConSeverity_warning:
			return "WARNING";

		case mdConSeverity_error:
			return "ERROR";

		case mdConSeverity_dataVerbose:
			return "dataVerbose";

		case mdConSeverity_dataInfo:
			return "dataInfo";

		case mdConSeverity_dataWarning:
			return "dataWarning";

		case mdConSeverity_dataError:
			return "dataError";

		case mdConSeverity_bellwether:
			return "Bellwether";

	}
	return "";

}

void mdConStateCreate(mdConState* State, const char* Name) {
	vset(State, 0, sizeof(mdConState));
	State->HtAlloc = dpow2(MD_CON_STATE_DEFAULT_CAPACITY);
	//State->HtSize = 0;
	State->HtPtr = (mdConVar*)vcalloc(sizeof(mdConVar), dpow2(MD_CON_STATE_DEFAULT_CAPACITY));
	if (State->HtPtr == NULL) {
		VASSERT(0, "Failed to allocate memory for mdConState ConVar buffer creation");
//        NOTE(V): Malloc failure
		return;

	}

	//State->EntryAlloc = dpow2(MD_CON_STATE_DEFAULT_CAPACITY);
	//State->
	//State->EntryPtr = (mdConEntry*)vcalloc(sizeof(mdConEntry), dpow2(MD_CON_STATE_DEFAULT_CAPACITY));
	//if (State->EntryPtr == NULL) {
		//VASSERT(0, "Failed to allocate memory for mdConState entry buffer creation");
		//return;

	//}

	State->OutAlloc = MD_CON_STATE_DEFAULT_OUT_LENGTH;
	State->OutSize = 0;
	State->Out = (char*)valloc(State->OutAlloc);
	vset(State->Out, 0, State->OutAlloc);

	st NameLength = vstrlen8(Name);
	if (NameLength > MD_CON_STATE_NAME_LENGTH - 1) {
		NameLength = MD_CON_STATE_NAME_LENGTH - 1;

	}

	vcpy(State->Name, Name, NameLength);
	State->Name[NameLength] = 0;

	mdConStateOutHeader(State);

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

	//for (u64 v = 0; v < State->EntryAlloc; v++) {
		//if (State->EntryPtr[v].Message != NULL) {
			//vfree((void*)State->EntryPtr[v].Message);

		//}

	//}

	vfree((void*)State->HtPtr);
	//vfree((void*)State->EntryPtr);
	vfree((void*)State->Out);
	vset(State, 0, sizeof(mdConState));

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

st mdConStateSetEntry(mdConVar* Entries, st Alloc, mdConVar* Entry, st* Length, mdConState* StatePtr) {
	u64 NewHash = vfnv64std(Entry->Name, vstrlen8(Entry->Name));
	st Index = (st)(NewHash & (u64)(Alloc - 1));
	while (Entries[Index].Name != NULL) {
		//        TODO(V): Use better string handeling
		if (vLEGACYstrcmp(Entry->Name, Entries[Index].Name) == 0) {
			Entries[Index].Var = Entry->Var;
			Entries[Index].Flags = Entry->Flags;
			Entries[Index].Type = Entry->Type;
			Entries[Index].Help = Entry->Help;
			Entries[Index].StatePtr = StatePtr;
			Entries[Index].CallbackPtr = Entry->CallbackPtr;
			return Index;

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
			return 0;

		}
		vcpy(NewNamePtr, Entry->Name, vstrlen8(Entry->Name));
		NewNamePtr[vstrlen8(Entry->Name)] = 0;

		(*Length)++;

	}
	else {
		VASSERT(0, "The con state is probabelly corupted");

	}

	Entries[Index].Name = NewNamePtr;
	Entries[Index].Var = Entry->Var;
	Entries[Index].Flags = Entry->Flags;
	Entries[Index].Type = Entry->Type;
	Entries[Index].Help = Entry->Help;
	Entries[Index].StatePtr = StatePtr;
	Entries[Index].CallbackPtr = Entry->CallbackPtr;

	return Index;

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
	st NewLength = 0;
	for (st v = 0; v < OldSize; v++) {
		mdConVar OldVar = State->HtPtr[v];
		if (OldVar.Name != NULL) {
			mdConStateSetEntry(NewVars, NewSize, &OldVar, &NewLength, State);

		}

	}

	vfree((void*)State->HtPtr);
	State->HtPtr = NewVars;
	State->HtAlloc = NewSize;
	State->HtSize = NewLength;
	return;

}

void mdConStateSet(mdConState* State, mdConVar* Var) {
	VASSERT(State != NULL, "State ptr passed to mdConStateSet is NULL");
	VASSERT(Var != NULL, "Var ptr passed to mdConStateSet is NULL");
	VASSERT(Var->Name != NULL, "Var->Name passed to mdConStateSet is NULL");

	if ((State == NULL) || (Var == NULL)) {
		return;

	}

	if (State->HtAlloc <= State->HtSize) {

		mdConStateResize(State);

	}

	mdConStateSetEntry(State->HtPtr, State->HtAlloc, Var, &State->HtSize, State);

}

void mdConStateDumpToStdout(mdConState* State) {
	vsys_writeConsoleNullStr("Dumping mdConState to stdout, ");
	vsys_writeConsoleInteger(State->HtSize);
	vsys_writeConsoleNullStr(" Found with size ");
	vsys_writeConsoleInteger(State->HtAlloc);
	vsys_writeConsoleNullStr("\n");

	for (st v = 0; v < State->HtAlloc; v++) {
		char Buff[2048] = "";
		mdConVarToStr(&(State->HtPtr[v]), Buff, 2048);
		vsys_writeConsoleNullStr(Buff);
		vsys_writeConsoleNullStr("\n");

	}

}

void mdConStateDumpDbToSelfe(mdConState* State) {
	mdConStatePrint(State, "mdOS", "Dumping all CVAR's", mdConSeverity_info);
	st Count = 0;

	for (st v = 0; v < State->HtAlloc; v++) {
		if (State->HtPtr[v].Name != NULL) {
			char Buff[2048] = { 0 };
			mdConVarToStr(&(State->HtPtr[v]), Buff, 2048);
			mdConStatePrint(State, "mdOS", Buff, mdConSeverity_info);

			Count++;

		}

	}

	mdConStateFmt(State, "mdOS", "Found {st} CVAR's", mdConSeverity_info, Count);

}

void mdConStateOutNullStr(mdConState* State, const char* Str) {
	mdConStateOut(State, Str, vstrlen8(Str));

}

void mdConStateOut(mdConState* State, const char* Str, st Size) {
	#ifndef VLIB_NO_STDOUT_MDCONSTATE_OUT_LOGGING
	char SystemFmt[Size + 256];
	//    TODO(V): Make it so we input the size of the string with something
	//     like {cstr:sizearg} where we pass another arg to be the size
	vformat8("DUNIA Console [{cstr}] {cstr}", SystemFmt, Size + 256, State->Name, Str);
	vsys_writeConsoleNullStr(SystemFmt);

	#endif

	mdConCheckSizeOut(State, State->OutSize + Size);
//    NOTE(V): If mdConCheckSizeOut fails to realloc the array it just doesent update OutAlloc so we check for that
	if (State->OutAlloc > (State->OutSize + Size)) {
		vcpy(State->Out + State->OutSize, Str, Size);
		State->OutSize += Size;

	}

}

void mdConCheckSizeOut(mdConState* State, st NewSize) {
	if (NewSize < State->OutAlloc) {
		return;

	}

	NewSize = dpow2(NewSize);
	char* NewPtr = (char*)valloc(NewSize);
	if (NewPtr == NULL) {
		return;

	}

	vset(NewPtr, 0, NewSize);
	vcpy(NewPtr, State->Out, State->OutSize);

	vfree((void*)State->Out);
	State->Out = NewPtr;
	State->OutAlloc = NewSize;

}

void mdConStateOutHeader(mdConState* State) {
	/*
	mdConStateOutNullStr(State, "Dunia log start\n");

	mdConStateOutNullStr(State, "UTC Time: [");
	char UTC[32];
	mdTimeToStr(mdTimeGetMicroSystemTime(), UTC);
	mdConStateOutNullStr(State, UTC);
	mdConStateOutNullStr(State, "Z] Local Time: [");

	char LOCAL[32];
	mdTimeToStr(mdTimeGetMicroSystemTime(), LOCAL);
	mdConStateOutNullStr(State, LOCAL);
	mdConStateOutNullStr(State, "]\n\n");
	*/

	char UTC[32];
	mdTimeToStr(mdTimeGetMicroSystemTime(), UTC);
	char LOCAL[32];
	mdTimeToStr(mdTimeGetMicroSystemTime(), LOCAL);
	//    TODO(V): Make it so we handle timezones for this

	char Buffer[1024];
	vformat8("Dunia log start\nUTC Time: [{cstr}Z] LocalTime: [{cstr}]\n\n", Buffer, 1024, UTC, LOCAL);
	mdConStateOutNullStr(State, Buffer);

}

static mdConState DuniaConsole;
static bool IsDuniaConsoleStarted = false;

void mdConStart() {
	if (IsDuniaConsoleStarted == false) {
		IsDuniaConsoleStarted = true;
		mdConStateCreate(&DuniaConsole, "DISRUPT");

	}

}

void mdConEnd() {
	mdConStateDestroy(&DuniaConsole);

}

void mdConLog(const char* Str) {
	mdConStart();
	mdConStateOutNullStr(&DuniaConsole, Str);

}

mdConState* mdConGetDisruptConsole() {
	return &DuniaConsole;

}

void mdConStatePrint(mdConState* State, const char* Subsystem, const char* Message, mdConSeverity Severity) {
	char OutStr[vstrlen8(Message) + vstrlen8(Subsystem) + 512];
	char OutTime[32];
	mdTimeToStr(mdTimeGetMicroSystemTime(), OutTime);
	vformat8("{cstr}Z [{cstr}, {cstr}] {cstr}\n", OutStr, vstrlen8(Message) + vstrlen8(Subsystem) + 512, OutTime, Subsystem,
			 mdConSeverityGetUserStr(Severity), Message);
	//mdConLog(OutStr);
	mdConStateOutNullStr(State, OutStr);

}

void mdConStateFmtImpl(mdConState* State, const char* Subsystem, const char* Message, mdConSeverity Severity, v_varargList Args) {
	char UsrFmt[vstrlen8(Message) + vstrlen8(Message) + 64];
	vformat8impl(Message, UsrFmt, vstrlen8(Message) + vstrlen8(Message) + 64, Args);

	char OutStr[vstrlen8(UsrFmt) + 512];
	char OutTime[32];
	mdTimeToStr(mdTimeGetMicroSystemTime(), OutTime);
	
	vformat8("{cstr}Z [{cstr}, {cstr}] {cstr}\n", OutStr, vstrlen8(UsrFmt) + 512,
			 OutTime , Subsystem, mdConSeverityGetUserStr(Severity), UsrFmt);
	//mdConLog(OutStr);
	mdConStateOutNullStr(State, OutStr);

}

void mdConStateFmt(mdConState* State, const char* Subsystem, const char* Message, mdConSeverity Severity, ...) {
	v_varargList Args;
	v_varargStart(Args, Severity);
	mdConStateFmtImpl(State, Subsystem, Message, Severity, Args);
	v_varargEnd(Args);

}

void mdConLogInternFmt_DO_NOT_USE(const char* Subsystem, const char* Message, mdConSeverity Severity, ...) {
	mdConStart();
	v_varargList Args;
	v_varargStart(Args, Severity);
	mdConStateFmtImpl(&DuniaConsole, Subsystem, Message, Severity, Args);
	
	v_varargEnd(Args);

}

void mdConLogIntern_DO_NOT_USE(const char* Subsystem, const char* Message, mdConSeverity Severity) {
	mdConStart();
	mdConStatePrint(&DuniaConsole, Subsystem, Message, Severity);

}

void mdConDumpToStdout() {
	mdConStart();
	vsys_writeConsoleNullStr("Dumping console state \"");
	vsys_writeConsoleNullStr(DuniaConsole.Name);
	vsys_writeConsoleNullStr("\" to Std out\n");

	vsys_writeConsoleNullStr("################# START OF CONSOLE BUFFER #################\n");
	vsys_writeConsoleNullStr(DuniaConsole.Out);
	vsys_writeConsoleNullStr("################# END OF CONSOLE BUFFER #################\n");

}

void mdConVarToStr(mdConVar* Var, char* Buffer, st BufferSize) {
	if (Var->Name != NULL) {
		vformat8("mdConVar VarInt \"{i64}\" Var raw \"{p}\" Flags \"{u64:hex}\" type \"{mdConVarType}\" \"{u64}\" name \"{cstr}\" help \"{cstr}\" StatePtr {p} CallbackPtr {p}",
				 Buffer, BufferSize,
				 Var->Var.VarInt, Var->Var.VarDouble, Var->Flags, Var->Flags,
				 Var->Type, Var->Type, Var->Name, Var->Help, Var->StatePtr, Var->CallbackPtr);

	}

	//if (Var->Name != NULL) {
		//vformat8("mdConVar VarInt \"{i64}\"",
				 //Buffer, BufferSize,
				 //Var->Var.VarInt);

	//}

}

VLIB_CABIEND

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

void mdTimeToStr(i64 Time, char* Buffer) {
//    TODO(V): Implement
	vinttostr8(Time, Buffer, 24);

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

//SECTION(V): Object loading

#if defined(VLIB_ON_CRT) && defined(VLIB_PLATFORM_LINUX)
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <dlfcn.h>

mdsoHandle mdsoOpen(const char* Name, const mdsoFlags* Flags) {
	void* Result = NULL;
	int GnuFlags = 0;
	if ((*Flags & mdsoFlags_lazyBind) == mdsoFlags_lazyBind) {
		GnuFlags |= RTLD_LAZY;

	}
	else {
		GnuFlags |= RTLD_NOW;

	}

	if ((*Flags & mdsoFlags_dontLoad) == mdsoFlags_dontLoad) {
		GnuFlags |= RTLD_NOLOAD;

	}

	if ((*Flags & mdsoFlags_localSymbols) == mdsoFlags_localSymbols) {
		GnuFlags |= RTLD_LOCAL;

	}
	else {
		GnuFlags |= RTLD_GLOBAL;

	}

	Result = dlopen(Name, GnuFlags);
	if (Result == NULL) {
		char* ErrorStr = dlerror();
		VDERR("SharedObject", "Failed to load library {cstr} flags {u32:hex} with error \"{cstr}\"", Name, Flags, ErrorStr);

	}

	return Result;

}

void* mdosGetFunc(mdsoHandle Handle, const char* Symbol) {
	void* Result;
	Result = dlsym((void*)Handle, Symbol);
	if (Result == NULL) {
		char* ErrorStr = dlerror();
//        TODO(V): Add code to get the name of the library that is failing and report it
		VDERR("SharedObject", "Failed to load function from library with error \"{cstr\"", ErrorStr);

	}

	return Result;

}

void mdsoClose(mdsoHandle Handle) {
	dlclose((void*)Handle);

}

#else
#error Implement for platform

#endif

//SECTION(V): System info

#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)
u64 mdsysTotalRam() {
	struct sysinfo Info;
	int Err = sysinfo(&Info);
	if (Err != 0) {
		VERR("mdSystemInfo", "Could not get amount of avalable memory with error \"{cstr}\"", strerror(errno));
		return 0;

	}

	return Info.totalram;

}

u64 mdsysTotalHighRam() {
	struct sysinfo Info;
	int Err = sysinfo(&Info);
	if (Err != 0) {
		VERR("mdSystemInfo", "Could not get amount of avalable highmem with error \"{cstr}\"", strerror(errno));
		return 0;

	}

	return Info.totalhigh;

}

u64 mdsysTotalSwap() {
	struct sysinfo Info;
	int Err = sysinfo(&Info);
	if (Err != 0) {
		VERR("mdSystemInfo", "Could not get amount of total total swap with error \"{cstr}\"", strerror(errno));
		return 0;

	}

	return Info.totalswap;

}

u64 mdsysFreeRam() {
	struct sysinfo Info;
	int Err = sysinfo(&Info);
	if (Err != 0) {
		VERR("mdSystemInfo", "Could not get amount of free memory with error \"{cstr}\"", strerror(errno));
		return 0;

	}

	return Info.freeram;

}

u64 mdsysFreeHighRam() {
	struct sysinfo Info;
	int Err = sysinfo(&Info);
	if (Err != 0) {
		VERR("mdSystemInfo", "Could not get amount of free highmem with error \"{cstr}\"", strerror(errno));
		return 0;

	}

	return Info.freehigh;

}

u64 mdsysFreeSwap() {
	struct sysinfo Info;
	int Err = sysinfo(&Info);
	if (Err != 0) {
		VERR("mdSystemInfo", "Could not get amount of free swap with error \"{cstr}\"", strerror(errno));
		return 0;

	}

	return Info.freeswap;

}

u64 mdsysSharedRam() {
	struct sysinfo Info;
	int Err = sysinfo(&Info);
	if (Err != 0) {
		VERR("mdSystemInfo", "Could not get amount of shared ram with error \"{cstr}\"", strerror(errno));
		return 0;

	}

	return Info.sharedram;

}

u64 mdsysBufferRam() {
	struct sysinfo Info;
	int Err = sysinfo(&Info);
	if (Err != 0) {
		VERR("mdSystemInfo", "Could not get amount of buffered ram with error \"{cstr}\"", strerror(errno));
		return 0;

	}

	return Info.bufferram;

}

u64 mdsysTotalProcesses() {
	struct sysinfo Info;
	int Err = sysinfo(&Info);
	if (Err != 0) {
		VERR("mdSystemInfo", "Could not get number of total processes with error \"{cstr}\"", strerror(errno));
		return 0;

	}

	return Info.procs;

}

u64 mdsysUptime() {
	struct sysinfo Info;
	int Err = sysinfo(&Info);
	if (Err != 0) {
		VERR("mdSystemInfo", "Could not get uptime with error \"{cstr}\"", strerror(errno));
		return 0;

	}

	return Info.uptime;

}

#else
#error Implement platform

#endif

//SECTION(V): Init

void mdosInit() {
	mdConStart();
	mdosPrintTermHeader();

}

void mdosExit() {
	mdConEnd();

}
