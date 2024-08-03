#include <cfloat>

namespace OdinMath {

    template<>
    inline float cosF<float>(float x) {
        /*      Algorithm and coefficients from:
                          "Software manual for the elementary functions"
                          by W.J. Cody and W. Waite, Prentice-Hall, 1980
          */

        static float piOverTwo = 1.57079632679489661923132169163975f;
        float xx = abs(x);
        float y = xx + piOverTwo;
        float sign = 1.f;
        static float oneOverPi = 3.183098861e-1f;

        float xn = y * oneOverPi;
        xn = round(xn);

        int n = abs((int) xn);

        if ((n & 0x1) == 1) sign = -sign;
        xn = xn - 0.5f;

        static float c1 = 3.1416015625f;
        static float c2 = -8.908910206761e-6f;

        // determine f
        float f = (xx - xn * c1) - xn * c2;
        float g = f * f;

        static float r[] = {
                -0.16666666666666665052e+0,
                0.83333333333331650314e-2,
                -0.19841269841201840457e-3,
                0.27557319210152756119e-5,
                -0.25052106798274584544e-7,
                0.16058936490371589114e-9,
                -0.76429178068910467734e-12,
                0.27204790957888846175e-14
        };

        float ffrg =
                (((((((((((r[7] * g + r[6]) * g + r[5]) * g) * g + r[4]) * g) * g + r[3]) * g) * g + r[2]) * g + r[1]) *
                  g + r[0]) * g) * f + f;
        return sign * ffrg;
    }

    template<>
    inline double cosF<double>(double x) {
        /*      Algorithm and coefficients from:
                          "Software manual for the elementary functions"
                          by W.J. Cody and W. Waite, Prentice-Hall, 1980
          */

        static double piOverTwo = 1.57079632679489661923132169163975;
        double xx = abs(x);
        double y = xx + piOverTwo;
        double sign = 1.f;
        static double oneOverPi = 3.183098861e-1f;

        double xn = y * oneOverPi;
        xn = round(xn);

        int n = abs((int) xn);

        if ((n & 0x1) == 1) sign = -sign;
        xn = xn - 0.5f;

        static double c1 = 3.1416015625f;
        static double c2 = -8.908910206761e-6f;

        // determine f
        double f = (xx - xn * c1) - xn * c2;
        double g = f * f;

        static double r[] = {
                -0.16666666666666665052e+0,
                0.83333333333331650314e-2,
                -0.19841269841201840457e-3,
                0.27557319210152756119e-5,
                -0.25052106798274584544e-7,
                0.16058936490371589114e-9,
                -0.76429178068910467734e-12,
                0.27204790957888846175e-14
        };

        double ffrg =
                (((((((((((r[7] * g + r[6]) * g + r[5]) * g) * g + r[4]) * g) * g + r[3]) * g) * g + r[2]) * g + r[1]) *
                  g + r[0]) * g) * f + f;
        return sign * ffrg;
    }


    template<>
    inline float sinF<float>(float x) {
        /*      Algorithm and coefficients from:
                          "Software manual for the elementary functions"
                          by W.J. Cody and W. Waite, Prentice-Hall, 1980
          */

        float sign = 1.0;
        if (x < 0.0f) {
            sign = -1;
            x = -x;
        }
        static float oneOverPi = 3.183098861e-1f;
        float xn = x * oneOverPi;
        xn = round(xn);

        int n = abs((int) xn);

        if ((n & 0x1) == 1) sign = -sign;
        static float c1 = 3.1416015625f;
        static float c2 = -8.908910206761e-6f;

        // determine f
        float f = (x - xn * c1) - xn * c2;
        float g = f * f;

        static float r[] = {
                -0.16666666666666665052e+0,
                0.83333333333331650314e-2,
                -0.19841269841201840457e-3,
                0.27557319210152756119e-5,
                -0.25052106798274584544e-7,
                0.16058936490371589114e-9,
                -0.76429178068910467734e-12,
                0.27204790957888846175e-14
        };

        float ffrg =
                (((((((((((r[7] * g + r[6]) * g + r[5]) * g) * g + r[4]) * g) * g + r[3]) * g) * g + r[2]) * g + r[1]) *
                  g + r[0]) * g) * f + f;
        return sign * ffrg;

    }

