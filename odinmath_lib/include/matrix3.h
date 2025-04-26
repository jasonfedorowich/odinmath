//
// Created by Jason Fedorowich on 2024-03-31.
//

#ifndef ODINMATH_MATRIX3_H
#define ODINMATH_MATRIX3_H

#include "odinmath.h"
#include <ostream>

namespace OdinMath {
    template<typename real>
    class Matrix3 : public Matrix<3, 3, real> {
    public:
        Matrix3(real _11, real _12, real _13,
                real _21, real _22, real _23,
                real _31, real _32, real _33) {

            this->mat[0][0] = _11;
            this->mat[0][1] = _12;
            this->mat[0][2] = _13;

            this->mat[1][0] = _21;
            this->mat[1][1] = _22;
            this->mat[1][2] = _23;

            this->mat[2][0] = _31;
            this->mat[2][1] = _32;
            this->mat[2][2] = _33;
        }

        Matrix3(Matrix3<real> &mat) {
            *this = mat;
        }

        Matrix3() : Matrix3((real) 0.0, (real) 0.0, (real) 0.0,
                            (real) 0.0, (real) 0.0, (real) 0.0,
                            (real) 0.0, (real) 0.0, (real) 0.0) {}

        virtual ~Matrix3() = default;

        Matrix3<real> &operator=(const Matrix3<real> &rhs);

        Matrix3<real> operator+(const Matrix3<real> &rhs);

        Matrix3<real> operator+(const Matrix3<real> &&rhs);

        Matrix3<real> operator-(const Matrix3<real> &rhs);

        Matrix3<real> operator-(const Matrix3<real> &&rhs);

        Matrix3<real> operator*(Matrix3<real> &rhs);

        Matrix3<real> operator*(Matrix3<real> &&rhs);

        Vector3<real> operator*(Vector3<real> &v);

        Vector3<real> operator*(Vector3<real> &&v);

        bool operator==(const Matrix3<real> &rhs) const;

        Vector3<real> col(int c);

        void col(int c, Vector3<real>& v);

        Vector3<real> row(int r);

        void row(int r, Vector3<real>& v);

        real det();

        real trace();

        /*Method returns true if Matrix is invertible argument `inv` holds in the inverse matrix if invertible
         * argument `eps` matrix is invertible determinant is greater than `eps` due to rounding errors
         * argument `det` holds the result of the determinant*/
        bool inverse(Matrix3<real> &inv, real eps, real *det);

        bool isUpperTriangular(real eps);

        Matrix3<real> transpose();

        static Matrix3<real> identity();

        static Matrix3<real> zeros();

    };



#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))

    class Matrix3Float : public Matrix4Float {
    public:
        Matrix3Float(float _11, float _12, float _13,
                     float _21, float _22, float _23,
                     float _31, float _32, float _33) {
            float mat[3][3];
            mat[0][0] = _11;
            mat[0][1] = _12;
            mat[0][2] = _13;

            mat[1][0] = _21;
            mat[1][1] = _22;
            mat[1][2] = _23;

            mat[2][0] = _31;
            mat[2][1] = _32;
            mat[2][2] = _33;

            this->floatMatrix128X4 = FloatMatrix128x4(mat);
        }

        Matrix3Float(Matrix3Float &mat) {
            *this = mat;
        }

        Matrix3Float() {}

        explicit Matrix3Float(FloatMatrix128x4 &floatMatrix128X4) : Matrix4Float() {
            this->floatMatrix128X4 = OdinMath::clear3(floatMatrix128X4);
        }

        explicit Matrix3Float(FloatMatrix128x4 &&floatMatrix128X4) : Matrix4Float() {
            this->floatMatrix128X4 = OdinMath::clear3(floatMatrix128X4);
        }

        ~Matrix3Float() override = default;

        float get(int r, int c) const override;

        void set(int r, int c, float v) override;

        Matrix3Float &operator=(const Matrix3Float &rhs);

        virtual Matrix3Float operator+(const Matrix3Float &rhs);

        virtual Matrix3Float operator+(const Matrix3Float &&rhs);

        virtual Matrix3Float operator-(const Matrix3Float &rhs);

