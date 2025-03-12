//
// Created by Jason Fedorowich on 2024-02-03.
//
#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;

TEST(Vector3TestSuit, TestDefaultConstructor) {
    Vector3<double> v;
    EXPECT_EQ(0.0, v.getX());
    EXPECT_EQ(0.0, v.getY());
    EXPECT_EQ(0.0, v.getZ());
}

TEST(Vector3TestSuit, TestValueConstructor) {
    Vector3<float> v(1.f, 2.f, 3.f);
    EXPECT_EQ(1.f, v.getX());
    EXPECT_EQ(2.f, v.getY());
    EXPECT_EQ(3.f, v.getZ());

}

TEST(Vector3TestSuit, TestCopyConstructor) {
    Vector3<float> v(1.f, 2.f, 3.f);
    Vector3<float> copy(v);
    EXPECT_EQ(1.f, copy.getX());
    EXPECT_EQ(2.f, copy.getY());
    EXPECT_EQ(3.f, copy.getZ());
    copy[0] = 2.f;
    EXPECT_EQ(1.f, v.getX());


}

TEST(Vector3TestSuit, TestValidIndexOperator) {
    Vector3<double> v(1.f, 2.f, 3.f);
    v[0] = 3.0;
    EXPECT_EQ(3.0, v[0]);
}

TEST(Vector3TestSuit, TestInvalidIndexOperator) {
    Vector3<double> v(1.f, 2.f, 3.f);
    v[0] = 3.0;
    EXPECT_THROW(v[5], OdinMath::InvalidArgument);
}

TEST(Vector3TestSuit, TestAddingAndMultiply) {
    Vector3<double> v(1.f, 2.f, 3.f);
    Vector3<double> v1(2.0, 4.0, 5.0);
    Vector3<double> res = v + v1;
    EXPECT_EQ(3.0, res[0]);
    Vector3<double> res2 = v + OdinMath::Vector3<double>{1.0, 2.0, 3.0};
    EXPECT_EQ(2.0, res2[0]);
    v1 *= 500.0;
    EXPECT_EQ(1000.0, v1[0]);
    EXPECT_EQ(2000.0, v1[1]);
    EXPECT_EQ(2500.0, v1[2]);
}


TEST(Vector3TestSuit, TestRHSOperators) {
    Vector3<float> v(1.f, 2.f, 3.f);
    Vector3<float> r = 200.f * v;
    EXPECT_EQ(r[0], 200.f);
    EXPECT_EQ(r[1], 400.f);
    EXPECT_EQ(r[2], 600.f);

    2.f *= r;
    EXPECT_EQ(r[0], 400.f);
    EXPECT_EQ(r[1], 800.f);
    EXPECT_EQ(r[2], 1200.f);
}

TEST(Vector3TestSuit, TestDotCross) {
    Vector3<double> v1 = Vector3<double>(1.f, 2.f, 3.f);
    Vector3<double> v2 = Vector3<double>(5.f, 6.f, 7.f);
    double d = v1.dot(v2);
    EXPECT_EQ(38.0, d);

    Vector3<double> v3 = Vector3<double>(500, 600, 3);
    Vector3<double> v4 = Vector3<double>(100, -700, 7);
    Vector3<double> v5 = v3.cross(v4);

    EXPECT_EQ(6300.0, v5.getX());
    EXPECT_EQ(-3200.0, v5.getY());
    EXPECT_EQ(-410000.0, v5.getZ());

}


TEST(Vector3TestSuit, TestProjection){
    Vector3<double> v1 = Vector3<double>(1.f, 2.f, 3.f);
    Vector3<double> v2 = Vector3<double>(5.f, 6.f, 7.f);
    Vector3<double> v3 = v1.project(v2);

    Vector3<double> v4 = {1.72727, 2.07273, 2.41818};
    EXPECT_NEAR(v3[0], v4[0], 0.01);
    EXPECT_NEAR(v3[1], v4[1], 0.01);
    EXPECT_NEAR(v3[2], v4[2], 0.01);

}

