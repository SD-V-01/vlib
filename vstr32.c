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
#include "mdos.h"
#include "openxr/xrmyth.h"
#include "vulkan/vkmyth.h"
#include "vmath.h"
#include "vhash.h"
#include "mderror.h"

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
	return 0;

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

bool visdigit8(const char In) {
	return In - '0' < 10;

}

bool visdigit32(const vchar In) {
	return In - '0' < 10;

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
	return NULL;

} //        STUB(V): Implement legacy realpath !!!!

char* vLEGACYgcvt(double In, int NumDigits, char* Buf) {
	return NULL;

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
	//vsys_writeConsoleInteger(TotalIter);
	//vsys_writeConsoleNullStr("#");

	const size_t TotalIter = TotalDigits;
	size_t v = 0;
	if (TotalIter != 0) {
		for (; v < (TotalIter - 1); v++) {
			Result[TotalDigits - 1] = Var % 10 + 48;
			Var = Var / 10;
			TotalDigits--;

		}

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
	if (TotalIter != 0) {
		for (; v < (TotalIter - 1); v++) {
			Result[TotalDigits - 1] = Var % 10 + 48;
			Var = Var / 10;
			TotalDigits--;

		}

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

static void vstr32_splitFloatInternal(double Val, u64* IntegerPart, u64* DecimalPart, i32* Exponent) {
	(*IntegerPart) = (u64)Val;
	double Remainder = Val - (*IntegerPart);

	Remainder *= 1e9;
	(*DecimalPart) = (u64)Remainder;

	Remainder -= (*DecimalPart);
	if (Remainder >= 0.5) {
		(*DecimalPart)++;
		if ((*DecimalPart) >= 1000000000) {
			(*DecimalPart) = 0;
			(*IntegerPart)++;
			if ((*Exponent) != 0 && (*IntegerPart) >= 10) {
				(*Exponent)++;
				(*IntegerPart) = 1;

			}

		}

	}

}

static i32 vstr32_normalizeFloatInternal(double Val) {
	const double PositiveExpThreshold = 1e7;
	const double NegativeExpThreshold = 1e-5;
	int exponent = 0;

	if (Val >= PositiveExpThreshold) {
		if (Val >= 1e256) {
			Val /= 1e256;
			exponent += 256;
		}
		if (Val >= 1e128) {
			Val /= 1e128;
			exponent += 128;
		}
		if (Val >= 1e64) {
			Val /= 1e64;
			exponent += 64;
		}
		if (Val >= 1e32) {
			Val /= 1e32;
			exponent += 32;
		}
		if (Val >= 1e16) {
			Val /= 1e16;
			exponent += 16;
		}
		if (Val >= 1e8) {
			Val /= 1e8;
			exponent += 8;
		}
		if (Val >= 1e4) {
			Val /= 1e4;
			exponent += 4;
		}
		if (Val >= 1e2) {
			Val /= 1e2;
			exponent += 2;
		}
		if (Val >= 1e1) {
			Val /= 1e1;
			exponent += 1;
		}
	}

	if (Val > 0 && Val <= NegativeExpThreshold) {
		if (Val < 1e-255) {
			Val *= 1e256;
			exponent -= 256;
		}
		if (Val < 1e-127) {
			Val *= 1e128;
			exponent -= 128;
		}
		if (Val < 1e-63) {
			Val *= 1e64;
			exponent -= 64;
		}
		if (Val < 1e-31) {
			Val *= 1e32;
			exponent -= 32;
		}
		if (Val < 1e-15) {
			Val *= 1e16;
			exponent -= 16;
		}
		if (Val < 1e-7) {
			Val *= 1e8;
			exponent -= 8;
		}
		if (Val < 1e-3) {
			Val *= 1e4;
			exponent -= 4;
		}
		if (Val < 1e-1) {
			Val *= 1e2;
			exponent -= 2;
		}
		if (Val < 1e0) {
			Val *= 1e1;
			exponent -= 1;
		}
	}

	return exponent;

}

st vdoubletostr8(double Val, char* Result, st MaxSize) {
	if (vmathisnan(Val)) {
		if (MaxSize >= 4) {
			Result[0] = 'N';
			Result[1] = 'A';
			Result[2] = 'N';
			Result[3] = 0;
			return 3;

		}
		else {
			return 0;

		}

	}

	st ResPos = 0;

	if (Val < 0.0) {
		//vsys_writeConsoleNullStr("#######");
		if (MaxSize < (ResPos + 2)) {
			Result[ResPos] = 0;
			return ResPos;

		}
		Result[ResPos] = '-';
		ResPos++;
		Val = -Val;

	}

	if (vmathisinf(Val)) {
		if (MaxSize < (ResPos + 4)) {
			Result[ResPos] = 0;
			return ResPos;

		}
		Result[ResPos] = 'I';
		Result[ResPos + 1] = 'F';
		Result[ResPos + 2] = 'N';
		ResPos += 3;

	}

	u64 IntegrapPart;
	u64 DecimalPart;
	i32 Exponent;
	Exponent = vstr32_normalizeFloatInternal(Val);
	vstr32_splitFloatInternal(Val, &IntegrapPart, &DecimalPart, &Exponent);

	/*
	vsys_writeConsoleInteger(IntegrapPart);
	vsys_writeConsoleNullStr("####");
	vsys_writeConsoleInteger(DecimalPart);
	vsys_writeConsoleNullStr("####");
	vsys_writeConsoleInteger(Exponent);
		*/

	if (MaxSize < ResPos) {
		Result[MaxSize - 1] = 0;
		return ResPos;

	}
	st IntegerSize = vinttostr8(IntegrapPart, &(Result[ResPos]), MaxSize - ResPos);
	if (MaxSize < (ResPos + IntegerSize)) {
		Result[MaxSize - 1] = 0;
		return ResPos;

	}
	ResPos += IntegerSize;

	if (DecimalPart != 0) {
		if (MaxSize < (ResPos + 2)) {
			Result[MaxSize - 1] = 0;
			return ResPos;

		}
		Result[ResPos] = '.';
		ResPos++;

		i32 Width = 9;
		//vsys_writeConsoleInteger(DecimalPart);
		//vsys_writeConsoleNullStr("######");
		while (DecimalPart % 10 == 0 && Width > 0) {
			DecimalPart /= 10;
			Width--;

		}
		//vsys_writeConsoleInteger(DecimalPart);

		st DecimalSize = vinttostr8(DecimalPart, &(Result[ResPos]), MaxSize - ResPos);
		if (MaxSize < (ResPos + DecimalSize)) {
			Result[MaxSize - 1] = 0;
			return ResPos;

		}
		ResPos += DecimalSize;

	}

	//vsys_writeConsoleInteger(Exponent);
	const st SizeOfPosExp = vdigitlensigned(Exponent) + 3;
	if (MaxSize < (ResPos + SizeOfPosExp)) {
		Result[MaxSize - 1] = 0;
		return ResPos;

	}

	if (Exponent > 0) {
		Result[ResPos] = 'e';
		Result[ResPos + 1] = '+';
		ResPos += 2;
		st ExpSize = vinttostr8(Exponent, Result + ResPos, MaxSize - ResPos);
		ResPos += ExpSize;

	}
	else if (Exponent < 0) {
		Result[ResPos] = 'e';
		Result[ResPos + 1] = '-';
		ResPos += 2;
		st ExpSize = vinttostr8(-Exponent, Result + ResPos, MaxSize - ResPos);
		ResPos += ExpSize;

	}

	Result[ResPos] = 0;
	return ResPos;

}

char* vstrlastchar8(const char* Str, int Char) {
	return (char*)vmemrchr(Str, Char, vstrlen8(Str) + 1);

}

void vformaterror(const char* Message) {
	//vsys_writeConsoleNullStr(Message);
	//vsys_writeConsoleNullStr("\n");

	VLOGNF("VFormat", Message);

}

st vformat8(const char* Fmt, char* Buf, st BufSize, ...) {
	v_varargList Args;
	v_varargStart(Args, BufSize);
	st Result = vformat8impl(Fmt, Buf, BufSize, Args);
	v_varargEnd(Args);

	return Result;

}

u64 vformathash(const char* In) {
	return vfnv64std(In, vstrlen8(In));

}

st vformat8impl(const char* Fmt, char* Buf, sst BufSize, v_varargList Args){
//    NOTE(V): Why dose c++ fucking crash for no reason ???
	//#ifdef VPP
	//return 0;
	//#endif

	#ifdef VPP
	//vsys_writeConsoleInteger((unsigned long int)BufSize);

	#endif

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

			u64 FmtHash = vformathash(TypeParameter);

			switch (FmtHash) {

				case 0xd89903186b764185: // u32
				case 0xd89905186b76452b: // u16
				case 0x08325307b4eb15e6: // u8
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
						u32 Dud = v_vararg(Args, u32);
						VUNDEF(Dud);
					
					}
					
					break;

				case 0xd898fe186b76390c: // u64
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
						u64 Dud = v_vararg(Args, u64);
						VUNDEF(Dud);

					}

					break;

				case 0x08325507b4eb1930: // st
				case 0x5c90cdc16ceef19f: // size_t
					if (vstrlen8(FormatParameter) == 0) {
						st IntSize = vinttostr8(v_vararg(Args, st), Buf + BufPosition, BufSize - BufPosition);
						BufPosition += IntSize;

					}
					else if (vformatisexactmatch8(FormatParameter, "hex")) {
						st IntSize = vinttohex8(v_vararg(Args, st), Buf + BufPosition, BufSize - BufPosition);
						BufPosition += IntSize;

					}
					else {
						vformaterror("Unknown format specifier for st");
						st Dud = v_vararg(Args, st);
						VUNDEF(Dud);

					}

					break;

				case 0xd8c1ee186b992328: // i64
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
						i64 Dud = v_vararg(Args, i64);
						VUNDEF(Dud);

					}

					break;

				case 0xd8c1eb186b991e31: // i32
				case 0xd8c1ed186b99215f: // i16
				case 0x08325f07b4eb2a7a: // i8
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
					else if (vformatisexactmatch8(FormatParameter, "hex")) {
						st IntSize = vinttohex8b32(v_vararg(Args, u32), Buf + BufPosition, BufSize - BufPosition);
						BufPosition += IntSize;

					}
					else {
						vformaterror("Unknown format specifier for i32/int");
						i32 Dud = v_vararg(Args, i32);
						VUNDEF(Dud);

					}

					break;

				//            NOTE(V): Floating point

				case 0xec7c599ba78b9449: // float
				case 0xf988dd63276d1506: // double
				case 0xd8cbfb186ba18d8a: // f32
				case 0xd8cc00186ba19603: // f64
				case 0xaf63bd4c8601b7b9: // f
					if (vstrlen8(FormatParameter) == 0) {
						double Var = v_vararg(Args, double);
						st VarSize = vdoubletostr8(Var, Buf + BufPosition, BufSize - BufPosition);
						BufPosition += VarSize;

					}
					else {
						vformaterror("Unknown format specifier for double");
						double Var = v_vararg(Args, double);
						VUNDEF(Var);

					}

					break;

				//            NOTE(V): String insertion

				case 0x1c86e37ef0dafb11: // cstr
				case 0xa117a11f63f461d7: // nullstr
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
						char* Dud = v_vararg(Args, char*);
						VUNDEF(Dud);

					}

					break;

				//            NOTE(V): Tostr enum functions

				case 0xbffd56fdac81e005: // mdConVarType
					if (vstrlen8(FormatParameter) == 0) {
						u64 Var = v_vararg(Args, u64);
						const char* Str = vtostr_mdConVarType((mdConVarType)Var);
						const st StrLen = vstrlen8(Str);
						if ((BufSize - BufPosition) > StrLen) {
							vcpy(Buf + BufPosition, Str, StrLen);
							BufPosition += StrLen;

						}

					}
					else {
						vformaterror("Unknwon format specifier for mdConVarType");
						u64 Dud = v_vararg(Args, u64);
						VUNDEF(Dud);

					}

					break;

				#ifndef MYTH_XR_NO_TOSTR

				case 0xace723cabe0b998e: // xrobjecttype
					if (vstrlen8(FormatParameter) == 0) {
						i32 Var = v_vararg(Args, i32);
						const char* Str = vtostr8_XrObjectType((XrObjectType)Var);
						const st StrLen = vstrlen8(Str);
						if ((BufSize - BufPosition) > StrLen) {
							vcpy(Buf + BufPosition, Str, StrLen);
							BufPosition += StrLen;

						}

					}
					else {
						vformaterror("Unknown format specifier for xrobjecttype/XrObjectType");
						i32 Dud = v_vararg(Args, i32);
						VUNDEF(Dud);

					}

					break;

				#endif

				//            NOTE(V): Ptr utils

				case 0xd8cfa7186ba4e7bf: // eol
					if (vstrlen8(FormatParameter) == 0) {
						if ((BufSize - BufPosition) > 1) {
							Buf[BufPosition] = '\n';
							BufPosition++;

						}

					}
					else {
						vformaterror("Unknown format specifier for eol");

					}

					break;

				case 0xd8a9be186b843fd9: // ptr
				case 0xaf63bd4c8601b7af: // p
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
						u64 Dud = v_vararg(Args, u64);
						VUNDEF(Dud);

					}

					break;

				//            NOTE(V): Binary

				case 0x2713257ef75d5119: // bool
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
						u32 Dud = v_vararg(Args, u32);
						VUNDEF(Dud);

					}

					break;

				case 0xbe851a7ebbf8a646: // null
					if (vstrlen8(FormatParameter) == 0) {
						if ((BufSize - BufPosition) > 1) {
							Buf[BufPosition] = 0;
							BufPosition++;

						}

					}
					else {
						vformaterror("Unknown format specifier for null");

					}

					break;

				default:
					vformaterror("Unknown type specifier");

					if ((BufSize - BufPosition) > 16) {
						Buf[BufPosition] = 'V';
						Buf[BufPosition + 1] = 'F';
						Buf[BufPosition + 2] = 'M';
						Buf[BufPosition + 3] = 'T';
						Buf[BufPosition + 4] = '_';
						Buf[BufPosition + 5] = 'T';
						Buf[BufPosition + 6] = 'Y';
						Buf[BufPosition + 7] = 'P';
						Buf[BufPosition + 8] = 'E';
						Buf[BufPosition + 9] = '_';
						Buf[BufPosition + 10] = 'E';
						Buf[BufPosition + 11] = 'R';
						Buf[BufPosition + 12] = 'R';
						Buf[BufPosition + 13] = 'O';
						Buf[BufPosition + 14] = 'R';
						Buf[BufPosition + 15] = 0;
						BufPosition += 15;
						return BufPosition;

					}

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

