//
// Created by Jason Fedorowich on 2025-04-18.
//


#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;


TEST(QrTestSuite, TestQrGs) {
    Matrix3<float> A = {1, 1, 0,
                        1, 0, 1,
                        0, 1, 1};

    Matrix3<float> q;
    Matrix3<float> r;
    gs<float>(A, q, r);
    ASSERT_TRUE(r.isUpperTriangular(0.0001));

    Matrix4<float> AA = {1,   2,    3,    6,
    4,   5,    6,    7,
    7,    8,    9,   11,
    5,    3,    2,    1};

    Matrix4<float> qq;
    Matrix4<float> rr;
    gs<float>(AA, qq, rr);

    ASSERT_TRUE(rr.isUpperTriangular(0.0001));



    Matrix2<float> A3 = {1, 0,
                         2, 3};
    Matrix2<float> q3, r3;
    gs<float>(A3, q3, r3);

    ASSERT_TRUE(r3.isUpperTriangular(0.0001));
}

TEST(QrTestSuite, TestQrGsMatrix4Float) {

    Matrix4Float AA = {1,   2,    3,    6,
                         4,   5,    6,    7,
                         7,    8,    9,   11,
                         5,    3,    2,    1};

    Matrix4Float qq;
    Matrix4Float rr;
    gsF(AA, qq, rr);

    ASSERT_TRUE(rr.isUpperTriangular(0.0001));



    Matrix2<float> A3 = {1, 0,
                         2, 3};
    Matrix2<float> q3, r3;
    gs<float>(A3, q3, r3);

    ASSERT_TRUE(r3.isUpperTriangular(0.0001));
}

TEST(QrTestSuite, TestQrGsMatrix3Float) {

    Matrix3Float AA = {1,   2,    3,
                       4,   5,    6,
                       7,    8,    9};

    Matrix3Float qq;
    Matrix3Float rr;
    gsF(AA, qq, rr);

    ASSERT_TRUE(rr.isUpperTriangular(0.0001));

}


TEST(QrTestSuite, TestQrGsMatrix2Float) {

    Matrix2Float AA = {1,   2,
                       4,   5};

    Matrix2Float qq;
    Matrix2Float rr;
    gsF(AA, qq, rr);

    ASSERT_TRUE(rr.isUpperTriangular(0.0001));

}

