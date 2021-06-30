#include "Halide.h"
#include <iostream>

using namespace Halide;

class Blur : public Generator<Blur> {
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
    Func blur_y;
    blur_y(x, y) = (blur_x(x, y - 1), blur_x(x, y), blur_x(x, y + 1)) / 3;
    result(x, y) = cast<uint8_t>(blur_y(x, y));

    // inline everything: 1.82
    // compute root: 5.14
    // inlined upcast and blur_y: 5.14

#ifdef COMPUTE_ROOT
    const int vec = 32;
    Var xi, yi;
    result.compute_root().tile(x, y, xi, yi, 256, vec).vectorize(xi, vec);
    blur_x.compute_at(result, x).vectorize(x, vec);
    input_16.compute_at(result, x).vectorize(x, vec);
#endif
  }
};

HALIDE_REGISTER_GENERATOR(Blur, blur);
