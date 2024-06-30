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

//TODO(V): Make this MDIO_MAX_PATH independent
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

#if defined(VLIB_PLATFORM_LINUX)
#ifdef VLIB_ON_CRT
#include <stdio.h>
#include <sys/stat.h>

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

#else
#error Implement for platform

#endif

#else
#error Implement for platform

#endif

VLIB_CABIEND
