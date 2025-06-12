//
// Created by Jason Fedorowich on 2024-03-14.
//

#ifndef ODINMATH_MATRIX4_H
#define ODINMATH_MATRIX4_H

#include "odinmath.h"

namespace OdinMath {
    template<typename real>
    class Matrix4 : public Matrix<4, 4, real> {
    public:
        Matrix4(real _11, real _12, real _13, real _14,
                real _21, real _22, real _23, real _24,
                real _31, real _32, real _33, real _34,
                real _41, real _42, real _43, real _44) {
            this->mat[0][0] = _11;
            this->mat[0][1] = _12;
            this->mat[0][2] = _13;
            this->mat[0][3] = _14;

            this->mat[1][0] = _21;
            this->mat[1][1] = _22;
            this->mat[1][2] = _23;
            this->mat[1][3] = _24;

            this->mat[2][0] = _31;
            this->mat[2][1] = _32;
            this->mat[2][2] = _33;
            this->mat[2][3] = _34;

            this->mat[3][0] = _41;
            this->mat[3][1] = _42;
            this->mat[3][2] = _43;
            this->mat[3][3] = _44;
        }

        Matrix4(Matrix4<real> &mat) {
            *this = mat;
        }

        Matrix4() : Matrix4((real) 0.0, (real) 0.0, (real) 0.0, (real) 0.0,
                            (real) 0.0, (real) 0.0, (real) 0.0, (real) 0.0,
                            (real) 0.0, (real) 0.0, (real) 0.0, (real) 0.0,
                            (real) 0.0, (real) 0.0, (real) 0.0, (real) 0.0) {}

        virtual ~Matrix4() = default;

        Matrix4<real> &operator=(const Matrix4<real> &rhs);

        Matrix4<real> operator+(const Matrix4<real> &rhs);

        Matrix4<real> operator+(const Matrix4<real> &&rhs);

        Matrix4<real> operator-(const Matrix4<real> &rhs);

        Matrix4<real> operator-(const Matrix4<real> &&rhs);

        Matrix4<real> operator*(Matrix4<real> &rhs);

        Matrix4<real> operator*(Matrix4<real> &&rhs);

        Vector4<real> operator*(Vector4<real> &v);

        Vector4<real> operator*(Vector4<real> &&v);

        bool operator==(const Matrix4<real> &rhs) const;

        Vector4<real> col(int c);

        void col(int c, Vector4<real>& v);

        Vector4<real> row(int r);

        void row(int r, Vector4<real>& v);

        real det();

        real trace();

        /*Method returns true if Matrix is invertible argument `inv` holds in the inverse matrix if invertible
         * argument `eps` matrix is invertible determinant is greater than `eps` due to rounding errors
         * argument `det` holds the result of the determinant*/
        bool inverse(Matrix4<real> &inv, real eps, real *det);

        bool isUpperTriangular(real eps);

        Matrix4<real> transpose();

        static Matrix4<real> identity();

        static Matrix4<real> zeros();


    };



#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))

    class Matrix4Float {
    protected:
        FloatMatrix128x4 floatMatrix128X4{};
    public:
        Matrix4Float(float _11, float _12, float _13, float _14,
                     float _21, float _22, float _23, float _24,
                     float _31, float _32, float _33, float _34,
                     float _41, float _42, float _43, float _44) {
            float mat[4][4];
            mat[0][0] = _11;
            mat[0][1] = _12;
            mat[0][2] = _13;
            mat[0][3] = _14;

            mat[1][0] = _21;
            mat[1][1] = _22;
            mat[1][2] = _23;
            mat[1][3] = _24;

            mat[2][0] = _31;
            mat[2][1] = _32;
            mat[2][2] = _33;
            mat[2][3] = _34;

            mat[3][0] = _41;
            mat[3][1] = _42;
            mat[3][2] = _43;
            mat[3][3] = _44;
            this->floatMatrix128X4 = FloatMatrix128x4(mat);
        }

        Matrix4Float(Matrix4Float &mat) {
            *this = mat;
        }

        Matrix4Float(Vector4Float& first,
                     Vector4Float& second,
                     Vector4Float& third,
                     Vector4Float& fourth){
            this->floatMatrix128X4.vectors[0] = first.getVector();
            this->floatMatrix128X4.vectors[1] = second.getVector();
            this->floatMatrix128X4.vectors[2] = third.getVector();
            this->floatMatrix128X4.vectors[3] = fourth.getVector();
        }

