////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mdinit.c
//  Version:     v1.00
//  Created:     17/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "mdinit.h"
#include "vmem.h"
#include "vhash.h"
#include "system.h"
#include "mdos.h"

#define MDINIT_NO_STDOUT_DEBUG

static st mdinitStrlen(const char* String) {
	const char* A = String;
	for (; *String; String++) {

	}
	return String - A;

}

VLIB_CABI
void mdinitCreateJob(mdinitJob* Job, const char* Name, mdinitJobFunc Func) {
	vset(Job, 0, sizeof(*Job));
	Job->Name = Name;
	Job->Hash = mdinitHash(Name);
	Job->Func = Func;
	Job->DepNames = valloc(MDINIT_DEFAULT_DEP_SIZE * sizeof(const char*));
	vset(Job->DepNames, 0, MDINIT_DEFAULT_DEP_SIZE * sizeof(const char*));
	Job->Dependencies = valloc(MDINIT_DEFAULT_DEP_SIZE * sizeof(u64));
	vset(Job->Dependencies, 0, MDINIT_DEFAULT_DEP_SIZE * sizeof(u64));
	Job->DepAlloc = MDINIT_DEFAULT_DEP_SIZE;

}

void mdinitJobCheckSize(mdinitJob* Job, st NewSize) {
	if (NewSize < Job->DepAlloc) {
		return;

	}

	NewSize = dpow2(NewSize);
	const char** NewCharPtr = valloc(NewSize * sizeof(const char*));
	if (NewCharPtr == NULL) {
		return;

	}

	vset(NewCharPtr, 0, NewSize);
	vcpy(NewCharPtr, Job->DepNames, Job->DepSize);

	u64* NewHashPtr = valloc(NewSize * sizeof(u64));
	if (NewHashPtr == NULL) {
		return;

	}

	vset(NewHashPtr, 0, NewSize);
	vcpy(NewHashPtr, Job->Dependencies, Job->DepSize);

	Job->DepAlloc = NewSize;

}

void mdinitDumpJobToStdout(mdinitJob* Job) {
	/*
	vsys_writeConsoleNullStr("    Dumping job ");
	if (Job->Name != NULL) {
		vsys_writeConsoleNullStr(Job->Name);

	}
	vsys_writeConsoleNullStr(" with hash \"");
	vsys_writeConsoleInteger((unsigned long int)Job->Hash);
	vsys_writeConsoleNullStr("\" dep Size \"");
	vsys_writeConsoleInteger(Job->DepSize);
	vsys_writeConsoleNullStr("\" alloc \"");
	vsys_writeConsoleInteger(Job->DepAlloc);
	vsys_writeConsoleNullStr("\" IsInit \"");
	vsys_writeConsoleInteger(Job->IsInit);
	vsys_writeConsoleNullStr("\" with deplist ");
	for (st v = 0; v < Job->DepSize; v++) {
		vsys_writeConsoleNullStr("\"");
		vsys_writeConsoleNullStr(Job->DepNames[v]);
		vsys_writeConsoleNullStr("\" ");

	}
	vsys_writeConsoleNullStr("\n");
	*/


	char DepToStr[4096];
	st DepToStrPos = 0;
	for (st v = 0; v < Job->DepSize; v++) {
		if ((vstrlen8(Job->DepNames[v]) + DepToStrPos) > 4096) {
			break;

		}

		DepToStr[DepToStrPos] = ' ';
		DepToStrPos++;
		DepToStr[DepToStrPos] = '\"';
		DepToStrPos++;
		vcpy(DepToStr + DepToStrPos, Job->DepNames[v], vstrlen8(Job->DepNames[v]));
		DepToStrPos += vstrlen8(Job->DepNames[v]);
		DepToStr[DepToStrPos] = '\"';
		DepToStrPos++;

	}
	DepToStr[DepToStrPos] = 0;
	//vsys_writeConsoleNullStr("########");

	VLOG("Init", "    Dumping job {cstr} with hash \"{ptr}\" dep size \"{st}\" alloc \"{st}\" IsInit {bool} dependencies {cstr}",
		 Job->Name, Job->Hash, Job->DepSize, Job->DepAlloc, Job->IsInit, DepToStr);

}

