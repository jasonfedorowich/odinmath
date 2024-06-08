//
// Created by Jason Fedorowich on 2024-04-20.
//

#include "include/matrix2.h"

namespace OdinMath{

    float Matrix2Float::get(int r, int c) const {
        if(r >= 2 || r < 0) throw InvalidArgument("Invalid row in get matrix2");
        switch(c){
            case 0:
                return GET_LANE_VECTOR(this->floatMatrix128X4.vectors[r], 0);
            case 1:
                return GET_LANE_VECTOR(this->floatMatrix128X4.vectors[r], 1);
            default:
                throw InvalidArgument("Invalid column in get matrix2");
        }
    }

    void Matrix2Float::set(int r, int c, float v) {
        if(r >= 2 || r < 0) throw InvalidArgument("Invalid row in set matrix4");
        switch(c){
            case 0:
                this->floatMatrix128X4.vectors[r] = SET_LANE_VECTOR(v, this->floatMatrix128X4.vectors[r], 0);
            case 1:
                this->floatMatrix128X4.vectors[r] = SET_LANE_VECTOR(v, this->floatMatrix128X4.vectors[r], 1);
            default:
                throw InvalidArgument("Invalid column in set matrix4");
        }
    }

    Matrix2Float &Matrix2Float::operator=(const Matrix2Float &rhs) {
        if(this != &rhs){
            this->floatMatrix128X4 = rhs.floatMatrix128X4;
        }
        return *this;
    }

    Matrix2Float Matrix2Float::operator+(const Matrix2Float &rhs) {
        return Matrix2Float(add(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix2Float Matrix2Float::operator+(const Matrix2Float &&rhs) {
        return Matrix2Float(add(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix2Float Matrix2Float::operator-(const Matrix2Float &rhs) {
        return Matrix2Float(sub(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix2Float Matrix2Float::operator-(const Matrix2Float &&rhs) {
        return Matrix2Float(sub(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix2Float Matrix2Float::operator*(Matrix2Float &rhs) {
        return Matrix2Float(mul(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Matrix2Float Matrix2Float::operator*(Matrix2Float &&rhs) {
        return Matrix2Float(mul(this->floatMatrix128X4, rhs.floatMatrix128X4));
    }

    Vector2Float Matrix2Float::operator*(Vector2Float &v) {
        return Vector2Float(matrixVectorMul(this->floatMatrix128X4, v.getVector()));
    }

    Vector2Float Matrix2Float::operator*(Vector2Float &&v) {
        return Vector2Float(matrixVectorMul(this->floatMatrix128X4, v.getVector()));
    }

    bool Matrix2Float::operator==(const Matrix2Float &rhs) const {
        return (this->floatMatrix128X4 == rhs.floatMatrix128X4);
    }

    float Matrix2Float::det() {
        return GET_LANE_VECTOR(determinant(this->floatMatrix128X4), 0);
    }

    bool Matrix2Float::inverse(Matrix2Float &inv, float eps, float *det) {
        inv.floatMatrix128X4 = OdinMath::inverse(this->floatMatrix128X4, det);
        if(abs(*det) <= eps){
            return false;
        }
        return true;
    }

    Matrix2Float Matrix2Float::transpose() {
        return Matrix2Float(OdinMath::transpose(this->floatMatrix128X4));
    }

    Matrix2Float Matrix2Float::identity() {
        return {1.f, 0.f,
                0.f, 1.f};
    }

    Matrix2Float Matrix2Float::zeros() {
        return {0.f, 0.f,
                0.f, 0.f};
    }

    Vector2Float operator*(Vector2Float &v, Matrix2Float &m) {
        return Vector2Float(matrixVectorMul(v.getVector(), m.floatMatrix128X4));
    }

    Vector2Float operator*(Vector2Float &&v, Matrix2Float &&m) {
        return Vector2Float(matrixVectorMul(v.getVector(), m.floatMatrix128X4));
    }

}
