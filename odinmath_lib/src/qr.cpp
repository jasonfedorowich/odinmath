//
// Created by Jason Fedorowich on 2025-04-25.
//
#include "odinmath.h"

namespace OdinMath{

    static Vector4Float subProject(const Vector4Float& s, const Vector4Float& u, const Vector4Float& w){
        return Vector4Float(sub(s.getVector(), u.project(w).getVector()));
    }

    static Vector3Float subProject(const Vector3Float& s, const Vector3Float& u, const Vector3Float& w){
        return Vector3Float(sub(s.getVector(), u.project(w).getVector()));
    }

    static Vector2Float subProject(const Vector2Float& s, const Vector2Float& u, const Vector2Float& w){
        return Vector2Float(sub(s.getVector(), u.project(w).getVector()));
    }

    void OdinMath::gsF(Matrix4Float &m, Matrix4Float &Q, Matrix4Float &R) {
        Matrix4Float t = m.transpose();
        Vector4Float u1 = t.row(0);
        Vector4Float u2 = t.row(1);
        Vector4Float u3 = t.row(2);
        Vector4Float u4 = t.row(3);

        u2 = subProject(u2, u2, u1);
        u2.normalize();
        u3 = subProject(subProject(u3, u3, u2), u3, u1);
        u3.normalize();
        u4 = subProject(subProject(subProject(u4, u4, u3), u4, u2), u4, u1);
        u4.normalize();

        Matrix4Float T(u1, u2, u3, u4);
        R = T * m;
        Q = T.transpose();
    }

    void OdinMath::gsF(Matrix3Float &m, Matrix3Float &Q, Matrix3Float &R) {
        Matrix3Float t = m.transpose();
        Vector3Float u1 = t.row(0);
        Vector3Float u2 = t.row(1);
        Vector3Float u3 = t.row(2);

        u2 = subProject(u2, u2, u1);
        u2.normalize();
        u3 = subProject(subProject(u3, u3, u2), u3, u1);
        u3.normalize();

        Matrix3Float T(u1, u2, u3);
        R = T * m;
        Q = T.transpose();

    }

    void OdinMath::gsF(Matrix2Float &m, Matrix2Float &Q, Matrix2Float &R) {
        Matrix2Float t = m.transpose();
        Vector2Float u1 = t.row(0);
        Vector2Float u2 = t.row(1);

        u2 = subProject(u2, u2, u1);
        u2.normalize();

        Matrix2Float T(u1, u2);
        R = T * m;
        Q = T.transpose();
    }

}