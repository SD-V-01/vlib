////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   main.cpp
//  Version:     v1.00
//  Created:     03/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "../v.h"
#include "../system.h"

//#define REMOVE_USRCODE

void vrt_preInitUsr(){
	#ifndef REMOVE_USRCODE

	#endif

}

#ifndef REMOVE_USRCODE
static void testMem(u32 Length) {
	char* TestPtr = (char*)vsys_allocSmallPageGeneric(Length);

	vsys_writeConsoleNullStr("Testing \"");
	vsys_writeConsoleInteger(Length);
	vsys_writeConsoleNullStr("\" Bytes of memory alloc with ptr \"");
	vsys_writeConsoleInteger((u64)TestPtr);
	vsys_writeConsoleNullStr("\"\n");

	const char TestChar = 'V';

	for (u32 i = 0; i < Length; i++) {
		TestPtr[i] = TestChar;

	}

	for (u32 i = 0; i < Length; i++) {
		//vsys_writeConsole(&(TestPtr[i]), 1);
		if (TestPtr[i] != TestChar) {
			vsys_writeConsoleNullStr("Failed on offset \"");
			vsys_writeConsoleInteger(i);
			vsys_writeConsoleNullStr("\"\n");

		}

	}

	vsys_freeSmallPageGeneric((void*)TestPtr);

}

static void testVMem(u32 Length) {
	char* TestPtr = (char*)valloc(Length);

	vsys_writeConsoleNullStr("Testing \"");
	vsys_writeConsoleInteger(Length);
	vsys_writeConsoleNullStr("\" Bytes of memory VAlloc with ptr \"");
	vsys_writeConsoleInteger((u64)TestPtr);
	vsys_writeConsoleNullStr("\"\n");

	const char TestChar = 'V';

	for (u32 i = 0; i < Length; i++) {
		TestPtr[i] = TestChar;

	}

	for (u32 i = 0; i < Length; i++) {
		//vsys_writeConsole(&(TestPtr[i]), 1);
		if (TestPtr[i] != TestChar) {
			vsys_writeConsoleNullStr("Failed on offset \"");
			vsys_writeConsoleInteger(i);
			vsys_writeConsoleNullStr("\"\n");

		}

	}

	vfree(TestPtr);

}

static void testIntegers() {
	vsys_writeConsoleNullStr("Testing integers\n");
	vsys_writeConsoleInteger(sizeof(u64));
	vsys_writeConsoleNullStr(" Bytes for u64\n");
	vsys_writeConsoleInteger(sizeof(u32));
	vsys_writeConsoleNullStr(" Bytes for u32\n");
	vsys_writeConsoleInteger(sizeof(u16));
	vsys_writeConsoleNullStr(" Bytes for u16\n");
	vsys_writeConsoleInteger(sizeof(u8));
	vsys_writeConsoleNullStr(" Bytes for u8\n");

	vsys_writeConsoleInteger(sizeof(i64));
	vsys_writeConsoleNullStr(" Bytes for i64\n");
	vsys_writeConsoleInteger(sizeof(i32));
	vsys_writeConsoleNullStr(" Bytes for i32\n");
	vsys_writeConsoleInteger(sizeof(i16));
	vsys_writeConsoleNullStr(" Bytes for i16\n");
	vsys_writeConsoleInteger(sizeof(i8));
	vsys_writeConsoleNullStr(" Bytes for i8\n");

}

#endif

void vrt_usrCode(){
	#ifndef REMOVE_USRCODE
	vsys_writeConsoleNullStr("Testing runtime\n");
	char TestArray[20];
	vsys_intToStr(321564687, TestArray);
	vsys_writeConsoleNullStr(TestArray);
	vsys_writeConsoleNullStr("#\n");

	vsys_writeConsoleNullStr("Testing memory alloc syscall\n");

	testMem(4096);
	testMem(32768);
	testMem(4096000);
	testMem(16384000);
	testMem(262144000);
	//testMem(2621440000);
	//testMem(3686400000);

	testVMem(4096);
	testVMem(32768);
	testVMem(4096000);
	testVMem(16384000);
	testVMem(262144000);

	testIntegers();

	vsys_breakpoint();

	#endif

}
