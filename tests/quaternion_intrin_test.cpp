//
// Created by Jason Fedorowich on 2025-01-03.
//

#include "gtest/gtest.h"
#include "odinmath.h"
#include <iostream>

using namespace OdinMath;

TEST(QuaternionFloatTestSuite, RotationMatrix){
    Matrix3Float rotation(0.0, 0.0, 1.0,
                             0.0, 1.0, 0.0,
                             -1.0, 0.0, 0.0);

    QuaternionFloat expQ(0.0,
                            0.7071,
                            0.0,
                            0.7071);

    QuaternionFloat rotQ(rotation);
    EXPECT_NEAR(expQ.getX(), rotQ.getX(), 0.001);
    EXPECT_NEAR(expQ.getY(), rotQ.getY(), 0.001);
    EXPECT_NEAR(expQ.getZ(), rotQ.getZ(), 0.001);
    EXPECT_NEAR(expQ.getW(), rotQ.getW(), 0.001);
    Matrix3Float mm;
    toRotationMatrix(mm, rotQ);


    QuaternionFloat q( 0.7071, 0, 0, 0.7071);
    Matrix3Float R;
    toRotationMatrix(R, q);
    Matrix3Float expR(1.0000, 0.0, 0.0,
                         0.0, -0.0000, -1.0000,
                         0.0, 1.0000, -0.0000);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            EXPECT_NEAR(expR.get(i, j), R.get(i, j), 0.01);
        }
    }

}


TEST(QuaternionFloatTestSuite, AxisAngle){
    Vector3Float axis(1.f, 0.f, 0.f);
    float pi = 3.1415926;
    QuaternionFloat q(pi / 2.f, axis);
    QuaternionFloat expQ(0.7071, 0, 0, 0.7071);
    EXPECT_NEAR(expQ.getX(), q.getX(), 0.01);
    EXPECT_NEAR(expQ.getY(), q.getY(), 0.01);
    EXPECT_NEAR(expQ.getZ(), q.getZ(), 0.01);
    EXPECT_NEAR(expQ.getW(), q.getW(), 0.01);
    std::cout << expQ;
    float angle[4];
    Vector3Float a;
    toAngleAxis(angle, a, expQ);
    std::cout << a;
    float piOver2 = pi / 2.f;
    EXPECT_NEAR(axis.getX(), a.getX(), 0.01);
    EXPECT_NEAR(axis.getY(), a.getY(), 0.01);
    EXPECT_NEAR(axis.getZ(), a.getZ(), 0.01);
    EXPECT_NEAR(piOver2, angle[0], 0.1);

}

TEST(QuaternionFloatTestSuite, RollPitchYaw){
    float yaw = 0.7854;
    float pitch = 0.1;
    float roll = 0.0;
    QuaternionFloat q(roll, pitch, yaw);
    EXPECT_NEAR(-0.0191 , q.getX(), 0.01);
    EXPECT_NEAR(0.0462, q.getY(), 0.01);
    EXPECT_NEAR(0.3822, q.getZ(), 0.01);
    EXPECT_NEAR(0.9227, q.getW(), 0.01);

    float angles[3];
    toRollPitchYaw(angles, q);
    EXPECT_NEAR(roll , angles[0], 0.01);
    EXPECT_NEAR(pitch, angles[1], 0.01);
    EXPECT_NEAR(yaw, angles[2], 0.01);

}

TEST(QuaternionFloatTestSuite, AddSub){
    QuaternionFloat q1(1.0, 2.0, 3.0, 5.0);
    QuaternionFloat q2(2.0, 3.0, 5.0, 10.0);
    QuaternionFloat q3 = q1 + q2;
    QuaternionFloat expAdd(3.0, 5.0, 8.0, 15.0);
    EXPECT_NEAR(expAdd.getX(), q3.getX(), 0.01);
    EXPECT_NEAR(expAdd.getY(), q3.getY(), 0.01);
    EXPECT_NEAR(expAdd.getZ(), q3.getZ(), 0.01);
    EXPECT_NEAR(expAdd.getW(), q3.getW(), 0.01);


    QuaternionFloat expSub(-0.10189, 0.65299, 0.5511, -0.5094);
    QuaternionFloat q4 = q1 - q2;
    EXPECT_NEAR(expSub.getX(), q4.getX(), 0.01);
    EXPECT_NEAR(expSub.getY(), q4.getY(), 0.01);
    EXPECT_NEAR(expSub.getZ(), q4.getZ(), 0.01);
    EXPECT_NEAR(expSub.getW(), q4.getW(), 0.01);
}

TEST(QuaternionFloatTestSuite, Multiplication){
    QuaternionFloat q1(1.0, 2.0, 3.0, 4.0);
    QuaternionFloat q2(1.0, 3.0, 4.0, 2.0);
    QuaternionFloat q3 = q1 * q2;
    QuaternionFloat expQ(5, 15,  23, -11);
    EXPECT_NEAR(expQ.getX(), q3.getX(), 0.01);
    EXPECT_NEAR(expQ.getY(), q3.getY(), 0.01);
    EXPECT_NEAR(expQ.getZ(), q3.getZ(), 0.01);
    EXPECT_NEAR(expQ.getW(), q3.getW(), 0.01);

}