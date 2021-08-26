cmake_minimum_required(VERSION 3.16)
project(blur)

find_package(HPX REQUIRED)
find_package(Halide REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_library(hpx_runtime OBJECT hpx_runtime.cpp)
target_link_libraries(hpx_runtime PUBLIC HPX::hpx HPX::iostreams_component Halide::Halide)
if(MSVC)
	target_compile_definitions(hpx_runtime PUBLIC NOMINMAX)
endif()

add_executable(blur.generator blur_aot.cpp)
target_link_libraries(blur.generator PRIVATE Halide::Generator)


add_halide_library(blur FROM blur.generator)

add_executable(runner blur_run.cpp)
target_link_libraries(runner PRIVATE blur Halide::ImageIO hpx_runtime HPX::wrap_main)
# if(MSVC)
# 	target_compile_options(runner PRIVATE /FI"hpx/hpx_main.hpp")
# else()
# 	target_compile_options(runner PRIVATE -include hpx/hpx_main.hpp)
# endif()
