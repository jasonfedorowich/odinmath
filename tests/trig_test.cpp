//
// Created by Jason Fedorowich on 2024-06-30.
//


#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;

float piF = 3.142f;
double piD = 3.142;

TEST(TrigTestSuit, TestSinF){
    float s1 = sinF<float>(0);
    double s2 = sinF<double>(piD / 6.0);
    float s3 = sinF<float>(piF / 4.0);
    double s4 = sinF<double>(piD / 3.0);
    float s5 = sinF<float>(piF / 2.0);

    float s6 = sinF<float>(-piF / 3.0);
    double s7 = sinF<double>(2 * piD);
    float s8 = sinF<float>(piF);

    ASSERT_NEAR(s1, 0.f, 0.01);
    ASSERT_NEAR(s2, 0.5, 0.01);
    ASSERT_NEAR(s3, 0.7071, 0.01);
    ASSERT_NEAR(s4, 0.8660, 0.01);
    ASSERT_NEAR(s5, 1.0, 0.01);
    ASSERT_NEAR(s6, -0.8660, 0.01);
    ASSERT_NEAR(s7, 0.0, 0.01);
    ASSERT_NEAR(s8, 0.0, 0.01);
}


TEST(TrigTestSuit, TestCosF){
    float s1 = cosF<float>(0);
    double s2 = cosF<double>(piD / 6.0);
    float s3 = cosF<float>(piF / 4.0);
    double s4 = cosF<double>(piD / 3.0);
    float s5 = cosF<float>(piF / 2.0);

    float s6 = cosF<float>(-piF / 3.0);
    double s7 = cosF<double>(2 * piD);
    double s8 = cosF<double>(piD);


    ASSERT_NEAR(s1, 1.f, 0.01);
    ASSERT_NEAR(s2, 0.8660, 0.01);
    ASSERT_NEAR(s3, 0.7071, 0.01);
    ASSERT_NEAR(s4, 0.5, 0.01);
    ASSERT_NEAR(s5, 0.0, 0.01);
    ASSERT_NEAR(s6, 0.5, 0.1);
    ASSERT_NEAR(s7, 1.0, 0.01);
    ASSERT_NEAR(s8, -1.0, 0.01);
}



TEST(TrigTestSuit, TestTanF){
    float s1 = tanF<float>(0);
    double s2 = tanF<double>(piD / 6.0);
    float s3 = tanF<float>(piF / 4.0);
    double s4 = tanF<double>(piD / 3.0);
    float s5 = abs(tanF<float>(piF / 2.0));

    float s6 = tanF<float>(-piF / 3.0);
    double s7 = tanF<double>(2 * piD);
    double s8 = tanF<double>(piD);


    ASSERT_NEAR(s1, 0.f, 0.01);
    ASSERT_NEAR(s2, 0.5774, 0.01);
    ASSERT_NEAR(s3, 1.0, 0.01);
    ASSERT_NEAR(s4, 1.732, 0.01);
    ASSERT_GT(s5, 10.f);
    ASSERT_NEAR(s6, -1.732, 0.1);
    ASSERT_NEAR(s7, 0.0, 0.01);
    ASSERT_NEAR(s8, 0.0, 0.01);
}


TEST(TrigTestSuit, TestCotF){
    float s1 = cotF<float>(0);
    double s2 = cotF<double>(piD / 6.0);
    float s3 = cotF<float>(piF / 4.0);
    double s4 = cotF<double>(piD / 3.0);
    float s5 = abs(cotF<float>(piF / 2.0));

    float s6 = cotF<float>(-piF / 3.0);
    double s7 = abs(cotF<double>(2 * piD));
    double s8 = abs(cotF<double>(piD));


    ASSERT_GT(s1, 100.f);
    ASSERT_NEAR(s2, 1.732, 0.01);
    ASSERT_NEAR(s3, 1.0, 0.01);
    ASSERT_NEAR(s4, 0.5774, 0.01);
    ASSERT_NEAR(s5, 0.0, 0.01f);
    ASSERT_NEAR(s6, -0.5774, 0.1);
    ASSERT_GT(s7, 100.0);
    ASSERT_GT(s8, 100.0);
}


