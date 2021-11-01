# Generator
add_executable(iir_blur.generator iir_blur_generator.cpp)
target_link_libraries(iir_blur.generator PRIVATE Halide::Generator)

# Filters
add_halide_library(iir_blur FROM iir_blur.generator)

# Main executable
## HPX
if(HPX_BACKEND)
    add_executable(iir_blur_filter_hpx filter.cpp)
    target_compile_definitions(iir_blur_filter_hpx PUBLIC -DHPX_INCLUDE)
    target_link_libraries(iir_blur_filter_hpx PRIVATE
                        Halide::Tools
                        Halide::ImageIO
                        iir_blur
                        hpx_runtime
                        HPX::wrap_main)
endif()

## Halide
if(HALIDE_BACKEND)
    add_executable(iir_blur_filter_halide filter.cpp)
    target_link_libraries(iir_blur_filter_halide PRIVATE
                      Halide::Tools
                      Halide::ImageIO
                      iir_blur)
endif()