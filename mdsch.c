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
#define _GNU_SOURCE
#include "sched.h"
#include <unistd.h>
#include <sys/sysinfo.h>
#include "vmem.h"
#include "pthread.h"

//NOTE(V): Frw
int pthread_setname_np(pthread_t thread, const char* name);
int pthread_getname_np(pthread_t thread, char* name, size_t len);
int pthread_setaffinity_np(pthread_t thread, size_t cpusetsize, const cpu_set_t *cpuset);
//void CPU_ZERO(cpu_set_t *set);
//void CPU_SET(int cpu, cpu_set_t *set);
//int sched_setaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);

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
mdHostMutex::mdHostMutex(){
	mdCreateHostMutex(this);

}

mdHostMutex::~mdHostMutex() {
	mdDestroyHostMutex(this);

}

#endif

bool mdHostMutex::create(){
	return mdCreateHostMutex(this);

}

void mdHostMutex::destroy() {
	mdDestroyHostMutex(this);

}

void mdHostMutex::acquire() {
	mdAcquireHostMutex(this);

}

bool mdHostMutex::tryAcquire() {
	return mdTryAcquireHostMutex(this);

}

void mdHostMutex::release() {
	mdReleaseHostMutex(this);

}

#endif

VLIB_CABI

#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT

bool mdCreateHostMutex(mdHostMutex* Mutex){
	Mutex->Spin = MD_MUTEX_DEFAULT_SPIN;
	Mutex->MutexImpl = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	pthread_mutexattr_t Attributes;
	int Status = pthread_mutexattr_init(&Attributes);
	Status |= pthread_mutexattr_settype(&Attributes, PTHREAD_MUTEX_RECURSIVE);
	Status |= pthread_mutex_init(&Mutex->MutexImpl, &Attributes);
	Status |= pthread_mutexattr_destroy(&Attributes);
	return Status == 0;

}

void mdDestroyHostMutex(mdHostMutex* Mutex) {
	pthread_mutex_destroy(&Mutex->MutexImpl);

}

void mdAcquireHostMutex(mdHostMutex* Mutex) {
	u32 Count = 0;
	while (Count < Mutex->Spin && pthread_mutex_trylock(&Mutex->MutexImpl) != 0) {
		Count++;

	}

	if (Count == Mutex->Spin) {
		int Result = pthread_mutex_lock(&Mutex->MutexImpl);
		VASSERT(Result == 0, "mdHostMutex failed to lock !");

	}

}

bool mdTryAcquireHostMutex(mdHostMutex* Mutex) {
	return pthread_mutex_trylock(&Mutex->MutexImpl) == 0;

}

void mdReleaseHostMutex(mdHostMutex* Mutex) {
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
mdHostCondVar::mdHostCondVar() {
	mdCreateHostCondVar(this);

}

mdHostCondVar::~mdHostCondVar() {
	mdDestroyHostCondVar(this);

}

#endif

bool mdHostCondVar::create() {
	return mdCreateHostCondVar(this);

}

void mdHostCondVar::destroy() {
	mdDestroyHostCondVar(this);

}

void mdHostCondVar::wait(mdHostMutex* Mutex) {
	mdWaitHostCondVar(this, Mutex);

}

void mdHostCondVar::wakeOne() {
	mdWakeOneHostCondVar(this);

}

void mdHostCondVar::wakeAll() {
	mdWakeAllHostCondVar(this);

}

#endif

VLIB_CABI

#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT
bool mdCreateHostCondVar(mdHostCondVar* Var) {
	Var->Impl = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	int Result = pthread_cond_init(&Var->Impl, NULL);
	MDASSERT(Result == 0, "Failed to create mdHostCondVar");
	return Result == 0;

}

void mdDestroyHostCondVar(mdHostCondVar* Var) {
	pthread_cond_destroy(&Var->Impl);

}

void mdWaitHostCondVar(mdHostCondVar* Var, mdHostMutex* Mutex) {
	pthread_mutex_t* Handle = (pthread_mutex_t *)&Mutex->MutexImpl;
	pthread_cond_wait(&Var->Impl, Handle);

}

void mdWakeOneHostCondVar(mdHostCondVar* Var) {
	pthread_cond_signal(&Var->Impl);

}

void mdWakeAllHostCondVar(mdHostCondVar* Var) {
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
		#ifdef USE_SCHED
		cpu_set_t Cpuset;
		CPU_ZERO(&Cpuset);
		#else
		cpu_set_t Cpuset;
		__CPU_ZERO_S(sizeof(cpu_set_t), &Cpuset);
		#endif
		for (u64 v = 0; v < MaskSize; ++v) {
			u8 Mask = * ((u8 *)Inits.AffinityMask + v);
			for (st vx = 0; vx < 8; ++vx) {
				if (Mask & 1) {
					__CPU_SET_S(v * 8 + vx, sizeof(cpu_set_t), &Cpuset);

				}

				Mask >>= 1;

			}

		}

		#ifdef USE_SCHED
		const i32 Result = sched_setaffinity(0, sizeof(cpu_set_t), &Cpuset);
		#else
		const i32 Result = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &Cpuset);
		#endif
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

//SECTION(V): Scheduler


