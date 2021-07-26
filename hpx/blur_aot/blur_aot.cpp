// Halide tutorial lesson 15: Generators part 1

// https://halide-lang.org/tutorials/tutorial_lesson_15_generators.html

#include "Halide.h"
#include <stdio.h>

using namespace Halide;

class Blur : public Halide::Generator<Blur> {
public:
  Input<uint8_t> offset{"offset"};
  Input<Buffer<uint8_t>> input{"input", 2};

  Output<Buffer<uint8_t>> output{"output", 2};

  Var x, y;

  void generate() {
    output(x, y) = input(x, y) + offset;
    output.vectorize(x, 16).parallel(y);
  }
};

HALIDE_REGISTER_GENERATOR(Blur, blur)