        virtual Matrix3Float operator-(const Matrix3Float &&rhs);

        virtual Matrix3Float operator*(Matrix3Float &rhs);

        virtual Matrix3Float operator*(Matrix3Float &&rhs);

        virtual Vector3Float operator*(Vector3Float &v);

        virtual Vector3Float operator*(Vector3Float &&v);

        bool operator==(const Matrix3Float &rhs) const;

        float det() override;

        Vector4Float trace() override;

        /*Method returns true if Matrix is invertible argument `inv` holds in the inverse matrix if invertible
         * argument `eps` matrix is invertible determinant is greater than `eps` due to rounding errors
         * argument `det` holds the result of the determinant*/
        bool inverse(Matrix3Float &inv, float eps, float *det);

        Matrix3Float transpose();

        static Matrix3Float identity();

        static Matrix3Float zeros();

        friend Vector3Float operator*(Vector3Float &v, Matrix3Float &m);

        friend Vector3Float operator*(Vector3Float &&v, Matrix3Float &&m);


        void load(FloatMatrix128x4& m);

        void load(FloatMatrix128x4&& m);

    };


#endif

    template<typename real>
    bool Matrix3<real>::isUpperTriangular(real eps) {
        return (this->mat[2][1] <= eps && this->mat[2][0] <= eps
                && this->mat[1][0] <= eps);
    }

    template<typename real>
    void Matrix3<real>::row(int r, Vector3<real> &v) {
        this->mat[r][0] = v[0];
        this->mat[r][1] = v[1];
        this->mat[r][2] = v[2];
    }

    template<typename real>
    Vector3<real> Matrix3<real>::row(int r) {
        return Vector3<real>(this->mat[r][0], this->mat[r][1], this->mat[r][2]);
    }

    template<typename real>
    void Matrix3<real>::col(int c, Vector3<real> &v) {
        this->mat[0][c] = v[0];
        this->mat[1][c] = v[1];
        this->mat[2][c] = v[2];
    }

    template<typename real>
    Vector3<real> Matrix3<real>::col(int c) {
        return Vector3<real>(this->mat[0][c], this->mat[1][c], this->mat[2][c]);
    }

    template<typename real>
    real Matrix3<real>::trace() {
        return (this->mat[0][0] + this->mat[1][1] + this->mat[2][2]);
    }

    template<typename real>
    Matrix3<real> Matrix3<real>::zeros() {
        return Matrix3<real>();
    }

    template<typename real>
    Matrix3<real> Matrix3<real>::identity() {
        return Matrix3<real>((real) 1.0, (real) 0.0, (real) 0.0,
                             (real) 0.0, (real) 1.0, (real) 0.0,
                             (real) 0.0, (real) 0.0, (real) 1.0);
    }

    template<typename real>
    Matrix3<real> Matrix3<real>::transpose() {
        return Matrix3<real>(this->mat[0][0], this->mat[1][0], this->mat[2][0],
                             this->mat[0][1], this->mat[1][1], this->mat[2][1],
                             this->mat[0][2], this->mat[1][2], this->mat[2][2]);
    }

    template<typename real>
    inline Matrix3<real> operator*(real c, Matrix3<real> &m) {
        return Matrix3<real>(c * m(0, 0), c * m(0, 1), c * m(0, 2),
                             c * m(1, 0), c * m(1, 1), c * m(1, 2),
                             c * m(2, 0), c * m(2, 1), c * m(2, 2));
    }

    template<typename real>
    inline Matrix3<real> operator*(real c, Matrix3<real> &&m) {
        return Matrix3<real>(c * m(0, 0), c * m(0, 1), c * m(0, 2),
                             c * m(1, 0), c * m(1, 1), c * m(1, 2),
                             c * m(2, 0), c * m(2, 1), c * m(2, 2));
    }

    template<typename real>
    inline Vector3<real> operator*(Vector3<real> &v, Matrix3<real> &m) {
        return Vector3<real>(
                v[0] * m(0, 0) + v[1] * m(1, 0) + v[2] * m(2, 0),
                v[0] * m(0, 1) + v[1] * m(1, 1) + v[2] * m(2, 1),
                v[0] * m(0, 2) + v[1] * m(1, 2) + v[2] * m(2, 2)
        );
    }

