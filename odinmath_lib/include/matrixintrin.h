//
// Created by Jason Fedorowich on 2024-04-23.
//

#ifndef ODINMATH_MATRIXINTRIN_H
#define ODINMATH_MATRIXINTRIN_H

#include "odinmath.h"

namespace OdinMath{

#if defined(INTRIN) && defined(__x86_64__)
    //todo
#endif

#if defined(INTRIN) && defined(__aarch64__)

    struct FloatMatrix128x4{
        FloatVector128 vectors[4];

        FloatMatrix128x4()= default;

        explicit FloatMatrix128x4(float matrix[4][4]){
            vectors[0] = load4(matrix[0]);
            vectors[1] = load4(matrix[1]);
            vectors[2] = load4(matrix[2]);
            vectors[3] = load4(matrix[3]);
        }

        explicit FloatMatrix128x4(float matrix[3][3]){
            vectors[0] = load3(matrix[0]);
            vectors[1] = load3(matrix[1]);
            vectors[2] = load3(matrix[2]);
            vectors[3] = duplicate(0.f);
            vectors[3] = SET_LANE_VECTOR(1.f, vectors[3], 3);
        }

        explicit FloatMatrix128x4(float matrix[2][2]){
            vectors[0] = load3(matrix[0]);
            vectors[1] = load3(matrix[1]);
            vectors[2] = duplicate(0.f);
            vectors[3] = duplicate(0.f);
        }

        explicit FloatMatrix128x4(Matrix<4, 4, float>& matrix){
            vectors[0] = load4(matrix[0]);
            vectors[1] = load4(matrix[1]);
            vectors[2] = load4(matrix[2]);
            vectors[3] = load4(matrix[3]);
        }

        explicit FloatMatrix128x4(Matrix<3, 3, float>& matrix){
            vectors[0] = load3(matrix[0]);
            vectors[1] = load3(matrix[1]);
            vectors[2] = load3(matrix[2]);
            vectors[3] = duplicate(0.f);
        }

        explicit FloatMatrix128x4(Matrix<2, 2, float>& matrix){
            vectors[0] = load3(matrix[0]);
            vectors[1] = load3(matrix[1]);
            vectors[2] = duplicate(0.f);
            vectors[3] = duplicate(0.f);
        }

        explicit FloatMatrix128x4(FloatVector128 first,
                                  FloatVector128 second,
                                  FloatVector128 third,
                                  FloatVector128 fourth){
            vectors[0] = first;
            vectors[1] = second;
            vectors[2] = third;
            vectors[3] = fourth;
        }

        bool operator==(const FloatMatrix128x4& lhs) const{
            uint32x4_t first = equal(this->vectors[0], lhs.vectors[0]);
            uint32x4_t second = equal(this->vectors[1], lhs.vectors[1]);
            uint32x4_t third = equal(this->vectors[2], lhs.vectors[2]);
            uint32x4_t fourth = equal(this->vectors[3], lhs.vectors[3]);

            uint32x4_t tmp1 = _and(first, second);
            uint32x4_t tmp2 = _and(third, fourth);
            tmp1 = _and(tmp1, tmp2);
            return GET_LANE_UINT_VECTOR(tmp1, 0) !=0 &&
                    GET_LANE_UINT_VECTOR(tmp1, 1) !=0 &&
                    GET_LANE_UINT_VECTOR(tmp1, 2) !=0 &&
                    GET_LANE_UINT_VECTOR(tmp1, 3) !=0;

        }

    };

    inline void store4(Matrix<4, 4, float>* output, FloatMatrix128x4 matrix){
        store4(output->getRow(0), matrix.vectors[0]);
        store4(output->getRow(1), matrix.vectors[1]);
        store4(output->getRow(2), matrix.vectors[2]);
        store4(output->getRow(3), matrix.vectors[3]);
    }

    inline void store3(Matrix<3, 3, float>* output, FloatMatrix128x4 matrix){
        store3(output->getRow(0), matrix.vectors[0]);
        store3(output->getRow(1), matrix.vectors[1]);
        store3(output->getRow(2), matrix.vectors[2]);
    }


    inline FloatMatrix128x4 add(FloatMatrix128x4 lhs, FloatMatrix128x4 rhs){
        return FloatMatrix128x4(add(lhs.vectors[0], rhs.vectors[0]),
                                add(lhs.vectors[1], rhs.vectors[1]),
                                add(lhs.vectors[2], rhs.vectors[2]),
                                add(lhs.vectors[3], rhs.vectors[3]));
    }

    inline FloatMatrix128x4 sub(FloatMatrix128x4 lhs, FloatMatrix128x4 rhs){
        return FloatMatrix128x4(sub(lhs.vectors[0], rhs.vectors[0]),
                                sub(lhs.vectors[1], rhs.vectors[1]),
                                sub(lhs.vectors[2], rhs.vectors[2]),
                                sub(lhs.vectors[3], rhs.vectors[3]));
    }

