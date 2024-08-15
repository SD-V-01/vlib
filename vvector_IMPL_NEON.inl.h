////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   vvector_IMPL_NEON.inl.h
//  Version:     v1.00
//  Created:     07/08/24 by V.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#ifdef TENX_PARSER
#include "base_types.h"
#include "vmath.h"

#endif

VLIB_STRUCT(vec4)
float32x4_t Data;

#ifdef VPP
vinl vec4(float X, float Y, float Z, float W) {
	float __attribute__ ((aligned(16))) FData[4] = { X, Y, Z, W };
	Data = vld1q_f32(FData);

}

vinl vec4(float Scalar) {
	Data = vdupq_n_f32(Scalar);

}

vinl vec4(float32x4_t In) {
	Data = In;

}

vinl void setAllLanes(float Scalar) {
	Data = vdupq_n_f32(Scalar);

}

vinl void zero() {
	VMATH_ALIGN(const float FData[4]) = { 0.0f, 0.0f, 0.0f, 0.0f };
	Data = vld1q_f32(FData);

}

vinl void zero() {
	const float __attribute__ ((aligned(16))) FData[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	Data = vld1q_f32(FData);

}

vinl void Xset(float In) {
	((float *)&(Data))[0] = In;

}

vinl void Yset(float In) {
	((float *)&(Data))[1] = In;

}

vinl void Zset(float In) {
	((float *)&(Data))[2] = In;

}

vinl void Wset(float In) {
	((float *)&(Data))[3] = In;

}

vinl void Lset(float In, st Lane) {
	((float *)&(Data))[Lane] = In;

}

vinl float Xget() {
	return ((float *)&(Data))[0];

}

vinl float Yget() {
	return ((float *)&(Data))[1];

}

vinl float Zget() {
	return ((float *)&(Data))[2];

}

vinl float Wget() {
	return ((float *)&(Data))[3];

}

vinl float Lget(st Lane) {
	return ((float *)&(Data))[Lane];

}

vinl float operator[](int Lane) {
	return ((float *)&(Data))[Lane];

}

vinl const float operator[](int Lane) const {
	return ((float *)&(Data))[Lane];

}

vinl const vec4 operator+(const vec4& Vector) const {
	return vec4(vaddq_f32(Data, Vector.Data));

}

vinl const vec4 operator-(const vec4& Vector) const {
	return vec4(vsubq_f32(Data, Vector.Data));

}

#endif

VLIB_STRUCTEND(vec4)

vinl vec4 vec4init4(float X, float Y, float Z, float W) {
	vec4 Result;
	float __attribute__ ((aligned(16))) Data[4] = { X, Y, Z, W };
	Result.Data = vld1q_f32(Data);
	return Result;

}

vinl vec4 vec4scalar(float Scalar) {
	vec4 Result;
	Result.data = vdupq_n_f32(Scalar);
	return Result;
}

vinl void vec4Xset(vec4* Vector, float In) {
	((float *)&(Vector->Data))[0] = In;

}

vinl void vec4Yset(vec4* Vector, float In) {
	((float *)&(Vector->Data))[1] = In;

}

vinl void vec4Zset(vec4* Vector, float In) {
	((float *)&(Vector->Data))[2] = In;

}

vinl void vec4Wset(vec4* Vector, float In) {
	((float *)&(Vector->Data))[3] = In;

}

vinl void vec4Lset(vec4* Vector, float In, st Lane) {
	((float *)&(Vector->Data))[Lane] = In;

}

vinl float vec4Xget(vec4* Vector) {
	return ((float *)&(Vector->Data))[0];

}

vinl float vec4Yget(vec4* Vector) {
	return ((float *)&(Vector->Data))[1];

}

vinl float vec4Zget(vec4* Vector) {
	return ((float *)&(Vector->Data))[2];

}

vinl float vec4Wget(vec4* Vector) {
	return ((float *)&(Vector->Data))[3];

}

vinl float vec4Lget(vec4* Vector, st Lane) {
	return ((float *)&(Vector->Data))[Lane];

}

vinl vec4 vec4add(const vec4* Vector0, const vec4* Vector1) {
	vec4 Result;
	Result.Data = vaddq_f32(Vector0->Data, Vector1->Data);
	return Result;

}

vinl void vec4addequal(vec4* Vector0, const vec4* Vector1) {
	Vector0->Data = vaddq_f32(Vector0->Data, Vector1->Data);

}

vinl vec4 vec4sub(const vec4* Vector0, const vec4* Vector1) {
	vec4 Result;
	Result.Data = vsubq_f32(Vector0->Data, Vector1->Data);
	return Result;

}

vinl void vec4subequal(vec4* Vector0, const vec4* Vector1) {
	Vector0->Data = vsubq_f32(Vector0->Data, Vector1->Data);

}

vinl vec4 vec4mul(const vec4* Vector0, const vec4* Vector1) {
	vec4 Result;
	Result.Data = vmulq_f32(Vector0->Data, Vector1->Data);
	return Result;

}

vinl void vec4mulequal(vec4* Vector0, const vec4* Vector1) {
	Vector0->Data = vmulq_f32(Vector0->Data, Vector1->Data);

}
