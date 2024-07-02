////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   mdos.h
//  Version:     v1.00
//  Created:     11/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"

#ifndef _MDOS_H_
#define _MDOS_H_

VLIB_CABI

const char* mdosGetArt(u32 Index);
void mdosPrintTermHeader();

VLIB_CABIEND

#endif

//SECTION(V): console

#define MDTIME_API
#define MDCON_API

enum mdConVarFlags {
	mdConVarFlags_USER MYTH_BIT(0),
	mdConVarFlags_SAVE MYTH_BIT(16),
	mdConVarFlags_CHEAT MYTH_BIT(17),
	mdConVarFlags_WRITE_PROTECTED MYTH_BIT(18),
	mdConVarFlags_REQUIRE_APP_REBOOT MYTH_BIT(19),
	mdConVarFlags_MODIFIED MYTH_BIT(20),
	mdConVarFlags_WAS_IN_CONFIG MYTH_BIT(21),
	mdConVarFlags_CREATED_THIS_INSTANCE MYTH_BIT(22),
	mdConVarFlags_INVISIBLE MYTH_BIT(23),

	mdConVarFlags_SERIALIZE_FLAGS = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5)
	| (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11) | (1 << 12) | (1 << 13)
	| (1 << 14) | (1 << 15) // USER
	| (1 << 16) | (1 << 17) | (1 << 18) | (1 << 19) | (1 << 23),

};

typedef void(*mdConCmdFunc)(const char*);

VLIB_STRUCT(mdConVar)

union {
	i64 VarInt;
	char* VarStr;
	double VarDouble;
	mdConCmdFunc VarCmd;

} Var;

u64 Flags;
u64 Type;
const char* Name;
void* StatePtr;

VLIB_STRUCTEND(mdConVar)

typedef void(*mdConVarCallback)(mdConVar*);
#define MD_CON_STATE_DEFAULT_CAPACITY 128

#define MD_CON_ENTRY_SUBSYSTEM_STR_LENGTH 32

VLIB_STRUCT(mdConEntry)
const char* Message;
i64 Time;
u64 Severity;
char Subsystem[MD_CON_ENTRY_SUBSYSTEM_STR_LENGTH];

VLIB_STRUCTEND(mdConEntry)

VLIB_STRUCT(mdConState)
mdConVar* HtPtr;
st HtAlloc;
st HtSize;

mdConEntry* EntryPtr;
st EntryAlloc;
st EntrySize;

VLIB_STRUCTEND(mdConState)

typedef enum mdConSeverity {
	mdConSeverity_none = 0,
	mdConSeverity_verbose,
	mdConSeverity_info,
	mdConSeverity_warning,
	mdConSeverity_error,
	mdConSeverity_dataVerbose,
	mdConSeverity_dataInfo,
	mdConSeverity_dataWarning,
	mdConSeverity_dataError,
	mdConSeverity_bellwether,

} mdConSeverity;

typedef enum mdConVarType {
	mdConVarType_none = 0,
	mdConVarType_Str,
	mdConVarType_Double,
	mdConVarType_Int,

} mdConVarType;

VLIB_CABI
MDCON_API void mdConStateCreate(mdConState* State);
MDCON_API void mdConStateDestroy(mdConState* State);
MDCON_API mdConVar* mdConStateSearchVar(mdConState* State, const char* Name);
MDCON_API void mdConStateSetEntry(mdConVar* Entries, st Alloc, mdConVar* Entry, st* Length, mdConState* StatePtr);
MDCON_API void mdConStateResize(mdConState* State);
MDCON_API void mdConStateSet(mdConState* State, mdConVar* Var);

MDCON_API void mdConStart();
MDCON_API void mdConEnd();

