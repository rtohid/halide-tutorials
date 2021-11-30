#include "Halide.h"

using namespace Halide;

class Doubler : public Halide::Generator<Doubler> {
public:
    Output<Buffer<double>> out_buffer{ "out_buffer", 1 };
    Input<int> coeff {"coeff"};
    Input<Buffer<double>> in_buffer{ "in_buffer", 1};
    Var x;
    Var x_i,x_o;

    void generate() {
        Halide::Func f("f");
        f(x) = x * coeff;

        out_buffer(x) = in_buffer(x) * coeff;
//        out_buffer.split(x,x_o,x_i,16);
//        out_buffer.vectorize(x_i);
        out_buffer.parallel(x);
    }
};

HALIDE_REGISTER_GENERATOR(Doubler, doubler)
