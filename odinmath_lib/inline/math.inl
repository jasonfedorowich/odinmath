#include <cfloat>

namespace OdinMath{

    template<> inline float expF<float>(float x){
//        /*      Algorithm and coefficients from:
//                          "Software manual for the elementary functions"
//                          by W.J. Cody and W. Waite, Prentice-Hall, 1980
//          */
//
       static float oneOverLnC = 1.4426950408889634074f;
       static float c1 = 0.693359375f;
       static float c2 = -2.1219444005469058277e-4f;
       static float sqrt10 = 3.1622776601683793320f;

       int n = x * oneOverLnC;
       float xn = n;
       float g = (x - xn * c1) - xn * c2;
       float z = g * g;

        static float p[] = {
                0.25000000000000000000e+0,
                0.75753180159422776666e-2,
                0.31555192765684646356e-4
        };

        static float q[] = {
                0.50000000000000000000e+0,
                0.56817302698551221787e-1,
                0.63121894374398503557e-3,
                0.75104028399870046114e-6
        };

        float gpz = ((p[2] * z + p[1]) * z + p[0]) * g;
        float qz = ((((q[3] * z + q[2]) * z) + q[1]) * z) + q[0];
        float rg = (0.5f + gpz / (qz - gpz));
        ++n;
        return ldexp(rg, n);

    }

    template<> inline double expF<double>(double x) {
//        /*      Algorithm and coefficients from:
//                          "Software manual for the elementary functions"
//                          by W.J. Cody and W. Waite, Prentice-Hall, 1980
//          */
//
        static double oneOverLnC = 1.4426950408889634074;
        static double c1 = 0.693359375;
        static double c2 = -2.1219444005469058277e-4;
        static double sqrt10 = 3.1622776601683793320;

        int n = x * oneOverLnC;
        double xn = n;
        double g = (x - xn * c1) - xn * c2;
        double z = g * g;

        static double p[] = {
                0.25000000000000000000e+0,
                0.75753180159422776666e-2,
                0.31555192765684646356e-4
        };

        static double q[] = {
                0.50000000000000000000e+0,
                0.56817302698551221787e-1,
                0.63121894374398503557e-3,
                0.75104028399870046114e-6
        };

        double gpz = ((p[2] * z + p[1]) * z + p[0]) * g;
        double qz = ((((q[3] * z + q[2]) * z) + q[1]) * z) + q[0];
        double rg = (0.5f + gpz / (qz - gpz));
        ++n;
        return ldexp(rg, n);
    }

}