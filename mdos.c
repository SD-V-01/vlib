////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   mdos.c v1.00
//  Created:     11/05/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

#include "vstr32.h"
#include "vmem.h"
#include "mderror.h"
#include "mdos.h"
#include "vhash.h"
#include "vmath.h"
#include "system.h"
#include "mdsch.h"
#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)
#include "errno.h"
#include "string.h"
#include "sys/sysinfo.h"
#include "time.h"

#elif defined(VLIB_PLATFORM_NT)
#include "mderror.h"
#include "timeapi.h"
#include "stdio.h"

#else
#error implement

#endif

//SECTION(V): console

//#define MDCON_RUN_DEBUG

//NOTE(V): I don't know if i want to implement the console with TLS because we are not logging *that mutch* and we can dissable it
//TODO(V): Make atomic when we do proper multithreading on console
internal bool DisruptCheat = false;

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

		case mdConSeverity_assert:
			return "Assert";

	}
	return "";

}

void mdConStateCreate(mdConState* State, const char* Name) {
	vset(State, 0, sizeof(mdConState));
	State->HtAlloc = dpow2(MD_CON_STATE_DEFAULT_CAPACITY);
	//State->HtSize = 0;
	State->HtPtr = (mdConVar*)dcalloc(sizeof(mdConVar), dpow2(MD_CON_STATE_DEFAULT_CAPACITY));
	if (State->HtPtr == NULL) {
		VASSERT(0, "Failed to allocate memory for mdConState ConVar buffer creation");
//        NOTE(V): Malloc failure
		return;

	}

	//vset(State->HtPtr, 0, sizeof(mdConVar) * dpow2(MD_CON_STATE_DEFAULT_CAPACITY));

	//State->EntryAlloc = dpow2(MD_CON_STATE_DEFAULT_CAPACITY);
	//State->
	//State->EntryPtr = (mdConEntry*)vcalloc(sizeof(mdConEntry), dpow2(MD_CON_STATE_DEFAULT_CAPACITY));
	//if (State->EntryPtr == NULL) {
		//VASSERT(0, "Failed to allocate memory for mdConState entry buffer creation");
		//return;

	//}

	State->OutAlloc = MD_CON_STATE_DEFAULT_OUT_LENGTH;
	State->OutSize = 0;
	State->Out = (char*)dalloc(State->OutAlloc);
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
			dfree((void*)State->HtPtr[v].Name);

		}
		if (State->HtPtr[v].Type == mdConVarType_Str) {
			dfree((void*)State->HtPtr[v].Var.VarStr);

		}

	}

	//for (u64 v = 0; v < State->EntryAlloc; v++) {
		//if (State->EntryPtr[v].Message != NULL) {
			//vfree((void*)State->EntryPtr[v].Message);

		//}

	//}

	dfree((void*)State->HtPtr);
	//vfree((void*)State->EntryPtr);
	dfree((void*)State->Out);
	vset(State, 0, sizeof(mdConState));

}

//#define MD_CON_SEARCH_DEBUG

mdConVar* mdConStateSearchVar(mdConState* State, const char* Name) {
	u64 Hash = vfnv64std(Name, vstrlen8(Name));
	st Index = (st)(Hash & (u64)(State->HtAlloc - 1));

	#ifdef MD_CON_SEARCH_DEBUG
	st DebugIter = 0;
	#endif

	while (State->HtPtr[Index].Name != NULL) {
		if (vLEGACYstrcmp(Name, State->HtPtr[Index].Name) == 0) {
			return &(State->HtPtr[Index]);

		}

		#ifdef MD_CON_SEARCH_DEBUG
		VVERBOSE("Console", "Could not find variable at try {st}, Moving to next index", DebugIter);
		DebugIter++;
		#endif

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
		NewNamePtr = (char*)dcalloc(vstrlen8(Entry->Name) + 1, sizeof(char));
		if (NewNamePtr == NULL) {
			return 0;

		}
		vcpy(NewNamePtr, Entry->Name, vstrlen8(Entry->Name));
		NewNamePtr[vstrlen8(Entry->Name)] = 0;

		(*Length)++;

	}
	else {
//        TODO(V): Dump con state to selfe here to make debugging easyer if dumping state dose not change state
		VASSERT(0, "The con state is probabelly corupted");

	}

	Entries[Index].Name = NewNamePtr;
	Entries[Index].Var = Entry->Var;
	Entries[Index].Flags = Entry->Flags;
	Entries[Index].Type = Entry->Type;
	char DebugToStr[2048] = "\0";
	//mdConVarToStr(&(Entries[Index]), DebugToStr, 2048);
	#ifdef MDCON_RUN_DEBUG
	VVERBOSE("Console", "Type flags for setting cvar {u32} and db {u32} index {st} state {cstr} int {i64} {i64}", Entry->Type, Entries[Index].Type, Index, DebugToStr, Entries[Index].Var.VarInt, Entry->Var.VarInt);
	#endif
	Entries[Index].Help = Entry->Help;
	Entries[Index].StatePtr = StatePtr;
	Entries[Index].CallbackPtr = Entry->CallbackPtr;

	return Index;

}

