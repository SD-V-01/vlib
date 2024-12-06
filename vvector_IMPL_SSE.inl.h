////////////////////////////////////////////////////////////////////////////
//
//  VLib Source File.
//  Copyright (C) 2024 S/N: V-01
// -------------------------------------------------------------------------
//  File name:   vvector_IMPL_SSE.inl.h
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

#ifndef VLIB_VMATH_IMPL
#warn Please try to include vmath.h instad of including random headers !!!

#endif

#define vmathVectorSplat(X, E) _mm_shuffle_ps(X, X, _MM_SHUFFLE(E, E, E, E))
#define vmathVectorDSplat(X, E) _mm_shuffle_pd(X, X, _MM_SHUFFLE(E, E, E, E))

vinl __m128 vmathVectorSelect(__m128 A, __m128 B, __m128 Mask){
	return _mm_or_ps(_mm_and_ps(Mask, B), _mm_andnot_ps(Mask, A));

}

vinl __m128 vmathVectorDot(__m128 A, __m128 B) {
	const __m128 Result = _mm_mul_ps(A, B);
	return _mm_add_ps(_mm_shuffle_ps(Result, Result, _MM_SHUFFLE(0, 0, 0, 0)),
					  _mm_add_ps(_mm_shuffle_ps(Result, Result, _MM_SHUFFLE(1, 1, 1, 1)),
								 _mm_add_ps(_mm_shuffle_ps(Result, Result, _MM_SHUFFLE(2, 2, 2, 2)),
											_mm_shuffle_ps(Result, Result, _MM_SHUFFLE(3, 3, 3, 3)))));

}

//SECTION(V): 3 Float vector simd SVEC3

VLIB_STRUCT(vec3)
union {
	__m128 Simd;
	float FArray[3];
	u32 UIntArray[3];
	i32 SIntArray[3];

	struct {
		float X;
		float Y;
		float Z;
		float __W; //NOTE(V): The forbidden float

	};

	struct {
		u32 AsUIntX;
		u32 AsUIntY;
		u32 AsUIntZ;
		u32 __AsUIntW;

	};

	struct {
		i32 AsSIntX;
		i32 AsSIntY;
		i32 AsSIntZ;
		i32 __AsSIntW;

	};

};

#ifdef VPP

explicit vinlpp vec3(){}

explicit vinlpp vec3(float X, float Y, float W) {
	Simd = _mm_setr_ps(X, Y, W, 0.0f);

}

explicit vinlpp vec3(float Scalar) {
	Simd = _mm_set1_ps(Scalar);

}

explicit vinlpp vec3(__m128 In) {
	Simd = In;

}

vinlpp void setAllLanes(float Scalar) {
	Simd = _mm_set1_ps(Scalar);

}

vinlpp void zero() {
	Simd = _mm_setzero_ps();

}

vinlpp void one() {
	Simd = _mm_setr_ps(1.0f, 1.0f, 1.0f, 1.0f);

}

vinlpp vec3& operator=(const vec3& Vec) {
	Simd = Vec.Simd;
	return *this;

}

vinlpp void Lset(float In, st Lane) {
	((float *)&(Simd))[Lane] = In;

}

vinlpp float Lget(st Lane) {
	return ((float *)&(Simd))[Lane];

}

vinlpp float operator[](int Lane) {
	return ((float *)&(Simd))[Lane];

}

vinlpp const float operator[](int Lane) const {
	return ((float *)&(Simd))[Lane];

}

vinlpp const vec3 operator+(const vec3& Vec) const {
	return vec3(_mm_add_ps(Simd, Vec.Simd));

}

vinlpp const vec3 operator+(float Scalar) const {
	return vec3(_mm_add_ps(Simd, _mm_set1_ps(Scalar)));

}

vinlpp const vec3 operator-(const vec3& Vec) const {
	return vec3(_mm_sub_ps(Simd, Vec.Simd));

}

vinlpp const vec3 operator-(float Scalar) const {
	return vec3(_mm_sub_ps(Simd, _mm_set1_ps(Scalar)));

}