        Matrix4Float() {}

        explicit Matrix4Float(FloatMatrix128x4 &floatMatrix128X4) {
            this->floatMatrix128X4 = floatMatrix128X4;
        }

        explicit Matrix4Float(FloatMatrix128x4 &&floatMatrix128X4) {
            this->floatMatrix128X4 = floatMatrix128X4;
        }

        virtual ~Matrix4Float() = default;

        virtual float get(int r, int c) const;

        Vector4Float row(int r);

        virtual void set(int r, int c, float v);

        Matrix4Float &operator=(const Matrix4Float &rhs);

        virtual Matrix4Float operator+(const Matrix4Float &rhs);

        virtual Matrix4Float operator+(const Matrix4Float &&rhs);

        virtual Matrix4Float operator-(const Matrix4Float &rhs);

        virtual Matrix4Float operator-(const Matrix4Float &&rhs);

        virtual Matrix4Float operator*(Matrix4Float &rhs);

        virtual Matrix4Float operator*(Matrix4Float &&rhs);

        virtual Vector4Float operator*(Vector4Float &v);

        virtual Vector4Float operator*(Vector4Float &&v);

        bool operator==(const Matrix4Float &rhs) const;

        virtual float det();

        virtual Vector4Float trace();

        /*Method returns true if Matrix is invertible argument `inv` holds in the inverse matrix if invertible
         * argument `eps` matrix is invertible determinant is greater than `eps` due to rounding errors
         * argument `det` holds the result of the determinant*/
        bool inverse(Matrix4Float &inv, float eps, float *det);

        //todo should make virtual?
        Matrix4Float transpose();

        bool isUpperTriangular(float eps);

        static Matrix4Float identity();

        static Matrix4Float zeros();

        static FloatMatrix128x4 to(Matrix4Float& m);

        friend Vector4Float operator*(Vector4Float &v, Matrix4Float &m);

        friend Vector4Float operator*(Vector4Float &&v, Matrix4Float &&m);

    };


#endif

    template<typename real>
    bool Matrix4<real>::isUpperTriangular(real eps) {
        return (this->mat[3][2] <= eps && this->mat[3][1] <= eps && this->mat[3][0] <= eps
                && this->mat[2][1] <= eps && this->mat[2][0] <= eps
                && this->mat[1][0] <= eps);
    }


    template<typename real>
    inline void Matrix4<real>::row(int r, Vector4<real> &v) {
        this->mat[r][0] = v[0];
        this->mat[r][1] = v[1];
        this->mat[r][2] = v[2];
        this->mat[r][3] = v[3];
    }

    template<typename real>
    inline void Matrix4<real>::col(int c, Vector4<real> &v) {
        this->mat[0][c] = v[0];
        this->mat[1][c] = v[1];
        this->mat[2][c] = v[2];
        this->mat[3][c] = v[3];
    }

    template<typename real>
    inline Vector4<real> Matrix4<real>::row(int r) {
        return Vector4<real>(this->mat[r][0], this->mat[r][1], this->mat[r][2], this->mat[r][3]);
    }

    template<typename real>
    inline Vector4<real> Matrix4<real>::col(int c) {
        return Vector4<real>(this->mat[0][c], this->mat[1][c], this->mat[2][c], this->mat[3][c]);
    }

    template<typename real>
    inline real Matrix4<real>::trace() {
        return (this->mat[0][0] + this->mat[1][1] + this->mat[2][2] + this->mat[3][3]);
    }


    template<typename real>
    Matrix4<real> Matrix4<real>::zeros() {
        return Matrix4<real>();
    }

    template<typename real>
    inline Matrix4<real> operator*(real c, Matrix4<real> &m) {
        return Matrix4<real>(c * m(0, 0), c * m(0, 1), c * m(0, 2), c * m(0, 3),
                             c * m(1, 0), c * m(1, 1), c * m(1, 2), c * m(1, 3),
                             c * m(2, 0), c * m(2, 1), c * m(2, 2), c * m(2, 3),
                             c * m(3, 0), c * m(3, 1), c * m(3, 2), c * m(3, 3));
    }

    template<typename real>
    inline Matrix4<real> operator*(real c, Matrix4<real> &&m) {
        return Matrix4<real>(c * m(0, 0), c * m(0, 1), c * m(0, 2), c * m(0, 3),
                             c * m(1, 0), c * m(1, 1), c * m(1, 2), c * m(1, 3),
                             c * m(2, 0), c * m(2, 1), c * m(2, 2), c * m(2, 3),
                             c * m(3, 0), c * m(3, 1), c * m(3, 2), c * m(3, 3));
    }

