//
// Created by Jason Fedorowich on 2024-03-19.
//

#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;

TEST(TestMatrix4, TestConstructor) {
    Matrix4<float> m1;
    EXPECT_EQ(0.f, m1(0, 0));
    EXPECT_EQ(0.f, m1(1, 1));
    Matrix4<double> m2(1.0, 2.0, 3.0, 4.0,
                       5.0, 6.0, 7.0, 8.0,
                       9.0, 10.0, 11.0, 12.0,
                       1.0, 2.0, 3.0, 4.0);
    EXPECT_EQ(4.0, m2(3, 3));
    EXPECT_THROW(m2(4, 4), OdinMath::InvalidArgument);
}

TEST(TestMatrix4, TestIdentity) {
    Matrix4<float> m = Matrix4<float>::identity();
    EXPECT_EQ(1.f, m(0, 0));
    EXPECT_EQ(1.f, m(1, 1));
    EXPECT_EQ(1.f, m(2, 2));
    EXPECT_EQ(1.f, m(3, 3));

}

TEST(TestMatrix4, TestDeterminant) {
    Matrix4<float> m = Matrix4<float>(1, 2, 3, 4,
                                      5, 6, 7, 8,
                                      9, 10, 11, 12,
                                      13, 14, 15, 16);
    float d = m.det();
    EXPECT_LE(d, 1e-12);

    Matrix4<float> m1 = Matrix4<float>(1, 2, 10, 4,
                                       5, 6, 7, 8,
                                       9, 10, 11, 12,
                                       0, 14, 15, 0);

    float d1 = m1.det();
    EXPECT_EQ(1176.0f, d1);

    Matrix4<float> m2 = Matrix4<float>(1, 2, 10, 4,
                                       5, 6, 7, 8,
                                       9, 10, 11, 12,
                                       10, 14, 15, 12);
    float d2 = m2.det();
    EXPECT_EQ(280.f, d2);
}


TEST(TestMatrix4, TestTranspose) {
    Matrix4<float> m = Matrix4<float>(1, 2, 3, 4,
                                      5, 6, 7, 8,
                                      9, 10, 11, 12,
                                      13, 14, 15, 16);

    Matrix4<float> expected = Matrix4<float>(1, 5, 9, 13,
                                             2, 6, 10, 14,
                                             3, 7, 11, 15,
                                             4, 8, 12, 16);
    Matrix4<float> t = m.transpose();
    EXPECT_EQ(expected, t);
}


TEST(TestMatrix4, TestInversion) {
    Matrix4<float> m1 = Matrix4<float>(1, 2, 10, 4,
                                       5, 6, 7, 8,
                                       9, 10, 11, 12,
                                       10, 14, 15, 12);
    Matrix4<float> inv;
    float det;
    bool res = m1.inverse(inv, 0.00000001, &det);
    float dd = m1.det();
    EXPECT_TRUE(res);
    EXPECT_EQ(280.0f, det);
    EXPECT_EQ(1.f, ceil(inv(0, 0)));
    EXPECT_EQ(0.f, inv(2, 3));
    EXPECT_EQ(-1.f, ceil(inv(0, 1)));
    EXPECT_EQ(1.f, ceil(inv(3, 1)));
}

TEST(TestMatrix4, TestArithmetic) {
    Matrix4<float> m = Matrix4<float>(1, 2, 10, 4,
                                      5, 6, 7, 8,
                                      9, 10, 11, 12,
                                      10, 14, 15, 12);
    Matrix4<float> T = m.transpose();
    Matrix4<float> R = m + T;
    Matrix4<float> expAdd = Matrix4<float>(
            2, 7, 19, 14,
            7, 12, 17, 22,
            19, 17, 22, 27,
            14, 22, 27, 24);
    EXPECT_EQ(expAdd, R);

    Matrix4<float> expMul = Matrix4<float>(
            121, 119, 187, 236,
            119, 174, 278, 335,
            187, 278, 446, 539,
            236, 335, 539, 665
    );
    Matrix4<float> RR = m * T;
    EXPECT_EQ(expMul, RR);

    Matrix4<float> expSub = Matrix4<float>(
            0, -3, 1, -6,
            3, 0, -3, -6,
            -1, 3, 0, -3,
            6, 6, 3, 0
    );

    Matrix4<float> RSub = m - T;
    EXPECT_EQ(expSub, RSub);

    Matrix4<float> A = 100.f * m;
    Matrix4<float> expectC = Matrix4<float>(
            100, 200, 1000, 400,
            500, 600, 700, 800,
            900, 1000, 1100, 1200,
            1000, 1400, 1500, 1200
    );
    EXPECT_EQ(expectC, A);

}


TEST(TestMatrix4, TestVectorMult) {
    Matrix4<double> m = Matrix4<double>(1, 2, 10, 4,
                                        5, 6, 7, 8,
                                        9, 10, 11, 12,
                                        10, 14, 15, 12);
    Vector4<double> v = {1, 2, 3, 4};
    Vector4<double> expected = {51, 70, 110, 131};
    Vector4<double> R = m * v;
    EXPECT_EQ(expected, R);

    Vector4<double> expL = {78, 100, 117, 104};
    Vector4<double> RR = v * m;
    EXPECT_EQ(expL, RR);
}

