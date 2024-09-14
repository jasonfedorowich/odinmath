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

TEST(VectorIntrinTestSuite, ATanF) {
    float f[4] = {0.f, 0.5, 0.7071, 0.8660};
    float r[4] = {1.f, -0.5, -1.f, -0.7071};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res1 = arcTanF(v1);
    auto res2 = arcTanF(v2);

    float store1[4];
    float store2[4];
    store4(store1, res1);
    store4(store2, res2);

    EXPECT_NEAR(0.f, store1[0], 0.01);
    EXPECT_NEAR(0.4636476090008061, store1[1], 0.01);
    EXPECT_NEAR(0.6154751878649, store1[2], 0.01);
    EXPECT_NEAR(0.7137098623140186, store1[3], 0.01);

    EXPECT_NEAR(0.7853981633974483, store2[0], 0.01);
    EXPECT_NEAR(-0.4636476090008061, store2[1], 0.01);
    EXPECT_NEAR(-0.7853981633974483, store2[2], 0.01);
    EXPECT_NEAR(-0.6161415445725856, store2[3], 0.01);
}


TEST(VectorIntrinTestSuite, ATan2F) {
    float f[4] = {0.f, 1, 1, sqrt(3.f)};
    float f2[4] = {1, 2, sqrt(2.f), 2.f};
    float r[4] = {-1.f, -1, -1.f, 1};
    float r2[4] = {2, 1, sqrt(2.f), 0};

    auto v1 = load4(f);
    auto v2 = load4(r);
    auto u1 = load4(f2);
    auto u2 = load4(r2);

    auto res1 = arcTan2F(v1, u1);
    auto res2 = arcTan2F(v2, u2);

    float store1[4];
    float store2[4];
    store4(store1, res1);
    store4(store2, res2);

    EXPECT_NEAR(0.f, store1[0], 0.01);
    EXPECT_NEAR(0.4636476090008061, store1[1], 0.01);
    EXPECT_NEAR(0.6154751878649, store1[2], 0.01);
    EXPECT_NEAR(0.7137098623140186, store1[3], 0.01);

    EXPECT_NEAR(-0.4636476090008061, store2[0], 0.01);
    EXPECT_NEAR(-0.7853981633974483, store2[1], 0.01);
    EXPECT_NEAR(-0.6161415445725856, store2[2], 0.01);
    EXPECT_NEAR(1.57078632679489695, store2[3], 0.01);

}

TEST(VectorIntrinTestSuite, Sinh) {
    float f[4] = {0.f, M_PI / 6.0, M_PI / 4.0, M_PI / 3.0};
    float r[4] = {M_PI / 2.0, -M_PI / 3.0, -2 * M_PI, -M_PI};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res1 = sinhF(v1);
    auto res2 = sinhF(v2);

    float store1[4];
    float store2[4];
    store4(store1, res1);
    store4(store2, res2);

    EXPECT_NEAR(0.f, store1[0], 0.01);
    EXPECT_NEAR(0.5478534738880397, store1[1], 0.01);
    EXPECT_NEAR(0.8686709614860095, store1[2], 0.01);
    EXPECT_NEAR(1.249367050524, store1[3], 0.01);

    EXPECT_NEAR(2.3012989023072947, store2[0], 0.01);
    EXPECT_NEAR(-1.249367050524, store2[1], 0.01);
    EXPECT_NEAR(-267.74489404101644, store2[2], 0.01);
    EXPECT_NEAR(-11.548739357257748, store2[3], 0.01);
}


TEST(VectorIntrinTestSuite, Cosh) {
    float f[4] = {0.f, M_PI / 6.0, M_PI / 4.0, M_PI / 3.0};
    float r[4] = {M_PI / 2.0, -M_PI / 3.0, -2 * M_PI, -M_PI};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res1 = coshF(v1);
    auto res2 = coshF(v2);

    float store1[4];
    float store2[4];
    store4(store1, res1);
    store4(store2, res2);

    EXPECT_NEAR(1.f, store1[0], 0.01);
    EXPECT_NEAR(1.1402383210764286, store1[1], 0.01);
    EXPECT_NEAR(1.324609089252, store1[2], 0.01);
    EXPECT_NEAR(1.600286857702386, store1[3], 0.01);

    EXPECT_NEAR(2.5091784786580567, store2[0], 0.01);
    EXPECT_NEAR(1.600286857702386, store2[1], 0.01);
    EXPECT_NEAR(267.7467614837482, store2[2], 0.01);
    EXPECT_NEAR(11.591953275521519, store2[3], 0.01);
}