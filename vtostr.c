////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   vtostr.c
//  Version:     v1.00
//  Created:     03/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "vtostr.h"
#include "mdos.h"
#include "system.h"

VLIB_CABI
const char* vtostr_mdConVarType(u64 Var){
	switch (Var) {
		case (mdConVarType_none):
			return "mdConVarType_none";
			break;
		case (mdConVarType_Str):
			return "mdConVarType_Str";
			break;
		case (mdConVarType_Double):
			return "mdConVarType_Double";
			break;
		case (mdConVarType_Int):
			return "mdConVarType_Int";
			break;

	}
	vsys_writeConsoleNullStr("#####");
	vsys_writeConsoleInteger(Var);
	return "vtostr_error_mdConVarType";

}

VLIB_CABIEND
