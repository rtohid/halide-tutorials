// Halide tutorial lesson 15: Generators part 1

// https://halide-lang.org/tutorials/tutorial_lesson_15_generators.html

#include "Halide.h"
#include <stdio.h>

using namespace Halide;

class Blur : public Halide::Generator<Blur> {
public:
  Input<Buffer<uint8_t>> input{"input", 2};
  Output<Buffer<uint8_t>> result{"result", 2};

  void generate() {
    Var x, y;
    Func clamped = BoundaryConditions::repeat_edge(input);
    Func input_16;
    input_16(x, y) = cast<uint16_t>(clamped(x, y));
    Func blur_x;
    blur_x(x, y) =
        (input_16(x - 1, y) + input_16(x, y) + input_16(x + 1, y)) / 3;
    blur_x.compute_root().parallel(y);
    Func blur_y;
    blur_y(x, y) = (blur_x(x, y - 1), blur_x(x, y), blur_x(x, y + 1)) / 3;
    result(x, y) = cast<uint8_t>(blur_y(x, y));
  }
};

HALIDE_REGISTER_GENERATOR(Blur, blur)