    inline FloatMatrix128x4 mul(FloatMatrix128x4 lhs, FloatMatrix128x4 rhs){
        float32x2_t lo = vget_low_f32(lhs.vectors[0]);
        float32x2_t hi = vget_high_f32(lhs.vectors[0]);
        float32x4_t first = vmulq_lane_f32(rhs.vectors[0], lo, 0);
        float32x4_t second = vmulq_lane_f32(rhs.vectors[1], lo, 1);
        first = vaddq_f32(first, second);
        first = vmlaq_lane_f32(first, rhs.vectors[2], hi, 0);
        first = vmlaq_lane_f32(first, rhs.vectors[3], hi, 1);

        lo = vget_low_f32(lhs.vectors[1]);
        hi = vget_high_f32(lhs.vectors[1]);
        second = vmulq_lane_f32(rhs.vectors[0], lo, 0);
        float32x4_t third = vmulq_lane_f32(rhs.vectors[1], lo, 1);
        second = vaddq_f32(second, third);
        second = vmlaq_lane_f32(second, rhs.vectors[2], hi, 0);
        second = vmlaq_lane_f32(second, rhs.vectors[3], hi, 1);

        lo = vget_low_f32(lhs.vectors[2]);
        hi = vget_high_f32(lhs.vectors[2]);
        third = vmulq_lane_f32(rhs.vectors[0], lo, 0);
        float32x4_t fourth = vmulq_lane_f32(rhs.vectors[1], lo, 1);
        third = vaddq_f32(third, fourth);
        third = vmlaq_lane_f32(third, rhs.vectors[2], hi, 0);
        third = vmlaq_lane_f32(third, rhs.vectors[3], hi, 1);

        lo = vget_low_f32(lhs.vectors[3]);
        hi = vget_high_f32(lhs.vectors[3]);
        fourth = vmulq_lane_f32(rhs.vectors[0], lo, 0);
        float32x4_t fifth = vmulq_lane_f32(rhs.vectors[1], lo, 1);
        fourth = vaddq_f32(fourth, fifth);
        fourth = vmlaq_lane_f32(fourth, rhs.vectors[2], hi, 0);
        fourth = vmlaq_lane_f32(fourth, rhs.vectors[3], hi, 1);

        return FloatMatrix128x4(first, second, third, fourth);

    }

    inline FloatMatrix128x4 transpose(FloatMatrix128x4 matrix){
        float32x2_t loFirst = vget_low_f32(matrix.vectors[0]);
        float32x2_t loThird = vget_low_f32(matrix.vectors[2]);
        float32x4_t tmp1 = vcombine_f32(loFirst, loThird);

        float32x2_t loSecond = vget_low_f32(matrix.vectors[1]);
        float32x2_t loFourth = vget_low_f32(matrix.vectors[3]);
        float32x4_t tmp2 = vcombine_f32(loSecond, loFourth);
        float32x4_t row1 = vtrn1q_f32(tmp1, tmp2);

        loFirst = vrev64_f32(loFirst);
        loThird = vrev64_f32(loThird);
        tmp1 = vcombine_f32(loFirst, loThird);

        loSecond = vrev64_f32(loSecond);
        loFourth = vrev64_f32(loFourth);
        tmp2 = vcombine_f32(loSecond, loFourth);
        float32x4_t row2 = vtrn1q_f32(tmp1, tmp2);

        float32x2_t hiFirst = vget_high_f32(matrix.vectors[0]);
        float32x2_t hiThird = vget_high_f32(matrix.vectors[2]);
        tmp1 = vcombine_f32(hiFirst, hiThird);

        float32x2_t hiSecond = vget_high_f32(matrix.vectors[1]);
        float32x2_t hiFourth = vget_high_f32(matrix.vectors[3]);
        tmp2 = vcombine_f32(hiSecond, hiFourth);
        float32x4_t row3 = vtrn1q_f32(tmp1, tmp2);

        hiFirst = vrev64_f32(hiFirst);
        hiThird = vrev64_f32(hiThird);
        tmp1 = vcombine_f32(hiFirst, hiThird);

        hiSecond = vrev64_f32(hiSecond);
        hiFourth = vrev64_f32(hiFourth);
        tmp2 = vcombine_f32(hiSecond, hiFourth);
        float32x4_t row4 = vtrn1q_f32(tmp1, tmp2);
        return FloatMatrix128x4(row1, row2, row3, row4);
    }

