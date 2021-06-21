// Copyright (c) 2021 R. Tohid (@rtohid)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include<iostream>
#include<Halide.h>

int main(int argv, char** argc) {
	Halide::Func gradient("gradient");
	Halide::Var x("x"), y("y");
	gradient(x, y) = x + y;
	Halide::Buffer<int> output = gradient.realize(8, 8);
	gradient.compile_to_lowered_stmt("gradient.html", {}, Halide::HTML);
	std::cout << "SUCCESS" << std::endl;

	return 0;

}
