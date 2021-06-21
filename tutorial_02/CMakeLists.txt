cmake_minimum_required(VERSION 3.16)
project(Tutorial_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

find_package(Halide REQUIRED)

add_executable(tutorial_02 tutorial_02.cpp)
target_link_libraries(tutorial_02 PRIVATE Halide::Halide Halide::ImageIO Halide::Tools)
