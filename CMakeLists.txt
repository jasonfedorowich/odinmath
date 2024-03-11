cmake_minimum_required(VERSION 3.27)
#set(CMAKE_OSX_ARCHITECTURES x86_64)


project(odinmath)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

include_directories(odinmath_lib)
add_subdirectory(odinmath_lib)

target_link_libraries(odinmath_lib)

add_subdirectory(tests)
