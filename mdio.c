////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mdio.cpp
//  Version:     v1.00
//  Created:     22/06/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"
#include "mdio.h"
#include "mderror.h"
#include "vstr32.h"
#include "vmem.h"

VLIB_CABI
bool mdioMergeDirAndFilename(const char* Directory, const char* Path, char Separator, char* Dest, st DestSize){
	*Dest = 0;
	st OutLength = mdioNormalizePathContinue(Directory, Separator, Dest, Dest, Dest + DestSize);

	if (
		OutLength && Dest[OutLength - 1] != Separator && !mdioIsDirectorySeparator(*Path)) {
		Dest[OutLength++] = Separator;
		Dest[OutLength] = 0;

	}

	OutLength = mdioNormalizePathContinue(Path, Separator, Dest, Dest + OutLength, Dest + DestSize);

	VASSERT(OutLength <= DestSize, "Buffer passed to mdioMergeDirAndFilename doesent have enouth space");

	bool Success = OutLength < DestSize;
	if (!Success) {
		VASSERT(0, "Failed to append path in mdioMergeDirAndFilename");

	}

	if (OutLength && Dest[OutLength - 1] == Separator) {
		Dest[OutLength - 1] = 0;

	}

	return Success;

}

bool mdioAppendDirAndFilename(const char* Directory, const char* Path, char* Dest, st DestSize){
	return mdioMergeDirAndFilename(Directory, Path, '/', Dest, DestSize);

}

void mdioReplacePathExtension(const char* Path, const char* NewExtension, char* Out, st OutSize){
	st NewExtensionLength = vstrlen8(NewExtension);
	const st BaseLength = vstrlen8(Path);

	const st MaxPathLength = BaseLength + NewExtensionLength + 1;

	VASSERT(BaseLength != 0, "Path passed to mdioReplacePathExtension is empty");
	if (MaxPathLength > (OutSize - 1)) {
		VASSERT(0, "New path length excede OutSize in mdioReplacePathExtension");
		return;

	}

	vcpy(Out, Path, BaseLength);
	Out[MaxPathLength] = 0;

	st NewPathLength = BaseLength;
	if (NewExtensionLength == 0) {
		return;

	}

	for (st v = 0; v < NewExtensionLength; v++) {
		if (mdioIsDirectorySeparator(NewExtension[v])) {
			VASSERT(0, "Extension passed to mdioReplacePathExtension contains a separator");

		}

	}
	VASSERT(NewExtension[NewExtensionLength - 1] == '.', "Extension passed to mdioReplacePathExtension ends with a '.'");

	if (NewExtension[0] == '.') {
		NewExtension++;
		NewExtensionLength--;

	}

	//TODO(V): Make this MDIO_MAX_PATH independent
	char CurrentExtension[MDIO_MAX_PATH] = { 0 };
	mdioGetPathExtension(Path, CurrentExtension, MDIO_MAX_PATH);
	NewPathLength -= vstrlen8(CurrentExtension);
	if (Out[NewPathLength - 1] != '.') {
		Out[NewPathLength] = '.';
		NewPathLength++;

	}

	vcpy(Out + NewPathLength, NewExtension, NewExtensionLength);
	Out[NewPathLength + NewExtensionLength] = 0;

}

void mdioGetParentPath(const char* Path, char* Out, st OutSize){
	st PathLength = vstrlen8(Path);
	if (!PathLength) {
		Out[0] = '\0';
		return;

	}

	const char* DirSeparatorLoc = NULL;
	for (const char* Cur = Path + PathLength - 1; Cur >= Path; --Cur) {
		if (!mdioIsDirectorySeparator(*Cur)) {
			continue;

		}
		DirSeparatorLoc = Cur;
		break;

	}

	if (!DirSeparatorLoc) {
		Out[0] = 0;
		return;

	}

	st OutLength = (st)(DirSeparatorLoc - Path);
	st ResLength = OutLength;
	if (ResLength > OutSize) {
		ResLength = OutSize - 1;

	}
	vcpy(Out, Path, ResLength);
	Out[ResLength] = 0;

}

