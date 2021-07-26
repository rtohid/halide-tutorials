cmake_minimum_required(VERSION 3.16)
project(blur)

find_package(HPX REQUIRED)
find_package(Halide REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_INSTALL_RPATH /work/rtohid/Halide/cmake-build-debug/lib64/)

add_executable(blur_generator blur_aot.cpp)
target_link_libraries(blur_generator PRIVATE Halide::Generator)

add_library(hpx_runtime hpx_runtime.cpp)
target_link_libraries(hpx_runtime PRIVATE HPX::hpx HPX::wrap_main HPX::iostreams_component Halide::Halide)

add_halide_library(blur FROM blur_generator
	REGISTRATION parallel_blur) # the name this configuration is registered by

add_executable(runner ${parallel_blur})
target_link_libraries(runner PRIVATE blur Halide::RunGenMain hpx_runtime)

