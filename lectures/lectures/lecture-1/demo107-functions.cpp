// Copyright (c) Hayden Smith.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "catch2/catch.hpp"

#include <sstream>

// Nullary function
bool is_about_cxx() {
	return true;
}

// Unary function
int square(int const x) {
	return x * x;
}

double square(double const x) {
	return x * x;
}

// Binary function
double rectangular_area(double const width, double const length) {
	return width * length;
}

std::string rgb(short r = 0, short g = 0, short b = 0) {
	std::stringstream my_string;
	my_string << "(" << r << "," << g << "," << b << ")";
	return my_string.str();
}

TEST_CASE("Functions") {
	CHECK(is_about_cxx());
	CHECK(square(2) == 4);
	CHECK(square(2.0) == 4.0);
	CHECK(rectangular_area(2.0, 4.0) == 8.0);
}

TEST_CASE("Default arguments") {
	CHECK(rgb() == "(0,0,0)");
	CHECK(rgb(100) == "(100,0,0)");
	CHECK(rgb(100, 200) == "(100,200,0)");
	// CHECK(rgb(100, ,200) == ...) // Error
}