void mdinitAddDep(mdinitJob* Job, const char* Name) {
	mdinitJobCheckSize(Job, Job->DepSize + 1);
	Job->DepNames[Job->DepSize] = Name;
	Job->Dependencies[Job->DepSize] = mdinitHash(Name);
	Job->DepSize++;

}

void mdinitRunState(mdInitState* State) {
	for (st v = 0; v < State->JobSize; v++) {
		st RecursiveLevel = 0;
		mdinitExecJob(State, v, RecursiveLevel);

	}

}

void mdinitExecJob(mdInitState* State, st Index, st Recursive) {
	if (Index == MDINIT_FIND_ERROR) {
		//vsys_writeConsoleNullStr("Was not able to a find dependency while initializing, recursive level \"");
		//vsys_writeConsoleInteger(Recursive);
		//vsys_writeConsoleNullStr("\"\nTry to recompile vlib or mdinit.c with #define MDINIT_NO_STDOUT_DEBUG to "
								 //"see stdout on graph walk and be able to spot where the missing dependency is\n");
		return;

	}

	mdinitJob* Job = &(State->Jobs[Index]);
	//#ifdef MDINIT_NO_STDOUT_DEBUG
	//vsys_writeConsoleNullStr("Executing init job \"");
	//vsys_writeConsoleNullStr(Job->Name);
	//vsys_writeConsoleNullStr("\" recursive level \"");
	//vsys_writeConsoleInteger(Recursive);
	//vsys_writeConsoleNullStr("\", ");


	//#endif

	if (Job->IsInit == true) {
		#ifdef MDINIT_NO_STDOUT_DEBUG
		//vsys_writeConsoleNullStr("Skipping\n");
		VLOG("Init", "  Skipping job {cstr} {st}", Job->Name, Recursive);

		#endif

		return;

	}
	#ifdef MDINIT_NO_STDOUT_DEBUG
	else {
		//vsys_writeConsoleNullStr("\n");
		VLOG("Init", "  Executing job {cstr}, recursive level {st}", Job->Name, Recursive);
		
	}

	#endif

	for (st v = 0; v < Job->DepSize; v++) {
		if (Job->Dependencies[v] != 0) {
			st DepIndex = mdinitSearchJob(Job->Dependencies[v], State);
			if (DepIndex == MDINIT_FIND_ERROR) {
				//vsys_writeConsoleNullStr("Could not find required dependency for initialization of \"");
				//vsys_writeConsoleNullStr(Job->Name);
				//vsys_writeConsoleNullStr("\" with nonexistant job being \"");
				//vsys_writeConsoleNullStr(Job->DepNames[v]);
				//vsys_writeConsoleNullStr("\" Skipping.....\n");
				VERR("Init", "Could not find required dependency for initialization of {cstr} "
					 "with missing subsystem {cstr}, Skipping...", Job->Name, Job->DepNames[v]);
				continue;

			}

			mdinitExecJob(State, DepIndex, Recursive + 1);

		}

	}

	if (Job->Func) {
		Job->Func();

	}

	Job->IsInit = true;

}

st mdinitSearchJob(u64 InHash, mdInitState* State) {
	if (InHash == 0) {
		return MDINIT_FIND_ERROR;

	}
	if (!State) {
		return MDINIT_FIND_ERROR;

	}

	for (st v = 0; v < State->JobSize; v++) {
		if (State->Jobs[v].Hash == InHash) {
			return v;

		}

	}

	return MDINIT_FIND_ERROR;

}

void mdinitCreateState(mdInitState* State) {
	vset(State, 0, sizeof(*State));
	State->Jobs = valloc(MDINIT_DEFAULT_JOB_NUMBER * sizeof(mdinitJob));
	vset(State->Jobs, 0, MDINIT_DEFAULT_JOB_NUMBER * sizeof(mdinitJob));
	State->JobAlloc = MDINIT_DEFAULT_JOB_NUMBER;

}