vinlpp const vec3 operator*(const vec3& Vec) const {
	return vec3(_mm_mul_ps(Simd, Vec.Simd));

}

vinlpp const vec3 operator*(float Scalar) const {
	return vec3(_mm_mul_ps(Simd, _mm_set1_ps(Scalar)));

}

vinlpp const vec3 operator/(float Scalar) const {
	return vec3(_mm_div_ps(Simd, _mm_set1_ps(Scalar)));

}

vinlpp const vec3& operator+=(const vec3& Vec) {
	*this = *this + Vec;
	return *this;

}

vinlpp const vec3& operator+=(float Scalar) {
	*this = *this + Scalar;
	return *this;

}

vinlpp const vec3& operator-=(const vec3& Vec) {
	*this = *this - Vec;
	return *this;

}

vinlpp const vec3& operator-=(float Scalar) {
	*this = *this - Scalar;
	return *this;

}

vinlpp const vec3& operator*=(const vec3& Vec) {
	*this = *this * Vec;
	return *this;

}

vinlpp const vec3& operator*=(float Scalar) {
	*this = *this * Scalar;
	return *this;

}

vinlpp const vec3& operator/=(float Scalar) {
	*this = *this / Scalar;
	return *this;

}

vinlpp const vec3 recip(const vec3& Vec) {
	return vec3(_mm_rcp_ps(Vec.Simd));

}

#endif

VLIB_STRUCTEND(vec3)

vinl vec3 vec3sqrt(const vec3* Vec) {
	vec3 Result;
	Result.Simd = _mm_sqrt_ps(Vec->Simd);
	return Result;

}

vinl vec3 vec3rcp(const vec3* Vec) {
	vec3 Result;
	Result.Simd = _mm_rcp_ps(Vec->Simd);
	return Result;

}

vinl vec3 vec3rsqrt(const vec3* Vec) {
	vec3 Result;
	Result.Simd = _mm_rsqrt_ps(Vec->Simd);
	return Result;

}

vinl vec3 vec3min(const vec3* A, const vec3* B) {
	vec3 Result;
	Result.Simd = _mm_min_ps(A->Simd, B->Simd);
	return Result;

}

vinl vec3 vec3max(const vec3* A, const vec3* B) {
	vec3 Result;
	Result.Simd = _mm_max_ps(A->Simd, B->Simd);
	return Result;

}

vinl vec3 vec3abs(const vec3* Vec) {
	const u32 FMask = 0x7FFFFFFF;
	const float* FMaskPtr = (const float*)&FMask;
	vec3 Result;
	__m128 Mask = _mm_set1_ps(*FMaskPtr);
	((float*)&(Mask))[3] = 0.0f;
	Result.Simd = _mm_and_ps(Vec->Simd, Mask);
	return Result;

}

vinl vec3 vec3sign(const vec3* Value, const vec3* Signing) {
	const u32 FMask = 0x7FFFFFFF;
	const float* FMaskPtr = (const float*)&FMask;
	__m128 Mask = _mm_set1_ps(*FMaskPtr);
	((u32*)&(Mask))[3] = 0;
	vec3 Result;
	Result.Simd = _mm_or_ps(_mm_and_ps(Mask, Value->Simd), _mm_andnot_ps(Mask, Signing->Simd));
	return Result;

}

vinl vec3 vec3add(const vec3* A, const vec3* B) {
	vec3 Result;
	Result.Simd = _mm_add_ps(A->Simd, B->Simd);
	return Result;

}

vinl vec3 vec3sub(const vec3* A, const vec3* B) {
	vec3 Result;
	Result.Simd = _mm_sub_ps(A->Simd, B->Simd);
	return Result;

}

vinl vec3 vec3mul(const vec3* A, const vec3* B) {
	vec3 Result;
	Result.Simd = _mm_mul_ps(A->Simd, B->Simd);
	return Result;

}

vinl void vec3addequal(vec3* A, const vec3* B) {
	A->Simd = _mm_add_ps(A->Simd, B->Simd);

}

