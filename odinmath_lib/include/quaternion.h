//
// Created by Jason Fedorowich on 2024-06-07.
//

#ifndef ODINMATH_QUATERNION_H
#define ODINMATH_QUATERNION_H

#include <ostream>
#include "odinmath.h"

namespace OdinMath{

    //todo  Rodrigues' Formula

    //* Quaternion's are of the form x*i + y*j + k*z + w where i, j, k are complex, quaternion are also normalized *//
    template<typename real>
    class Quaternion : public Vector<4, real>{
    public:

        Quaternion() : Vector<4, real>(){}

        Quaternion(const Quaternion<real>& q){
            *this = q;
        }

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

        virtual ~Quaternion() = default;


        Quaternion<real> operator*();

        Quaternion<real> operator+(const Quaternion<real>& rhs);
        Quaternion<real> operator-(const Quaternion<real>& rhs);
        Quaternion<real> operator*(const Quaternion<real>& rhs);
        Quaternion<real> &operator=(const Quaternion<real>& rhs);
        bool operator==(const Quaternion<real>& rhs) const;

        real length();

        void normalize();

        /* Same operation as operator*() */
        Quaternion<real> conjugate();


        bool isNormalized(real& length, real eps);
    };

#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))

    class QuaternionFloat{
    protected:
        FloatVector128 floatVector128{};
    public:

        QuaternionFloat(FloatVector128& v){
            this->floatVector128 = v;
            normalize();
        }

        QuaternionFloat(FloatVector128&& v) : QuaternionFloat(v){

        }

        QuaternionFloat(const QuaternionFloat& q){
            *this = q;
        }

        QuaternionFloat() = default;

        QuaternionFloat(float x, float y, float z, float w){
            float tmp[4];
            tmp[0] = x;
            tmp[1] = y;
            tmp[2] = z;
            tmp[3] = w;
            this->floatVector128 = load4(tmp);
            normalize();
        }

        QuaternionFloat(float roll, float pitch, float yaw){
            float tmp[4];
            tmp[0] = roll;
            tmp[1] = pitch;
            tmp[2] = yaw;
            tmp[3] = 0.0f;
            FloatVector128 v = load4(tmp);
            v = div(v, two.v);
            FloatVector128 c1 = cosF(v);
            FloatVector128 s1 = sinF(v);

            FloatVector128 t1 = dupX(c1);
            t1 = COPY_LANE(t1, 0, s1, 0);
            FloatVector128 t2 = dupY(c1);
            t2 = COPY_LANE(t2, 1, s1, 1);
            FloatVector128 t3 = dupZ(c1);
            t3 = COPY_LANE(t3, 2, s1, 2);

            t1 = mul(t1, mul(t2, t3));

            FloatVector128 t4 = dupX(s1);
            t4 = COPY_LANE(t4, 0, c1, 0);
            t2 = dupY(s1);
            t2 = COPY_LANE(t2, 1, c1, 1);
            t3 = dupZ(s1);
            t3 = COPY_LANE(t3, 2, c1, 1);
            t3 = COPY_LANE(t3, 3, s1, 1);

            t2 = mul(t4, mul(t2, t3));

            VectorFloat32 m = {{-1.f, 1.f, -1.f, 1.f}};

            t2 = mul(m.v, t2);
            this->floatVector128 = add(t1, t2);
        }
        QuaternionFloat(float angle, FloatVector128& axis){
            FloatVector128 v = duplicate(angle / 2.f);
            FloatVector128 s = sinF(v);
            FloatVector128 c = cosF(v);
            FloatVector128 t = mul(s, axis);
            this->floatVector128 = COPY_LANE(t, 3, c, 0);

        }
        QuaternionFloat(float angle, Vector4Float& axis){
            FloatVector128 v = duplicate(angle / 2.f);
            FloatVector128 s = sinF(v);
            FloatVector128 c = cosF(v);
            FloatVector128 t = mul(s, axis.getVector());
            this->floatVector128 = COPY_LANE(t, 3, c, 0);

        }