    template<>
    inline double sinF<double>(double x) {
        /*      Algorithm and coefficients from:
                           "Software manual for the elementary functions"
                           by W.J. Cody and W. Waite, Prentice-Hall, 1980
           */

        double sign = 1.0;
        if (x < 0.0f) {
            sign = -1;
            x = -x;
        }
        static double oneOverPi = 3.183098861e-1;

        // determine xn
        double xn = x * oneOverPi;
        xn = round(xn);

        int n = abs((int) xn);

        if ((n & 0x1) == 1) sign = -sign;
        static double c1 = 3.1416015625;
        static double c2 = -8.908910206761e-6;

        // determine f
        double f = (x - xn * c1) - xn * c2;

        // determine g
        double g = f * f;

        static double r[] = {
                -0.16666666666666665052e+0,
                0.83333333333331650314e-2,
                -0.19841269841201840457e-3,
                0.27557319210152756119e-5,
                -0.25052106798274584544e-7,
                0.16058936490371589114e-9,
                -0.76429178068910467734e-12,
                0.27204790957888846175e-14
        };

        // determine f + f * r(g)
        double ffrg =
                (((((((((((r[7] * g + r[6]) * g + r[5]) * g) * g + r[4]) * g) * g + r[3]) * g) * g + r[2]) * g + r[1]) *
                  g + r[0]) * g) * f + f;
        return sign * ffrg;

    }


    template<>
    inline float tanF<float>(float x) {

        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */

        static float twoOverPi = 0.63661977228f;
        // find X * N
        static float eps = 0.001;
        float xn = x * twoOverPi;

        xn = round(xn);
        int n = abs((int) xn);

        // find f
        static float c1 = 1.570796371f;
        static float c2 = -4.454455103380768678308e-6;

        float f = (x - xn * c1) - xn * c2;


        if (abs(f) < eps) {
            float xnum = f;
            float xden = 1.f;
            if ((n & 0x1) == 1) return -xden / xnum;
            else return xnum / xden;
        }


        static float p[] = {
                1.f,
                -0.13338350006421960681e+0f,
                0.34248878235890589960e-2f,
                -0.17861707342254426711e-4f
        };

        static float q[] = {
                1.f,
                -0.46671683339755294240e+0f,
                0.25663832289440112864e-1f,
                -0.31181531907010027307e-3f,
                0.49819433993786512270e-6f
        };

        // find g
        float g = f * f;
        float fpg = (((p[3] * g + p[2]) * g + p[1]) * g) * f + f;
        float qg = (((((q[4] * g + q[3]) * g) + q[2]) * g) + q[1]) * g + q[0];


        if ((n & 0x1) == 1)
            return -qg / fpg;
        else
            return fpg / qg;


    }

    template<>
    inline double tanF<double>(double x) {

        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */

        static double twoOverPi = 0.63661977228;
        // find X * N
        static double eps = 0.001;
        double xn = x * twoOverPi;
        xn = round(xn);

        int n = abs((int) xn);

        // find f
        static double c1 = 1.570796371;
        static double c2 = -4.454455103380768678308e-6;

        double f = (x - xn * c1) - xn * c2;


        if (abs(f) < eps) {
            double xnum = f;
            double xden = 1.f;
            if ((n & 0x1) == 1) return -xden / xnum;
            else return xnum / xden;
        }


        static double p[] = {
                1.f,
                -0.13338350006421960681e+0f,
                0.34248878235890589960e-2f,
                -0.17861707342254426711e-4f
        };

        static double q[] = {
                1.f,
                -0.46671683339755294240e+0f,
                0.25663832289440112864e-1f,
                -0.31181531907010027307e-3f,
                0.49819433993786512270e-6f
        };

        // find g
        double g = f * f;
        double fpg = (((p[3] * g + p[2]) * g + p[1]) * g) * f + f;
        double qg = (((((q[4] * g + q[3]) * g) + q[2]) * g) + q[1]) * g + q[0];

        if ((n & 0x1) == 1)
            return -qg / fpg;
        else
            return fpg / qg;

    }


