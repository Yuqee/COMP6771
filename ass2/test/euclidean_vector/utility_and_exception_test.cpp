#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

// This file test unity functions and its expections.

TEST_CASE("unit") {
	auto dim = 100;
	auto vec1 = comp6771::euclidean_vector(dim, 1);
	auto unit1 = comp6771::unit(vec1);
	auto point1 = comp6771::euclidean_vector(dim, 0.1);
	CHECK(unit1 == point1);

	auto num = double{3};
	vec1 *= num;
	unit1 = comp6771::unit(vec1);
	CHECK(unit1 == point1);
}

TEST_CASE("unit exception") {
	auto const dim = 100;
	auto vec1 = comp6771::euclidean_vector();
	auto vec2 = std::move(vec1);
	CHECK_THROWS_MATCHES(comp6771::unit(vec1),
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("euclidean_vector with no dimensions does not "
	                                              "have a unit vector"));
	auto vec3 = comp6771::euclidean_vector(dim);
	CHECK_THROWS_MATCHES(comp6771::unit(vec3),
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("euclidean_vector with zero euclidean normal does "
	                                              "not have a unit vector"));
}

TEST_CASE("dot") {
	auto const dim = 100;
	auto const ones = comp6771::euclidean_vector(dim, 1);
	CHECK(comp6771::dot(ones, ones) == dim);
	auto longer_ones = comp6771::euclidean_vector(dim + 1, 1);
	CHECK_THROWS_MATCHES(comp6771::dot(longer_ones, ones),
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Dimensions of LHS(101) and RHS(100) do not "
	                                              "match"));
}