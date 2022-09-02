#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

auto const EPSILON = 0.0001;

// This file tests member functions and the expections they should throw.
TEST_CASE("at return value") {
	auto num = double{0.0031415926};
	auto size = int{66};
	auto const vec1 = comp6771::euclidean_vector(size, num);
	CHECK(abs(vec1.at(7) - num) < EPSILON);
	CHECK_THROWS_MATCHES(vec1.at(1000),
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Index 1000 is not valid for this "
	                                              "euclidean_vector object"));
	CHECK_THROWS_MATCHES(vec1.at(-1000),
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Index -1000 is not valid for this "
	                                              "euclidean_vector object"));
}

TEST_CASE("at return refernce") {
	auto num = double{0.0031415926};
	auto vec1 = comp6771::euclidean_vector(int{66}, num);
	CHECK(abs(vec1.at(7) - num) < EPSILON);
	vec1.at(7) = 0;
	CHECK(vec1.at(7) == 0);
	CHECK(vec1.at(7) == vec1[7]);
	CHECK_THROWS_MATCHES(vec1.at(-1),
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Index -1 is not valid for this "
	                                              "euclidean_vector object"));
}

TEST_CASE("dimensions()") {
	auto dim = int{200};
	auto vec = std::vector<double>(static_cast<size_t>(dim));
	auto vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	CHECK(vec1.dimensions() == dim);
}