    inline FloatMatrix128x4 inverse(FloatMatrix128x4 matrix, float* d){
        FloatMatrix128x4 t = transpose(matrix);
        float32x2_t lo = vget_low_f32(t.vectors[2]);
        float32x2_t hi = vget_high_f32(t.vectors[2]);

        float32x4_t tmp1 = vmulq_lane_f32(t.vectors[3], hi, 0);
        float32x4_t tmp2 = vmulq_lane_f32(t.vectors[3], hi, 1);
        float32x4_t tmp3 = vmulq_lane_f32(t.vectors[3], lo, 0);
        float32x4_t tmp4 = vmulq_lane_f32(t.vectors[3], lo, 1);

        // region row0
        float32x4_t _5444 = vcopyq_laneq_f32(t.vectors[1], 0, t.vectors[1], 1);
        _5444 = vcopyq_laneq_f32(_5444, 1, t.vectors[1], 0);
        _5444 = vcopyq_laneq_f32(_5444, 2, t.vectors[1], 0);
        _5444 = vcopyq_laneq_f32(_5444, 3, t.vectors[1], 0);

        float32x4_t tmp0 = vcopyq_laneq_f32(tmp1, 0, tmp1, 3);
        tmp0 = vcopyq_laneq_f32(tmp0, 1, tmp2, 2);
        tmp0 = vcopyq_laneq_f32(tmp0, 2, tmp4, 3);
        tmp0 = vcopyq_laneq_f32(tmp0, 3, tmp1, 1);
        tmp0 = vmulq_f32(tmp0, _5444);

        float32x4_t tmp6 = vcopyq_laneq_f32(tmp2, 0, tmp2, 2);
        tmp6 = vcopyq_laneq_f32(tmp6, 1, tmp1, 3);
        tmp6 = vcopyq_laneq_f32(tmp6, 2, tmp2, 1);
        tmp6 = vcopyq_laneq_f32(tmp6, 3, tmp4, 2);
        tmp6 = vmulq_f32(tmp6, _5444);

        float32x4_t _6655 = vcopyq_laneq_f32(t.vectors[1], 0, t.vectors[1], 2);
        _6655 = vcopyq_laneq_f32(_6655, 1, t.vectors[1], 2);
        _6655 = vcopyq_laneq_f32(_6655, 2, t.vectors[1], 1);
        _6655 = vcopyq_laneq_f32(_6655, 3, t.vectors[1], 1);

        float32x4_t tmp7 = vcopyq_laneq_f32(tmp2, 0, tmp2, 1);
        tmp7 = vcopyq_laneq_f32(tmp7, 1, tmp3, 3);
        tmp7 = vcopyq_laneq_f32(tmp7, 2, tmp2, 0);
        tmp7 = vcopyq_laneq_f32(tmp7, 3, tmp3, 2);
        tmp7 = vmulq_f32(_6655, tmp7);

        float32x4_t tmp8 = vcopyq_laneq_f32(tmp4, 0, tmp4, 3);
        tmp8 = vcopyq_laneq_f32(tmp8, 1, tmp2, 0);
        tmp8 = vcopyq_laneq_f32(tmp8, 2, tmp3, 3);
        tmp8 = vcopyq_laneq_f32(tmp8, 3, tmp1, 0);
        tmp8 = vmulq_f32(_6655, tmp8);

        float32x4_t _7776 = vcopyq_laneq_f32(t.vectors[1], 0, t.vectors[1], 3);
        _7776 = vcopyq_laneq_f32(_7776, 1, t.vectors[1], 3);
        _7776 = vcopyq_laneq_f32(_7776, 2, t.vectors[1], 3);
        _7776 = vcopyq_laneq_f32(_7776, 3, t.vectors[1], 2);

        float32x4_t tmp9 = vcopyq_laneq_f32(tmp4, 0, tmp4, 2);
        tmp9 = vcopyq_laneq_f32(tmp9, 1, tmp1, 0);
        tmp9 = vcopyq_laneq_f32(tmp9, 2, tmp3, 1);
        tmp9 = vcopyq_laneq_f32(tmp9, 3, tmp4, 0);
        tmp9 = vmulq_f32(_7776, tmp9);

        float32x4_t tmp10 = vcopyq_laneq_f32(tmp1, 0, tmp1, 1);
        tmp10 = vcopyq_laneq_f32(tmp10, 1, tmp3, 2);
        tmp10 = vcopyq_laneq_f32(tmp10, 2, tmp4, 0);
        tmp10 = vcopyq_laneq_f32(tmp10, 3, tmp3, 1);
        tmp10 = vmulq_f32(_7776, tmp10);

        float32x4_t row0 = vaddq_f32(tmp0, tmp7);
        row0 = vaddq_f32(row0, tmp9);
        row0 = vsubq_f32(row0, tmp6);
        row0 = vsubq_f32(row0, tmp8);
        row0 = vsubq_f32(row0, tmp10);
        // endregion

        // region row1
        float32x4_t _1000 = vcopyq_laneq_f32(t.vectors[0], 0, t.vectors[0], 1);
        _1000 = vcopyq_laneq_f32(_1000, 1, t.vectors[0], 0);
        _1000 = vcopyq_laneq_f32(_1000, 2, t.vectors[0], 0);
        _1000 = vcopyq_laneq_f32(_1000, 3, t.vectors[0], 0);

        tmp0 = vcopyq_laneq_f32(tmp2, 0, tmp2, 2);
        tmp0 = vcopyq_laneq_f32(tmp0, 1, tmp1, 3);
        tmp0 = vcopyq_laneq_f32(tmp0, 2, tmp2, 1);
        tmp0 = vcopyq_laneq_f32(tmp0, 3, tmp4, 2);
        tmp0 = vmulq_f32(tmp0, _1000);

        tmp6 = vcopyq_laneq_f32(tmp1, 0, tmp1, 3);
        tmp6 = vcopyq_laneq_f32(tmp6, 1, tmp2, 2);
        tmp6 = vcopyq_laneq_f32(tmp6, 2, tmp4, 3);
        tmp6 = vcopyq_laneq_f32(tmp6, 3, tmp1, 1);
        tmp6 = vmulq_f32(tmp6, _1000);

        float32x4_t _2211 = vcopyq_laneq_f32(t.vectors[0], 0, t.vectors[0], 2);
        _2211 = vcopyq_laneq_f32(_2211, 1, t.vectors[0], 2);
        _2211 = vcopyq_laneq_f32(_2211, 2, t.vectors[0], 1);
        _2211 = vcopyq_laneq_f32(_2211, 3, t.vectors[0], 1);

        tmp7 = vcopyq_laneq_f32(tmp4, 0, tmp4, 3);
        tmp7 = vcopyq_laneq_f32(tmp7, 1, tmp2, 0);
        tmp7 = vcopyq_laneq_f32(tmp7, 2, tmp3, 3);
        tmp7 = vcopyq_laneq_f32(tmp7, 3, tmp1, 0);
        tmp7 = vmulq_f32(tmp7, _2211);

        tmp8 = vcopyq_laneq_f32(tmp2, 0, tmp2, 1);
        tmp8 = vcopyq_laneq_f32(tmp8, 1, tmp3, 3);
        tmp8 = vcopyq_laneq_f32(tmp8, 2, tmp2, 0);
        tmp8 = vcopyq_laneq_f32(tmp8, 3, tmp3, 2);
        tmp8 = vmulq_f32(tmp8, _2211);

        float32x4_t _3332 = vcopyq_laneq_f32(t.vectors[0], 0, t.vectors[0], 3);
        _3332 = vcopyq_laneq_f32(_3332, 1, t.vectors[0], 3);
        _3332 = vcopyq_laneq_f32(_3332, 2, t.vectors[0], 3);
        _3332 = vcopyq_laneq_f32(_3332, 3, t.vectors[0], 2);

        tmp9 = vcopyq_laneq_f32(tmp9, 0, tmp1, 1);
        tmp9 = vcopyq_laneq_f32(tmp9, 1, tmp3, 2);
        tmp9 = vcopyq_laneq_f32(tmp9, 2, tmp4, 0);
        tmp9 = vcopyq_laneq_f32(tmp9, 3, tmp3, 1);
        tmp9 = vmulq_f32(tmp9, _3332);

        tmp10 = vcopyq_laneq_f32(tmp10, 0, tmp4, 2);
        tmp10 = vcopyq_laneq_f32(tmp10, 1, tmp1, 0);
        tmp10 = vcopyq_laneq_f32(tmp10, 2, tmp3, 1);
        tmp10 = vcopyq_laneq_f32(tmp10, 3, tmp4, 0);
        tmp10 = vmulq_f32(tmp10, _3332);

        float32x4_t row1 = vaddq_f32(tmp0, tmp7);
        row1 = vaddq_f32(row1, tmp9);
        row1 = vsubq_f32(row1, tmp6);
        row1 = vsubq_f32(row1, tmp8);
        row1 = vsubq_f32(row1, tmp10);

        // endregion

        lo = vget_low_f32(t.vectors[0]);
        hi = vget_high_f32(t.vectors[0]);

        tmp1 = vmulq_lane_f32(t.vectors[1], hi, 0);
        tmp2 = vmulq_lane_f32(t.vectors[1], hi, 1);
        tmp3 = vmulq_lane_f32(t.vectors[1], lo, 0);
        tmp4 = vmulq_lane_f32(t.vectors[1], lo, 1);

        // region row2

        _5444 = vcopyq_laneq_f32(t.vectors[3], 0, t.vectors[3], 1);
        _5444 = vcopyq_laneq_f32(_5444, 1, t.vectors[3], 0);
        _5444 = vcopyq_laneq_f32(_5444, 2, t.vectors[3], 0);
        _5444 = vcopyq_laneq_f32(_5444, 3, t.vectors[3], 0);

        tmp0 = vcopyq_laneq_f32(tmp1, 0, tmp1, 3);
        tmp0 = vcopyq_laneq_f32(tmp0, 1, tmp2, 2);
        tmp0 = vcopyq_laneq_f32(tmp0, 2, tmp4, 3);
        tmp0 = vcopyq_laneq_f32(tmp0, 3, tmp1, 1);
        tmp0 = vmulq_f32(tmp0, _5444);

        tmp6 = vcopyq_laneq_f32(tmp2, 0, tmp2, 2);
        tmp6 = vcopyq_laneq_f32(tmp6, 1, tmp1, 3);
        tmp6 = vcopyq_laneq_f32(tmp6, 2, tmp2, 1);
        tmp6 = vcopyq_laneq_f32(tmp6, 3, tmp4, 2);
        tmp6 = vmulq_f32(tmp6, _5444);

        _6655 = vcopyq_laneq_f32(t.vectors[3], 0, t.vectors[3], 2);
        _6655 = vcopyq_laneq_f32(_6655, 1, t.vectors[3], 2);
        _6655 = vcopyq_laneq_f32(_6655, 2, t.vectors[3], 1);
        _6655 = vcopyq_laneq_f32(_6655, 3, t.vectors[3], 1);

        tmp7 = vcopyq_laneq_f32(tmp2, 0, tmp2, 1);
        tmp7 = vcopyq_laneq_f32(tmp7, 1, tmp3, 3);
        tmp7 = vcopyq_laneq_f32(tmp7, 2, tmp2, 0);
        tmp7 = vcopyq_laneq_f32(tmp7, 3, tmp3, 2);
        tmp7 = vmulq_f32(_6655, tmp7);

        tmp8 = vcopyq_laneq_f32(tmp4, 0, tmp4, 3);
        tmp8 = vcopyq_laneq_f32(tmp8, 1, tmp2, 0);
        tmp8 = vcopyq_laneq_f32(tmp8, 2, tmp3, 3);
        tmp8 = vcopyq_laneq_f32(tmp8, 3, tmp1, 0);
        tmp8 = vmulq_f32(_6655, tmp8);

        _7776 = vcopyq_laneq_f32(t.vectors[3], 0, t.vectors[3], 3);
        _7776 = vcopyq_laneq_f32(_7776, 1, t.vectors[3], 3);
        _7776 = vcopyq_laneq_f32(_7776, 2, t.vectors[3], 3);
        _7776 = vcopyq_laneq_f32(_7776, 3, t.vectors[3], 2);

        tmp9 = vcopyq_laneq_f32(tmp4, 0, tmp4, 2);
        tmp9 = vcopyq_laneq_f32(tmp9, 1, tmp1, 0);
        tmp9 = vcopyq_laneq_f32(tmp9, 2, tmp3, 1);
        tmp9 = vcopyq_laneq_f32(tmp9, 3, tmp4, 0);
        tmp9 = vmulq_f32(_7776, tmp9);

        tmp10 = vcopyq_laneq_f32(tmp1, 0, tmp1, 1);
        tmp10 = vcopyq_laneq_f32(tmp10, 1, tmp3, 2);
        tmp10 = vcopyq_laneq_f32(tmp10, 2, tmp4, 0);
        tmp10 = vcopyq_laneq_f32(tmp10, 3, tmp3, 1);
        tmp10 = vmulq_f32(_7776, tmp10);

        float32x4_t row2 = vaddq_f32(tmp0, tmp7);
        row2 = vaddq_f32(row2, tmp9);
        row2 = vsubq_f32(row2, tmp6);
        row2 = vsubq_f32(row2, tmp8);
        row2 = vsubq_f32(row2, tmp10);

        // endregion

        // region row3
        float32x4_t _2312 = vcopyq_laneq_f32(t.vectors[2], 0, t.vectors[2], 2);
        _2312 = vcopyq_laneq_f32(_2312, 1, t.vectors[2], 3);
        _2312 = vcopyq_laneq_f32(_2312, 2, t.vectors[2], 1);
        _2312 = vcopyq_laneq_f32(_2312, 3, t.vectors[2], 2);

        tmp0 = vcopyq_laneq_f32(tmp4, 0, tmp4, 3);
        tmp0 = vcopyq_laneq_f32(tmp0, 1, tmp3, 2);
        tmp0 = vcopyq_laneq_f32(tmp0, 2, tmp3, 3);
        tmp0 = vcopyq_laneq_f32(tmp0, 3, tmp3, 1);
        tmp0 = vmulq_f32(_2312, tmp0);

        float32x4_t _3231 = vcopyq_laneq_f32(t.vectors[2], 0, t.vectors[2], 3);
        _3231 = vcopyq_laneq_f32(_3231, 1, t.vectors[2], 2);
        _3231 = vcopyq_laneq_f32(_3231, 2, t.vectors[2], 3);
        _3231 = vcopyq_laneq_f32(_3231, 3, t.vectors[2], 1);

        tmp6 = vcopyq_laneq_f32(tmp4, 0, tmp4, 2);
        tmp6 = vcopyq_laneq_f32(tmp6, 1, tmp3, 3);
        tmp6 = vcopyq_laneq_f32(tmp6, 2, tmp3, 1);
        tmp6 = vcopyq_laneq_f32(tmp6, 3, tmp3, 2);
        tmp6 = vmulq_f32(tmp6, _3231);

        float32x4_t _3030 = vcopyq_laneq_f32(t.vectors[2], 0, t.vectors[2], 3);
        _3030 = vcopyq_laneq_f32(_3030, 1, t.vectors[2], 0);
        _3030 = vcopyq_laneq_f32(_3030, 2, t.vectors[2], 3);
        _3030 = vcopyq_laneq_f32(_3030, 3, t.vectors[2], 0);

        tmp7 = vcopyq_laneq_f32(tmp0, 0, tmp1, 1);
        tmp7 = vcopyq_laneq_f32(tmp7, 1, tmp1, 3);
        tmp7 = vcopyq_laneq_f32(tmp7, 2, tmp4, 0);
        tmp7 = vcopyq_laneq_f32(tmp7, 3, tmp4, 2);
        tmp7 = vmulq_f32(tmp7, _3030);

        float32x4_t _1302 = vcopyq_laneq_f32(t.vectors[2], 0, t.vectors[2], 1);
        _1302 = vcopyq_laneq_f32(_1302, 1, t.vectors[2], 3);
        _1302 = vcopyq_laneq_f32(_1302, 2, t.vectors[2], 0);
        _1302 = vcopyq_laneq_f32(_1302, 3, t.vectors[2], 2);

        tmp8 = vcopyq_laneq_f32(tmp8, 0, tmp1, 3);
        tmp8 = vcopyq_laneq_f32(tmp8, 1, tmp1, 0);
        tmp8 = vcopyq_laneq_f32(tmp8, 2, tmp4, 3);
        tmp8 = vcopyq_laneq_f32(tmp8, 3, tmp4, 0);
        tmp8 = vmulq_f32(tmp8, _1302);

        float32x4_t _1201 = vcopyq_laneq_f32(t.vectors[2], 0, t.vectors[2], 1);
        _1201 = vcopyq_laneq_f32(_1201, 1, t.vectors[2], 2);
        _1201 = vcopyq_laneq_f32(_1201, 2, t.vectors[2], 0);
        _1201 = vcopyq_laneq_f32(_1201, 3, t.vectors[2], 1);

        tmp9 = vcopyq_laneq_f32(tmp2, 0, tmp2, 2);
        tmp9 = vcopyq_laneq_f32(tmp9, 1, tmp2, 0);
        tmp9 = vcopyq_laneq_f32(tmp9, 2, tmp2, 1);
        tmp9 = vcopyq_laneq_f32(tmp9, 3, tmp1, 0);
        tmp9 = vmulq_f32(tmp9, _1201);

        float32x4_t _2010 = vcopyq_laneq_f32(t.vectors[2], 0, t.vectors[2], 2);
        _2010 = vcopyq_laneq_f32(_2010, 1, t.vectors[2], 0);
        _2010 = vcopyq_laneq_f32(_2010, 2, t.vectors[2], 1);
        _2010 = vcopyq_laneq_f32(_2010, 3, t.vectors[2], 0);

        tmp10 = vcopyq_laneq_f32(tmp2, 0, tmp2, 1);
        tmp10 = vcopyq_laneq_f32(tmp10, 1, tmp2, 2);
        tmp10 = vcopyq_laneq_f32(tmp10, 2, tmp2, 0);
        tmp10 = vcopyq_laneq_f32(tmp10, 3, tmp1, 1);
        tmp10 = vmulq_f32(tmp10, _2010);

        float32x4_t row3 = vaddq_f32(tmp0, tmp7);
        row3 = vaddq_f32(row3, tmp9);
        row3 = vsubq_f32(row3, tmp6);
        row3 = vsubq_f32(row3, tmp8);
        row3 = vsubq_f32(row3, tmp10);

        // endregion


        // region get determinant
        tmp0 = vmulq_f32(row0, t.vectors[0]);
        lo = vget_low_f32(tmp0);
        hi = vget_high_f32(tmp0);
        float32x2_t tmpd = vadd_f32(lo, hi);
        tmpd = vadd_f32(vrev64_f32(tmpd), tmpd);
        float32x4_t determ = vcombine_f32(tmpd, tmpd);
        float32x4_t invDet = vrecpeq_f32(determ);

        // endregion

        // region multiply determinant

        row0 = vmulq_f32(row0, invDet);
        row1 = vmulq_f32(row1, invDet);
        row2 = vmulq_f32(row2, invDet);
        row3 = vmulq_f32(row3, invDet);

        *d = GET_LANE_VECTOR(determ, 0);
        return FloatMatrix128x4(row0, row1, row2, row3);
    }

