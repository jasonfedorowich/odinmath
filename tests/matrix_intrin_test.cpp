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

TEST(MatrixIntrinTestSuite, MatrixVectorMult){
    Matrix4<float> m1 = Matrix4<float>( 1,    2,  10,    4,
                                        5,    6,    7,    8,
                                        9,   10,   11,   12,
                                        10,   14,   15,   12);

    FloatMatrix128x4 floatMatrix128X4(m1);
    float arr[4] = {1, 2, 3, 4};
    float32x4_t v = load4(arr);
    float32x4_t r = matrixVectorMul(v, floatMatrix128X4);
    float res[4];
    store4(res, r);
    float expected[4] = {78,   100,   117,   104};
    EXPECT_EQ(expected[0], res[0]);
    EXPECT_EQ(expected[1], res[1]);
    EXPECT_EQ(expected[2], res[2]);
    EXPECT_EQ(expected[3], res[3]);

    r = matrixVectorMul(floatMatrix128X4, v);
    store4(res, r);
    float expected2[4] = {51, 70, 110, 131};
    EXPECT_EQ(expected2[0], res[0]);
    EXPECT_EQ(expected2[1], res[1]);
    EXPECT_EQ(expected2[2], res[2]);
    EXPECT_EQ(expected2[3], res[3]);
}


TEST(MatrixIntrinTestSuite, TestMatrixEquality){
    Matrix4<float> m1 = Matrix4<float>( 1,    2,  10,    4,
                                        5,    6,    7,    8,
                                        9,   10,   11,   12,
                                        10,   14,   15,   12);
    Matrix4<float> m2 = Matrix4<float>( 1,    23,  10,    4,
                                        5,    6,    7,    8,
                                        9,   10,   11,   12,
                                        10,   14,   15,   12);

    FloatMatrix128x4 floatMatrix128X4(m1);
    FloatMatrix128x4 floatMatrix128X41(m1);
    FloatMatrix128x4 floatMatrix128X42(m2);
    EXPECT_EQ(floatMatrix128X41, floatMatrix128X4);
    EXPECT_FALSE(floatMatrix128X4 == floatMatrix128X42);
}

TEST(Matrix4FloatTestSuite, TestArithmetic){
    Matrix4Float matrix4Float1(1,    2,  10,    4,
                              5,    6,    7,    8,
                              9,   10,   11,   12,
                              10,   14,   15,   12);

    Matrix4Float matrix4Float2(1,    23,  10,    4,
                               5,    6,    7,    8,
                               9,   10,   11,   12,
                               10,   14,   15,   12);
    Matrix4Float res = matrix4Float1 + matrix4Float2;
    Matrix4Float expAdd(2, 25, 20, 8,
                        10, 12, 14, 16,
                        18, 20, 22, 24,
                        20, 28, 30, 24);
    EXPECT_EQ(expAdd, res);

    Matrix4Float resMul = matrix4Float1 * matrix4Float2;
    Matrix4Float expMul(141,   191,   194,   188,
    178,   333,   289,   248,
    278,   545,   461,   392,
    335,   632,   543,   476);
    EXPECT_EQ(expMul, resMul);

    Matrix4Float resSub = matrix4Float1 - matrix4Float2;
    Matrix4Float expSub(0, -21, 0, 0,
                        0, 0, 0, 0,
                        0, 0, 0, 0,
                        0, 0, 0, 0);
    EXPECT_EQ(expSub, resSub);

    Vector4Float v(1, 2, 3, 4);
    Vector4Float resL = v * matrix4Float1;
    Vector4Float expL(78, 100, 117, 104);
    EXPECT_EQ(expL, resL);

    Vector4Float resR = matrix4Float1 * v;
    Vector4Float expR(51, 70, 110, 131);
    EXPECT_EQ(expR, resR);

}

TEST(Matrix4FloatTestSuit, TestInverseAndDeter){
    Matrix4Float matrix4Float2(1,    23,  10,    4,
                               5,    6,    7,    8,
                               9,   10,   11,   12,
                               10,   14,   15,   12);
    Matrix4Float inv;
    float d = 0;
    bool res = matrix4Float2.inverse(inv, 0.001, &d);
    EXPECT_TRUE(res);
    Matrix4Float expI(-0.024845,  -0.993789,   0.714286, -0.043478,
                        0.068323,  -0.267081,   0.285714,  -0.130435,
                        -0.062112,   0.515528,  -0.714286,   0.391304,
                        0.018634,   0.495342,  -0.035714,  -0.217391);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            EXPECT_NEAR(expI.get(i, j), inv.get(i, j), 0.01);
        }
    }
    EXPECT_NEAR(-644.0, d, 0.001);
    d = matrix4Float2.det();
    EXPECT_EQ(-644.0, d);

    Matrix4Float t = matrix4Float2.transpose();
    Matrix4Float expT(1, 5, 9, 10,
                      23, 6, 10, 14,
                      10, 7, 11, 15,
                      4, 8, 12, 12);
    EXPECT_EQ(expT, t);

}