//TODO(V): Make this MDIO_MAX_PATH independent
void mdioGetPathFilename(const char* Path, char* Out, st OutSize){
	const st PathLength = vstrlen8(Path);
	VASSERT(PathLength != 0, "Path length in mdioGetPathFilename is 0 !!");
	char ParentPath[MDIO_MAX_PATH] = { '\0' };
	mdioGetParentPath(Path, ParentPath, MDIO_MAX_PATH);
	st ParentPathLength = vstrlen8(ParentPath);
	if (ParentPathLength < PathLength && (mdioIsDirectorySeparator(Path[ParentPathLength]))) {
		ParentPathLength++;

	}

	char Extension[MDIO_MAX_PATH] = { '\0' };
	mdioGetPathExtension(Path, Extension, MDIO_MAX_PATH);
	 
	const st ExtensionLength = Extension[0] != 0 ? vstrlen8(Extension) + 1 : 0;
	st OutLength = PathLength - ParentPathLength - ExtensionLength;
	if (OutLength > OutSize) {
		OutLength = OutSize - 1;

	}
	vcpy(Out, Path + ParentPathLength, OutLength);
	Out[OutLength] = 0;

}

void mdioGetPathExtension(const char* Path, char* Out, st OutSize){
	st PathLength = vstrlen8(Path);
	VASSERT(PathLength != 0, "Tried to get path extension of a empty string !?");

	const char* DotLocation = vstrlastchar8(Path, '.');
	if (DotLocation == NULL) {
		return;

	}
	DotLocation++;
	const st ExtLength = vstrlen8(DotLocation);
	if (ExtLength == 0 || mdioIsDirectorySeparator(DotLocation[0])) {
		return;

	}

	if (OutSize > vstrlen8(DotLocation)) {
		OutSize = vstrlen8(DotLocation);

	}
	vcpy(Out, DotLocation, OutSize);
	Out[vstrlen8(DotLocation)] = 0;
	return;

}

bool mdioIsDirectorySeparator(const char Char) {
	return (Char) == '/' || (Char) == '\\';

}

st mdioNormalizePathContinue(const char* NextPath, char Separator, const char* OutBeg, char* OutCur, const char* OutEnd) {
	VASSERT(NextPath, "Nextpath is a null pointer passed to mdioNormalizePathContinue");
	VASSERT(Separator, "Separator is a 0 char passed to mdioNormalizePathContinue");
	VASSERT(OutBeg <= OutCur && OutCur <= OutEnd && OutBeg < OutEnd, "Bad pointers passed to mdioNormalizePathContinue");

	if (OutEnd <= OutBeg) {
		return 0;

	}

	const bool NotEmptyAtStart = OutCur > OutBeg;
	char* Noback = OutCur - (OutCur - OutBeg);
	if (OutCur > OutBeg) {
		if (mdioIsDriveLetter(Noback)) {
			Noback += 2;

		}

		if (mdioSeparatorFilter(*Noback, Separator) == Separator) {
			Noback++;

		}

		for (; Noback <= OutCur - 3;) {
			char C = Noback[0];
			char Nc = Noback[1];
			char Nnc = Noback[2];

			if (C != '.' || Nc != '.' || Nnc != Separator) {
				break;

			}

			Noback += 3;

		}

	}
	else {
		if (Noback == OutCur && mdioSeparatorFilter(*NextPath, Separator) == Separator) {
			++Noback;

		}

	}

	for (const char* Src = NextPath; *Src; Src++) {
		char C = mdioSeparatorFilter(*Src, Separator);

		if (C == Separator) {
			if ((OutCur != OutBeg && mdioIsDirectorySeparator(OutCur[-1])) || (OutCur == OutBeg && Src != NextPath)) {
				//                NOTE(V): Fuck
				continue;

			}

			*(OutCur++) = Separator;
			if (OutCur == OutEnd) {
				break;

			}

			continue;

		}

		const bool EntryStart = OutCur == OutBeg || OutCur[-1] == Separator;

		if (!EntryStart || C != '.') {
			*(OutCur++) = C;
			if (OutCur == OutEnd) {
				break;

			}

			continue;

		}

		const char Nc = mdioSeparatorFilter(Src[1], Separator);
		if (!Nc) {
			break;

		}

		if (Nc == Separator) {
			Src++;
			continue;

		}

		const char Nnc = mdioSeparatorFilter(Src[2], Separator);
		const bool Backlink = Nc == '.' && (Nnc == Separator || !Nnc);
		bool IsNoback = OutCur == Noback;

		if (Backlink && IsNoback) {
			Noback += 3;

		}

		if (!Backlink && IsNoback) {
			*(OutCur++) = C;
			if (OutCur == OutEnd) {
				break;

			}
			*(OutCur++) = Nc;
			if (OutCur == OutEnd) {
				break;

			}

			if (Nnc) {
				*(OutCur++) = Nnc;
				if (OutCur == OutEnd) {
					break;

				}

			}

		}
		else {
			for(OutCur -= 2; OutCur >= OutBeg && *OutCur != Separator; --OutCur);
			OutCur++;

		}

		Src += 1 + (Nnc != 0);

	}

	st Size = (st)(OutCur - OutBeg);
	VASSERT(OutCur <= OutEnd, "Internal Error mdioNormalizePathContinue");

	if (OutCur == OutEnd) {
		//    Failed
		OutCur[-1] = 0;
		return (st)(OutEnd - OutBeg);

	}

	if (!Size && (NotEmptyAtStart || *NextPath)) {
		*OutCur = '.';
		++OutCur;

	}

	*OutCur = 0;
	VASSERT(mdioIsNormalizedPath(OutBeg, Separator), "Internal Error mdioNormalizePathContinue");
	return Size;

}

