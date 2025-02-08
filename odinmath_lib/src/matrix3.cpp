//
// Created by Jason Fedorowich on 2024-03-31.
//

#include "odinmath.h"
#include "include/matrix3.h"


namespace OdinMath {

    float Matrix3Float::get(int r, int c) const {
        if (r >= 3 || r < 0) throw InvalidArgument("Invalid row in get matrix3");
        switch (c) {
            case 0:
                return GET_LANE_VECTOR(this->floatMatrix128X4.vectors[r], 0);
            case 1:
                return GET_LANE_VECTOR(this->floatMatrix128X4.vectors[r], 1);
            case 2:
                return GET_LANE_VECTOR(this->floatMatrix128X4.vectors[r], 2);
            default:
                throw InvalidArgument("Invalid column in get matrix3");
        }
    }

    void Matrix3Float::set(int r, int c, float v) {
        if (r >= 3 || r < 0) throw InvalidArgument("Invalid row in set matrix4");
        switch (c) {
            case 0:
                this->floatMatrix128X4.vectors[r] = SET_LANE_VECTOR(v, this->floatMatrix128X4.vectors[r], 0);
            case 1:
                this->floatMatrix128X4.vectors[r] = SET_LANE_VECTOR(v, this->floatMatrix128X4.vectors[r], 1);
            case 2:
                this->floatMatrix128X4.vectors[r] = SET_LANE_VECTOR(v, this->floatMatrix128X4.vectors[r], 2);
            default:
                throw InvalidArgument("Invalid column in set matrix4");
        }
    }

    Matrix3Float &Matrix3Float::operator=(const Matrix3Float &rhs) {
        if (this != &rhs) {
            this->floatMatrix128X4 = rhs.floatMatrix128X4;
        }
        return *this;
    }

    Matrix3Float Matrix3Float::operator+(const Matrix3Float &rhs) {
        return Matrix3Float(add(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix3Float Matrix3Float::operator+(const Matrix3Float &&rhs) {
        return Matrix3Float(add(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix3Float Matrix3Float::operator-(const Matrix3Float &rhs) {
        return Matrix3Float(sub(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix3Float Matrix3Float::operator-(const Matrix3Float &&rhs) {
        return Matrix3Float(sub(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix3Float Matrix3Float::operator*(Matrix3Float &rhs) {
        return Matrix3Float(mul(this->floatMatrix128X4, rhs.floatMatrix128X4));

    }

    Matrix3Float Matrix3Float::operator*(Matrix3Float &&rhs) {
        return Matrix3Float(mul(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Vector3Float Matrix3Float::operator*(Vector3Float &v) {
        return Vector3Float(matrixVectorMul(this->floatMatrix128X4, v.getVector()));

    }

    Vector3Float Matrix3Float::operator*(Vector3Float &&v) {
        return Vector3Float(matrixVectorMul(this->floatMatrix128X4, v.getVector()));
    }

    bool Matrix3Float::operator==(const Matrix3Float &rhs) const {

        return (this->floatMatrix128X4 == rhs.floatMatrix128X4);
    }

    float Matrix3Float::det() {
        return GET_LANE_VECTOR(determinant(this->floatMatrix128X4), 0);
    }

    bool Matrix3Float::inverse(Matrix3Float &inv, float eps, float *det) {
        inv.floatMatrix128X4 = OdinMath::inverse(this->floatMatrix128X4, det);
        if (abs(*det) <= eps) {
            return false;
        }
        return true;
    }


    Matrix3Float Matrix3Float::identity() {
        return {1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                0.f, 0.f, 1.f};
    }

    Matrix3Float Matrix3Float::zeros() {
        return {0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f};
    }

    Vector3Float operator*(Vector3Float &v, Matrix3Float &m) {
        return Vector3Float(matrixVectorMul(v.getVector(), m.floatMatrix128X4));
    }

    Vector3Float operator*(Vector3Float &&v, Matrix3Float &&m) {
        return Vector3Float(matrixVectorMul(v.getVector(), m.floatMatrix128X4));
    }

    void Matrix3Float::load(FloatMatrix128x4& m) {
        this->floatMatrix128X4 = OdinMath::clear3(m);
    }

    void Matrix3Float::load(FloatMatrix128x4 &&m) {
        this->floatMatrix128X4 = OdinMath::clear3(m);
    }

    Vector4Float Matrix3Float::trace() {
        FloatVector128 t0 = dupX(this->floatMatrix128X4.vectors[0]);
        FloatVector128 t1 = dupY(this->floatMatrix128X4.vectors[1]);
        FloatVector128 t2 = dupZ(this->floatMatrix128X4.vectors[2]);
        FloatVector128 t3 = zero.v;
        //todo check this
        return Vector4Float(add(t0, add(t1, add(t2, t3))));
    }

    Matrix3Float Matrix3Float::transpose() {
        return Matrix3Float(OdinMath::transpose(this->floatMatrix128X4));

    }

}
