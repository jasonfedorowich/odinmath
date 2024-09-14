#include <cfloat>

namespace OdinMath{

    static VectorFloat32 piOverTwoIntr = {{1.57079632679489661923132169163975f, 1.57079632679489661923132169163975f, 1.57079632679489661923132169163975f, 1.57079632679489661923132169163975f}};
    static VectorFloat32 oneOverPiIntr = {{3.183098861e-1f, 3.183098861e-1f, 3.183098861e-1f, 3.183098861e-1f}};
    static VectorFloat32 twoOverPiIntr = {{0.63661977228f, 0.63661977228f, 0.63661977228f, 0.63661977228f}};
    static VectorFloat32 piIntr = {{3.14159265358979323846264338327950288f, 3.14159265358979323846264338327950288f, 3.14159265358979323846264338327950288f, 3.14159265358979323846264338327950288f}};

    static VectorFloat32 sinCosConsts1 = {{3.1416015625f, -8.908910206761e-6f, -0.16666666666666665052e+0, 0.83333333333331650314e-2}};
    static VectorFloat32 sinCosConsts2 = {{-0.19841269841201840457e-3, 0.27557319210152756119e-5, -0.25052106798274584544e-7, 0.16058936490371589114e-9}};
    static VectorFloat32 sinCosConsts3 = {{-0.76429178068910467734e-12, 0.27204790957888846175e-14, 1.f, 1.f}};

    static VectorFloat32 tanCotConst1 = {{1.570796371f, -4.454455103380768678308e-6f, 1.f, -0.13338350006421960681e+0f}};
    static VectorFloat32 tanCotConst2 = {{0.34248878235890589960e-2f, -0.17861707342254426711e-4f, 1.f, -0.46671683339755294240e+0f}};
    static VectorFloat32 tanCotConst3 = {{0.25663832289440112864e-1f, -0.31181531907010027307e-3f, 0.49819433993786512270e-6f, 0.0001}};

    static VectorFloat32 arcCosSin1 = {{-0.27368494524164255994e+2, 0.57208227877891731407e+2, -0.39688862997540877339e+2, 0.10152522233806463645e+2 }};
    static VectorFloat32 arcCosSin2 = {{-0.69674573447350646411e+0, -0.16421096714498560795e+3, 0.41714430248260412556e+3, -0.38186303361750149284e+3}};
    static VectorFloat32 arcCosSin3 = {{0.15095270841030604719e+3, -0.23823859153670238830e+2, 0.78539816339744830961566084581987572f, 1.57079632679489661923132169163975144}};

    static VectorFloat32 arcTan1 = {{0.2679491924311228f, 1.7320508075688772f, 0.78539816339744830961566084581987572f, 1.57079632679489661923132169163975144}};
    static VectorFloat32 arcTan2 = {{-0.13688768894191926929e+2, -0.20505855195861651981e+2, -0.84946240351320683534e+1, -0.83758299368150059274e+0}};
    static VectorFloat32 arcTan3 = {{0.41066306682575781263e+2, 0.86157349597130242515e+2, 0.59578436142597344465e+2, 0.15024001160028576121e+2}};
    static VectorFloat32 arcTan4 = {{0.0, 0.52359877559829887307710723554658381, 1.57079632679489661923132169163975144, 1.04719755119659774615421446109316763}};

    static VectorFloat32 sinhCosh1 = {{0.69316101074218750000e+0f, FLT_MAX_EXP * M_LN2, 0.52820835025874852469e-4f, M_LN2}};
    static VectorFloat32 sinhCosh2 = {{-0.35181283430177117881e+6, -0.11563521196851768270e+5, -0.16375798202630751372e+3, -0.78966127417357099479e+0}};
    static VectorFloat32 sinhCosh3 = {{-0.21108770058106271242e+7, 0.36162723109421836460e+5, -0.27773523119650701167e+3, 1.0}};

