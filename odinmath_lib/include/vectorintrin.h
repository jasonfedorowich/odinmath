//
// Created by Jason Fedorowich on 2024-02-18.
//

#ifndef ODINMATH_VECTORINTRIN_H
#define ODINMATH_VECTORINTRIN_H

#include "odinmath.h"

namespace OdinMath {



#if defined(INTRIN) && defined(__aarch64__)
    using FloatVector128 = float32x4_t;
#elif defined(INTRIN) && defined(__x86_64__)
    using FloatVector128 = __m128;
#else
    using FloatVector128 = uint8_t;
#endif

    struct VectorFloat32{

        union {
            FloatVector128 v;
            float f[4];

        };
    };

    struct VectorInteger32{
        union {
            uint32x4_t v;
            int f[4];

        };
    };

    static VectorFloat32 zero = {{0.f, 0.f, 0.f, 0.f}};
    static VectorFloat32 one = {{1.f, 1.f, 1.f, 1.f}};
    static VectorFloat32 two = {{2.f, 2.f, 2.f, 2.f}};
    static VectorInteger32 oneInt = {{1, 1, 1, 1}};


#if defined(INTRIN) && defined(__x86_64__)
    inline __m256d load3(double* data){
        __m128d t1 = _mm_load_pd(data);
        __m128d t2 = _mm_load_sd(&(data[2]));
        __m128d t3 = _mm_set_sd(0.0);
        t3 = _mm_unpacklo_pd(t2, t3);
        float32x4_t qv  = vld1q_f32(&data[0]);
        return _mm256_set_m128d(t3, t1);
    }
    inline void store3(double* out, __m256d& in){
        _mm256_store_pd(out, in);
    }
    __m256d load4(double* data);
    __m128 load3(float* data);
    inline __m128 load4(float* data){
       return  _mm_load_ps(data);
    }
    inline void store4(float* out, __m128& in){
        _mm_store_ps(out, in);
    }
#endif

#if defined(INTRIN) && defined(__aarch64__)

#define SET_LANE_VECTOR(v, vector, lane) \
    vsetq_lane_f32(v, vector, lane)

#define GET_LANE_VECTOR(vector, lane) \
    vgetq_lane_f32(vector, lane)

#define GET_LANE_UINT_VECTOR(vector, lane) \
    vgetq_lane_s32(vector, lane)

    inline float32x4_t load4(const float *in) {
        return vld1q_f32(in);
    }

    inline void store4(float *out, float32x4_t in) {
        vst1q_f32(out, in);
    }

    inline float32x4_t load3(const float *in) {
        float32x2_t zeros = vdup_n_f32(0.f);
        float32x2_t first = vld1_f32(in);
        float32x2_t second = vld1_f32(&(in[2]));
        second = vcopy_lane_f32(second, 1, zeros, 0);
        return vcombine_f32(first, second);
    }

    inline void store3(float *out, float32x4_t in) {
        float32x2_t high = vget_high_f32(in);
        float32x2_t lo = vget_low_f32(in);
        float32x2_t tmp = vcopy_lane_f32(lo, 0, lo, 1);
        float32x2_t second = vcopy_lane_f32(tmp, 1, high, 0);
        vst1_f32(out, lo);
        vst1_f32(&(out[1]), second);

    }

    inline float32x4_t load2(const float *in) {
        float32x2_t zeros = vdup_n_f32(0.f);
        float32x2_t first = vld1_f32(in);
        return vcombine_f32(first, zeros);
    }

    inline void store2(float *out, float32x4_t in) {
        float32x2_t lo = vget_low_f32(in);
        vst1_f32(out, lo);
    }

    inline float32x4_t dupX(float32x4_t v){
        return vdupq_lane_f32(vget_low_f32(v), 0);
    }

    inline float32x4_t dupY(float32x4_t v){
        return vdupq_lane_f32(vget_low_f32(v), 1);
    }

    inline float32x4_t dupZ(float32x4_t v){
        return vdupq_lane_f32(vget_high_f32(v), 0);
    }

    inline float32x4_t dupW(float32x4_t v){
        return vdupq_lane_f32(vget_high_f32(v), 1);
    }

    inline float32x4_t add(const float32x4_t lhs, const float32x4_t rhs) {
        return vaddq_f32(lhs, rhs);
    }

