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

VLIB_STRUCT(mdConVar)


VLIB_STRUCTEND(mdConVar)

VLIB_STRUCT(mdConState)


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

typedef void(*mdConVarCallback)(mdConVar*);
typedef void(*mdConCmdFunc)(const char*);

VLIB_CABI
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
MDTIME_API u32 mdTimeGetMsSystemTime();
MDTIME_API i64 mdTimeGetMicroSystemTime();
MDTIME_API u32 mdTimeGetTimeSinceStartup();
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
