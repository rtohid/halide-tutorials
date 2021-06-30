cmake_minimum_required(VERSION 3.16)
project(HPX_runtime)

#find_package(HPX REQUIRED)
find_package(Halide REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_INSTALL_RPATH /work/rtohid/Halide/install-release/lib64/)

add_executable(blurring blur_generator.cpp)
target_link_libraries(blurring PRIVATE Halide::Generator)

add_halide_library(blur FROM blurring REGISTRATION blur_reg)
add_executable(runner ${blur_reg})
target_link_libraries(runner PRIVATE blur Halide::RunGenMain)

