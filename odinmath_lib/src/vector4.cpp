//
// Created by Jason Fedorowich on 2024-03-02.
//

#include "odinmath.h"
#include "include/vector4.h"


namespace OdinMath {

#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))

    void Vector4Float::setX(float x) {
        this->floatVector128 = SET_LANE_VECTOR(x, this->floatVector128, 0);
    }

    void Vector4Float::setY(float y) {
        this->floatVector128 = SET_LANE_VECTOR(y, this->floatVector128, 1);
    }

    void Vector4Float::setZ(float z) {
        this->floatVector128 = SET_LANE_VECTOR(z, this->floatVector128, 2);
    }

    void Vector4Float::setW(float w) {
        this->floatVector128 = SET_LANE_VECTOR(w, this->floatVector128, 3);
    }

    Vector4Float &Vector4Float::operator=(const Vector4Float &v) {
        if (this != &v) {
            this->floatVector128 = v.floatVector128;
        }
        return *this;
    }

    Vector4Float Vector4Float::operator+(const Vector4Float &rhs) {
        FloatVector128 r = add(this->floatVector128, rhs.floatVector128);
        return Vector4Float(r);
    }

    Vector4Float Vector4Float::operator+(Vector4Float &&rhs) {
        FloatVector128 r = add(this->floatVector128, rhs.floatVector128);
        return Vector4Float(r);
    }

    void Vector4Float::operator+=(const Vector4Float &rhs) {
        this->floatVector128 = add(this->floatVector128, rhs.floatVector128);
    }

    void Vector4Float::operator+=(const Vector4Float &&rhs) {
        this->floatVector128 = add(this->floatVector128, rhs.floatVector128);
    }

    void Vector4Float::operator/=(float c) {
        this->floatVector128 = scalarMul(1 / c, this->floatVector128);
    }

    void Vector4Float::operator*=(float c) {
        this->floatVector128 = scalarMul(c, this->floatVector128);
    }

    Vector4Float Vector4Float::operator*(float c) {
        return Vector4Float(scalarMul(c, this->floatVector128));
    }

    float Vector4Float::dot(const Vector4Float &rhs) {
        FloatVector128 vector = OdinMath::dot(this->floatVector128, rhs.floatVector128);
        return GET_LANE_VECTOR(vector, 0);
    }

    Vector4Float Vector4Float::cross(const Vector4Float &rhs) {
        FloatVector128 v31 = zeroLast(this->floatVector128);
        FloatVector128 v32 = zeroLast(rhs.floatVector128);
        return Vector4Float(cross3(v31, v32));
    }

    void Vector4Float::getData(float *data) {
        store4(data, this->floatVector128);
    }

    bool Vector4Float::operator==(const Vector4Float &v) const {
        return equals(this->floatVector128, v.floatVector128);
    }

    Vector4Float Vector4Float::project(const Vector4Float &b) const {
        FloatVector128 ab = OdinMath::dot(this->floatVector128, b.floatVector128);
        FloatVector128 bb = OdinMath::dot(b.floatVector128, b.floatVector128);
        FloatVector128 t = div(ab, bb);
        return Vector4Float(mul(t, b.floatVector128));
    }

    float Vector4Float::length() {
        FloatVector128 v = sqrtF(OdinMath::dot(this->floatVector128, this->floatVector128));
        return GET_LANE_VECTOR(v, 0);
    }

    void Vector4Float::normalize() {
        FloatVector128 v = sqrtF(OdinMath::dot(this->floatVector128, this->floatVector128));
        this->floatVector128 = div(this->floatVector128, v);
    }


#endif


}