    template<typename real>
    inline Vector3<real> operator*(Vector3<real> &&v, Matrix3<real> &m) {
        return Vector3<real>(
                v[0] * m(0, 0) + v[1] * m(1, 0) + v[2] * m(2, 0),
                v[0] * m(0, 1) + v[1] * m(1, 1) + v[2] * m(2, 1),
                v[0] * m(0, 2) + v[1] * m(1, 2) + v[2] * m(2, 2)
        );
    }


    template<typename real>
    bool Matrix3<real>::inverse(Matrix3<real> &inv, real eps, real *det) {
        real tmp[12] = {0}; /* temp array for pairs */
        real src[3][3]; /* array of transpose source matrix */
        real d; /* determinant */
        /* transpose matrix */
        for (int i = 0; i < 3; i++) {
            src[i][0] = (*this)(0, i);
            src[i][1] = (*this)(1, i);
            src[i][2] = (*this)(2, i);
        }
        /* calculate pairs for first 8 elements (cofactors) */
        tmp[0] = src[2][2];
        tmp[2] = src[2][1];
        tmp[6] = src[2][0];
        /* calculate first 8 elements (cofactors) */

        inv(0, 0) = tmp[0] * src[1][1] + tmp[3] * src[1][2];
        inv(0, 0) -= tmp[1] * src[1][1] + tmp[2] * src[1][2];
        inv(0, 1) = tmp[1] * src[1][0] + tmp[6] * src[1][2];
        inv(0, 1) -= tmp[0] * src[1][0] + tmp[7] * src[1][2];
        inv(0, 2) = tmp[2] * src[1][0] + tmp[7] * src[1][1];
        inv(0, 2) -= tmp[3] * src[1][0] + tmp[6] * src[1][1];
        inv(1, 0) = tmp[1] * src[0][1] + tmp[2] * src[0][2];
        inv(1, 0) -= tmp[0] * src[0][1] + tmp[3] * src[0][2];
        inv(1, 1) = tmp[0] * src[0][0] + tmp[7] * src[0][2];
        inv(1, 1) -= tmp[1] * src[0][0] + tmp[6] * src[0][2];
        inv(1, 2) = tmp[3] * src[0][0] + tmp[6] * src[0][1];
        inv(1, 2) -= tmp[2] * src[0][0] + tmp[7] * src[0][1];
        /* calculate pairs for second 8 elements (cofactors) */

        tmp[4] = src[0][1] * src[1][2];
        tmp[5] = src[0][2] * src[1][1];


        tmp[8] = src[0][0] * src[1][2];
        tmp[9] = src[0][2] * src[1][0];
        tmp[10] = src[0][0] * src[1][1];
        tmp[11] = src[0][1] * src[1][0];
        /* calculate second 8 elements (cofactors) */

        inv(2, 0) = tmp[4];
        inv(2, 0) -= tmp[5];
        inv(2, 1) = tmp[9];
        inv(2, 1) -= tmp[8];
        inv(2, 2) = tmp[10];
        inv(2, 2) -= tmp[11];
        /* calculate determinant */
        d = src[0][0] * inv(0, 0) + src[0][1] * inv(0, 1) + src[0][2] * inv(0, 2);
        if (abs(d) <= eps)
            return false;

        /* calculate matrix inverse */
        real dtmp = (real) 1.0 / d;

        for (int j = 0; j < 3; j++) {
            inv(j, 0) *= dtmp;
            inv(j, 1) *= dtmp;
            inv(j, 2) *= dtmp;
        }

        if (det != nullptr)
            *det = d;

        return true;
    }

    template<typename real>
    real Matrix3<real>::det() {
        real t1 = this->mat[0][0] *
                  (this->mat[1][1] * this->mat[2][2]
                   - this->mat[1][2] * this->mat[2][1]);
        real t2 = this->mat[0][1] *
                  (this->mat[1][0] * this->mat[2][2]
                   - this->mat[1][2] * this->mat[2][0]);
        real t3 = this->mat[0][2] *
                  (this->mat[1][0] * this->mat[2][1]
                   - this->mat[1][1] * this->mat[2][0]);

        return t1 - t2 + t3;
    }

