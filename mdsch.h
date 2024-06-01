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

VLIB_STRUCT(mdThread)


VLIB_STRUCTEND(mdThread)
