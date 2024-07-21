////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mdinit.h
//  Version:     v1.00
//  Created:     17/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "base_types.h"

#define MDINIT_API

#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)
#define VPREINIT(Name) \
static void Name() __attribute__((constructor));\
static void Name()

#else
#error Implement for platform

#endif

//SECTION(V): Init system

#define MDINIT_DEFAULT_DEP_SIZE 32
#define MDINIT_DEFAULT_JOB_NUMBER 32
#define MDINIT_HASH_SEED 0xDEAD55FFAA865702
#define MDINIT_FIND_ERROR 666666

typedef void(*mdinitJobFunc)();

VLIB_STRUCT(mdinitJob)
const char* Name;
u64 Hash;
const char** DepNames;
u64* Dependencies;
st DepSize;
st DepAlloc;
mdinitJobFunc Func;
bool IsInit;

VLIB_STRUCTEND(mdinitJob)

VLIB_STRUCT(mdInitState)
bool IsInit;
mdinitJob* Jobs;
st JobSize;
st JobAlloc;

VLIB_STRUCTEND(mdInitState)

VLIB_CABI
MDINIT_API void mdinitCreateJob(mdinitJob* Job, const char* Name, mdinitJobFunc Func);
MDINIT_API void mdinitJobCheckSize(mdinitJob* Job, st NewSize);
MDINIT_API void mdinitDumpJobToStdout(mdinitJob* Job);
MDINIT_API void mdinitAddDep(mdinitJob* Job, const char* Name);
MDINIT_API void mdinitRunState(mdInitState* State);
MDINIT_API st mdinitSearchJob(u64 InHash, mdInitState* State);
MDINIT_API void mdinitExecJob(mdInitState* State, st Index, st Recursive);
MDINIT_API void mdinitCreateState(mdInitState* State);
MDINIT_API void mdinitDumpStateToStdout(mdInitState* State);
MDINIT_API void mdinitStateCheckSize(mdInitState* State, st NewSize);
MDINIT_API mdinitJob* mdinitGetNewJobPtr(mdInitState* State, const char* Name, mdinitJobFunc Func);
MDINIT_API void mdinitCopyJobToState(mdInitState* State, mdinitJob* Job);
MDINIT_API u64 mdinitHash(const char* Name);

VLIB_CABIEND

//SECTION(V): Runtime init system

VLIB_CABI
MDINIT_API void vrtinitCheckInit();
MDINIT_API mdinitJob* vrtinitAddJob(const char* Name, mdinitJobFunc Func);
MDINIT_API void vrtinitRun();

VLIB_CABIEND
