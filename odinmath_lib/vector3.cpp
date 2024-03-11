//
// Created by Jason Fedorowich on 2024-02-03.
//

#include "odinmath.h"

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
            this->data[0] = v.data[0];
            this->data[1] = v.data[1];
            this->data[2] = v.data[2];
            this->floatVector128 = load3(this->data);
        }
        return *this;
    }

    void Vector3Float::setX(float x) {
        this->floatVector128 = SET_LANE_VECTOR(x, this->floatVector128, 0);
    }

    void Vector3Float::setY(float y) {
        this->floatVector128 = SET_LANE_VECTOR(y, this->floatVector128, 1);
    }

    void Vector3Float::setZ(float z) {
        this->floatVector128 = SET_LANE_VECTOR(z, this->floatVector128, 2);
    }

    const float &Vector3Float::operator[](int idx) const {
        throw UnimplementedException("Override of [] unimplemented for Vector3Float");
    }

    float &Vector3Float::operator[](int idx) {
        throw UnimplementedException("Override of [] unimplemented for Vector3Float");
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

    const float *Vector3Float::getData() {
        store4(this->data, this->floatVector128);
        return data;
    }

#endif

}