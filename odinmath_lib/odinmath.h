//
// Created by Jason Fedorowich on 2024-02-18.
//

#ifndef ODINMATH_ODINMATH_H
#define ODINMATH_ODINMATH_H

#include <exception>
#include "include/exception.h"

#include "include/Vector.h"
#include "include/Matrix.h"

#define INTRIN
#if defined(INTRIN) && defined(__aarch64__)

#include <arm_neon.h>
#include "include/vectorintrin.h"
#include "include/matrixintrin.h"

#elif defined(INTRIN) && defined(__x86_64__)
#include <immintrin.h>
#include <xmmintrin.h>
#include <avxintrin.h>
#include "vectorintrin.h"
#endif


#include "include/vector4.h"
#include "include/vector3.h"
#include "include/vector2.h"
#include "include/matrix4.h"
#include "include/matrix3.h"
#include "include/matrix2.h"


#endif //ODINMATH_ODINMATH_H
