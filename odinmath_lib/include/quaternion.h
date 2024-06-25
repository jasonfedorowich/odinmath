//
// Created by Jason Fedorowich on 2024-06-07.
//

#ifndef ODINMATH_QUATERNION_H
#define ODINMATH_QUATERNION_H

#include "odinmath.h"

namespace OdinMath{

    //todo  Rodrigues' Formula

    //* Quaternion's are of the form x*i + y*j + k*z + w where i, j, k are complex, quaternion are also normalized *//
    template<typename real>
    class Quaternion : public Vector<4, real>{
    public:

        Quaternion() : Vector<4, real>(){}

        Quaternion(real x, real y, real z, real w){
            this->data[0] = x;
            this->data[1] = y;
            this->data[2] = z;
            this->data[3] = w;
            normalize();
        }

        Quaternion(real angle, const Vector3<real>& axis){
            real halfAngle = angle / 2;
            real sinHalfAngle = sin(halfAngle);
            this->data[0] = axis[0] * sinHalfAngle;
            this->data[1] = axis[1] * sinHalfAngle;
            this->data[2] = axis[2] * sinHalfAngle;
            this->data[3] = cos(halfAngle);
        }

        explicit Quaternion(const Matrix3<real>& m){
            real trace = m(0,0) + m(1,1) + m(2,2);
            if (trace > (real)0.0f)
            {
                real k = (real) 2.0 * sqrt((real)1.0 + trace);
                k = (real)1.0 / k;
                this->data[0] = k * (m(2, 1) - m(1, 2));
                this->data[1] = k * (m(0, 2) - m(2, 0));
                this->data[2] = k * (m(1, 0) - m(0, 1));
                this->data[3] = (real)0.25 / k;
            }else{
                if ((m(0,0) > m(1,1)) && (m(0,0) > m(2,2))){
                    real k = (real)2.0 * sqrt(1.0f + m(0,0) - m(1,1) - m(2, 2));
                    this->data[0] = (real)0.25 * k;
                    k = (real)1.0 / k;
                    this->data[1] = k * (m(0, 1) + m(1, 0));
                    this->data[2] = k * (m(0, 2) + m(2, 0));
                    this->data[3] = k * (m(2, 1) - m(1, 2));
                }else if(m(1,1) > m(2,2)){
                    real k = (real)2.0 * sqrt(1.0f + m(1,1) - m(0,0) - m(2,2));
                    this->data[1] = (real)0.25 * k;
                    k = (real)1.0 / k;
                    this->data[0] = k * (m(0, 1) + m(1, 0));
                    this->data[2] = k * (m(1, 2) + m(2, 1));
                    this->data[3] = k * (m(0, 2) - m(2, 0));
                }else{
                    real k = (real)2.0 * sqrt(1.0f + m(2,2) - m(0,0) - m(1,1));
                    this->data[2] = (real)0.25f * k;
                    k = (real)1.0 / k;
                    this->data[0] = k * (m(0, 2) + m(2, 0));
                    this->data[1] = k * (m(1, 2) + m(2, 1));
                    this->data[3] = k * (m(1, 0) - m(0, 1));
                }
            }


        }

        Quaternion(real roll, real pitch, real yaw){
            real halfRoll = roll / (real) 2.0;
            real halfPitch = pitch / (real) 2.0;
            real halfYaw = yaw / (real) 2.0;

            real cHalfRoll = cos(halfRoll);
            real sHalfRoll = sin(halfRoll);
            real cHalfPitch = cos(halfPitch);
            real sHalfPitch = sin(halfPitch);
            real cHalfYaw = cos(halfYaw);
            real sHalfYaw = sin(halfYaw);

            this->data[0] = sHalfRoll * cHalfPitch * cHalfYaw - cHalfRoll * sHalfPitch * sHalfYaw;
            this->data[1] = cHalfRoll * sHalfPitch * cHalfYaw + sHalfRoll * cHalfPitch * sHalfYaw;
            this->data[2] = cHalfRoll * cHalfPitch * sHalfYaw - sHalfRoll * sHalfPitch * cHalfPitch;
            this->data[3] = cHalfRoll * cHalfPitch * cHalfYaw + sHalfRoll * sHalfPitch * sHalfPitch;
        }


        Quaternion<real> operator*();

        Quaternion<real> operator+(const Quaternion<real>& lhs);
        Quaternion<real> operator-(const Quaternion<real>& lhs);
        Quaternion<real> operator*(const Quaternion<real>& lhs);
        Quaternion<real> &operator=(const Quaternion<real>& lhs);
        bool operator==(const Quaternion<real>& lhs) const;

        real length();

        void normalize();

        /* Same operation as operator*() */
        Quaternion<real> conjugate();


        bool isNormalized(real& length, real eps);
    };

