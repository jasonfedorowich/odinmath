//
// Created by Jason Fedorowich on 2024-04-20.
//

#ifndef ODINMATH_MATRIX2_H
#define ODINMATH_MATRIX2_H

#include "odinmath.h"

namespace OdinMath {

    template<typename real>
    class Matrix2 : public Matrix<2, 2, real> {
    public:
        Matrix2(real _11, real _12,
                real _21, real _22) {

            this->mat[0][0] = _11;
            this->mat[0][1] = _12;

            this->mat[1][0] = _21;
            this->mat[1][1] = _22;

        }

        Matrix2(Matrix2<real> &mat) {
            *this = mat;
        }

        Matrix2() : Matrix2((real) 0.0, (real) 0.0,
                            (real) 0.0, (real) 0.0) {}

        virtual ~Matrix2() = default;

        Matrix2<real> &operator=(const Matrix2<real> &rhs);

        Matrix2<real> operator+(const Matrix2<real> &rhs);

        Matrix2<real> operator+(const Matrix2<real> &&rhs);

        Matrix2<real> operator-(const Matrix2<real> &rhs);

        Matrix2<real> operator-(const Matrix2<real> &&rhs);

        Matrix2<real> operator*(Matrix2<real> &rhs);

        Matrix2<real> operator*(Matrix2<real> &&rhs);

        Vector2<real> operator*(Vector2<real> &v);

        Vector2<real> operator*(Vector2<real> &&v);

        bool operator==(const Matrix2<real> &rhs) const;

        real det();

        /*Method returns true if Matrix is invertible argument `inv` holds in the inverse matrix if invertible
         * argument `eps` matrix is invertible determinant is greater than `eps` due to rounding errors
         * argument `det` holds the result of the determinant*/
        bool inverse(Matrix2<real> &inv, real eps, real *det);

        Matrix2<real> transpose();

        static Matrix2<real> identity();

        static Matrix2<real> zeros();
    };

#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))

    class Matrix2Float : Matrix4Float {
    public:
        Matrix2Float(float _11, float _12,
                     float _21, float _22) {
            float mat[2][2];
            mat[0][0] = _11;
            mat[0][1] = _12;

            mat[1][0] = _21;
            mat[1][1] = _22;

            this->floatMatrix128X4 = FloatMatrix128x4(mat);
        }

        Matrix2Float(Matrix2Float &mat) {
            *this = mat;
        }

        Matrix2Float() {}

        explicit Matrix2Float(FloatMatrix128x4 &floatMatrix128X4) : Matrix4Float() {
            this->floatMatrix128X4 = OdinMath::clear2(floatMatrix128X4);
        }

        explicit Matrix2Float(FloatMatrix128x4 &&floatMatrix128X4) : Matrix4Float() {
            this->floatMatrix128X4 = OdinMath::clear2(floatMatrix128X4);
        }

        ~Matrix2Float() override = default;

        float get(int r, int c) const override;

        void set(int r, int c, float v) override;

        Matrix2Float &operator=(const Matrix2Float &rhs);

        Matrix2Float operator+(const Matrix2Float &rhs);

        Matrix2Float operator+(const Matrix2Float &&rhs);

        Matrix2Float operator-(const Matrix2Float &rhs);

        Matrix2Float operator-(const Matrix2Float &&rhs);

        Matrix2Float operator*(Matrix2Float &rhs);

        Matrix2Float operator*(Matrix2Float &&rhs);

        Vector2Float operator*(Vector2Float &v);

        Vector2Float operator*(Vector2Float &&v);

        bool operator==(const Matrix2Float &rhs) const;

        float det() override;

        /*Method returns true if Matrix is invertible argument `inv` holds in the inverse matrix if invertible
         * argument `eps` matrix is invertible determinant is greater than `eps` due to rounding errors
         * argument `det` holds the result of the determinant*/
        bool inverse(Matrix2Float &inv, float eps, float *det);

        Matrix2Float transpose();