    template<>
    inline float cotF<float>(float x) {

        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */

        static float twoOverPi = 0.63661977228f;
        // find X * N
        static float eps = 0.001;
        float xn = x * twoOverPi;

        xn = round(xn);
        int n = abs((int) xn);

        // find f
        static float c1 = 1.570796371f;
        static float c2 = -4.454455103380768678308e-6;

        float f = (x - xn * c1) - xn * c2;


        if (abs(f) < eps) {
            float xnum = f;
            float xden = 1.f;
            if ((n & 0x1) == 1) return -xnum / xden;
            else return xden / xnum;
        }


        static float p[] = {
                1.f,
                -0.13338350006421960681e+0f,
                0.34248878235890589960e-2f,
                -0.17861707342254426711e-4f
        };

        static float q[] = {
                1.f,
                -0.46671683339755294240e+0f,
                0.25663832289440112864e-1f,
                -0.31181531907010027307e-3f,
                0.49819433993786512270e-6f
        };

        // find g
        float g = f * f;
        float fpg = (((p[3] * g + p[2]) * g + p[1]) * g) * f + f;
        float qg = (((((q[4] * g + q[3]) * g) + q[2]) * g) + q[1]) * g + q[0];


        if ((n & 0x1) == 1)
            return -fpg / qg;
        else
            return qg / fpg;


    }

    template<>
    inline double cotF<double>(double x) {

        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */

        static double twoOverPi = 0.63661977228;
        // find X * N
        static double eps = 0.001;
        double xn = x * twoOverPi;
        xn = round(xn);

        int n = abs((int) xn);

        // find f
        static double c1 = 1.570796371;
        static double c2 = -4.454455103380768678308e-6;

        double f = (x - xn * c1) - xn * c2;


        if (abs(f) < eps) {
            double xnum = f;
            double xden = 1.f;
            if ((n & 0x1) == 1) return -xnum / xden;
            else return xden / xnum;
        }

        static double p[] = {
                1.f,
                -0.13338350006421960681e+0f,
                0.34248878235890589960e-2f,
                -0.17861707342254426711e-4f
        };

        static double q[] = {
                1.f,
                -0.46671683339755294240e+0f,
                0.25663832289440112864e-1f,
                -0.31181531907010027307e-3f,
                0.49819433993786512270e-6f
        };

        // find g
        double g = f * f;
        double fpg = (((p[3] * g + p[2]) * g + p[1]) * g) * f + f;
        double qg = (((((q[4] * g + q[3]) * g) + q[2]) * g) + q[1]) * g + q[0];

        if ((n & 0x1) == 1)
            return -fpg / qg;
        else
            return qg / fpg;

    }


    template<>
    inline float sinTaylor<float>(float x) {
        float xx = x * x;
        return (((((((-x / 1.3076e12f) * xx + (x / 6.227e9f)) * xx - (x / 39916900.0f)) * xx + (x / 362880.f)) * xx -
                  (x / 5040.0f)) * xx + (x / 120.0f)) * xx - (x / 6.0f)) * xx + x;
    }

    template<>
    inline double sinTaylor<double>(double x) {
        double xx = x * x;
        return (((((((-x / 1.3076e12) * xx + (x / 6.227e9)) * xx - (x / 39916900.0)) * xx + (x / 362880)) * xx -
                  (x / 5040.0)) * xx + (x / 120.0)) * xx - (x / 6.0)) * xx + x;
    }

