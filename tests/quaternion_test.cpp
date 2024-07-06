//
// Created by Jason Fedorowich on 2024-06-11.
//


#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;

TEST(QuaternionTestSuite, RotationMatrix){
    Matrix3<double> rotation(0.0, 0.0, 1.0,
                             0.0, 1.0, 0.0,
                             -1.0, 0.0, 0.0);
    Quaternion<double> expQ(0.0,
                            0.7071,
                            0.0,
                            0.7071);

    Quaternion<double> rotQ(rotation);
    EXPECT_NEAR(expQ[0], rotQ[0], 0.001);
    EXPECT_NEAR(expQ[1], rotQ[1], 0.001);
    EXPECT_NEAR(expQ[2], rotQ[2], 0.001);
    EXPECT_NEAR(expQ[3], rotQ[3], 0.001);
    Matrix3<double> DD;
    toRotationMatrix(DD, rotQ);

    Quaternion<double> q( 0.7071, 0, 0, 0.7071);
    Matrix3<double> R;
    toRotationMatrix(R, q);
    Matrix3<double> expR(1.0000, 0.0, 0.0,
                         0.0, -0.0000, -1.0000,
                         0.0, 1.0000, -0.0000);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            EXPECT_NEAR(expR(i, j), R(i, j), 0.01);
        }
    }

}


TEST(QuaternionTestSuite, AxisAngle){
    Vector3<float> axis(1.f, 0.f, 0.f);
    float pi = 3.1415926;
    Quaternion<float> q(pi / 2.f, axis);
    Quaternion<float> expQ(0.7071, 0, 0, 0.7071);
    EXPECT_NEAR(expQ[0], q[0], 0.01);
    EXPECT_NEAR(expQ[1], q[1], 0.01);
    EXPECT_NEAR(expQ[2], q[2], 0.01);
    EXPECT_NEAR(expQ[3], q[3], 0.01);

    float angle;
    Vector3<float> a;
    toAngleAxis(angle, a, expQ);
    EXPECT_NEAR(axis[0], a[0], 0.01);
    EXPECT_NEAR(axis[1], a[1], 0.01);
    EXPECT_NEAR(axis[2], a[2], 0.01);
    EXPECT_NEAR(pi / 2.f, angle, 0.01);

}

TEST(QuaternionTestSuite, RollPitchYaw){
    double yaw = 0.7854;
    double pitch = 0.1;
    double roll = 0.0;
    Quaternion<double> q(roll, pitch, yaw);
    EXPECT_NEAR(-0.0191 , q[0], 0.01);
    EXPECT_NEAR(0.0462, q[1], 0.01);
    EXPECT_NEAR(0.3822, q[2], 0.01);
    EXPECT_NEAR(0.9227, q[3], 0.01);

    double rollActual;
    double pitchActual;
    double yawActual;
    toRollPitchYaw(rollActual, pitchActual, yawActual, q);
    EXPECT_NEAR(roll , rollActual, 0.01);
    EXPECT_NEAR(pitch, pitchActual, 0.01);
    EXPECT_NEAR(yaw, yawActual, 0.01);

}

TEST(QuaternionTestSuite, AddSub){
    Quaternion<double> q1(1.0, 2.0, 3.0, 5.0);
    Quaternion<double> q2(2.0, 3.0, 5.0, 10.0);
    Quaternion<double> expAdd(3.0, 5.0, 8.0, 15.0);
    EXPECT_EQ(expAdd, q1 + q2);

    Quaternion<double> expSub(-1.0, -1.0, -2.0, -5.0);
    EXPECT_EQ(expSub, q1 - q2);
}

TEST(QuaternionTestSuite, Multiplication){
    Quaternion<double> q1(1.0, 2.0, 3.0, 4.0);
    Quaternion<double> q2(1.0, 3.0, 4.0, 2.0);
    Quaternion<double> q3 = q1 * q2;
    Quaternion<double> expQ(5,  15,  23, -11);
    EXPECT_NEAR(expQ[0], q3[0], 0.01);
    EXPECT_NEAR(expQ[1], q3[1], 0.01);
    EXPECT_NEAR(expQ[2], q3[2], 0.01);
    EXPECT_NEAR(expQ[3], q3[3], 0.01);

}