vinl void vec3subequal(vec3* A, const vec3* B) {
	A->Simd = _mm_sub_ps(A->Simd, B->Simd);

}

vinl void vec3mulequal(vec3* A, const vec3* B) {
	A->Simd = _mm_mul_ps(A->Simd, B->Simd);

}

vinl vec3 vec3Sadd(vec3* A, float Scalar) {
	vec3 Result;
	Result.Simd = _mm_add_ps(A->Simd, _mm_set1_ps(Scalar));
	return Result;

}

vinl vec3 vec3Ssub(vec3* A, float Scalar) {
	vec3 Result;
	Result.Simd = _mm_sub_ps(A->Simd, _mm_set1_ps(Scalar));
	return Result;

}

vinl vec3 vec3Smul(vec3* A, float Scalar) {
	vec3 Result;
	Result.Simd = _mm_mul_ps(A->Simd, _mm_set1_ps(Scalar));
	return Result;

}

vinl vec3 vec3Sdiv(vec3* A, float Scalar) {
	vec3 Result;
	Result.Simd = _mm_div_ps(A->Simd, _mm_set1_ps(Scalar));
	return Result;

}

vinl void vec3Saddequal(vec3* A, float Scalar) {
	A->Simd = _mm_add_ps(A->Simd, _mm_set1_ps(Scalar));

}

vinl void vec3Ssubequal(vec3* A, float Scalar) {
	A->Simd = _mm_sub_ps(A->Simd, _mm_set1_ps(Scalar));

}

vinl void vec3Smulequal(vec3* A, float Scalar) {
	A->Simd = _mm_mul_ps(A->Simd, _mm_set1_ps(Scalar));

}

vinl void vec3Sdivequal(vec3* A, float Scalar) {
	A->Simd = _mm_div_ps(A->Simd, _mm_set1_ps(Scalar));

}

//SECTION(V): 4 Float simd vector SVEC4

VLIB_STRUCT(vec4)

union {
	__m128 Simd;
	float FArray[4];
	double DArray[2];
	u64 UInt64Array[2];
	u32 UIntArray[4];
	i64 SInt64Array[2];
	i32 SIntArray[4];

	struct {
		float X;
		float Y;
		float Z;
		float W;

	};

	struct {
		u32 AsUIntX;
		u32 AsUIntY;
		u32 AsUIntZ;
		u32 AsUIntW;

	};

	struct {
		i32 AsSIntX;
		i32 AsSIntY;
		i32 AsSIntZ;
		i32 AsSIntW;

	};

};

#ifdef VPP

explicit vinlpp vec4(){}

explicit vinlpp vec4(float X, float Y, float Z, float W) {
	Simd = _mm_setr_ps(X, Y, Z, W);

}

explicit vinlpp vec4(float Scalar) {
	Simd = _mm_set1_ps(Scalar);

}

explicit vinlpp vec4(__m128 In) {
	Simd = In;

}

vinlpp void setAllLanes(float Scalar) {
	Simd = _mm_set1_ps(Scalar);

}

vinlpp void zero() {
	Simd = _mm_setzero_ps();

}

vinlpp void one() {
	Simd = _mm_setr_ps(1.0f, 1.0f, 1.0f, 1.0f);

}

vinlpp vec4& operator=(const vec4& Vec) {
	Simd = Vec.Simd;
	return *this;

}

vinlpp vec4& setXYZ(const vec3& Vec) {
	const u32 AllOne = 0xFFFFFFFF;
	const float* AllOnePtr = (float*)&AllOne;
	__m128 S = _mm_setr_ps(0, 0, 0, *AllOnePtr);
	Simd = vmathVectorSelect(Vec.Simd, Simd, S);
	return *this;

}

vinlpp void Lset(float In, st Lane) {
	((float *)&(Simd))[Lane] = In;

}

vinlpp float Lget(st Lane) {
	return ((float *)&(Simd))[Lane];

}

vinlpp float operator[](int Lane) {
	return ((float *)&(Simd))[Lane];

}

vinlpp const float operator[](int Lane) const {
	return ((float *)&(Simd))[Lane];

}