    template<>
    inline float cosTaylor<float>(float x) {
        float xx = x * x;
        return (((((((-1.f / 87.178e9f) * xx + (1.f / 4.79e6f)) * xx - (1.f / 3628800.f)) * xx + (1.f / 40320.f)) * xx -
                  (1.f / 720.f)) * xx + (1.f / 24.f)) * xx - (1.f / 2.f)) * xx + 1;
    }

    template<>
    inline double cosTaylor<double>(double x) {
        double xx = x * x;
        return (((((((-1.f / 87.178e9) * xx + (1.f / 4.79e6)) * xx - (1.f / 3628800)) * xx + (1.f / 40320)) * xx -
                  (1.f / 720)) * xx + (1.f / 24)) * xx - (1.f / 2)) * xx + 1;
    }

    template<>
    inline float arcSinF<float>(float x) {
        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */
        float y = abs(x);
        int i;
        float g;
        if (y < 0.5f) {
            i = 0;
            g = y * y;
        } else {
            i = 1;
            if (y > 1.f) return FLT_MAX;
            g = 0.5f - 0.5f * y;
            y = -2.f * sqrt(g);
        }

        static float p[] = {
                -0.27368494524164255994e+2,
                0.57208227877891731407e+2,
                -0.39688862997540877339e+2,
                0.10152522233806463645e+2,
                -0.69674573447350646411e+0
        };

        static float q[] = {
                -0.16421096714498560795e+3,
                0.41714430248260412556e+3,
                -0.38186303361750149284e+3,
                0.15095270841030604719e+3,
                -0.23823859153670238830e+2,
                1.0
        };

        static float a[] = {
                0.0f,
                0.78539816339744830961566084581987572f
        };


        float gpg = (((((((p[4] * g + p[3]) * g) + p[2]) * g) + p[1]) * g) + p[0]) * g;
        float qg = ((((((((q[5] * g + q[4]) * g) + q[3]) * g) + q[2]) * g) + q[1]) * g) + q[0];
        float rg = gpg / qg;
        float r = y + y * rg;
        r = a[i] + (r + a[i]);
        if (x < 0.f) return -r;
        return r;
    }

    template<>
    inline double arcSinF<double>(double x) {
        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */
        double y = abs(x);
        int i;
        double g;
        if (y < 0.5) {
            i = 0;
            g = y * y;
        } else {
            i = 1;
            if (y > 1.f) return DBL_MAX;
            g = 0.5 - 0.5 * y;
            y = -2.0 * sqrt(g);
        }

        static double p[] = {
                -0.27368494524164255994e+2,
                0.57208227877891731407e+2,
                -0.39688862997540877339e+2,
                0.10152522233806463645e+2,
                -0.69674573447350646411e+0
        };

        static double q[] = {
                -0.16421096714498560795e+3,
                0.41714430248260412556e+3,
                -0.38186303361750149284e+3,
                0.15095270841030604719e+3,
                -0.23823859153670238830e+2,
                1.0
        };

        static double a[] = {
                0.0f,
                0.78539816339744830961566084581987572f
        };


        double gpg = (((((((p[4] * g + p[3]) * g) + p[2]) * g) + p[1]) * g) + p[0]) * g;
        double qg = ((((((((q[5] * g + q[4]) * g) + q[3]) * g) + q[2]) * g) + q[1]) * g) + q[0];
        double rg = gpg / qg;
        double r = y + y * rg;
        r = a[i] + (r + a[i]);
        if (x < 0.0) return -r;
        return r;
    }


