// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <string>

#include <catch2/catch.hpp>

TEST_CASE("Basic types") {
	SECTION("Numbers") {
		int meaning_of_life = 42; // type `int`, for integers.
		double six_feet_in_metres = 1.8288; // type `double`, for rational numbers.
		CHECK(six_feet_in_metres < meaning_of_life); // report if this expression is false
	}

	SECTION("Text") {
		std::string course_code = std::string("Applied Modern C++"); // type `string`, for text.
		char letter = 'A'; // type `char`, for single characters.
		CHECK(course_code.front() == letter);
	}

	SECTION("Truth values") {
		bool is_cxx = true; // type `bool`, for truth
		bool is_danish = false;
		CHECK(is_cxx != is_danish);
	}
}
