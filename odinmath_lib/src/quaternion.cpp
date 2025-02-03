//
// Created by Jason Fedorowich on 2024-06-07.
//

#include "include/quaternion.h"

namespace OdinMath{

    void QuaternionFloat::normalize() {
        FloatVector128 l = ::OdinMath::length(this->floatVector128, this->floatVector128);
        FloatVector128 invL = invert(l);
        this->floatVector128 = mul(invL, this->floatVector128);
    }

    float QuaternionFloat::length() {
        FloatVector128 l = ::OdinMath::length(this->floatVector128, this->floatVector128);
        return GET_LANE_VECTOR(l, 0);
    }

    QuaternionFloat QuaternionFloat::conjugate() {
        VectorFloat32 m1 = {{-1.f, -1.f, -1.f, 1.f}};
        FloatVector128 r = ::OdinMath::mul(m1.v, this->floatVector128);
        return {r};
    }

    bool QuaternionFloat::isNormalized(float &length, float eps) {
        FloatVector128 l = ::OdinMath::length(this->floatVector128, this->floatVector128);
        IntegerVector128 c1 = greaterThanOrEqual(duplicate(eps), l);
        length = GET_LANE_VECTOR(l, 0);
        return GET_LANE_UINT_VECTOR(c1, 0) != 0;
    }

    QuaternionFloat QuaternionFloat::operator*() {
        return conjugate();
    }

    QuaternionFloat QuaternionFloat::operator+(const QuaternionFloat &rhs) {
        return QuaternionFloat(add(this->floatVector128, rhs.floatVector128));
    }

    QuaternionFloat QuaternionFloat::operator-(const QuaternionFloat &rhs) {
        return QuaternionFloat(sub(this->floatVector128, rhs.floatVector128));
    }

    QuaternionFloat QuaternionFloat::operator*(const QuaternionFloat &rhs) {
        FloatVector128 t1 = mul(dupW(this->floatVector128), rhs.floatVector128);

        VectorFloat32 m1 = {{1.f, -1.f, 1.f, -1.f}};
        FloatVector128 v1 = COPY_LANE(rhs.floatVector128, 0, rhs.floatVector128, 3);
        v1 = COPY_LANE(v1, 1, rhs.floatVector128, 2);
        v1 = COPY_LANE(v1, 2, rhs.floatVector128, 1);
        v1 = COPY_LANE(v1, 3, rhs.floatVector128, 0);
        FloatVector128 t2 = mul(m1.v, dupX(this->floatVector128));
        t2 = mul(t2, v1);

        VectorFloat32 m2 = {{1.f, 1.f, -1.f, -1.f}};
        FloatVector128 v2 = COPY_LANE(rhs.floatVector128, 0, rhs.floatVector128, 2);
        v2 = COPY_LANE(v2, 1, rhs.floatVector128, 3);
        v2 = COPY_LANE(v2, 2, rhs.floatVector128, 0);
        v2 = COPY_LANE(v2, 3, rhs.floatVector128, 1);
        FloatVector128 t3 = mul(m2.v, dupY(this->floatVector128));
        t3 = mul(t3, v2);

        VectorFloat32 m3 = {{-1.f, 1.f, 1.f, -1.f}};
        FloatVector128 v3 = COPY_LANE(rhs.floatVector128, 0, rhs.floatVector128, 1);
        v3 = COPY_LANE(v3, 1, rhs.floatVector128, 0);
        v3 = COPY_LANE(v3, 2, rhs.floatVector128, 3);
        v3 = COPY_LANE(v3, 3, rhs.floatVector128, 2);
        FloatVector128 t4 = mul(m3.v, dupZ(this->floatVector128));
        t4 = mul(t4, v3);

        t1 = add(t1, add(t2, add(t3, t4)));
        return QuaternionFloat(t1);
    }

    QuaternionFloat &QuaternionFloat::operator=(const QuaternionFloat &rhs) {
        if(this != &rhs){
            this->floatVector128 = rhs.floatVector128;
        }
        return *this;
    }

    bool QuaternionFloat::operator==(const QuaternionFloat &rhs) const {
        return equals(this->floatVector128, rhs.floatVector128);
    }

    void QuaternionFloat::setX(float x) {
        this->floatVector128 = SET_LANE_VECTOR(x, this->floatVector128, 0);
    }

    void QuaternionFloat::setY(float y) {
        this->floatVector128 = SET_LANE_VECTOR(y, this->floatVector128, 1);
    }

    void QuaternionFloat::setZ(float z) {
        this->floatVector128 = SET_LANE_VECTOR(z, this->floatVector128, 2);
    }

    void QuaternionFloat::setW(float w) {
        this->floatVector128 = SET_LANE_VECTOR(w, this->floatVector128, 3);
    }
}