void mdConStateResize(mdConState* State) {
	if ((State->HtAlloc / 2) > State->HtSize) {
		return;

	}

	const st OldSize = State->HtAlloc;
	st NewSize = dpow2(State->HtAlloc + 1);
	if (NewSize < State->HtAlloc) {
		return;

	}

	#ifdef MDCON_RUN_DEBUG
	VVERBOSE("Console", "Resizing console with state {p} size old {st} new {st}", State, State->HtAlloc, NewSize);
	#endif

	mdConVar* NewVars = (mdConVar*)dcalloc(sizeof(mdConVar), NewSize);
	if (NewVars == NULL) {
		return;

	}
	//vset(NewVars, 0, sizeof(mdConVar) * NewSize);

	st NewLength = 0;
	for (st v = 0; v < OldSize; v++) {
		mdConVar OldVar = State->HtPtr[v];
		if (OldVar.Name != NULL) {
			mdConStateSetEntry(NewVars, NewSize, &OldVar, &NewLength, State);

		}

	}

	dfree((void*)State->HtPtr);
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

	//if (State->HtAlloc <= State->HtSize) {
	mdConStateResize(State);

	//}

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
	mdConStatePrint(State, "Dunia", "Dumping all CVAR's to self", mdConSeverity_info);
	st Count = 0;

	for (st v = 0; v < State->HtAlloc; v++) {
		if (State->HtPtr[v].Name != NULL) {
			#ifdef MDCON_RUN_DEBUG
			VVERBOSE("Console", "Printing state {st}", v);
			#endif
			char Buff[2048] = { 0 };
			mdConVarToStr(&(State->HtPtr[v]), Buff, 2048);
			if (Buff [0] != NULL) {
				mdConStatePrint(State, "Dunia", Buff, mdConSeverity_info);

			}

			Count++;

		}

	}

	mdConStateFmt(State, "Dunia", "Found {st} CVAR's", mdConSeverity_info, Count);

}

void mdConStateOutNullStr(mdConState* State, const char* Str) {
	mdConStateOut(State, Str, vstrlen8(Str));

}

void mdConStateOut(mdConState* State, const char* Str, st Size) {
	#ifndef VLIB_NO_STDOUT_MDCONSTATE_OUT_LOGGING
	char SystemFmt[Size + 256];
	//    TODO(V): Make it so we input the size of the string with something
	//     like {cstr:sizearg} where we pass another arg to be the size
	vformat8("[{cstr}] {cstr}", SystemFmt, Size + 256, State->Name, Str);
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
	char* NewPtr = (char*)dalloc(NewSize);
	if (NewPtr == NULL) {
		return;

	}

	vset(NewPtr, 0, NewSize);
	vcpy(NewPtr, State->Out, State->OutSize);

	dfree((void*)State->Out);
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

	char UTC[64];
	//mdTimeToStr(mdTimeGetMicroSystemTime(), UTC);
	mdCurrentSystemTimeStr(UTC, 64);
	char LOCAL[64];
	mdCurrentSystemTimeStr(LOCAL, 64);
	//mdTimeToStr(mdTimeGetMicroSystemTime(), LOCAL);
	//    TODO(V): Make it so we handle timezones for this

	char Buffer[1024];
	vformat8("DISRUPT log start\nUTC Time: [{cstr}Z] LocalTime: [{cstr}]\n\n", Buffer, 1024, UTC, LOCAL);
	mdConStateOutNullStr(State, Buffer);

}