vinlpp const vec4 operator+(const vec4& Vec) const {
	return vec4(_mm_add_ps(Simd, Vec.Simd));

}

vinlpp const vec4 operator+(float Scalar) const {
	return vec4(_mm_add_ps(Simd, _mm_set1_ps(Scalar)));

}

vinlpp const vec4 operator-(const vec4& Vec) const {
	return vec4(_mm_sub_ps(Simd, Vec.Simd));

}

vinlpp const vec4 operator-(float Scalar) const {
	return vec4(_mm_sub_ps(Simd, _mm_set1_ps(Scalar)));

}

vinlpp const vec4 operator*(const vec4& Vec) const {
	return vec4(_mm_mul_ps(Simd, Vec.Simd));

}

vinlpp const vec4 operator*(float Scalar) const {
	return vec4(_mm_mul_ps(Simd, _mm_set1_ps(Scalar)));

}

vinlpp const vec4 operator/(const vec4& Vec) const {
	return vec4(_mm_div_ps(Simd, Vec.Simd));

}

vinlpp const vec4 operator/(float Scalar) const {
	return vec4(_mm_div_ps(Simd, _mm_set1_ps(Scalar)));

}

vinlpp const vec4& operator+=(const vec4& Vec) {
	*this = *this + Vec;
	return *this;

}

vinlpp const vec4& operator+=(float Scalar) {
	*this = *this + Scalar;
	return *this;

}

vinlpp const vec4& operator-=(const vec4& Vec) {
	*this = *this - Vec;
	return *this;

}

vinlpp const vec4& operator-=(float Scalar) {
	*this = *this - Scalar;
	return *this;

}

vinlpp const vec4& operator*=(const vec4& Vec) {
	*this = *this * Vec;
	return *this;

}

vinlpp const vec4& operator*=(float Scalar) {
	*this = *this * Scalar;
	return *this;

}

vinlpp const vec4& operator/=(const vec4& Vec) {
	*this = *this / Vec;
	return *this;

}

vinlpp const vec4& operator/=(float Scalar) {
	*this = *this / Scalar;
	return *this;

}

vinlpp const vec4 recip(const vec4& Vec) {
	return vec4(_mm_rcp_ps(Vec.Simd));

}

#endif

VLIB_STRUCTEND(vec4)

vinl vec4 vec4sqrt(const vec4* Vec) {
	vec4 Result;
	Result.Simd = _mm_sqrt_ps(Vec->Simd);
	return Result;

}

vinl vec4 vec4rcp(const vec4* Vec) {
	vec4 Result;
	Result.Simd = _mm_rcp_ps(Vec->Simd);
	return Result;

}

vinl vec4 vec4rsqrt(const vec4* Vec) {
	vec4 Result;
	Result.Simd = _mm_rsqrt_ps(Vec->Simd);
	return Result;

}

vinl vec4 vec4min(const vec4* A, const vec4* B) {
	vec4 Result;
	Result.Simd = _mm_min_ps(A->Simd, B->Simd);
	return Result;

}

vinl vec4 vec4max(const vec4* A, const vec4* B) {
	vec4 Result;
	Result.Simd = _mm_max_ps(A->Simd, B->Simd);
	return Result;

}

vinl vec4 vec4abs(const vec4* Vec) {
	const u32 FMask = 0x7FFFFFFF;
	const float* FMaskPtr = (const float*)&FMask;
	vec4 Result;
	Result.Simd = _mm_and_ps(Vec->Simd, _mm_set1_ps(*FMaskPtr));
	return Result;

}

vinl vec4 vec4sign(const vec4* Value, const vec4* Signing) {
	const u32 FMask = 0x7FFFFFFF;
	const float* FMaskPtr = (const float*)&FMask;
	const __m128 Mask = _mm_set1_ps(*FMaskPtr);
	vec4 Result;
	Result.Simd = _mm_or_ps(_mm_and_ps(Mask, Value->Simd), _mm_andnot_ps(Mask, Signing->Simd));
	return Result;

}

