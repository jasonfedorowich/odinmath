enable_testing()
#set(CMAKE_OSX_ARCHITECTURES x86_64)
#set(INTRIN 1)
add_compile_definitions(INTRIN)

project(tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(odinmath_tests_run
        vector3_test.cpp
        vector_intrin_test.cpp
        vector2_test.cpp
        vector4_test.cpp
        matrix4_test.cpp
        matrix3_test.cpp
        vector_test.cpp
        matrix_test.cpp
        matrix2_test.cpp
        matrix_intrin_test.cpp
        quaternion_test.cpp
        trig_test.cpp
        math_test.cpp)

target_link_libraries(odinmath_tests_run odinmath_lib)

target_link_libraries(odinmath_tests_run gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(odinmath_tests_run)