u32 mdConSanitizeInFlags(u32 InFlags) {
//    TODO(V): Implement !!!!!!!!!!!!!!!!
	return 0;
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

#ifdef _WIN32

void mdConLateStdoutInit() {
	mdConStart();
	vsys_writeConsoleNullStr(DuniaConsole.Out);
	VDLOG("Console", "Copy'd {st} characters from DISRUPT Console's back buffer to STDOUT", DuniaConsole.OutSize);

}

#endif

mdConState* mdConGetDisruptConsole() {
	return &DuniaConsole;

}

void mdConStatePrint(mdConState* State, const char* Subsystem, const char* Message, mdConSeverity Severity) {
	char OutStr[vstrlen8(Message) + vstrlen8(Subsystem) + 512];
	char OutTime[32];
	//mdTimeToStr(mdTimeGetMicroSystemTime(), OutTime);
	mdCurrentSystemTimeStr(OutTime, 32);
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
	//mdTimeToStr(mdTimeGetMicroSystemTime(), OutTime);
	mdCurrentSystemTimeStr(OutTime, 32);
	
	vformat8("{cstr}Z [{cstr}, {cstr}] {cstr}\n", OutStr, vstrlen8(UsrFmt) + 512,
			 OutTime , Subsystem, mdConSeverityGetUserStr(Severity), UsrFmt);
	//mdConLog(OutStr);
	mdConStateOutNullStr(State, OutStr);

}

void mdConStateFmt(mdConState* State, const char* Subsystem, const char* Message, mdConSeverity Severity, ...) {
	v_varargList Args;
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wvarargs"
	v_varargStart(Args, Severity);
	#pragma clang diagnostic pop

	mdConStateFmtImpl(State, Subsystem, Message, Severity, Args);
	v_varargEnd(Args);

}

void mdConLogInternFmt_DO_NOT_USE(const char* Subsystem, const char* Message, mdConSeverity Severity, ...) {
	mdConStart();
	v_varargList Args;
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wvarargs"
	v_varargStart(Args, Severity);
	#pragma clang diagnostic pop

	mdConStateFmtImpl(&DuniaConsole, Subsystem, Message, Severity, Args);
	
	v_varargEnd(Args);

}

void mdConLogIntern_DO_NOT_USE(const char* Subsystem, const char* Message, mdConSeverity Severity) {
	mdConStart();
	mdConStatePrint(&DuniaConsole, Subsystem, Message, Severity);

}

void mdConStateLogInternFmt_DO_NOT_USE(mdConState* State, const char* Subsystem, const char* Message, mdConSeverity Severity, ...) {
	mdConStart();
	v_varargList Args;
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wvarargs"
	v_varargStart(Args, Severity);
	#pragma clang diagnostic pop

	mdConStateFmtImpl(State, Subsystem, Message, Severity, Args);
	
	v_varargEnd(Args);

}

void mdConStateLogIntern_DO_NOT_USE(mdConState* State, const char* Subsystem, const char* Message, mdConSeverity Severity) {
	mdConStart();
	mdConStatePrint(State, Subsystem, Message, Severity);

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

bool mdConVarRunCommandPtr(mdConVar* Var, const char* Args){
	if (!Var) {
		VASSERT(0, "Bad ptr passed in");
		return false;

	}

	if (!Args) {
		VASSERT(0, "Bad ptr passed in");
		return false;

	}

	if (Var->Type != mdConVarType_Command) {
		VASSERT(0, "Trying to execute command on CVar of other type");
		mdConStatePrint((mdConState*)Var->StatePtr, "Console", "Trying to execute command on CVar of other type", mdConSeverity_error);
		return false;

	}

	Var->Flags |= mdConVarFlags_WAS_EXECUTED;

	bool VarResult = false;
	if (Var->Var.VarCmd != NULL) {
		VarResult = Var->Var.VarCmd(Args, Var->StatePtr, Var);

	}
	else {
		mdConStatePrint((mdConState*)Var->StatePtr, "Console", "Null ptr for function pointer inside CVar command", mdConSeverity_error);
		return false;

	}

	if (VarResult == true) {
		Var->Flags |= mdConVarFlags_LAST_RESULT;

	}
	else {
		Var->Flags = Var->Flags & ~mdConVarFlags_LAST_RESULT;

	}

	return VarResult;

}

bool mdConVarSetStrParsed(mdConVar* Var, const char* Args) {
	if (vstrlen8(Args) != 0) {
		if (Args[0] == '?' || Args[1] == '?') {
			mdConStateFmt((mdConState*)Var->StatePtr, "Console", "{cstr} : {cstr}", mdConSeverity_dataInfo, Var->Name, Var->Var.VarStr);
			return true;

		}

	}

	if ((Var->Flags & mdConVarFlags_WRITE_PROTECTED) == mdConVarFlags_WRITE_PROTECTED) {
		mdConStatePrint((mdConState*)Var->StatePtr, "Console", "Cannot change value of write protected CVar", mdConSeverity_error);
		mdConStateFmt((mdConState*)Var->StatePtr, "Console", "{cstr} : {cstr}", mdConSeverity_dataInfo, Var->Name, Var->Var.VarStr);
		return false;

	}

	bool Result = mdConVarSetStrPtr(Var, Args);

	if (Result == true) {
		mdConStateFmt((mdConState*)Var->StatePtr, "Console", "{cstr} = {cstr}", mdConSeverity_dataInfo, Var->Name, Var->Var.VarStr);

	}

	return Result;

}

bool mdConVarSetStrPtr(mdConVar* Var, const char* Args) {
	if (!Var) {
		VASSERT(0, "Bad ptr passed in");
		return false;

	}

	if (!Args) {
		VASSERT(0, "Bad ptr passed in");
		return false;

	}

	if (Var->Type != mdConVarType_Str) {
		VASSERT(0, "Trying to change string CVar of other type");
		mdConStatePrint((mdConState*)Var->StatePtr, "Console", "Trying to change string CVar of other type", mdConSeverity_error);
		return false;

	}

//    NOTE(V): This has being moved somewhere else inside the parse functions because we don't want to prevent code from writing to it
	/*if (mdConVarFlags_WRITE_PROTECTED == (Var->Flags & mdConVarFlags_WRITE_PROTECTED)) {
		mdConStatePrint((mdConState*)Var->StatePtr, "Console", "Cannot change CVar, its write protected", mdConSeverity_error);
		return false;

	}*/

	mdConVar OldState = *Var;

	const st NewStrLen = vstrlen8(Args);
	char* NewStr = (char*)dalloc(NewStrLen + 1);
	vset(NewStr, 0, NewStrLen);
	vcpy(NewStr, Args, NewStrLen);
	NewStr[NewStrLen] = 0;
	Var->Var.VarStr = NewStr;

	if (Var->CallbackPtr != NULL) {
		mdConVarCallback Callback = (mdConVarCallback)Var->CallbackPtr;
		bool CallbackResult = Callback(Var, &OldState);
		if(CallbackResult == true){
			Var->Flags |= mdConVarFlags_LAST_RESULT;

		}
		else {
			Var->Flags = Var->Flags & ~mdConVarFlags_LAST_RESULT;

		}

	}
	else {
		Var->Flags |= mdConVarFlags_LAST_RESULT;

	}

	if (OldState.Var.VarStr != NULL) {
		dfree((void*)OldState.Var.VarStr);
		//VASSERT(OldState.Var.VarStr == NULL, "Could not free old string from heap");

	}

	return true;

}

bool mdConVarSetIntParsed(mdConVar* Var, const char* Args) {
	if (vstrlen8(Args) != 0) {
		if (Args[0] == '?' || Args[1] == '?') {
			mdConStateFmt((mdConState*)Var->StatePtr, "Console", "{cstr} : {i64}", mdConSeverity_dataInfo, Var->Name, Var->Var.VarInt);
			return true;

		}

	}

	if ((Var->Flags & mdConVarFlags_WRITE_PROTECTED) == mdConVarFlags_WRITE_PROTECTED) {
		mdConStatePrint((mdConState*)Var->StatePtr, "Console", "Cannot change value of write protected CVar", mdConSeverity_error);
		mdConStateFmt((mdConState*)Var->StatePtr, "Console", "{cstr} : {i64}", mdConSeverity_dataInfo, Var->Name, Var->Var.VarInt);
		return false;

	}

	i64 ParserResult = 0;
	bool ParseSuccedded = vconargtoi64(Args, vstrlen8(Args), &ParserResult);
	if (ParseSuccedded == false) {
		VSERR((mdConState*)Var->StatePtr, "Console", "Could not parse integer expression trying to set \"{cstr}\"", Var->Name);
		return false;

	}

	bool Result = mdConVarSetIntPtr(Var, ParserResult);
	if (Result == true) {
		mdConStateFmt((mdConState*)Var->StatePtr, "Console", "{cstr} = {i64}", mdConSeverity_dataInfo, Var->Name, Var->Var.VarInt);

	}

	return Result;

}

bool mdConVarSetIntPtr(mdConVar* Var, const i64 WantedValue) {
	if (!Var) {
		VASSERT(0, "Bad ptr passed in");
		return false;

	}

	if (Var->Type != mdConVarType_Int) {
		VASSERT(0, "Trying to change int cvar to other type");
		mdConStatePrint((mdConState*)Var->StatePtr, "Console", "Trying to change int CVar of other type", mdConSeverity_error);
		return false;

	}

	mdConVar OldState = *Var;

	/*
	i64 ParseResult = 0;
	bool ParseSucceded = vconargtoi64(Args, vstrlen8(Args), &ParseResult);
	if (ParseSucceded == false) {
		VSERR((mdConState*)Var->StatePtr, "Console", "Could not parse integer expression trying to set \"{cstr}\"", Var->Name);
		return false;

	}*/

	Var->Var.VarInt = WantedValue;

	if (Var->CallbackPtr != NULL) {
		mdConVarCallback Callback = (mdConVarCallback)Var->CallbackPtr;
		bool CallbackResult = Callback(Var, &OldState);
		if(CallbackResult == true){
			Var->Flags |= mdConVarFlags_LAST_RESULT;

		}
		else {
			Var->Flags = Var->Flags & ~mdConVarFlags_LAST_RESULT;

		}

	}
	else {
		Var->Flags |= mdConVarFlags_LAST_RESULT;

	}


	return true;

}

void mdConGetArgsFromStr(const char* In, char* Out) {
	const st InLen = vstrlen8(In);
	for (st v = 0; v < InLen; v++) {
		if (*In == 0) {
			break;

		}

		if (*In == ' ') {
			In++;
			break;

		}

		In++;

	}

	st OutSize = 0;
	for (st v = 0; v < vstrlen8(In); v++) {
		Out[v] = In[v];
		OutSize++;

	}

	Out[OutSize] = 0;

}

#define MDCONSTATERUN_CHECK_BAD_CHAR(Char) { const char* Str = Char;  \
if (vischarpresent8(Cmd, *Str)) { \
mdConStatePrint(State, "Console", "Failed to parse command, found \"" Char "\" character in name", mdConSeverity_error); return false; } }


bool mdConStateRunStr(mdConState* State, const char* InCmd, bool BypassCheat) {
	if (BypassCheat == false) {
		mdConStatePrint(State, "Console", InCmd, mdConSeverity_info);

	}

	const st CmdSize = vstrlen8(InCmd);
	char Cmd[CmdSize];
	vgetfirstsubstr8(InCmd, ' ', Cmd, CmdSize);
	//VVERBOSE("Testing", "Cmd {cstr}", Cmd);

	MDCONSTATERUN_CHECK_BAD_CHAR(",");
	MDCONSTATERUN_CHECK_BAD_CHAR("\"");
	MDCONSTATERUN_CHECK_BAD_CHAR("$");
	MDCONSTATERUN_CHECK_BAD_CHAR("(");
	MDCONSTATERUN_CHECK_BAD_CHAR(")");
	MDCONSTATERUN_CHECK_BAD_CHAR("\\");
	MDCONSTATERUN_CHECK_BAD_CHAR("`");
	MDCONSTATERUN_CHECK_BAD_CHAR("~");

	mdConVar* Var = mdConStateSearchVar(State, Cmd);
	if (Var == NULL) {
		mdConStatePrint(State, "Console", "Could not find command", mdConSeverity_error);
		return false;

	}

	if (Var->StatePtr != State) {
		mdConStatePrint(State, "Console", "Corupted console state", mdConSeverity_error);
		return false;

	}

	if ((Var->Flags & mdConVarFlags_CHEAT) == mdConVarFlags_CHEAT) {
		if (!BypassCheat) {
			if (DisruptCheat == false) {
				mdConStateFmt(State, "Console", "Cannot execute cheat command \"{cstr}\" with cheats dissabled", mdConSeverity_error, Cmd);
				return false;

			}

		}

	}

	char OutArgs[CmdSize];
	vset(OutArgs, 0, CmdSize);
	mdConGetArgsFromStr(InCmd, OutArgs);
	#ifdef MDCON_RUN_DEBUG
	VVERBOSE("Console", "Executing command {cstr} with args \"{cstr}\"", Cmd, OutArgs);
	#endif

	//    TODO(V): Implement flags like mdConVarFlags_WRITE_PROTECTED !!!!

	switch (Var->Type) {
		case(mdConVarType_none):
			mdConStatePrint(State, "Console", "CVar has no type", mdConSeverity_error);
			return false;

		case(mdConVarType_Command):
			return mdConVarRunCommandPtr(Var, OutArgs);

		case(mdConVarType_Str):
			return mdConVarSetStrParsed(Var, OutArgs);

		case(mdConVarType_Double):
			//return mdConVarSetDoublePtr(Var, OutArgs);

		case(mdConVarType_Int):
			return mdConVarSetIntParsed(Var, OutArgs);

		default:
			mdConStateFmt(State, "Console", "Bad datatype on CVAR. Got {u64} for type enum", mdConSeverity_error, Var->Type);
			return false;

	}

}

internal bool mdConCheckIfPresent(mdConState* State, const char* Name) {
	mdConVar* OldVar = mdConStateSearchVar(State, Name);
	if (OldVar != NULL) {
		mdConStateFmt(State, "Console", "Cannot register console command/CVar \"{cstr}\" that allready exists",
					  mdConSeverity_dataError, Name);
		VASSERTNF(0);
		return true;

	}

	return false;

}

void mdConStateCmdRegister(mdConState* State, const char* Name, mdConCmdFunc Func, u32 Flags, const char* Help) {

	#ifdef MDCON_RUN_DEBUG
	VVERBOSE("Console", "Registering console command {cstr}", Name);
	#endif

	if (!State) {
		VASSERT(0, "Bad ptr");
		return;

	}

	if (!Name) {
		VASSERT(0, "Bad ptr");
		return;

	}


	st NameLength = vstrlen8(Name);
	//mdConStateFmt(State, "Console", "Name is {cstr} length {st}", mdConSeverity_verbose, Name, NameLength);
	if (NameLength != 0) {
		/*
		mdConVar* PossibleOldVar = mdConStateSearchVar(State, Name);
		if (PossibleOldVar != NULL) {
			mdConStatePrint(State, "Console", "Cannot register console command that allready exist", mdConSeverity_dataError);
			VASSERTNF(0);
			return;

		}*/

		if (mdConCheckIfPresent(State, Name)) {
			return;

		}

		Flags = mdConSanitizeInFlags(Flags);

		mdConVar NewVar;
		NewVar.Var.VarCmd = Func;
		NewVar.Flags = Flags;
		NewVar.Type = mdConVarType_Command;
		NewVar.Name = Name;
		NewVar.Help = Help;
		NewVar.StatePtr = State;
		NewVar.CallbackPtr = NULL;

		mdConStateSet(State, &NewVar);

		return;

	}
	else {
		mdConStatePrint(State, "Console", "Cannot register console command with empty name", mdConSeverity_dataError);
		VASSERTNF(0);
		return;

	}

}

void mdConStateStrRegister(mdConState* State, const char* Name, const char* Value, u32 Flags, const char* Help, mdConVarCallback Callback) {
	if (!State) {
		VASSERT(0, "Bad ptr");
		return;

	}

	if (!Name) {
		VASSERT(0, "Bad ptr");

	}

	if (vstrlen8(Name) != 0) {
		if (mdConCheckIfPresent(State, Name)) {
			return;

		}

		Flags = mdConSanitizeInFlags(Flags);

		const st ValueLength = vstrlen8(Value);
		mdConVar NewVar;
		NewVar.Var.VarStr = (char*)dalloc(ValueLength);
		vset(NewVar.Var.VarStr, 0, ValueLength);
		vcpy(NewVar.Var.VarStr, Value, ValueLength);
		NewVar.Flags = Flags;
		NewVar.Type = mdConVarType_Str;
		NewVar.Name = Name;
		NewVar.Help = Help;
		NewVar.StatePtr = State;
		NewVar.CallbackPtr = (void*)Callback;

		mdConStateSet(State, &NewVar);
		return;

	}
	else {
		mdConStatePrint(State, "Console", "Cannot register CVar with empty name", mdConSeverity_dataError);
		VASSERTNF(0);
		return;

	}

}

void mdConStateIntRegister(mdConState* State, const char* Name, i64 Value, u32 Flags, const char* Help, mdConVarCallback Callback) {
	if (!State) {
		VASSERT(0, "Bad ptr");
		return;

	}

	if (!Name) {
		VASSERT(0, "Bad ptr");
		return;

	}

	if (vstrlen8(Name) != 0) {
		if (mdConCheckIfPresent(State, Name)) {
			return;

		}

		Flags = mdConSanitizeInFlags(Flags);

		mdConVar NewVar;
		NewVar.Var.VarInt = Value;
		NewVar.Flags = Flags;
		NewVar.Type = mdConVarType_Int;
		NewVar.Name = Name;
		NewVar.Help = Help;
		NewVar.StatePtr = State;
		NewVar.CallbackPtr = (void*)Callback;

		if (Callback == NULL) {
			NewVar.Flags |= mdConVarFlags_LAST_RESULT;

		}

		mdConStateSet(State, &NewVar);

		return;

	}
	else {
		mdConStatePrint(State, "Console", "Cannot register CVar with emtpy name", mdConSeverity_dataError);
		VASSERTNF(0);
		return;

	}

}

//TODO(V): I found a bug when crating 10000 CVars and then deleteng all of them sometimes it would fail ?? and mdConStateSearchVar is fine two ??
void mdConStateDeleteVar(mdConState* State, const char* Name) {
	mdConVar* ConVar = mdConStateSearchVar(State, Name);
	if (ConVar == NULL) {
		VSWARN(State, "Console", "Failed to delete console variable with name \"{cstr}\"", Name);
		return;

	}
	else {
		//VSVERBOSE(State, "Testing", "Found {cstr}", Name);

	}

	if ((ConVar->Flags & mdConVarFlags_DO_NOT_DELETE) == mdConVarFlags_DO_NOT_DELETE) {
		VSWARN(State, "Console", "Tried to delete console variable \"{cstr}\" because it was marked not for delete", Name);
		return;

	}

	if (ConVar->Type == mdConVarType_Str) {
		dsafefree((void*)ConVar->Var.VarStr);
		//dfree((char*)ConVar->Var.VarStr);

	}
	dsafefree((void*)ConVar->Name);

	vset(ConVar, 0, sizeof(mdConVar));

}

void mdConVarToStr(mdConVar* Var, char* Buffer, st BufferSize) {
	if (Var->Name != NULL) {
		//vformat8("mdConVar VarInt \"{i64}\" Var raw \"{p}\" Flags \"{u64:hex}\" type mdConVarType \"{u32}\" \"{u64}\" name \"#cstr}\" help \"#cstr}\" StatePtr {p} CallbackPtr {p}",
				 //Buffer, BufferSize,
				 //Var->Var.VarInt, Var->Var.VarDouble, Var->Flags, Var->Flags,
				 //Var->Type, Var->Type,
				 //Var->Name, Var->Help,
				 //Var->StatePtr, Var->CallbackPtr);

		#if 0
		if (Var->Help == NULL) {
			return;

		}
		#endif

		vformat8("	mdConVar raw {p} Flags {u32:hex} Type {u32} Name \"{cstr}\" Help \"{cstr}\"",
				 Buffer, BufferSize,
				 Var->Var, Var->Flags, Var->Type, Var->Name, Var->Help);

	}

	//if (Var->Name != NULL) {
		//vformat8("mdConVar VarInt \"{i64}\"",
				 //Buffer, BufferSize,
				 //Var->Var.VarInt);

	//}

}

void mdConVarRegisterStr(const char* Name, const char* Value, const u32 Flags, const char* Help, mdConVarCallback Cb) {
	mdConStart();
	mdConStateStrRegister(&DuniaConsole, Name, Value, Flags, Help, Cb);

}

void mdConVarRegisterInt(const char* Name, i64 Value, const u32 Flags, const char* Help, mdConVarCallback Cb) {
	mdConStart();
	mdConStateIntRegister(&DuniaConsole, Name, Value, Flags, Help, Cb);

}

void mdConVarDelete(const char* Name) {
	mdConStateDeleteVar(&DuniaConsole, Name);

}

void mdConVarSetInt(const char* Name, const i64 Value) {
	mdConVar* VarPtr = mdConStateSearchVar(&DuniaConsole, Name);
	if (VarPtr == NULL) {
		VERR("Console", "Failed to find console variable {cstr}", Name);
		VASSERTNF(0);
		return;

	}

	mdConVarSetIntPtr(VarPtr, Value);

}

void mdConFlush() {
//    TODO(V): Implement

}

void mdConCmdRegister(const char* Name, mdConCmdFunc Func, const u32 Flags, const char* Help) {
	mdConStart();
	mdConStateCmdRegister(&DuniaConsole, Name, Func, Flags, Help);

}

void mdConCmdReg(const char* Name, mdConCmdTypedFunc Func, const u32 Flags, const char* Help) {
	mdConStart();
	mdConStateCmdRegister(&DuniaConsole, Name, (mdConCmdFunc)Func, Flags, Help);

}

#ifdef VLIB_PLATFORM_NT
#define CON_WIN_API_CALL(WindowsCallFunc) {\
BOOL ResultOfApi = WindowsCallFunc;\
if (ResultOfApi == 0) {\
VDERR("Console", "Failed call \"{cstr}\" to WIN32 api with error \"{werr}\"", #WindowsCallFunc);\
return;\
}\
}

void mdConWin32Console(st Vertical, st Horizontal) {
	VDLOG("Console", "Atempting to create a WIN32 terminal to dump engine log to with size {st}v {st}h", Vertical, Horizontal);
	BOOL AllocResult = AllocConsole();

	if (AllocResult == 0) {
		VDERR("Console", "Failed to create WIN32 terminal with error {werr} size {st}v {st}h", Vertical, Horizontal);
		return;

	}

	//    NOTE(V): Adjust size
	{
		CONSOLE_SCREEN_BUFFER_INFO BufInfo;
		CON_WIN_API_CALL(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo));
		if (BufInfo.dwSize.X < Horizontal) {
			BufInfo.dwSize.X = Horizontal;

		}

		if (BufInfo.dwSize.Y < Vertical) {
			BufInfo.dwSize.Y = Vertical;

		}

		CON_WIN_API_CALL(SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), BufInfo.dwSize));

	}

	//    NOTE(V): Redirect STDOUT to it
	{
		FILE* FileHandle = NULL;
		if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE) {
			if (freopen_s(&FileHandle, "CONOUT$", "w", stdout) != 0) {
				VDERRNF("Console", "Failed to redirect the stdout to newly created console");
				return;

			}
			else {
				setvbuf(stdout, NULL, _IONBF, 0);

			}

		}
		else {
			VDERRNF("Console", "Failed to get stdout windows handle");

		}

		if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE) {
			if (freopen_s(&FileHandle, "CONOUT$", "w", stderr) != 0) {
				return;

			}
			else {
				setvbuf(stderr, NULL, _IONBF, 0);

			}

		}
		else {
			VDERRNF("Console", "Failed to get stderr windows handle");

		}

	}

	//printf("Testing logging\n");
	//fprintf(stderr, "Testing stderr\n");
	//vsys_writeConsoleNullStr("Testing logging with kernel functions\n");
	mdConLateStdoutInit();
	VDLOG("Console", "Sucessfully initialized WIN32 terminal for engine logging");

}

