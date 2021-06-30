cmake_minimum_required(VERSION 3.16)
project(HPX_runtime)

find_package(HPX REQUIRED)
find_package(Halide REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_executable(blur blur_generator.cpp)
target_link_libraries(blur PRIVATE HPX::hpx HPX::wrap_main HPX::iostreams_component Halide::Halide Halide::ImageIO Halide::Tools)
set_target_properties(blur PROPERTIES ENABLE_EXPORTS TRUE)

