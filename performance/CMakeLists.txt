add_executable(doubler.generator doubler_generator.cpp)
target_link_libraries(doubler.generator PRIVATE 
Halide::Generator Halide::Tools)

add_halide_library(doubler FROM doubler.generator)

# Double
## HPX
if(HPX_BACKEND)
    add_executable(doubling_hpx doubler.cpp)
    target_compile_definitions(doubling_hpx PUBLIC -DHPX_INCLUDE)
    target_link_libraries(doubling_hpx PRIVATE doubler 
        Halide::Halide Halide::Tools
        hpx_runtime HPX::wrap_main)
endif()

## Halide
if(HALIDE_BACKEND)
    add_executable(doubling_halide doubler.cpp)
    target_link_libraries(doubling_halide PRIVATE doubler 
    	Halide::Halide Halide::Tools)
endif()

