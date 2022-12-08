// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "catch2/catch.hpp"

TEST_CASE("Enumerations") {
	enum class computing_courses {
		intro,
		data_structures,
		engineering_design,
		compilers,
		amcxx,
	};

	auto const computing101 = computing_courses::intro;
	auto const computing102 = computing_courses::data_structures;
	CHECK(computing101 != computing102);

	// enum class fake_courses {
	// 	intro,
	// 	data_structures,
	// 	engineering_design,
	// 	compilers,
	// 	amcxx,
	// };

	// auto const fake_computing101 = fake_courses::intro;
	// CHECK(computing101 == fake_computing101);
	// error: courses and fake_courses are different types
}
