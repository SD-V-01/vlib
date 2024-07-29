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

#pragma once

#include "base_types.h"
#include "vstr32.h"

VLIB_CABI

const char* mdosGetArt(u32 Index);
void mdosPrintTermHeader();

VLIB_CABIEND

//SECTION(V): console

#define MDTIME_API
#define MDCON_API

#define VVERBOSE(Subsystem, Message, ...) mdConLogInternFmt_DO_NOT_USE(Subsystem, Message, mdConSeverity_verbose, __VA_ARGS__);
#define VVERBOSENF(Subsystem, Message) mdConLogIntern_DO_NOT_USE(Subsystem, Message, mdConSeverity_verbose);

#define VLOG(Subsystem, Message, ...) mdConLogInternFmt_DO_NOT_USE(Subsystem, Message, mdConSeverity_info, __VA_ARGS__);
#define VLOGNF(Subsystem, Message) mdConLogIntern_DO_NOT_USE(Subsystem, Message, mdConSeverity_info);

#define VWARN(Subsystem, Message, ...) mdConLogInternFmt_DO_NOT_USE(Subsystem, Message, mdConSeverity_warning, __VA_ARGS__);
#define VWARNNF(Subsystem, Message) mdConLogIntern_DO_NOT_USE(Subsystem, Message, mdConSeverity_warning);

#define VERR(Subsystem, Message, ...) mdConLogInternFmt_DO_NOT_USE(Subsystem, Message, mdConSeverity_error, __VA_ARGS__);
#define VERRNF(Subsystem, Message) mdConLogIntern_DO_NOT_USE(Subsystem, Message, mdConSeverity_error);

#define VBELLWETHER(Subsystem, Message, ...) mdConLogInternFmt_DO_NOT_USE(Subsystem, Message, mdConSeverity_bellwether, __VA_ARGS__);
#define VBELLWETHERNF(Subsystem, Message) mdConLogIntern_DO_NOT_USE(Subsystem, Message, mdConSeverity_bellwether);

#define VDVERBOSE(Subsystem, Message, ...) mdConLogInternFmt_DO_NOT_USE(Subsystem, Message, mdConSeverity_dataVerbose, __VA_ARGS__);
#define VDVERBOSENF(Subsystem, Message) mdConLogIntern_DO_NOT_USE(Subsystem, Message, mdConSeverity_dataVerbose);

#define VDLOG(Subsystem, Message, ...) mdConLogInternFmt_DO_NOT_USE(Subsystem, Message, mdConSeverity_dataInfo, __VA_ARGS__);
#define VDLOGNF(Subsystem, Message) mdConLogIntern_DO_NOT_USE(Subsystem, Message, mdConSeverity_dataInfo);

#define VDWARN(Subsystem, Message, ...) mdConLogInternFmt_DO_NOT_USE(Subsystem, Message, mdConSeverity_dataWarning, __VA_ARGS__);
#define VDWARNNF(Subsystem, Message) mdConLogIntern_DO_NOT_USE(Subsystem, Message, mdConSeverity_dataWarning);

#define VDERR(Subsystem, Message, ...) mdConLogInternFmt_DO_NOT_USE(Subsystem, Message, mdConSeverity_dataError, __VA_ARGS__);
#define VDERRNF(Subsystem, Message) mdConLogIntern_DO_NOT_USE(Subsystem, Message, mdConSeverity_dataError);

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
const char* Help;
void* StatePtr;
void* CallbackPtr;

VLIB_STRUCTEND(mdConVar)

typedef void(*mdConVarCallback)(mdConVar*);
#define MD_CON_STATE_DEFAULT_CAPACITY 64

//NOTE(V): Larger will not make mdConEntry fit inside a cache line witch would be bad
#define MD_CON_ENTRY_SUBSYSTEM_STR_LENGTH 40

#define MD_CON_STATE_NAME_LENGTH 32

#define MD_CON_STATE_DEFAULT_OUT_LENGTH 32768

VLIB_STRUCT(mdConState)
mdConVar* HtPtr;
st HtAlloc;
st HtSize;

//mdConEntry* EntryPtr;
//st EntryAlloc;
//st EntrySize;

char* Out;
st OutSize;
st OutAlloc;

