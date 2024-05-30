
#include "cpp_compiler.h"
#include "mem.h"
#include "dstr.h"

#ifdef VLIB_INCLUDE_DEPRECATED
namespace VLIB_NAMESPACE {

    //    FRW
    size_t mstrlen(const char* String);

    dstr::dstr() {
        DataPtr = (char*)dalloc(dpow2(DSTR_DEFAULT_SIZE));
        DataSize = 0;
        DataAlloc = dpow2(DSTR_DEFAULT_SIZE);
        *DataPtr = 0;

    }

    dstr::dstr(const char* Rhs) {
        init(Rhs);

    }

    void dstr::init(const char* Rhs) {
        const u32 StrSize = mstrlen(Rhs);
        u32 DemandedSize = dpow2(StrSize);
        if (DemandedSize < DSTR_DEFAULT_SIZE) {
            DemandedSize = DSTR_DEFAULT_SIZE;

        }

        DataPtr = (char*)dalloc(DemandedSize);
        dcpy((void*)DataPtr, (const void*) Rhs, StrSize);
        DataSize = StrSize;
        DataAlloc = DemandedSize;

    }

    dstr::dstr(dstr const& Rhs) {
        DataSize = Rhs.DataSize;
        DataAlloc = Rhs.DataAlloc;
        DataPtr = (char*)dalloc(DataAlloc);
        dcpy(DataPtr, Rhs.DataPtr, DataSize);

    }

    dstr& dstr::operator=(dstr const& Rhs) {
        //printf("Called assignment operator for %s", Rhs.DataPtr);
        DataSize = Rhs.DataSize;
        DataAlloc = Rhs.DataAlloc;
        DataPtr = (char*)dalloc(DataAlloc);
        dcpy(DataPtr, Rhs.DataPtr, DataSize);
        return *this;

    }

    dstr::~dstr() {
        dfree(DataPtr);

    }

    void dstr::set(const char* Rhs) {
        const u32 StrSize = mstrlen(Rhs);
        checkSize(StrSize);
        dcpy((char*)DataPtr, (const char*)Rhs, StrSize);
        DataSize = StrSize;

    }

    void dstr::checkSize(u32 InSize) {
        const u32 NewSize = dpow2(InSize);
        if (NewSize != DataAlloc && NewSize >= DSTR_DEFAULT_SIZE) {
            DataPtr = (char*) drealloc(DataPtr, NewSize);
            DataAlloc = NewSize;

        }

    }

    void dstr::append(const char* In) {
        const u32 Size = mstrlen(In);
        checkSize(DataSize + Size);
        dcpy(DataPtr + DataSize, In, Size);
        DataSize += Size;

    }

    void dstr::append(dstr const& In) {
        checkSize(DataSize + In.DataSize);
        dcpy((DataPtr + DataSize), In.DataPtr, In.DataSize);
        DataSize += In.DataSize;

    }

    bool dstr::isExactMatch(const char* In) {
        if (mstrlen(In) != DataSize) {
            return false;

        }

        return VLIB_NAMESPACE::isExactMatch(DataPtr, In, DataSize);

    }

    void dstr::isExactMatch(const char* In, bool& Result) {
        Result = isExactMatch(In);

    }

    u32 dstr::getFirstPosition(char In) {
        for (u32 i = 0; i < DataSize; i++) {
            if (DataPtr[i] == 0) {
                return 0;

            }

            if (DataPtr[i] == In) {
                return i;
                break;

            }

        }

        return 0;

    }

//    TODO(V): Write this function
    //void dstr::getCharsAfterChar(char In, dstr& Result) {
        //u32 Offset = getFirstPosition(In);

        //printf("Got Offset %u\n", In);

    //}

    u32 dstr::size() {
        return DataSize;

    }

    char* dstr::data() {
        DataPtr[DataSize] = 0;
        return DataPtr;

    }

    bool isExactMatch(const char* Lhs, const char* Rhs, u32 Size) {
        for (u32 i = 0; i < Size; i++) {
            if (Lhs[i] == 0 || Rhs[i] == 0) {
                return false;

            }

            if (Lhs[i] != Rhs[i]) {
                return false;

            }

        }
        return true;

    }

}

#endif