vinl float vec4Emax(const vec4* Vec) {
	const __m128 Result = _mm_max_ps(_mm_max_ps(vmathVectorSplat(Vec->Simd, 0), vmathVectorSplat(Vec->Simd, 1)),
							  _mm_max_ps(vmathVectorSplat(Vec->Simd, 2), vmathVectorSplat(Vec->Simd, 3)));

	return ((float *)&(Result))[0];

}

vinl float vec4Emin(const vec4* Vec) {
	const __m128 Result = _mm_min_ps(_mm_min_ps(vmathVectorSplat(Vec->Simd, 0), vmathVectorSplat(Vec->Simd, 1)),
									 _mm_min_ps(vmathVectorSplat(Vec->Simd, 2), vmathVectorSplat(Vec->Simd, 3)));

	return ((float *)&(Result))[0];

}

vinl float vec4Esum(const vec4* Vec) {
	const __m128 Result = _mm_add_ps(_mm_add_ps(vmathVectorSplat(Vec->Simd, 0), vmathVectorSplat(Vec->Simd, 1)),
									 _mm_add_ps(vmathVectorSplat(Vec->Simd, 2), vmathVectorSplat(Vec->Simd, 3)));

	return ((float *)&(Result))[0];

}

vinl float vec4Edot(const vec4* A, const vec4* B) {
	const __m128 Result = vmathVectorDot(A->Simd, B->Simd);
	return ((float *)&(Result))[0];

}

vinl void vec4Lfill(vec4* Vec, float Scalar) {
	Vec->Simd = _mm_set1_ps(Scalar);

}

vinl void vec4zero(vec4* Vec) {
	Vec->Simd = _mm_setzero_ps();

}

vinl void vec4one(vec4* Vec) {
	Vec->Simd = _mm_setr_ps(1.0f, 1.0f, 1.0f, 1.0f);

}

vinl vec4 vec4init(float X, float Y, float Z, float W) {
	vec4 Result;
	Result.Simd = _mm_setr_ps(X, Y, Z, W);
	return Result;

}

vinl void vec4setXYZ(vec4* Vec, const vec3* InVec) {
	const u32 AllOne = 0xFFFFFFFF;
	const float* AllOnePtr = (float*)&AllOne;
	__m128 S = _mm_setr_ps(0, 0, 0, *AllOnePtr);
	Vec->Simd = vmathVectorSelect(Vec->Simd, InVec->Simd, S);

}

vinl void vec4Lset(vec4* Vec, float In, st Lane) {
	((float*)&(Vec->Simd))[Lane] = In;

}

vinl float vec4Lget(vec4* Vec, st Lane) {
	return ((float*)&(Vec->Simd))[Lane];

}

vinl vec4 vec4add(const vec4* A, const vec4* B) {
	vec4 Result;
	Result.Simd = _mm_add_ps(A->Simd, B->Simd);
	return Result;

}

vinl vec4 vec4sub(const vec4* A, const vec4* B) {
	vec4 Result;
	Result.Simd = _mm_sub_ps(A->Simd, B->Simd);
	return Result;

}

vinl vec4 vec4mul(const vec4* A, const vec4* B) {
	vec4 Result;
	Result.Simd = _mm_mul_ps(A->Simd, B->Simd);
	return Result;

}

vinl vec4 vec4div(const vec4* A, const vec4* B) {
	vec4 Result;
	Result.Simd = _mm_div_ps(A->Simd, B->Simd);
	return Result;

}

vinl void vec4addequal(vec4* A, const vec4* B) {
	A->Simd = _mm_add_ps(A->Simd, B->Simd);

}

vinl void vec4subequal(vec4* A, const vec4* B) {
	A->Simd = _mm_sub_ps(A->Simd, B->Simd);

}

vinl void vec4mulequal(vec4* A, const vec4* B) {
	A->Simd = _mm_mul_ps(A->Simd, B->Simd);

}

vinl void vec4divequal(vec4* A, const vec4* B) {
	A->Simd = _mm_div_ps(A->Simd, B->Simd);

}