    template<typename real>
    inline void toRotationMatrix(Matrix3<real>& rotation, Quaternion<real>& q){
        real one = (real)1.0;
        real two = (real)2.0;

        real xx = two * q[0] * q[0];
        real yy = two * q[1] * q[1];
        real zz = two * q[2] * q[2];
        real xy = two * q[0] * q[1];
        real zw = two * q[2] * q[3];
        real xz = two * q[0] * q[2];
        real yw = two * q[1] * q[3];
        real yz = two * q[1] * q[2];
        real xw = two * q[0] * q[3];

        rotation(0, 0) = one - yy - zz;
        rotation(0, 1) = xy - zw;
        rotation(0, 2) = xz + yw;

        rotation(1, 0) = xy + zw;
        rotation(1, 1) = one - xx - zz;
        rotation(1, 2) = yz - xw;

        rotation(2, 0) = xz - yw;
        rotation(2, 1) = yz + xw;
        rotation(2, 2) = one - xx - yy;
    }

    template<typename real>
    inline void toAngleAxis(real& angle, Vector3<real>& axis, Quaternion<real>& q){
        real t = (real)2.0;
        angle = t * acos(q[3]);
        real invSinAngleBy2 = ((real)1.0) / sin(angle / t);
        axis[0] = q[0] * invSinAngleBy2;
        axis[1] = q[1] * invSinAngleBy2;
        axis[2] = q[2] * invSinAngleBy2;
    }

    template<typename real>
    inline void toRollPitchYaw(real& roll, real& pitch, real& yaw, Quaternion<real>& q){
        real t = (real)2.0;
        real ww = (q[3] * q[3]);
        real xx = (q[0] * q[0]);
        real yy = (q[1] * q[1]);
        real zz = (q[2] * q[2]);
        real tmp1 = t * (q[3] * q[0] + q[1] * q[2]);
        real tmp2 = ww - xx - yy + zz;
        roll = atan2(tmp1, tmp2);
        tmp1 = t * (q[3] * q[1] - q[0] * q[2]);
        pitch = asin(tmp1);
        tmp1 = t * (q[3] * q[2] + q[0] * q[1]);
        tmp2 = ww + xx - yy - zz;
        yaw = atan2(tmp1, tmp2);
    }

    template<typename real>
    bool Quaternion<real>::operator==(const Quaternion<real> &lhs) const {
        return (this->data[0] == lhs[0]
        && this->data[1] == lhs[1]
        && this->data[2] == lhs[2]
        && this->data[3] == lhs[3]);
    }


    template<typename real>
    Quaternion<real> Quaternion<real>::operator*(const Quaternion<real> &lhs) {
        real r1 = this->data[3] * lhs[0] + this->data[0] * lhs[3] + this->data[1] * lhs[2] - this->data[2] * lhs[1];
        real r2 = this->data[3] * lhs[1] - this->data[0] * lhs[2] + this->data[1] * lhs[3] + this->data[2] * lhs[0];
        real r3 = this->data[3] * lhs[2] + this->data[0] * lhs[1] - this->data[1] * lhs[0] + this->data[2] * lhs[3];
        real r4 = this->data[3] * lhs[3] - this->data[0] * lhs[0] - this->data[1] * lhs[1] - this->data[2] * lhs[2];
        return Quaternion<real>(r1, r2, r3, r4);
    }

    template<typename real>
    Quaternion<real> Quaternion<real>::operator-(const Quaternion<real> &lhs) {
        return Quaternion<real>(
                this->data[0] - lhs[0],
                this->data[1] - lhs[1],
                this->data[2] - lhs[2],
                this->data[3] - lhs[3]
        );
    }

    template<typename real>
    Quaternion<real> Quaternion<real>::operator+(const Quaternion<real> &lhs) {
        return Quaternion<real>(
                this->data[0] + lhs[0],
                this->data[1] + lhs[1],
                this->data[2] + lhs[2],
                this->data[3] + lhs[3]
                );
    }

    template<typename real>
    Quaternion<real> &Quaternion<real>::operator=(const Quaternion<real> &lhs) {
        if(this != &lhs){
            this->data[0] = lhs[0];
            this->data[1] = lhs[1];
            this->data[2] = lhs[2];
            this->data[3] = lhs[3];
        }
        return *this;
    }

    template<typename real>
    Quaternion<real> Quaternion<real>::operator*() {
        return conjugate();
    }

    template<typename real>
    Quaternion<real> Quaternion<real>::conjugate() {
        real negativeOne = (real)-1.0;
        return Quaternion<real>(negativeOne * this->data[0],
                                negativeOne * this->data[1],
                                negativeOne * this->data[2],
                                this->data[3]);
    }

    template<typename real>
    bool Quaternion<real>::isNormalized(real& length, real eps) {
        length = this->length();
        return abs(length - (real)1.0) <= eps;
    }

    template<typename real>
    void Quaternion<real>::normalize() {
        real length = this->length();
        real invLength = (real)1.0 / length;
        this->data[0] * invLength;
        this->data[1] * invLength;
        this->data[2] * invLength;
        this->data[3] * invLength;
    }

    template<typename real>
    real Quaternion<real>::length() {
        return sqrt(this->data[0] * this->data[0]
        + this->data[1] * this->data[1]
        + this->data[2] * this->data[2]
        + this->data[3] * this->data[3]);
    }
}



#endif //ODINMATH_QUATERNION_H