    template<typename real>
    inline Vector4<real> operator*(Vector4<real> &v, Matrix4<real> &m) {
        return Vector4<real>(
                v[0] * m(0, 0) + v[1] * m(1, 0) + v[2] * m(2, 0) + v[3] * m(3, 0),
                v[0] * m(0, 1) + v[1] * m(1, 1) + v[2] * m(2, 1) + v[3] * m(3, 1),
                v[0] * m(0, 2) + v[1] * m(1, 2) + v[2] * m(2, 2) + v[3] * m(3, 2),
                v[0] * m(0, 3) + v[1] * m(1, 3) + v[2] * m(2, 3) + v[3] * m(3, 3)
        );
    }

    template<typename real>
    inline Vector4<real> operator*(Vector4<real> &&v, Matrix4<real> &m) {
        return Vector4<real>(
                v[0] * m(0, 0) + v[1] * m(1, 0) + v[2] * m(2, 0) + v[3] * m(3, 0),
                v[0] * m(0, 1) + v[1] * m(1, 1) + v[2] * m(2, 1) + v[3] * m(3, 1),
                v[0] * m(0, 2) + v[1] * m(1, 2) + v[2] * m(2, 2) + v[3] * m(3, 2),
                v[0] * m(0, 3) + v[1] * m(1, 3) + v[2] * m(2, 3) + v[3] * m(3, 3)
        );
    }

    template<typename real>
    Vector4<real> Matrix4<real>::operator*(Vector4<real> &&v) {
        return Vector4<real>(
                this->mat[0][0] * v[0] + this->mat[0][1] * v[1] + this->mat[0][2] * v[2] + this->mat[0][3] * v[3],
                this->mat[1][0] * v[0] + this->mat[1][1] * v[1] + this->mat[1][2] * v[2] + this->mat[1][3] * v[3],
                this->mat[2][0] * v[0] + this->mat[2][1] * v[1] + this->mat[2][2] * v[2] + this->mat[2][3] * v[3],
                this->mat[3][0] * v[0] + this->mat[3][1] * v[1] + this->mat[3][2] * v[2] + this->mat[3][3] * v[3]);
    }

    template<typename real>
    Matrix4<real> Matrix4<real>::operator*(Matrix4<real> &&rhs) {
        real _11 = this->mat[0][0] * rhs(0, 0) + this->mat[0][1] * rhs(1, 0) + this->mat[0][2] * rhs(2, 0) +
                   this->mat[0][3] * rhs(3, 0);
        real _12 = this->mat[0][0] * rhs(0, 1) + this->mat[0][1] * rhs(1, 1) + this->mat[0][2] * rhs(2, 1) +
                   this->mat[0][3] * rhs(3, 1);
        real _13 = this->mat[0][0] * rhs(0, 2) + this->mat[0][1] * rhs(1, 2) + this->mat[0][2] * rhs(2, 2) +
                   this->mat[0][3] * rhs(3, 2);
        real _14 = this->mat[0][0] * rhs(0, 3) + this->mat[0][1] * rhs(1, 3) + this->mat[0][2] * rhs(2, 3) +
                   this->mat[0][3] * rhs(3, 3);

        real _21 = this->mat[1][0] * rhs(0, 0) + this->mat[1][1] * rhs(1, 0) + this->mat[1][2] * rhs(2, 0) +
                   this->mat[1][3] * rhs(3, 0);
        real _22 = this->mat[1][0] * rhs(0, 1) + this->mat[1][1] * rhs(1, 1) + this->mat[1][2] * rhs(2, 1) +
                   this->mat[1][3] * rhs(3, 1);
        real _23 = this->mat[1][0] * rhs(0, 2) + this->mat[1][1] * rhs(1, 2) + this->mat[1][2] * rhs(2, 2) +
                   this->mat[1][3] * rhs(3, 2);
        real _24 = this->mat[1][0] * rhs(0, 3) + this->mat[1][1] * rhs(1, 3) + this->mat[1][2] * rhs(2, 3) +
                   this->mat[1][3] * rhs(3, 3);

        real _31 = this->mat[2][0] * rhs(0, 0) + this->mat[2][1] * rhs(1, 0) + this->mat[2][2] * rhs(2, 0) +
                   this->mat[2][3] * rhs(3, 0);
        real _32 = this->mat[2][0] * rhs(0, 1) + this->mat[2][1] * rhs(1, 1) + this->mat[2][2] * rhs(2, 1) +
                   this->mat[2][3] * rhs(3, 1);
        real _33 = this->mat[2][0] * rhs(0, 2) + this->mat[2][1] * rhs(1, 2) + this->mat[2][2] * rhs(2, 2) +
                   this->mat[2][3] * rhs(3, 2);
        real _34 = this->mat[2][0] * rhs(0, 3) + this->mat[2][1] * rhs(1, 3) + this->mat[2][2] * rhs(2, 3) +
                   this->mat[2][3] * rhs(3, 3);

        real _41 = this->mat[3][0] * rhs(0, 0) + this->mat[3][1] * rhs(1, 0) + this->mat[3][2] * rhs(2, 0) +
                   this->mat[3][3] * rhs(3, 0);
        real _42 = this->mat[3][0] * rhs(0, 1) + this->mat[3][1] * rhs(1, 1) + this->mat[3][2] * rhs(2, 1) +
                   this->mat[3][3] * rhs(3, 1);
        real _43 = this->mat[3][0] * rhs(0, 2) + this->mat[3][1] * rhs(1, 2) + this->mat[3][2] * rhs(2, 2) +
                   this->mat[3][3] * rhs(3, 2);
        real _44 = this->mat[3][0] * rhs(0, 3) + this->mat[3][1] * rhs(1, 3) + this->mat[3][2] * rhs(2, 3) +
                   this->mat[3][3] * rhs(3, 3);
        return Matrix4<real>(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44);
    }