#endif

void mdConExecuteCmd(const char* Cmd) {
	mdConStateRunStr(&DuniaConsole, Cmd, true);

}

void DO_NOT_USE_mdConUSERExecuteCmd(const char* Cmd) {
	mdConStateRunStr(&DuniaConsole, Cmd, false);

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
/*
void mdTimeToStr(i64 Time, char* Buffer) {
//    TODO(V): Implement
	vinttostr8(Time, Buffer, 24);

}*/

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
	mdCallOnce(&CallOnceTime, mdTimeInitIngernal);

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

void mdCurrentSystemTimeStr(char* Buffer, st Size) {
	if (Size < 32) {
		return;

	}

	SYSTEMTIME WinTime;
	GetSystemTime(&WinTime);
	vformat8("{u16}-{u16}-{u16}T{u16}:{u16}:{u16}.{u16}", Buffer, Size,
			 WinTime.wYear, WinTime.wMonth, WinTime.wDay,
			 WinTime.wHour, WinTime.wMinute, WinTime.wSecond, WinTime.wMilliseconds);

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

mdsoHandle mdsoOpen(const char* Name, const mdsoFlags Flags) {
	void* Result = NULL;
	int GnuFlags = 0;
	if ((Flags & mdsoFlags_lazyBind) == mdsoFlags_lazyBind) {
		GnuFlags |= RTLD_LAZY;

	}
	else {
		GnuFlags |= RTLD_NOW;

	}

	if ((Flags & mdsoFlags_dontLoad) == mdsoFlags_dontLoad) {
		VDWARN("SharedObject", "Using mdsoFlags_dontLoad is deprecated, please use DISRUPT core to see if module is loaded or not !!!");
		GnuFlags |= RTLD_NOLOAD;

	}

	if ((Flags & mdsoFlags_localSymbols) == mdsoFlags_localSymbols) {
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
	else {
		VDLOG("SharedObject", "Loaded library {cstr} with flags {u32:hex} sucessfully", Name, Flags);

	}

	return Result;

}

void* mdsoGetFunc(mdsoHandle Handle, const char* Symbol) {
	void* Result = NULL;
	Result = dlsym((void*)Handle, Symbol);
	if (Result == NULL) {
		char* ErrorStr = dlerror();
//        TODO(V): Add code to get the name of the library that is failing and report it
		VDERR("SharedObject", "Failed to load function from library with error \"{cstr\"", ErrorStr);
		return NULL;

	}

	return Result;

}

void mdsoClose(mdsoHandle Handle) {
	dlclose((void*)Handle);

}

#elif defined(VLIB_PLATFORM_NT)
mdsoHandle mdsoOpen(const char* Name, const mdsoFlags Flags) {
	if (Flags != 0) {
		VDWARN("SharedObject", "Flags for mdsoOpen do nothing on windows");

	}

	HMODULE Result;
	Result = LoadLibraryA(Name);

	if (Result == NULL) {
		DWORD Error = GetLastError();
		LPSTR ErrorStr = NULL;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
									 NULL, Error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&ErrorStr, 0, NULL);
		VDERR("SharedObject", "Failed to load library {cstr} flags {u32:hex} with error \"{cstr}\"", Name, Flags, ErrorStr);
		LocalFree(ErrorStr);
		return NULL;

	}
	else {
		VDLOG("SharedObject", "Loaded library {cstr} with flags {u32:hex} sucessfully", Name, Flags);
		return (mdsoHandle)Result;

	}

}

void* mdsoGetFunc(mdsoHandle Handle, const char* Symbol) {
	void* Result = NULL;
	Result = (void*)GetProcAddress((HMODULE)Handle, Symbol);
	if (Result == NULL) {
		DWORD Error = GetLastError();
		LPSTR ErrorStr = NULL;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
									 NULL, Error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&ErrorStr, 0, NULL);
		VDERR("SharedObject", "Failed to load function \"{cstr}\" from library with error \"{cstr}\"", Symbol, ErrorStr);
		LocalFree(ErrorStr);
		return NULL;

	}

	return Result;

}

void mdsoClose(mdsoHandle Handle) {
	BOOL Result = FreeLibrary((HMODULE)Handle);
	if (Result == 0) {
		DWORD Error = GetLastError();
		LPSTR ErrorStr = NULL;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
									 NULL, Error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&ErrorStr, 0, NULL);
		VDERR("SharedObject", "Failed to unload shared object with err \"{cstr}\"", ErrorStr);
		LocalFree(ErrorStr);

	}

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

#elif defined(VLIB_PLATFORM_NT)
//TODO(V): Implement

#else
#error Implement platform

#endif

//SECTION(V): Init

void mdosInit() {
	mdConStart();

}

void mdosExit() {
	mdConEnd();

}
