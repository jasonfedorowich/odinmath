//
// Created by Jason Fedorowich on 2024-07-23.
//
#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;

TEST(VectorIntrinTestSuite, CosF) {
    float f[4] = {0.f, M_PI / 6.0, M_PI / 4.0, M_PI / 3.0};
    float r[4] = {M_PI / 2.0, -M_PI / 3.0, -2 * M_PI, -M_PI};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res1 = cosF(v1);
    auto res2 = cosF(v2);

    float store1[4];
    float store2[4];
    store4(store1, res1);
    store4(store2, res2);

    EXPECT_NEAR(1.f, store1[0], 0.01);
    EXPECT_NEAR(0.8660254037844387, store1[1], 0.01);
    EXPECT_NEAR(0.7071067811865476, store1[2], 0.01);
    EXPECT_NEAR(0.5, store1[3], 0.01);

    EXPECT_NEAR(0.0f, store2[0], 0.01);
    EXPECT_NEAR(0.5, store2[1], 0.01);
    EXPECT_NEAR(1.f, store2[2], 0.01);
    EXPECT_NEAR(-1.f, store2[3], 0.01);
}

TEST(VectorIntrinTestSuite, SinF) {
    float f[4] = {0.f, M_PI / 6.0, M_PI / 4.0, M_PI / 3.0};
    float r[4] = {M_PI / 2.0, -M_PI / 3.0, -2 * M_PI, -M_PI};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res1 = sinF(v1);
    auto res2 = sinF(v2);

    float store1[4];
    float store2[4];
    store4(store1, res1);
    store4(store2, res2);

    EXPECT_NEAR(0.f, store1[0], 0.01);
    EXPECT_NEAR(0.5, store1[1], 0.01);
    EXPECT_NEAR(0.7071067811865475, store1[2], 0.01);
    EXPECT_NEAR(0.8660254037844386, store1[3], 0.01);

    EXPECT_NEAR(1.f, store2[0], 0.01);
    EXPECT_NEAR(-0.8660254037844386, store2[1], 0.01);
    EXPECT_NEAR(0.f, store2[2], 0.01);
    EXPECT_NEAR(0.f, store2[3], 0.01);
}


TEST(VectorIntrinTestSuite, TanF) {
    float f[4] = {0.f, M_PI / 6.0, M_PI / 4.0, M_PI / 3.0};
    float r[4] = {M_PI / 2.0, -M_PI / 3.0, -2 * M_PI, -M_PI};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res1 = tanF(v1);
    auto res2 = tanF(v2);

    float store1[4];
    float store2[4];
    store4(store1, res1);
    store4(store2, res2);

    EXPECT_NEAR(0.f, store1[0], 0.01);
    EXPECT_NEAR(0.5773502691896257, store1[1], 0.01);
    EXPECT_NEAR(1.0, store1[2], 0.01);
    EXPECT_NEAR(1.7320508075688767, store1[3], 0.01);

    EXPECT_GT(abs(store2[0]), 10.f);
    EXPECT_NEAR(-1.7320508075688767, store2[1], 0.01);
    EXPECT_NEAR(0.f, store2[2], 0.01);
    EXPECT_NEAR(0.f, store2[3], 0.01);
}


TEST(VectorIntrinTestSuite, CotF) {
    float f[4] = {0.f, M_PI / 6.0, M_PI / 4.0, M_PI / 3.0};
    float r[4] = {M_PI / 2.0, -M_PI / 3.0, -2 * M_PI, -M_PI};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res1 = cotF(v1);
    auto res2 = cotF(v2);

    float store1[4];
    float store2[4];
    store4(store1, res1);
    store4(store2, res2);

    EXPECT_GT(abs(store1[0]), 10.f);
    EXPECT_NEAR(1.7320508075688774, store1[1], 0.01);
    EXPECT_NEAR(1.0, store1[2], 0.01);
    EXPECT_NEAR(0.577350269189626, store1[3], 0.01);

    EXPECT_NEAR(0.f, store2[0], 0.01);
    EXPECT_NEAR(-0.577350269189626, store2[1], 0.01);
    EXPECT_GT(abs(store2[2]), 10.f);
    EXPECT_GT(abs(store2[3]), 10.f);
}


TEST(VectorIntrinTestSuite, ACosF) {
    float f[4] = {0.f, 0.5, 0.7071, 0.8660};
    float r[4] = {1.f, -0.5, -1.f, -0.7071};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res1 = arcCosF(v1);
    auto res2 = arcCosF(v2);

    float store1[4];
    float store2[4];
    store4(store1, res1);
    store4(store2, res2);

    EXPECT_NEAR(1.57, store1[0], 0.01);
    EXPECT_NEAR(1.047, store1[1], 0.01);
    EXPECT_NEAR(0.7854, store1[2], 0.01);
    EXPECT_NEAR(0.5236, store1[3], 0.01);

    EXPECT_NEAR(0, store2[0], 0.01);
    EXPECT_NEAR(2.094, store2[1], 0.01);
    EXPECT_NEAR(3.142, store2[2], 0.01);
    EXPECT_NEAR(2.356, store2[3], 0.01);
}

TEST(VectorIntrinTestSuite, ASinF) {
    float f[4] = {0.f, 0.5, 0.7071, 0.8660};
    float r[4] = {1.f, -0.5, -1.f, -0.7071};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res1 = arcSinF(v1);
    auto res2 = arcSinF(v2);

    float store1[4];
    float store2[4];
    store4(store1, res1);
    store4(store2, res2);

    EXPECT_NEAR(0.f, store1[0], 0.01);
    EXPECT_NEAR(0.5235987755983, store1[1], 0.01);
    EXPECT_NEAR(0.7853885733974476, store1[2], 0.01);
    EXPECT_NEAR(1.0471467458630677, store1[3], 0.01);

    EXPECT_NEAR(1.5707963267948966, store2[0], 0.01);
    EXPECT_NEAR(-0.5235987755983, store2[1], 0.01);
    EXPECT_NEAR(-1.5707963267948966, store2[2], 0.01);
    EXPECT_NEAR(-0.7853885733974476, store2[3], 0.01);
}