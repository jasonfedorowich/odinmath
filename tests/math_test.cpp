//
// Created by Jason Fedorowich on 2024-07-17.
//


#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;


TEST(MathTest, TestExp){
    float s1 = expF<float>(0);
    double s2 = expF<double>(2 * M_PI);
    float s3 = expF<float>(M_PI / 4.0);
    double s4 = expF<double>(M_PI / 3.0);
    float s5 = expF<float>(M_PI / 2.0);

    float s6 = expF<float>(-M_PI / 3.0);
    double s7 = expF<double>(-2 * M_PI);
    float s8 = expF<float>(M_PI);
    double s9 = expF<double>(M_PI / 6);
    float s10 = expF<float>(-M_PI / 2);

    ASSERT_NEAR(s1, 1.f, 0.01);
    ASSERT_NEAR(s2, 535.4916555247646, 0.01);
    ASSERT_NEAR(s3, 2.193280050738, 0.01);
    ASSERT_NEAR(s4, 2.849653908226361, 0.01);
    ASSERT_NEAR(s5, 4.810477380965351, 0.01);
    ASSERT_NEAR(s6, 0.350919807178411, 0.01);
    ASSERT_NEAR(s7, 0.001867442731708, 0.01);
    ASSERT_NEAR(s8, 23.140692632779267, 0.01);
    ASSERT_NEAR(s9, 1.6880917949644685, 0.01);
    ASSERT_NEAR(s10, 0.20787957635076193, 0.01);
}
