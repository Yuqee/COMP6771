#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

// test copy from the spec
TEST_CASE("Creation of unit vectors") {
	SECTION("You have two identical vectors") {
		auto a = comp6771::euclidean_vector(2);
		a[0] = 1;
		a[1] = 2;
		auto b = comp6771::euclidean_vector(2);
		b[0] = 1;
		b[1] = 2;

		auto c = comp6771::unit(a);
		auto d = comp6771::unit(b);
		REQUIRE(c == d);
	}
}