    template<typename real>
    bool Matrix3<real>::operator==(const Matrix3<real> &rhs) const {
        return (this->mat[0][0] == rhs(0, 0) && this->mat[0][1] == rhs(0, 1) && this->mat[0][2] == rhs(0, 2) &&
                this->mat[1][0] == rhs(1, 0) && this->mat[1][1] == rhs(1, 1) && this->mat[1][2] == rhs(1, 2) &&
                this->mat[2][0] == rhs(2, 0) && this->mat[2][1] == rhs(2, 1) && this->mat[2][2] == rhs(2, 2));

    }

    template<typename real>
    Vector3<real> Matrix3<real>::operator*(Vector3<real> &&v) {
        return Vector3<real>(this->mat[0][0] * v[0] + this->mat[0][1] * v[1] + this->mat[0][2] * v[2],
                             this->mat[1][0] * v[0] + this->mat[1][1] * v[1] + this->mat[1][2] * v[2],
                             this->mat[2][0] * v[0] + this->mat[2][1] * v[1] + this->mat[2][2] * v[2]);
    }

    template<typename real>
    Vector3<real> Matrix3<real>::operator*(Vector3<real> &v) {
        return Vector3<real>(this->mat[0][0] * v[0] + this->mat[0][1] * v[1] + this->mat[0][2] * v[2],
                             this->mat[1][0] * v[0] + this->mat[1][1] * v[1] + this->mat[1][2] * v[2],
                             this->mat[2][0] * v[0] + this->mat[2][1] * v[1] + this->mat[2][2] * v[2]);
    }

    template<typename real>
    Matrix3<real> Matrix3<real>::operator*(Matrix3<real> &&rhs) {
        real _11 = this->mat[0][0] * rhs(0, 0) + this->mat[0][1] * rhs(1, 0) + this->mat[0][2] * rhs(2, 0);
        real _12 = this->mat[0][0] * rhs(0, 1) + this->mat[0][1] * rhs(1, 1) + this->mat[0][2] * rhs(2, 1);
        real _13 = this->mat[0][0] * rhs(0, 2) + this->mat[0][1] * rhs(1, 2) + this->mat[0][2] * rhs(2, 2);

        real _21 = this->mat[1][0] * rhs(0, 0) + this->mat[1][1] * rhs(1, 0) + this->mat[1][2] * rhs(2, 0);
        real _22 = this->mat[1][0] * rhs(0, 1) + this->mat[1][1] * rhs(1, 1) + this->mat[1][2] * rhs(2, 1);
        real _23 = this->mat[1][0] * rhs(0, 2) + this->mat[1][1] * rhs(1, 2) + this->mat[1][2] * rhs(2, 2);

        real _31 = this->mat[2][0] * rhs(0, 0) + this->mat[2][1] * rhs(1, 0) + this->mat[2][2] * rhs(2, 0);
        real _32 = this->mat[2][0] * rhs(0, 1) + this->mat[2][1] * rhs(1, 1) + this->mat[2][2] * rhs(2, 1);
        real _33 = this->mat[2][0] * rhs(0, 2) + this->mat[2][1] * rhs(1, 2) + this->mat[2][2] * rhs(2, 2);

        return Matrix3<real>(_11, _12, _13,
                             _21, _22, _23,
                             _31, _32, _33);
    }