vinl vec4 vec4Sadd(vec4* A, float Scalar) {
	vec4 Result;
	Result.Simd = _mm_add_ps(A->Simd, _mm_set1_ps(Scalar));
	return Result;

}

vinl vec4 vec4Ssub(vec4* A, float Scalar) {
	vec4 Result;
	Result.Simd = _mm_sub_ps(A->Simd, _mm_set1_ps(Scalar));
	return Result;

}

vinl vec4 vec4Smul(vec4* A, float Scalar) {
	vec4 Result;
	Result.Simd = _mm_mul_ps(A->Simd, _mm_set1_ps(Scalar));
	return Result;

}

vinl vec4 vec4Sdiv(vec4* A, float Scalar) {
	vec4 Result;
	Result.Simd = _mm_div_ps(A->Simd, _mm_set1_ps(Scalar));
	return Result;

}

vinl void vec4Saddequal(vec4* A, float Scalar) {
	A->Simd = _mm_add_ps(A->Simd, _mm_set1_ps(Scalar));

}

vinl void vec4Ssubequal(vec4* A, float Scalar) {
	A->Simd = _mm_sub_ps(A->Simd, _mm_set1_ps(Scalar));

}

vinl void vec4Smulequal(vec4* A, float Scalar) {
	A->Simd = _mm_mul_ps(A->Simd, _mm_set1_ps(Scalar));

}

vinl void vec4Sdivequal(vec4* A, float Scalar) {
	A->Simd = _mm_div_ps(A->Simd, _mm_set1_ps(Scalar));

}

//SECTION(V): 2 Double simd vector SVEC2D

VLIB_STRUCT(vec2d)

union {
	__m128d Simd;
	float FArray[4];
	double DArray[2];
	u64 UInt64Array[2];
	u32 UIntArray[4];
	i64 SInt64Array[2];
	i32 SIntArray[4];

	struct {
		double X;
		double Y;

	};

	struct {
		u32 AsUIntX;
		u32 AsUIntY;
		u32 AsUIntZ;
		u32 AsUIntW;

	};

	struct {
		i32 AsSIntX;
		i32 AsSIntY;
		i32 AsSIntZ;
		i32 AsSIntW;

	};

};

#ifdef VPP
explicit vinlpp vec2d(){}

explicit vinlpp vec2d(double Xin, double Yin) {
	Simd = _mm_setr_pd(Xin, Yin);

}

explicit vinlpp vec2d(double Scalar) {
	Simd = _mm_set1_pd(Scalar);

}

explicit vinlpp vec2d(__m128d In) {
	Simd = In;

}

vinlpp void setAllLanes(double Scalar) {
	Simd = _mm_set1_pd(Scalar);

}

vinlpp void zero() {
	Simd = _mm_setzero_pd();

}

vinlpp void one() {
	Simd = _mm_setr_pd(1.0l, 1.0l);

}

vinlpp vec2d& operator=(const vec2d& Vec) {
	Simd = Vec.Simd;
	return *this;

}

vinlpp void Lset(double In, st Lane) {
	((double*)&(Simd))[Lane] = In;

}

//TODO(V): Add asserts to check for invalid lane set

vinlpp double Lget(st Lane) {
	return ((double*)&(Simd))[Lane];

}

vinlpp double operator[](int Lane) {
	return ((double*)&(Simd))[Lane];

}

vinlpp const double operator[](int Lane) const {
	return ((double*)&(Simd))[Lane];

}

vinlpp const vec2d operator+(const vec2d& Vec) const {
	return vec2d(_mm_add_pd(Simd, Vec.Simd));

}

vinlpp const vec2d operator+(double Scalar) const {
	return vec2d(_mm_add_pd(Simd, _mm_set1_pd(Scalar)));

}

vinlpp const vec2d operator-(const vec2d& Vec) const {
	return vec2d(_mm_sub_pd(Simd, Vec.Simd));

}

vinlpp const vec2d operator-(double Scalar) const {
	return vec2d(_mm_sub_pd(Simd, _mm_set1_pd(Scalar)));

}

