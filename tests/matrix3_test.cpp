//
// Created by Jason Fedorowich on 2024-04-07.
//


#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;

TEST(TestMatrix3, TestConstructor) {
    Matrix3<float> m1;
    EXPECT_EQ(0.f, m1(0, 0));
    EXPECT_EQ(0.f, m1(1, 1));
    Matrix3<double> m2(1.0, 2.0, 3.0,
                       5.0, 6.0, 7.0,
                       9.0, 10.0, 11.0);
    EXPECT_EQ(11.0, m2(2, 2));
    EXPECT_THROW(m2(4, 4), OdinMath::InvalidArgument);
}

TEST(TestMatrix3, TestIdentity) {
    Matrix3<float> m = Matrix3<float>::identity();
    EXPECT_EQ(1.f, m(0, 0));
    EXPECT_EQ(1.f, m(1, 1));
    EXPECT_EQ(1.f, m(2, 2));
}

TEST(TestMatrix3, TestDeterminant) {
    Matrix3<float> m = Matrix3<float>(1, 2, 3,
                                      4, 5, 6,
                                      7, 8, 9);
    float d = m.det();
    EXPECT_LE(d, 1e-12);

    Matrix3<float> m1 = Matrix3<float>(1, 2, 10,
                                       5, 6, 7,
                                       9, 10, 1);

    float d1 = m1.det();
    EXPECT_EQ(12.0f, d1);

    Matrix3<float> m2 = Matrix3<float>(1, 2, 10,
                                       5, 6, 7,
                                       9, 10, 11);
    float d2 = m2.det();
    EXPECT_EQ(-28.f, d2);
}


TEST(TestMatrix3, TestTranspose) {
    Matrix3<float> m = Matrix3<float>(1, 2, 3,
                                      5, 6, 7,
                                      9, 10, 11);

    Matrix3<float> expected = Matrix3<float>(1, 5, 9,
                                             2, 6, 10,
                                             3, 7, 11);
    Matrix3<float> t = m.transpose();
    EXPECT_EQ(expected, t);
}


TEST(TestMatrix3, TestInversion) {
    Matrix3<float> m1 = Matrix3<float>(1, 2, 10,
                                       5, 6, 7,
                                       9, 10, 11);
    Matrix3<float> inv;
    float det;
    bool res = m1.inverse(inv, 0.00000001, &det);
    float dd = m1.det();
    EXPECT_TRUE(res);
    Matrix3<float> expected = Matrix3<float>( 0.1429,  -2.7857,   1.6429,
                                              -0.2857,   2.8214 , -1.5357,
                                              0.1429,  -0.2857,  0.1429);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            expected(i, j) = round(expected(i, j));
            inv(i, j) = round(inv(i, j));
        }
    }

    EXPECT_EQ(expected, inv);
    EXPECT_EQ(-28.0f, det);
}

TEST(TestMatrix3, TestArithmetic) {
    Matrix3<float> m = Matrix3<float>(1, 2, 10,
                                      5, 6, 7,
                                      9, 10, 11);
    Matrix3<float> T = m.transpose();
    Matrix3<float> R = m + T;
    Matrix3<float> expAdd = Matrix3<float>(
            2, 7, 19,
            7, 12, 17,
            19, 17, 22);
    EXPECT_EQ(expAdd, R);

    Matrix3<float> expMul = Matrix3<float>(
    105,    87,   139,
    87,   110,   182,
    139,   182,   302
    );
    Matrix3<float> RR = m * T;
    EXPECT_EQ(expMul, RR);

    Matrix3<float> expSub = Matrix3<float>(
            0, -3, 1,
            3, 0, -3,
            -1, 3, 0
    );

    Matrix3<float> RSub = m - T;
    EXPECT_EQ(expSub, RSub);

    Matrix3<float> A = 100.f * m;
    Matrix3<float> expectC = Matrix3<float>(
            100, 200, 1000,
            500, 600, 700,
            900, 1000, 1100
    );
    EXPECT_EQ(expectC, A);

}


TEST(TestMatrix3, TestVectorMult) {
    Matrix3<double> m = Matrix3<double>(1, 2, 10,
                                        5, 6, 7,
                                        9, 10, 11);
    Vector3<double> v = {1, 2, 3};
    Vector3<double> expected = {
            35,
            38,
            62};
    Vector3<double> R = m * v;
    EXPECT_EQ(expected, R);

    Vector3<double> expL = {38,  44,   57};
    Vector3<double> RR = v * m;
    EXPECT_EQ(expL, RR);
}