    template<>
    inline float arcCosF<float>(float x) {
        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */
        float y = abs(x);
        int i;
        float g;
        if (y < 0.5f) {
            i = 1;
            g = y * y;
        } else {
            i = 0;
            if (y > 1.f) return FLT_MAX;
            g = 0.5f - 0.5f * y;
            y = -2.f * sqrt(g);
        }

        static float p[] = {
                -0.27368494524164255994e+2,
                0.57208227877891731407e+2,
                -0.39688862997540877339e+2,
                0.10152522233806463645e+2,
                -0.69674573447350646411e+0
        };

        static float q[] = {
                -0.16421096714498560795e+3,
                0.41714430248260412556e+3,
                -0.38186303361750149284e+3,
                0.15095270841030604719e+3,
                -0.23823859153670238830e+2,
                1.0
        };

        static float a[] = {
                0.0f,
                0.78539816339744830961566084581987572f
        };

        static float b[] = {
                1.57079632679489661923132169163975144,
                a[1]
        };


        float gpg = (((((((p[4] * g + p[3]) * g) + p[2]) * g) + p[1]) * g) + p[0]) * g;
        float qg = ((((((((q[5] * g + q[4]) * g) + q[3]) * g) + q[2]) * g) + q[1]) * g) + q[0];
        float rg = gpg / qg;
        float r = y + y * rg;
        if (x < 0.0f)
            return (b[i] + (b[i] + r));
        else
            return (a[i] + (a[i] - r));

    }

    template<>
    inline double arcCosF<double>(double x) {
        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */
        double y = abs(x);
        int i;
        double g;
        if (y < 0.5) {
            i = 1;
            g = y * y;
        } else {
            i = 0;
            if (y > 1.0) return DBL_MAX;
            g = 0.5 - 0.5 * y;
            y = -2.0 * sqrt(g);
        }

        static double p[] = {
                -0.27368494524164255994e+2,
                0.57208227877891731407e+2,
                -0.39688862997540877339e+2,
                0.10152522233806463645e+2,
                -0.69674573447350646411e+0
        };

        static double q[] = {
                -0.16421096714498560795e+3,
                0.41714430248260412556e+3,
                -0.38186303361750149284e+3,
                0.15095270841030604719e+3,
                -0.23823859153670238830e+2,
                1.0
        };

        static double a[] = {
                0.0f,
                0.78539816339744830961566084581987572f
        };

        static double b[] = {
                1.57079632679489661923132169163975144,
                a[1]
        };


        double gpg = (((((((p[4] * g + p[3]) * g) + p[2]) * g) + p[1]) * g) + p[0]) * g;
        double qg = ((((((((q[5] * g + q[4]) * g) + q[3]) * g) + q[2]) * g) + q[1]) * g) + q[0];
        double rg = gpg / qg;
        double r = y + y * rg;
        if (x < 0.0)
            return (b[i] + (b[i] + r));
        else
            return (a[i] + (a[i] - r));
    }

    template<>
    inline float arcTanF(float x) {
        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */
        float f = abs(x);
        int N = 0;
        if (f > 1.0f) {
            f = 1.f / f;
            N = 2;
        }
        static float c = 0.2679491924311228f;
        static float sqrt3 = 1.7320508075688772f;
        static float A = sqrt3 - 1.f;

        if (f > c) {
            f = (((A * f - 0.5f) - 0.5f) + f) / (sqrt3 + f);
            ++N;
        }

        float g = f * f;

        static float p[] = {
                -0.13688768894191926929e+2,
                -0.20505855195861651981e+2,
                -0.84946240351320683534e+1,
                -0.83758299368150059274e+0
        };
        static float q[] = {
                0.41066306682575781263e+2,
                0.86157349597130242515e+2,
                0.59578436142597344465e+2,
                0.15024001160028576121e+2,
                1.0
        };

        float gpg = (((((p[3] * g + p[2]) * g) + p[1]) * g) + p[0]) * g;
        float qg = ((((((q[4] * g + q[3]) * g) + q[2]) * g) + q[1]) * g) + q[0];
        float rg = gpg / qg;
        float r = f + f * rg;
        if (N > 1)
            r = -r;

        static float a[] = {
                0.0,
                0.52359877559829887307710723554658381,
                1.57079632679489661923132169163975144,
                1.04719755119659774615421446109316763
        };

        r = a[N] + r;

        if (x < 0.f) {
            r = -r;
        }
        return r;
    }

