////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   dstr.h v1.00
//  Created:     30/04/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

#ifndef _DSTR_H_
#define _DSTR_H_

#if defined(VLIB_INCLUDE_DEPRECATED) && defined(__cplusplus)

#include "cpp_compiler.h"
#include "base_types.h"

#define DSTR_DEFAULT_SIZE 16

namespace VLIB_NAMESPACE {
    struct dstr {
        //        Ctor's
        dstr();
        dstr(wchar_t* Rhs);
        dstr(const char* Rhs);
        void init(const char* Rhs);
        dstr(dstr const& Rhs);
        dstr& operator=(dstr const& Rhs);
        ~dstr();

        char* data();

        void set(const char* Rhs);
        void checkSize(u32 InSize);
        void append(const char* In);
        void append(dstr const& In);
        bool isExactMatch(const char* In);
        void isExactMatch(const char* In, bool& Result);
        void getCharsAfterChar(char In, dstr& Result);
        u32 getFirstPosition(char In);

        u32 size();

    private:
        char* DataPtr;
        u32 DataSize;
        u32 DataAlloc;

    };

    bool isExactMatch(const char* Lhs, const char* Rhs, u32 Size);

}

#endif

#endif