    inline float32x4_t cosF(float32x4_t v){
        float32x4_t xx = vabsq_f32(v);
        float32x4_t y = vaddq_f32(xx, piOverTwoIntr.v);
        float32x4_t xn = vmulq_f32(y, oneOverPiIntr.v);
        uint32x4_t nn = vcvtq_u32_f32(xn);
        xn = vcvtq_f32_s32(nn);
        xn = vsubq_f32(xn, duplicate(0.5f));

        float32x4_t f = mulSub(xx, xn, dupX(sinCosConsts1.v));
        f = mulSub(f, xn, dupY(sinCosConsts1.v));
        float32x4_t g = mul(f, f);

        float32x4_t t = mulAdd(dupX(sinCosConsts3.v), g, dupY(sinCosConsts3.v));
        t = mulAdd(dupW(sinCosConsts2.v), g, t);
        t = mulAdd(dupZ(sinCosConsts2.v), g, t);
        t = mulAdd(dupY(sinCosConsts2.v), g, t);
        t = mulAdd(dupX(sinCosConsts2.v), g, t);
        t = mulAdd(dupW(sinCosConsts1.v), g, t);
        t = mulAdd(dupZ(sinCosConsts1.v), g, t);
        t = mul(t, g);
        t = mulAdd(f, f, t);

        uint32x4_t a = _and(nn, oneInt.v);
        uint32x4_t e = equalInt(a, oneInt.v);
        return condSelect(e, vnegq_f32(t), t);
    }

    inline float32x4_t sinF(float32x4_t v){
        float32x4_t y = vabsq_f32(v);
        float32x4_t xn = vmulq_f32(y, oneOverPiIntr.v);
        uint32x4_t nn = vcvtq_u32_f32(xn);
        xn = vcvtq_f32_s32(nn);

        float32x4_t f = mulSub(y, xn, dupX(sinCosConsts1.v));
        f = mulSub(f, xn, dupY(sinCosConsts1.v));
        float32x4_t g = mul(f, f);

        float32x4_t t = mulAdd(dupX(sinCosConsts3.v), g, dupY(sinCosConsts3.v));
        t = mulAdd(dupW(sinCosConsts2.v), g, t);
        t = mulAdd(dupZ(sinCosConsts2.v), g, t);
        t = mulAdd(dupY(sinCosConsts2.v), g, t);
        t = mulAdd(dupX(sinCosConsts2.v), g, t);
        t = mulAdd(dupW(sinCosConsts1.v), g, t);
        t = mulAdd(dupZ(sinCosConsts1.v), g, t);
        t = mul(t, g);
        t = mulAdd(f, f, t);

        uint32x4_t a = _and(nn, oneInt.v);
        uint32x4_t e = equalInt(a, oneInt.v);
        uint32x4_t lt = lessThan(v, zero.v);
        t = condSelect(lt, vnegq_f32(t), t);
        return condSelect(e, vnegq_f32(t), t);
    }

    inline float32x4_t tanF(float32x4_t v){
        float32x4_t xn = mul(v, twoOverPiIntr.v);
        uint32x4_t nn = vcvtq_u32_f32(vabsq_f32(xn));
        xn = vcvtq_f32_s32(nn);
        nn = vabsq_s32(nn);
        uint32x4_t ltz = lessThan(v, zero.v);
        xn = condSelect(ltz, vnegq_f32(xn), xn);

        float32x4_t f = mulSub(v, dupX(tanCotConst1.v), xn);
        f = mulSub(f, dupY(tanCotConst1.v), xn);
        float32x4_t g = mul(f, f);

        float32x4_t fpg = mulAdd(dupX(tanCotConst2.v), dupY(tanCotConst2.v), g);
        fpg = mulAdd(dupW(tanCotConst1.v), fpg, g);
        fpg = mul(g, fpg);
        fpg = mulAdd(f, fpg, f);

        float32x4_t qg = mulAdd(dupY(tanCotConst3.v), g, dupZ(tanCotConst3.v));
        qg = mulAdd(dupX(tanCotConst3.v), g, qg);
        qg = mulAdd(dupW(tanCotConst2.v), g, qg);
        qg = mulAdd(dupZ(tanCotConst2.v), g, qg);

        uint32x4_t isNotEven = _and(nn, oneInt.v);
        isNotEven = equalInt(isNotEven, oneInt.v);

        uint32x4_t isSmall = lessThan(vabsq_f32(f), dupW(tanCotConst3.v));

        float32x4_t t1 = div(vnegq_f32(ones()), f);
        float32x4_t t2 = div(vnegq_f32(qg), fpg);
        float32x4_t t3 = div(fpg, qg);

        float32x4_t r1 = condSelect(isNotEven, t1, f);
        float32x4_t r2 = condSelect(isNotEven, t2, t3);

        return condSelect(isSmall, r1, r2);

    }

