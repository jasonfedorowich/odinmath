//
// Created by Jason Fedorowich on 2024-06-30.
//


#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;


TEST(TrigTestSuit, TestSinF){
    float s1 = sinF<float>(0);
    double s2 = sinF<double>(M_PI / 6.0);
    float s3 = sinF<float>(M_PI / 4.0);
    double s4 = sinF<double>(M_PI / 3.0);
    float s5 = sinF<float>(M_PI / 2.0);

    float s6 = sinF<float>(-M_PI / 3.0);
    double s7 = sinF<double>(2 * M_PI);
    float s8 = sinF<float>(M_PI);

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
    double s2 = cosF<double>(M_PI / 6.0);
    float s3 = cosF<float>(M_PI / 4.0);
    double s4 = cosF<double>(M_PI / 3.0);
    float s5 = cosF<float>(M_PI / 2.0);

    float s6 = cosF<float>(-M_PI / 3.0);
    double s7 = cosF<double>(2 * M_PI);
    double s8 = cosF<double>(M_PI);


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
    double s2 = tanF<double>(M_PI / 6.0);
    float s3 = tanF<float>(M_PI / 4.0);
    double s4 = tanF<double>(M_PI / 3.0);
    float s5 = abs(tanF<float>(M_PI / 2.0));

    float s6 = tanF<float>(-M_PI / 3.0);
    double s7 = tanF<double>(2 * M_PI);
    double s8 = tanF<double>(M_PI);


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
    double s2 = cotF<double>(M_PI / 6.0);
    float s3 = cotF<float>(M_PI / 4.0);
    double s4 = cotF<double>(M_PI / 3.0);
    float s5 = abs(cotF<float>(M_PI / 2.0));

    float s6 = cotF<float>(-M_PI / 3.0);
    double s7 = abs(cotF<double>(2 * M_PI));
    double s8 = abs(cotF<double>(M_PI));


    ASSERT_GT(s1, 100.f);
    ASSERT_NEAR(s2, 1.732, 0.01);
    ASSERT_NEAR(s3, 1.0, 0.01);
    ASSERT_NEAR(s4, 0.5774, 0.01);
    ASSERT_NEAR(s5, 0.0, 0.01f);
    ASSERT_NEAR(s6, -0.5774, 0.1);
    ASSERT_GT(s7, 100.0);
    ASSERT_GT(s8, 100.0);
}

TEST(TrigTestSuit, TestAsinF){
    float s1 = arcSinF<float>(0);
    double s2 = arcSinF<double>(0.5);
    float s3 = arcSinF<float>(0.7071);
    double s4 = arcSinF<double>(0.8660);
    float s5 = arcSinF<float>(1.f);

    float s6 = arcSinF<float>(-0.5);
    double s7 = arcSinF<double>(-1);
    double s8 = arcSinF<double>(-0.7071);

    ASSERT_NEAR(s1, 0.0f, 0.01);
    ASSERT_NEAR(s2, 0.5235987755983, 0.01);
    ASSERT_NEAR(s3, 0.7853885733974476, 0.01);
    ASSERT_NEAR(s4, 1.0471467458630677, 0.01);
    ASSERT_NEAR(s5, 1.5707963267948966, 0.01);
    ASSERT_NEAR(s6, -0.5235987755983, 0.1);
    ASSERT_NEAR(s7, -1.5707963267948966, 0.1);
    ASSERT_NEAR(s8, -0.7853885733974476, 0.1);

}

TEST(TrigTestSuit, TestAcosF){
    float s1 = arcCosF<float>(0);
    double s2 = arcCosF<double>(0.5);
    float s3 = arcCosF<float>(0.7071);
    double s4 = arcCosF<double>(0.8660);
    float s5 = arcCosF<float>(1.f);

    float s6 = arcCosF<float>(-0.5);
    double s7 = arcCosF<double>(-1);
    double s8 = arcCosF<double>(-0.7071);

    ASSERT_NEAR(s1, 1.5707963267948966, 0.01);
    ASSERT_NEAR(s2, 1.0471975511965979, 0.01);
    ASSERT_NEAR(s3, 0.785407753397449, 0.01);
    ASSERT_NEAR(s4, 0.5236495809318289, 0.01);
    ASSERT_NEAR(s5, 0.0, 0.01);
    ASSERT_NEAR(s6, 2.0943951023931957, 0.1);
    ASSERT_NEAR(s7, 3.141592653589793, 0.1);
    ASSERT_NEAR(s8, 2.356184900192344, 0.1);

}

TEST(TrigTestSuit, TestAtanF){
    float s1 = arcTanF<float>(0);
    double s2 = arcTanF<double>(0.5);
    float s3 = arcTanF<float>(0.7071);
    double s4 = arcTanF<double>(0.8660);
    float s5 = arcTanF<float>(1.f);

    float s6 = arcTanF<float>(-0.5);
    double s7 = arcTanF<double>(-1);
    double s8 = arcTanF<double>(-0.7071);
    float s9 = arcTanF<float>(100000);

    ASSERT_NEAR(s1, 0.0, 0.01);
    ASSERT_NEAR(s2, 0.4636476090008061, 0.01);
    ASSERT_NEAR(s3, 0.6154751878649, 0.01);
    ASSERT_NEAR(s4, 0.7137098623140186, 0.01);
    ASSERT_NEAR(s5, 0.7853981633974483, 0.01);
    ASSERT_NEAR(s6, -0.4636476090008061, 0.1);
    ASSERT_NEAR(s7, -0.7853981633974483, 0.1);
    ASSERT_NEAR(s8, -0.6161415445725856, 0.1);
    ASSERT_NEAR(s9, 1.57078632679489695, 0.1);
}


