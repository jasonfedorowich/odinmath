//
// Created by Jason Fedorowich on 2024-04-14.
//

#include "gtest/gtest.h"
#include "odinmath.h"

using namespace OdinMath;

TEST(MatrixtestSuite, TestIteration) {
    Matrix3<float> m = {1, 2, 3,
                        4, 5, 6,
                        7, 8, 9};

    ASSERT_TRUE(m.begin() != m.end());
    float sum = 0;
    auto it = m.begin();

    for (Vector<3, float> v: m) {
        for(float ele: v){
            sum += ele;
        }
    }
    EXPECT_EQ(45.f, sum);
}
