cmake_minimum_required(VERSION 3.27)
#set(CMAKE_OSX_ARCHITECTURES x86_64)

#Release
#cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Release

#Tests
#ctest --rerun-failed --output-on-failure
#ctest --test-dir ./tests

project(odinmath)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

include_directories(odinmath_lib)
add_subdirectory(odinmath_lib)

target_link_libraries(odinmath_lib)

add_subdirectory(tests)
