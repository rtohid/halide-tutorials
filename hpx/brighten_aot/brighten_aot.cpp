#include "Halide.h"
#include <stdio.h>

using namespace Halide;

class Brighten : public Halide::Generator<Brighten> {
public:
  Input<Buffer<uint8_t>> input{ "input", 3};
  Output<Buffer<uint8_t>> output{ "output", 3};

  void generate() {
    Func brighter;
    Var x, y, c;
    Expr value = input(x, y, c);
    value = Halide::cast<float>(value);
    value = value * 1.5f + value;
    value = Halide::min(value, 255.0f);
    value = Halide::cast<uint8_t>(value);
    brighter(x, y, c) = value;
    output(x, y, c) = brighter(x, y, c);
    brighter.compute_root().parallel(x);
  }
};

HALIDE_REGISTER_GENERATOR(Brighten, brighten)