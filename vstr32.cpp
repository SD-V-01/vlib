////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   vstr32.cpp
//  Version:     v1.00
//  Created:     09/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "vstr32.h"
#include "system.h"
#include "mem.h"

#ifdef VPP
namespace VLIB_NAMESPACE{
	st mstrlen(const char* String) {
		return vstrlen8(String);

	}

	st mstrlen(const vchar* String) {
		return vstrlen32(String);

	}

}

#endif

VLIB_CABI
st vstrlen8(const char* String) {
	const char* A = String;
	for (; *String; String++) {

	}
	return String - A;

}

st vstrlen16(const wchar_t* String) {
	const wchar_t* A = String;
	for (; *String; String++) {

	}
	return String - A;

}

st vstrlen32(const vchar* String) {
	const vchar* A = String;
	for (; *String; String++) {

	}
	return String - A;

}

char* vstrchr8(const char* Str, int Char) {
	const unsigned char* CharPtr;
	const unsigned long int* LongwordPtr;
	unsigned long int Longword, MagicBits, CharMask;
	unsigned char C;

	C = (unsigned char)Char;

	for (CharPtr = (const unsigned char*) Str;
		((unsigned long int) CharPtr & (sizeof(Longword) - 1)) != 0;
		++CharPtr) {
		if (*CharPtr == C) {
			return (char*)CharPtr;

		}
		else if (*CharPtr == 0) {
			return NULL;

		}

	}

	LongwordPtr = (unsigned long int*)CharPtr;
	MagicBits = -1;
	MagicBits = MagicBits / 0xff * 0xfe << 1 >> 1 | 1;

	CharMask = C | (C << 8);
	CharMask |= CharMask << 16;
	if (sizeof(Longword) > 4) {
		CharMask |= (CharMask << 16) << 16;

	}

	if (sizeof(Longword) > 8) {
//        TODO(V): Replace that with string handeling specific logging
		vsys_writeConsoleNullStr("Something went terribly wrong in legacy strchr implementation\n");
		return NULL;

	}

	for (;;) {
		Longword = *LongwordPtr++;

		if ((((Longword + MagicBits)
			^ ~Longword)
			& ~MagicBits) != 0 ||
			((((Longword ^ CharMask) + MagicBits) ^ ~(Longword ^ CharMask))
				& ~MagicBits) != 0) {
			const unsigned char* Cp = (const unsigned char*)(LongwordPtr - 1);

			if (*Cp == C) {
				return (char*)Cp;

			}
			else if (*Cp == 0) {
				return NULL;

			}

			if (*++Cp == C) {
				return (char*)Cp;

			}
			else if (*Cp == 0) {
				return NULL;

			}

			if (*++Cp == C) {
				return (char*)Cp;

			}
			else if (*Cp == 0) {
				return NULL;

			}

			if (*++Cp == C) {
				return (char*)Cp;

			}
			else if (*Cp == 0) {
				return NULL;

			}

			if (sizeof(Longword) > 4) {
				if (*++Cp == C) {
					return (char*)Cp;

				}
				else if (*Cp == 0) {
					return NULL;

				}

				if (*++Cp == C) {
					return (char*)Cp;

				}
				else if (*Cp == 0) {
					return NULL;

				}

				if (*++Cp == C) {
					return (char*)Cp;

				}
				else if (*Cp == 0) {
					return NULL;

				}

				if (*++Cp == C) {
					return (char*)Cp;

				}
				else if (*Cp == 0) {
					return NULL;

				}

			}

		}

	}

	return NULL;

}

char* vstrstr8(const char* In, const char* Search) {
	st InLength;
	st SearchLength;

	if (*Search == 0) {
		return (char*)In;

	}

	In = vstrchr8(In, Search[0]);
	if (In == NULL || Search[1] == 0) {
		return (char*)In;

	}

	SearchLength = vstrlen8(Search);
	InLength = vstrlen8(In);

	if (InLength < SearchLength) {
		return NULL;

	}

//    TODO(V): !!!!!!!!!!! Implement
	return NULL;

}

VSTR32_API long int vstrtol8(const char* Str, char** EndPtr, int Base) {
	//    TODO(V): !!!!!!!!!!! Implement
	return 0;

}

u32 vdigitlen(u64 In) {
	if (In == 0) {
		return 0;

	}
	u32 Result = 0;

	for (; In != 0;) {
		In = In / 10;
		Result++;

	}
	return Result;

}

u32 vdigitlensigned(i64 In) {
	if (In == 0) {
		return 0;

	}

	u64 Significant = 0;
	if (In < 0) {
		Significant = In * -1;

	}
	else {
		Significant = In;

	}

	return vdigitlen(Significant);

}

void v32to8char(const vchar* Source, char* Target, u32 Size) {
	for (u32 i = 0; i < Size; i++) {
		Target[i] = (char)Source[i];

	}

}

void v8to32char(const char* Source, vchar* Target, u32 Size) {
	for (u32 i = 0; i < Size; i++) {
		*Target = *Source;
		Target++;
		Source++;

	}

}

int vLEGACYstrcmp(const char* s1, const char* s2) {
	while(*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;

}

void vLEGACYstrcopy(const char* Source, char* Dest) {
	const u32 Size = vstrlen8(Source);
	vcpy(Dest, Source, Size);
	Dest[Size] = 0;

}

char* vLEGACYstrncat(char* Dest, const char* Source, size_t Size) {
	char* A = Dest;
	Dest += vstrlen8(Dest);
	while (Size && *Source) {
		Size--;
		*Dest++ = *Source++;

	}
	*Dest++ = 0;
	return A;

}

char* vLEGACYgcvt(double In, int NumDigits, char* Buf) {

} //        STUB(V): Implement legacy gcvt c library function

VLIB_CABIEND
