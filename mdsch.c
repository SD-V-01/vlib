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

#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)
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


#elif defined(VLIB_PLATFORM_NT)
#include <windows.h>
#include <process.h>

#else
#error Implement platform

#endif

//SECTION(V): CallOnce impl
#if defined(VLIB_PLATFORM_LINUX) && defined(VLIB_ON_CRT)
VLIB_CABI
void mdCallOnce(mdCallOnceGuard* Guard, mdCallOnceFunc Fn){
	pthread_once(Guard, Fn);

}

VLIB_CABIEND

#elif defined(VLIB_PLATFORM_NT)
typedef struct mdCallOnceWindowsWrapper {
	mdCallOnceFunc Func;

} mdCallOnceWindowsWrapper;

static BOOL mdCallOnceInternal(PINIT_ONCE InitOnce, PVOID Wrapper, PVOID* Context) {
	VUNDEF(InitOnce);
	VUNDEF(Context);
	mdCallOnceFunc Func = ((mdCallOnceWindowsWrapper*)Wrapper)->Func;
	if (Func) {
		Func();

	}

	return TRUE;

}

void mdCallOnce(mdCallOnceGuard* Guard, mdCallOnceFunc Fn) {
	mdCallOnceWindowsWrapper Wrapper = { Fn };
	InitOnceExecuteOnce(Guard, mdCallOnceInternal, &Wrapper, NULL);

}

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

#elif defined(VLIB_PLATFORM_NT)
bool mdCreateHostMutex(mdHostMutex* Mutex) {
	return InitializeCriticalSectionAndSpinCount((CRITICAL_SECTION *)&Mutex->MutexImpl, (DWORD)MD_MUTEX_DEFAULT_SPIN);

}

void mdDestroyHostMutex(mdHostMutex* Mutex) {
	CRITICAL_SECTION* Section = (CRITICAL_SECTION *)&Mutex->MutexImpl;
	DeleteCretecalSection(Section);
	vset(&Mutex->MutexImpl, 0, sizeof(Mutex->MutexImpl));

}

void mdAcquireHostMutex(mdHostMutex* Mutex) {
	EnterCriticalSection((CRITICAL_SECTION *)&Mutex->MutexImpl);

}

bool mdTryAcquireHostMutex(mdHostMutex* Mutex) {
	return TryEnterCriticalSection((CRITICAL_SECTION *)&Mutex->MutexImpl);

}

void mdReleaseHostMutex(mdHostMutex* Mutex) {
	LeaveCriticalSection((CRITICAL_SECTION *)&Mutex->MutexImpl);

}

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

#elif defined(VLIB_PLATFORM_NT)
bool mdCreateHostCondVar(mdHostCondVar* Var) {
	Var->Impl = (CONDITION_VARIABLE *)vcalloc(1, sizeof(CONDITION_VARIABLE));
	InitializeConditionVariable((PCONDITION_VARIABLE)Var->Impl);
	return true;

}

void mdDestroyHostCondVar(mdHostCondVar* Var) {
	vfree(Var->Impl);

}

void mdWaitHostCondVar(mdHostCondVar* Var, mdHostMutex* Mutex) {
	SleepConditionVariableCS((PCONDITION_VARIABLE)Var->Impl, (PCRITICAL_SECTION)&Mutex->MutexImpl);

}

void mdWakeOneHostCondVar(mdHostCondVar* Var) {
	WakeConditionVariable((PCONDITION_VARIABLE)Var->Impl);

}

void mdWakeAllHostCondVar(mdHostCondVar* Var) {
	WakeAllConditionVariable((PCONDITION_VARIABLE)Var->Impl);

}

#else
#error Implement platform

#endif

VLIB_CABIEND

//SECTION(V): Thread impl

static mdThreadId MainThreadId;

VLIB_CABI

void mdSetMainThreadId(){
	MainThreadId = mdGetCurrentThreadId();

}

bool mdIsMainThread(){
	return mdGetCurrentThreadId() == MainThreadId;

}