        static Matrix2Float identity();

        static Matrix2Float zeros();

        friend Vector2Float operator*(Vector2Float &v, Matrix2Float &m);

        friend Vector2Float operator*(Vector2Float &&v, Matrix2Float &&m);


    };

#endif

    template<typename real>
    inline Matrix2<real> operator*(real c, Matrix2<real> &m) {
        return Matrix2<real>(c * m(0, 0), c * m(0, 1),
                             c * m(1, 0), c * m(1, 1));
    }

    template<typename real>
    inline Matrix2<real> operator*(real c, Matrix2<real> &&m) {
        return Matrix2<real>(c * m(0, 0), c * m(0, 1),
                             c * m(1, 0), c * m(1, 1));
    }

    template<typename real>
    inline Vector2<real> operator*(Vector2<real> &v, Matrix2<real> &m) {
        return Vector2<real>(
                v[0] * m(0, 0) + v[1] * m(1, 0),
                v[0] * m(0, 1) + v[1] * m(1, 1)
        );
    }

    template<typename real>
    inline Vector2<real> operator*(Vector2<real> &&v, Matrix2<real> &m) {
        return Vector2<real>(
                v[0] * m(0, 0) + v[1] * m(1, 0),
                v[0] * m(0, 1) + v[1] * m(1, 1)
        );
    }


    template<typename real>
    Matrix2<real> Matrix2<real>::zeros() {
        return Matrix2<real>();
    }

    template<typename real>
    Matrix2<real> Matrix2<real>::identity() {
        return Matrix2<real>((real) 1.f, (real) 0.f,
                             (real) 0.f, (real) 1.f);
    }

    template<typename real>
    Matrix2<real> Matrix2<real>::transpose() {
        return Matrix2<real>(this->mat[0][0], this->mat[1][0],
                             this->mat[0][1], this->mat[1][1]);
    }

    template<typename real>
    bool Matrix2<real>::inverse(Matrix2<real> &inv, real eps, real *det) {
        real tmp[12] = {0}; /* temp array for pairs */
        real src[2][2]; /* array of transpose source matrix */
        real d; /* determinant */
        /* transpose matrix */
        for (int i = 0; i < 2; i++) {
            src[i][0] = (*this)(0, i);
            src[i][1] = (*this)(1, i);
        }
        /* calculate pairs for first 8 elements (cofactors) */
        tmp[0] = 1;
        tmp[2] = 0;
        tmp[6] = 0;
        /* calculate first 8 elements (cofactors) */

        inv(0, 0) = tmp[0] * src[1][1];
        inv(0, 0) -= tmp[1] * src[1][1];
        inv(0, 1) = tmp[1] * src[1][0];
        inv(0, 1) -= tmp[0] * src[1][0];
        inv(1, 0) = tmp[1] * src[0][1];
        inv(1, 0) -= tmp[0] * src[0][1];
        inv(1, 1) = tmp[0] * src[0][0];
        inv(1, 1) -= tmp[1] * src[0][0];

        /* calculate pairs for second 8 elements (cofactors) */

        tmp[10] = src[0][0] * src[1][1];
        tmp[11] = src[0][1] * src[1][0];

        /* calculate determinant */
        d = src[0][0] * inv(0, 0) + src[0][1] * inv(0, 1);
        if (abs(d) <= eps)
            return false;

        /* calculate matrix inverse */
        real dtmp = (real) 1.0 / d;

        for (int j = 0; j < 2; j++) {
            inv(j, 0) *= dtmp;
            inv(j, 1) *= dtmp;
        }

        if (det != nullptr)
            *det = d;

        return true;
    }

    template<typename real>
    real Matrix2<real>::det() {
        real t1 = this->mat[0][0] * this->mat[1][1];
        real t2 = this->mat[0][1] * this->mat[1][0];
        return t1 - t2;
    }