    inline float32x4_t cotF(float32x4_t v){
        float32x4_t xn = mul(v, twoOverPiIntr.v);
        uint32x4_t nn = vcvtq_u32_f32(vabsq_f32(xn));
        xn = vcvtq_f32_s32(nn);
        nn = vabsq_s32(nn);
        uint32x4_t ltz = lessThan(v, zero.v);
        xn = condSelect(ltz, vnegq_f32(xn), xn);

        float32x4_t f = mulSub(v, dupX(tanCotConst1.v), xn);
        f = mulSub(f, dupY(tanCotConst1.v), xn);
        float32x4_t g = mul(f, f);

        float32x4_t fpg = mulAdd(dupX(tanCotConst2.v), dupY(tanCotConst2.v), g);
        fpg = mulAdd(dupW(tanCotConst1.v), fpg, g);
        fpg = mul(g, fpg);
        fpg = mulAdd(f, fpg, f);

        float32x4_t qg = mulAdd(dupY(tanCotConst3.v), g, dupZ(tanCotConst3.v));
        qg = mulAdd(dupX(tanCotConst3.v), g, qg);
        qg = mulAdd(dupW(tanCotConst2.v), g, qg);
        qg = mulAdd(dupZ(tanCotConst2.v), g, qg);

        uint32x4_t isNotEven = _and(nn, oneInt.v);
        isNotEven = equalInt(isNotEven, oneInt.v);

        uint32x4_t isSmall = lessThan(vabsq_f32(f), dupW(tanCotConst3.v));

        float32x4_t t1 = div(one.v, f);
        float32x4_t t2 = div(vnegq_f32(fpg), qg);
        float32x4_t t3 = div(qg, fpg);

        float32x4_t r1 = condSelect(isNotEven, vnegq_f32(f), t1);
        float32x4_t r2 = condSelect(isNotEven, t2, t3);

        return condSelect(isSmall, r1, r2);
    }

    inline float32x4_t arcCosF(float32x4_t v){
        float32x4_t y = vabsq_f32(v);
        float32x4_t point5 = duplicate(0.5f);

        int32x4_t lt = lessThan(y, point5);
        
        float32x4_t t1 = mul(y, y);
        float32x4_t t2 = mulSub(point5, point5, y);
        float32x4_t g = condSelect(lt, t1, t2);

        y = condSelect(lt, y, negMul(duplicate(2.f), sqrtF(g)));

        float32x4_t gpg = mulAdd(dupW(arcCosSin1.v), g, dupX(arcCosSin2.v));
        gpg = mulAdd(dupZ(arcCosSin1.v), g, gpg);
        gpg = mulAdd(dupY(arcCosSin1.v), g, gpg);
        gpg = mulAdd(dupX(arcCosSin1.v), g, gpg);
        gpg = mul(g, gpg);

        float32x4_t qg = mulAdd(dupY(arcCosSin3.v), g, one.v);
        qg = mulAdd(dupX(arcCosSin3.v), g, qg);
        qg = mulAdd(dupW(arcCosSin2.v), g, qg);
        qg = mulAdd(dupZ(arcCosSin2.v), g, qg);
        qg = mulAdd(dupY(arcCosSin2.v), g, qg);

        float32x4_t rg = div(gpg, qg);
        float32x4_t r = mulAdd(y, y, rg);

        float32x4_t a = condSelect(lt, dupZ(arcCosSin3.v), zero.v);
        float32x4_t b = condSelect(lt, dupZ(arcCosSin3.v), dupW(arcCosSin3.v));

        int32x4_t ltz = lessThan(v, zero.v);

        return condSelect(ltz, addAdd(b, r), addAddNeg(a, r));
    }

