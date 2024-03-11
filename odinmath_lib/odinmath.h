//
// Created by Jason Fedorowich on 2024-02-18.
//

#ifndef ODINMATH_ODINMATH_H
#define ODINMATH_ODINMATH_H
#define INTRIN
#if defined(INTRIN) && defined(__aarch64__)

#include <arm_neon.h>
#include "vectorintrin.h"

#elif defined(INTRIN) && defined(__x86_64__)
#include <immintrin.h>
#include <xmmintrin.h>
#include <avxintrin.h>
#include "vectorintrin.h"
#endif

#include <exception>
#include "exception.h"
#include "Vector.h"
#include "vector3.h"
#include "vector2.h"
#include "vector4.h"

#endif //ODINMATH_ODINMATH_H
