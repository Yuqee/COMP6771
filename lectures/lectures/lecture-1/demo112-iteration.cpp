// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <string>
#include <vector>

#include "catch2/catch.hpp"

auto square(int const x) -> int {
	return x * x;
}

auto cube(int const x) -> int {
	return x * square(x);
}

auto all_computer_scientists(std::vector<std::string> const& names) -> bool {
	auto const famous_mathematician = std::string("Gauss");
	auto const famous_physicist = std::string("Newton");

	for (auto const& name : names) {
		if (name == famous_mathematician or name == famous_physicist) {
			return false;
		}
	}

	return true;
}

auto square_vs_cube() -> bool {
	// 0 and 1 are special cases, since they're actually equal.
	if (square(0) != cube(0) or square(1) != cube(1)) {
		return false;
	}

	for (auto i = 2; i < 100; ++i) {
		if (square(i) == cube(i)) {
			return false;
		}
	}

	return true;
}

TEST_CASE("Iteration") {
	// Test cases should avoid having loops in them, since that's logic, and we don't write tests for
	// our tests, so we put the loops in some "program logic" and "test" that.
	SECTION("Range-based for") {
		auto const famous_computer_scientists = std::vector<std::string>{
		"Borg",
		"Dahl",
		"Knuth",
		"Hamilton",
		"Hopper",
		"Lovelace",
		"Nygaard",
		"Ritchie",
		"Stepanov",
		"Stroustrup",
		"Thompson",
		"Turing",
		};
		CHECK(all_computer_scientists(famous_computer_scientists));
	}

	SECTION("for-statement") {
		CHECK(square_vs_cube());
	}
}