    inline float32x4_t mul(const float32x4_t lhs, const float32x4_t rhs) {
        return vmulq_f32(lhs, rhs);
    }

    inline float32x4_t div(const float32x4_t top, const float32x4_t bot) {
        return vdivq_f32(top, bot);
    }

    inline float32x4_t div3(const float32x4_t top, const float32x4_t bot) {
        float32x4_t ones = vdupq_n_f32(1.f);
        float32x4_t tmp = vcopyq_laneq_f32(bot, 3, ones, 0);
        return vdivq_f32(top, tmp);
    }

    inline float32x4_t div2(const float32x4_t top, const float32x4_t bot) {
        float32x4_t ones = vdupq_n_f32(1.f);
        float32x4_t tmp = vcopyq_laneq_f32(bot, 3, ones, 0);
        tmp = vcopyq_laneq_f32(tmp, 2, ones, 0);
        return vdivq_f32(top, tmp);
    }

    inline float32x4_t sub(const float32x4_t lhs, const float32x4_t rhs) {
        return vsubq_f32(lhs, rhs);
    }

    /* a[i] + (b[i] * c[i]) */
    inline float32x4_t mulAdd(const float32x4_t a, const float32x4_t b, const float32x4_t c){
        return vmlaq_f32(a, b, c);
    }

    /* a[i] - (b[i] * c[i]) */
    inline float32x4_t mulSub(const float32x4_t a, const float32x4_t b, const float32x4_t c){
        return vmlsq_f32(a, b, c);
    }

    inline float32x4_t scalar(float scalar) {
        return vdupq_n_f32(scalar);
    }

    inline float32x4_t scalarMul(float sc, const float32x4_t rhs) {
        float32x4_t s = scalar(sc);
        return mul(s, rhs);
    }

    inline float32x4_t dot(const float32x4_t lhs, const float32x4_t rhs) {
        float32x4_t m = mul(lhs, rhs);
        float32x4_t rev = vrev64q_f32(m);
        float32x4_t ad = add(m, rev);
        float32x2_t lo = vget_low_f32(ad);
        float32x2_t hi = vget_high_f32(ad);
        float32x2_t sum = vadd_f32(lo, hi);
        return vcombine_f32(sum, sum);
    }

    inline float32x4_t length(const float32x4_t lhs, const float32x4_t rhs) {
        float32x4_t d = dot(lhs, rhs);
        return vsqrtq_f32(d);
    }

    inline float32x4_t cross3(const float32x4_t lhs, const float32x4_t rhs) {
        float32x4_t tmp1 = vrev64q_f32(lhs);
        tmp1 = vcopyq_laneq_f32(tmp1, 2, lhs, 0);
        float32x4_t tmp2 = vrev64q_f32(rhs);
        tmp2 = vcopyq_laneq_f32(tmp2, 2, rhs, 0);

        float32x4_t tmp3 = vrev64q_f32(lhs);
        tmp3 = vcopyq_laneq_f32(tmp3, 0, lhs, 2);
        tmp3 = vcopyq_laneq_f32(tmp3, 1, lhs, 2);
        tmp3 = vcopyq_laneq_f32(tmp3, 2, lhs, 1);

        float32x4_t tmp4 = vrev64q_f32(rhs);
        tmp4 = vcopyq_laneq_f32(tmp4, 0, rhs, 2);
        tmp4 = vcopyq_laneq_f32(tmp4, 1, rhs, 2);
        tmp4 = vcopyq_laneq_f32(tmp4, 2, rhs, 1);

        tmp1 = vmulq_f32(tmp1, tmp4);
        tmp2 = vmulq_f32(tmp2, tmp3);

        float32x4_t tmp = vdupq_n_f32(1.f);
        tmp = vsetq_lane_f32(-1.f, tmp, 1);
        float32x4_t sub = vsubq_f32(tmp1, tmp2);
        return vmulq_f32(sub, tmp);
    }

    inline float32x4_t zeroLast(float32x4_t vector) {
        float32x4_t zeros = vdupq_n_f32(0.f);
        return vcopyq_laneq_f32(vector, 3, zeros, 0);
    }

    inline float32x4_t duplicate(float number) {
        return vdupq_n_f32(number);
    }

    inline float32x4_t zeros() {
        return duplicate(0.f);
    }

