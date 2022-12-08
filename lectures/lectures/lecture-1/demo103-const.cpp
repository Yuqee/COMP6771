// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <iostream>
#include <string>

#include "catch2/catch.hpp"

// Unique and independent context
TEST_CASE("Basic types") {
	// SETUP

	SECTION("Numbers") {
		// `int` for integers.
		auto const meaning_of_life = 42;

		// `double` for rational numbers.
		auto const six_feet_in_metres = 1.8288;

		// report if this expression is false
		CHECK(six_feet_in_metres < meaning_of_life);
	}
}
