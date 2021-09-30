cmake_minimum_required(VERSION 3.16)
project(conv_layer)

enable_testing()

# Set up language settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# Find Halide
find_package(Halide REQUIRED)
find_package(HPX REQUIRED)

add_library(hpx_runtime OBJECT hpx_runtime.cpp)
target_link_libraries(hpx_runtime PUBLIC HPX::hpx HPX::iostreams_component Halide::Halide)
if(MSVC)
    target_compile_definitions(hpx_runtime PUBLIC NOMINMAX)
endif()

# Generator
add_executable(conv_layer.generator conv_layer_generator.cpp)
target_link_libraries(conv_layer.generator
                      PRIVATE
                      Halide::Generator)

# Filters
add_halide_library(conv_layer FROM conv_layer.generator)
add_halide_library(conv_layer_auto_schedule FROM conv_layer.generator
                   GENERATOR conv_layer
                   AUTOSCHEDULER Halide::Mullapudi2016)

# Main executable
add_executable(conv_layer_process process.cpp)
target_link_libraries(conv_layer_process
                      PRIVATE
                      Halide::ImageIO
                      conv_layer
                      conv_layer_auto_schedule
                      hpx_runtime
                      HPX::wrap_main)

# Test that the app actually works!
add_test(NAME conv_layer_process COMMAND conv_layer_process)
set_tests_properties(conv_layer_process PROPERTIES
                     LABELS conv_layer
                     PASS_REGULAR_EXPRESSION "Success!"
                     SKIP_REGULAR_EXPRESSION "\\[SKIP\\]")
