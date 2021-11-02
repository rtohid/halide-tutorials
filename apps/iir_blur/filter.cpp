#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "HalideBuffer.h"
#include "HalideRuntime.h"

#include "iir_blur.h"

#include "halide_benchmark.h"
#include "halide_image_io.h"

#ifdef HPX_INCLUDE
#include <hpx/hpx_main.hpp>
#endif

using namespace Halide::Tools;

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: %s in out\n", argv[0]);
    return 1;
  }

  Halide::Runtime::Buffer<float> input = load_and_convert_image(argv[1]);
  Halide::Runtime::Buffer<float> output(input.width(), input.height(),
                                        input.channels());

  auto start = benchmark_now();

  iir_blur(input, 0.5f, output);
  auto end = benchmark_now();
  double elapsed_seconds = benchmark_duration_seconds(start, end);
  printf("time: %gms\n", elapsed_seconds * 1e3);

  convert_and_save_image(output, argv[2]);

  return 0;
}
