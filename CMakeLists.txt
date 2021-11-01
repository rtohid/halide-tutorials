cmake_minimum_required(VERSION 3.0.0)
project(PLDI VERSION 0.1.0)

# Set up language settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# Find Halide
find_package(Halide REQUIRED)
SET(HPX_BACKEND ON CACHE BOOL "HPX backend")
SET(HALIDE_BACKEND ON CACHE BOOL "Halide backend")

if(HPX_BACKEND)
    find_package(HPX REQUIRED)

    add_library(hpx_runtime OBJECT hpx_runtime.cpp)
    target_link_libraries(hpx_runtime PUBLIC HPX::hpx HPX::iostreams_component Halide::Halide)
    if(MSVC)
        target_compile_definitions(hpx_runtime PUBLIC NOMINMAX)
    endif()
endif()

add_subdirectory(apps)
add_subdirectory(linear_algebra)
add_subdirectory(performance)
