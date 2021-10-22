#include <iostream>

#include "doubler.h"
#include "HalideBuffer.h"
#include "Halide.h"

#include <hpx/hpx_main.hpp>

#define N 10000000

using namespace Halide;

int main(int argc, char** argv) {
    std::vector<double> in_vector(N, 1);
    // generate(in_vector.begin(), in_vector.end(), rand);
    Runtime::Buffer<double> in_buffer(in_vector.data(), N);
    Runtime::Buffer<double> out_buffer(in_buffer.width() * in_buffer.height());

    doubler(2, in_buffer, out_buffer);

    for (size_t i = 0; i < 10; i++)
    {
        std::cout << in_buffer(i) << " " << out_buffer(i) << std::endl;
    }

    return 0;
}