mdThreadId mdGetMainThreadId(){
	return MainThreadId;

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

#ifdef VLIB_PLATFORM_LINUX
#ifdef VLIB_ON_CRT

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
		VASSERT(0, "mdGetCurrentThreadId case STUB");
		//        STUB(V): Implement !!!!!!!!!!!!!

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

void mdThreadSleep(u64 TimeMs){
	usleep(TimeMs * 1000);

}

u32 mdGetNumOfCpuCores(){
	return get_nprocs_conf();

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
	//    NOTE(V): I am not sure if this is actually necesary but some
	// older code did that so im not going to question my 15yo self
	CallerHandle = (mdThreadHandle)NULL;

}

void mdDetatchThread(mdThreadHandle CallerHandle){
	pthread_detach(CallerHandle);

}

#else
#error Implement platform

#endif

#elif defined(VLIB_PLATFORM_NT)
mdThreadId mdGetCurrentThreadId() {
	return GetCurrentThreadId();

}

static const char* mdSchInternalThreadName() {
	__declspec(thread) static char Name[MD_THREAD_NAME_LENGTH + 1];
	return Name;

}

void mdGetCurrentThreadName(char* Buf, st BufSize) {
	const char* Name = mdSchInternalThreadName();
	if (Name[0]) {
		st NameLength = vstrlen8(Name);
		if (NameLength > (BufSize - 1)) {
			NameLength = BufSize - 1;

		}
		vcpy(Buf, Name, NameLength);
		Buf[NameLength] = 0;

	}
	else {
		if (BufSize != 0) {
			Buf[0] = 0;

		}

	}

}

void mdSetCurrentThreadName(char* Buf) {
	char * const ThreadName = mdSchInternalThreadName();
	st StrSize = vstrlen8(Buf);
	if (StrSize > (MD_THREAD_NAME_LENGTH)) {
		StrSize = MD_THREAD_NAME_LENGTH;

	}

	vcpy(ThreadName, Buf, StrSize);
	ThreadName[StrSize] = 0;
	//        TODO(V): Set the thread name inside windows instad of the thread local name only

}

void mdThreadSleep(u64 TimeMs) {
	Sleep(TimeMs);

}

u32 mdGetNumOfCpuCores() {
	struct _SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	return SystemInfo.dwNumberOfProcessors;

}

static unsigned WINAPI threadKickstart(void* Data) {
	mdThreadInits Item = *((mdThreadInits*)(Data));
	vfree(Data);

	if (Item.Name[0] != 0) {
		mdSetCurrentThreadName(Item.Name);

//        TODO(V): Set the thread name inside windows instad of the thread local name only

	}

	if (Item.AffinityMask) {
		u32 Cores = mdGetNumOfCpuCores();
		for (u32 GroupId = 0; GroupId < Cores / 64; ++GroupId) {
			GROUP_AFFINITY GroupAfinity = { 0 };
			GroupAfinity.Mask = Item.AffinityMask[GroupId];
			GroupAfinity.Group = (WORD)GroupId;

			BOOL Result = SetThreadGroupAffinity(GetCurrentThread(), &GroupAfinity, NULL);
			VASSERT(Result == 0, "Failed to set affinity on threadKickstart");

		}

	}

	Item.Func(Item.UsrData);
	return 0;

}

bool mdCreateThread(mdThreadInits* Inits, mdThreadHandle* ResultHandle) {
	VASSERT(ResultHandle, "Thread handle ptr passed to mdCreateThread is invalid or NULL");
	*ResultHandle = NULL;
	mdThreadInits* InitsCopy = (mdThreadInits*)valloc(sizeof(mdThreadInits));
	*InitsCopy = *Inits;
	*ResultHandle = (mdThreadHandle)_beginthreadex(0, 0, threadKickstart, InitsCopy, 0, 0);
	return *ResultHandle != NULL;

}

void mdJoinThread(mdThreadHandle CallerHandle) {
	if (!CallerHandle) {
		return;

	}

	WaitForSingleObject((HANDLE)CallerHandle, INFINITE);
	CloseHandle((HANDLE)CallerHandle);

}

void mdDetatchThread(mdThreadHandle CallerHandle) {
	if (!CallerHandle) {
		return;

	}
	CloseHandle((HANDLE)CallerHandle);

}

#else
#error Implement platform

#endif

VLIB_CABIEND

//SECTION(V): Scheduler


