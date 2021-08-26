#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "HalideBuffer.h"
#include "halide_image_io.h"

#include "blur.h"

using namespace Halide::Tools;

int main(int argc, char** argv) {


    Halide::Runtime::Buffer<uint8_t> input = load_and_convert_image("gray.png");

    // The harris app doesn't use a boundary condition
    Halide::Runtime::Buffer<uint8_t> output = Halide::Runtime::Buffer<uint8_t>::make_with_shape_of(input);

    blur(input, output);
    convert_and_save_image(output, "blurred.png");

    printf("Success!\n");
    return 0;
}
