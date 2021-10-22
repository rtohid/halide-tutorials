cmake_minimum_required(VERSION 3.16)
project(iir_blur)

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

# Generator
add_executable(iir_blur.generator iir_blur_generator.cpp)
target_link_libraries(iir_blur.generator PRIVATE Halide::Generator)

# Filters
add_halide_library(iir_blur FROM iir_blur.generator)
add_halide_library(iir_blur_auto_schedule FROM iir_blur.generator
                   GENERATOR iir_blur
                   AUTOSCHEDULER Halide::Mullapudi2016)

# Main executable
if(HALIDE_BACKEND)
add_executable(iir_blur_filter_halide filter.cpp)
target_link_libraries(iir_blur_filter_halide PRIVATE
                      Halide::Tools
                      Halide::ImageIO
                      iir_blur
                      iir_blur_auto_schedule)
endif()

if(HPX_BACKEND)
add_executable(iir_blur_filter_hpx filter.cpp)
target_compile_definitions(iir_blur_filter_hpx PUBLIC -DHPX_INCLUDE)
target_link_libraries(iir_blur_filter_hpx PRIVATE
                      Halide::Tools
                      Halide::ImageIO
                      iir_blur
                      iir_blur_auto_schedule
		      hpx_runtime
                      HPX::wrap_main)
endif()

