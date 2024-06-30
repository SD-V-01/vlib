////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   str.cpp
//  Version:     v1.00
//  Created:     03/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#ifdef TENX_PARSER
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include "vmem.h"
#include "str.h"
#include "dstr.h"
#include "vulkan/vulkan_core.h"
#include "openxr/openxr.h"

#define STRING_DEFAULT_SIZE 16
#define MYTH_DLLEXP

#ifdef MYTH_GCC
#pragma GCC diagnostic ignored "-Wwrite-strings"

#endif

namespace VLIB_NAMESPACE {
    template struct MYTH_DLLEXP dmem < string >;

    string::string() {
        initinternal(STRING_DEFAULT_SIZE);
        StringSize = 0;

    }

    string::string(const char32_t* Str) {
        u32 StrLen = mstrlen(Str);
        initinternal(dpow2(StrLen));
        StringSize = StrLen;
        dcpy(DataPtr, Str, StrLen * sizeof(char32_t));

    }

    string::string(const char* Str) {
        const u32 StrLen = mstrlen(Str);
        char32_t WString[StrLen + 1];
        chartowchar(Str, &WString[0], StrLen);
        WString[StrLen] = 0;
        initinternal(dpow2(StrLen));
        StringSize = StrLen;
        dcpy(DataPtr, &WString[0], StrLen * sizeof(char32_t));

    }

    string::string(const u32 InitSize) {
        initinternal(dpow2(InitSize));
        StringSize = 0;

    }

    string::string(string const& Rhs) {
        init(Rhs.AllocSize);
        StringSize = Rhs.StringSize;
        DataPtr = (char32_t*)dcpy(DataPtr, Rhs.DataPtr, AllocSize * sizeof(char32_t));

    }

    string::~string() {
        quit();

    }

    void string::init() {
        initinternal(STRING_DEFAULT_SIZE);
        StringSize = 0;

    }

    void string::init(u32 Size) {
        initinternal(dpow2(Size));
        StringSize = 0;

    }

    void string::init(string const& Rhs) {
        init(Rhs.AllocSize);
        StringSize = Rhs.StringSize;
        DataPtr = (char32_t*)dcpy(DataPtr, Rhs.DataPtr, AllocSize * sizeof(char32_t));

    }

    u32 string::length32() {
        return StringSize;

    }

    size_t string::length() {
        return (size_t)StringSize;

    }

    u32 string::allocLength() {
        return AllocSize;

    }

    char32_t* string::getWchar() {
        checkSize(StringSize + 1);
        *(DataPtr + StringSize) = 0;
        return DataPtr;

    }

    char32_t* string::data() {
        checkSize(StringSize + 1);
        *(DataPtr + StringSize) = 0;
        return DataPtr;

    }

    const char32_t* string::cdata() const {
        return DataPtr;

    }

    char* string::cstr() {
        char* Result = (char*)dalloc((StringSize + 1) * sizeof(char));
        for (u32 i = 0; i < StringSize; i++) {
            Result[i] = (char)DataPtr[i];

        }
        Result[StringSize] = 0;

        return Result;

    }

    void string::set(const char32_t* Str) {
        size_t Strlen = mstrlen(Str);
        checkSize(Strlen);
        internset(Str, Strlen);

    }

    void string::set(const char* Str) {
        const u32 CharSize = mstrlen(Str);
        //printf("StringSetSize: %i", CharSize);
        char32_t WCharArray[CharSize + 1];
        chartowchar(Str, WCharArray, CharSize);
        WCharArray[CharSize] = 0;
        //printf("%ls,%i\n", &WCharArray[0], CharSize);
        set(&WCharArray[0]);

    }

    void string::addNullEnd() {
        checkSize(StringSize + 1);
        *(DataPtr + StringSize) = 0;

    }

    void string::clear() {
        vset(DataPtr, 0, AllocSize * sizeof(char32_t));
        StringSize = 0;
        checkSize(0);

    }

    void string::clearSize() {
        StringSize = 0;
        addNullEnd();

    }

    void string::append(const char* Str) {
        //const u32 SourceSize = mstrlen(Str);
        //char32_t WcharString[SourceSize + 1] = U""; // Doesent compile under clang ??
        //char32_t WcharString[SourceSize + 1];
        //WcharString[0] = 0;
        //chartowchar(Str, &WcharString[0], SourceSize);
        //WcharString[SourceSize] = 0;
        //append(&WcharString[0]);

        //        TODO(V): Implement
        //printf("Got %s to print\n", Str);
        if (Str != NULL) {
            appendCharArray(Str, mstrlen(Str));

        }
        else {
            formatError(U"Trying to append a string but ptr is NULL !!!");

        }

    }

