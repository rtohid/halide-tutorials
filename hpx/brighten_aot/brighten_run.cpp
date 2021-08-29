#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "HalideBuffer.h"
#include "halide_image_io.h"


#include <hpx/hpx_main.hpp>

#include "brighten.h"

using namespace Halide::Tools;

int main(int argc, char** argv) {
  Halide::Runtime::Buffer<uint8_t> input = Halide::Tools::load_image("images/lsu_campus.jpg");
    Halide::Runtime::Buffer<uint8_t> output = Halide::Runtime::Buffer<uint8_t>::make_with_shape_of(input);  
  brighten(input, output);
  Halide::Tools::save_image(output, "images/brighter_campus.jpg");

  printf("Success!\n");
  return 0;
}
