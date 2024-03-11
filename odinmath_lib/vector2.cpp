//
// Created by Jason Fedorowich on 2024-03-02.
//

#include "odinmath.h"

namespace OdinMath {

#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))

    void Vector2Float::setX(float x) {
        this->floatVector128 = SET_LANE_VECTOR(x, this->floatVector128, 0);
    }

    void Vector2Float::setY(float y) {
        this->floatVector128 = SET_LANE_VECTOR(y, this->floatVector128, 1);
    }

    Vector2Float &Vector2Float::operator=(const Vector2Float &v) {
        if (this != &v) {
            this->data[0] = v.data[0];
            this->data[1] = v.data[1];
            this->floatVector128 = load2(this->data);
        }
        return *this;
    }

    Vector2Float Vector2Float::operator+(const Vector2Float &rhs) {
        FloatVector128 r = add(this->floatVector128, rhs.floatVector128);
        return Vector2Float(r);
    }

    Vector2Float Vector2Float::operator+(Vector2Float &&rhs) {
        FloatVector128 r = add(this->floatVector128, rhs.floatVector128);
        return Vector2Float(r);
    }

    void Vector2Float::operator+=(const Vector2Float &rhs) {
        this->floatVector128 = add(this->floatVector128, rhs.floatVector128);
    }

    void Vector2Float::operator+=(const Vector2Float &&rhs) {
        this->floatVector128 = add(this->floatVector128, rhs.floatVector128);
    }

    void Vector2Float::operator/=(float c) {
        this->floatVector128 = scalarMul(1.f / c, this->floatVector128);
    }

    void Vector2Float::operator*=(float c) {
        this->floatVector128 = scalarMul(c, this->floatVector128);
    }

    Vector2Float Vector2Float::operator*(float c) {
        FloatVector128 r = scalarMul(c, this->floatVector128);
        return Vector2Float(r);
    }

    float Vector2Float::dot(const Vector2Float &rhs) {
        FloatVector128 v = OdinMath::dot(this->floatVector128, rhs.floatVector128);
        return GET_LANE_VECTOR(v, 0);
    }

    const float &Vector2Float::operator[](int idx) const {
        throw UnimplementedException("Override of [] unimplemented for Vector2Float");
    }

    float &Vector2Float::operator[](int idx) {
        throw UnimplementedException("Override of [] unimplemented for Vector2Float");
    }

    const float *Vector2Float::getData() {
        store2(this->data, this->floatVector128);
        return data;
    }

#endif


}
