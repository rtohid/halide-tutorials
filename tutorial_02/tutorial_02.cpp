// Copyright (c) 2021 R. Tohid (@rtohid)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include<iostream>
#include<Halide.h>
#include<halide_image_io.h>

int main(int argv, char** argc) {
	Halide::Buffer<uint8_t> input = Halide::Tools::load_image("images/rgb.png");
	Halide::Func brighter;
	Halide::Var x, y, c;
	Halide::Expr value = input(x, y, c);

	value = Halide::cast<float>(value);
	value = value * 1.5f;
	value = Halide::min(value, 225.0f);
	value = Halide::cast<uint8_t>(value);
	brighter(x, y, c) = value;

	Halide::Buffer<uint8_t>output = brighter.realize(input.width(), input.height(), input.channels());
	Halide::Tools::save_image(output, "images/brighter.png");
	std::cout << "SUCCESS" << std::endl;

	return 0;

}