    template<typename real>
    Matrix4<real> Matrix4<real>::operator-(const Matrix4<real> &&rhs) {
        return Matrix4(this->mat[0][0] - rhs(0, 0), this->mat[0][1] - rhs(0, 1), this->mat[0][2] - rhs(0, 2),
                       this->mat[0][3] - rhs(0, 3),
                       this->mat[1][0] - rhs(1, 0), this->mat[1][1] - rhs(1, 1), this->mat[1][2] - rhs(1, 2),
                       this->mat[1][3] - rhs(1, 3),
                       this->mat[2][0] - rhs(2, 0), this->mat[2][1] - rhs(2, 1), this->mat[2][2] - rhs(2, 2),
                       this->mat[2][3] - rhs(2, 3),
                       this->mat[3][0] - rhs(3, 0), this->mat[3][1] - rhs(3, 1), this->mat[3][2] - rhs(3, 2),
                       this->mat[3][3] - rhs(3, 3));
    }

    template<typename real>
    Matrix4<real> Matrix4<real>::operator+(const Matrix4<real> &&rhs) {
        return Matrix4(this->mat[0][0] + rhs(0, 0), this->mat[0][1] + rhs(0, 1), this->mat[0][2] + rhs(0, 2),
                       this->mat[0][3] + rhs(0, 3),
                       this->mat[1][0] + rhs(1, 0), this->mat[1][1] + rhs(1, 1), this->mat[1][2] + rhs(1, 2),
                       this->mat[1][3] + rhs(1, 3),
                       this->mat[2][0] + rhs(2, 0), this->mat[2][1] + rhs(2, 1), this->mat[2][2] + rhs(2, 2),
                       this->mat[2][3] + rhs(2, 3),
                       this->mat[3][0] + rhs(3, 0), this->mat[3][1] + rhs(3, 1), this->mat[3][2] + rhs(3, 2),
                       this->mat[3][3] + rhs(3, 3));
    }

    template<typename real>
    bool Matrix4<real>::operator==(const Matrix4<real> &rhs) const {
        return this->mat[0][0] == rhs.mat[0][0] && this->mat[0][1] == rhs.mat[0][1] &&
               this->mat[0][2] == rhs.mat[0][2] && this->mat[0][3] == rhs.mat[0][3]
               && this->mat[1][0] == rhs.mat[1][0] && this->mat[1][1] == rhs.mat[1][1] &&
               this->mat[1][2] == rhs.mat[1][2] && this->mat[1][3] == rhs.mat[1][3]
               && this->mat[2][0] == rhs.mat[2][0] && this->mat[2][1] == rhs.mat[2][1] &&
               this->mat[2][2] == rhs.mat[2][2] && this->mat[2][3] == rhs.mat[2][3]
               && this->mat[3][0] == rhs.mat[3][0] && this->mat[3][1] == rhs.mat[3][1] &&
               this->mat[3][2] == rhs.mat[3][2] && this->mat[3][3] == rhs.mat[3][3];
    }