    template<typename real>
    bool Matrix2<real>::operator==(const Matrix2<real> &rhs) const {
        return (this->mat[0][0] == rhs(0, 0) && this->mat[0][1] == rhs(0, 1) &&
                this->mat[1][0] == rhs(1, 0) && this->mat[1][1] == rhs(1, 1));
    }

    template<typename real>
    Vector2<real> Matrix2<real>::operator*(Vector2<real> &&v) {
        return Vector2<real>(this->mat[0][0] * v[0] + this->mat[0][1] * v[1],
                             this->mat[1][0] * v[0] + this->mat[1][1] * v[1]);
    }

    template<typename real>
    Vector2<real> Matrix2<real>::operator*(Vector2<real> &v) {
        return Vector2<real>(this->mat[0][0] * v[0] + this->mat[0][1] * v[1],
                             this->mat[1][0] * v[0] + this->mat[1][1] * v[1]);
    }

    template<typename real>
    Matrix2<real> Matrix2<real>::operator*(Matrix2<real> &&rhs) {
        real _11 = this->mat[0][0] * rhs(0, 0) + this->mat[0][1] * rhs(1, 0);
        real _12 = this->mat[0][0] * rhs(0, 1) + this->mat[0][1] * rhs(1, 1);

        real _21 = this->mat[1][0] * rhs(0, 0) + this->mat[1][1] * rhs(1, 0);
        real _22 = this->mat[1][0] * rhs(0, 1) + this->mat[1][1] * rhs(1, 1);

        return Matrix2<real>(_11, _12,
                             _21, _22);
    }

    template<typename real>
    Matrix2<real> Matrix2<real>::operator*(Matrix2<real> &rhs) {
        real _11 = this->mat[0][0] * rhs(0, 0) + this->mat[0][1] * rhs(1, 0);
        real _12 = this->mat[0][0] * rhs(0, 1) + this->mat[0][1] * rhs(1, 1);

        real _21 = this->mat[1][0] * rhs(0, 0) + this->mat[1][1] * rhs(1, 0);
        real _22 = this->mat[1][0] * rhs(0, 1) + this->mat[1][1] * rhs(1, 1);

        return Matrix2<real>(_11, _12,
                             _21, _22);
    }

    template<typename real>
    Matrix2<real> Matrix2<real>::operator-(const Matrix2<real> &&rhs) {
        return Matrix2<real>(this->mat[0][0] - rhs(0, 0), this->mat[0][1] - rhs(0, 1),
                             this->mat[1][0] - rhs(1, 0), this->mat[1][1] - rhs(1, 1));
    }

    template<typename real>
    Matrix2<real> Matrix2<real>::operator-(const Matrix2<real> &rhs) {
        return Matrix2<real>(this->mat[0][0] - rhs(0, 0), this->mat[0][1] - rhs(0, 1),
                             this->mat[1][0] - rhs(1, 0), this->mat[1][1] - rhs(1, 1));
    }

    template<typename real>
    Matrix2<real> Matrix2<real>::operator+(const Matrix2<real> &&rhs) {
        return Matrix2<real>(this->mat[0][0] + rhs(0, 0), this->mat[0][1] + rhs(0, 1),
                             this->mat[1][0] + rhs(1, 0), this->mat[1][1] + rhs(1, 1));
    }

    template<typename real>
    Matrix2<real> Matrix2<real>::operator+(const Matrix2<real> &rhs) {
        return Matrix2<real>(this->mat[0][0] + rhs(0, 0), this->mat[0][1] + rhs(0, 1),
                             this->mat[1][0] + rhs(1, 0), this->mat[1][1] + rhs(1, 1));
    }

    template<typename real>
    Matrix2<real> &Matrix2<real>::operator=(const Matrix2<real> &rhs) {
        if (this != &rhs) {
            this->mat[0][0] = rhs(0, 0);
            this->mat[0][1] = rhs(0, 1);
            this->mat[1][0] = rhs(1, 0);
            this->mat[1][1] = rhs(1, 1);
        }
        return *this;
    }
}


#endif //ODINMATH_MATRIX2_H
