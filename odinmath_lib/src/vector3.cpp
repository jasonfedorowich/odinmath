//
// Created by Jason Fedorowich on 2024-02-03.
//

#include "odinmath.h"
#include "include/vector3.h"


namespace OdinMath {

#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))

    Vector3Float Vector3Float::operator+(const Vector3Float &rhs) {
        FloatVector128 r = add(this->floatVector128, rhs.floatVector128);
        return Vector3Float(r);
    }

    Vector3Float Vector3Float::operator+(Vector3Float &&rhs) {
        FloatVector128 r = add(this->floatVector128, rhs.floatVector128);
        return Vector3Float(r);
    }

    Vector3Float &Vector3Float::operator=(const Vector3Float &v) {
        if (this != &v) {
            this->floatVector128 = v.floatVector128;
        }
        return *this;
    }

    void Vector3Float::operator+=(const Vector3Float &rhs) {
        this->floatVector128 = add(this->floatVector128, rhs.floatVector128);
    }

    void Vector3Float::operator+=(const Vector3Float &&rhs) {
        this->floatVector128 = add(this->floatVector128, rhs.floatVector128);
    }

    void Vector3Float::operator/=(float c) {
        this->floatVector128 = scalarMul(1.f / c, this->floatVector128);
    }

    void Vector3Float::operator*=(float c) {
        this->floatVector128 = scalarMul(c, this->floatVector128);
    }

    Vector3Float Vector3Float::operator*(float c) {
        FloatVector128 r = scalarMul(c, this->floatVector128);
        return Vector3Float(r);
    }

    float Vector3Float::dot(const Vector3Float &rhs) {
        FloatVector128 v = OdinMath::dot(this->floatVector128, rhs.floatVector128);
        return GET_LANE_VECTOR(v, 0);
    }

    Vector3Float Vector3Float::cross(const Vector3Float &rhs) {
        FloatVector128 v = OdinMath::cross3(this->floatVector128, rhs.floatVector128);
        return Vector3Float(v);
    }

    void Vector3Float::getData(float *data) {
        store3(data, this->floatVector128);
    }

    bool Vector3Float::operator==(const Vector3Float &v) const {
        return equals(this->floatVector128, v.floatVector128);
    }

    std::ostream &operator<<(std::ostream &os, const Vector3Float &v) {
        os << '\n' <<"Vector3Float "
           << " X: "<< GET_LANE_VECTOR(v.floatVector128, 0) << " Y: " <<  GET_LANE_VECTOR(v.floatVector128, 1)
           << " Z: " << GET_LANE_VECTOR(v.floatVector128, 2);
        return os;
    }

    Vector3Float Vector3Float::project(const Vector3Float &b) const {
        FloatVector128 ab = OdinMath::dot(this->floatVector128, b.floatVector128);
        FloatVector128 bb = OdinMath::dot(b.floatVector128, b.floatVector128);
        bb = SET_LANE_VECTOR(3, bb, 0.f);
        FloatVector128 t = div(ab, bb);
        return Vector3Float(mul(t, b.floatVector128));
    }


#endif

}