void mdinitDumpStateToStdout(mdInitState* State) {
	//vsys_writeConsoleNullStr("Dumping mdInitState with \"");
	//vsys_writeConsoleInteger(State->JobSize);
	//vsys_writeConsoleNullStr("\" Jobs and \"");
	//vsys_writeConsoleInteger(State->JobAlloc);
	//vsys_writeConsoleNullStr("\" Allocated with ptr \"");
	//vsys_writeConsoleInteger((unsigned long int)State->Jobs);
	//vsys_writeConsoleNullStr("\"\n");

	VLOG("Init", "Dumpint mdInitState with {st} jobs and {st} allocated with ptr {ptr}",
		 State->JobSize, State->JobAlloc, State->Jobs);

	for (st v = 0; v < State->JobAlloc; v++) {
		/*
		vsys_writeConsoleNullStr("    Job ");
		if (State->Jobs[v].Name != NULL) {
			vsys_writeConsoleNullStr(State->Jobs[v].Name);

		}
		vsys_writeConsoleNullStr(" hash \"");
		vsys_writeConsoleInteger(State->Jobs[v].Hash);
		vsys_writeConsoleNullStr("\" isInit \"");
		vsys_writeConsoleInteger(State->Jobs[v].IsInit);
		vsys_writeConsoleNullStr("\"\n");
		*/

		mdinitDumpJobToStdout(State->Jobs + v);

	}
	//vsys_writeConsoleNullStr("End of mdinitState\n");
	VLOGNF("Init", "End of mdinitState");

}

void mdinitStateCheckSize(mdInitState* State, st NewSize) {
	if (NewSize < State->JobAlloc) {
		return;

	}

	NewSize = dpow2(NewSize);
	mdinitJob* NewPtr = valloc(NewSize * sizeof(mdinitJob));
	if (NewPtr == NULL) {
		return;

	}

	vset(NewPtr, 0, NewSize * sizeof(mdinitJob));
	vcpy(NewPtr, State->Jobs, State->JobSize);
	State->JobAlloc = NewSize;
	State->Jobs = NewPtr;

}

//TODO(V): Check for duplicates
mdinitJob* mdinitGetNewJobPtr(mdInitState* State, const char* Name, mdinitJobFunc Func) {
	mdinitStateCheckSize(State, State->JobSize + 1);
	mdinitJob* Result = State->Jobs + State->JobSize;
	State->JobSize++;
	mdinitCreateJob(Result, Name, Func);
	return Result;

}

//TODO(V): Check for duplicates
void mdinitCopyJobToState(mdInitState* State, mdinitJob* Job) {
	mdinitStateCheckSize(State, State->JobSize + 1);
	vcpy(State->Jobs + State->JobSize, Job, sizeof(mdinitJob));
	State->JobSize++;

}

u64 mdinitHash(const char* Name) {
	return XXH64(Name, mdinitStrlen(Name), MDINIT_HASH_SEED);

}

VLIB_CABIEND

//SECTION(V): Runtime init system implementation

static bool IsMdinitInit = false;
static mdInitState IState;

VLIB_CABI
void vrtinitCheckInit(){
	//    NOTE(V): We could use the exec_once feature in mdsch but i am not willing to introduce more interdependencies
	if (IsMdinitInit == false) {
		mdinitCreateState(&IState);
		IsMdinitInit = true;

	}

}

mdinitJob* vrtinitAddJob(const char* Name, mdinitJobFunc Func) {
	vrtinitCheckInit();
	return mdinitGetNewJobPtr(&IState, Name, Func);

}

void vrtinitRun() {
	//vsys_writeConsoleNullStr("Initializing usr program thru init system\n");
	VLOGNF("vrtinit", "Initializing usr program thru init system");
	mdinitDumpStateToStdout(&IState);
	mdinitRunState(&IState);

}

VLIB_CABIEND
