#include "Halide.h"

using namespace Halide;

class Doubler : public Halide::Generator<Doubler> {
public:
    Output<Buffer<double>> out_buffer{ "out_buffer", 1 };
    Input<int> coeff {"coeff"};
    Input<Buffer<double>> in_buffer{ "in_buffer", 1};
    Var x;

    void generate() {
        out_buffer(x) = in_buffer(x) * coeff;
        out_buffer.parallel(x);
    }
};

HALIDE_REGISTER_GENERATOR(Doubler, doubler)