    template<>
    inline double arcTanF(double x) {
        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */
        double f = abs(x);
        int N = 0;
        if (f > 1.0f) {
            f = 1.f / f;
            N = 2;
        }
        static double c = 0.2679491924311228;
        static double sqrt3 = 1.7320508075688772;
        static double A = sqrt3 - 1.f;

        if (f > c) {
            f = (((A * f - 0.5f) - 0.5f) + f) / (sqrt3 + f);
            ++N;
        }

        double g = f * f;

        static double p[] = {
                -0.13688768894191926929e+2,
                -0.20505855195861651981e+2,
                -0.84946240351320683534e+1,
                -0.83758299368150059274e+0
        };
        static double q[] = {
                0.41066306682575781263e+2,
                0.86157349597130242515e+2,
                0.59578436142597344465e+2,
                0.15024001160028576121e+2,
                1.0
        };

        double gpg = (((((p[3] * g + p[2]) * g) + p[1]) * g) + p[0]) * g;
        double qg = ((((((q[4] * g + q[3]) * g) + q[2]) * g) + q[1]) * g) + q[0];
        double rg = gpg / qg;
        double r = f + f * rg;
        if (N > 1)
            r = -r;

        static double a[] = {
                0.0,
                0.52359877559829887307710723554658381,
                1.57079632679489661923132169163975144,
                1.04719755119659774615421446109316763
        };

        r = a[N] + r;

        if (x < 0.0) {
            r = -r;
        }
        return r;
    }

    template<>
    inline float arcTan2F(float v, float u) {
        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */
        float r;
        if (u == 0.f) {
            r = 1.57079632679489661923132169163975144f;
            if (v < 0.f) return -r;
            return r;
        }
        float x = v / u;
        if (x >= FLT_MAX) {
            r = 1.57079632679489661923132169163975144f;
            if (v < 0.f) return -r;
            return r;
        }

        if (x == 0.f) {
            r = 0.f;
            if (u < 0.f) {
                r = 3.14159265358979323846264338327950288f - r;
            }
            if (v < 0.f) {
                r = -r;
            }
            return r;
        }

        float f = abs(x);
        int N = 0;
        if (f > 1.0f) {
            f = 1.f / f;
            N = 2;
        }
        static float c = 0.2679491924311228f;
        static float sqrt3 = 1.7320508075688772f;
        static float A = sqrt3 - 1.f;

        if (f > c) {
            f = (((A * f - 0.5f) - 0.5f) + f) / (sqrt3 + f);
            ++N;
        }

        float g = f * f;

        static float p[] = {
                -0.13688768894191926929e+2,
                -0.20505855195861651981e+2,
                -0.84946240351320683534e+1,
                -0.83758299368150059274e+0
        };
        static float q[] = {
                0.41066306682575781263e+2,
                0.86157349597130242515e+2,
                0.59578436142597344465e+2,
                0.15024001160028576121e+2,
                1.0
        };

        float gpg = (((((p[3] * g + p[2]) * g) + p[1]) * g) + p[0]) * g;
        float qg = ((((((q[4] * g + q[3]) * g) + q[2]) * g) + q[1]) * g) + q[0];
        float rg = gpg / qg;
        r = f + f * rg;
        if (N > 1)
            r = -r;

        static float a[] = {
                0.0,
                0.52359877559829887307710723554658381,
                1.57079632679489661923132169163975144,
                1.04719755119659774615421446109316763
        };

        r = a[N] + r;

        if (x < 0.f) {
            r = -r;
        }
        return r;
    }