bool mdioIsNormalizedPath(const char* Path, char Separator) {
	const char* Cur = Path;
	if (mdioIsDriveLetter(Cur)) {
		Cur += 2;

	}

	bool RealEntryFound = false;
	i32 DotCounter = -1;
	if (Cur[0] == '.') {
		if (Cur[1] == 0) {
			return true;

		}

		DotCounter = 1;
		Cur++;

	}

	for (;; ++Cur) {
		char Char = *Cur;
		bool IsSep = mdioIsDirectorySeparator(Char);
		if (IsSep || !Char) {
			switch (DotCounter) {
				case 0:
					if (IsSep) {
						goto NORM_PATH_RETURN_FALSE;

					}
					break;

				case 1:
					goto NORM_PATH_RETURN_FALSE;

				case 2:
					if (RealEntryFound) {
						goto NORM_PATH_RETURN_FALSE;

					}
					break;

			}

			if (!Char) {
				break;

			}

			if (Char != Separator) {
				goto NORM_PATH_RETURN_FALSE;

			}

			DotCounter = 0;

		}
		else if (Char == '.') {
			if (DotCounter >= 0) {
				++DotCounter;
				if (DotCounter > 2) {
					RealEntryFound = true;

				}

			}

		}
		else {
			RealEntryFound = true;
			DotCounter = -1;

		}

	}

	return true;

	NORM_PATH_RETURN_FALSE:
	(void)NULL;
	return false;

}

bool mdioIsDriveLetter(const char* Path) {
	return Path[0] && Path[1] == ':' && mdioIsDirectorySeparator(Path[2]);

}

bool mdioSeparatorFilter(char Char, char Separator) {
	return mdioIsDirectorySeparator(Char) ? Separator : Char;

}

//SECTION(V): System

#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include "system.h"

void mdioErrorReportFile(const char* Error, const char* Path, int ErrorCode) {
//    TODO(V): Make this use a better api for error reporting

	vsys_writeConsoleNullStr("mdIO Error \"");
	vsys_writeConsoleNullStr(Error);
	vsys_writeConsoleNullStr("\" with code \"");
	if (ErrorCode < 0) {
		vsys_writeConsoleNullStr("-");

	}
	vsys_writeConsoleInteger(ErrorCode);
	vsys_writeConsoleNullStr("\" and path \"");
	vsys_writeConsoleNullStr(Path);
	vsys_writeConsoleNullStr("\"\n");

	#ifdef VLIB_IO_ERROR_BREAKPOINT
	vsys_breakpoint();

	#endif

}

bool mdioDeleteFile(const char* Filename) {
	return !remove(Filename);

}

bool mdioRenameFile(const char* Filename, const char* NewFilename) {
	return !rename(Filename, NewFilename);

}

bool mdioFileExist(const char* Filename) {
	struct stat Stat = { 0 };
	i32 Res = stat(Filename, &Stat);
	if (Res != 0) {
		return false;

	}
	return true;

}

