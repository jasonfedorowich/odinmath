namespace OdinMath{

    static VectorFloat32 piOverTwoIntr = {{1.57079632679489661923132169163975f, 1.57079632679489661923132169163975f, 1.57079632679489661923132169163975f, 1.57079632679489661923132169163975f}};
    static VectorFloat32 oneOverPiIntr = {{3.183098861e-1f, 3.183098861e-1f, 3.183098861e-1f, 3.183098861e-1f}};
    static VectorFloat32 twoOverPiIntr = {{0.63661977228f, 0.63661977228f, 0.63661977228f, 0.63661977228f}};

    static VectorFloat32 sinCosConsts1 = {{3.1416015625f, -8.908910206761e-6f, -0.16666666666666665052e+0, 0.83333333333331650314e-2}};
    static VectorFloat32 sinCosConsts2 = {{-0.19841269841201840457e-3, 0.27557319210152756119e-5, -0.25052106798274584544e-7, 0.16058936490371589114e-9}};
    static VectorFloat32 sinCosConsts3 = {{-0.76429178068910467734e-12, 0.27204790957888846175e-14, 1.f, 1.f}};

    static VectorFloat32 tanCotConst1 = {{1.570796371f, -4.454455103380768678308e-6f, 1.f, -0.13338350006421960681e+0f}};
    static VectorFloat32 tanCotConst2 = {{0.34248878235890589960e-2f, -0.17861707342254426711e-4f, 1.f, -0.46671683339755294240e+0f}};
    static VectorFloat32 tanCotConst3 = {{0.25663832289440112864e-1f, -0.31181531907010027307e-3f, 0.49819433993786512270e-6f, 0.0001}};


    static VectorFloat32 zero = {{0.f, 0.f, 0.f, 0.f}};
    static VectorFloat32 one = {{1.f, 1.f, 1.f, 1.f}};
    static VectorInteger32 oneInt = {{1, 1, 1, 1}};

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
}