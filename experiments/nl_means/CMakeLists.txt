cmake_minimum_required(VERSION 3.16)
project(nl_means)

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
add_executable(nl_means.generator nl_means_generator.cpp)
target_link_libraries(nl_means.generator PRIVATE Halide::Generator Halide::Tools)

# Filters
add_halide_library(nl_means FROM nl_means.generator)
add_halide_library(nl_means_auto_schedule FROM nl_means.generator
                   GENERATOR nl_means
                   AUTOSCHEDULER Halide::Mullapudi2016)

# Main executable
if(HPX_BACKEND)
add_executable(nl_means_process_hpx process.cpp)
target_compile_definitions(nl_means_process_hpx PUBLIC -DHPX_INCLUDE)
target_link_libraries(nl_means_process_hpx
                      PRIVATE
                      Halide::ImageIO
                      nl_means
                      nl_means_auto_schedule
		      hpx_runtime
                      HPX::wrap_main)
endif()
if(HALIDE_BACKEND)
add_executable(nl_means_process_halide process.cpp)
target_link_libraries(nl_means_process_halide
                      PRIVATE
                      Halide::ImageIO
                      nl_means
                      nl_means_auto_schedule)
endif()
