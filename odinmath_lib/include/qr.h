//
// Created by Jason Fedorowich on 2025-03-17.
//

#ifndef ODINMATH_QR_H
#define ODINMATH_QR_H

#endif //ODINMATH_QR_H
#include "odinmath.h"

namespace OdinMath {

    template<typename real>
    inline void gs(Matrix4<real>& m, Matrix4<real>& Q, Matrix4<real>& R){
        Vector4<real> u1 = m.col(0);
        u1.normalize();
        Vector4<real> u2 = m.col(1);
        u2 = u2 - u2.project(u1);
        u2.normalize();
        Vector4<real> u3 = m.col(2);
        u3 = u3 - u3.project(u2)- u3.project(u1);
        u3.normalize();
        Vector4<real> u4 = m.col(3);
        u4 = u4 - u4.project(u3) - u4.project(u2) - u4.project(u1);
        u4.normalize();

        Q.col(0, u1);
        Q.col(1, u2);
        Q.col(2, u3);
        Q.col(3, u4);
        R = Q.transpose() * m;
    }

    template<typename real>
    inline void gs(Matrix3<real>& m, Matrix3<real>& Q, Matrix3<real>& R){
        Vector3<real> u1 = m.col(0);
        u1.normalize();
        Vector3<real> u2 = m.col(1);
        u2 = u2 - u2.project(u1);
        u2.normalize();
        Vector3<real> u3 = m.col(2);
        u3 = u3 - u3.project(u2) - u3.project(u1);
        u3.normalize();

        Q.col(0, u1);
        Q.col(1, u2);
        Q.col(2, u3);
        R = Q.transpose() * m;
    }

    template<typename real>
    inline void gs(Matrix2<real>& m, Matrix2<real>& Q, Matrix2<real>& R) {
        Vector2<real> u1 = m.col(0);
        Vector2<real> u2 = m.col(1);
        u2 = u2 - u2.project(u1);
        Q.col(0, u1);
        Q.col(1, u2);
        R = Q.transpose() * m;
    }



//
//    void gs(Matrix4Float& m, Matrix4Float& Q, Matrix4Float& R);
//
//    void gs(Matrix3Float& m, Matrix3Float& Q, Matrix3Float& R);
//
//    void gs(Matrix2Float& m, Matrix2Float& Q, Matrix2Float& R);
}
