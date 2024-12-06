////////////////////////////// DISRUPT ENGINE //////////////////////////////
//
//  DISRUPT ENGINE Source File.
//  Copyright (C) 2024 LAVAGANG
// -------------------------------------------------------------------------
//  File name:   mdsch.h v1.00
//  Created:     30/05/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  Lava gang roll in, break things, melt stuff, clean up, sign off!!
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "base_types.h"
#include "system.h"

//SECTION(V): General

#define MDSCHEDULER_API

#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)
#include "pthread.h"

#elif defined(VLIB_PLATFORM_NT)

#if 0
#include <synchapi.h>

#else

#endif

#else
#error Implement platform

#endif

//SECTION(V): CallOnce
#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)

#ifndef MD_THREAD_LOCAL
#define MD_THREAD_LOCAL __thread

#endif

#define MD_CALL_ONCE_GUARD_CREATE PTHREAD_ONCE_INIT
typedef pthread_once_t mdCallOnceGuard;

#elif defined(VLIB_PLATFORM_NT)

#ifndef MD_THREAD_LOCAL
#define MD_THREAD_LOCAL __declspec(thread)

#endif


#define MD_CALL_ONCE_GUARD_CREATE INIT_ONCE_STATIC_INIT
typedef INIT_ONCE mdCallOnceGuard;

#else
#error Implement platform

#endif

VLIB_CABI
typedef void(*mdCallOnceFunc)();

MDSCHEDULER_API void mdCallOnce(mdCallOnceGuard* Guard, mdCallOnceFunc Fn);

VLIB_CABIEND

//SECTION(V): Mutex

VLIB_STRUCT(mdHostMutex)
#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)
pthread_mutex_t MutexImpl;
u32 Spin;

#elif defined(VLIB_PLATFORM_NT)
CRITICAL_SECTION MutexImpl;

#else
#error Implement for platform
#endif

#ifdef VPP

#ifndef VLIB_NO_RAII
explicit mdHostMutex();
~mdHostMutex();

#endif

MDSCHEDULER_API bool create();
MDSCHEDULER_API void destroy();
MDSCHEDULER_API void acquire();
MDSCHEDULER_API bool tryAcquire();
MDSCHEDULER_API void release();

#endif

VLIB_STRUCTEND(mdHostMutex)

VLIB_CABI
MDSCHEDULER_API bool mdCreateHostMutex(mdHostMutex* Mutex);
MDSCHEDULER_API void mdDestroyHostMutex(mdHostMutex* Mutex);
MDSCHEDULER_API void mdAcquireHostMutex(mdHostMutex* Mutex);
MDSCHEDULER_API bool mdTryAcquireHostMutex(mdHostMutex* Mutex);
MDSCHEDULER_API void mdReleaseHostMutex(mdHostMutex* Mutex);

VLIB_CABIEND

//SECTION(V): Conditional variable

#define MDSCH_TIME_INFINITE 0xFFFFFFFF

VLIB_STRUCT(mdHostCondVar)

#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT
pthread_cond_t Impl;

#else
#error Implement for platform
#endif

#elif defined(VLIB_PLATFORM_NT)
void* Impl;

#else
#error Implement for platform
#endif

#ifdef VPP
#ifndef VLIB_NO_RAII
mdHostCondVar();
~mdHostCondVar();
#endif
MDSCHEDULER_API bool create();
MDSCHEDULER_API void destroy();
MDSCHEDULER_API void wait(mdHostMutex* Mutex);
MDSCHEDULER_API void timedWait(mdHostMutex* Mutex, u32 Ms);
MDSCHEDULER_API void wakeOne();
MDSCHEDULER_API void wakeAll();

#endif


VLIB_STRUCTEND(mdHostCondVar)

VLIB_CABI
MDSCHEDULER_API bool mdCreateHostCondVar(mdHostCondVar* Var);
MDSCHEDULER_API void mdDestroyHostCondVar(mdHostCondVar* Var);
MDSCHEDULER_API void mdWaitHostCondVar(mdHostCondVar* Var, mdHostMutex* Mutex);
MDSCHEDULER_API void mdTimedWaitHostCondVar(mdHostCondVar* Var, mdHostMutex* Mutex, u32 Ms);
MDSCHEDULER_API void mdWakeOneHostCondVar(mdHostCondVar* Var);
MDSCHEDULER_API void mdWakeAllHostCondVar(mdHostCondVar* Var);

VLIB_CABIEND

//SECTION(V): Thread

#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT
typedef pthread_t mdThreadHandle;
typedef u32 mdThreadId;

#else
#error Implement for platform
#endif

#elif defined(VLIB_PLATFORM_NT)
typedef void* mdThreadHandle;
typedef unsigned long mdThreadId;

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

//SECTION(V): Atomics

MDSCHEDULER_API inline void mdHardwareFullMemoryBarrier() {
	__sync_synchronize();

}

MDSCHEDULER_API inline void mdYeildProc() {
	_mm_pause();

}

//SECTION(V): Scheduler

#define MD_FIBER_SCHEDULER_MAX_THREAD_COUNT 64
#define MD_FIBER_SCHEDULER_STACK_SIZE 2097152
#define MD_FIBER_SCHEDULER_FIBER_COUNT 512
#define MD_FIBER_SCHEDULER_FIBER_STACK 65536
#define MD_FIBER_SCHEDULER_EXTENDED_FIBER_COUNT 16
#define MD_FIBER_SCHEDULER_EXTENDED_FIBER_STACK 2097152

enum mdschTaskProirity {
	mdschTaskProirity_realtime = 0,
	mdschTaskProirity_high,
	mdschTaskProirity_normal,
	mdschTaskProirity_low,

	mdschTaskProirity_COUNT,

};

VLIB_STRUCT(mdschTaskQueue)


VLIB_STRUCTEND(mdschTaskQueue)