        explicit QuaternionFloat(Matrix3Float& m){
            FloatVector128 t = m.trace().getVector();
            IntegerVector128 c1 = greaterThan(t, zero.v);


            FloatMatrix128x4 fm = Matrix4Float::to(m);
            FloatVector128 _00 = dupX(fm.vectors[0]);
            FloatVector128 _11 = dupY(fm.vectors[1]);
            FloatVector128 _22 = dupZ(fm.vectors[2]);

            FloatVector128 _01 = dupY(fm.vectors[0]);
            FloatVector128 _02 = dupZ(fm.vectors[0]);

            FloatVector128 _10 = dupX(fm.vectors[1]);
            FloatVector128 _12 = dupZ(fm.vectors[1]);

            FloatVector128 _20 = dupX(fm.vectors[2]);
            FloatVector128 _21 = dupY(fm.vectors[2]);

            VectorFloat32 m1 = {{1.f, 1.f, 1.f, -1.f}};
            float32x4_t _25 = duplicate(0.25f);


            IntegerVector128 c2 = _and(greaterThan(_00, _11), greaterThan(_00, _11));
            IntegerVector128 c3 = greaterThan(_11, _22);

            FloatVector128 k1 = mul(duplicate(2.f), sqrtF(add(one.v, t)));
            k1 = invert(k1);

            //todo in here
            FloatVector128 v1 = _21;
            v1 = COPY_LANE(v1, 1, _02, 2);
            v1 = COPY_LANE(v1, 2, _10, 0);
            v1 = COPY_LANE(v1, 3, div(_25, k1), 0);

            FloatVector128 v2 = _12;
            v2 = COPY_LANE(v2, 1, _20, 0);
            v2 = COPY_LANE(v2, 2, _01, 1);
            v2 = COPY_LANE(v2, 3, zero.v, 0);

            v1 = sub(v1, v2);
            k1 = COPY_LANE(k1, 3, one.v, 0);
            v1 = mul(k1, v1);
            //in here
            FloatVector128 k2 = one.v;
            k2 = add(k2, _00);
            k2 = sub(k2, _11);
            k2 = sub(k2, _22);
            k2 = sqrtF(k2);
            k2 = mul(two.v, k2);

            FloatVector128 v3 = mul(_25, k2);
            v3 = COPY_LANE(v3, 1, _01, 1);
            v3 = COPY_LANE(v3, 2, _02, 2);
            v3 = COPY_LANE(v3, 3, _21, 1);

            FloatVector128 v4 = zero.v;
            v4 = COPY_LANE(v4, 1, _10, 0);
            v4 = COPY_LANE(v4, 2, _20, 0);
            v4 = COPY_LANE(v4, 3, _12, 2);

            v4 = mul(v4, m1.v);
            v3 = add(v3, v4);

            k2 = invert(k2);
            k2 = COPY_LANE(k2, 0, one.v, 0);
            v3 = mul(k2, v3);

            FloatVector128 k3 = one.v;
            k3 = add(k3, _11);
            k3 = sub(k3, _00);
            k3 = sub(k3, _22);
            k3 = sqrtF(k3);
            k3 = mul(two.v, k3);

            FloatVector128 v5 = mul(_25, k3);
            v5 = COPY_LANE(v5, 0, _01, 0);
            v5 = COPY_LANE(v5, 2, _12, 0);
            v5 = COPY_LANE(v5, 3, _02, 0);

            FloatVector128 v6 = zero.v;
            v6 = COPY_LANE(v6, 0, _10, 0);
            v6 = COPY_LANE(v6, 2, _21, 0);
            v6 = COPY_LANE(v6, 3, _20, 0);
            v6 = mul(v6, m1.v);

            v5 = add(v5, v6);
            k3 = invert(k3);
            k3 = COPY_LANE(k3, 1, one.v, 0);
            v5 = mul(v5, k3);

            FloatVector128 k4 = one.v;
            k4 = add(k4, _22);
            k4 = sub(k4, _00);
            k4 = sub(k4, _11);
            k4 = mul(two.v, sqrtF(k4));

            FloatVector128 v7 = mul(k4, _25);
            v7 = COPY_LANE(v7, 0, _02, 0);
            v7 = COPY_LANE(v7, 1, _12, 0);
            v7 = COPY_LANE(v7, 3, _10, 0);

            FloatVector128 v8 = zero.v;
            v8 = COPY_LANE(v8, 0, _20, 0);
            v8 = COPY_LANE(v8, 1, _21, 0);
            v8 = COPY_LANE(v8, 3, _01, 0);

            v8 = mul(m1.v, v8);
            v7 = add(v7, v8);

            k4 = invert(k4);
            k4 = COPY_LANE(k4, 2, one.v, 0);
            v7 = mul(k4, v7);

            this->floatVector128 = condSelect(c1, v1, condSelect(c2, v3, condSelect(c3, v5, v7)));

        }

