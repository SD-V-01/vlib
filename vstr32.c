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
#include "vmem.h"
#include "vtostr.h"

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

st vstrlen16(const char16* String) {
	const char16* A = String;
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
	char* R = vstrchrnul8(Str, Char);
	return * (unsigned char*)R == (unsigned char)Char ? R : 0;

}

#define vstrchrnul8_UCHAR_MAX 255
#define vstrchrnul8_ALIGN (sizeof(size_t))
#define vstrchrnul8_ONES ((size_t)-1/vstrchrnul8_UCHAR_MAX)
#define vstrchrnul8_HIGHS (vstrchrnul8_ONES * (vstrchrnul8_UCHAR_MAX/2+1))
#define vstrchrnul8_HASZERO(x) ((x)-vstrchrnul8_ONES & ~(x) & vstrchrnul8_HIGHS)

char* vstrchrnul8(const char* Str, int Char) {
	const unsigned char UChar = Char;
	Char = UChar;
	if (!Char) {
		return (char*)Str + vstrlen8(Str);

	}

	#ifdef __GNUC__
	typedef st __attribute__((__may_alias__)) word;
	const word* W;
	for (; (uintptr_t)Str % vstrchrnul8_ALIGN; Str++) {
		if (!*Str || * (unsigned char*)Str == Char) {
			return (char*)Str;

		}

	}

	st K = vstrchrnul8_ONES * Char;
	for (W = (word*)Str; !vstrchrnul8_HASZERO(*W) && !vstrchrnul8_HASZERO(*W ^ K); W++);
	Str = (char*)W;
	#endif
	for (; *Str && * (unsigned char*)Str != Char; Str++);
	return (char*)Str;

}

char* vstrrchr8(const char* Str, int Char) {
	return vstrlastchar8(Str, Char);

}

char* vstrstr8(const char* In, const char* Search) {
	if (!Search[0]) {
		return(char*)In;

	}

	In = vstrchr8(In, *Search);
	if (!In || !Search[1]) {
		return (char*)In;

	}
	if (!In[1]) {
		return 0;

	}
	if (!Search[2]) {
		return vstrstr2((const unsigned char*)(void*)In, (const unsigned char*)(void*)Search);

	}
	if (!In[2]) {
		return 0;

	}
	if (!Search[3]) {
		return vstrstr3((const unsigned char*)(void*)In, (const unsigned char*)(void*)Search);

	}
	if (!In[3]) {
		return 0;

	}
	if (!Search[4]) {
		return vstrstr4((const unsigned char*)(void*)In, (const unsigned char*)(void*)Search);

	}

	return vstrstrtw((const unsigned char*)(void*)In, (const unsigned char*)(void*)Search);

}

char* vstrstr2(const unsigned char* In, const unsigned char* Search) {
	u32 Nw = Search[0] << 8 | Search[1], Hw = In[0] << 8 || In[1];
	for(In++; *In && Hw != Nw; Hw = Hw << 8 | *++In);
	return *In ? (char*)In - 1 : 0;

}

char* vstrstr3(const unsigned char* In, const unsigned char* Search) {
	u32 Nw = (u32)Search[0] << 24 | Search[1] << 16 | Search[2] << 8;
	u32 Hw = (u32)In[0] << 24 | In[1] << 16 | In[2] << 8;
	for(In += 2; *In && Hw != Nw; Hw = (Hw|*++In) << 8);
	return *In ? (char*)In - 3: 0;

}

char* vstrstr4(const unsigned char* In, const unsigned char* Search) {
	u32 Nw = (u32)Search[0] << 24 | Search[1] << 16 | Search[2] << 8 | Search[3];
	u32 Hw = (u32)In[0] << 24 | In[1] << 16 | In[2] << 8 | In[3];
	for(In += 3; *In && Hw != Nw; Hw = Hw<<8 | *++In);
	return *In ? (char*)In - 3 : 0;

}

#define vstrstrtw_MAX(a,b) ((a)>(b)?(a):(b))
#define vstrstrtw_MIN(a,b) ((a)<(b)?(a):(b))

#define vstrstrtw_BITOP(a,b,op) \
((a)[(size_t)(b)/(8*sizeof *(a))] op (size_t)1<<((size_t)(b)%(8*sizeof *(a))))

