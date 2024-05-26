//
// Created by Jason Fedorowich on 2024-02-18.
//
#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;

//float f1[4] = {1, 3, 1, 4};
//float f2[4] = {2, 2, 2, 2};
//v1 = load4(f1);
//v2 = load4(f2);
//set the position from first index to the number from the second index
//auto v3 = vcopyq_laneq_f32(v2, 3, v1, 1);

#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))

TEST(VectorIntrinTestSuite, LoadAndStore) {
    float f[4] = {1.f, 2.f, 3.f, 4.f};
    float r[4];
    auto v = load4(f);
    store4(r, v);
    EXPECT_EQ(1.f, r[0]);
    EXPECT_EQ(2.f, r[1]);
    EXPECT_EQ(3.f, r[2]);
    EXPECT_EQ(4.f, r[3]);
}

TEST(VectorIntrinTestSuite, Add) {
    float f[4] = {1.f, 2.f, 3.f, 4.f};
    float r[4] = {3.f, 5.f, 6.f, 7.f};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res = add(v1, v2);
    float store[4];
    store4(store, res);
    EXPECT_EQ(4.f, store[0]);
    EXPECT_EQ(7.f, store[1]);
    EXPECT_EQ(9.f, store[2]);
    EXPECT_EQ(11.f, store[3]);
}


TEST(VectorIntrinTestSuite, Sub) {
    float f[4] = {1.f, 2.f, 3.f, 4.f};
    float r[4] = {3.f, 5.f, 6.f, 8.f};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res = sub(v1, v2);
    float store[4];
    store4(store, res);
    EXPECT_EQ(-2.f, store[0]);
    EXPECT_EQ(-3.f, store[1]);
    EXPECT_EQ(-3.f, store[2]);
    EXPECT_EQ(-4.f, store[3]);
}

TEST(VectorIntrinTestSuite, Mul) {
    float f[4] = {1.f, 2.f, 3.f, 4.f};
    float r[4] = {3.f, 5.f, 6.f, 7.f};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res = mul(v1, v2);
    float store[4];
    store4(store, res);
    EXPECT_EQ(3.f, store[0]);
    EXPECT_EQ(10.f, store[1]);
    EXPECT_EQ(18.f, store[2]);
    EXPECT_EQ(28.f, store[3]);
}

TEST(VectorIntrinTestSuite, Div) {
    float f[4] = {9.f, 10.f, 4.f, 5.f};
    float r[4] = {3.f, 5.f, 2.f, 1.f};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res = div(v1, v2);
    float store[4];
    store4(store, res);
    EXPECT_EQ(3.f, store[0]);
    EXPECT_EQ(2.f, store[1]);
    EXPECT_EQ(2.f, store[2]);
    EXPECT_EQ(5.f, store[3]);
}


TEST(VectorIntrinTestSuite, Load3AndStore3) {
    float f[3] = {9.f, 10.f, 4.f};
    float r[3];
    auto v1 = load3(f);
    store3(r, v1);
    EXPECT_EQ(9.f, r[0]);
    EXPECT_EQ(10.f, r[1]);
    EXPECT_EQ(4.f, r[2]);
}

TEST(VectorIntrinTestSuite, Load2AndStore2) {
    float f[2] = {9.f, 10.f};
    float r[2];
    auto v1 = load2(f);
    store2(r, v1);
    EXPECT_EQ(9.f, r[0]);
    EXPECT_EQ(10.f, r[1]);
}

TEST(VectorIntrinTestSuite, Div3) {
    float f[3] = {9.f, 10.f, 26.f};
    float r[3] = {3.f, 2.f, 2.f};
    auto v1 = load3(f);
    auto v2 = load3(r);
    auto res = div3(v1, v2);
    float rr[3];
    store3(rr, res);
    EXPECT_EQ(3.f, rr[0]);
    EXPECT_EQ(5.f, rr[1]);
    EXPECT_EQ(13.f, rr[2]);
}

TEST(VectorIntrinTestSuite, Div2) {
    float f[2] = {9.f, 10.f};
    float r[2] = {3.f, 2.f};
    auto v1 = load2(f);
    auto v2 = load2(r);
    auto res = div2(v1, v2);
    float rr[2];
    store2(rr, res);
    EXPECT_EQ(3.f, rr[0]);
    EXPECT_EQ(5.f, rr[1]);
}


TEST(VectorIntrinTestSuite, Dot4) {
    float f[4] = {1, 2, 3, 4};
    float r[4] = {5, 6, 7, 8};
    auto v1 = load4(f);
    auto v2 = load4(r);
    auto res = dot(v1, v2);
    float rr[4];
    store4(rr, res);
    EXPECT_EQ(70.f, rr[0]);
    EXPECT_EQ(70.f, rr[1]);
}