    template<typename real>
    Matrix3<real> Matrix3<real>::operator*(Matrix3<real> &rhs) {
        real _11 = this->mat[0][0] * rhs(0, 0) + this->mat[0][1] * rhs(1, 0) + this->mat[0][2] * rhs(2, 0);
        real _12 = this->mat[0][0] * rhs(0, 1) + this->mat[0][1] * rhs(1, 1) + this->mat[0][2] * rhs(2, 1);
        real _13 = this->mat[0][0] * rhs(0, 2) + this->mat[0][1] * rhs(1, 2) + this->mat[0][2] * rhs(2, 2);

        real _21 = this->mat[1][0] * rhs(0, 0) + this->mat[1][1] * rhs(1, 0) + this->mat[1][2] * rhs(2, 0);
        real _22 = this->mat[1][0] * rhs(0, 1) + this->mat[1][1] * rhs(1, 1) + this->mat[1][2] * rhs(2, 1);
        real _23 = this->mat[1][0] * rhs(0, 2) + this->mat[1][1] * rhs(1, 2) + this->mat[1][2] * rhs(2, 2);

        real _31 = this->mat[2][0] * rhs(0, 0) + this->mat[2][1] * rhs(1, 0) + this->mat[2][2] * rhs(2, 0);
        real _32 = this->mat[2][0] * rhs(0, 1) + this->mat[2][1] * rhs(1, 1) + this->mat[2][2] * rhs(2, 1);
        real _33 = this->mat[2][0] * rhs(0, 2) + this->mat[2][1] * rhs(1, 2) + this->mat[2][2] * rhs(2, 2);

        return Matrix3<real>(_11, _12, _13,
                             _21, _22, _23,
                             _31, _32, _33);
    }

    template<typename real>
    Matrix3<real> Matrix3<real>::operator-(const Matrix3<real> &&rhs) {
        return Matrix3<real>(this->mat[0][0] - rhs(0, 0), this->mat[0][1] - rhs(0, 1), this->mat[0][2] - rhs(0, 2),
                             this->mat[1][0] - rhs(1, 0), this->mat[1][1] - rhs(1, 1), this->mat[1][2] - rhs(1, 2),
                             this->mat[2][0] - rhs(2, 0), this->mat[2][1] - rhs(2, 1), this->mat[2][2] - rhs(2, 2));
    }

    template<typename real>
    Matrix3<real> Matrix3<real>::operator-(const Matrix3<real> &rhs) {
        return Matrix3<real>(this->mat[0][0] - rhs(0, 0), this->mat[0][1] - rhs(0, 1), this->mat[0][2] - rhs(0, 2),
                             this->mat[1][0] - rhs(1, 0), this->mat[1][1] - rhs(1, 1), this->mat[1][2] - rhs(1, 2),
                             this->mat[2][0] - rhs(2, 0), this->mat[2][1] - rhs(2, 1), this->mat[2][2] - rhs(2, 2));
    }

    template<typename real>
    Matrix3<real> Matrix3<real>::operator+(const Matrix3<real> &&rhs) {
        return Matrix3<real>(this->mat[0][0] + rhs(0, 0), this->mat[0][1] + rhs(0, 1), this->mat[0][2] + rhs(0, 2),
                             this->mat[1][0] + rhs(1, 0), this->mat[1][1] + rhs(1, 1), this->mat[1][2] + rhs(1, 2),
                             this->mat[2][0] + rhs(2, 0), this->mat[2][1] + rhs(2, 1), this->mat[2][2] + rhs(2, 2));
    }

    template<typename real>
    Matrix3<real> Matrix3<real>::operator+(const Matrix3<real> &rhs) {
        return Matrix3<real>(this->mat[0][0] + rhs(0, 0), this->mat[0][1] + rhs(0, 1), this->mat[0][2] + rhs(0, 2),
                             this->mat[1][0] + rhs(1, 0), this->mat[1][1] + rhs(1, 1), this->mat[1][2] + rhs(1, 2),
                             this->mat[2][0] + rhs(2, 0), this->mat[2][1] + rhs(2, 1), this->mat[2][2] + rhs(2, 2));
    }

    template<typename real>
    Matrix3<real> &Matrix3<real>::operator=(const Matrix3<real> &rhs) {
        if (this != &rhs) {
            this->mat[0][0] = rhs(0, 0);
            this->mat[0][1] = rhs(0, 1);
            this->mat[0][2] = rhs(0, 2);

            this->mat[1][0] = rhs(1, 0);
            this->mat[1][1] = rhs(1, 1);
            this->mat[1][2] = rhs(1, 2);

            this->mat[2][0] = rhs(2, 0);
            this->mat[2][1] = rhs(2, 1);
            this->mat[2][2] = rhs(2, 2);
        }
        return *this;
    }
}


#endif //ODINMATH_MATRIX3_H