i64 mdioGetModifiedLastTimeUnix(const char* Filename) {
	struct stat Fileinfo = { 0 };
	stat(Filename, &Fileinfo);
	return Fileinfo.st_mtime;

}

//TODO(V): Should error chek those stat calls
i64 mdioGetAccessedLastTimeUnix(const char* Filename) {
	struct stat Fileinfo = { 0 };
	stat(Filename, &Fileinfo);
	return Fileinfo.st_atime;

}

st mdioGetFileSize(const char* Filename) {
	struct stat FileInfo = { 0 };
	stat(Filename, &FileInfo);
	return FileInfo.st_size;

}

bool mdioDirectoryExist(const char* Path) {
	struct stat Fileinfo = { 0 };
	if (stat(Path, &Fileinfo)) {
		return false;

	}

	return (Fileinfo.st_mode & S_IFDIR) != 0;

}

bool mdio777CreateDir(const char* Path) {
	if (mdioDirectoryExist(Path)) {
		return true;

	}

//    TODO(V): Make this MDIO_MAX_PATH independent
	char ParentPath[MDIO_MAX_PATH] = { 0 };
	mdioGetParentPath(Path, ParentPath, MDIO_MAX_PATH);
	if (ParentPath[0] != 0) {
		mdio777CreateDir(ParentPath);

	}

	//    TODO(V): Passin permissions
	if (mkdir(Path, 0777) != 0) {
//        TODO(V): Replace this with a better error handeling message
		VASSERT(0, "Could not create directory");
		return false;

	}

	return true;

}

bool mdio777NoRecurseCreateDir(const char* Path) {
	if (mdioDirectoryExist(Path)) {
		return true;

	}

	//    TODO(V): Passin permissions
	if (mkdir(Path, 0777) != 0) {
		//        TODO(V): Replace this with a better error handeling message
		VASSERT(0, "Could not create directory");
		return false;

	}

	return true;

}

bool mdio777RecurseCreateDir(const char* Path, const bool ShouldRecurse) {
	if (mdioDirectoryExist(Path)) {
		return true;

	}

	if (ShouldRecurse) {
		//    TODO(V): Make this MDIO_MAX_PATH independent
		char ParentPath[MDIO_MAX_PATH] = { 0 };
		mdioGetParentPath(Path, ParentPath, MDIO_MAX_PATH);
		if (ParentPath[0] != 0) {
			mdio777CreateDir(ParentPath);

		}

	}

	//    TODO(V): Passin permissions
	if (mkdir(Path, 0777) != 0) {
		//        TODO(V): Replace this with a better error handeling message
		VASSERT(0, "Could not create directory");
		return false;

	}

	return true;

}

bool mdio666OpenFile(mdioFile* File, const char* Path, mdioMode Mode) {
	vset(File, 0, sizeof(*File));

	int Flags = 0;
	mode_t SysPerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IROTH;
	if (Mode & mdioMode_write) {
		Flags |= O_CREAT;
		if (Mode & mdioMode_append) {
			Flags |= O_APPEND;

		}
		else {
			Flags |= O_TRUNC;

		}

		if (Mode & mdioMode_read) {
			Flags |= O_RDWR;

		}
		else {
			Flags |= O_WRONLY;

		}

	}
	else {
		Flags |= O_RDONLY;

	}

	int FileDesc = open(Path, Flags, SysPerms);
	if (FileDesc < 0) {
		mdioErrorReportFile("Could not 666Open requested file", Path, errno);
		return false;

	}

	File->Descriptor.UnixFileDesc = FileDesc;
	File->Size = -1;

	struct stat FileInfo = { 0 };
	if (fstat(FileDesc, &FileInfo) == 0) {
		File->Size = FileInfo.st_size;

	}
	else {
		mdioErrorReportFile("Could not get the size of the file that was just 666Open'd", Path, errno);

	}

	File->Mode = Mode;
	File->Map = NULL;

	if ((Mode & mdioMode_read) && (Mode & mdioMode_append) && !(Mode & mdioMode_write)) {
		if (!mdioSeekFile(File, mdioSeek_end, 0)) {
			mdioCloseFile(File);
			return false;

		}

	}

	return true;

}

