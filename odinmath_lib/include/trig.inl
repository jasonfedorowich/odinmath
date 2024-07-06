
namespace OdinMath{

    template<> inline float cosF<float>(float x){
        /*      Algorithm and coefficients from:
                          "Software manual for the elementary functions"
                          by W.J. Cody and W. Waite, Prentice-Hall, 1980
          */

        static float piOverTwo = 1.57079632679489661923132169163975f;

        float y = abs(x) + piOverTwo;
        float sign = 1.f;
        static float oneOverPi = 3.183098861e-1f;

        float xn = y * oneOverPi;
        xn = round(xn);

        int n = abs((int)xn);

        if((n & 0x1) == 1) sign = -sign;
        xn = xn - 0.5f;

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

        float ffrg = (((((((((((r[7] * g + r[6]) * g + r[5]) * g) * g + r[4]) * g) * g + r[3]) * g) * g + r[2]) * g + r[1]) * g + r[0]) * g) * f + f;
        return sign * ffrg;
    }

    template<> inline double cosF<double>(double x){
        /*      Algorithm and coefficients from:
                          "Software manual for the elementary functions"
                          by W.J. Cody and W. Waite, Prentice-Hall, 1980
          */

        static double piOverTwo = 1.57079632679489661923132169163975;

        double y = abs(x) + piOverTwo;
        double sign = 1.f;
        static double oneOverPi = 3.183098861e-1f;

        double xn = y * oneOverPi;
        xn = round(xn);

        int n = abs((int)xn);

        if((n & 0x1) == 1) sign = -sign;
        xn = xn - 0.5f;

        static double c1 = 3.1416015625f;
        static double c2 = -8.908910206761e-6f;

        // determine f
        double f = (x - xn * c1) - xn * c2;
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

        double ffrg = (((((((((((r[7] * g + r[6]) * g + r[5]) * g) * g + r[4]) * g) * g + r[3]) * g) * g + r[2]) * g + r[1]) * g + r[0]) * g) * f + f;
        return sign * ffrg;
    }


    template<> inline float sinF<float>(float x){
        /*      Algorithm and coefficients from:
                          "Software manual for the elementary functions"
                          by W.J. Cody and W. Waite, Prentice-Hall, 1980
          */

        float sign = 1.0;
        if(x < 0.0f){
            sign = -1;
            x = -x;
        }
        static float oneOverPi = 3.183098861e-1f;
        float xn = x * oneOverPi;
        xn = round(xn);

        int n = abs((int)xn);

        if((n & 0x1) == 1) sign = -sign;
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

        float ffrg = (((((((((((r[7] * g + r[6]) * g + r[5]) * g) * g + r[4]) * g) * g + r[3]) * g) * g + r[2]) * g + r[1]) * g + r[0]) * g) * f + f;
        return sign * ffrg;

    }

    template<> inline double sinF<double>(double x){
        /*      Algorithm and coefficients from:
                           "Software manual for the elementary functions"
                           by W.J. Cody and W. Waite, Prentice-Hall, 1980
           */

        double sign = 1.0;
        if(x < 0.0f){
            sign = -1;
            x = -x;
        }
        static double oneOverPi = 3.183098861e-1;

        // determine xn
        double xn = x * oneOverPi;
        xn = round(xn);

        int n = abs((int)xn);

        if((n & 0x1) == 1) sign = -sign;
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
        double ffrg = (((((((((((r[7] * g + r[6]) * g + r[5]) * g) * g + r[4]) * g) * g + r[3]) * g) * g + r[2]) * g + r[1]) * g + r[0]) * g) * f + f;
        return sign * ffrg;

    }


