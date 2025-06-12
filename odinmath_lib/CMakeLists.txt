cmake_minimum_required(VERSION 3.27)
#set(CMAKE_OSX_ARCHITECTURES x86_64)


project(odinmath)

set(HEADER_FILES
        include/vector3.h
        include/Vector.h
        odinmath.h
        include/vectorintrin.h
        include/vector2.h
        include/vector4.h
        include/Matrix.h
        include/matrix4.h
        include/matrix3.h
        include/matrixintrin.h
        include/matrix2.h
        include/matrix3.h
        include/quaternion.h
        include/trigonometry.h
        include/math.h
        include/qr.h
)

set(SOURCE_FILES
        src/vector3.cpp
        src/exception.cpp
        src/vector2.cpp
        src/vector4.cpp
        src/matrix4.cpp
        src/matrix3.cpp
        src/matrix2.cpp
        src/quaternion.cpp
        src/qr.cpp
)

add_library(odinmath_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})