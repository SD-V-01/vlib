////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   log.h
//  Version:     v1.00
//  Created:     30/04/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#ifndef _LOG_H_
#define _LOG_H_

#include "str.h"

#define VRCS_LOG(VrcSolverSubsystem, ...) { VrcSolver::string FormatStr{}; \
FormatStr.format(__VA_ARGS__); \
VrcSolver::logToConsole(VrcSolverSubsystem, FormatStr, VrcSolver::logType::Info); }

#define VRCS_WARN(VrcSolverSubsystem, ...) { VrcSolver::string FormatStr{}; \
FormatStr.format(__VA_ARGS__); \
VrcSolver::logToConsole(VrcSolverSubsystem, FormatStr, VrcSolver::logType::Warn); }

#define VRCS_ERROR(VrcSolverSubsystem, ...) { VrcSolver::string FormatStr{}; \
FormatStr.format(__VA_ARGS__); \
VrcSolver::logToConsole(VrcSolverSubsystem, FormatStr, VrcSolver::logType::Error); }

namespace VLIB_NAMESPACE{
	enum class logType : u32 {
		Info,
		Warn,
		Error,

	};

    void logToConsole(const char* Subsystem, string& StringToPrint, logType Type);
	const char* logTypeToStr(logType Type);

}

#endif