MDCON_API void mdConVarRegisterStr(const char* Name, const char* Value, const u32 Flags, const char* Help, mdConVarCallback Cb);
MDCON_API void mdConVarRegisterDouble(const char* Name, const double* Value, const u32 Flags, const char* Help, mdConVarCallback Cb);
MDCON_API void mdConVarRegisterInt(const char* Name, const i64* Value, const u32 Flags, const char* Help, mdConVarCallback Cb);
MDCON_API void mdConVarDelete(const char* Name);
MDCON_API void mdConVarGetStr(const char* Name, char* Result);
MDCON_API double mdConVarGetDouble(const char* Name);
MDCON_API i64 mdConVarGetInt(const char* Name);
MDCON_API mdConVar* mdConVarGet(const char* Name);
MDCON_API void mdConVarSetStr(const char* Name, const char* Value);
MDCON_API void mdConVarSetDouble(const char* Name, const double* Value);
MDCON_API void mdConVarSetInt(const char* Name, const i64* Value);
MDCON_API void mdConVarSet(const char* Name, const void* Value, mdConVarType Type);
MDCON_API void mdConVarRegisterOrSetStr(const char* Name, const char* Value);
MDCON_API void mdConVarRegisterOrSetDouble(const char* Name, const double* Value);
MDCON_API void mdConVarRegisterOrSetInt(const char* Name, const i64* Value);
MDCON_API void mdConVarRegisterOrSet(const char* Name, const void* Value, mdConVarType Type);

MDCON_API st mdConGetNumCmd();
MDCON_API st mdConGetSortedCmd(char** Array, st ArraySize, st StringSize, const char* Prefix);

MDCON_API void mdConCmdRegister(const char* Name, mdConCmdFunc Func, const u32 Flags, const char* Help);
MDCON_API void mdConCmdDelete(const char* Name);

MDCON_API void mdConExecuteCmd(const char* Cmd);
MDCON_API void mdConAddCommandToHistory(const char* Command);
MDCON_API void mdConDeferedExecuteCmd(const char* Cmd);
MDCON_API void mdConPrint(const char* Message, i64 Time, mdConSeverity Severity);
MDCON_API st mdConGetLineCount();

MDCON_API void mdConCreateKeybind(const char* Cmd, const char* Res);
VLIB_CABIEND

//SECTION(V): System time

VLIB_CABI
MDTIME_API i64 mdTimeInt64MulDiv(i64 Val, i64 Num, i64 Denom);
MDTIME_API u32 mdTimeGetMsSystemTime();
MDTIME_API i64 mdTimeGetMicroSystemTime();
MDTIME_API u32 mdTimeGetUnixTime();
MDTIME_API i64 mdTimeGetTimerFreq();

VLIB_CABIEND

VLIB_STRUCT(mdTimeStopwatch)
u32 StartTime;

#ifdef VPP
void create();
void reset();
u32 getTime();

#endif

VLIB_STRUCTEND(mdTimeStopwatch)

#define mdTimePrecisewatch_MAX_HISTORY 60
VLIB_STRUCT(mdTimePrecisewatch)
i64 StartTime;
i64 Hystory[mdTimePrecisewatch_MAX_HISTORY];
u32 HistoryIndex;
#ifdef VPP
void create();
i64 getMicro();
i64 getAverageMicro();
float getSecond();
float getAverageSecond();
void reset();

#endif

VLIB_STRUCTEND(mdTimePrecisewatch)

VLIB_CABI
MDTIME_API void mdTimeCreateStopwatch(mdTimeStopwatch* Watch);
MDTIME_API void mdTimeResetStopwatch(mdTimeStopwatch* Watch);
MDTIME_API u32 mdTimeFromStopwatch(mdTimeStopwatch* Watch);

MDTIME_API void mdTimeCreatePrecisewatch(mdTimePrecisewatch* Watch);
MDTIME_API i64 mdTimeGetMicroFromPresicewatch(mdTimePrecisewatch* Watch);
MDTIME_API i64 mdTimeGetMicroAverageFromPresicewatch(mdTimePrecisewatch* Watch);
MDTIME_API float mdTimeGetSecondFromPresicewatch(mdTimePrecisewatch* Watch);
MDTIME_API float mdTimeGetSecondAverageFromPresicewatch(mdTimePrecisewatch* Watch);
MDTIME_API void mdTimeResetPresicewatch(mdTimePrecisewatch* Watch);

VLIB_CABIEND