char* vstrstrtw(const unsigned char* In, const unsigned char* Search) {
	const unsigned char* h = In;
	const unsigned char* n = Search;
	const unsigned char *z;
	size_t l, ip, jp, k, p, ms, p0, mem, mem0;
	size_t byteset[32 / sizeof(size_t)] = { 0 };
	size_t shift[256];

	/* Computing length of needle and fill shift table */
	for (l=0; n[l] && h[l]; l++)
	vstrstrtw_BITOP(byteset, n[l], |=), shift[n[l]] = l+1;
	if (n[l]) return 0; /* hit the end of h */

	/* Compute maximal suffix */
	ip = -1; jp = 0; k = p = 1;
	while (jp+k<l) {
		if (n[ip+k] == n[jp+k]) {
			if (k == p) {
				jp += p;
				k = 1;
			} else k++;
		} else if (n[ip+k] > n[jp+k]) {
			jp += k;
			k = 1;
			p = jp - ip;
		} else {
			ip = jp++;
			k = p = 1;
		}
	}
	ms = ip;
	p0 = p;

	/* And with the opposite comparison */
	ip = -1; jp = 0; k = p = 1;
	while (jp+k<l) {
		if (n[ip+k] == n[jp+k]) {
			if (k == p) {
				jp += p;
				k = 1;
			} else k++;
		} else if (n[ip+k] < n[jp+k]) {
			jp += k;
			k = 1;
			p = jp - ip;
		} else {
			ip = jp++;
			k = p = 1;
		}
	}
	if (ip+1 > ms+1) ms = ip;
	else p = p0;

	/* Periodic needle? */
	if (vmemcmp(n, n+p, ms+1)) {
		mem0 = 0;
		p = vstrstrtw_MAX(ms, l-ms-1) + 1;
	} else mem0 = l-p;
	mem = 0;

	/* Initialize incremental end-of-haystack pointer */
	z = h;

	/* Search loop */
	for (;;) {
		/* Update incremental end-of-haystack pointer */
		if (z-h < l) {
			/* Fast estimate for MAX(l,63) */
			size_t grow = l | 63;
			const unsigned char *z2 = (const unsigned char*)vmemchr(z, 0, grow);
			if (z2) {
				z = z2;
				if (z-h < l) return 0;
			} else z += grow;
		}

		/* Check last byte first; advance by shift on mismatch */
		if (vstrstrtw_BITOP(byteset, h[l-1], &)) {
			k = l-shift[h[l-1]];
			if (k) {
				if (k < mem) k = mem;
				h += k;
				mem = 0;
				continue;
			}
		} else {
			h += l;
			mem = 0;
			continue;
		}

		/* Compare right half */
		for (k=vstrstrtw_MAX(ms+1,mem); n[k] && n[k] == h[k]; k++);
		if (n[k]) {
			h += k-ms;
			mem = 0;
			continue;
		}
		/* Compare left half */
		for (k=ms+1; k>mem && n[k-1] == h[k-1]; k--);
		if (k <= mem) return (char *)h;
		h += p;
		mem = mem0;
	}

}

VSTR32_API long int vstrtol8(const char* Str, char** EndPtr, int Base) {

}//    TODO(V): !!!!!!!!!!! Implement

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
	if (s1 == NULL) {
		return -70;

	}

	if (s2 == NULL) {
		return -70;

	}

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

char* vLEGACYrealpath(const char* filename, char* resolved) {

} //        STUB(V): Implement legacy realpath !!!!

char* vLEGACYgcvt(double In, int NumDigits, char* Buf) {

} //        STUB(V): Implement legacy gcvt c library function

void dstrcreate32(const st Size, dstr32* This) {
	This->DataPtr = (vchar *)valloc(Size * sizeof(vchar));
	vset(This->DataPtr, 0, Size * sizeof(vchar));
	This->Size = 0;
	This->Alloc = Size;

}

void dstrdestroy32(dstr32* This) {
	vfree(This->DataPtr);
	This->Size = 0;
	This->Alloc = 0;

}

void dstrchecksize32(const st TargetSize, dstr32* This) {
	st NewSize = dpow2(TargetSize);

	if (TargetSize < This->Alloc) {
		return;

	}

	if (NewSize < VLIB_DSTR32_SMALLEST_SIZE) {
		NewSize = VLIB_DSTR32_SMALLEST_SIZE;

	}

	This->DataPtr = (vchar *)drealloc(This->DataPtr, NewSize * sizeof(vchar));
	This->Alloc = NewSize;

}

