// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "catch2/catch.hpp"

auto is_even(int const x) -> bool {
	return x % 2 == 0;
}

auto collatz_point_if_statement(int const x) -> int {
	if (is_even(x)) {
		return x / 2;
	}

	return 3 * x + 1;
}

auto collatz_point_conditional(int const x) -> int {
	return is_even(x) ? x / 2 : 3 * x + 1;
}

auto is_digit(char const c) -> bool {
	switch (c) {
	case '0': [[fallthrough]];
	case '1': [[fallthrough]];
	case '2': [[fallthrough]];
	case '3': [[fallthrough]];
	case '4': [[fallthrough]];
	case '5': [[fallthrough]];
	case '6': [[fallthrough]];
	case '7': [[fallthrough]];
	case '8': [[fallthrough]];
	case '9': return true;
	default: return false;
	}
}

TEST_CASE("Selection") {
	CHECK(collatz_point_conditional(6) == 3);
	CHECK(collatz_point_conditional(5) == 16);

	CHECK(collatz_point_if_statement(6) == collatz_point_conditional(6));
	CHECK(collatz_point_if_statement(5) == collatz_point_conditional(5));

	CHECK(is_digit('0'));
	CHECK(is_digit('1'));
	CHECK(is_digit('2'));
	CHECK(is_digit('3'));
	CHECK(is_digit('4'));
	CHECK(is_digit('5'));
	CHECK(is_digit('6'));
	CHECK(is_digit('7'));
	CHECK(is_digit('8'));
	CHECK(is_digit('9'));
	CHECK(not is_digit('A'));
	CHECK(not is_digit('Z'));
	CHECK(not is_digit('a'));
	CHECK(not is_digit('z'));
	CHECK(not is_digit('~'));
	CHECK(not is_digit('!'));
	CHECK(not is_digit('\0'));
	CHECK(not is_digit('\n'));
}
