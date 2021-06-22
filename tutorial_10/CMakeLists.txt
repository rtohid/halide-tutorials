cmake_minimum_required(VERSION 3.16)
project(Tutorial_10)
find_package(Halide REQUIRED)

# Generator
add_executable(tutorial_10_gen tutorial_10_gen.cpp)
target_link_libraries(tutorial_10_gen PRIVATE Halide::Halide Halide::Tools)
target_compile_options(tutorial_10_gen PRIVATE "$<$<CXX_COMPILER_ID:GNU>:-Wno-unused-but-set-variable>")

# Runner
set(FILTER_LIB "tutorial_10${CMAKE_STATIC_LIBRARY_SUFFIX}")
add_custom_command(OUTPUT tutorial_10.h ${FILTER_LIB}
				   DEPENDS tutorial_10_gen
				   COMMAND ${CMAKE_COMMAND} -E env "ASAN_OPTIONS=detect_leaks=0" $<TARGET_FILE:tutorial_10_gen>
				   VERBATIM)
add_custom_target(exec_tutorial_10_gen
				  DEPENDS tutorial_10.h ${FILTER_LIB})

add_executable(tutorial_10_run tutorial_10_run.cpp)
add_dependencies(tutorial_10_run exec_tutorial_10_gen)
target_include_directories(tutorial_10_run PRIVATE ${CMAKE_CURRENT_LIST_DIR}/build)
target_link_libraries(tutorial_10_run PRIVATE
				      ${CMAKE_CURRENT_BINARY_DIR}/${FILTER_LIB}
				      Halide::Runtime
				      Threads::Threads
				      ${CMAKE_DL_LIBS})