void dstrset32(const vchar* Str, const st Size, dstr32* This) {
	dstrchecksize32(Size, This);
	This->Size = Size;
	vcpy(This->DataPtr, Str, Size * sizeof(vchar));

}

st vinttostr8(u64 Var, char* Result, st MaxSize) {
	if (MaxSize == 0) {
		return 0;

	}

	if (MaxSize == 1) {
		*Result = 0;
		return 0;

	}

	const st TotalDigitsOrig = vdigitlen(Var);
	st TotalDigits = TotalDigitsOrig;
	if ((TotalDigits + 1) > MaxSize) {
		TotalDigits = MaxSize - 1;

	}

	Result[TotalDigits] = 0;

	const st TotalIter = TotalDigits;
	st v = 0;
	for (; v < (TotalIter - 1); v++) {
 		Result[TotalDigits - 1] = Var % 10 + 48;
		Var = Var / 10;
		TotalDigits--;

	}

	if ((v + 1) < TotalDigitsOrig) {
		Result[0] = '<';

	}
	else {
		Result[0] = Var + 48;

	}

	return v + 1;

}

st vinttostr32(u64 Var, vchar* Result, st MaxSize) {
	if (MaxSize == 0) {
		return 0;

	}

	if (MaxSize == 1) {
		*Result = 0;
		return 0;

	}

	const st TotalDigitsOrig = vdigitlen(Var);
	st TotalDigits = TotalDigitsOrig;
	if ((TotalDigits + 1) > MaxSize) {
		TotalDigits = MaxSize - 1;

	}

	Result[TotalDigits] = 0;

	const st TotalIter = TotalDigits;
	st v = 0;
	for (; v < (TotalIter - 1); v++) {
		Result[TotalDigits - 1] = Var % 10 + 48;
		Var = Var / 10;
		TotalDigits--;

	}

	if ((v + 1) < TotalDigitsOrig) {
		Result[0] = L'<';

	}
	else {
		Result[0] = Var + 48;

	}

	return v + 1;

}

/*
	void string::u64tohex(u64 In, string& Target, const u32 Pos) {
	if (In == 0) {
	Target.insert(L'0', Pos);
	Target.insert(L'0', Pos);
	Target.insert(L'x', Pos);
	Target.insert(L'0', Pos);
	return;

	}

	while (In >= 16) {
	if (In % 16 < 10) {
	Target.insert(In % 16 + 48, Pos);

	}
	else {
	Target.insert(In % 16 + 55, Pos);

	}
	In = In / 16;

	}
	if (In % 16 < 10) {
	Target.insert(In % 16 + 48, Pos);

	}
	else {
	Target.insert(In % 16 + 55, Pos);

	}
	Target.insert(L'x', Pos);
	Target.insert(L'0', Pos);

	}
	*/

st vinttohex8(u64 Var, char* Result, st MaxSize) {
	if (Var == 0) {
		if (MaxSize < 5) {
			if (MaxSize != 0) {
				Result[0] = 0;

			}
			return 0;

		}

		Result[0] = '0';
		Result[1] = 'x';
		Result[2] = '0';
		Result[3] = '0';
		Result[4] = 0;

		return 4;

	}

	if (MaxSize < 19) {
		if (MaxSize != 0) {
			Result[0] = 0;

		}

		return 0;

	}

	st Digit = 17;
	for (st v = 0; v < 15; v++) {
		if (Var % 16 < 10) {
			Result[Digit] = Var % 16 + 48;

		}
		else {
			Result[Digit] = Var % 16 + 55;

		}

		Var = Var / 16;
		Digit--;

	}

	if (Var % 16 < 10) {
		Result[2] = Var % 16 + 48;

	}
	else {
		Result[2] = Var % 16 + 55;

	}

	Result[0] = '0';
	Result[1] = 'x';
	Result[18] = 0;
	return 18;

}

