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

add_library(hpx_runtime OBJECT hpx_runtime.cpp)
target_link_libraries(hpx_runtime PUBLIC HPX::hpx HPX::iostreams_component Halide::Halide)
if(MSVC)
	target_compile_definitions(hpx_runtime PUBLIC NOMINMAX)
endif()

add_halide_library(blur FROM blur_generator
	REGISTRATION parallel_blur) # the name this configuration is registered by

add_executable(runner ${parallel_blur})
target_link_libraries(runner PRIVATE blur Halide::RunGenMain hpx_runtime HPX::hpx HPX::wrap_main)
if(MSVC)
	target_compile_options(runner PRIVATE /FI"hpx/hpx_main.hpp")
else()
	target_compile_options(runner PRIVATE -include hpx/hpx_main.hpp)
endif()
