# cmake_minimum_required(VERSION 3.16)
# project(HPX_runtime)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED YES)
# set(CMAKE_CXX_EXTENSIONS NO)

# find_package(Halide REQUIRED)

# add_executable(loopy loopy.cpp)
# target_link_libraries(loopy PRIVATE Halide::Halide)
# set_target_properties(loopy PROPERTIES ENABLE_EXPORTS TRUE)

cmake_minimum_required(VERSION 3.16)
project(my_hpx_project CXX)
find_package(HPX REQUIRED)
add_executable(my_hpx_program main.cpp)
target_link_libraries(my_hpx_program HPX::hpx HPX::wrap_main HPX::iostreams_component)