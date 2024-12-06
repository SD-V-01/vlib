////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   mdio.h v1.00
//  Created:     22/06/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
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

typedef enum mdioKernel {
	mdioKernel_direct MYTH_BIT(1),
	mdioKernel_noSymLinkDereference MYTH_BIT(2),
	mdioKernel_temp MYTH_BIT(3),

} mdioKernel;

typedef enum mdioSeek {
	mdioSeek_start = 0,
	mdioSeek_current,
	mdioSeek_end,

	mdioSeek_COUNT,

} mdioSeek;

typedef union mdioFileDesc{
	int UnixFileDesc;
	void* VoidP;

} mdioFileDesc;

VLIB_STRUCT(mdioFile)
mdioMode Mode;
st Size;
void* Map;
mdioFileDesc Descriptor;

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
MDIO_API void mdioErrorReportFile(const char* Error, const char* Path, int ErrorCode);
MDIO_API bool mdioDeleteFile(const char* Filename);
MDIO_API bool mdioRenameFile(const char* Filename, const char* NewFilename);
MDIO_API bool mdioMoveFile(const char* Filename, const char* NewFilename);
MDIO_API bool mdioFileExist(const char* Filename);
MDIO_API i64 mdioGetModifiedLastTimeUnix(const char* Filename);
MDIO_API i64 mdioGetAccessedLastTimeUnix(const char* Filename);
MDIO_API st mdioGetFileSize(const char* Filename);
MDIO_API bool mdioDirectoryExist(const char* Path);
MDIO_API bool mdio777CreateDir(const char* Path);
MDIO_API bool mdio777NoRecurseCreateDir(const char* Path);
MDIO_API bool mdio777RecurseCreateDir(const char* Path, const bool ShouldRecurse);
MDIO_API bool mdio666OpenFile(mdioFile* File, const char* Path, mdioMode Mode);
MDIO_API bool mdioSeekFile(mdioFile* File, mdioSeek Start, st Offset);
MDIO_API st mdioGetPositionFile(mdioFile* File);
MDIO_API const char* mdioDereferenceDescriptorFile(mdioFile* File, char* Buffer, st BufferSize);
MDIO_API bool mdioCloseFile(mdioFile* File);
MDIO_API bool mdioFlushFile(mdioFile* File);
MDIO_API bool mdioFlushMetaAndFile(mdioFile* File);
MDIO_API bool mdioUpdateSizeFile(mdioFile* File);
MDIO_API st mdioGetSizeOfFile(mdioFile* File);
MDIO_API st mdioReadFile(mdioFile* File, void* Dest, st Size);
MDIO_API st mdioWriteFile(mdioFile* File, void* Src, st Size);
MDIO_API char mdioGetSystemSeparator();

VLIB_CABIEND