    template<typename real>
    bool Matrix4<real>::inverse(Matrix4<real> &inv, real eps, real *det) {
        real tmp[12]; /* temp array for pairs */
        real src[4][4]; /* array of transpose source matrix */
        real d; /* determinant */
        /* transpose matrix */
        for (int i = 0; i < 4; i++) {
            src[i][0] = (*this)(0, i);
            src[i][1] = (*this)(1, i);
            src[i][2] = (*this)(2, i);
            src[i][3] = (*this)(3, i);


        }
        /* calculate pairs for first 8 elements (cofactors) */
        tmp[0] = src[2][2] * src[3][3];
        tmp[1] = src[2][3] * src[3][2];
        tmp[2] = src[2][1] * src[3][3];
        tmp[3] = src[2][3] * src[3][1];
        tmp[4] = src[2][1] * src[3][2];
        tmp[5] = src[2][2] * src[3][1];
        tmp[6] = src[2][0] * src[3][3];
        tmp[7] = src[2][3] * src[3][0];
        tmp[8] = src[2][0] * src[3][2];
        tmp[9] = src[2][2] * src[3][0];
        tmp[10] = src[2][0] * src[3][1];
        tmp[11] = src[2][1] * src[3][0];

        /* calculate first 8 elements (cofactors) */
        inv(0, 0) = tmp[0] * src[1][1] + tmp[3] * src[1][2] + tmp[4] * src[1][3];
        inv(0, 0) -= tmp[1] * src[1][1] + tmp[2] * src[1][2] + tmp[5] * src[1][3];
        inv(0, 1) = tmp[1] * src[1][0] + tmp[6] * src[1][2] + tmp[9] * src[1][3];
        inv(0, 1) -= tmp[0] * src[1][0] + tmp[7] * src[1][2] + tmp[8] * src[1][3];
        inv(0, 2) = tmp[2] * src[1][0] + tmp[7] * src[1][1] + tmp[10] * src[1][3];
        inv(0, 2) -= tmp[3] * src[1][0] + tmp[6] * src[1][1] + tmp[11] * src[1][3];
        inv(0, 3) = tmp[5] * src[1][0] + tmp[8] * src[1][1] + tmp[11] * src[1][2];
        inv(0, 3) -= tmp[4] * src[1][0] + tmp[9] * src[1][1] + tmp[10] * src[1][2];

        inv(1, 0) = tmp[1] * src[0][1] + tmp[2] * src[0][2] + tmp[5] * src[0][3];
        inv(1, 0) -= tmp[0] * src[0][1] + tmp[3] * src[0][2] + tmp[4] * src[0][3];
        inv(1, 1) = tmp[0] * src[0][0] + tmp[7] * src[0][2] + tmp[8] * src[0][3];
        inv(1, 1) -= tmp[1] * src[0][0] + tmp[6] * src[0][2] + tmp[9] * src[0][3];
        inv(1, 2) = tmp[3] * src[0][0] + tmp[6] * src[0][1] + tmp[11] * src[0][3];
        inv(1, 2) -= tmp[2] * src[0][0] + tmp[7] * src[0][1] + tmp[10] * src[0][3];
        inv(1, 3) = tmp[4] * src[0][0] + tmp[9] * src[0][1] + tmp[10] * src[0][2];
        inv(1, 3) -= tmp[5] * src[0][0] + tmp[8] * src[0][1] + tmp[11] * src[0][2];
        /* calculate pairs for second 8 elements (cofactors) */
        tmp[0] = src[0][2] * src[1][3];
        tmp[1] = src[0][3] * src[1][2];
        tmp[2] = src[0][1] * src[1][3];
        tmp[3] = src[0][3] * src[1][1];
        tmp[4] = src[0][1] * src[1][2];
        tmp[5] = src[0][2] * src[1][1];

        tmp[6] = src[0][0] * src[1][3];
        tmp[7] = src[0][3] * src[1][0];
        tmp[8] = src[0][0] * src[1][2];
        tmp[9] = src[0][2] * src[1][0];
        tmp[10] = src[0][0] * src[1][1];
        tmp[11] = src[0][1] * src[1][0];

        /* calculate second 8 elements (cofactors) */
        inv(2, 0) = tmp[0] * src[3][1] + tmp[3] * src[3][2] + tmp[4] * src[3][3];
        inv(2, 0) -= tmp[1] * src[3][1] + tmp[2] * src[3][2] + tmp[5] * src[3][3];
        inv(2, 1) = tmp[1] * src[3][0] + tmp[6] * src[3][2] + tmp[9] * src[3][3];
        inv(2, 1) -= tmp[0] * src[3][0] + tmp[7] * src[3][2] + tmp[8] * src[3][3];
        inv(2, 2) = tmp[2] * src[3][0] + tmp[7] * src[3][1] + tmp[10] * src[3][3];
        inv(2, 2) -= tmp[3] * src[3][0] + tmp[6] * src[3][1] + tmp[11] * src[3][3];
        inv(2, 3) = tmp[5] * src[3][0] + tmp[8] * src[3][1] + tmp[11] * src[3][2];
        inv(2, 3) -= tmp[4] * src[3][0] + tmp[9] * src[3][1] + tmp[10] * src[3][2];

        inv(3, 0) = tmp[2] * src[2][2] + tmp[5] * src[2][3] + tmp[1] * src[2][1];
        inv(3, 0) -= tmp[4] * src[2][3] + tmp[0] * src[2][1] + tmp[3] * src[2][2];
        inv(3, 1) = tmp[8] * src[2][3] + tmp[0] * src[2][0] + tmp[7] * src[2][2];
        inv(3, 1) -= tmp[6] * src[2][2] + tmp[9] * src[2][3] + tmp[1] * src[2][0];
        inv(3, 2) = tmp[6] * src[2][1] + tmp[11] * src[2][3] + tmp[3] * src[2][0];
        inv(3, 2) -= tmp[10] * src[2][3] + tmp[2] * src[2][0] + tmp[7] * src[2][1];
        inv(3, 3) = tmp[10] * src[2][2] + tmp[4] * src[2][0] + tmp[9] * src[2][1];
        inv(3, 3) -= tmp[8] * src[2][1] + tmp[11] * src[2][2] + tmp[5] * src[2][0];
        /* calculate determinant */
        d = src[0][0] * inv(0, 0) + src[0][1] * inv(0, 1) + src[0][2] * inv(0, 2) + src[0][3] * inv(0, 3);
        if (abs(d) <= eps)
            return false;

        /* calculate matrix inverse */
        real dtmp = (real) 1.0 / d;

        for (int j = 0; j < 4; j++) {
            inv(j, 0) *= dtmp;
            inv(j, 1) *= dtmp;
            inv(j, 2) *= dtmp;
            inv(j, 3) *= dtmp;
        }

        if (det != nullptr)
            *det = d;

        return true;
    }


