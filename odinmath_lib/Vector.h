//
// Created by Jason Fedorowich on 2024-02-18.
//

#ifndef ODINMATH_VECTOR_H
#define ODINMATH_VECTOR_H

#include "odinmath.h"

namespace OdinMath {
    template<int SIZE, typename real>
    class Vector {
    protected:
        real data[SIZE];
    public:
        virtual const real &operator[](int idx) const;

        virtual real &operator[](int idx);

        virtual const real *getData() {
            return data;
        }

        virtual ~Vector() = default;

        //todo
        struct Iterator{
            Vector<SIZE, real>* vector;
            int element;
            explicit Iterator(Vector<SIZE, real>* vector) : vector(vector), element(0) { }
            Iterator(Vector<SIZE, real>* vector, int element) : vector(vector), element(element) {}
            Iterator() {}
            Iterator& operator++() {
                ++element;
                return *this;
            }
            real operator*(){ return (*vector)[0]; }
            friend bool operator==(const Iterator& a, const Iterator& b) { return a.row == b.row; }
            friend bool operator!=(const Iterator& a, const Iterator& b) { return a.row != b.row; }

            virtual ~Iterator() = default;
        };

        Iterator& begin() { return Iterator(*this); }
        Iterator& end() { return Iterator(*this, SIZE); }
    };

    template<int SIZE, typename real>
    inline real &Vector<SIZE, real>::operator[](int idx) {
        if (idx < 0 || idx >= SIZE) {
            throw InvalidArgument("Cannot index Vector; invalid index");
        }
        return data[idx];
    }

    template<int SIZE, typename real>
    inline const real &Vector<SIZE, real>::operator[](int idx) const {
        if (idx < 0 || idx >= SIZE) {
            throw InvalidArgument("Cannot index Vector; invalid index");
        }
        return data[idx];
    }


}


#endif //ODINMATH_VECTOR_H
