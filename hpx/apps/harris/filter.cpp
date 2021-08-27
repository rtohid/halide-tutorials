#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "HalideBuffer.h"
#include "HalideRuntime.h"

#include "harris.h"
#include "harris_auto_schedule.h"

#include "halide_benchmark.h"
#include "halide_image_io.h"

#include <hpx/hpx_main.hpp>

using namespace Halide::Tools;

int main(int argc, char **argv) {


    Halide::Runtime::Buffer<float> input = load_and_convert_image("rgba.png");

    // The harris app doesn't use a boundary condition
    Halide::Runtime::Buffer<float> output(input.width() - 6, input.height() - 6);
    output.set_min(3, 3);

    double best_manual = benchmark([&]() {
        harris(input, output);
        output.device_sync();
    });
    printf("Manually-tuned time: %gms\n", best_manual * 1e3);

    //double best_auto = benchmark([&]() {
    //    harris_auto_schedule(input, output);
    //    output.device_sync();
    //});
    //printf("Auto-scheduled time: %gms\n", best_auto * 1e3);

    convert_and_save_image(output, "result.png");

    printf("Success!\n");
    return 0;
}
