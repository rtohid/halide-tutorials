#include <Halide.h>
#include <HalideRuntime.h>

#include <hpx/hpx_main.hpp>
#include <hpx/iostream.hpp>

#include <hpx/include/parallel_for_loop.hpp>
#include <hpx/runtime.hpp>

extern "C" int halide_do_par_for(void *ctx, int (*f)(void *, int, uint8_t *),
                              int min, int extent, uint8_t *closure) {
  hpx::for_loop(hpx::execution::par, min, min + extent,
                [&](int i) { f(ctx, i, closure); });
  return 0;
}