        friend std::ostream &operator<<(std::ostream &os, const QuaternionFloat &aFloat);

        QuaternionFloat operator*();
        QuaternionFloat operator+(const QuaternionFloat& rhs);
        QuaternionFloat operator-(const QuaternionFloat& rhs);
        QuaternionFloat operator*(const QuaternionFloat& rhs);
        QuaternionFloat &operator=(const QuaternionFloat&  rhs);
        bool operator==(const QuaternionFloat& rhs) const;

        void normalize();

        float length();

        /* Same operation as operator*() */
        QuaternionFloat conjugate();

        bool isNormalized(float& length, float eps);

        float getX(){
            return GET_LANE_VECTOR(this->floatVector128, 0);
        }

        float getY(){
            return GET_LANE_VECTOR(this->floatVector128, 1);
        }

        float getZ(){
            return GET_LANE_VECTOR(this->floatVector128, 2);
        }

        float getW(){
            return GET_LANE_VECTOR(this->floatVector128, 3);
        }

        void setX(float x);
        void setY(float y);
        void setZ(float z);
        void setW(float w);

        friend void toRotationMatrix(Matrix3Float& rotation, QuaternionFloat& q);

        friend void toAngleAxis(float* angle, Vector3Float& axis, QuaternionFloat& q);

        friend void toRollPitchYaw(float* angles, QuaternionFloat& q);

    };


    inline void toRotationMatrix(Matrix3Float& rotation, QuaternionFloat& q){

        FloatVector128 _00 = dupX(q.floatVector128);
        FloatVector128 _11 = dupY(q.floatVector128);
        FloatVector128 _22 = dupZ(q.floatVector128);

        FloatVector128 t0 = mul(_00, q.floatVector128);
        FloatVector128 t1 = mul(_11, q.floatVector128);
        FloatVector128 t2 = mul(_22, q.floatVector128);

        t0 = mul(t0, two.v);
        t1 = mul(t1, two.v);
        t2 = mul(t2, two.v);

        VectorFloat32 m1 = {{-1.f, -1.f, 1.f, 1.f}};

        FloatVector128 x1 = dupY(t1);
        x1 = sub(one.v, x1);

        x1 = COPY_LANE(x1, 1, t0, 1);
        x1 = COPY_LANE(x1, 2, t0, 2);

        FloatVector128 x2 = dupZ(t2);
        x2 = COPY_LANE(x2, 1, t2, 3);
        x2 = COPY_LANE(x2, 2, t1, 3);

        x1 = add(x1, mul(m1.v, x2));

        FloatVector128 x3 = dupX(t0);
        x3 = sub(one.v, x3);
        x3 = COPY_LANE(x3, 0, t0, 1);
        x3 = COPY_LANE(x3, 2, t1, 2);

        VectorFloat32 m2 = {{1.f, -1.f, -1.f, 1.f}};

        FloatVector128 x4 = dupZ(t2);
        x4 = COPY_LANE(x4, 0, t2, 3);
        x4 = COPY_LANE(x4, 2, t0, 3);

        x3 = add(x3, mul(m2.v, x4));

        FloatVector128 x5 = dupX(t0);
        x5 = sub(one.v, x5);
        x5 = COPY_LANE(x5, 0, t0, 2);
        x5 = COPY_LANE(x5, 1, t1, 2);

        VectorFloat32 m3 = {{-1.f, 1.f, -1.f, 1.f}};

        FloatVector128 x6 = dupY(t1);
        x6 = COPY_LANE(x6, 0, t1, 3);
        x6 = COPY_LANE(x6, 1, t0, 3);

        x5 = add(x5, mul(m3.v, x6));

        rotation.load(FloatMatrix128x4(x1, x3, x5, x1));
    }

    inline void toAngleAxis(float* angle, Vector3Float& axis, QuaternionFloat& q){
        FloatVector128 ang = OdinMath::arcCosF(dupW(q.floatVector128));
        ang = mul(two.v, ang);
        FloatVector128 a = div(ang, two.v);
        FloatVector128 invS = div(one.v, OdinMath::sinF(a));

        axis = Vector3Float(mul(q.floatVector128, invS));
        store2(angle, ang);
    }

