// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <iostream>
#include <string>

#include "catch2/catch.hpp"

TEST_CASE("Value") {
	SECTION("Semantics") {
		auto const hello = std::string("Hello!");
		auto hello2 = hello;

		// Abort TEST_CASE if expression is false
		REQUIRE(hello == hello2);

		hello2.append("2");
		REQUIRE(hello != hello2);

		CHECK(hello.back() == '!');
		CHECK(hello2.back() == '2');
	}
}
