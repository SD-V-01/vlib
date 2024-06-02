////////////////////////////////////////////////////////////////////////////
//
//  VLIB Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mdsch.cpp
//  Version:     v1.00
//  Created:     30/05/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "mdsch.h"
#include "mderror.h"
#include "system.h"

#define MD_MUTEX_DEFAULT_SPIN 1500

#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <sched.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include "mem.h"

#else
#error Implement platform

#endif

#else
#error Implement platform

#endif

//SECTION(V): CallOnce impl
#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT
VLIB_CABI
void mdCallOnce(mdCallOnceGuard* Guard, mdCallOnceFunc Fn){
	pthread_once(Guard, Fn);

}

VLIB_CABIEND

#else
#error Implement platform

#endif

#else
#error Implement platform

#endif

//SECTION(V): Mutex impl

//NOTE(V): C++ Wrapper
#ifdef VPP
#ifndef VLIB_NO_RAII
mdMutex::mdMutex(){
	mdCreateMutex(this);

}

mdMutex::~mdMutex() {
	mdDestroyMutex(this);

}

#endif

bool mdMutex::create(){
	return mdCreateMutex(this);

}

void mdMutex::destroy() {
	mdDestroyMutex(this);

}

void mdMutex::acquire() {
	mdAcquireMutex(this);

}

bool mdMutex::tryAcquire() {
	return mdTryAcquireMutex(this);

}

void mdMutex::release() {
	mdReleaseMutex(this);

}

#endif

VLIB_CABI

#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT

bool mdCreateMutex(mdMutex* Mutex){
	Mutex->Spin = MD_MUTEX_DEFAULT_SPIN;
	Mutex->MutexImpl = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	pthread_mutexattr_t Attributes;
	int Status = pthread_mutexattr_init(&Attributes);
	Status |= pthread_mutexattr_settype(&Attributes, PTHREAD_MUTEX_RECURSIVE);
	Status |= pthread_mutex_init(&Mutex->MutexImpl, &Attributes);
	Status |= pthread_mutexattr_destroy(&Attributes);
	return Status == 0;

}

void mdDestroyMutex(mdMutex* Mutex) {
	pthread_mutex_destroy(&Mutex->MutexImpl);

}

void mdAcquireMutex(mdMutex* Mutex) {
	u32 Count = 0;
	while (Count < Mutex->Spin && pthread_mutex_trylock(&Mutex->MutexImpl) != 0) {
		Count++;

	}

	if (Count == Mutex->Spin) {
		int Result = pthread_mutex_lock(&Mutex->MutexImpl);
		VASSERT(Result == 0, "mdMutex failed to lock !");

	}

}

bool mdTryAcquireMutex(mdMutex* Mutex) {
	return pthread_mutex_trylock(&Mutex->MutexImpl) == 0;

}

void mdReleaseMutex(mdMutex* Mutex) {
	pthread_mutex_unlock(&Mutex->MutexImpl);

}

#else
#error Implement platform

#endif

#else
#error Implement platform

#endif

VLIB_CABIEND

//SECTION(V): Conditional variable impl

#ifdef VPP
#ifndef VLIB_NO_RAII
mdCondVar::mdCondVar() {
	mdCreateCondVar(this);

}

mdCondVar::~mdCondVar() {
	mdDestroyCondVar(this);

}

#endif

bool mdCondVar::create() {
	return mdCreateCondVar(this);

}

void mdCondVar::destroy() {
	mdDestroyCondVar(this);

}

void mdCondVar::wait(mdMutex* Mutex) {
	mdWaitCondVar(this, Mutex);

}

void mdCondVar::wakeOne() {
	mdWakeOneCondVar(this);

}

void mdCondVar::wakeAll() {
	mdWakeAllCondVar(this);

}

#endif

VLIB_CABI

#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT
bool mdCreateCondVar(mdCondVar* Var) {
	Var->Impl = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	int Result = pthread_cond_init(&Var->Impl, NULL);
	MDASSERT(Result == 0, "Failed to create mdCondVar");
	return Result == 0;

}

void mdDestroyCondVar(mdCondVar* Var) {
	pthread_cond_destroy(&Var->Impl);

}

void mdWaitCondVar(mdCondVar* Var, mdMutex* Mutex) {
	pthread_mutex_t* Handle = (pthread_mutex_t *)&Mutex->MutexImpl;
	pthread_cond_wait(&Var->Impl, Handle);

}

void mdWakeOneCondVar(mdCondVar* Var) {
	pthread_cond_signal(&Var->Impl);

}