TEST(VectorIntrinTestSuite, Dot3) {
    float f[3] = {1, 2, 3};
    float r[3] = {5, 6, 7};
    auto v1 = load3(f);
    auto v2 = load3(r);
    auto res = dot(v1, v2);
    float rr[3];
    store3(rr, res);
    EXPECT_EQ(38.f, rr[0]);
    EXPECT_EQ(38.f, rr[1]);
}

TEST(VectorIntrinTestSuite, Cross3) {
    float f[3] = {500, 600, 3};
    float r[3] = {100, -700, 7};
    auto v1 = load3(f);
    auto v2 = load3(r);
    auto res = cross3(v1, v2);
    float rr[3];
    store3(rr, res);
    EXPECT_EQ(6300.f, rr[0]);
    EXPECT_EQ(-3200.f, rr[1]);
    EXPECT_EQ(-410000.f, rr[2]);
}

TEST(VectorIntrinTestSuite, ScalarMult) {
    float f[4] = {500, 600, 3, 100};
    auto v1 = load4(f);
    auto res = scalarMul(10.f, v1);
    float rr[4];
    store4(rr, res);
    EXPECT_EQ(5000.f, rr[0]);
    EXPECT_EQ(6000.f, rr[1]);
    EXPECT_EQ(30.f, rr[2]);
    EXPECT_EQ(1000.f, rr[3]);

}


TEST(VectorIntrinTestSuite, ZeroLast) {
    float f[4] = {500, 600, 3, 100};
    auto v1 = load4(f);
    v1 = zeroLast(v1);
    float rr[4];
    store4(rr, v1);
    EXPECT_EQ(500.f, rr[0]);
    EXPECT_EQ(600.f, rr[1]);
    EXPECT_EQ(3.f, rr[2]);
    EXPECT_EQ(0.f, rr[3]);

}

TEST(VectorIntrinTestSuite, Equal){
    float f[4] = {500, 600, 3, 100};
    auto v1 = load4(f);
    float f1[4] = {501, 600, 3, 100};
    auto v2 = load4(f1);
    auto r = equal(v1, v2);
    float res[4];
    store4(res, r);
    EXPECT_EQ(res[0], 0.f);
}


TEST(Vector2FloatTestSuite, Constructor) {
    Vector2Float v;
    float x = 1 + 2;
    v.setX(x);
    EXPECT_EQ(3.f, v.getX());
}

TEST(Vector2FloatTestSuite, Arithmetic) {
    Vector2Float v1 = Vector2Float(1.f, 2.f);
    Vector2Float v2 = Vector2Float(1.f, 2.f);

    Vector2Float v3 = v1 + v2;
    EXPECT_EQ(2.f, v3.getX());
    EXPECT_EQ(4.f, v3.getY());

    Vector2Float v4 = v3 * 3.f;
    EXPECT_EQ(6.f, v4.getX());
    EXPECT_EQ(12.f, v4.getY());

    v4 /= 3.f;
    EXPECT_EQ(2.f, v4.getX());
    EXPECT_EQ(4.f, v4.getY());

    v4 *= 3.f;
    EXPECT_EQ(6.f, v4.getX());
    EXPECT_EQ(12.f, v4.getY());

    v4 += v1;
    EXPECT_EQ(7.f, v4.getX());
    EXPECT_EQ(14.f, v4.getY());

}

TEST(Vector2FloatTestSuite, TestDot) {
    Vector2Float v1 = Vector2Float(1.f, 2.f);
    Vector2Float v2 = Vector2Float(5.f, 6.f);
    float d = v1.dot(v2);
    EXPECT_EQ(17.f, d);


}


TEST(Vector3FloatTestSuite, Constructor) {
    Vector3Float v = Vector3Float();
    float x = 1 + 2;
    v.setX(x);
    v.setY(x);
    v.setZ(x);
    EXPECT_EQ(3.f, v.getX());
    EXPECT_EQ(3.f, v.getY());
    EXPECT_EQ(3.f, v.getZ());
}

