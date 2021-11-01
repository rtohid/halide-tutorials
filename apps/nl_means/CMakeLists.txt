# Generator
add_executable(nl_means.generator nl_means_generator.cpp)
target_link_libraries(nl_means.generator PRIVATE Halide::Generator Halide::Tools)

# Filters
add_halide_library(nl_means FROM nl_means.generator)

# Main executable
## HPX
if(HPX_BACKEND)
add_executable(nl_means_process_hpx process.cpp)
target_compile_definitions(nl_means_process_hpx PUBLIC -DHPX_INCLUDE)
target_link_libraries(nl_means_process_hpx
                    PRIVATE
                    Halide::ImageIO
                    nl_means
		            hpx_runtime
                    HPX::wrap_main)
endif()

## Halide
if(HALIDE_BACKEND)
add_executable(nl_means_process_halide process.cpp)
target_link_libraries(nl_means_process_halide
                    PRIVATE
                    Halide::ImageIO
                    nl_means)
endif()