bool mdioSeekFile(mdioFile* File, mdioSeek Start, st Offset) {
	int SystemStart;
	char Buffer2[1024];
	switch (Start) {
		case mdioSeek_start:
			SystemStart = SEEK_SET;
			break;

		case mdioSeek_current:
			SystemStart = SEEK_CUR;
			break;

		case mdioSeek_end:
			SystemStart = SEEK_END;
			break;

		default:
		case mdioSeek_COUNT:
			mdioDereferenceDescriptorFile(File, Buffer2, 1024);
			mdioErrorReportFile("Bad/Data Coruption on the mdioSeek passed", Buffer2, Start);
			break;

	}

	off_t Result = lseek(File->Descriptor.UnixFileDesc, Offset, SystemStart);
	if (Result >= 0) {
		return true;

	}

	char Buffer[1024];
	mdioDereferenceDescriptorFile(File, Buffer, 1024);
	mdioErrorReportFile("Could not seek intro file", Buffer, errno);
	return false;

}

st mdioGetPositionFile(mdioFile* File) {
	off_t Res = lseek(File->Descriptor.UnixFileDesc, 0, SEEK_CUR);
	if (Res >= 0) {
		return Res;

	}

	char Buffer[1024];
	mdioDereferenceDescriptorFile(File, Buffer, 1024);
	mdioErrorReportFile("Could not get position of file", Buffer, errno);
	return 0;

}

const char* mdioDereferenceDescriptorFile(mdioFile* File, char* Buffer, st BufferSize) {
	char FdPath[64];
	snprintf(FdPath, 64, "/proc/self/fd/%i", File->Descriptor.UnixFileDesc);
	sst Len = readlink(FdPath, Buffer, BufferSize - 1);
	if (Len >= 0) {
		Buffer[Len] = 0;
		return Buffer;

	}

	mdioErrorReportFile("Could not dereference file name from descriptor", FdPath, errno);
	return "UNKNOWN_FILE_NAME_DEREF_FAILED";

}

bool mdioCloseFile(mdioFile* File) {
	if (File->Map) {
		if (munmap(File->Map, (st)File->Size)) {
			char Buffer[1024];
			mdioDereferenceDescriptorFile(File, Buffer, 1024);
			mdioErrorReportFile("Could not munmap memory mapped file", Buffer, errno);

		}
		else {
			File->Map = NULL;

		}

	}

	char Buffer[1024] = { 0 };
	mdioDereferenceDescriptorFile(File, Buffer, 1024);

	bool Success = File->Descriptor.UnixFileDesc < 0 || close(File->Descriptor.UnixFileDesc) == 0;
	if (!Success) {
		mdioErrorReportFile("Could not close file", Buffer, errno);

	}
	File->Descriptor.UnixFileDesc = -1;
	return Success;

}

bool mdioFlushFile(mdioFile* File) {
	if (!(File->Mode & mdioMode_write)) {
		return true;

	}

	if (!fdatasync(File->Descriptor.UnixFileDesc)) {
		return true;

	}

	char Buffer[1024] = { 0 };
	mdioDereferenceDescriptorFile(File, Buffer, 1024);
	mdioErrorReportFile("Could not flush file data", Buffer, errno);
	return false;

}

bool mdioFlushMetaAndFile(mdioFile* File) {
	if (!(File->Mode & mdioMode_write)) {
		return true;

	}

	if (!fsync(File->Descriptor.UnixFileDesc)) {
		return true;

	}

	char Buffer[1024] = { 0 };
	mdioDereferenceDescriptorFile(File, Buffer, 1024);
	mdioErrorReportFile("Could not flush file data and metadata", Buffer, errno);
	return false;

}

bool mdioUpdateSizeFile(mdioFile* File) {
	off_t Offset = lseek(File->Descriptor.UnixFileDesc, 0, SEEK_CUR);
	if (Offset < 0) {
		return false;

	}
	off_t Size = lseek(File->Descriptor.UnixFileDesc, 0, SEEK_END);
	if (Size < 0) {
		return false;

	}

	if (Offset == Size) {
		File->Size = Size;
		return true;

	}

	off_t Offset2 = lseek(File->Descriptor.UnixFileDesc, Offset, SEEK_SET);
	if (Offset2 < 0 || Offset2 != Offset) {
		char Buffer[1024];
		mdioDereferenceDescriptorFile(File, Buffer, 1024);
		mdioErrorReportFile("File position is broken, closing the file", Buffer, errno);
		mdioCloseFile(File);
		return false;

	}

	File->Size = Size;
	return true;

}