vinlpp const vec2d operator*(const vec2d& Vec) const {
	return vec2d(_mm_mul_pd(Simd, Vec.Simd));

}

vinlpp const vec2d operator*(double Scalar) const {
	return vec2d(_mm_mul_pd(Simd, _mm_set1_pd(Scalar)));

}

vinlpp const vec2d operator/(const vec2d& Vec) const {
	return vec2d(_mm_div_pd(Simd, Vec.Simd));

}

vinlpp const vec2d operator/(double Scalar) const {
	return vec2d(_mm_div_pd(Simd, _mm_set1_pd(Scalar)));

}


vinlpp const vec2d& operator+=(const vec2d& Vec) {
	*this = *this + Vec;
	return *this;

}

vinlpp const vec2d& operator+=(float Scalar) {
	*this = *this + Scalar;
	return *this;

}

vinlpp const vec2d& operator-=(const vec2d& Vec) {
	*this = *this - Vec;
	return *this;

}

vinlpp const vec2d& operator-=(float Scalar) {
	*this = *this - Scalar;
	return *this;

}

vinlpp const vec2d& operator*=(const vec2d& Vec) {
	*this = *this * Vec;
	return *this;

}

vinlpp const vec2d& operator*=(float Scalar) {
	*this = *this * Scalar;
	return *this;

}

vinlpp const vec2d& operator/=(const vec2d& Vec) {
	*this = *this / Vec;
	return *this;

}

vinlpp const vec2d& operator/=(float Scalar) {
	*this = *this / Scalar;
	return *this;

}

#endif

VLIB_STRUCTEND(vec2d)

vinl vec2d vec2dsqrt(const vec2d* Vec) {
	vec2d Result;
	Result.Simd = _mm_sqrt_pd(Vec->Simd);
	return Result;

}

vinl vec2d vec2dmin(const vec2d* A, const vec2d* B) {
	vec2d Result;
	Result.Simd = _mm_min_pd(A->Simd, B->Simd);
	return Result;

}

vinl vec2d vec2dmax(const vec2d* A, const vec2d* B) {
	vec2d Result;
	Result.Simd = _mm_max_pd(A->Simd, B->Simd);
	return Result;

}

//TODO(V): Write vec2dsign

//TODO(V): This dosen't compile for some reason, i am probabelly not going to use this so fuck it
#if 0
vinl double vec2dEmax(const vec2d* Vec) {
	const __m128d Result = _mm_max_pd(vmathVectorDSplat(Vec->Simd, 0), vmathVectorDSplat(Vec->Simd, 1));
	return ((double*)&(Result))[0];
//    UNTESTED(V):

}

vinl double vec2dEmin(const vec2d* Vec) {
	const __m128d Result = _mm_min_pd(vmathVectorDSplat(Vec->Simd, 0), vmathVectorDSplat(Vec->Simd, 1));
	return ((double*)&(Result))[0];
//    UNTESTED(V):

}

vinl double vec2dEsum(const vec2d* Vec) {
	const __m128d Result = _mm_add_pd(vmathVectorDSplat(Vec->Simd, 0), vmathVectorDSplat(Vec->Simd, 1));
	return ((double*)&(Result))[0];
//    UNTESTED(V):

}

#endif

//TODO(V): Write vec2dEdot

vinl void vec2dLfill(vec2d* Vec, double Scalar) {
	Vec->Simd = _mm_set1_pd(Scalar);

}

vinl void vec2dzero(vec2d* Vec) {
	Vec->Simd = _mm_setzero_pd();

}

vinl void vec2done(vec2d* Vec) {
	Vec->Simd = _mm_setr_pd(1.0l, 1.0l);

}

vinl vec2d vec2dinit(double X, double Y) {
	vec2d Result;
	Result.Simd = _mm_setr_pd(X, Y);
	return Result;

}

vinl void vec2dLset(vec2d* Vec, double In, st Lane) {
	((double*)&(Vec->Simd))[Lane] = In;

}

vinl double vec2dLget(vec2d* Vec, st Lane) {
	return ((double*)&(Vec->Simd))[Lane];

}
