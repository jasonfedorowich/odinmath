//
// Created by Jason Fedorowich on 2024-03-02.
//

#include "odinmath.h"
#include "vector2.h"


namespace OdinMath {

#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))

    Vector2Float &Vector2Float::operator=(const Vector2Float &v) {
        if (this != &v) {
            this->floatVector128 = v.floatVector128;
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

    void Vector2Float::getData(float *data) {
        store3(data, this->floatVector128);
    }


#endif


}
