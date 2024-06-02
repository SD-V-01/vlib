////////////////////////////////////////////////////////////////////////////
//
//  VLIB Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mdsch.h
//  Version:     v1.00
//  Created:     30/05/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "base_types.h"

//SECTION(V): General

#define MDSCHEDULER_API
#define MDSCHEDULER_THREAD_NAME_LENGTH 256

#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT
#include "pthread.h"

#else
#error Implement platform

#endif

#else
#error Implement platform

#endif

//SECTION(V): CallOnce
#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT
#ifndef MD_THREAD_LOCAL
#define MD_THREAD_LOCAL __thread

#endif
#define MD_CALL_ONCE_GUARD_CREATE PTHREAD_ONCE_INIT
typedef pthread_once_t mdCallOnceGuard;

#else
#error Implement platform

#endif

#else
#error Implement platform

#endif

VLIB_CABI
typedef void(*mdCallOnceFunc)();

MDSCHEDULER_API void mdCallOnce(mdCallOnceGuard* Guard, mdCallOnceFunc Fn);

VLIB_CABIEND

//SECTION(V): Atomics
//TODO(V): Implement

//SECTION(V): Mutex

VLIB_STRUCT(mdMutex)
#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT
pthread_mutex_t MutexImpl;
u32 Spin;

#else
#error Implement for platform
#endif

#else
#error Implement for platform
#endif

#ifdef VPP

#ifndef VLIB_NO_RAII
mdMutex();
~mdMutex();

#endif

MDSCHEDULER_API bool create();
MDSCHEDULER_API void destroy();
MDSCHEDULER_API void acquire();
MDSCHEDULER_API bool tryAcquire();
MDSCHEDULER_API void release();

#endif

VLIB_STRUCTEND(mdMutex)

VLIB_CABI
MDSCHEDULER_API bool mdCreateMutex(mdMutex* Mutex);
MDSCHEDULER_API void mdDestroyMutex(mdMutex* Mutex);
MDSCHEDULER_API void mdAcquireMutex(mdMutex* Mutex);
MDSCHEDULER_API bool mdTryAcquireMutex(mdMutex* Mutex);
MDSCHEDULER_API void mdReleaseMutex(mdMutex* Mutex);

VLIB_CABIEND

//SECTION(V): Conditional variable

VLIB_STRUCT(mdCondVar)

#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT
pthread_cond_t Impl;

#else
#error Implement for platform
#endif

#else
#error Implement for platform
#endif

#ifdef VPP
#ifndef VLIB_NO_RAII
mdCondVar();
~mdCondVar();
#endif
MDSCHEDULER_API bool create();
MDSCHEDULER_API void destroy();
MDSCHEDULER_API void wait(mdMutex* Mutex);
MDSCHEDULER_API void wakeOne();
MDSCHEDULER_API void wakeAll();

#endif


VLIB_STRUCTEND(mdCondVar)

VLIB_CABI
MDSCHEDULER_API bool mdCreateCondVar(mdCondVar* Var);
MDSCHEDULER_API void mdDestroyCondVar(mdCondVar* Var);
MDSCHEDULER_API void mdWaitCondVar(mdCondVar* Var, mdMutex* Mutex);
MDSCHEDULER_API void mdWakeOneCondVar(mdCondVar* Var);
MDSCHEDULER_API void mdWakeAllCondVar(mdCondVar* Var);

VLIB_CABIEND

//SECTION(V): Thread

#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT
typedef pthread_t mdThreadHandle;
typedef u32 mdThreadId;

#else
#error Implement for platform
#endif

#else
#error Implement for platform
#endif

#define MD_THREAD_NAME_LENGTH 31
typedef void(*mdThreadFunc)(void*);

VLIB_STRUCT(mdThreadInits)
mdThreadFunc Func;
void* UsrData;
char Name[MD_THREAD_NAME_LENGTH];

bool SetAffinityMask;
u64 AffinityMask[16];

VLIB_STRUCTEND(mdThreadInits)

VLIB_CABI
MDSCHEDULER_API void mdSetMainThreadId();
MDSCHEDULER_API mdThreadId mdGetMainThreadId();
MDSCHEDULER_API mdThreadId mdGetCurrentThreadId();
MDSCHEDULER_API void mdGetCurrentThreadName(char* Buf, st BufSize);
MDSCHEDULER_API void mdSetCurrentThreadName(char* Buf);
MDSCHEDULER_API bool mdIsMainThread();
MDSCHEDULER_API void mdThreadSleep(u64 TimeMs);
MDSCHEDULER_API u32 mdGetNumOfCpuCores();
MDSCHEDULER_API void mdSetCpuAffinity(mdThreadInits* Thread, u64 Id);
MDSCHEDULER_API bool mdCreateThread(mdThreadInits* Inits, mdThreadHandle* ResultHandle);
MDSCHEDULER_API void mdJoinThread(mdThreadHandle CallerHandle);
MDSCHEDULER_API void mdDetatchThread(mdThreadHandle CallerHandle);

VLIB_CABIEND
