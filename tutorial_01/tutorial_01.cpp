// Copyright (c) 2021 R. Tohid (@rtohid)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include<Halide.h>
#include<iostream>
#include<stdio.h>

int main (int argv, char** argc){
	Halide::Func gradient;
	Halide::Var x, y;

	Halide::Expr e = x + y;
	gradient (x, y) = e;
	Halide::Buffer<int32_t> output = gradient.realize(800, 600);
	for (int i = 0; i < 800; i++){
		for (int j = 0; j < 600; j++){
			if (output(i, j) != i + j){
				printf("Something went wrong!\n" "Pixel %d, %d was supposed to be %d, but instead it's %d\n", i, j, i + j, output(i, j));
				return -1;
			}
		}
	}

	std::cout << "SUCCESS" << std::endl;

	return 0;

}