st vinttohex8b32(u32 Var, char* Result, st MaxSize) {
	if (Var == 0) {
		if (MaxSize < 5) {
			if (MaxSize != 0) {
				Result[0] = 0;

			}
			return 0;

		}

		Result[0] = '0';
		Result[1] = 'x';
		Result[2] = '0';
		Result[3] = '0';
		Result[4] = 0;

		return 4;

	}

	if (MaxSize < 11) {
		if (MaxSize != 0) {
			Result[0] = 0;

		}

		return 0;

	}

	st Digit = 9;
	for (st v = 0; v < 7; v++) {
		if (Var % 16 < 10) {
			Result[Digit] = Var % 16 + 48;

		}
		else {
			Result[Digit] = Var % 16 + 55;

		}

		Var = Var / 16;
		Digit--;

	}

	if (Var % 16 < 10) {
		Result[2] = Var % 16 + 48;

	}
	else {
		Result[2] = Var % 16 + 55;

	}

	Result[0] = '0';
	Result[1] = 'x';
	Result[10] = 0;
	return 10;

}

char* vstrlastchar8(const char* Str, int Char) {
	return (char*)vmemrchr(Str, Char, vstrlen8(Str) + 1);

}

void vformaterror(const char* Message) {
	vsys_writeConsoleNullStr(Message);
	vsys_writeConsoleNullStr("\n");

}

