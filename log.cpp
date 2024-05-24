////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   log.cpp
//  Version:     v1.00
//  Created:     30/04/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "cpp_compiler.h"
#include "log.h"

namespace VLIB_NAMESPACE{
	const char* logTypeToStr(logType Type) {
		switch (Type) {
			case(logType::Info):
				return "Info";
				break;
			case(logType::Warn):
				return "Warn";
				break;
			case(logType::Error):
				return "Error";
				break;

		}

		return "TOSTR_ERROR";

	}

}