    void string::append(char* Str) {
        //printf("Got %s to print (nonstatic)", Str);
        if (Str != NULL) {
            appendCharArray(Str, mstrlen(Str));

        }
        else {
            formatError(U"Trying to append a string but ptr is NULL !!!");

        }

    }

    void string::append(const char32_t* Str) {
        const u32 StringLength = mstrlen(Str);
        checkSize(StringSize + StringLength + 1);
        
        for (u32 i = 0; i < StringLength; i++) {
            *(DataPtr + StringSize) = *(Str + i);
            
            StringSize++;

        }

    }

    void string::append(string const& Str) {
        for (u32 i = 0; i < Str.StringSize; i++) {
            *(DataPtr + StringSize) = *(Str.DataPtr + i);
            StringSize++;

        }

    }

    void string::appendChar(const char Char) {
        checkSize(StringSize + 1);
        StringSize++;
        *(DataPtr + StringSize - 1) = (char32_t)Char;

    }

    void string::appendChar(const char32_t Char) {
        checkSize(StringSize + 1);
        StringSize++;
        *(DataPtr + StringSize - 1) = Char;

    }

    void string::appendCharw(const char32_t Char) {
        checkSize(StringSize + 1);
        StringSize++;
        *(DataPtr + StringSize - 1) = Char;

    }

    void string::appendCharEnd(const char32_t Char) {
        checkSize(StringSize + 1);
        StringSize++;
        dmove(DataPtr + 1, DataPtr, StringSize - 1);
        *DataPtr = Char;

    }

    void string::appendCharArray(const char* Char, u32 Size) {
        //printf("Printing %u chars %s\n", Size, Char);
        for (u32 i = 0; i < Size; i++) {
            appendChar(Char[i]);

        }

    }

    bool string::isExactMatch(const char32_t In[]) {
        u32 InLength = mstrlen(In);
        if (StringSize != InLength) {
            return false;

        }

        for (u32 i = 0; i < InLength; i++) {
            if (In[i] != *(DataPtr + i)) {
                return false;

            }

        }

        return true;

    }

    void string::insert(char32_t Char, u32 Pos) {
        checkSize(StringSize + 1);
        if (Pos == StringSize) {
            appendCharw(Char);
            return;

        }
        //char32_t TempStor[StringSize] = U"";
        char32_t TempStor[StringSize + 1];
        TempStor[0] = 0;
        dcpy(&TempStor[0], DataPtr + Pos, (StringSize - Pos) * sizeof(char32_t));
        StringSize++;
        dcpy(DataPtr + Pos + 1, &TempStor[0], (StringSize - Pos) * sizeof(char32_t));
        //printf("StringState %ls %ls\n", &TempStor[0], DataPtr);
        *(DataPtr + Pos) = Char;

    }

    void string::insert(char32_t* Src, u32 Pos) {
        const u32 InStrSize = mstrlen(Src);
        u32 CurrentPos = Pos;
        for (u32 i = 0; i < InStrSize; i++) {
            insert(Src[i], CurrentPos);
            CurrentPos++;

        }
        //        TODO(V): Make a better implementation for this

    }

    u64 string::strtou64() {
        u64 Result = 0;

        for (u32 i = 0; i < StringSize; i++) {
            Result = Result * 10 + DataPtr[i] - L'0';

        }

        return Result;

    }

