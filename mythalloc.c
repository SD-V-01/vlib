////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   mythalloc.c
//  Version:     v1.00
//  Created:     28/07/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "mythalloc_api.h"
#include "mythalloc.h"

//SECTION(V): API

VLIB_CABI
void mytha_init(){


}

void* mytha_malloc(st Size) {


}

void* mytha_aalloc(st Size, st Alignment) {


}

void mytha_free(void* Ptr) {


}

void* mytha_realloc(void* Ptr, st NewSize) {


}

void* mytha_arealloc(void* Ptr, st NewSize, st Alignment) {


}

void* mytha_calloc(st Size, st Count) {


}

void* mytha_zeroalloc(st NewSize) {


}

void* mytha_zerocalloc(void* Ptr, st NewCount, st NewSize) {


}

void* mytha_zerorealloc(void* Ptr, st NewSize) {


}

void mytha_zerofree(void* Ptr) {


}

VLIB_CABIEND