    inline float32x4_t arcSinF(float32x4_t v){
        float32x4_t y = vabsq_f32(v);
        float32x4_t point5 = duplicate(0.5f);

        int32x4_t lt = lessThan(y, point5);

        float32x4_t t1 = mul(y, y);
        float32x4_t t2 = mulSub(point5, point5, y);
        float32x4_t g = condSelect(lt, t1, t2);

        y = condSelect(lt, y, negMul(duplicate(2.f), sqrtF(g)));

        float32x4_t gpg = mulAdd(dupW(arcCosSin1.v), g, dupX(arcCosSin2.v));
        gpg = mulAdd(dupZ(arcCosSin1.v), g, gpg);
        gpg = mulAdd(dupY(arcCosSin1.v), g, gpg);
        gpg = mulAdd(dupX(arcCosSin1.v), g, gpg);
        gpg = mul(g, gpg);


        float32x4_t qg = mulAdd(dupY(arcCosSin3.v), g, one.v);
        qg = mulAdd(dupX(arcCosSin3.v), g, qg);
        qg = mulAdd(dupW(arcCosSin2.v), g, qg);
        qg = mulAdd(dupZ(arcCosSin2.v), g, qg);
        qg = mulAdd(dupY(arcCosSin2.v), g, qg);

        float32x4_t rg = div(gpg, qg);
        float32x4_t r = mulAdd(y, y, rg);

        float32x4_t a = condSelect(lt, zero.v, dupZ(arcCosSin3.v));
        r = addAdd(a, r);
        int32x4_t ltz = lessThan(v, zero.v);

        return condSelect(ltz, vnegq_f32(r), r);
    }

    inline float32x4_t arcTanF(float32x4_t v){
        float32x4_t f = vabsq_f32(v);
        float32x4_t point5 = duplicate(-0.5f);

        int32x4_t gto = greaterThan(f, one.v);
        f = condSelect(gto, invert(v), f);

        float32x4_t N = condSelect(gto, two.v, zero.v);


        float32x4_t A = sub(dupY(arcTan1.v), one.v);
        int32x4_t gtc = greaterThan(f, dupX(arcTan1.v));

        float32x4_t t = mulAdd(point5, A, f);
        t = add(t, point5);
        t = add(t, f);

        float32x4_t tt = add(dupY(arcTan1.v), f);
        t = div(t, tt);

        f = condSelect(gtc, t, f);
        N = condSelect(gtc, add(N, one.v), N);

        float32x4_t g = mul(f, f);

        float32x4_t gpg = mulAdd(dupZ(arcTan2.v), g, dupW(arcTan2.v));
        gpg = mulAdd(dupY(arcTan2.v), g, gpg);
        gpg = mulAdd(dupX(arcTan2.v), g, gpg);
        gpg = mul(g, gpg);

        float32x4_t qg = mulAdd(dupZ(arcTan3.v), g, dupW(arcTan3.v));
        qg = mulAdd(dupY(arcTan3.v), qg, g);
        qg = mulAdd(dupX(arcTan3.v), qg, g);

        float32x4_t rg = div(gpg, qg);
        float32x4_t r = mulAdd(f, f, rg);

        int32x4_t ngo = greaterThan(N, one.v);
        r = condSelect(ngo, neg(r), r);

        float32x4_t a = condSelect(gto,
                                   condSelect(gtc, dupW(arcTan4.v), dupZ(arcTan4.v)),
                                   condSelect(gtc, dupY(arcTan4.v), zero.v));
        r = add(a, r);
        return condSelect(lessThan(v, zero.v), neg(r), r);

    }

