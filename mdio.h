////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mdio.h
//  Version:     v1.00
//  Created:     22/06/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "base_types.h"

#define MDIO_API

#define MDIO_MAX_PATH 512

typedef enum mdioMode{
	mdioMode_read MYTH_BIT(0),
	mdioMode_write MYTH_BIT(1),
	mdioMode_append MYTH_BIT(2),
	mdioMode_allowRead MYTH_BIT(4),

	mdioMode_readWrite = mdioMode_read | mdioMode_write,
	mdioMode_writeAppend = mdioMode_write | mdioMode_append,
	mdioMode_readAppend = mdioMode_read | mdioMode_append,
	mdioMode_readWriteAppend = mdioMode_read | mdioMode_write | mdioMode_append,

	mdioMode_writeAllowRead = mdioMode_write | mdioMode_allowRead,
	mdioMode_readAllowRead = mdioMode_read | mdioMode_allowRead,
	mdioMode_writeAppendAllowRead = mdioMode_writeAppend | mdioMode_allowRead,
	mdioMode_readWriteAppendAllowRead = mdioMode_readWriteAppend | mdioMode_allowRead,

} mdioMode;

typedef enum mdioAccess {
	mdioAccess_ownerExec MYTH_BIT(6),
	mdioAccess_groupExec MYTH_BIT(3),
	mdioAccess_otherExec MYTH_BIT(0),

	mdioAccess_ownerWrite MYTH_BIT(7),
	mdioAccess_groupWrite MYTH_BIT(4),
	mdioAccess_otherWrite MYTH_BIT(1),

	mdioAccess_ownerRead MYTH_BIT(8),
	mdioAccess_groupRead MYTH_BIT(5),
	mdioAccess_otherRead MYTH_BIT(2),

} mdioAccess;

VLIB_STRUCT(mdioFileInterface)


VLIB_STRUCTEND(mdioFileInterface)

VLIB_STRUCT(mdioFile)
mdioFileInterface* Interface;
mdioMode Mode;


VLIB_STRUCTEND(mdioFile)

VLIB_CABI
MDIO_API void mdioAppendPathExtension(const char* Base, const char* Extension, char* Out, st OutSize);
MDIO_API bool mdioMergeDirAndFilename(const char* Directory, const char* Path, char Separator, char* Dest, st DestSize);
MDIO_API bool mdioAppendDirAndFilename(const char* Directory, const char* Path, char* Dest, st DestSize);
MDIO_API void mdioReplacePathExtension(const char* Path, const char* NewExtension, char* Out, st OutSize);
MDIO_API void mdioGetParentPath(const char* Path, char* Out, st OutSize);
MDIO_API void mdioGetPathFilename(const char* Path, char* Out, st OutSize);
MDIO_API void mdioGetPathExtension(const char* Path, char* Out, st OutSize);
MDIO_API bool mdioIsDirectorySeparator(const char Char);
MDIO_API st mdioNormalizePathContinue(const char* NextPath, char Separator, const char* OutBeg, char* OutCur, const char* OutEnd);
MDIO_API bool mdioIsNormalizedPath(const char* Path, char Separator);
MDIO_API bool mdioIsDriveLetter(const char* Path);
MDIO_API bool mdioSeparatorFilter(char Char, char Separator);

//SECTION(V): System
MDIO_API bool mdioDeleteFile(const char* Filename);
MDIO_API bool mdioRenameFile(const char* Filename, const char* NewFilename);
MDIO_API bool mdioFileExist(const char* Filename);

VLIB_CABIEND
