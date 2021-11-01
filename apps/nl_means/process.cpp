#include <chrono>
#include <cstdio>

#include "nl_means.h"

#include "HalideBuffer.h"
#include "halide_benchmark.h"
#include "halide_image_io.h"

#ifdef HPX_INCLUDE
#include <hpx/hpx_main.hpp>
#endif

using namespace Halide::Runtime;
using namespace Halide::Tools;

int main(int argc, char **argv) {
  if (argc < 7) {
    printf("Usage: ./process input.png patch_size search_area sigma "
           "timing_iterations output.png\n"
           "e.g.: ./process input.png 7 7 0.12 10 output.png\n");
    return 0;
  }

  Buffer<float> input = load_and_convert_image(argv[1]);
  int patch_size = atoi(argv[2]);
  int search_area = atoi(argv[3]);
  float sigma = atof(argv[4]);
  Buffer<float> output(input.width(), input.height(), 3);
  int timing_iterations = atoi(argv[5]);

  auto start = benchmark_now();

  nl_means(input, patch_size, search_area, sigma, output);

  auto end = benchmark_now();
  double elapsed_seconds = benchmark_duration_seconds(start, end);
  printf("time: %gms\n", elapsed_seconds * 1e3);

  return 0;
}
