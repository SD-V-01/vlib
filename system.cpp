////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   system.cpp
//  Version:     v1.00
//  Created:     03/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "system.h"
#include "cpp_compiler.h"

#ifdef __cplusplus
extern "C"{
	#endif
	static vsys_size vsys_strlen(const char* String) {
		const char* A = String;
		for (; *String; String++) {

		}
		return String - A;

	}

	void vsys_writeConsoleNullStr(const char* InText) {
		vsys_writeConsole(InText, vsys_strlen(InText));

	}

	void vsys_intToStr(unsigned long int In, char* Target) {
		if (In == 0) {
			Target[0] = '0';
			Target[1] = 0;
			return;

		}

		unsigned int TotalDigits = vsys_getNumberOfDigits(In);
		Target[TotalDigits] = 0;

		while (In >= 10) {
			Target[TotalDigits - 1] = In % 10 + 48;
			In = In / 10;
			TotalDigits--;

		}


		Target[0] = In + 48;

	}

	unsigned int vsys_getNumberOfDigits(unsigned long int In) {
		if (In == 0) {
			return 0;

		}

		unsigned int Result = 0;
		for (; In != 0;) {
			In = In / 10;
			Result++;

		}

		return Result;

	}

	void vsys_writeConsoleInteger(unsigned long int In) {
		char Array[64];
		vsys_intToStr(In, Array);
		vsys_writeConsoleNullStr(Array);

	}

	void vsys_appRtInit() {
		vsys_earlyInit();
		vsys_initConsole();

		vsys_init();

		vsys_coreMemoryProfile MemProfile;

		vsys_initMemory(&MemProfile);

	}

	
	#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
//    frw
	void vlib_mimalloc_preinit();
	#endif

	void vsys_initCoreMemory() {
		#if VLIB_ALLOCATOR_IMPL == VLIB_ALLOCATOR_IMPL_MIMALLOC
		vlib_mimalloc_preinit();

		#else
		#error define allocator implementation

		#endif

	}

	#ifdef __cplusplus
}
#endif
