// Copyright (c) 2021 R. Tohid (@rtohid)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include<Halide.h>
#include<iostream>
#include<stdio.h>

int main (int argv, char** argc){
	Halide::Func brighter;
	Halide::Var x, y;
	Halide::Param<uint8_t> offset;
	Halide::ImageParam input(Halide::type_of<uint8_t>(), 2);
	brighter(x,y) = input(x,y) + offset;
	brighter.vectorize(x, 16).parallel(y);
	brighter.compile_to_static_library("tutorial_10", {input, offset}, "brighter");
	std::cout << "SUCCESS" << std::endl;

	return 0;

}