    template<typename real>
    Matrix4<real> Matrix4<real>::identity() {
        return Matrix4<real>((real) 1.f, (real) 0.f, (real) 0.f, (real) 0.f,
                             (real) 0.f, (real) 1.f, (real) 0.f, (real) 0.f,
                             (real) 0.f, (real) 0.f, (real) 1.f, (real) 0.f,
                             (real) 0.f, (real) 0.f, (real) 0.f, (real) 1.f);
    }

    template<typename real>
    Matrix4<real> Matrix4<real>::transpose() {
        return Matrix4<real>(this->mat[0][0], this->mat[1][0], this->mat[2][0], this->mat[3][0],
                             this->mat[0][1], this->mat[1][1], this->mat[2][1], this->mat[3][1],
                             this->mat[0][2], this->mat[1][2], this->mat[2][2], this->mat[3][2],
                             this->mat[0][3], this->mat[1][3], this->mat[2][3], this->mat[3][3]);
    }

    template<typename real>
    real Matrix4<real>::det() {
        real t1 = this->mat[0][0] *
                  (this->mat[1][1] * (this->mat[2][2] * this->mat[3][3] - this->mat[2][3] * this->mat[3][2])
                   - this->mat[1][2] * (this->mat[2][1] * this->mat[3][3] - this->mat[2][3] * this->mat[3][1])
                   + this->mat[1][3] * (this->mat[2][1] * this->mat[3][2] - this->mat[2][2] * this->mat[3][1]));
        real t2 = this->mat[0][1] *
                  (this->mat[1][0] * (this->mat[2][2] * this->mat[3][3] - this->mat[2][3] * this->mat[3][2])
                   - this->mat[1][2] * (this->mat[2][0] * this->mat[3][3] - this->mat[2][3] * this->mat[3][0])
                   + this->mat[1][3] * (this->mat[2][0] * this->mat[3][2] - this->mat[2][2] * this->mat[3][0]));
        real t3 = this->mat[0][2] *
                  (this->mat[1][0] * (this->mat[2][1] * this->mat[3][3] - this->mat[2][3] * this->mat[3][1])
                   - this->mat[1][1] * (this->mat[2][0] * this->mat[3][3] - this->mat[2][3] * this->mat[3][0])
                   + this->mat[1][3] * (this->mat[2][0] * this->mat[3][1] - this->mat[2][1] * this->mat[3][0]));
        real t4 = this->mat[0][3] *
                  (this->mat[1][0] * (this->mat[2][1] * this->mat[3][2] - this->mat[2][2] * this->mat[3][1])
                   - this->mat[1][1] * (this->mat[2][0] * this->mat[3][2] - this->mat[2][2] * this->mat[3][0])
                   + this->mat[1][2] * (this->mat[2][0] * this->mat[3][1] - this->mat[2][1] * this->mat[3][0]));
        return t1 - t2 + t3 - t4;

    }