    template<> inline float tanF<float>(float x){

        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */

        static float twoOverPi = 0.63661977228f;
        // find X * N
        static float eps = 0.001;
        float xn = x * twoOverPi;

        xn = round(xn);
        int n = abs((int)xn);

        // find f
        static float c1 = 1.570796371f;
        static float c2 = -4.454455103380768678308e-6;

        float f = (x - xn * c1) - xn * c2;


        if(abs(f) < eps){
            float xnum = f;
            float xden = 1.f;
            if((n & 0x1) == 1) return -xden / xnum;
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


        if((n & 0x1) == 1)
            return -qg / fpg;
        else
            return fpg / qg;


    }

    template<> inline double tanF<double>(double x){

        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */

        static double twoOverPi = 0.63661977228;
        // find X * N
        static double eps = 0.001;
        double xn = x * twoOverPi;
        xn = round(xn);

        int n = abs((int)xn);

        // find f
        static double c1 = 1.570796371;
        static double c2 = -4.454455103380768678308e-6;

        double f = (x - xn * c1) - xn * c2;


        if(abs(f) < eps){
            double xnum = f;
            double xden = 1.f;
            if((n & 0x1) == 1) return -xden / xnum;
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

        if((n & 0x1) == 1)
            return -qg / fpg;
        else
            return fpg / qg;

    }


    template<> inline float cotF<float>(float x){

        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */

        static float twoOverPi = 0.63661977228f;
        // find X * N
        static float eps = 0.001;
        float xn = x * twoOverPi;

        xn = round(xn);
        int n = abs((int)xn);

        // find f
        static float c1 = 1.570796371f;
        static float c2 = -4.454455103380768678308e-6;

        float f = (x - xn * c1) - xn * c2;


        if(abs(f) < eps){
            float xnum = f;
            float xden = 1.f;
            if((n & 0x1) == 1) return -xnum / xden;
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


        if((n & 0x1) == 1)
            return -fpg / qg;
        else
            return qg / fpg;


    }

    template<> inline double cotF<double>(double x){

        /*      Algorithm and coefficients from:
                            "Software manual for the elementary functions"
                            by W.J. Cody and W. Waite, Prentice-Hall, 1980
            */

        static double twoOverPi = 0.63661977228;
        // find X * N
        static double eps = 0.001;
        double xn = x * twoOverPi;
        xn = round(xn);

        int n = abs((int)xn);

        // find f
        static double c1 = 1.570796371;
        static double c2 = -4.454455103380768678308e-6;

        double f = (x - xn * c1) - xn * c2;


        if(abs(f) < eps){
            double xnum = f;
            double xden = 1.f;
            if((n & 0x1) == 1) return -xnum / xden;
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

        if((n & 0x1) == 1)
            return -fpg / qg;
        else
            return qg / fpg;

    }


    template<> inline float sinTaylor<float>(float x){
        float xx = x * x;
        return (((((((-x / 1.3076e12f) * xx + (x / 6.227e9f)) * xx - (x / 39916900.0f)) * xx + (x / 362880.f)) * xx - (x / 5040.0f)) * xx + (x / 120.0f)) * xx - (x / 6.0f)) * xx + x;
    }

    template<> inline double sinTaylor<double>(double x){
        double xx = x * x;
        return (((((((-x / 1.3076e12) * xx + (x / 6.227e9)) * xx - (x / 39916900.0)) * xx + (x / 362880)) * xx - (x / 5040.0)) * xx + (x / 120.0)) * xx - (x / 6.0)) * xx + x;
    }

    template<> inline float cosTaylor<float>(float x){
        float xx = x * x;
        return (((((((-1.f /  87.178e9f) * xx + (1.f / 4.79e6f)) * xx - (1.f / 3628800.f)) * xx + (1.f / 40320.f)) * xx - (1.f / 720.f)) * xx + (1.f / 24.f)) * xx - (1.f / 2.f)) * xx + 1;
    }

    template<> inline double cosTaylor<double>(double x){
        double xx = x * x;
        return (((((((-1.f /  87.178e9) * xx + (1.f / 4.79e6)) * xx - (1.f / 3628800)) * xx + (1.f / 40320)) * xx - (1.f / 720)) * xx + (1.f / 24)) * xx - (1.f / 2)) * xx + 1;
    }
}
