#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

auto const EPSILON = 0.0001;

// This test file has native loops for the cache_test to compare the time with.
// If the norm is cached properly, the running time of
// cache_test and norm_test should be very close.

TEST_CASE("norm") {
	auto dim = 100000;
	auto vec1 = comp6771::euclidean_vector(dim, 1);
	auto norm1 = comp6771::euclidean_norm(vec1);
	CHECK(abs(norm1 - sqrt(dim)) < EPSILON);
	for (auto i = 0; i < dim; ++i) {
		CHECK(abs(norm1 - sqrt(dim)) < EPSILON);
	}
	auto num = double{3};
	vec1 *= num;
	auto norm2 = comp6771::euclidean_norm(vec1);
	CHECK(abs(norm2 - sqrt(dim * pow(num, 2.0))) < EPSILON);
}

TEST_CASE("norm cache +=") {
	auto const dim = 1000;
	auto const epoch = 100000;
	auto vec1 = comp6771::euclidean_vector(dim, 1);
	auto norm1 = comp6771::euclidean_norm(vec1);
	CHECK(abs(norm1 - sqrt(dim)) < EPSILON);

	auto zeros = comp6771::euclidean_vector(vec1.dimensions());
	for (auto i = 0; i < epoch; ++i) {
		vec1 += zeros;
		CHECK(abs(norm1 - sqrt(dim)) < EPSILON);
	}
}

TEST_CASE("norm cache -=") {
	auto const dim = 1000;
	auto const epoch = 100000;
	auto vec1 = comp6771::euclidean_vector(dim, 1);
	auto norm1 = comp6771::euclidean_norm(vec1);
	CHECK(abs(norm1 - sqrt(dim)) < EPSILON);

	auto zeros = comp6771::euclidean_vector(vec1.dimensions());
	for (auto i = 0; i < epoch; ++i) {
		vec1 -= zeros;
		CHECK(abs(norm1 - sqrt(dim)) < EPSILON);
	}
}

TEST_CASE("norm cache *=") {
	auto const dim = 1000;
	auto const epoch = 100000;
	auto vec1 = comp6771::euclidean_vector(dim, 1);
	auto norm1 = comp6771::euclidean_norm(vec1);
	CHECK(abs(norm1 - sqrt(dim)) < EPSILON);

	for (auto i = 0; i < epoch; ++i) {
		vec1 *= 1;
		CHECK(abs(norm1 - sqrt(dim)) < EPSILON);
	}
}

TEST_CASE("norm cache /=") {
	auto const dim = 1000;
	auto const epoch = 100000;
	auto vec1 = comp6771::euclidean_vector(dim, 1);
	auto norm1 = comp6771::euclidean_norm(vec1);
	CHECK(abs(norm1 - sqrt(dim)) < EPSILON);

	for (auto i = 0; i < epoch; ++i) {
		vec1 /= 1;
		CHECK(abs(norm1 - sqrt(dim)) < EPSILON);
	}
}