char Name[MD_CON_STATE_NAME_LENGTH];

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
MDCON_API const char* mdConSeverityGetUserStr(mdConSeverity In);

MDCON_API void mdConStateCreate(mdConState* State, const char* Name);
MDCON_API void mdConStateDestroy(mdConState* State);
MDCON_API mdConVar* mdConStateSearchVar(mdConState* State, const char* Name);
MDCON_API st mdConStateSetEntry(mdConVar* Entries, st Alloc, mdConVar* Entry, st* Length, mdConState* StatePtr);
MDCON_API void mdConStateResize(mdConState* State);
MDCON_API void mdConStateSet(mdConState* State, mdConVar* Var);
MDCON_API void mdConStateDumpToStdout(mdConState* State);
MDCON_API void mdConStateDumpDbToSelfe(mdConState* State);
MDCON_API void mdConStateOutNullStr(mdConState* State, const char* Str);
MDCON_API void mdConStateOut(mdConState* State, const char* Str, st Size);
MDCON_API void mdConCheckSizeOut(mdConState* State, st NewSize);
MDCON_API void mdConStateOutHeader(mdConState* State);

MDCON_API void mdConStart();
MDCON_API void mdConEnd();
MDCON_API void mdConLog(const char* Str);
MDCON_API mdConState* mdConGetDisruptConsole();
MDCON_API void mdConStatePrint(mdConState* State, const char* Subsystem, const char* Message, mdConSeverity Severity);
MDCON_API void mdConStateFmtImpl(mdConState* State, const char* Subsystem, const char* Message, mdConSeverity Severity, v_varargList Args);
MDCON_API void mdConStateFmt(mdConState* State, const char* Subsystem, const char* Message, mdConSeverity Severity, ...);
MDCON_API void mdConLogInternFmt_DO_NOT_USE(const char* Subsystem, const char* Message, mdConSeverity Severity, ...);
MDCON_API void mdConLogIntern_DO_NOT_USE(const char* Subsystem, const char* Message, mdConSeverity Severity);
MDCON_API void mdConDumpToStdout();

//NOTE(V): Only the char* Name can be dealocated as we do a copy of it for serialization reasons
//    but we count on the user to never nullify the char* Help pointer
//    DO NOT INVALIDATE THE CONST CHAR* HELP POINTER PASSED OR HELP STRING WON'T APPEAR OR CRASH THE RUNTIME
MDCON_API void mdConVarToStr(mdConVar* Var, char* Buffer, st BufferSize);
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

MDTIME_API void mdTimeToStr(i64 Time, char* Buffer);

VLIB_CABIEND

//SECTION(V): Object loading

#define MDSO_API

#if defined(VLIB_ON_CRT) && defined(VLIB_PLATFORM_LINUX)
typedef void* mdsoHandle;
#define mdsoNullHandle NULL;

#else
#error Implement for platform

#endif

typedef enum mdsoFlags {
	mdsoFlags_lazyBind MYTH_BIT(1),
	mdsoFlags_dontLoad MYTH_BIT(2),
	mdsoFlags_localSymbols MYTH_BIT(3),

	mdsoFlags_COUNT,

} mdsoFlags;

VLIB_CABI
MDSO_API mdsoHandle mdsoOpen(const char* Name, const mdsoFlags Flags);
MDSO_API void* mdsoGetFunc(mdsoHandle Handle, const char* Symbol);
MDSO_API void mdsoClose(mdsoHandle Handle);

VLIB_CABIEND

//SECTION(V): System info

#define MDSYSTEMINFO_API

VLIB_CABI
MDSYSTEMINFO_API u64 mdsysTotalRam();
MDSYSTEMINFO_API u64 mdsysTotalHighRam();
MDSYSTEMINFO_API u64 mdsysTotalSwap();
MDSYSTEMINFO_API u64 mdsysFreeRam();
MDSYSTEMINFO_API u64 mdsysFreeHighRam();
MDSYSTEMINFO_API u64 mdsysFreeSwap();
MDSYSTEMINFO_API u64 mdsysSharedRam();
MDSYSTEMINFO_API u64 mdsysBufferRam();
MDSYSTEMINFO_API u64 mdsysTotalProcesses();
MDSYSTEMINFO_API u64 mdsysUptime();
VLIB_CABIEND

//SECTION(V): Init

void mdosInit();
void mdosExit();