    inline float32x4_t ones() {
        return duplicate(1.f);
    }

    inline uint32x4_t lessThan(float32x4_t v, float32x4_t p){
        return vcltq_f32(v, p);
    }

    inline uint32x4_t greaterThan(float32x4_t v, float32x4_t p){
        return vcgtq_f32(v, p);
    }

    inline uint32x4_t equalFloat(float32x4_t lhs, float32x4_t rhs) {
        return vceqq_f32(lhs, rhs);
    }

    inline float32x4_t condSelect(uint32x4_t cond, float32x4_t a, float32x4_t b){
        return vbslq_f32(cond, a, b);
    }

    inline uint32x4_t equalInt(uint32x4_t lhs, uint32x4_t rhs){
        return vceqq_s32(lhs, rhs);
    }

    inline bool equals(float32x4_t lhs, float32x4_t rhs) {
        uint32x4_t r = equalFloat(lhs, rhs);
        return GET_LANE_UINT_VECTOR(r, 0) != 0 &&
               GET_LANE_UINT_VECTOR(r, 1) != 0 &&
               GET_LANE_UINT_VECTOR(r, 2) != 0 &&
               GET_LANE_UINT_VECTOR(r, 3) != 0;
    }

    inline uint32x4_t _and(uint32x4_t lhs, uint32x4_t rhs) {
        return vandq_u32(lhs, rhs);
    }

    inline float32x4_t sqrtF(float32x4_t v){
        return vsqrtq_f32(v);
    }

    inline float32x4_t neg(float32x4_t v){
        return vnegq_f32(v);
    }

    /* Result = -x * y */
    inline float32x4_t negMul(float32x4_t x, float32x4_t y){
        return vmulq_f32(vnegq_f32(x), y);
    }

    inline float32x4_t addAdd(float32x4_t x, float32x4_t y){
        return add(x, add(x, y));
    }

    inline float32x4_t addAddNeg(float32x4_t x, float32x4_t y){
        return add(x, add(x, neg(y)));
    }

    inline float32x4_t addSub(float32x4_t x, float32x4_t y, float32x4_t z){
        return add(x, sub(y, z));
    }

    inline float32x4_t invert(float32x4_t v){
        return vrecpeq_f32(v);
    }

    inline int32x4_t greaterThanOrEqual(float32x4_t x, float32x4_t y) {
        return vcgeq_f32(x, y);
    }

    inline float32x4_t pow2(int32x4_t n){
        int32x4_t temp = vshlq_s32(oneInt.v, n);
        return vcvtq_f32_s32(temp);
    }

    inline float32x4_t expF(float32x4_t v){
        static VectorFloat32 v1 = {{1.4426950408889634074f, 0.693359375f, -2.1219444005469058277e-4f, 3.1622776601683793320f}};
        static VectorFloat32 v2 = {{0.25000000000000000000e+0, 0.75753180159422776666e-2, 0.31555192765684646356e-4, 0.5f}};
        static VectorFloat32 v3 = {{0.50000000000000000000e+0, 0.56817302698551221787e-1, 0.63121894374398503557e-3, 0.75104028399870046114e-6}};

        float32x4_t xn = mul(v, dupX(v1.v));
        int32x4_t n = vcvtq_u32_f32(xn);
        xn = vcvtq_f32_s32(n);
        float32x4_t g = mulSub(v, xn, dupY(v1.v));
        g = mulSub(g, xn, dupZ(v1.v));
        float32x4_t z = mul(g, g);

        float32x4_t gpz = mulAdd(dupY(v2.v), dupZ(v2.v), z);
        gpz = mulAdd(dupX(v2.v), gpz, z);
        gpz = mul(gpz, g);

        float32x4_t qz = mulAdd(dupZ(v3.v), dupW(v3.v), z);
        qz = mulAdd(dupY(v3.v), qz, z);
        qz = mulAdd(dupX(v3.v), qz, z);

        float32x4_t rg = sub(qz, gpz);
        rg = div(gpz, rg);
        rg = add(dupW(v2.v), rg);
        n = vaddq_s32(n, oneInt.v);
        float32x4_t p2 = pow2(n);
        return mul(rg, p2);

    }



#endif

}

#include "inline/vectorintrintrig.inl"

#endif