    template<typename real>
    Vector4<real> Matrix4<real>::operator*(Vector4<real> &v) {
        return Vector4<real>(
                this->mat[0][0] * v[0] + this->mat[0][1] * v[1] + this->mat[0][2] * v[2] + this->mat[0][3] * v[3],
                this->mat[1][0] * v[0] + this->mat[1][1] * v[1] + this->mat[1][2] * v[2] + this->mat[1][3] * v[3],
                this->mat[2][0] * v[0] + this->mat[2][1] * v[1] + this->mat[2][2] * v[2] + this->mat[2][3] * v[3],
                this->mat[3][0] * v[0] + this->mat[3][1] * v[1] + this->mat[3][2] * v[2] + this->mat[3][3] * v[3]);
    }

    template<typename real>
    Matrix4<real> Matrix4<real>::operator*(Matrix4<real> &rhs) {
        real _11 = this->mat[0][0] * rhs(0, 0) + this->mat[0][1] * rhs(1, 0) + this->mat[0][2] * rhs(2, 0) +
                   this->mat[0][3] * rhs(3, 0);
        real _12 = this->mat[0][0] * rhs(0, 1) + this->mat[0][1] * rhs(1, 1) + this->mat[0][2] * rhs(2, 1) +
                   this->mat[0][3] * rhs(3, 1);
        real _13 = this->mat[0][0] * rhs(0, 2) + this->mat[0][1] * rhs(1, 2) + this->mat[0][2] * rhs(2, 2) +
                   this->mat[0][3] * rhs(3, 2);
        real _14 = this->mat[0][0] * rhs(0, 3) + this->mat[0][1] * rhs(1, 3) + this->mat[0][2] * rhs(2, 3) +
                   this->mat[0][3] * rhs(3, 3);

        real _21 = this->mat[1][0] * rhs(0, 0) + this->mat[1][1] * rhs(1, 0) + this->mat[1][2] * rhs(2, 0) +
                   this->mat[1][3] * rhs(3, 0);
        real _22 = this->mat[1][0] * rhs(0, 1) + this->mat[1][1] * rhs(1, 1) + this->mat[1][2] * rhs(2, 1) +
                   this->mat[1][3] * rhs(3, 1);
        real _23 = this->mat[1][0] * rhs(0, 2) + this->mat[1][1] * rhs(1, 2) + this->mat[1][2] * rhs(2, 2) +
                   this->mat[1][3] * rhs(3, 2);
        real _24 = this->mat[1][0] * rhs(0, 3) + this->mat[1][1] * rhs(1, 3) + this->mat[1][2] * rhs(2, 3) +
                   this->mat[1][3] * rhs(3, 3);

        real _31 = this->mat[2][0] * rhs(0, 0) + this->mat[2][1] * rhs(1, 0) + this->mat[2][2] * rhs(2, 0) +
                   this->mat[2][3] * rhs(3, 0);
        real _32 = this->mat[2][0] * rhs(0, 1) + this->mat[2][1] * rhs(1, 1) + this->mat[2][2] * rhs(2, 1) +
                   this->mat[2][3] * rhs(3, 1);
        real _33 = this->mat[2][0] * rhs(0, 2) + this->mat[2][1] * rhs(1, 2) + this->mat[2][2] * rhs(2, 2) +
                   this->mat[2][3] * rhs(3, 2);
        real _34 = this->mat[2][0] * rhs(0, 3) + this->mat[2][1] * rhs(1, 3) + this->mat[2][2] * rhs(2, 3) +
                   this->mat[2][3] * rhs(3, 3);

        real _41 = this->mat[3][0] * rhs(0, 0) + this->mat[3][1] * rhs(1, 0) + this->mat[3][2] * rhs(2, 0) +
                   this->mat[3][3] * rhs(3, 0);
        real _42 = this->mat[3][0] * rhs(0, 1) + this->mat[3][1] * rhs(1, 1) + this->mat[3][2] * rhs(2, 1) +
                   this->mat[3][3] * rhs(3, 1);
        real _43 = this->mat[3][0] * rhs(0, 2) + this->mat[3][1] * rhs(1, 2) + this->mat[3][2] * rhs(2, 2) +
                   this->mat[3][3] * rhs(3, 2);
        real _44 = this->mat[3][0] * rhs(0, 3) + this->mat[3][1] * rhs(1, 3) + this->mat[3][2] * rhs(2, 3) +
                   this->mat[3][3] * rhs(3, 3);
        return Matrix4<real>(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44);
    }


