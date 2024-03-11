//
// Created by Jason Fedorowich on 2024-03-04.
//
#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;

TEST(Vector4TestSuit, TestDefaultConstructor){
    Vector4<double> v;
    EXPECT_EQ(0.0, v.getX());
    EXPECT_EQ(0.0, v.getY());
    EXPECT_EQ(0.0, v.getZ());
    EXPECT_EQ(0.0, v.getW());
}

TEST(Vector4TestSuit, TestValueConstructor){
    Vector4<float> v(1.f, 2.f, 3.f, 4.f);
    EXPECT_EQ(1.f, v.getX());
    EXPECT_EQ(2.f, v.getY());
    EXPECT_EQ(3.f, v.getZ());
    EXPECT_EQ(4.f, v.getW());
}

TEST(Vector4TestSuit, TestCopyConstructor){
    Vector4<float> v(1.f, 2.f, 3.f, 5.f);
    Vector4<float> copy(v);
    EXPECT_EQ(1.f, copy.getX());
    EXPECT_EQ(2.f, copy.getY());
    EXPECT_EQ(3.f, copy.getZ());
    EXPECT_EQ(5.f, copy.getW());
    copy[0] = 2.f;
    EXPECT_EQ(1.f, v.getX());


}

TEST(Vector4TestSuit, TestValidIndexOperator){
    Vector4<double> v(1.f, 2.f, 3.f, 6.f);
    v[3] = 3.0;
    EXPECT_EQ(3.0, v[3]);
}

TEST(Vector4TestSuit, TestInvalidIndexOperator){
    Vector4<double> v(1.f, 2.f, 3.f, 1.f);
    v[0] = 3.0;
    EXPECT_THROW(v[5], OdinMath::InvalidArgument);
}

TEST(Vector4TestSuit, TestAddingAndMultiply){
    Vector4<double> v(1.f, 2.f, 3.f, 2.f);
    Vector4<double> v1(2.0, 4.0, 5.0, 5.f);
    Vector4<double> res = v + v1;
    EXPECT_EQ(3.0, res[0]);
    Vector4<double> res2 = v + OdinMath::Vector4<double>{1.0, 2.0, 3.0, 5.f};
    EXPECT_EQ(2.0, res2[0]);
    v1 *= 500.0;
    EXPECT_EQ(1000.0, v1[0]);
    EXPECT_EQ(2000.0, v1[1]);
    EXPECT_EQ(2500.0, v1[2]);
    EXPECT_EQ(2500.0, v1[3]);
}


TEST(Vector4TestSuit, TestRHSOperators){
    Vector4<float> v(1.f, 2.f, 3.f, 5.f);
    Vector4<float> r = 200.f * v;
    EXPECT_EQ(r[0], 200.f);
    EXPECT_EQ(r[1], 400.f);
    EXPECT_EQ(r[2], 600.f);
    EXPECT_EQ(r[3], 1000.f);

    2.f *= r;
    EXPECT_EQ(r[0], 400.f);
    EXPECT_EQ(r[1], 800.f);
    EXPECT_EQ(r[2], 1200.f);
    EXPECT_EQ(r[3], 2000.f);
}

TEST(Vector4TestSuit, TestDotCross){
    Vector4<double> v1 = Vector4<double>(1.f, 2.f, 3.f, 5.f);
    Vector4<double> v2 = Vector4<double>(5.f, 6.f, 7.f, 6.f);
    double d = v1.dot(v2);
    EXPECT_EQ(68.0, d);

}

