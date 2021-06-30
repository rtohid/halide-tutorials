cmake_minimum_required(VERSION 3.16)
project(HPX_runtime)

#find_package(HPX REQUIRED)
find_package(Halide REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_INSTALL_RPATH /work/rtohid/Halide/install-release/lib64/)

add_executable(blurring blur_generator.cpp)
target_link_libraries(blurring PRIVATE Halide::Generator)
add_halide_library(blur FROM blurring)
#add_executable(runner /work/rtohid/Halide/tools/RunGenMain.cpp blur_generator.cpp)
#target_link_libraries(blur PRIVATE Halide::Halide Halide::ImageIO Halide::Tools Halide::RunGenMain)
##target_link_libraries(blur PRIVATE HPX::hpx HPX::wrap_main HPX::iostreams_component Halide::Halide Halide::ImageIO Halide::Tools)
#set_target_properties(blur PROPERTIES ENABLE_EXPORTS TRUE)

