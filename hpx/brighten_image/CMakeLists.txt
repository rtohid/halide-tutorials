cmake_minimum_required(VERSION 3.16)
project(HPX_runtime)

find_package(HPX REQUIRED)
find_package(Halide REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_executable(loopy loopy.cpp)
target_link_libraries(loopy PRIVATE HPX::hpx HPX::wrap_main HPX::iostreams_component Halide::Halide Halide::ImageIO Halide::Tools)
set_target_properties(loopy PROPERTIES ENABLE_EXPORTS TRUE)


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


