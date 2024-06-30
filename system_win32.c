////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   system_win32.cpp
//  Version:     v1.00
//  Created:     03/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32

#include "system.h"
#include "windows.h"
#include "winbase.h"

#ifdef __cplusplus
extern "C"{
	#endif

	//    mdos frw

	void mdosPrintTermHeader();

	#ifdef __cplusplus
}
#endif



#ifdef __cplusplus
extern "C" {
	#endif
	int _fltused=0; // it should be a single underscore since the double one is the mangled name
	//    NOTE(V): I hate programing in the lowest level that os's will allow me to do because of shit like this, *WTF* ??

	//    NOTE(V): More compiler magic
	ULONG _tls_index = 0;
	__declspec(thread) bool __tls_guard = false;

	#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"{
	#endif

	static HANDLE StdConsoleHandle;

	void vsys_initConsole() {
		StdConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (StdConsoleHandle != INVALID_HANDLE_VALUE) {
			mdosPrintTermHeader();
			vsys_writeConsoleNullStr("Initalized STD out console sucesfully, standard out logging now avalable\n");

		}

	}

	void vsys_writeConsole(const char* InText, int Length) {
		if (StdConsoleHandle != INVALID_HANDLE_VALUE) {
			WriteConsoleA(StdConsoleHandle, InText, (DWORD)Length, NULL, NULL);

		}

	}

	void vsys_earlyInit() {

	}

	void vsys_init() {
		vsys_writeConsoleNullStr("Starting V Runtime enviroment for Windows NT 7 !!!\n");

	}

	static vsys_coreMemoryProfile SystemMemProfile ;

	void vsys_initMemory(vsys_coreMemoryProfile* MemProfile) {
		MemProfile->hasOvercomit = vsys_true;
		SystemMemProfile.hasOvercomit = vsys_true;

		MemProfile->mustFreeWhole = vsys_false;
		SystemMemProfile.mustFreeWhole = vsys_false;
	
		MemProfile->hasVirtualReserve = vsys_true;
		SystemMemProfile.hasVirtualReserve = vsys_true;

		SYSTEM_INFO NtSysInfo;
		GetSystemInfo(&NtSysInfo);
		
		if (NtSysInfo.dwPageSize > 0) {
			MemProfile->smallPageSize = NtSysInfo.dwPageSize;
			SystemMemProfile.smallPageSize = NtSysInfo.dwPageSize;

			#ifdef VSYS_DEBUG
			vsys_writeConsoleInteger(MemProfile->smallPageSize);
			vsys_writeConsoleNullStr(" Bytes page size set\n");

			#endif

		}

		if (NtSysInfo.dwAllocationGranularity > 0) {
			MemProfile->allocGranularity = NtSysInfo.dwAllocationGranularity;
			SystemMemProfile.allocGranularity = NtSysInfo.dwAllocationGranularity;
			#ifdef VSYS_DEBUG
			vsys_writeConsoleInteger(MemProfile->allocGranularity);
			vsys_writeConsoleNullStr(" Allocation granularity set\n");

			#endif

		}

		//    TODO(V): Add option in core strings to dissable large page support
		//vsys_enableLargePage(&MemProfile->largePageSize);
		//SystemMemProfile.largePageSize = MemProfile->largePageSize;

	}

	vsys_bool vsys_enableLargePage(vsys_size* PageSize) {
		unsigned long ErrCode = 0;
		HANDLE Token = NULL;
		BOOL Ok = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &Token);
		if (Ok) {
			TOKEN_PRIVILEGES Tp;
			Ok = LookupPrivilegeValue(NULL, TEXT("SeLockMemoryPrivilege"), &Tp.Privileges[0].Luid);
			if (Ok) {
				Tp.PrivilegeCount = 1;
				Tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
				Ok = AdjustTokenPrivileges(Token, FALSE, &Tp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
				if (Ok) {
					ErrCode = GetLastError();
					Ok = (ErrCode == ERROR_SUCCESS);
					if (Ok && PageSize != NULL) {
						*PageSize = GetLargePageMinimum();

					}

				}

			}

			CloseHandle(Token);

		}

		if (!Ok) {
			if (ErrCode == 0) {
				ErrCode = GetLastError();

			}

			//        TODO(V): Large page support is borken right now and i will have to fix it later
			vsys_writeConsoleNullStr("Could not enable large page support with error code \"");
			vsys_writeConsoleInteger(ErrCode);
			vsys_writeConsoleNullStr("\"\n");

		}
		#ifdef VSYS_DEBUG
		else {
			vsys_writeConsoleNullStr("Sucessfully enabled large page support\n");

		}
		#endif

		return (Ok != 0);

	}

	void* vsys_allocSmallPageGeneric(vsys_size Size) {
		if (Size % SystemMemProfile.smallPageSize != 0) {
			vsys_writeConsoleNullStr("[ERROR] Call to vsys_allocSmallPageGeneric(vsys_size Size) has input that are not divisable by page size\n");

		}

		void* Result = VirtualAlloc2(
			NULL, // Current process
			NULL, // System picks an adress for us
			Size,
			MEM_COMMIT | MEM_RESERVE, // We actually allocate physical ram with this
			PAGE_READWRITE,
			NULL,
			0);

		if (Result == NULL) {
			vsys_writeConsoleNullStr("[ERROR] VirtualAlloc2 Failed in SmallPageGeneric api !!! Error code \"");
			vsys_writeConsoleInteger(GetLastError());
			vsys_writeConsoleNullStr("\" with ptr \"");
			vsys_writeConsoleInteger((unsigned long int)Result);
			vsys_writeConsoleNullStr("\"\n");


		}

		return Result;

	}

	void vsys_freeSmallPageGeneric(void* Ptr) {
		vsys_bool Result = VirtualFree(Ptr, 0, MEM_RELEASE);
		if (Result == 0) {
			vsys_writeConsoleNullStr("[ERROR] Failed VirtualFree in SmallPageGeneric api with error code \"");
			vsys_writeConsoleInteger((unsigned long int)GetLastError());
			vsys_writeConsoleNullStr("\"\n");

		}

	}

	void vsys_killProcess(int ReturnCode) {
		ExitProcess(ReturnCode);

	}

	void vsys_breakpoint() {
		__debugbreak();

	}

	#define _VLIB_WIN32_MAX_ENVIROMENT_VAR_LENGTH_DO_NOT_USE_LEGACY 16384

	void _DEPRECATED_DO_NOT_USE_vlib_crtinterop_getenv(const char* In, char* Buffer, vsys_size BufferSize){
		GetEnvironmentVariableA(In, Buffer, BufferSize);
	

	}

	void _DEPRECATED_DO_NOT_USE_vlib_crtinterop_getenv_32(const wchar_t* In, wchar_t* Buffer, vsys_size BufferSize){
		GetEnvironmentVariableW(In, Buffer, BufferSize);

	}

	void __cdecl _Thrd_yield(){
		//    NOTE(V): Do nothing on windows ???
		//    NOTE(V): This is soo fucked up
		//    TODO(V): !!!!!! Implement, i touhgt that this was unimplemented but i think it is

		//    NOTE(V): I am not sure if this implementation is correct, the c standard is bliurry on this anyway so fuck me i guess
		SwitchToThread();

	}

	typedef void (__cdecl* _PVFV)(void);

	#define _CRTALLOC(x) __declspec(allocate(x))

	static _CRTALLOC(".CRT$XDA") _PVFV __xd_a = nullptr;

	static _CRTALLOC(".CRT$XDZ") _PVFV __xd_z = nullptr;

	//NOTE(V): This is code copied from the visual c runtime, i hate this
	void WINAPI __dyn_tls_init(PVOID, DWORD dwReason, LPVOID) 
	#ifdef __cplusplus
	noexcept // terminate on any C++ exception that leaves a
	#endif
	// namespace-scope thread-local initializer
	// N4830 [basic.start.dynamic]/7
	{
		if (dwReason != DLL_THREAD_ATTACH || __tls_guard == true)
        return;

		/*
		* Guard against repeated initialization by setting the tls guard tested
		* by the compiler before we run any initializers.
		*/
		__tls_guard = true;

		/* prefast assumes we are overflowing __xd_a */
		#pragma warning(push)
		#pragma warning(disable: 26000)
		for (_PVFV* pfunc = &__xd_a + 1; pfunc != &__xd_z; ++pfunc)
		{
			if (*pfunc)
            (*pfunc)();
		}
		#pragma warning(pop)
	}

	void __cdecl __dyn_tls_on_demand_init()
	#ifdef __cplusplus
	noexcept
	#endif
	{
		__dyn_tls_init(nullptr, DLL_THREAD_ATTACH, nullptr);
	}

	vsys_size __chkstk(vsys_size StackSpaceSize) {
		//    TODO(V): !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! IMPLEMENT !!!!!!!!!

		//vsys_uintptr AdjustedStackPointer = __rsp + 0x18 - StackSpaceSize;
		//if (__rsp + 0x18 > StackSpaceSize) {
		//AdjustedStackPointer = 0;

		//}

		//vsys_uintptr StackLimit = reinterpret_cast<PNT_TIB>(NtCurrentTeb())->StackLimit;

	}

	#ifdef __cplusplus
}
#endif

#endif
