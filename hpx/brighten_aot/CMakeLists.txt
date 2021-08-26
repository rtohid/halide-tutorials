cmake_minimum_required(VERSION 3.16)
project(brighten)

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

add_executable(brighten.generator brighten_aot.cpp)
target_link_libraries(brighten.generator PRIVATE Halide::Generator)


add_halide_library(brighten FROM brighten.generator)

add_executable(runner brighten_run.cpp)
target_link_libraries(runner PRIVATE brighten Halide::ImageIO hpx_runtime HPX::wrap_main)


# cmake_minimum_required(VERSION 3.16)
# project(HPX_runtime)
# 
# find_package(HPX REQUIRED)
# 
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED YES)
# set(CMAKE_CXX_EXTENSIONS NO)
# 
# add_executable(loopy main.cpp)
# target_link_libraries(loopy PRIVATE HPX::hpx HPX::wrap_main HPX::iostreams_component)


