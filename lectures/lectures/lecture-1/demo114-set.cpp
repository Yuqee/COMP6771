// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <catch2/catch.hpp>

#include <string>
#include <unordered_set>

TEST_CASE("Sets of values") {
	auto computer_scientists = std::unordered_set<std::string>{
	"Lovelace",
	"Babbage",
	"Turing",
	"Hamilton",
	"Church",
	"Borg",
	};

	CHECK(computer_scientists.contains("Lovelace"));
	CHECK(not computer_scientists.contains("Gauss"));

	SECTION("Inserting and removing an element") {
		computer_scientists.insert("Gauss");
		CHECK(computer_scientists.contains("Gauss"));

		computer_scientists.erase("Gauss");
		CHECK(not computer_scientists.contains("Gauss"));
	}

	SECTION("Finding an element") {
		auto ada = computer_scientists.find("Lovelace");
		REQUIRE(ada != computer_scientists.end());

		CHECK(*ada == "Lovelace");
	}

	SECTION("An empty set") {
		computer_scientists.clear();
		CHECK(computer_scientists.empty());
	}
}