void mdWakeAllCondVar(mdCondVar* Var) {
	pthread_cond_broadcast(&Var->Impl);

}

#else
#error Implement platform

#endif

#else
#error Implement platform

#endif

VLIB_CABIEND

//SECTION(V): Thread impl

static mdThreadId MainThreadId;

VLIB_CABI

#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT
void mdSetMainThreadId(){
	MainThreadId = mdGetCurrentThreadId();

}

mdThreadId mdGetMainThreadId(){
	return MainThreadId;

}

static mdCallOnceGuard KeyInitGuard = MD_CALL_ONCE_GUARD_CREATE;
static pthread_key_t ThreadIdKey;

static void destroyThreadKey() {
	pthread_key_delete(ThreadIdKey);

}

static void initThreadKey() {
	int Result = pthread_key_create(&ThreadIdKey, NULL);
	MDASSERT(Result == 0, "Could not create pthread key !!!");
	VUNDEF(Result);
//    TODO(V): Use new init system maybe ?
	Result = vLEGACYatexit(destroyThreadKey);
	VASSERT(Result == 0, "legacy atexit failed for thread key");

}

mdThreadId mdGetCurrentThreadId() {
	static volatile u32 Counter;
	mdCallOnce(&KeyInitGuard, initThreadKey);
	void* Ptr = pthread_getspecific(ThreadIdKey);
	uintptr_t PtrId = (uintptr_t)Ptr;
	mdThreadId Id = (mdThreadId)PtrId;

	if (Id == 0) {
//        TODO(V): Implement !!!!!!!!!!!!
		//Id = (mdThreadId)

	}
	VASSERT(Id != 0, "mdThreadId is 0 !!!");
	return Id;

}

void mdGetCurrentThreadName(char* Buf, st BufSize){
	pthread_getname_np(pthread_self(), Buf, BufSize);

}

void mdSetCurrentThreadName(char* Buf){
	pthread_setname_np(pthread_self(), Buf);

}

bool mdIsMainThread(){
	return mdGetCurrentThreadId() == MainThreadId;

}

void mdThreadSleep(u64 TimeMs){
	usleep(TimeMs * 1000);

}

u32 mdGetNumOfCpuCores(){
	return get_nprocs_conf();

}

void mdSetCpuAffinity(mdThreadInits* Thread, u64 Id) {
	if (Id >= 1024) {
		return;

	}

	u64 VId = Id / 64;
	u64 Bit = Id - VId * 64;
	Thread->AffinityMask[VId] |= ((u64)1) << Bit;
	Thread->SetAffinityMask = true;

}

static void* threadKickstart(void* Data) {
	mdThreadInits Inits = * ((mdThreadInits*)Data);
	vfree(Data);

	if (Inits.Name[0] != 0) {
		mdSetCurrentThreadName(Inits.Name);

	}

	if (Inits.SetAffinityMask) {
		st MaskSize = sizeof(Inits.AffinityMask);
		cpu_set_t Cpuset;
		CPU_ZERO(&Cpuset);
		for (u64 v = 0; v < MaskSize; ++v) {
			u8 Mask = * ((u8 *)Inits.AffinityMask + v);
			for (st vx = 0; vx < 8; ++vx) {
				if (Mask & 1) {
					CPU_SET(v * 8 + vx, &Cpuset);

				}

				Mask >>= 1;

			}

		}

		const i32 Result = sched_setaffinity(0, sizeof(cpu_set_t), &Cpuset);
		VASSERT(Result == 0, "Failed to set cpu afinity in thread kickstart");

	}

	Inits.Func(Inits.UsrData);
	return 0;

}

bool mdCreateThread(mdThreadInits* Inits, mdThreadHandle* ResultHandle){
	mdThreadInits* DataCopy = (mdThreadInits*)valloc(sizeof(mdThreadInits));
	if (DataCopy == NULL) {
		return false;

	}

	*DataCopy = *Inits;
	int Result = pthread_create(ResultHandle, NULL, threadKickstart, DataCopy);
	if (Result) {
		vfree((void*)DataCopy);

	}

	return Result == 0;

}

void mdJoinThread(mdThreadHandle CallerHandle){
	pthread_join(CallerHandle, NULL);
//    NOTE(V): I am not sure if this is actually necesary but some older code did that so im not going to question my 15yo self
	CallerHandle = (mdThreadHandle)NULL;

}

void mdDetatchThread(mdThreadHandle CallerHandle){
	pthread_detach(CallerHandle);

}

#else
#error Implement platform

#endif

#else
#error Implement platform

#endif

VLIB_CABIEND