    template<>
    inline double arcTan2F(double v, double u) {
        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */
        double r;
        if (u == 0.0) {
            r = 1.57079632679489661923132169163975144;
            if (v < 0.f) return -r;
            return r;
        }
        double x = v / u;
        if (x >= DBL_MAX) {
            r = 1.57079632679489661923132169163975144;
            if (v < 0.f) return -r;
            return r;
        }

        if (x == 0.0) {
            r = 0.0;
            if (u < 0.0) {
                r = 3.14159265358979323846264338327950288 - r;
            }
            if (v < 0.0) {
                r = -r;
            }
            return r;
        }

        double f = abs(x);
        int N = 0;
        if (f > 1.0) {
            f = 1.0 / f;
            N = 2;
        }
        static double c = 0.2679491924311228;
        static double sqrt3 = 1.7320508075688772;
        static double A = sqrt3 - 1.0;

        if (f > c) {
            f = (((A * f - 0.5) - 0.5) + f) / (sqrt3 + f);
            ++N;
        }

        double g = f * f;

        static double p[] = {
                -0.13688768894191926929e+2,
                -0.20505855195861651981e+2,
                -0.84946240351320683534e+1,
                -0.83758299368150059274e+0
        };
        static double q[] = {
                0.41066306682575781263e+2,
                0.86157349597130242515e+2,
                0.59578436142597344465e+2,
                0.15024001160028576121e+2,
                1.0
        };

        double gpg = (((((p[3] * g + p[2]) * g) + p[1]) * g) + p[0]) * g;
        double qg = ((((((q[4] * g + q[3]) * g) + q[2]) * g) + q[1]) * g) + q[0];
        double rg = gpg / qg;
        r = f + f * rg;
        if (N > 1)
            r = -r;

        static double a[] = {
                0.0,
                0.52359877559829887307710723554658381,
                1.57079632679489661923132169163975144,
                1.04719755119659774615421446109316763
        };

        r = a[N] + r;

        if (x < 0.0) {
            r = -r;
        }
        return r;
    }

    template<>
    inline float sinhF<float>(float x) {
        int sign = 1;
        float y = x;
        if (x < 0.f) {
            sign = -1;
            y = abs(x);
        }
        static float lnv = 0.69316101074218750000e+0f;
        static float lnMax = FLT_MAX_EXP * M_LN2;
        static float vOver2MinusOne = 0.52820835025874852469e-4f;

        static float p[] = {
                -0.35181283430177117881e+6,
                -0.11563521196851768270e+5,
                -0.16375798202630751372e+3,
                -0.78966127417357099479e+0
        };
        static float q[] = {
                -0.21108770058106271242e+7,
                0.36162723109421836460e+5,
                -0.27773523119650701167e+3,
                1.0
        };

        if (y > 1.f) {
            float z;
            if (y > lnMax) {
                float w = y - lnv;
                if (w > (lnMax + M_LN2 - lnv)) {
                    return FLT_MAX;
                } else {
                    z = exp(w);
                    z = z + vOver2MinusOne * z;
                    if (sign == -1) z = -z;
                    return z;
                }
            } else {
                z = exp(y);
                z = (z - 1.f / z) * 0.5f;
                if (sign == -1) z = -z;
                return z;
            }
        } else {
            float f = x * x;
            float pf = ((((p[3] * f + p[2]) * f) + p[1]) * f) + p[0];
            float qf = ((((q[3] * f + q[2]) * f) + q[1]) * f) + q[0];
            float rf = f * (pf / qf);
            return x + x * rf;
        }
    }

    template<>
    inline double sinhF<double>(double x) {
        int sign = 1;
        double y = x;
        if (x < 0.f) {
            sign = -1;
            y = abs(x);
        }
        static double lnv = 0.69316101074218750000e+0f;
        static double lnMax = DBL_MAX_EXP * M_LN2;
        static double vOver2MinusOne = 0.52820835025874852469e-4f;

        static double p[] = {
                -0.35181283430177117881e+6,
                -0.11563521196851768270e+5,
                -0.16375798202630751372e+3,
                -0.78966127417357099479e+0
        };
        static double q[] = {
                -0.21108770058106271242e+7,
                0.36162723109421836460e+5,
                -0.27773523119650701167e+3,
                1.0
        };

        if (y > 1.f) {
            double z;
            if (y > lnMax) {
                double w = y - lnv;
                if (w > (lnMax + M_LN2 - lnv)) {
                    return DBL_MAX;
                } else {
                    z = exp(w);
                    z = z + vOver2MinusOne * z;
                    if (sign == -1) z = -z;
                    return z;
                }
            } else {
                z = exp(y);
                z = (z - 1.f / z) * 0.5f;
                if (sign == -1) z = -z;
                return z;
            }
        } else {
            double f = x * x;
            double pf = ((((p[3] * f + p[2]) * f) + p[1]) * f) + p[0];
            double qf = ((((q[3] * f + q[2]) * f) + q[1]) * f) + q[0];
            double rf = f * (pf / qf);
            return x + x * rf;
        }
    }

