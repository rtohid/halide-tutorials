cmake_minimum_required(VERSION 3.0.0)
project(HalideHPX VERSION 0.1.0)

include(CTest)
enable_testing()

# Set up language settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

find_package(Halide REQUIRED)
find_package(HPX REQUIRED)

add_library(hpx_runtime OBJECT hpx_runtime.cpp)
target_link_libraries(hpx_runtime PUBLIC HPX::hpx HPX::iostreams_component Halide::Halide)
if(MSVC)
    target_compile_definitions(hpx_runtime PUBLIC NOMINMAX)
endif()

## Double
add_executable(doubler.generator doubler_generator.cpp)
target_link_libraries(doubler.generator PRIVATE 
                      Halide::Generator Halide::Tools)

add_halide_library(doubler FROM doubler.generator)

add_executable(doubling doubler.cpp)
target_link_libraries(doubling PRIVATE doubler 
                      Halide::Halide Halide::Tools
                      hpx_runtime HPX::wrap_main)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