TEST(Vector3FloatTestSuite, Arithmetic) {
    Vector3Float v1 = Vector3Float(1.f, 2.f, 3.f);
    Vector3Float v2 = Vector3Float(1.f, 2.f, 3.f);

    Vector3Float v3 = v1 + v2;
    EXPECT_EQ(2.f, v3.getX());
    EXPECT_EQ(4.f, v3.getY());
    EXPECT_EQ(6.f, v3.getZ());

    Vector3Float v4 = v3 * 3.f;
    EXPECT_EQ(6.f, v4.getX());
    EXPECT_EQ(12.f, v4.getY());
    EXPECT_EQ(18.f, v4.getZ());

    v4 /= 3.f;
    EXPECT_EQ(2.f, v4.getX());
    EXPECT_EQ(4.f, v4.getY());
    EXPECT_EQ(6.f, v4.getZ());

    v4 *= 3.f;
    EXPECT_EQ(6.f, v4.getX());
    EXPECT_EQ(12.f, v4.getY());
    EXPECT_EQ(18.f, v4.getZ());

    v4 += v1;
    EXPECT_EQ(7.f, v4.getX());
    EXPECT_EQ(14.f, v4.getY());
    EXPECT_EQ(21.f, v4.getZ());

}

TEST(Vector3FloatTestSuite, TestDotAndCross) {
    Vector3Float v1 = Vector3Float(1.f, 2.f, 3.f);
    Vector3Float v2 = Vector3Float(5.f, 6.f, 7.f);
    float d = v1.dot(v2);
    EXPECT_EQ(38.f, d);

    Vector3Float v3 = Vector3Float(500, 600, 3);
    Vector3Float v4 = Vector3Float(100, -700, 7);
    Vector3Float v5 = v3.cross(v4);

    EXPECT_EQ(6300.f, v5.getX());
    EXPECT_EQ(-3200.f, v5.getY());
    EXPECT_EQ(-410000.f, v5.getZ());
}


TEST(Vector4FloatTestSuite, Constructor) {
    Vector4Float v = Vector4Float();
    EXPECT_EQ(0.f, v.getX());
    EXPECT_EQ(0.f, v.getY());
    EXPECT_EQ(0.f, v.getZ());
    EXPECT_EQ(0.f, v.getW());
    float x = 1 + 2;
    v.setX(x);
    v.setY(x);
    v.setZ(x);
    v.setW(3 + 4);
    EXPECT_EQ(3.f, v.getX());
    EXPECT_EQ(3.f, v.getY());
    EXPECT_EQ(3.f, v.getZ());
    EXPECT_EQ(7.f, v.getW());
    Vector4Float vv = {1, 2, 3, 4};
    v = vv;
    EXPECT_EQ(1.f, v.getX());
    EXPECT_EQ(2.f, v.getY());
    EXPECT_EQ(3.f, v.getZ());
    EXPECT_EQ(4.f, v.getW());
}

TEST(Vector4FloatTestSuite, Arithmetic) {
    Vector4Float v1 = Vector4Float(1.f, 2.f, 3.f, 5.f);
    Vector4Float v2 = Vector4Float(1.f, 2.f, 3.f, 5.f);

    Vector4Float v3 = v1 + v2;
    EXPECT_EQ(2.f, v3.getX());
    EXPECT_EQ(4.f, v3.getY());
    EXPECT_EQ(6.f, v3.getZ());
    EXPECT_EQ(10.f, v3.getW());

    Vector4Float v4 = v3 * 3.f;
    EXPECT_EQ(6.f, v4.getX());
    EXPECT_EQ(12.f, v4.getY());
    EXPECT_EQ(18.f, v4.getZ());
    EXPECT_EQ(30.f, v4.getW());

    v4 /= 3.f;
    EXPECT_EQ(2.f, v4.getX());
    EXPECT_EQ(4.f, v4.getY());
    EXPECT_EQ(6.f, v4.getZ());
    EXPECT_EQ(10.f, v4.getW());


    v4 *= 3.f;
    EXPECT_EQ(6.f, v4.getX());
    EXPECT_EQ(12.f, v4.getY());
    EXPECT_EQ(18.f, v4.getZ());
    EXPECT_EQ(30.f, v4.getW());


    v4 += v1;
    EXPECT_EQ(7.f, v4.getX());
    EXPECT_EQ(14.f, v4.getY());
    EXPECT_EQ(21.f, v4.getZ());
    EXPECT_EQ(35.f, v4.getW());

}

TEST(Vector4FloatTestSuite, TestDotAndCross) {
    Vector4Float v1 = Vector4Float(1.f, 2.f, 3.f, 5.f);
    Vector4Float v2 = Vector4Float(5.f, 6.f, 7.f, 5.f);
    float d = v1.dot(v2);
    EXPECT_EQ(63.f, d);

    Vector4Float v3 = Vector4Float(500, 600, 3, 10.f);
    Vector4Float v4 = Vector4Float(100, -700, 7, 10.f);
    Vector4Float v5 = v3.cross(v4);

    EXPECT_EQ(6300.f, v5.getX());
    EXPECT_EQ(-3200.f, v5.getY());
    EXPECT_EQ(-410000.f, v5.getZ());
    EXPECT_EQ(0.f, v5.getW());
}

#endif