st mdioGetSizeOfFile(mdioFile* File) {
	if (File->Size == -1) {
		if (!mdioUpdateSizeFile(File)) {
			return -1;

		}

	}
	else if (File->Mode & mdioMode_write) {
		if (!mdioUpdateSizeFile(File)) {
			return -1;

		}

	}

	return File->Size;

}

st mdioReadFile(mdioFile* File, void* Dest, st Size) {
	if (!(File->Mode & mdioMode_read)) {
		char Buffer[1024] = { 0 };
		mdioDereferenceDescriptorFile(File, Buffer, 1024);
		mdioErrorReportFile("Trying to read from file while mode is not set to read, this may not work", Buffer, Size);

	}

	sst Result = read(File->Descriptor.UnixFileDesc, Dest, Size);
	if (Result >= 0) {
		return Result;

	}

	char Buffer[1024] = { 0 };
	mdioDereferenceDescriptorFile(File, Buffer, 1024);
	mdioErrorReportFile("Could not read from file", Buffer, errno);
	return 0;

}

st mdioWriteFile(mdioFile* File, void* Src, st Size) {
	if (!(File->Mode & mdioMode_write)) {
		char Buffer[1024] = { 0 };
		mdioDereferenceDescriptorFile(File, Buffer, 1024);
		mdioErrorReportFile("Trying to read from file while mode is not set to write, this may not work", Buffer, Size);

	}

	sst Result = write(File->Descriptor.UnixFileDesc, Src, Size);
	if (Result >= 0) {
		return Result;

	}

	char Buffer[1024] = { 0 };
	mdioDereferenceDescriptorFile(File, Buffer, 1024);
	mdioErrorReportFile("Could not write to file", Buffer, errno);
	return 0;

}

#elif defined(VLIB_PLATFORM_NT)
bool mdioDeleteFile(const char* Filename) {
	st FilePathLen = vstrlen8(Filename);
	wchar_t* PathStr = (wchar_t*)alloca((FilePathLen + 1) * sizeof(wchar_t));
	st PathStrlength = MultiByteToWideChar(CP_UTF8, 0, Filename, (int)FilePathLen, PathStr, (int)FilePathLen);
	PathStr[PathStrlength] = 0;

	return !_wremove(PathStr);

}

bool mdioRenameFile(const char* Filename, const char* NewFilename) {
	wchar_t PathStr = NULL;
	wchar_t NewPathStr = NULL;

	{
		st FilePathLen = vstrlen8(Filename);
		PathStr = (wchar_t*)alloca((FilePathLen + 1) * sizeof(wchar_t));
		st PathStrLength = MultiByteToWideChar(CP_UTF8, 0, Filename, (int)FilePathLen, PathStr, (int)FilePathLen);
		PathStr[PathStrLength] = 0;

	}

	{
		st NewFilePathLen = vstrlen8(NewFilename);
		NewPathStr = (wchar_t*)alloca((NewFilePathLen + 1) * sizeof(wchar_t));
		st NewPathStrLength = MultiByteToWideChar(CP_UTF8, 0, NewFilename, (int)NewFilePathLen, NewPathStr, (int)NewFilePathLen);
		NewPathStr[NewPathStrLength] = 0;

	}

	return !_wrename(PathStr, NewPathStr);

}

bool mdioFileExist(const char* Filename) {
	st FilePathLength = vstrlen8(Filename);
	wchar_t* PathStr = (wchar_t*)alloca((FilePathLength + 1) * sizeof(wchar_t));
	st PathStrLength = MultiByteToWideChar(CP_UTF8, 0, Filename, (int)FilePathLength, PathStr, (int)FilePathLength);
	PathStr[PathStrLength] = 0;

	struct _stat S = {};
	int Res = _wstat(PathStr, &S);
	if (Res != 0) {
		return false;

	}
	return true;

}

#else
#error Implement for platform

#endif

VLIB_CABIEND
