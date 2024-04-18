//
// Created by Jason Fedorowich on 2024-04-14.
//

#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;

TEST(VectorSuiteTest, TestIteration) {
    Vector3<float> v = {1.f, 2.f, 3.f};
    ASSERT_TRUE(v.begin() != v.end());
    float sum = 0;
    for (float ele: v) {
        sum += ele;
    }
    EXPECT_EQ(6.f, sum);
}