    inline float32x4_t determinant(FloatMatrix128x4 matrix){
        FloatMatrix128x4 t = transpose(matrix);
        float32x2_t lo = vget_low_f32(t.vectors[2]);
        float32x2_t hi = vget_high_f32(t.vectors[2]);

        float32x4_t tmp1 = vmulq_lane_f32(t.vectors[3], hi, 0);
        float32x4_t tmp2 = vmulq_lane_f32(t.vectors[3], hi, 1);
        float32x4_t tmp3 = vmulq_lane_f32(t.vectors[3], lo, 0);
        float32x4_t tmp4 = vmulq_lane_f32(t.vectors[3], lo, 1);

        // region row0
        float32x4_t _5444 = vcopyq_laneq_f32(t.vectors[1], 0, t.vectors[1], 1);
        _5444 = vcopyq_laneq_f32(_5444, 1, t.vectors[1], 0);
        _5444 = vcopyq_laneq_f32(_5444, 2, t.vectors[1], 0);
        _5444 = vcopyq_laneq_f32(_5444, 3, t.vectors[1], 0);

        float32x4_t tmp0 = vcopyq_laneq_f32(tmp1, 0, tmp1, 3);
        tmp0 = vcopyq_laneq_f32(tmp0, 1, tmp2, 2);
        tmp0 = vcopyq_laneq_f32(tmp0, 2, tmp4, 3);
        tmp0 = vcopyq_laneq_f32(tmp0, 3, tmp1, 1);
        tmp0 = vmulq_f32(tmp0, _5444);

        float32x4_t tmp6 = vcopyq_laneq_f32(tmp2, 0, tmp2, 2);
        tmp6 = vcopyq_laneq_f32(tmp6, 1, tmp1, 3);
        tmp6 = vcopyq_laneq_f32(tmp6, 2, tmp2, 1);
        tmp6 = vcopyq_laneq_f32(tmp6, 3, tmp4, 2);
        tmp6 = vmulq_f32(tmp6, _5444);

        float32x4_t _6655 = vcopyq_laneq_f32(t.vectors[1], 0, t.vectors[1], 2);
        _6655 = vcopyq_laneq_f32(_6655, 1, t.vectors[1], 2);
        _6655 = vcopyq_laneq_f32(_6655, 2, t.vectors[1], 1);
        _6655 = vcopyq_laneq_f32(_6655, 3, t.vectors[1], 1);

        float32x4_t tmp7 = vcopyq_laneq_f32(tmp2, 0, tmp2, 1);
        tmp7 = vcopyq_laneq_f32(tmp7, 1, tmp3, 3);
        tmp7 = vcopyq_laneq_f32(tmp7, 2, tmp2, 0);
        tmp7 = vcopyq_laneq_f32(tmp7, 3, tmp3, 2);
        tmp7 = vmulq_f32(_6655, tmp7);

        float32x4_t tmp8 = vcopyq_laneq_f32(tmp4, 0, tmp4, 3);
        tmp8 = vcopyq_laneq_f32(tmp8, 1, tmp2, 0);
        tmp8 = vcopyq_laneq_f32(tmp8, 2, tmp3, 3);
        tmp8 = vcopyq_laneq_f32(tmp8, 3, tmp1, 0);
        tmp8 = vmulq_f32(_6655, tmp8);

        float32x4_t _7776 = vcopyq_laneq_f32(t.vectors[1], 0, t.vectors[1], 3);
        _7776 = vcopyq_laneq_f32(_7776, 1, t.vectors[1], 3);
        _7776 = vcopyq_laneq_f32(_7776, 2, t.vectors[1], 3);
        _7776 = vcopyq_laneq_f32(_7776, 3, t.vectors[1], 2);

        float32x4_t tmp9 = vcopyq_laneq_f32(tmp4, 0, tmp4, 2);
        tmp9 = vcopyq_laneq_f32(tmp9, 1, tmp1, 0);
        tmp9 = vcopyq_laneq_f32(tmp9, 2, tmp3, 1);
        tmp9 = vcopyq_laneq_f32(tmp9, 3, tmp4, 0);
        tmp9 = vmulq_f32(_7776, tmp9);

        float32x4_t tmp10 = vcopyq_laneq_f32(tmp1, 0, tmp1, 1);
        tmp10 = vcopyq_laneq_f32(tmp10, 1, tmp3, 2);
        tmp10 = vcopyq_laneq_f32(tmp10, 2, tmp4, 0);
        tmp10 = vcopyq_laneq_f32(tmp10, 3, tmp3, 1);
        tmp10 = vmulq_f32(_7776, tmp10);

        float32x4_t row0 = vaddq_f32(tmp0, tmp7);
        row0 = vaddq_f32(row0, tmp9);
        row0 = vsubq_f32(row0, tmp6);
        row0 = vsubq_f32(row0, tmp8);
        row0 = vsubq_f32(row0, tmp10);

        tmp0 = vmulq_f32(row0, t.vectors[0]);
        lo = vget_low_f32(tmp0);
        hi = vget_high_f32(tmp0);
        float32x2_t tmpd = vadd_f32(lo, hi);
        tmpd = vadd_f32(vrev64_f32(tmpd), tmpd);
        return vcombine_f32(tmpd, tmpd);
    }

