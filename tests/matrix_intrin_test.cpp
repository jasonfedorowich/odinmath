//
// Created by Jason Fedorowich on 2024-04-25.
//


#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;

#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))


TEST(MatrixIntrinTestSuite, LoadAndStore) {
    float mat[4][4] ={
            {1, 1, 1, 1},
            {2, 2, 2, 2},
            {3, 3, 3, 3},
            {4, 4, 4, 4}};
    FloatMatrix128x4 floatMatrix128X4(mat);

    Matrix<4, 4, float> output;
    store4(&output, floatMatrix128X4);
    Matrix<4, 4, float> expected(mat);

    EXPECT_EQ(expected, output);
}

TEST(MatrixIntrinTestSuite, Add) {
    float mat[3][3] ={
            {1, 1, 1},
            {2, 2, 2},
            {3, 3, 3}};

    FloatMatrix128x4 rhs(mat);
    FloatMatrix128x4 lhs(mat);
    FloatMatrix128x4 res = add(lhs, rhs);
    Matrix<3, 3, float> output;
    store3(&output, res);

    float exp[3][3] ={
            {2, 2, 2},
            {4, 4, 4},
            {6, 6, 6}};
    Matrix<3, 3, float> expected(exp);

    EXPECT_EQ(expected, output);

}


TEST(MatrixIntrinTestSuite, Sub) {
    float mat[3][3] = {
            {1, 1, 1},
            {2, 2, 2},
            {3, 3, 3}};

    FloatMatrix128x4 rhs(mat);
    FloatMatrix128x4 lhs(mat);
    FloatMatrix128x4 res = sub(lhs, rhs);
    Matrix<3, 3, float> output;
    store3(&output, res);

    float exp[3][3] ={
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}};
    Matrix<3, 3, float> expected(exp);

    EXPECT_EQ(expected, output);
}

TEST(MatrixIntrinTestSuite, Mul) {
    float mat[4][4] ={
            {1, 1, 1, 1},
            {2, 2, 2, 2},
            {3, 3, 3, 3},
            {4, 4, 4, 4}};

    FloatMatrix128x4 floatMatrix128X4(mat);
    FloatMatrix128x4 res = mul(floatMatrix128X4, floatMatrix128X4);

    Matrix<4, 4, float> output;
    store4(&output, res);
    float exp[4][4] = {{10, 10, 10, 10},
                       {20, 20, 20, 20},
                       {30, 30, 30, 30},
                       {40, 40, 40, 40}};
    Matrix<4, 4, float> expected(exp);
    EXPECT_EQ(expected, output);

    float mat1[3][3] = {{1, 2, 3},
                  {6, 7, 8},
                  {10, 11, 14}};

    FloatMatrix128x4 mat2(mat1);
    res = mul(mat2, mat2);
    Matrix<3, 3, float> res1;
    store3(&res1, res);

    float exp1[3][3] = {{ 43,   49,   61},
                        {128,   149,   186},
                        {216,   251,   314}};
    Matrix<3, 3, float> exp2(exp1);
    EXPECT_EQ(exp2, res1);
}


TEST(MatrixIntrinTestSuite, Transpose) {
    float mat[4][4] ={
            {1, 2, 3, 4},
            {2, 2, 2, 2},
            {3, 3, 3, 3},
            {4, 4, 4, 4}};

    FloatMatrix128x4 floatMatrix128X4(mat);
    FloatMatrix128x4 transpose = OdinMath::transpose(floatMatrix128X4);

    Matrix<4, 4, float> output;
    store4(&output, transpose);
    float exp[4][4] = {{1, 2, 3, 4},
                       {2, 2, 3, 4},
                       {3, 2, 3, 4},
                       {4, 2, 3, 4}};
    Matrix<4, 4, float> expected(exp);
    EXPECT_EQ(expected, output);

}



TEST(MatrixIntrinTestSuite, Inverse) {
    Matrix4<float> m1 = Matrix4<float>( 1,    2,  10,    4,
    5,    6,    7,    8,
    9,   10,   11,   12,
    10,   14,   15,   12);

    FloatMatrix128x4 floatMatrix128X4(m1);
    float d;
    FloatMatrix128x4 inv = OdinMath::inverse(floatMatrix128X4, &d);

    Matrix<4, 4, float> output;
    store4(&output, inv);
    float exp[4][4] = {{ 0.0571,  -1.3143,   1.0571, -0.2000},
                       {-0.1571,  0.6143,  -0.6571,   0.3000},
                       {0.1429,  -0.2857,  0.1429,        0},
                       {-0.0429,   0.7357, -0.2929, -0.1000}};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_NEAR(exp[i][j], output(i, j), 0.01);
        }
    }

    Matrix<4, 4, float> expected(exp);
    EXPECT_NEAR(280.0, d, 0.01);

}

TEST(MatrixIntrinTestSuite, Determinant){
    Matrix4<float> m1 = Matrix4<float>( 1,    2,  10,    4,
                                        5,    6,    7,    8,
                                        9,   10,   11,   12,
                                        10,   14,   15,   12);

    FloatMatrix128x4 floatMatrix128X4(m1);
    float32x4_t d = OdinMath::determinant(floatMatrix128X4);
    float res[4];
    store4(res, d);

    EXPECT_NEAR(280.0, res[0], 0.01);
}
#endif