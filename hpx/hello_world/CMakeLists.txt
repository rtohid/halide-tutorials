cmake_minimum_required(VERSION 3.16)
project(HPX_runtime)

find_package(HPX REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_executable(parallel_for main.cpp)
target_link_libraries(parallel_for PRIVATE HPX::hpx HPX::wrap_main HPX::iostreams_component)