    // lhs vector rhs matrix
    inline float32x4_t matrixVectorMul(float32x4_t vector, FloatMatrix128x4 matrix){
        float32x4_t v0 = vcopyq_laneq_f32(vector, 0, vector, 0);
        v0 = vcopyq_laneq_f32(v0, 1, vector, 0);
        v0 = vcopyq_laneq_f32(v0, 2, vector, 0);
        v0 = vcopyq_laneq_f32(v0, 3, vector, 0);

        float32x4_t v1 = vcopyq_laneq_f32(vector, 0, vector, 1);
        v1 = vcopyq_laneq_f32(v1, 1, vector, 1);
        v1 = vcopyq_laneq_f32(v1, 2, vector, 1);
        v1 = vcopyq_laneq_f32(v1, 3, vector, 1);

        float32x4_t v2 = vcopyq_laneq_f32(vector, 0, vector, 2);
        v2 = vcopyq_laneq_f32(v2, 1, vector, 2);
        v2 = vcopyq_laneq_f32(v2, 2, vector, 2);
        v2 = vcopyq_laneq_f32(v2, 3, vector, 2);

        float32x4_t v3 = vcopyq_laneq_f32(vector, 0, vector, 3);
        v3 = vcopyq_laneq_f32(v3, 1, vector, 3);
        v3 = vcopyq_laneq_f32(v3, 2, vector, 3);
        v3 = vcopyq_laneq_f32(v3, 3, vector, 3);

        float32x4_t v = vmulq_f32(v0, matrix.vectors[0]);
        v = vmlaq_f32(v, v1, matrix.vectors[1]);
        v = vmlaq_f32(v, v2, matrix.vectors[2]);
        v = vmlaq_f32(v, v3, matrix.vectors[3]);
        return v;
    }