    inline void toRollPitchYaw(float* angles, QuaternionFloat& q){
        FloatVector128 qq = mul(q.floatVector128, q.floatVector128);
        FloatVector128 _w = dupW(q.floatVector128);
        FloatVector128 _y = dupY(q.floatVector128);
        FloatVector128 _x = dupX(q.floatVector128);

        FloatVector128 _wq = mul(q.floatVector128, _w);
        FloatVector128 _yq = mul(q.floatVector128, _y);
        FloatVector128 _xq = mul(q.floatVector128, _x);

        FloatVector128 tmp1 = COPY_LANE(_yq, 0, _yq, 2);
        tmp1 = COPY_LANE(tmp1, 1, _xq, 2);
        tmp1 = COPY_LANE(tmp1, 2, _xq, 1);

        VectorFloat32 m1 = {{1.f, -1.f, 1.f, 1.f}};
        tmp1 = mul(m1.v, tmp1);
        tmp1 = add(_wq, tmp1);
        tmp1 = mul(two.v, tmp1);

        FloatVector128 ww = dupW(qq);
        FloatVector128 xx = dupX(qq);
        FloatVector128 yy = dupY(qq);
        FloatVector128 zz = dupZ(qq);

        VectorFloat32 m2 = {{-1.f, 1.f, 1.f, 1.f}};
        VectorFloat32 m3 = {{-1.f, -1.f, 1.f, 1.f}};

        FloatVector128 tmp2 = mul(m2.v, xx);
        tmp2 = add(ww, tmp2);
        tmp2 = add(mul(m3.v, yy), tmp2);
        tmp2 = add(mul(m1.v, zz), tmp2);
        tmp2 = COPY_LANE(tmp2, 2, tmp2, 1);

        FloatVector128 _angles = OdinMath::arcTan2F(tmp1, tmp2);
        FloatVector128 _pitch = OdinMath::arcSinF(tmp1);

        FloatVector128 v = COPY_LANE(_angles, 1, _pitch, 1);
        v = COPY_LANE(v, 2, _angles, 2);

        store3(angles, v);
    }

#endif

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
    bool Quaternion<real>::operator==(const Quaternion<real> &rhs) const {
        return (this->data[0] == rhs[0]
        && this->data[1] == rhs[1]
        && this->data[2] == rhs[2]
        && this->data[3] == rhs[3]);
    }


    template<typename real>
    Quaternion<real> Quaternion<real>::operator*(const Quaternion<real> &rhs) {
        real r1 = this->data[3] * rhs[0] + this->data[0] * rhs[3] + this->data[1] * rhs[2] - this->data[2] * rhs[1];
        real r2 = this->data[3] * rhs[1] - this->data[0] * rhs[2] + this->data[1] * rhs[3] + this->data[2] * rhs[0];
        real r3 = this->data[3] * rhs[2] + this->data[0] * rhs[1] - this->data[1] * rhs[0] + this->data[2] * rhs[3];
        real r4 = this->data[3] * rhs[3] - this->data[0] * rhs[0] - this->data[1] * rhs[1] - this->data[2] * rhs[2];
        return Quaternion<real>(r1, r2, r3, r4);
    }

    template<typename real>
    Quaternion<real> Quaternion<real>::operator-(const Quaternion<real> &rhs) {
        return Quaternion<real>(
                this->data[0] - rhs[0],
                this->data[1] - rhs[1],
                this->data[2] - rhs[2],
                this->data[3] - rhs[3]
        );
    }

    template<typename real>
    Quaternion<real> Quaternion<real>::operator+(const Quaternion<real> &rhs) {
        return Quaternion<real>(
                this->data[0] + rhs[0],
                this->data[1] + rhs[1],
                this->data[2] + rhs[2],
                this->data[3] + rhs[3]
                );
    }

    template<typename real>
    Quaternion<real> &Quaternion<real>::operator=(const Quaternion<real> &rhs) {
        if(this != &rhs){
            this->data[0] = rhs[0];
            this->data[1] = rhs[1];
            this->data[2] = rhs[2];
            this->data[3] = rhs[3];
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
        this->data[0] *= invLength;
        this->data[1] *= invLength;
        this->data[2] *= invLength;
        this->data[3] *= invLength;
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
