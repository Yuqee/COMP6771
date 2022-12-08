// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <cmath>
#include <string>

#include "catch2/catch.hpp"

TEST_CASE("Expressions") {
	SECTION("Integral arithmetic") {
		auto const x = 10;
		auto const y = 173;

		auto const sum = 183;
		CHECK(x + y == sum);

		auto const difference = 163;
		CHECK(y - x == difference);
		CHECK(x - y == -difference);

		auto const product = 1730;
		CHECK(x * y == product);

		auto const quotient = 17;
		CHECK(y / x == quotient);

		auto const remainder = 3;
		CHECK(y % x == remainder);
	}

	SECTION("Floating-point arithmetic") {
		auto const x = 15.63;
		auto const y = 1.23;

		auto const sum = 16.86;
		CHECK(x + y == sum);

		auto const difference = 14.4;
		CHECK(x - y == difference);
		CHECK(y - x == -difference);

		auto const product = 19.2249;
		CHECK(x * y == product);

		auto const expected_quotient = 12.7073170732;
		auto const actual_quotient = x / y;
		auto const acceptable_delta = 0.0000001;
		CHECK(std::abs(expected_quotient - actual_quotient) < acceptable_delta);
	}

	SECTION("String expressions") {
		auto const hello_expr = std::string("Hello, expressions!");
		auto const hello_cpp = std::string("Hello, C++!");
		CHECK(hello_expr != hello_cpp);
		CHECK(hello_expr.front() == hello_cpp[0]);

		SECTION("C++ copies values, not references") {
			auto hello_expr2 = hello_expr;
			REQUIRE(hello_expr == hello_expr2); // Abort TEST_CASE if expression is false
			hello_expr2.append("2");
			REQUIRE(hello_expr != hello_expr2);
			CHECK(hello_expr.back() == '!');
			CHECK(hello_expr2.back() == '2');
		}
	}

	SECTION("Boolean expressions") {
		auto const is_amcxx = true;
		auto const is_about_cxx = true;
		auto const is_about_german = false;

		CHECK((is_amcxx and is_about_cxx));
		CHECK((is_about_german or is_about_cxx));
		CHECK(not is_about_german);
	}
}
