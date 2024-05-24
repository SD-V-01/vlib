////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   str.h
//  Version:     v1.00
//  Created:     30/04/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"
#include "vstr32.h"

#ifndef _STR_H_
#define _STR_H_

#pragma once

#define STRING_API

namespace VLIB_NAMESPACE{
    struct string {
        //            String ctor for initialization
        STRING_API string();
        //        Initialize string with {U"mystr"}
        STRING_API string(const char32_t* Str);
        //        Initialize string with {"mystr"}
        STRING_API string(const char* Str);
        //        Initialize string with a specific size
        STRING_API string(const u32 InitSize);
        //        Copy ctor
        STRING_API string(string const& Rhs);
        //        String destructor for deallocation
        STRING_API ~string();
        //        Initialize string
        STRING_API void init();
        //        Initialize string with a specific size
        STRING_API void init(u32 Size);
        //        Copy string manually
        STRING_API void init(string const& Rhs);
        //

        //            Util
        //        Get string length
        STRING_API u32 length32();
        //        Get string length as size_t
        STRING_API size_t length();
        //        Get number of char32_t allocated in the buffer
        STRING_API u32 allocLength();
        //        Get wchar pointermvr
        STRING_API char32_t* getWchar();
        //        Get wchar pointer
        STRING_API char32_t* data();
        //        Get wchar pointer
        STRING_API const char32_t* cdata() const;
        //        Get char malloc heap pointer the exact size with utf8 encoding
        STRING_API char* cstr();
        //        Sets the input string as the instance
        STRING_API void set(const char32_t* Str);
        //        Sets the input string as the instance
        STRING_API void set(const char* Str);
        //        Adds a null character at the end of the string for char32_t* usage
        //          (generally avoid, use MythOS::string internal functions please)
        STRING_API void addNullEnd();
        //        Resizes the string to fit the new string size
        STRING_API void checkSize(u32 TargetSize);

        //            String processing
        //        Clears the string
        STRING_API void clear();
        //        Makes the string size zero without actually setting the memory to 0 like .clear
        STRING_API void clearSize();
        //        Appends a char* str to instance
        STRING_API void append(const char* Str);
        //        Appends a char* str to instalce
        STRING_API void append(char* Str);
        //        Appends a wchar* string to instance
        STRING_API void append(const char32_t* Str);
        //        Appends a string to instance
        STRING_API void append(string const& Str);
        //        Appends a 8 bit character to end of string
        STRING_API void appendChar(const char Char);
        //        Appends a 16 bit character to the end of string
        STRING_API void appendChar(const char32_t Char);
        //        Appends a 16 bit character to the end of string
        STRING_API void appendCharw(const char32_t Char);
        //        Appends a 16 bit character to the start of a string
        STRING_API void appendCharEnd(const char32_t Char);
        //        Appends a fixed array of chars
        STRING_API void appendCharArray(const char* Char, u32 Size);
        //        Returns true if the inputed char32_t* string is an exact match
        STRING_API bool isExactMatch(const char32_t In[]);
        //        Inserts a char32_t in the string
        STRING_API void insert(char32_t Char, u32 Pos);
        //        Instart a char32_t string in string instance
        STRING_API void insert(char32_t* Src, u32 Pos);

        //            String formatting
        //        Turn string into int
        STRING_API u64 strtoi();
        //        Turn string into float/f32
        STRING_API f32 strtof();
        //        Turn string into double/f64
        STRING_API f64 strtod();
        //        Format string into u8
        STRING_API u8 strtou8();
        //        Format string into u16
        STRING_API u16 strtou16();
        //        Format string into u32
        STRING_API u32 strtou32();
        //        Format string into u64
        STRING_API u64 strtou64();
        //        Format string into i8
        STRING_API i8 strtoi8();
        //        Format string into i16
        STRING_API i16 strtoi16();
        //        Format string into i32
        STRING_API i32 strtoi32();
        //        Format string into i64
        STRING_API i64 strtoi64();

        //        Format u64 into string
        STRING_API static void u64tostr(u64 In, string& Target, const u32 Pos);
        STRING_API static void u64tohex(u64 In, string& Target, const u32 Pos);
        STRING_API static void memtohex(const u16* InPtr, u32 InSize, string& Target, const u32 Pos);
        STRING_API static void u64tobit(u64 In, string& Target, const u32 Pos);
        //        DO NOT USE, UNFINISHED
        static void floattostr(f32 In, string& Target, u32 PrecisionDigits, const u32 Pos);
        
        STRING_API static void appendVkResult(i32 In, string& Target);
        STRING_API void appendVkFormat(i32 In);
        STRING_API void appendVkVersion(u32 Ver);
        STRING_API void appendXrType(i32 In);
        STRING_API static void appendXrVersion(u64 In, string& Target);
        STRING_API static void appendXrViewConfigType();
        STRING_API static void appendXrEnvBlendMode(u32 In, string& Target);
        STRING_API static void appendXrResult(i32 In, string& Target);

        //        Formats string
        STRING_API void format(const char32_t* Fmt, ...);
        //        Format error reporting
        STRING_API void formatError(const char32_t* Message);

        //        f32 to string
        STRING_API static string ftostr(f32 In);
        //        f64 to string
        STRING_API static string dtostr(f64 In);

        //            search operations
        //        Returns true if arg is found in instance
        STRING_API u32 isInString(string const& Str);
        //        Returns true if arg is found in instance
        STRING_API u32 isInString(char32_t* Str);

        //        Debug
        STRING_API void dumpToConsole();

    private:
        void initinternal(u32 InitSize);
        void quit();
        void internset(const char32_t* Str, size_t Size);

        u32 AllocSize;
        u32 StringSize;
        char32_t* DataPtr;

    };

	STRING_API char* vlegacy_gcvt(double In, int NumDigits, char* Buf);
    
    STRING_API void mstrcpy(const char* Source, char* Dest);
    STRING_API char* mstrncat(char* Dest, const char* Source, size_t Size);
    STRING_API int mstrcmp(const char* s1, const char* s2);
    STRING_API void chartowchar(const char* Source, char32_t* Target, u32 Size);
    STRING_API void wchartochar(const char32_t* Source, char* Target, u32 Size);
    STRING_API u32 getDigitFromNumber(u64 In);
    STRING_API u32 getDigitFromNumber(u32 In);
    STRING_API u32 getDigitFromNumber(u16 In);
    STRING_API u32 getDigitFromNumber(u8 In);
    STRING_API u32 getDigitFromNumber(i64 In);
    STRING_API u32 getDigitFromNumber(i32 In);
    STRING_API u32 getDigitFromNumber(i16 In);
    STRING_API u32 getDigitFromNumber(i8 In);

}

#endif