    // lhs matrix rhs vector
    inline float32x4_t matrixVectorMul(FloatMatrix128x4 matrix, float32x4_t vector){
        FloatMatrix128x4 t = transpose(matrix);

        float32x4_t v0 = vcopyq_laneq_f32(vector, 0, vector, 0);
        v0 = vcopyq_laneq_f32(v0, 1, vector, 0);
        v0 = vcopyq_laneq_f32(v0, 2, vector, 0);
        v0 = vcopyq_laneq_f32(v0, 3, vector, 0);

        float32x4_t v1 = vcopyq_laneq_f32(vector, 0, vector, 1);
        v1 = vcopyq_laneq_f32(v1, 1, vector, 1);
        v1 = vcopyq_laneq_f32(v1, 2, vector, 1);
        v1 = vcopyq_laneq_f32(v1, 3, vector, 1);

        float32x4_t v2 = vcopyq_laneq_f32(vector, 0, vector, 2);
        v2 = vcopyq_laneq_f32(v2, 1, vector, 2);
        v2 = vcopyq_laneq_f32(v2, 2, vector, 2);
        v2 = vcopyq_laneq_f32(v2, 3, vector, 2);

        float32x4_t v3 = vcopyq_laneq_f32(vector, 0, vector, 3);
        v3 = vcopyq_laneq_f32(v3, 1, vector, 3);
        v3 = vcopyq_laneq_f32(v3, 2, vector, 3);
        v3 = vcopyq_laneq_f32(v3, 3, vector, 3);

        float32x4_t v = vmulq_f32(v0, t.vectors[0]);
        v = vmlaq_f32(v, v1, t.vectors[1]);
        v = vmlaq_f32(v, v2, t.vectors[2]);
        v = vmlaq_f32(v, v3, t.vectors[3]);
        return v;
    }



#endif
}

#endif //ODINMATH_MATRIXINTRIN_H
