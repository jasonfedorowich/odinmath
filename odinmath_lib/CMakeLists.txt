cmake_minimum_required(VERSION 3.27)
#set(CMAKE_OSX_ARCHITECTURES x86_64)


project(odinmath)

set(HEADER_FILES
        vector3.h
        Vector.h
        odinmath.h
        vectorintrin.h
        vector2.h
        vector4.h
        Matrix.h
        matrix4.h
)

set(SOURCE_FILES
        vector3.cpp
        exception.cpp
        vector2.cpp
        vector4.cpp
        matrix4.cpp
)

add_library(odinmath_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})