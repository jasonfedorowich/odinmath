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