    inline float32x4_t arcTan2F(float32x4_t v, float32x4_t u){
        float32x4_t x = div(v, u);

        float32x4_t f = vabsq_f32(x);
        float32x4_t point5 = duplicate(-0.5f);

        int32x4_t gto = greaterThan(f, one.v);
        f = condSelect(gto, invert(x), f);

        float32x4_t N = condSelect(gto, two.v, zero.v);


        float32x4_t A = sub(dupY(arcTan1.v), one.v);
        int32x4_t gtc = greaterThan(f, dupX(arcTan1.v));

        float32x4_t t = mulAdd(point5, A, f);
        t = add(t, point5);
        t = add(t, f);

        float32x4_t tt = add(dupY(arcTan1.v), f);
        t = div(t, tt);

        f = condSelect(gtc, t, f);
        N = condSelect(gtc, add(N, one.v), N);

        float32x4_t g = mul(f, f);

        float32x4_t gpg = mulAdd(dupZ(arcTan2.v), g, dupW(arcTan2.v));
        gpg = mulAdd(dupY(arcTan2.v), g, gpg);
        gpg = mulAdd(dupX(arcTan2.v), g, gpg);
        gpg = mul(g, gpg);

        float32x4_t qg = mulAdd(dupZ(arcTan3.v), g, dupW(arcTan3.v));
        qg = mulAdd(dupY(arcTan3.v), qg, g);
        qg = mulAdd(dupX(arcTan3.v), qg, g);

        float32x4_t rg = div(gpg, qg);
        float32x4_t r = mulAdd(f, f, rg);

        int32x4_t ngo = greaterThan(N, one.v);
        r = condSelect(ngo, neg(r), r);

        float32x4_t a = condSelect(gto,
                                   condSelect(gtc, dupW(arcTan4.v), dupZ(arcTan4.v)),
                                   condSelect(gtc, dupY(arcTan4.v), zero.v));
        r = add(a, r);
        r = condSelect(lessThan(v, zero.v), neg(r), r);

        int32x4_t ez = equalFloat(u, zero.v);
        int32x4_t gtm = greaterThanOrEqual(x, duplicate(FLT_MAX));
        int32x4_t vlz = lessThan(v, zero.v);
        int32x4_t xeq = equalFloat(x, zero.v);
        int32x4_t ulz = lessThan(u, zero.v);

        r = condSelect(ez, condSelect(vlz, neg(piOverTwoIntr.v), piOverTwoIntr.v), r);
        r = condSelect(gtm, condSelect(vlz, neg(piOverTwoIntr.v), piOverTwoIntr.v), r);
        return condSelect(xeq, condSelect(ulz, piIntr.v, zero.v), r);

    }

    inline float32x4_t sinhF(float32x4_t v){
        int32x4_t ltz = lessThan(v, zero.v);
        float32x4_t y = vabsq_f32(v);
        int32x4_t gto = greaterThan(y, one.v);
        int32x4_t gtlnMax = greaterThan(y, dupY(sinhCosh1.v));

        float32x4_t w = sub(y, dupX(sinhCosh1.v));

        float32x4_t z1 = expF(w);
        z1 = mulAdd(z1, dupZ(sinhCosh1.v), z1);
        z1 = condSelect(ltz, neg(z1), z1);

        float32x4_t z2 = expF(y);
        z2 = mul(sub(z2, invert(z2)), duplicate(0.5f));
        z2 = condSelect(ltz, neg(z2), z2);

        int32x4_t wgt = greaterThan(w, addSub(dupY(sinhCosh1.v), dupW(sinhCosh1.v), dupX(sinhCosh1.v)));

        float32x4_t f = mul(v, v);

        float32x4_t pf = mulAdd(dupZ(sinhCosh2.v), f, dupW(sinhCosh2.v));
        pf = mulAdd(dupY(sinhCosh2.v), f, pf);
        pf = mulAdd(dupX(sinhCosh2.v), f, pf);

        float32x4_t qf = mulAdd(dupZ(sinhCosh3.v), f, dupW(sinhCosh3.v));
        qf = mulAdd(dupY(sinhCosh3.v), f, qf);
        qf = mulAdd(dupX(sinhCosh3.v), f, qf);

        float32x4_t rf = mul(f, div(pf, qf));
        float32x4_t r = mulAdd(v, v, rf);

        float32x4_t wBranch = condSelect(wgt, duplicate(FLT_MAX), z1);
        float32x4_t yGtBranch = condSelect(gtlnMax, wBranch, z2);
        return condSelect(gto, yGtBranch,r);

    }

    inline float32x4_t coshF(float32x4_t v){
        float32x4_t y = vabsq_f32(v);
        float32x4_t w = sub(y, dupX(sinhCosh1.v));
        float32x4_t z1 = expF(w);
        z1 = mulAdd(z1, z1, dupZ(sinhCosh1.v));
        float32x4_t z2 = expF(y);
        z2 = add(z2, invert(z2));
        z2 = mul(z2, duplicate(0.5f));

        int32x4_t gtlnMax = greaterThan(y, dupY(sinhCosh1.v));
        int32x4_t wgt = greaterThan(w, addSub(dupY(sinhCosh1.v), dupW(sinhCosh1.v), dupX(sinhCosh1.v)));

        return condSelect(gtlnMax, condSelect(wgt, duplicate(FLT_MAX), z1), z2);

    }

}