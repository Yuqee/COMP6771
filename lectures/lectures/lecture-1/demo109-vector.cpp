// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <catch2/catch.hpp>

#include <vector>

TEST_CASE("Collections of objects") {
	auto const single_digits = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto more_single_digits = single_digits;
	REQUIRE(single_digits == more_single_digits);

	more_single_digits[2] = 0;
	CHECK(single_digits != more_single_digits);
}
