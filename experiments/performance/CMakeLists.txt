cmake_minimum_required(VERSION 3.16)
project(doubler)

# Set up language settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# Find Halide
find_package(Halide REQUIRED)
SET(HPX_BACKEND ON CACHE BOOL "HPX backend")
SET(HALIDE_BACKEND ON CACHE BOOL "Halide backend")
SET(WITH_APEX ON CACHE BOOL "With apex support")


if(HPX_BACKEND)
    find_package(HPX REQUIRED)
    add_library(hpx_runtime OBJECT profiling.cpp)
    target_compile_definitions(hpx_runtime PUBLIC -DHPX_INCLUDE)
    target_link_libraries(hpx_runtime PUBLIC HPX::hpx HPX::iostreams_component Halide::Halide)
    if(MSVC)
        target_compile_definitions(hpx_runtime PUBLIC NOMINMAX)
    endif()
endif()

# Generator
add_executable(doubler.generator doubler_generator.cpp)
target_link_libraries(doubler.generator
        PRIVATE
        Halide::Generator)

## Filters
add_halide_library(doubler FROM doubler.generator)
add_halide_library(doubler_auto_schedule FROM doubler.generator
        GENERATOR doubler
        AUTOSCHEDULER Halide::Mullapudi2016)
#
# Main executable
if(HPX_BACKEND)
    find_package(HPX)
    add_executable(doubling_hpx doubler.cpp)
    target_compile_definitions(doubling_hpx PUBLIC -DHPX_INCLUDE)
    target_link_libraries(doubling_hpx PRIVATE doubler
            Halide::Halide Halide::Tools
            hpx_runtime HPX::wrap_main)
endif()

## Halide
if(HALIDE_BACKEND)
    add_library(profiling OBJECT profiling.cpp)
    # Make sure the compiler can find include files from our Apex library.
    include_directories (${APEX_SOURCE_DIR}/src/apex)
    # Make sure the linker can find the Apex library once it is built.
    link_directories (${APEX_BINARY_DIR}/src/apex)
    target_link_libraries(profiling PUBLIC Halide::Halide)

    add_executable(doubling_halide doubler.cpp)
    target_compile_definitions(doubling_halide PUBLIC -DAPEX)
    target_link_libraries(doubling_halide PRIVATE doubler
            Halide::Halide Halide::Tools
            profiling apex)

endif()