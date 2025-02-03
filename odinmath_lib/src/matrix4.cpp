//
// Created by Jason Fedorowich on 2024-03-14.
//

#include "odinmath.h"
#include "include/matrix4.h"


namespace OdinMath {

    Matrix4Float &Matrix4Float::operator=(const Matrix4Float &rhs) {
        if (this != &rhs) {
            this->floatMatrix128X4 = rhs.floatMatrix128X4;
        }
        return *this;
    }

    Matrix4Float Matrix4Float::operator+(const Matrix4Float &rhs) {
        return Matrix4Float(add(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix4Float Matrix4Float::operator+(const Matrix4Float &&rhs) {
        return Matrix4Float(add(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix4Float Matrix4Float::operator-(const Matrix4Float &rhs) {
        return Matrix4Float(sub(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix4Float Matrix4Float::operator-(const Matrix4Float &&rhs) {
        return Matrix4Float(sub(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix4Float Matrix4Float::operator*(Matrix4Float &rhs) {
        return Matrix4Float(mul(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix4Float Matrix4Float::operator*(Matrix4Float &&rhs) {
        return Matrix4Float(mul(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Vector4Float Matrix4Float::operator*(Vector4Float &v) {
        return Vector4Float(matrixVectorMul(this->floatMatrix128X4, v.getVector()));
    }

    Vector4Float Matrix4Float::operator*(Vector4Float &&v) {
        return Vector4Float(matrixVectorMul(this->floatMatrix128X4, v.getVector()));
    }

    bool Matrix4Float::operator==(const Matrix4Float &rhs) const {
        return (this->floatMatrix128X4 == rhs.floatMatrix128X4);
    }

    float Matrix4Float::det() {
        return GET_LANE_VECTOR(determinant(this->floatMatrix128X4), 0);
    }

    bool Matrix4Float::inverse(Matrix4Float &inv, float eps, float *det) {
        inv.floatMatrix128X4 = OdinMath::inverse(this->floatMatrix128X4, det);
        if (abs(*det) <= eps) {
            return false;
        }
        return true;
    }

    Matrix4Float Matrix4Float::transpose() {
        return Matrix4Float(OdinMath::transpose(this->floatMatrix128X4));
    }

    Matrix4Float Matrix4Float::identity() {
        return {1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f};
    }

    Matrix4Float Matrix4Float::zeros() {
        return {0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f};
    }

    Vector4Float operator*(Vector4Float &v, Matrix4Float &m) {
        return Vector4Float(matrixVectorMul(v.getVector(), m.floatMatrix128X4));
    }

    Vector4Float operator*(Vector4Float &&v, Matrix4Float &&m) {
        return Vector4Float(matrixVectorMul(v.getVector(), m.floatMatrix128X4));
    }

    float Matrix4Float::get(int r, int c) const {
        if (r >= 4 || r < 0) throw InvalidArgument("Invalid row in get matrix4");
        switch (c) {
            case 0:
                return GET_LANE_VECTOR(this->floatMatrix128X4.vectors[r], 0);
            case 1:
                return GET_LANE_VECTOR(this->floatMatrix128X4.vectors[r], 1);
            case 2:
                return GET_LANE_VECTOR(this->floatMatrix128X4.vectors[r], 2);
            case 3:
                return GET_LANE_VECTOR(this->floatMatrix128X4.vectors[r], 3);
            default:
                throw InvalidArgument("Invalid column in get matrix4");
        }
    }

    void Matrix4Float::set(int r, int c, float v) {
        if (r >= 4 || r < 0) throw InvalidArgument("Invalid row in set matrix4");
        switch (c) {
            case 0:
                this->floatMatrix128X4.vectors[r] = SET_LANE_VECTOR(v, this->floatMatrix128X4.vectors[r], 0);
            case 1:
                this->floatMatrix128X4.vectors[r] = SET_LANE_VECTOR(v, this->floatMatrix128X4.vectors[r], 1);
            case 2:
                this->floatMatrix128X4.vectors[r] = SET_LANE_VECTOR(v, this->floatMatrix128X4.vectors[r], 2);
            case 3:
                this->floatMatrix128X4.vectors[r] = SET_LANE_VECTOR(v, this->floatMatrix128X4.vectors[r], 3);
            default:
                throw InvalidArgument("Invalid column in set matrix4");
        }
    }

    Vector4Float Matrix4Float::trace() {
        FloatVector128 t0 = dupX(this->floatMatrix128X4.vectors[0]);
        FloatVector128 t1 = dupY(this->floatMatrix128X4.vectors[1]);
        FloatVector128 t2 = dupZ(this->floatMatrix128X4.vectors[2]);
        FloatVector128 t3 = dupW(this->floatMatrix128X4.vectors[3]);
        return Vector4Float(add(t0, add(t1, add(t2, t3))));
    }

    FloatMatrix128x4 Matrix4Float::to(Matrix4Float &m) {
        return m.floatMatrix128X4;
    }


}
