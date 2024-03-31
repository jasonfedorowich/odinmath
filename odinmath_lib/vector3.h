//
// Created by Jason Fedorowich on 2024-02-03.
//

#ifndef ODINMATH_VECTOR3_H
#define ODINMATH_VECTOR3_H

#include "odinmath.h"

namespace OdinMath {

    template<typename real>
    class Vector3 : public Vector<3, real> {

    public:
        Vector3(real x, real y, real z) {
            this->data[0] = x;
            this->data[1] = y;
            this->data[2] = z;
        }

        virtual ~Vector3() = default;

        Vector3() {
            this->data[0] = (real) 0.0;
            this->data[1] = (real) 0.0;
            this->data[2] = (real) 0.0;
        }

        Vector3(const Vector3<real> &v) { *this = v; }

        real getX() const {
            return this->data[0];
        }

        real getY() const {
            return this->data[1];
        }

        real getZ() const {
            return this->data[2];
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

        Vector3<real> operator+(const Vector3<real> &rhs);

        Vector3<real> operator+(Vector3<real> &&rhs);

        Vector3<real> &operator=(const Vector3<real> &v);

        void operator+=(const Vector3<real> &rhs);

        void operator+=(const Vector3<real> &&rhs);

        virtual void operator/=(real c);

        virtual void operator*=(real val);

        Vector3<real> operator*(real val);

        real dot(const Vector3<real> &rhs);

        Vector3<real> cross(const Vector3<real> &rhs);

    };

#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))

    //todo should remove this superclass
    class Vector3Float : public Vector<3, float> {
    private:
        FloatVector128 floatVector128;
    public:
        Vector3Float(float x, float y, float z) {
            this->data[0] = x;
            this->data[1] = y;
            this->data[2] = z;
            this->floatVector128 = load3(this->data);
        }

        Vector3Float(FloatVector128& v){
            store3(this->data, v);
            this->floatVector128 = v;
        };

        Vector3Float(FloatVector128&& v){
            store3(this->data, v);
            this->floatVector128 = v;
        };

        explicit Vector3Float(Vector3<float> &vector3) : Vector3Float(vector3[0], vector3[1], vector3[2]) {};

        explicit Vector3Float(Vector3<float> &&vector3) : Vector3Float(vector3[0], vector3[1], vector3[2]) {};

        Vector3Float() : Vector3Float(0.f, 0.f, 0.f) {};

        ~Vector3Float() override = default;


        float getX() {
            store3(this->data, this->floatVector128);
            return this->data[0];
        }

        float getY() {
            store3(this->data, this->floatVector128);
            return this->data[1];
        }

        float getZ() {
            store3(this->data, this->floatVector128);
            return this->data[2];
        }

        void setX(float x);

        void setY(float y);

        void setZ(float z);


        Vector3Float &operator=(const Vector3Float &v);

        Vector3Float operator+(const Vector3Float &rhs);

        Vector3Float operator+(Vector3Float &&rhs);

        void operator+=(const Vector3Float &rhs);

        void operator+=(const Vector3Float &&rhs);

        void operator/=(float c);

        void operator*=(float val);

        Vector3Float operator*(float val);

        float dot(const Vector3Float &rhs);

        Vector3Float cross(const Vector3Float &rhs);

        const float &operator[](int idx) const override;

        float &operator[](int idx) override;

        const float *getData() override;

    };

#endif


    template<typename real>
    Vector3<real> Vector3<real>::cross(const Vector3<real> &rhs) {
        real x = this->getY() * rhs.getZ() - this->getZ() * rhs.getY();
        real y = this->getZ() * rhs.getX() - this->getX() * rhs.getZ();
        real z = this->getX() * rhs.getY() - this->getY() * rhs.getX();
        return {x, y, z};
    }

    template<typename real>
    real Vector3<real>::dot(const Vector3<real> &rhs) {
        return rhs.data[0] * this->data[0] + rhs.data[1] * this->data[1] + rhs.data[2] * this->data[2];
    }

    template<typename real>
    Vector3<real> Vector3<real>::operator*(real val) {
        return Vector3<real>(val * this->data[0], val * this->data[1], val * this->data[2]);
    }

    template<typename real>
    void Vector3<real>::operator*=(real val) {
        this->data[0] *= val;
        this->data[1] *= val;
        this->data[2] *= val;
    }

    template<typename real>
    void Vector3<real>::operator/=(real c) {
        this->data[0] /= c;
        this->data[1] /= c;
        this->data[2] /= c;
    }

    template<typename real>
    inline Vector3<real> operator*(real c, Vector3<real> &rhs) {
        real x = c * rhs[0];
        real y = c * rhs[1];
        real z = c * rhs[2];
        return {x, y, z};
    }

    template<typename real>
    inline Vector3<real> operator*(real c, Vector3<real> &&rhs) {
        real x = c * rhs[0];
        real y = c * rhs[1];
        real z = c * rhs[2];
        return {x, y, z};
    }

    template<typename real>
    inline void operator*=(real c, Vector3<real> &rhs) {
        rhs[0] *= c;
        rhs[1] *= c;
        rhs[2] *= c;
    }

    template<typename real>
    inline Vector3<real> &Vector3<real>::operator=(const Vector3 &v) {
        if (this != &v) {
            (*this)[0] = v[0];
            (*this)[1] = v[1];
            (*this)[2] = v[2];
        }
        return *this;
    }

    template<typename real>
    void Vector3<real>::operator+=(const Vector3<real> &&rhs) {
        (*this)[0] += rhs[0];
        (*this)[1] += rhs[1];
        (*this)[2] += rhs[2];
    }

    template<typename real>
    void Vector3<real>::operator+=(const Vector3<real> &rhs) {
        (*this)[0] += rhs[0];
        (*this)[1] += rhs[1];
        (*this)[2] += rhs[2];
    }

    template<typename real>
    Vector3<real> Vector3<real>::operator+(Vector3<real> &&rhs) {
        return Vector3<real>((*this)[0] + rhs[0], (*this)[1] + rhs[1], (*this)[2] + rhs[2]);
    }

    template<typename real>
    Vector3<real> Vector3<real>::operator+(const Vector3<real> &rhs) {
        return Vector3<real>((*this)[0] + rhs[0], (*this)[1] + rhs[1], (*this)[2] + rhs[2]);
    }



}


#endif //ODINMATH_VECTOR3_H
