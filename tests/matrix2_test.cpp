//
// Created by Jason Fedorowich on 2024-04-21.
//


#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;

TEST(TestMatrix2, TestConstructor) {
    Matrix2<float> m1;
    EXPECT_EQ(0.f, m1(0, 0));
    EXPECT_EQ(0.f, m1(1, 1));
    Matrix2<double> m2(1.0, 2.0,
                       5.0, 6.0);
    EXPECT_EQ(6.0, m2(1, 1));
    EXPECT_THROW(m2(4, 4), OdinMath::InvalidArgument);
}

TEST(TestMatrix2, TestIdentity) {
    Matrix2<float> m = Matrix2<float>::identity();
    EXPECT_EQ(1.f, m(0, 0));
    EXPECT_EQ(1.f, m(1, 1));
}

TEST(TestMatrix2, TestDeterminant) {
    Matrix2<float> m = Matrix2<float>(1, 1,
                                      5, 5);
    float d = m.det();
    EXPECT_LE(d, 1e-12);

    Matrix2<float> m1 = Matrix2<float>(1, 2,
                                       5, 12);

    float d1 = m1.det();
    EXPECT_EQ(2.0f, d1);

    Matrix2<float> m2 = Matrix2<float>(1, 2,
                                       5, 6);
    float d2 = m2.det();
    EXPECT_EQ(-4.f, d2);
}


TEST(TestMatrix2, TestTranspose) {
    Matrix2<float> m = Matrix2<float>(1, 2,
                                      5, 6);

    Matrix2<float> expected = Matrix2<float>(1, 5,
                                             2, 6);
    Matrix2<float> t = m.transpose();
    EXPECT_EQ(expected, t);
}


TEST(TestMatrix2, TestInversion) {
    Matrix2<float> m1 = Matrix2<float>(1, 2,
                                       5, 6);
    Matrix2<float> inv;
    float det;
    bool res = m1.inverse(inv, 0.00000001, &det);
    float dd = m1.det();
    EXPECT_TRUE(res);
    Matrix2<float> expected = Matrix2<float>( -1.5000,   0.5000, 1.2500, -0.2500);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            expected(i, j) = round(expected(i, j));
            inv(i, j) = round(inv(i, j));
        }
    }

    EXPECT_EQ(expected, inv);
    EXPECT_EQ(-4.0f, det);
}

TEST(TestMatrix2, TestArithmetic) {
    Matrix2<float> m = Matrix2<float>(1, 2,
                                      5, 6);
    Matrix2<float> T = m.transpose();
    Matrix2<float> R = m + T;
    Matrix2<float> expAdd = Matrix2<float>(
            2, 7,
            7, 12);
    EXPECT_EQ(expAdd, R);

    Matrix2<float> expMul = Matrix2<float>(
            5, 17,
            17, 61);

    Matrix2<float> RR = m * T;
    EXPECT_EQ(expMul, RR);

    Matrix2<float> expSub = Matrix2<float>(
            0, -3,
            3, 0);

    Matrix2<float> RSub = m - T;
    EXPECT_EQ(expSub, RSub);

    Matrix2<float> A = 100.f * m;
    Matrix2<float> expectC = Matrix2<float>(
            100, 200,
            500, 600);
    EXPECT_EQ(expectC, A);

}


TEST(TestMatrix2, TestVectorMult) {
    Matrix2<double> m = Matrix2<double>(1, 2,
                                        5, 6);
    Vector2<double> v = {1, 2};
    Vector2<double> expected = {
            5,
            17};
    Vector2<double> R = m * v;
    EXPECT_EQ(expected, R);

    Vector2<double> expL = {11, 14};
    Vector2<double> RR = v * m;
    EXPECT_EQ(expL, RR);
}

