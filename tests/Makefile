#///////////////////////////////////////////////////////////////////////////
#/
#/  VLiB Source File.
#/  Copyright (C), V Studio, 2018-2024.
#/ -------------------------------------------------------------------------
#/  File name:   Makefile
#/  Version:     v1.00
#/  Created:     03/05/24 by Serial Designation V-X1.
#/  Description: 
#/ -------------------------------------------------------------------------
#/  History:
#/
#///////////////////////////////////////////////////////////////////////////

GLOBAL_INC_PATHS ?= -I ../
GLOBAL_LIB_PATHS ?= 
GLOBAL_LIB_LINK ?= -l ws2_32 -l	onecore --for-linker=-nodefaultlib --for-linker=-subsystem:console --for-linker=-entry:VRuntime_MDos_NTAppInit -l kernel32 -l user32 -l ntdll -fno-exceptions -fno-builtin
VRCS_CPP_FLAGS ?= -O2 -g -DVLIB_REMOVE_TOSTR_FUNC -DVSYS_DEBUG

VRCS_CORE_SRX = ../*.cpp
V_MIMALLOC_SRX = ../mimalloc/alloc.c ../mimalloc/alloc-aligned.c ../mimalloc/alloc-posix.c ../mimalloc/arena.c ../mimalloc/bitmap.c ../mimalloc/heap.c ../mimalloc/init.c ../mimalloc/libc.c ../mimalloc/options.c ../mimalloc/os.c ../mimalloc/page.c ../mimalloc/random.c ../mimalloc/segment.c ../mimalloc/segment-map.c ../mimalloc/stats.c ../mimalloc/prim/prim.c

# This is for the 10x parser to not consider the /* as a c++ comment
# */


VLIB_RuntimeExecutable: $(VRCS_CORE_SRX) main.cpp $(V_MIMALLOC_SRX)
	@echo Building VLIB !!!
	clang++ -o $@.exe \
	$^ \
	$(GLOBAL_INC_PATHS) $(VRCS_CPP_FLAGS) $(GLOBAL_LIB_PATHS) $(GLOBAL_LIB_LINK)

run_tests:
	VLIB_RuntimeExecutable.exe