TEST(Matrix3FloatTestSuite, TestArithmetic){
    Matrix3Float matrix3Float1(1,    2,  10,
                               5,    6,    7,
                               9,   10,   11);

    Matrix3Float matrix3Float2(1,    23,  10,
                               5,    6,    7,
                               9,   10,   11);
    Matrix3Float res = matrix3Float1 + matrix3Float2;
    Matrix3Float expAdd(2, 25, 20,
                        10, 12, 14,
                        18, 20, 22);
    EXPECT_EQ(expAdd, res);
    Matrix3Float t = expAdd;

    Matrix3Float resMul = matrix3Float1 * matrix3Float2;
    Matrix3Float expMul(101,   135,   134,
                        98,   221,   169,
                        158,   377,   281);
    EXPECT_EQ(expMul, resMul);

    Matrix3Float resSub = matrix3Float1 - matrix3Float2;
    Matrix3Float expSub(0, -21, 0,
                        0, 0, 0,
                        0, 0, 0);
    EXPECT_EQ(expSub, resSub);

    Vector3Float v(1, 2, 3);
    Vector3Float resL = v * matrix3Float1;
    Vector3Float expL(38,   44,   57);
    EXPECT_EQ(expL, resL);

    Vector3Float resR = matrix3Float1 * v;
    Vector3Float expR(35, 38, 62);
    EXPECT_EQ(expR, resR);

}

TEST(Matrix3FloatTestSuit, TestInverseAndDeter){
    Matrix3Float matrix3Float2(1,    23,  10,
                               5,    6,    7,
                               9,   10,   11);
    Matrix3Float inv;
    float d = 0;
    bool res = matrix3Float2.inverse(inv, 0.001, &d);
    EXPECT_TRUE(res);
    Matrix3Float expI(-0.028571, -1.092857,   0.721429,
                      0.057143,  -0.564286,   0.307143,
                        -0.028571,   1.407143,  -0.778571);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            EXPECT_NEAR(expI.get(i, j), inv.get(i, j), 0.01);
        }
    }
    EXPECT_NEAR(140.0, d, 0.001);
    d = matrix3Float2.det();
    EXPECT_EQ(140.0, d);

    Matrix3Float t = matrix3Float2.transpose();
    Matrix3Float expT(1, 5, 9,
                      23, 6, 10,
                      10, 7, 11);
    EXPECT_EQ(expT, t);

}

TEST(Matrix2FloatTestSuite, TestArithmetic){
    Matrix2Float matrix2Float1(1,    2,
                               5,    6);

    Matrix2Float matrix2Float2(1,    23,
                               5,    6);
    Matrix2Float res = matrix2Float1 + matrix2Float2;
    Matrix2Float expAdd(2, 25,
                        10, 12);
    EXPECT_EQ(expAdd, res);
    Matrix2Float t = expAdd;

    Matrix2Float resMul = matrix2Float1 * matrix2Float2;
    Matrix2Float expMul(11,   35,
                        35,   151);
    EXPECT_EQ(expMul, resMul);

    Matrix2Float resSub = matrix2Float1 - matrix2Float2;
    Matrix2Float expSub(0, -21,
                        0, 0);
    EXPECT_EQ(expSub, resSub);

    Vector2Float v(1, 2);
    Vector2Float resL = v * matrix2Float1;
    Vector2Float expL(11,   14);
    EXPECT_EQ(expL, resL);

    Vector2Float resR = matrix2Float1 * v;
    Vector2Float expR(5, 17);
    EXPECT_EQ(expR, resR);

}

TEST(Matrix2FloatTestSuit, TestInverseAndDeter){
    Matrix2Float matrix2Float2(1,    23,
                               5,    6);
    Matrix2Float inv;
    float d = 0;
    bool res = matrix2Float2.inverse(inv, 0.001, &d);
    EXPECT_TRUE(res);
    Matrix2Float expI(-5.5046e-02,   2.1101e-01,
                      4.5872e-02, -9.1743e-03);
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            EXPECT_NEAR(expI.get(i, j), inv.get(i, j), 0.01);
        }
    }
    EXPECT_NEAR(-109.0, d, 0.001);
    d = matrix2Float2.det();
    EXPECT_EQ(-109.0, d);

    Matrix2Float t = matrix2Float2.transpose();
    Matrix2Float expT(1, 5,
                      23, 6);
    EXPECT_EQ(expT, t);

}
#endif