st vgetfirstsubstr8(const char* In, const char StopAt, char* Buf, st BufSize) {
	VASSERT(In, "Invalid string passed into vgetfirstsubstr8");
	VASSERT(Buf, "Invalid output buffer passed into vgetfirstsubstr8");
	if (BufSize < 2) {
		return 0;

	}

	if (vstrlen8(In) == 0) {
		return 0;

	}

	st FinalSize = 0;
	for (st v = 0; v < vstrlen8(In); v++) {
		if ((FinalSize + 1) > BufSize) {
//            NOTE(V): Ran out of buffer space, returning early
			Buf[FinalSize] = In[FinalSize];
			FinalSize++;
			Buf[FinalSize] = 0;
			FinalSize++;
			return FinalSize;

		}

		if (In[v] == 0 || In[v] == StopAt) {
			Buf[FinalSize] = 0;
			FinalSize++;
			return FinalSize;

		}

		Buf[FinalSize] = In[FinalSize];
		FinalSize++;

	}

	Buf[FinalSize] = 0;
	VASSERT(0, "Control flow should never go here");
	return FinalSize;

}

bool vischarpresent8(const char* In, const char Char) {
	VASSERT(In, "Invalid string passed to vischarpresent8");
	const st InSize = vstrlen8(In);
	for (st v = 0; v < InSize; v++) {
		if (In[v] == Char) {
			return true;

		}

	}

	return false;

}

VLIB_CABIEND
