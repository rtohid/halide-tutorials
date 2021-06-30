#include "Halide.h"
#include "halide_image_io.h"
#include <stdio.h>

#include <hpx/hpx_main.hpp>
#include <hpx/iostream.hpp>

#include <hpx/include/parallel_for_loop.hpp>
#include <hpx/runtime.hpp>

using namespace Halide;

int hpx_parallel_loop(void *ctx, int (*f)(void *, int, uint8_t *), int min,
                      int extent, uint8_t *closure) {
  hpx::for_loop(hpx::execution::par, min, min + extent,
                [&](int i) { f(ctx, i, closure); });
  return 0;
}

int main(int argc, char **argv) {
  Buffer<uint8_t> input = Halide::Tools::load_image("images/lsu_campus.jpg");
  Func brighter;
  Var x, y, c;
  Expr value = input(x, y, c);
  value = Halide::cast<float>(value);
  value = value * 1.5f + value;
  value = Halide::min(value, 255.0f);
  value = Halide::cast<uint8_t>(value);
  brighter(x, y, c) = value;
  brighter.parallel(x);
  brighter.set_custom_do_par_for(&hpx_parallel_loop);
  hpx::chrono::high_resolution_timer t;
  Buffer<uint8_t> output =
      brighter.realize({input.width(), input.height(), input.channels()});
  std::cout << "ELAPSED: " << t.elapsed() << std::endl;
  Halide::Tools::save_image(output, "images/brighter_campus.jpg");

  printf("Success!\n");
  return 0;
}