TEST(TrigTestSuit, TestAtan2F){
    float s1 = arcTan2F<float>(0, 1);
    double s2 = arcTan2F<double>(1.0, 2.0);
    float s3 = arcTan2F<float>(1.0, sqrt(2));
    double s4 = arcTan2F<double>(sqrt(3), 2.0);
    float s5 = arcTan2F<float>(1.f, 1.f);

    float s6 = arcTan2F<float>(-1.f, 2.f);
    double s7 = arcTan2F<double>(-1, 1);
    double s8 = arcTan2F<double>(-1.0, sqrt(2));
    float s9 = arcTan2F<float>(1, 0);

    ASSERT_NEAR(s1, 0.0, 0.01);
    ASSERT_NEAR(s2, 0.4636476090008061, 0.01);
    ASSERT_NEAR(s3, 0.6154751878649, 0.01);
    ASSERT_NEAR(s4, 0.7137098623140186, 0.01);
    ASSERT_NEAR(s5, 0.7853981633974483, 0.01);
    ASSERT_NEAR(s6, -0.4636476090008061, 0.1);
    ASSERT_NEAR(s7, -0.7853981633974483, 0.1);
    ASSERT_NEAR(s8, -0.6161415445725856, 0.1);
    ASSERT_NEAR(s9, 1.57078632679489695, 0.1);
}


TEST(TrigTestSuit, TestSinh){
    float s1 = sinhF<float>(0);
    double s2 = sinhF<double>(M_PI / 6.0);
    float s3 = sinhF<float>(M_PI / 4.0);
    double s4 = sinhF<double>(M_PI / 3.0);
    float s5 = sinhF<float>(M_PI / 2.0);

    float s6 = sinhF<float>(-M_PI / 3.0);
    double s7 = sinhF<double>(2 * M_PI);
    float s8 = sinhF<float>(M_PI);

    ASSERT_NEAR(s1, 0.f, 0.01);
    ASSERT_NEAR(s2, 0.5478534738880397, 0.001);
    ASSERT_NEAR(s3, 0.8686709614860095, 0.001);
    ASSERT_NEAR(s4, 1.249367050524, 0.001);
    ASSERT_NEAR(s5, 2.3012989023072947, 0.001);
    ASSERT_NEAR(s6, -1.249367050524, 0.001);
    ASSERT_NEAR(s7, 267.74489404101644, 0.001);
    ASSERT_NEAR(s8, 11.548739357257748, 0.001);
}


TEST(TrigTestSuit, TestCosh){
    float s1 = coshF<float>(0);
    double s2 = coshF<double>(M_PI / 6.0);
    float s3 = coshF<float>(M_PI / 4.0);
    double s4 = coshF<double>(M_PI / 3.0);
    float s5 = coshF<float>(M_PI / 2.0);

    float s6 = coshF<float>(-M_PI / 3.0);
    double s7 = coshF<double>(2 * M_PI);
    float s8 = coshF<float>(M_PI);

    ASSERT_NEAR(s1, 1.f, 0.01);
    ASSERT_NEAR(s2, 1.1402383210764286, 0.001);
    ASSERT_NEAR(s3, 1.324609089252, 0.001);
    ASSERT_NEAR(s4, 1.600286857702386, 0.001);
    ASSERT_NEAR(s5, 2.5091784786580567, 0.001);
    ASSERT_NEAR(s6, 1.600286857702386, 0.001);
    ASSERT_NEAR(s7, 267.7467614837482, 0.001);
    ASSERT_NEAR(s8, 11.591953275521519, 0.001);
}

TEST(TrigTestSuit, TestTanh){
    float s1 = tanhF<float>(0);
    double s2 = tanhF<double>(M_PI / 6.0);
    float s3 = tanhF<float>(M_PI / 4.0);
    double s4 = tanhF<double>(M_PI / 3.0);
    float s5 = tanhF<float>(M_PI / 2.0);

    float s6 = tanhF<float>(-M_PI / 3.0);
    double s7 = tanhF<double>(2 * M_PI);
    float s8 = tanhF<float>(M_PI);

    ASSERT_NEAR(s1, 0.f, 0.01);
    ASSERT_NEAR(s2, 0.4804727781564516, 0.001);
    ASSERT_NEAR(s3, 0.6557942026326724, 0.001);
    ASSERT_NEAR(s4, 0.7807144353592677, 0.001);
    ASSERT_NEAR(s5, 0.9171523356672744, 0.001);
    ASSERT_NEAR(s6, -0.7807144353592677, 0.001);
    ASSERT_NEAR(s7, 0.9999930253396107, 0.001);
    ASSERT_NEAR(s8, 0.99627207622075, 0.001);
}