    template<>
    inline float coshF<float>(float x) {
        float y = abs(x);

        static float lnv = 0.69316101074218750000e+0f;
        static float lnMax = FLT_MAX_EXP * M_LN2;
        static float vOver2MinusOne = 0.52820835025874852469e-4f;

        float z;
        if (y > lnMax) {
            float w = y - lnv;
            if (w > (lnMax + M_LN2 - lnv)) {
                return FLT_MAX;
            } else {
                z = exp(w);
                return z + vOver2MinusOne * z;
            }
        } else {
            z = exp(y);
            return (z + 1.f / z) * 0.5f;
        }

    }

    template<>
    inline double coshF<double>(double x) {
        float y = abs(x);

        static double lnv = 0.69316101074218750000e+0f;
        static double lnMax = DBL_MAX_EXP * M_LN2;
        static double vOver2MinusOne = 0.52820835025874852469e-4f;

        double z;
        if (y > lnMax) {
            double w = y - lnv;
            if (w > (lnMax + M_LN2 - lnv)) {
                return DBL_MAX;
            } else {
                z = exp(w);
                return z + vOver2MinusOne * z;
            }
        } else {
            z = exp(y);
            return (z + 1.f / z) * 0.5f;
        }
    }

    template<> inline float tanhF<float>(float x){
        static float p[] = {
                -0.16134119023996228053e+4,
                -0.99225929672236083313e+2,
                -0.96437492777225469787e+0
        };
        static float q[] = {
                0.48402357071988688686e+4,
                0.22337720718962312926e+4,
                0.11274474380534949335e+3,
                1.0
        };

        float f = abs(x);
        float r;
        if(f > FLT_MAX_EXP * M_LN2){
            r = 1.f;
        }else if(f > 0.54930614433405484570e+0){
            r = 0.5f - 1.f / (exp(f + f) + 1.f);
            r = r + r;
        }else{
            float g = f * f;
            float gpg = (((p[2] * g + p[1]) * g) + p[0]) * g;
            float qg = ((((q[3] * g + q[2]) * g) + q[1]) * g) + q[0];
            float rg = gpg / qg;
            r = f + f * rg;
        }

        if(x < 0.f) r = -r;
        return r;
    }

    template<> inline double tanhF<double>(double x){
        static double p[] = {
                -0.16134119023996228053e+4,
                -0.99225929672236083313e+2,
                -0.96437492777225469787e+0
        };
        static double q[] = {
                0.48402357071988688686e+4,
                0.22337720718962312926e+4,
                0.11274474380534949335e+3,
                1.0
        };

        double f = abs(x);
        double r;
        if(f > DBL_MAX_EXP * M_LN2){
            r = 1.0;
        }else if(f > 0.54930614433405484570e+0){
            r = 0.50 - 1.f / (exp(f + f) + 1.0);
            r = r + r;
        }else{
            double g = f * f;
            double gpg = (((p[2] * g + p[1]) * g) + p[0]) * g;
            double qg = ((((q[3] * g + q[2]) * g) + q[1]) * g) + q[0];
            double rg = gpg / qg;
            r = f + f * rg;
        }

        if(x < 0.f) r = -r;
        return r;
    }




}