    template<typename real>
    Matrix4<real> Matrix4<real>::operator-(const Matrix4<real> &rhs) {
        return Matrix4(this->mat[0][0] - rhs(0, 0), this->mat[0][1] - rhs(0, 1), this->mat[0][2] - rhs(0, 2),
                       this->mat[0][3] - rhs(0, 3),
                       this->mat[1][0] - rhs(1, 0), this->mat[1][1] - rhs(1, 1), this->mat[1][2] - rhs(1, 2),
                       this->mat[1][3] - rhs(1, 3),
                       this->mat[2][0] - rhs(2, 0), this->mat[2][1] - rhs(2, 1), this->mat[2][2] - rhs(2, 2),
                       this->mat[2][3] - rhs(2, 3),
                       this->mat[3][0] - rhs(3, 0), this->mat[3][1] - rhs(3, 1), this->mat[3][2] - rhs(3, 2),
                       this->mat[3][3] - rhs(3, 3));
    }

    template<typename real>
    Matrix4<real> Matrix4<real>::operator+(const Matrix4<real> &rhs) {
        return Matrix4(this->mat[0][0] + rhs(0, 0), this->mat[0][1] + rhs(0, 1), this->mat[0][2] + rhs(0, 2),
                       this->mat[0][3] + rhs(0, 3),
                       this->mat[1][0] + rhs(1, 0), this->mat[1][1] + rhs(1, 1), this->mat[1][2] + rhs(1, 2),
                       this->mat[1][3] + rhs(1, 3),
                       this->mat[2][0] + rhs(2, 0), this->mat[2][1] + rhs(2, 1), this->mat[2][2] + rhs(2, 2),
                       this->mat[2][3] + rhs(2, 3),
                       this->mat[3][0] + rhs(3, 0), this->mat[3][1] + rhs(3, 1), this->mat[3][2] + rhs(3, 2),
                       this->mat[3][3] + rhs(3, 3));
    }

    template<typename real>
    Matrix4<real> &Matrix4<real>::operator=(const Matrix4<real> &rhs) {
        if (this != &rhs) {
            this->mat[0][0] = rhs(0, 0);
            this->mat[0][1] = rhs(0, 1);
            this->mat[0][2] = rhs(0, 2);
            this->mat[0][3] = rhs(0, 3);

            this->mat[1][0] = rhs(1, 0);
            this->mat[1][1] = rhs(1, 1);
            this->mat[1][2] = rhs(1, 2);
            this->mat[1][3] = rhs(1, 3);

            this->mat[2][0] = rhs(2, 0);
            this->mat[2][1] = rhs(2, 1);
            this->mat[2][3] = rhs(2, 2);
            this->mat[2][4] = rhs(2, 3);

            this->mat[3][0] = rhs(3, 0);
            this->mat[3][1] = rhs(3, 1);
            this->mat[3][2] = rhs(3, 2);
            this->mat[3][3] = rhs(3, 3);
        }
        return *this;
    }
}


#endif //ODINMATH_MATRIX4_H
