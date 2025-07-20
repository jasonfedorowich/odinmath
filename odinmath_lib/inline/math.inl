#include <cfloat>

namespace OdinMath {

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

    template<> inline float logF<float>(float x){
//        /*      Algorithm and coefficients from:
//                          "Software manual for the elementary functions"
//                          by W.J. Cody and W. Waite, Prentice-Hall, 1980
//          */
//
        if(x <= 0.f) FLT_MIN;

        static float c0 = 0.70710678118654752440f;

        static float a[] = {-0.64124943423745581147e+2f,
                    0.16383943563021534222e+2f,
                    -0.78956112887491257267e+0f};

        static float b[] = {-0.76949932108494879777e+3f,
                     0.31203222091924532844e+3f,
                     -0.35667977739034646171e+2f,
                     0.10000000000000000000e+1f};



        int n = -1;
        float f = frexp(x, &n);
        float znum;
        float zden;

        if(f > c0){
            znum = (f - 0.5f) - 0.5f;
            zden = f * 0.5f + 0.5f;
        }else{
            znum = f - 0.5f;
            zden = znum * 0.5f + 0.5f;
            n--;
        }

        float z = znum / zden;
        float w = z * z;

        float aw = (a[2] * w + a[1]) * w + a[0];
        float bw = ((b[3] * w + b[2]) * w + b[1]) * w + b[0];

        float rz2 = w * aw / bw;
        float rz = z + z * rz2;

        float xn = n;
        float c2 = -2.121944400546905827679e-4f;
        float c1 = 0.693359375f;

        return (xn * c2 + rz) + xn * c1;

    }

    template<> inline double logF<double>(double x){
//        /*      Algorithm and coefficients from:
//                          "Software manual for the elementary functions"
//                          by W.J. Cody and W. Waite, Prentice-Hall, 1980
//          */
//
        if(x <= 0.0) DBL_MIN;

        static double c0 = 0.70710678118654752440;

        static double a[] = {-0.64124943423745581147e+2,
                            0.16383943563021534222e+2,
                            -0.78956112887491257267e+0};

        static double b[] = {-0.76949932108494879777e+3,
                            0.31203222091924532844e+3,
                            -0.35667977739034646171e+2,
                            0.10000000000000000000e+1};



        int n = -1;
        double f = frexp(x, &n);
        double znum;
        double zden;

        if(f > c0){
            znum = (f - 0.5f) - 0.5f;
            zden = f * 0.5f + 0.5f;
        }else{
            znum = f - 0.5f;
            zden = znum * 0.5f + 0.5f;
            n--;
        }

        double z = znum / zden;
        double w = z * z;

        double aw = (a[2] * w + a[1]) * w + a[0];
        double bw = ((b[3] * w + b[2]) * w + b[1]) * w + b[0];

        double rz2 = w * aw / bw;
        double rz = z + z * rz2;

        double xn = n;
        double c2 = -2.121944400546905827679e-4;
        double c1 = 0.693359375;

        return (xn * c2 + rz) + xn * c1;

    }

    template<> inline float log10F<float>(float x){
//        /*      Algorithm and coefficients from:
//                          "Software manual for the elementary functions"
//                          by W.J. Cody and W. Waite, Prentice-Hall, 1980
//          */
//
        float c3 = 0.43429448190325182765f;
        float l = logF<float>(x);
        return c3 * l;
    }

    template<> inline double log10F<double>(double x){
        //        /*      Algorithm and coefficients from:
//                          "Software manual for the elementary functions"
//                          by W.J. Cody and W. Waite, Prentice-Hall, 1980
//          */
//
        double c3 = 0.43429448190325182765;
        double l = logF<double>(x);
        return c3 * l;

    }


}