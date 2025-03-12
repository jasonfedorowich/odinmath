//
// Created by Jason Fedorowich on 2024-03-02.
//

#ifndef ODINMATH_VECTOR4_H
#define ODINMATH_VECTOR4_H

#include "odinmath.h"

namespace OdinMath {

    template<typename real>
    class Vector4 : public Vector<4, real> {

    public:
        Vector4(real x, real y, real z, real w) {
            this->data[0] = x;
            this->data[1] = y;
            this->data[2] = z;
            this->data[3] = w;
        }

        virtual ~Vector4() = default;

        Vector4() {
            this->data[0] = (real) 0.0;
            this->data[1] = (real) 0.0;
            this->data[2] = (real) 0.0;
            this->data[3] = (real) 0.0;
        }

        Vector4(const Vector4<real> &v) { *this = v; }

        real getX() const {
            return this->data[0];
        }

        real getY() const {
            return this->data[1];
        }

        real getZ() const {
            return this->data[2];
        }

        real getW() const {
            return this->data[3];
        }

        virtual void setX(real x) {
            this->data[0] = x;
        }

        virtual void setY(real y) {
            this->data[1] = y;
        }

        virtual void setZ(real z) {
            this->data[2] = z;
        }

        virtual void setW(real w) {
            this->data[2] = w;
        }

        Vector4<real> operator+(const Vector4<real> &rhs);

        Vector4<real> operator+(Vector4<real> &&rhs);

        Vector4<real> &operator=(const Vector4<real> &v);

        void operator+=(const Vector4<real> &rhs);

        void operator+=(const Vector4<real> &&rhs);

        virtual void operator/=(real c);

        virtual void operator*=(real c);

        Vector4<real> operator*(real c);

        bool operator==(const Vector4<real> &v) const;

        real dot(const Vector4<real> &rhs) const;

        Vector4<real> project(const Vector4<real>& b);

    };



#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))

    class Vector4Float {
    protected:
        FloatVector128 floatVector128;
    public:
        Vector4Float(float x, float y, float z, float w) {
            float tmp[4];
            tmp[0] = x;
            tmp[1] = y;
            tmp[2] = z;
            tmp[3] = w;
            this->floatVector128 = load4(tmp);
        }

        explicit Vector4Float(const float *vector) {
            this->floatVector128 = load4(vector);
        }

        explicit Vector4Float(FloatVector128 &v) {
            this->floatVector128 = v;
        };

        explicit Vector4Float(FloatVector128 &&v) {
            this->floatVector128 = v;
        };

        explicit Vector4Float(Vector4<float> &vector3) : Vector4Float(vector3[0], vector3[1], vector3[2],
                                                                      vector3[3]) {};

        explicit Vector4Float(Vector4<float> &&vector3) : Vector4Float(vector3[0], vector3[1], vector3[2],
                                                                       vector3[3]) {};

        Vector4Float() {};

        virtual ~Vector4Float() = default;

        FloatVector128 getVector() { return this->floatVector128; }

        float getX() {
            return GET_LANE_VECTOR(this->floatVector128, 0);
        }

        float getY() {
            return GET_LANE_VECTOR(this->floatVector128, 1);
        }

        virtual float getZ() {
            return GET_LANE_VECTOR(this->floatVector128, 2);
        }

        virtual float getW() {
            return GET_LANE_VECTOR(this->floatVector128, 3);
        }

        void setX(float x);

        void setY(float y);

        virtual void setZ(float z);

        virtual void setW(float w);

        Vector4Float &operator=(const Vector4Float &v);

        Vector4Float operator+(const Vector4Float &rhs);

        Vector4Float operator+(Vector4Float &&rhs);

        void operator+=(const Vector4Float &rhs);

        void operator+=(const Vector4Float &&rhs);

        virtual void operator/=(float c);

        virtual void operator*=(float c);

        Vector4Float operator*(float val);

        bool operator==(const Vector4Float &v) const;

        //todo make getData(Vector4* out)
        virtual void getData(float *data);

        float dot(const Vector4Float &rhs);

        Vector4Float cross(const Vector4Float &rhs);

        Vector4Float project(const Vector4Float& b);


    };


#endif

    template<typename real>
    Vector4<real> Vector4<real>::project(const Vector4<real>& b) {
        real ab = dot(b);
        real bb = b.dot(b);
        return (ab / bb) * b;
    }

    template<typename real>
    inline Vector4<real> operator*(real c, const Vector4<real> &rhs) {
        real x = c * rhs[0];
        real y = c * rhs[1];
        real z = c * rhs[2];
        real w = c * rhs[3];
        return {x, y, z, w};
    }

    template<typename real>
    inline Vector4<real> operator*(real c, const Vector4<real> &&rhs) {
        real x = c * rhs[0];
        real y = c * rhs[1];
        real z = c * rhs[2];
        real w = c * rhs[3];
        return {x, y, z, w};
    }

    template<typename real>
    inline void operator*=(real c, Vector4<real> &rhs) {
        rhs[0] *= c;
        rhs[1] *= c;
        rhs[2] *= c;
        rhs[3] *= c;
    }


    template<typename real>
    real Vector4<real>::dot(const Vector4<real> &rhs) const {
        return (*this)[0] * rhs[0] + (*this)[1] * rhs[1] + (*this)[2] * rhs[2] + (*this)[3] * rhs[3];
    }

    template<typename real>
    Vector4<real> Vector4<real>::operator*(real c) {
        return Vector4<real>(c * (*this)[0], c * (*this)[1], c * (*this)[2], c * (*this)[3]);
    }

    template<typename real>
    void Vector4<real>::operator*=(real c) {
        (*this)[0] *= c;
        (*this)[1] *= c;
        (*this)[2] *= c;
        (*this)[3] *= c;

    }

    template<typename real>
    void Vector4<real>::operator/=(real c) {
        (*this)[0] /= c;
        (*this)[1] /= c;
        (*this)[2] /= c;
        (*this)[3] /= c;
    }

    template<typename real>
    void Vector4<real>::operator+=(const Vector4<real> &&rhs) {
        (*this)[0] += rhs[0];
        (*this)[1] += rhs[1];
        (*this)[2] += rhs[2];
        (*this)[3] += rhs[3];
    }

    template<typename real>
    void Vector4<real>::operator+=(const Vector4<real> &rhs) {
        (*this)[0] += rhs[0];
        (*this)[1] += rhs[1];
        (*this)[2] += rhs[2];
        (*this)[3] += rhs[3];
    }

    template<typename real>
    Vector4<real> &Vector4<real>::operator=(const Vector4<real> &v) {
        if (this != &v) {
            (*this)[0] = v[0];
            (*this)[1] = v[1];
            (*this)[2] = v[2];
            (*this)[3] = v[3];
        }
        return *this;
    }

    template<typename real>
    Vector4<real> Vector4<real>::operator+(Vector4<real> &&rhs) {
        return Vector4<real>((*this)[0] + rhs[0], (*this)[1] + rhs[1], (*this)[2] + rhs[2], (*this)[3] + rhs[3]);
    }

    template<typename real>
    Vector4<real> Vector4<real>::operator+(const Vector4<real> &rhs) {
        return Vector4<real>((*this)[0] + rhs[0], (*this)[1] + rhs[1], (*this)[2] + rhs[2], (*this)[3] + rhs[3]);
    }

    template<typename real>
    bool Vector4<real>::operator==(const Vector4<real> &v) const {
        return (v[0] == this->data[0] && v[1] == this->data[1] && v[2] == this->data[2] && v[3] == this->data[3]);
    }

}


#endif //ODINMATH_VECTOR4_H
