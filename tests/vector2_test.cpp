//
// Created by Jason Fedorowich on 2024-03-02.
//
#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;


TEST(Vector2TestSuit, TestDefaultConstructor) {
    Vector2<double> v;
    EXPECT_EQ(0.0, v.getX());
    EXPECT_EQ(0.0, v.getY());
}

TEST(Vector2TestSuit, TestValueConstructor) {
    Vector2<float> v(1.f, 2.f);
    EXPECT_EQ(1.f, v.getX());
    EXPECT_EQ(2.f, v.getY());

}

TEST(Vector2TestSuit, TestCopyConstructor) {
    Vector2<float> v(1.f, 2.f);
    Vector2<float> copy(v);
    EXPECT_EQ(1.f, copy.getX());
    EXPECT_EQ(2.f, copy.getY());
    copy[0] = 2.f;
    EXPECT_EQ(1.f, v.getX());


}

TEST(Vector2TestSuit, TestValidIndexOperator) {
    Vector2<double> v(1.f, 2.f);
    v[0] = 3.0;
    EXPECT_EQ(3.0, v[0]);
}

TEST(Vector2TestSuit, TestInvalidIndexOperator) {
    Vector2<double> v(1.f, 2.f);
    v[0] = 3.0;
    EXPECT_THROW(v[5], OdinMath::InvalidArgument);
}

TEST(Vector2TestSuit, TestAddingAndMultiply) {
    Vector2<double> v(1.f, 2.f);
    Vector2<double> v1(2.0, 4.0);
    Vector2<double> res = v + v1;
    EXPECT_EQ(3.0, res[0]);
    Vector2<double> res2 = v + OdinMath::Vector2<double>{1.0, 2.0};
    EXPECT_EQ(2.0, res2[0]);
    v1 *= 500.0;
    EXPECT_EQ(1000.0, v1[0]);
    EXPECT_EQ(2000.0, v1[1]);
}


TEST(Vector2TestSuit, TestRHSOperators) {
    Vector2<float> v(1.f, 2.f);
    Vector2<float> r = 200.f * v;
    EXPECT_EQ(r[0], 200.f);
    EXPECT_EQ(r[1], 400.f);

    2.f *= r;
    EXPECT_EQ(r[0], 400.f);
    EXPECT_EQ(r[1], 800.f);
}

TEST(Vector2TestSuit, TestDot) {
    Vector2<double> v1 = Vector2<double>(1.f, 2.f);
    Vector2<double> v2 = Vector2<double>(5.f, 6.f);
    double d = v1.dot(v2);
    EXPECT_EQ(17.0, d);
}


TEST(Vector2TestSuit, TestProjection){
    Vector2<double> v1 = Vector2<double>(1.f, 2.f);
    Vector2<double> v2 = Vector2<double>(5.f, 6.f);
    Vector2<double> v3 = v1.project(v2);

    Vector2<double> v4 = {1.39344, 1.67213};
    EXPECT_NEAR(v3[0], v4[0], 0.01);
    EXPECT_NEAR(v3[1], v4[1], 0.01);
}