st vformat8(const char* Fmt, char* Buf, st BufSize, ...) {
	v_varargList Args;
	v_varargStart(Args, BufSize);

	st BufPosition = 0;
	while (*Fmt != 0) {
		bool IsBackToBackExpression;
		IsBackToBackExpression = false;
		if (*Fmt == '{') {
			vformat8_expression_back_to_back:
				(void)NULL;
			bool IsSecondExpression = false;
			st TypeParameterPos = 0;
			char TypeParameter[64] = { 0 };
			st FormatParameterPos = 0;
			char FormatParameter[64] = { 0 };
			while (*Fmt != '}') {
				if (*Fmt == 0) {
					vformaterror("Format expression malformed, could not find trailing \"}\" during parsing");
					return BufPosition;

				}
				switch (*Fmt) {
					case ':':
						IsSecondExpression = true;
						break;

					case '}':
						break;

					case '{':
						break;

					default:
						if (IsSecondExpression) {
							if (FormatParameterPos > 63) {
								vformaterror("Format parameter is more than 64 characters long, this is not handleled by the formatting parser");
								Buf[BufPosition] = 0;
								return BufPosition;

							}

							FormatParameter[FormatParameterPos] = *Fmt;
							FormatParameter[FormatParameterPos + 1] = 0;
							FormatParameterPos++;

						}
						else {
							if (TypeParameterPos > 63) {
								vformaterror("Type parameter is more than 64 characters long, this is not handleled by the formatting parser");
								Buf[BufPosition] = 0;
								return BufPosition;

							}

							TypeParameter[TypeParameterPos] = *Fmt;
							TypeParameter[TypeParameterPos + 1] = 0;
							TypeParameterPos++;

						}
						break;

				}
				Fmt++;

			}
			Fmt++;

			if (*Fmt == '{') {
				//vsys_writeConsole(Fmt, 1);
				IsBackToBackExpression = true;

			}

			//vsys_writeConsoleNullStr("#");
			//vsys_writeConsoleNullStr(TypeParameter);
			//vsys_writeConsoleInteger(TypeParameterPos);
			//vsys_writeConsoleNullStr(FormatParameter);
			//vsys_writeConsoleInteger(FormatParameterPos);
			//            TODO(V): Use a switch with hashing to goto the right one instad of doing string comparasons like that
			if (vformatisexactmatch8(TypeParameter, "u32") ||
			vformatisexactmatch8(TypeParameter, "u16") ||
				vformatisexactmatch8(TypeParameter, "u8")){
				if (vstrlen8(FormatParameter) == 0) {
					st IntSize = vinttostr8(v_vararg(Args, u32), Buf + BufPosition, BufSize - BufPosition);
					BufPosition += IntSize;

				}
				else if (vformatisexactmatch8(FormatParameter, "hex")) {
					st IntSize = vinttohex8b32(v_vararg(Args, u32), Buf + BufPosition, BufSize - BufPosition);
					BufPosition += IntSize;

				}
				else {
					vformaterror("Unknown format specifier for u32");

				}

			}
			else if (vformatisexactmatch8(TypeParameter, "u64")) {
				if (vstrlen8(FormatParameter) == 0) {
					st IntSize = vinttostr8(v_vararg(Args, u64), Buf + BufPosition, BufSize - BufPosition);
					BufPosition += IntSize;

				}
				else if (vformatisexactmatch8(FormatParameter, "hex")) {
					st IntSize = vinttohex8(v_vararg(Args, u64), Buf + BufPosition, BufSize - BufPosition);
					BufPosition += IntSize;

				}
				else {
					vformaterror("Unknown format specifier for u64");

				}

			}
			else if (vformatisexactmatch8(TypeParameter, "i64")) {
				if (vstrlen8(FormatParameter) == 0) {
					i64 Var = v_vararg(Args, i64);
					if (Var < 0) {
						Var = -Var;
						if ((BufSize - BufPosition) > 1) {
							Buf[BufPosition] = '-';
							BufPosition++;

						}

					}
					st IntSize = vinttostr8(Var, Buf + BufPosition, BufSize - BufPosition);
					BufPosition += IntSize;

				}
				else if (vformatisexactmatch8(FormatParameter, "hex")) {
					st IntSize = vinttohex8(v_vararg(Args, u64), Buf + BufPosition, BufSize - BufPosition);
					BufPosition += IntSize;

				}
				else {
					vformaterror("Unknown format specifier for i64");

				}

			}
			else if (vformatisexactmatch8(TypeParameter, "i32")) {
				//vsys_writeConsoleNullStr("VVVVV");
				if (vstrlen8(FormatParameter) == 0) {
					i32 Var = v_vararg(Args, i32);
					if (Var < 0) {
						Var = -Var;
						if ((BufSize - BufPosition) > 1) {
							Buf[BufPosition] = '-';
							BufPosition++;

						}

					}
					//vsys_writeConsoleNullStr("######");
					//vsys_writeConsoleInteger(Var);
					//vsys_writeConsoleNullStr("#");

					st IntSize = vinttostr8(Var, Buf + BufPosition, BufSize - BufPosition);
					BufPosition += IntSize;

				}
				else if (vformatisexactmatch8(FormatParameter, "hex")) {
					st IntSize = vinttohex8b32(v_vararg(Args, u32), Buf + BufPosition, BufSize - BufPosition);
					BufPosition += IntSize;

				}
				else {
					vformaterror("Unknown format specifier for i32/int");

				}

			}
			else if (vformatisexactmatch8(TypeParameter, "i16")) {
				if (vstrlen8(FormatParameter) == 0) {
					i32 Var = v_vararg(Args, i32);
					if (Var < 0) {
						Var = -Var;
						if ((BufSize - BufPosition) > 1) {
							Buf[BufPosition] = '-';
							BufPosition++;

						}

					}
					st IntSize = vinttostr8(Var, Buf + BufPosition, BufSize - BufPosition);
					BufPosition += IntSize;

				}
				else {
					vformaterror("Unknown format specifier for i16");

				}

			}
			else if (vformatisexactmatch8(TypeParameter, "i8")) {
				if (vstrlen8(FormatParameter) == 0) {
					i32 Var = v_vararg(Args, i32);
					if (Var < 0) {
						Var = -Var;
						if ((BufSize - BufPosition) > 1) {
							Buf[BufPosition] = '-';
							BufPosition++;

						}

					}
					st IntSize = vinttostr8(Var, Buf + BufPosition, BufSize - BufPosition);
					BufPosition += IntSize;

				}
				else {
					vformaterror("Unknown format specifier for i8");

				}

			}

			//            NOTE(V): String insertion
			else if (vformatisexactmatch8(TypeParameter, "cstr") || vformatisexactmatch8(TypeParameter, "nullstr")) {
				if (vstrlen8(FormatParameter) == 0) {
					char* InStr = v_vararg(Args, char*);
					if (InStr) {
						st InSize = vstrlen8(InStr);
						if (InSize < (BufSize - BufPosition)) {
							vcpy(Buf + BufPosition, InStr, BufSize - BufPosition);
							BufPosition += InSize;

						}

					}

				}
				else {
					vformaterror("Unknown format specifier for cstr/nullstr");

				}

			}

			//            NOTE(V): Tostr enum functions
			else if (vformatisexactmatch8(TypeParameter, "mdConVarType")) {
				if (vstrlen8(FormatParameter) == 0) {
					u64 Var = v_vararg(Args, u64);
					const char* Str = vtostr_mdConVarType(Var);
					const st StrLen = vstrlen8(Str);
					if ((BufSize - BufPosition) > StrLen) {
						vcpy(Buf + BufPosition, Str, StrLen);
						BufPosition += StrLen;

					}

				}
				else {
					vformaterror("Unknwon format specifier for mdConVarType");

				}

			}

			//            NOTE(V): Ptr utils
			else if (vformatisexactmatch8(TypeParameter, "eol")) {
				if (vstrlen8(FormatParameter) == 0) {
					if ((BufSize - BufPosition) > 1) {
						Buf[BufPosition] = '\n';
						BufPosition++;

					}

				}
				else {
					vformaterror("Unknown format specifier for eol");

				}

			}
			else if (vformatisexactmatch8(TypeParameter, "ptr") || vformatisexactmatch8(TypeParameter, "p")) {
				if (vstrlen8(FormatParameter) == 0) {
					st HexSize = vinttohex8(v_vararg(Args, u64), Buf + BufPosition, BufSize - BufPosition);
					BufPosition += HexSize;

				}
				else if (vformatisexactmatch8(FormatParameter, "int") || vformatisexactmatch8(FormatParameter, "integer")) {
					st IntSize = vinttostr8(v_vararg(Args, u64), Buf + BufPosition, BufSize - BufPosition);
					BufPosition += IntSize;

				}
				else {
					vformaterror("Unknown format specifier for ptr");

				}

			}
			//            NOTE(V): Binary
			else if (vformatisexactmatch8(TypeParameter, "bool")) {
				if (vstrlen8(FormatParameter) == 0) {
					const bool Val = v_vararg(Args, u32);
					if (Val) {
						if ((BufSize - BufPosition) > 4) {
							Buf[BufPosition] = 't';
							Buf[BufPosition + 1] = 'r';
							Buf[BufPosition + 2] = 'u';
							Buf[BufPosition + 3] = 'e';
							BufPosition += 4;

						}

					}
					else {
						if ((BufSize - BufPosition) > 5) {
							Buf[BufPosition] = 'f';
							Buf[BufPosition + 1] = 'a';
							Buf[BufPosition + 2] = 'l';
							Buf[BufPosition + 3] = 's';
							Buf[BufPosition + 4] = 'e';
							BufPosition += 5;

						}

					}

				}
				else if (vformatisexactmatch8(FormatParameter, "num") || vformatisexactmatch8(FormatParameter, "number")) {
					const bool Val = v_vararg(Args, u32);
					if (Val) {
						if ((BufSize - BufPosition) > 1) {
							Buf[BufPosition] = '1';
							BufPosition++;

						}

					}
					else {
						if ((BufSize - BufPosition) > 1) {
							Buf[BufPosition] = '0';
							BufPosition++;

						}

					}

				}
				else {
					vformaterror("Unknown format specifier for bool");

				}

			}
			else if (vformatisexactmatch8(TypeParameter, "null")) {
				if (vstrlen8(FormatParameter) == 0) {
					if ((BufSize - BufPosition) > 1) {
						Buf[BufPosition] = 0;
						BufPosition++;

					}

				}
				else {
					vformaterror("Unknown format specifier for null");

				}

			}
			else {
				vformaterror("Unknown type specifier");

			}

		}

		if (*Fmt == 0) {
			break;

		}

		if (BufPosition >= BufSize) {
			vformaterror("Ran out of buffer space while formatting");
			Buf[BufSize] = 0;
			return BufPosition;

		}

		if (IsBackToBackExpression) {
			//vsys_writeConsoleNullStr("#");
			IsBackToBackExpression = false;
			goto vformat8_expression_back_to_back;

		}

		Buf[BufPosition] = *Fmt;
		BufPosition++;
		Fmt++;

	}

	v_varargEnd(Args);
	Buf[BufPosition] = 0;
	return BufPosition;

}

bool vformatisexactmatch8(const char* Buf, const char* Search) {
	const st BufLen = vstrlen8(Buf);
	const st SearchLen = vstrlen8(Search);
	if (BufLen != SearchLen) {
		return false;

	}

	for (st v = 0; v < BufLen; v++) {
		if (Buf[v] != Search[v]) {
			return false;

		}

	}

	return true;

}

VLIB_CABIEND