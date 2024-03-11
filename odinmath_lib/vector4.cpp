//
// Created by Jason Fedorowich on 2024-03-02.
//

#include "vector4.h"

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
            this->data[0] = v.data[0];
            this->data[1] = v.data[1];
            this->data[2] = v.data[2];
            this->data[3] = v.data[3];
            this->floatVector128 = load4(v.data);
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
        FloatVector128 v31 = load3(this->data);
        FloatVector128 v32 = load3(rhs.data);
        return Vector4Float(cross3(v31, v32));
    }

    const float *Vector4Float::getData() {
        store4(this->data, this->floatVector128);
        return data;
    }

    const float &Vector4Float::operator[](int idx) const {
        throw UnimplementedException("Override of [] unimplemented for Vector4Float");
    }

    float &Vector4Float::operator[](int idx) {
        throw UnimplementedException("Override of [] unimplemented for Vector4Float");
    }


#endif


}
