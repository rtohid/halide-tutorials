// Copyright (c) 2021 R. Tohid (@rtohid)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include<HalideBuffer.h>
#include<iostream>

#include"tutorial_10.h"

int main(int argv, char** argc) {
	Halide::Runtime::Buffer<uint8_t> input(640, 480), output(640, 480);
    int offset = 5;
    int error = brighter(input, offset, output);
	if (error) {
		std::cout << "Halide returned an error: " << std::endl;
		std::cout << error << std::endl;
	}

	for (int y = 0; y < 480; y++) {
		for (int x = 0; x < 640; x++) {
			uint8_t input_val = input(x, y);
			uint8_t output_val = output(x, y);
			uint8_t correct_val = input_val + offset;
			if (output_val != correct_val) {
				printf("output(%d, %d) was %d instead of %d\n",
					x, y, output_val, correct_val);
				return -1;
			}
		}
	}
	std::cout << "SUCCESS" << std::endl;

	return 0;

}
