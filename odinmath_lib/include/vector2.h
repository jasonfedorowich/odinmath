//
// Created by Jason Fedorowich on 2024-03-02.
//

#ifndef ODINMATH_VECTOR2_H
#define ODINMATH_VECTOR2_H

#include "odinmath.h"

namespace OdinMath {

    template<typename real>
    class Vector2 : public Vector<2, real> {
    public:
        Vector2(real x, real y) {
            this->data[0] = x;
            this->data[1] = y;
        }

        virtual ~Vector2() = default;

        Vector2() {
            this->data[0] = (real) 0.0;
            this->data[1] = (real) 0.0;
        }

        Vector2(const Vector2<real> &v) { *this = v; }

        real getX() const {
            return this->data[0];
        }

        real getY() const {
            return this->data[1];
        }

        virtual void setX(real x) {
            this->data[0] = x;
        }

        virtual void setY(real y) {
            this->data[1] = y;
        }

        Vector2<real> operator+(const Vector2<real> &rhs);

        Vector2<real> operator+(Vector2<real> &&rhs);

        Vector2<real> &operator=(const Vector2<real> &v);

        void operator+=(const Vector2<real> &rhs);

        void operator+=(const Vector2<real> &&rhs);

        virtual void operator/=(real c);

        virtual void operator*=(real val);

        Vector2<real> operator*(real val);

        bool operator==(const Vector2<real> &rhs) const;

        real dot(const Vector2<real> &rhs);

    };


#if defined(INTRIN) && (defined(__aarch64__) || defined(__x86_64__))

    class Vector2Float : public Vector4Float {
    public:
        Vector2Float(float x, float y) : Vector4Float(x, y, 0.f, 0.f) {}

        explicit Vector2Float(FloatVector128 &v) : Vector4Float(v) {};

        explicit Vector2Float(FloatVector128 &&v) : Vector4Float(v) {};

        explicit Vector2Float(Vector2<float> &vector) : Vector2Float(vector[0], vector[1]) {};

        explicit Vector2Float(Vector2<float> &&vector) : Vector2Float(vector[0], vector[1]) {};

        Vector2Float() : Vector2Float(0.f, 0.f) {};

        ~Vector2Float() = default;

        float getZ() override {
            throw UnimplementedException("No Z parameter for size 2 vectors");
        }

        float getW() override {
            throw UnimplementedException("No W parameter for size 2 vectors");
        }

        void setZ(float z) override {
            throw UnimplementedException("No Z parameter for size 2 vectors");
        }

        void setW(float w) override {
            throw UnimplementedException("No W parameter for size 2 vectors");
        }

        Vector2Float &operator=(const Vector2Float &v);

        Vector2Float operator+(const Vector2Float &rhs);

        Vector2Float operator+(Vector2Float &&rhs);

        void operator+=(const Vector2Float &rhs);

        void operator+=(const Vector2Float &&rhs);

        void operator/=(float c) override;

        void operator*=(float val) override;

        Vector2Float operator*(float val);

        float dot(const Vector2Float &rhs);

        void getData(float *data) override;

    };


#endif



    template<typename real>
    inline Vector2<real> operator*(real c, Vector2<real> &rhs) {
        real x = c * rhs[0];
        real y = c * rhs[1];
        return {x, y};
    }

    template<typename real>
    inline Vector2<real> operator*(real c, Vector2<real> &&rhs) {
        real x = c * rhs[0];
        real y = c * rhs[1];
        return {x, y};
    }

    template<typename real>
    inline void operator*=(real c, Vector2<real> &rhs) {
        rhs[0] *= c;
        rhs[1] *= c;
    }

    template<typename real>
    inline bool Vector2<real>::operator==(const Vector2<real> &rhs) const {
        return this->data[0] == rhs[0] && this->data[1] == rhs[1];
    }

    template<typename real>
    real Vector2<real>::dot(const Vector2<real> &rhs) {
        return (*this)[0] * rhs[0] + (*this)[1] * rhs[1];
    }

    template<typename real>
    Vector2<real> Vector2<real>::operator*(real val) {
        return Vector2<real>((*this)[0] * val, (*this)[1] * val);
    }

    template<typename real>
    void Vector2<real>::operator*=(real val) {
        (*this)[0] *= val;
        (*this)[1] *= val;
    }

    template<typename real>
    void Vector2<real>::operator/=(real c) {
        (*this)[0] /= c;
        (*this)[1] /= c;

    }

    template<typename real>
    void Vector2<real>::operator+=(const Vector2<real> &&rhs) {
        (*this)[0] += rhs[0];
        (*this)[1] += rhs[1];
    }

    template<typename real>
    void Vector2<real>::operator+=(const Vector2<real> &rhs) {
        (*this)[0] += rhs[0];
        (*this)[1] += rhs[1];
    }

    template<typename real>
    Vector2<real> &Vector2<real>::operator=(const Vector2<real> &v) {
        if (this != &v) {
            (*this)[0] = v[0];
            (*this)[1] = v[1];
        }
        return *this;
    }

    template<typename real>
    Vector2<real> Vector2<real>::operator+(Vector2<real> &&rhs) {
        return Vector2<real>((*this)[0] + rhs.getX(), (*this)[1] + rhs.getY());
    }

    template<typename real>
    Vector2<real> Vector2<real>::operator+(const Vector2<real> &rhs) {
        return Vector2<real>((*this)[0] + rhs.getX(), (*this)[1] + rhs.getY());
    }


}


#endif //ODINMATH_VECTOR2_H