    void string::format(const char32_t* Fmt, ...) {
        va_list Args;
        u32 SizeCheckBase = mstrlen(Fmt) + StringSize;
        checkSize(SizeCheckBase + 10);

        va_start(Args, Fmt);

        while (*Fmt != 0) {
            if (*Fmt == L'{') {
                bool IsSeccondExression = false;
                string TypeParameter { 8 };
                string FormatParameter { 8 };
                while (*Fmt != L'}') {
                    if (*Fmt == 0) {
                        formatError(U"Formatting expresion malformed, could not find trailing \"}\" during parsing");
                        return;

                    }
                    switch (*Fmt) {
                        case L':':
                            IsSeccondExression = true;
                            break;
                        case L'}':
                            break;
                        case L'{':
                            break;
                        default:
                            if (IsSeccondExression) {
                                FormatParameter.appendChar(*Fmt);

                            }
                            else {
                                TypeParameter.appendChar(*Fmt);

                            }
                            break;

                    }
                    Fmt++;

                }
                Fmt++;

                //printf("[%ls] [%ls]\n", TypeParameter.data(), FormatParameter.data());

                if (TypeParameter.isExactMatch(U"u32")) {
                    if (FormatParameter.length() == 0) {
                        u64tostr(va_arg(Args, u32), *this, StringSize);

                    }
                    else if (FormatParameter.isExactMatch(U"str")) {
                        insert(L'"', StringSize);
                        insert(L'"', StringSize);
                        u64tostr(va_arg(Args, u32), *this, StringSize - 1);

                    }
                    else if (FormatParameter.isExactMatch(U"hex")) {
                        u64tohex(va_arg(Args, u32), *this, StringSize);

                    }
                    else {
                        formatError(U"Unknown format specifier for u32 type");

                    }

                }
                else if (TypeParameter.isExactMatch(U"u64")) {
                    if (FormatParameter.length() == 0) {
                        u64tostr(va_arg(Args, u64), *this, StringSize);

                    }
                    else if (FormatParameter.isExactMatch(U"str")) {
                        insert(L'"', StringSize);
                        insert(L'"', StringSize);
                        u64tostr(va_arg(Args, u64), *this, StringSize - 1);

                    }
                    else if (FormatParameter.isExactMatch(U"hex")) {
                        u64tohex(va_arg(Args, u64), *this, StringSize);

                    }
                    else {
                        formatError(U"Unknown format specifier for u64 type");

                    }

                }
                else if (TypeParameter.isExactMatch(U"u16")) {
                    if (FormatParameter.length() == 0) {
                        u64tostr(va_arg(Args, u32), *this, StringSize);

                    }
                    else if (FormatParameter.isExactMatch(U"str")) {
                        insert(L'"', StringSize);
                        insert(L'"', StringSize);
                        u64tostr(va_arg(Args, u32), *this, StringSize - 1);

                    }
                    else if (FormatParameter.isExactMatch(U"hex")) {
                        u64tohex(va_arg(Args, u32), *this, StringSize);

                    }
                    else {
                        formatError(U"Unknown format specifier for u16 type");

                    }

                }
                else if (TypeParameter.isExactMatch(U"u8")) {
                    if (FormatParameter.length() == 0) {
                        u64tostr(va_arg(Args, u32), *this, StringSize);

                    }
                    else if (FormatParameter.isExactMatch(U"str")) {
                        insert(L'"', StringSize);
                        insert(L'"', StringSize);
                        u64tostr(va_arg(Args, u32), *this, StringSize - 1);

                    }
                    else if (FormatParameter.isExactMatch(U"hex")) {
                        u64tohex(va_arg(Args, u32), *this, StringSize);

                    }
                    else {
                        formatError(U"Unknown format specifier for u8 type");

                    }

                }
                else if (TypeParameter.isExactMatch(U"i32")) {
                    if (FormatParameter.length() == 0) {
                        i32 Var = va_arg(Args, i32);
                        if (Var < 0) {
                            Var = -Var;
                            u32 StrPosForMinus = StringSize;
                            u64tostr(Var, *this, StringSize);
                            insert('-', StrPosForMinus);

                        }
                        else {
                            u64tostr(Var, *this, StringSize);

                        }

                    }
                    else {
                        formatError(U"Unknown format specifier for i32 type");

                    }

                }
                else if (TypeParameter.isExactMatch(U"float") || TypeParameter.isExactMatch(U"f32")) {
                    if (FormatParameter.length() == 0) {
                        char FloatString[15] = "";
                        //                        TODO(V): implement the float to string implementation here
                        //                        floattostr is unimplemented yet
                        //floattostr(va_arg(Args, double), *this, 0, StringSize);
                        vlegacy_gcvt((float)va_arg(Args, double), 8, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"hex")) {
                        u64tohex((u32)va_arg(Args, double), *this, StringSize);

                    }
                    else if (FormatParameter.isExactMatch(U"0")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 0, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"1")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 1, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"2")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 2, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"3")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 3, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"4")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 4, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"5")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 5, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"6")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 6, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"7")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 7, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"8")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 8, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"9")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 9, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"10")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 10, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else {
                        formatError(U"Unknown format specifier for float type");

                    }

                }
                else if (TypeParameter.isExactMatch(U"double") || TypeParameter.isExactMatch(U"f64")) {
                    if (FormatParameter.length() == 0) {
                        char FloatString[15] = "";
                        //                        TODO(V): implement the float to string implementation here
                        //                        floattostr is unimplemented yet
                        //floattostr(va_arg(Args, double), *this, 0, StringSize);
                        vlegacy_gcvt((float)va_arg(Args, double), 8, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"hex")) {
                        u64tohex((u64)va_arg(Args, double), *this, StringSize);

                    }
                    else if (FormatParameter.isExactMatch(U"0")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 0, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"1")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 1, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"2")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 2, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"3")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 3, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"4")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 4, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"5")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 5, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"6")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 6, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"7")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 7, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"8")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 8, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"9")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 9, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else if (FormatParameter.isExactMatch(U"10")) {
                        char FloatString[15] = "";
                        vlegacy_gcvt((float)va_arg(Args, double), 10, &FloatString[0]);
                        append(&FloatString[0]);

                    }
                    else {
                        formatError(U"Unknown format specifier for float type");

                    }

                }
                else if (TypeParameter.isExactMatch(U"mem")) {
                    if (FormatParameter.length() == 0) {
                        memtohex(va_arg(Args, u16*), 1024, *this, StringSize);

                    }
                    else {
                        formatError(U"Unknown format specifier for mem dump");

                    }

                }
                else if (TypeParameter.isExactMatch(U"vk")) {
                    if (FormatParameter.length() == 0) {
                        appendVkResult(va_arg(Args, i32), *this);

                    }
                    else {
                        formatError(U"Unknown format specifier for VkResult");

                    }

                }
                else if (TypeParameter.isExactMatch(U"vkphysdevicetype")) {
                    if (FormatParameter.length() == 0) {
                        switch (va_arg(Args, i32)) {
                            case(VK_PHYSICAL_DEVICE_TYPE_OTHER):
                                append(U"VK_PHYSICAL_DEVICE_TYPE_OTHER");
                                break;
                            case(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU):
                                append(U"VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU");
                                break;
                            case(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU):
                                append(U"VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU");
                                break;
                            case(VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU):
                                append(U"VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU");
                                break;
                            case(VK_PHYSICAL_DEVICE_TYPE_CPU):
                                append(U"VK_PHYSICAL_DEVICE_TYPE_CPU");
                                break;
                            case(VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM):
                                append(U"VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM");
                                break;
                            default:
                                append(U"vkphysdevicetype_tostr_error");

                        }

                    }
                    else {
                        formatError(U"Unknown format specifier for vkphysdevicetype");

                    }

                }
                else if (TypeParameter.isExactMatch(U"vkformat")) {
                    if (FormatParameter.length() == 0) {
                        appendVkFormat(va_arg(Args, i32));

                    }
                    else {
                        formatError(U"Unknown format specifier for vkformat");

                    }

                }
                else if (TypeParameter.isExactMatch(U"vkversion")) {
                    if (FormatParameter.length() == 0) {
                        appendVkVersion(va_arg(Args, u32));

                    }
                    else {
                        formatError(U"Unknown format specifier for vkversion");

                    }

                }
                else if (TypeParameter.isExactMatch(U"vkcolorspace")) {
                    if (FormatParameter.length() == 0) {
                        switch (va_arg(Args, i32)) {
                            case (VK_COLOR_SPACE_SRGB_NONLINEAR_KHR):
                                append(U"VK_COLOR_SPACE_SRGB_NONLINEAR_KHR");
                                break;
                            case (VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT):
                                append(U"VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT");
                                break;
                            case (VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT):
                                append(U"VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT");
                                break;
                            case (VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT):
                                append(U"VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT");
                                break;
                            case (VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT):
                                append(U"VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT");
                                break;
                            case (VK_COLOR_SPACE_BT709_LINEAR_EXT):
                                append(U"VK_COLOR_SPACE_BT709_LINEAR_EXT");
                                break;
                            case (VK_COLOR_SPACE_BT709_NONLINEAR_EXT):
                                append(U"VK_COLOR_SPACE_BT709_NONLINEAR_EXT");
                                break;
                            case (VK_COLOR_SPACE_BT2020_LINEAR_EXT):
                                append(U"VK_COLOR_SPACE_BT2020_LINEAR_EXT");
                                break;
                            case (VK_COLOR_SPACE_HDR10_ST2084_EXT):
                                append(U"VK_COLOR_SPACE_HDR10_ST2084_EXT");
                                break;
                            case (VK_COLOR_SPACE_DOLBYVISION_EXT):
                                append(U"VK_COLOR_SPACE_DOLBYVISION_EXT");
                                break;
                            case (VK_COLOR_SPACE_HDR10_HLG_EXT):
                                append(U"VK_COLOR_SPACE_HDR10_HLG_EXT");
                                break;
                            case (VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT):
                                append(U"VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT");
                                break;
                            case (VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT):
                                append(U"VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT");
                                break;
                            case (VK_COLOR_SPACE_PASS_THROUGH_EXT):
                                append(U"VK_COLOR_SPACE_PASS_THROUGH_EXT");
                                break;
                            case (VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT):
                                append(U"VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT");
                                break;
                            case (VK_COLOR_SPACE_DISPLAY_NATIVE_AMD):
                                append(U"VK_COLOR_SPACE_DISPLAY_NATIVE_AMD");
                                break;
                            case (VK_COLOR_SPACE_MAX_ENUM_KHR):
                                append(U"VK_COLOR_SPACE_MAX_ENUM_KHR");
                                break;

                        }

                    }
                    else {
                        formatError(U"Unknown format specifier for vkcolorspace");

                    }

                }
                else if (TypeParameter.isExactMatch(U"vkpresentmode")) {
                    if (FormatParameter.length() == 0) {
                        switch (va_arg(Args, i32)) {
                            case (VK_PRESENT_MODE_IMMEDIATE_KHR):
                                append(U"VK_PRESENT_MODE_IMMEDIATE_KHR");
                                break;
                            case (VK_PRESENT_MODE_MAILBOX_KHR):
                                append(U"VK_PRESENT_MODE_MAILBOX_KHR");
                                break;
                            case (VK_PRESENT_MODE_FIFO_KHR):
                                append(U"VK_PRESENT_MODE_FIFO_KHR");
                                break;
                            case (VK_PRESENT_MODE_FIFO_RELAXED_KHR):
                                append(U"VK_PRESENT_MODE_FIFO_RELAXED_KHR");
                                break;
                            case (VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR):
                                append(U"VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR");
                                break;
                            case (VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR):
                                append(U"VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR");
                                break;
                            case (VK_PRESENT_MODE_MAX_ENUM_KHR):
                                append(U"VK_PRESENT_MODE_MAX_ENUM_KHR");
                                break;

                        }

                    }
                    else {
                        formatError(U"Unknown format specifier for vkpresentmode");

                    }

                }
                else if (TypeParameter.isExactMatch(U"xr")) {
                    if (FormatParameter.length() == 0) {
                        appendXrResult(va_arg(Args, i32), *this);

                    }
                    else {
                        formatError(U"Unknown format specifier for XrResult");

                    }

                }
                else if (TypeParameter.isExactMatch(U"xrversion")) {
                    if (FormatParameter.length() == 0) {
                        appendXrVersion(va_arg(Args, u64), *this);

                    }
                    else {
                        formatError(U"Unknown format specifier for XrVersion");

                    }

                }
                else if (TypeParameter.isExactMatch(U"xrenvblendmode")) {
                    if (FormatParameter.length() == 0) {
                        appendXrEnvBlendMode(va_arg(Args, u32), *this);

                    }
                    else {
                        formatError(U"Unknown format specifier for XrEnvironmentBlendMode");

                    }

                }
                else if (TypeParameter.isExactMatch(U"xrreferencespacetype")) {
                    if (FormatParameter.length() == 0) {
                        switch (va_arg(Args, i32)) {
                            case (XR_REFERENCE_SPACE_TYPE_VIEW):
                                append(U"XR_REFERENCE_SPACE_TYPE_VIEW");
                                break;
                            case (XR_REFERENCE_SPACE_TYPE_LOCAL):
                                append(U"XR_REFERENCE_SPACE_TYPE_LOCAU");
                                break;
                            case (XR_REFERENCE_SPACE_TYPE_STAGE):
                                append(U"XR_REFERENCE_SPACE_TYPE_STAGE");
                                break;
                            case (XR_REFERENCE_SPACE_TYPE_UNBOUNDED_MSFT):
                                append(U"XR_REFERENCE_SPACE_TYPE_UNBOUNDED_MSFT");
                                break;
                            case (XR_REFERENCE_SPACE_TYPE_COMBINED_EYE_VARJO):
                                append(U"XR_REFERENCE_SPACE_TYPE_COMBINED_EYE_VARJO");
                                break;
                            case (XR_REFERENCE_SPACE_TYPE_LOCALIZATION_MAP_ML):
                                append(U"XR_REFERENCE_SPACE_TYPE_LOCALIZATION_MAP_MU");
                                break;
                            case (XR_REFERENCE_SPACE_TYPE_LOCAL_FLOOR_EXT):
                                append(U"XR_REFERENCE_SPACE_TYPE_LOCAL_FLOOR_EXT");
                                break;
                            case (XR_REFERENCE_SPACE_TYPE_MAX_ENUM):
                                append(U"XR_REFERENCE_SPACE_TYPE_MAX_ENUM");
                                break;
                            default:
                                append(U"xrreferencespacetype_TO_STRING_FAILED");

                        }

                    }
                    else {
                        formatError(U"Unknown format specifier for xrreferencespacetype");

                    }

                }
                else if (TypeParameter.isExactMatch(U"xrsessionstate")) {
                    if (FormatParameter.length() == 0) {
                        switch (va_arg(Args, i32)) {
                            case (XR_SESSION_STATE_UNKNOWN):
                                append(U"XR_SESSION_STATE_UNKNOWN");
                                break;
                            case (XR_SESSION_STATE_IDLE):
                                append(U"XR_SESSION_STATE_IDLE");
                                break;
                            case (XR_SESSION_STATE_READY):
                                append(U"XR_SESSION_STATE_READY");
                                break;
                            case (XR_SESSION_STATE_SYNCHRONIZED):
                                append(U"XR_SESSION_STATE_SYNCHRONIZED");
                                break;
                            case (XR_SESSION_STATE_VISIBLE):
                                append(U"XR_SESSION_STATE_VISIBLE");
                                break;
                            case (XR_SESSION_STATE_FOCUSED):
                                append(U"XR_SESSION_STATE_FOCUSED");
                                break;
                            case (XR_SESSION_STATE_STOPPING):
                                append(U"XR_SESSION_STATE_STOPPING");
                                break;
                            case (XR_SESSION_STATE_LOSS_PENDING):
                                append(U"XR_SESSION_STATE_LOSS_PENDING");
                                break;
                            case (XR_SESSION_STATE_EXITING):
                                append(U"XR_SESSION_STATE_EXITING");
                                break;
                            case (XR_SESSION_STATE_MAX_ENUM):
                                append(U"XR_SESSION_STATE_MAX_ENUM");
                                break;
                            default:
                                append(U"xrsessionstate_tostr_error");

                        }

                    }
                    else {
                        formatError(U"Unknown format specifier for xrsessionstate");

                    }

                }
                else if (TypeParameter.isExactMatch(U"string")) {
                    if (FormatParameter.length() == 0) {
                        append(*va_arg(Args, string*));

                    }
                    else {
                        formatError(U"Unknown format specifier for string");

                    }

                }
                else if (TypeParameter.isExactMatch(U"dstr")) {
                    if (FormatParameter.length() == 0) {
                        dstr* CharToPrint = va_arg(Args, dstr*);
                        append((*CharToPrint).data());

                    }
                    else {
                        formatError(U"Unknown format specifier for dstr");

                    }

                }
                else if (TypeParameter.isExactMatch(U"chararray")) {
                    if (FormatParameter.length() == 0) {
                        //formatError(U"Null terminated string are not implemented in formatting yet");
                        //append((const char*)va_arg(Args, char*));
                        
                        char* Ptr = va_arg(Args, char*);
                        u32 Size = mstrlen(Ptr);
                        appendCharArray(Ptr, Size);
                        //printf("Pritning null string %x size %u\n", Ptr, Size);

                    }
                    else {
                        u64 NumberOfChar = FormatParameter.strtou64();
                        //printf("Got %llu chars to print\n", NumberOfChar);
                        appendCharArray(va_arg(Args, char*), NumberOfChar);

                    }

                }
                else if (TypeParameter.isExactMatch(U"ptr")) {
                    if (FormatParameter.length() == 0) {
                        u64tohex(va_arg(Args, u64), *this, StringSize);

                    }
                    else {
                        formatError(U"Unknown format specifier for ptr");

                    }

                }
                else if (TypeParameter.isExactMatch(U"booU")) {
                    if (FormatParameter.length() == 0) {
                        bool Value = va_arg(Args, int);
                        if (Value) {
                            append(U"true");

                        }
                        else {
                            append(U"false");

                        }

                    }
                    else {
                        formatError(U"Unknown format specifier for booU");

                    }

                }

                else {
                    //va_arg(Args, void*);
                    formatError(U"Unknown type specifier");

                }
                //printf("## Formatting stuff %ls %ls\n", TypeParameter.data(), FormatParameter.data());
                //TypeParameter.clear();
                //FormatParameter.clear();

            }
            if (*Fmt == 0) {
                //formatError(U"Detected null char at end of format expression");
                break;

            }

            appendChar(*Fmt);
            Fmt++;

        }

        va_end(Args);

    }

    void string::formatError(const char32_t* Message) {
        u32 MessageLength = mstrlen(Message);
        char CharBuffer[MessageLength + 1];
        wchartochar(Message, CharBuffer, MessageLength);
        CharBuffer[MessageLength] = 0;
        //        TODO(V): Change this to the internal console later when that figured out and we are not using std out anymore
		//        STUB(V): This print statement doesent work anymore because we don't have a c runtime anymore
        //printf("%s", CharBuffer);

    }

	/*
    void string::u64tostr(u64 In, string& Target, const u32 Pos) {
        if (In == 0) {
            Target.insert(L'0', Pos);
            return;

        }

        while(In >= 10) {
            Target.insert(In % 10 + 48, Pos);
            //printf("%i %i\n", In % 10 + 48, In);
            In = In / 10;

        }
        //printf("%i %i\n", In, In);
        Target.insert(In + 48, Pos);

    }*/
	
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

    void string::memtohex(const u16* InPtr, u32 InSize, string& Target, const u32 Pos) {
        u32 AdressHelper = 0;
        Target.appendCharw(L'\n');
        if (InSize < 2) {
            Target.append(U"00x ");

            if (InSize == 0) {
                Target.append(U"00");

            }
            else {
                if (*InPtr < 10) {
                    Target.append(*InPtr + 48);

                }
                else {
                    Target.append(*InPtr + 55);

                }

            }
            return;

        }

        Target.append(U"00x ");
        for (u32 i = 0; i < InSize / 2; i++) {
            if (*InPtr < 16) {
                Target.appendCharw(L'0');
                if (*InPtr < 10) {
                    Target.appendCharw(*InPtr % 16 + 48);

                }
                else {
                    Target.appendCharw(*InPtr % 16 + 55);

                }

            }
            else {
                u16 Val = *InPtr / 16;
                if (Val % 16 < 10) {
                    Target.appendCharw(Val % 16 + 48);

                }
                else {
                    Target.appendCharw(Val % 16 + 55);

                }

                if (*InPtr % 16 < 10) {
                    Target.appendCharw(*InPtr % 16 + 48);

                }
                else {
                    Target.appendCharw(*InPtr % 16 + 55);

                }

            }

            Target.appendCharw(L' ');
            if ((i % 16) == 15) {
                if (true) {
                    Target.appendCharw(L'\n');
                    AdressHelper++;
                    if (AdressHelper >= 16) {
                        AdressHelper = 0;

                    }
                    if (AdressHelper < 10) {
                        Target.appendCharw(AdressHelper + 48);

                    }
                    else {
                        Target.appendCharw(AdressHelper + 55);

                    }
                    Target.append(U"0x ");

                }

            }
            InPtr++;

        }

    }

    #define MYTH_MAX_FLOAT_STR_CAST_PRECISION 10
    static const f64 FloatRoundingStr[MYTH_MAX_FLOAT_STR_CAST_PRECISION + 1] =
    {
        0.5,
        0.05,
        0.005,
        0.0005,
        0.00005,
        0.000005,
        0.0000005,
        0.00000005,
        0.000000005,
        0.0000000005,
        0.00000000005,

    };

    void string::floattostr(f32 In, string& Target, u32 PrecisionDigits, const u32 Pos) {
        if (PrecisionDigits > MYTH_MAX_FLOAT_STR_CAST_PRECISION) {
            PrecisionDigits = MYTH_MAX_FLOAT_STR_CAST_PRECISION;

        }

        if (In < 0) {
            In = -In;
            Target.appendCharw(L'-');

        }

        if (PrecisionDigits == 0) {
            if (In < 1.0) {
                PrecisionDigits = 7;

            }
            else if (In < 10.0) {
                PrecisionDigits = 6;

            }
            else if (In < 100.0) {
                PrecisionDigits = 5;

            }
            else if (In < 1000.0) {
                PrecisionDigits = 4;

            }
            else if (In < 10000.0) {
                PrecisionDigits = 3;

            }
            else if (In < 100000.0) {
                PrecisionDigits = 2;

            }
            else if (In < 1000000.0) {
                PrecisionDigits = 1;

            }
            else {
                PrecisionDigits = 0;

            }

        }

        if (PrecisionDigits) {
            In += FloatRoundingStr[PrecisionDigits];

        }

        //u64 DecimalPart = In;
        //printf("Deicmal part %lli", In);
        //        TODO(V): Implement my own float to string implementation

    }

    

    

    void string::appendXrVersion(u64 In, string& Target) {
        string Result {};
        Result.format(U"{u16}.{u16}.{u32}", XR_VERSION_MAJOR(In), XR_VERSION_MINOR(In), XR_VERSION_MINOR(In));
        Target.append(Result);

    }

    

    

    void string::appendVkVersion(u32 Ver) {
        string Result{};
        Result.format(U"{u32}.{u32}.{u32}", VK_VERSION_MAJOR(Ver), VK_VERSION_MINOR(Ver), VK_VERSION_PATCH(Ver));
        append(Result);

    }

	/*
    void string::dumpToConsole() {
        //printf("Dumping string, Size: %i Alloc: %i String:", StringSize, AllocSize);
        char32_t* itPtr = DataPtr;
        for (u32 i = 0; AllocSize > i; i++) {
            //printf("%i,", *itPtr);
            itPtr++;

        }
		//        STUB(V): Implement with new internal print function
        //printf("\n");

    }
	*/

	/*
    //    INTERN 
    void string::initinternal(u32 InitSize) {
        DataPtr = (char32_t*)dalloc(InitSize * sizeof(char32_t));
        vset(DataPtr, 0, InitSize * sizeof(char32_t));
        StringSize = 0;
        AllocSize = InitSize;

    }

    void string::quit() {
        dfree(DataPtr);
        AllocSize = 0;
        StringSize = 0;

    }

    void string::checkSize(u32 TargetSize) {
        u32 NewSize = dpow2(TargetSize);
        #if 1
        if (TargetSize < AllocSize) {
            return;

        }
        #else
        if (NewSize = AllocSize) {
            return;

        }
        #endif

        if (NewSize < 8) {
            NewSize = 8;

        }

        DataPtr = (char32_t*)drealloc(DataPtr, NewSize * sizeof(char32_t));
        AllocSize = NewSize;

    }

    void string::internset(const char32_t* Str, size_t Size) {
        checkSize(Size);
        StringSize = Size;
        dcpy(DataPtr, Str, Size * sizeof(char32_t));

    }
	*/

	/*
	char* vlegacy_gcvt(double In, int NumDigits, char* Buf) {
		//        STUB(V): Implement legacy gcvt c library function

	}
	*/

    
	/*
    void mstrcpy(const char* Source, char* Dest) {
        const u32 Size = mstrlen(Source);
        dcpy(Dest, Source, Size);
        Dest[Size] = 0;

    }

    char* mstrncat(char* Dest, const char* Source, size_t Size) {
        char* A = Dest;
        Dest += mstrlen(Dest);
        while (Size && *Source) {
            Size--;
            *Dest++ = *Source++;

        }
        *Dest++ = 0;
        return A;

    }
	*/

	/*
    int mstrcmp(const char* s1, const char* s2) {
        while(*s1 && (*s1 == *s2))
        {
            s1++;
            s2++;
        }
        return *(const unsigned char*)s1 - *(const unsigned char*)s2;

    }*/


	/*
    void chartowchar(const char* Source, char32_t* Target, u32 Size) {
        for (u32 i = 0; i < Size; i++) {
            *Target = *Source;
            Target++;
            Source++;

        }

    }*/

	/*
    void wchartochar(const char32_t* Source, char* Target, u32 Size) {
        for (u32 i = 0; i < Size; i++) {
            Target[i] = (char)Source[i];

        }

    }
	*/

	/*
    u32 getDigitFromNumber(u64 In) {
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


    u32 getDigitFromNumber(u32 In) {
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

    u32 getDigitFromNumber(u16 In) {
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

    u32 getDigitFromNumber(u8 In) {
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

    u32 getDigitFromNumber(i64 In) {
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

        return getDigitFromNumber(Significant);

    }

    u32 getDigitFromNumber(i32 In) {
        if (In == 0) {
            return 0;

        }

        u32 Significant = 0;
        if (In < 0) {
            Significant = In * -1;

        }
        else {
            Significant = In;

        }

        return getDigitFromNumber(Significant);

    }

    u32 getDigitFromNumber(i16 In) {
        if (In == 0) {
            return 0;

        }

        u16 Significant = 0;
        if (In < 0) {
            Significant = In * -1;

        }
        else {
            Significant = In;

        }

        return getDigitFromNumber(Significant);

    }

    u32 getDigitFromNumber(i8 In) {
        if (In == 0) {
            return 0;

        }

        u8 Significant = 0;
        if (In < 0) {
            Significant = In * -1;

        }
        else {
            Significant = In;

        }

        return getDigitFromNumber(Significant);

    }*/

}

#endif
