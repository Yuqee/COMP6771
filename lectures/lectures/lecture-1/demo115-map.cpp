// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <string>
#include <unordered_map>

#include "catch2/catch.hpp"

auto check_code_mapping(std::unordered_map<std::string, std::string> const& country_codes,
                        std::string const& code,
                        std::string const& name) -> void {
	auto const country = country_codes.find(code);
	REQUIRE(country != country_codes.end());

	auto const [key, value] = *country;
	CHECK(code == key);
	CHECK(name == value);
}

TEST_CASE("hash map") {
	auto country_codes = std::unordered_map<std::string, std::string>{
	{"AU", "Australia"},
	{"NZ", "New Zealand"},
	{"CK", "Cook Islands"},
	{"ID", "Indonesia"},
	{"DK", "Denmark"},
	{"CN", "China"},
	{"JP", "Japan"},
	{"ZM", "Zambia"},
	{"YE", "Yemen"},
	{"CA", "Canada"},
	{"BR", "Brazil"},
	{"AQ", "Antarctica"},
	};

	CHECK(country_codes.contains("AU"));
	CHECK(not country_codes.contains("DE")); // Germany not present

	check_code_mapping(country_codes, "AU", "Australia");
	check_code_mapping(country_codes, "NZ", "New Zealand");
	check_code_mapping(country_codes, "CK", "Cook Islands");
	check_code_mapping(country_codes, "ID", "Indonesia");
	check_code_mapping(country_codes, "DK", "Denmark");
	check_code_mapping(country_codes, "CN", "China");
	check_code_mapping(country_codes, "JP", "Japan");
	check_code_mapping(country_codes, "ZM", "Zambia");
	check_code_mapping(country_codes, "YE", "Yemen");
	check_code_mapping(country_codes, "CA", "Canada");
	check_code_mapping(country_codes, "BR", "Brazil");
	check_code_mapping(country_codes, "AQ", "Antarctica");

	country_codes.emplace("DE", "Germany");
	check_code_mapping(country_codes, "DE", "Germany");
}
