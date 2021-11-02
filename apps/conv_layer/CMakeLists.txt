# Generator
add_executable(conv_layer.generator conv_layer_generator.cpp)
target_link_libraries(conv_layer.generator PRIVATE Halide::Generator)

# Filters
add_halide_library(conv_layer FROM conv_layer.generator)

# Main executable
## HPX
if(HPX_BACKEND)
    add_executable(conv_layer_process_hpx process.cpp)
    target_compile_definitions(conv_layer_process_hpx PUBLIC -DHPX_INCLUDE)
    target_link_libraries(conv_layer_process_hpx
                        PRIVATE
                        Halide::Tools
                        conv_layer
                        hpx_runtime
                        HPX::wrap_main)
endif()

## Halide
if(HALIDE_BACKEND)
    add_executable(conv_layer_process_halide process.cpp)
    target_link_libraries(conv_layer_process_halide
                      PRIVATE
                      Halide::Tools
                      conv_layer)
endif()
