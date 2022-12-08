// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "catch2/catch.hpp"

TEST_CASE("Promoting conversions") {
	auto const i = 42;

	SECTION("Promoting conversions") { // These are okay, but prefer explicit conversions below
		auto d = 0.0;
		d = i; // Silent conversion from int to double
		CHECK(d == 42.0);
		CHECK(d != 41);
	}

	SECTION("Explicit conversions") { // Preferred over implicit, since your intention is clear
		auto const d = static_cast<double>(i);
		CHECK(d == 42.0);
		CHECK(d != 41);
	}
}
