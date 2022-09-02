#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

auto const EPSILON = 0.0001;

// This file tests all the operators overloaded including firends and member functions.
// Used std::addressof to make sure its a copy instead of the object itself.

TEST_CASE("Copy Assignment, copy const to non-const") {
	auto const vec = std::vector<double>{1, 3, 1, 4};
	auto const vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	auto vec2 = comp6771::euclidean_vector(2, 1.33);

	CHECK(vec1.dimensions() == static_cast<int>(vec.size()));
	CHECK(vec1.dimensions() != vec2.dimensions());

	vec2 = vec1;
	std::ostringstream oss1;
	oss1 << vec1;
	std::ostringstream oss2;
	oss2 << vec2;

	CHECK(oss1.str() == "[1 3 1 4]");
	CHECK(vec1.dimensions() == vec2.dimensions());
	CHECK(std::addressof(vec1) != std::addressof(vec2));
	CHECK(oss1.str() == oss2.str());
}

TEST_CASE("Copy Assignment, copy non-const to non-const") {
	auto const vec = std::vector<double>{1, 3, 1, 4};
	auto vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	auto vec2 = comp6771::euclidean_vector(2, 1.33);
	CHECK(vec1.dimensions() == static_cast<int>(vec.size()));
	CHECK(vec1.dimensions() != vec2.dimensions());

	vec2 = vec1;

	vec2 = vec1;
	std::ostringstream oss1;
	oss1 << vec1;
	std::ostringstream oss2;
	oss2 << vec2;

	CHECK(oss1.str() == "[1 3 1 4]");
	CHECK(vec1.dimensions() == vec2.dimensions());
	CHECK(std::addressof(vec1) != std::addressof(vec2));
	CHECK(oss1.str() == oss2.str());
}

TEST_CASE("Move Assignment") {
	auto const vec = std::vector<double>{1.23, 3.222, 1.78, 4};
	auto vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	auto vec1_move = comp6771::euclidean_vector();

	CHECK(vec1.dimensions() == static_cast<int>(vec.size()));
	CHECK(vec1_move.dimensions() == 1);

	vec1_move = std::move(vec1);
	std::ostringstream oss1;
	oss1 << vec1_move;
	std::string vec1_move_string = oss1.str();
	CHECK(vec1.dimensions() == 0);
	CHECK(vec1_move.dimensions() == static_cast<int>(vec.size()));
	CHECK(vec1_move_string == "[1.23 3.222 1.78 4]");
}

TEST_CASE("Self Move") {
	auto const vec = std::vector<double>{1.23, 3.222, 1.78, 4};
	auto vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	vec1 = std::move(vec1);
	CHECK(vec1.dimensions() == 0);
}

TEST_CASE("Subscript") {
	auto const vec1 = comp6771::euclidean_vector{-6.17, 5.88, 0, 6.92, 4.66};
	double num{vec1[1]};
	CHECK(abs(num - 5.88) < EPSILON);

	auto vec2 = comp6771::euclidean_vector(3, 1.22);
	vec2[2] = 0.332;
	std::ostringstream oss;
	oss << vec2;
	std::string vec2_string = oss.str();
	CHECK(vec2_string == "[1.22 1.22 0.332]");
}

TEST_CASE("Unary plus") {
	auto const vec1 = comp6771::euclidean_vector{-6.17, 5.88, 0, 6.92, 4.66};
	auto vec2 = comp6771::euclidean_vector(3, 1.22);
	CHECK(vec1.dimensions() != vec2.dimensions());

	vec2 = +vec1;
	std::ostringstream oss1;
	oss1 << vec1;
	std::string vec1_string = oss1.str();
	std::ostringstream oss2;
	oss2 << vec2;
	std::string vec2_string = oss2.str();
	CHECK(vec2_string == vec1_string);
	CHECK(vec1.dimensions() == vec2.dimensions());
	CHECK(std::addressof(vec1) != std::addressof(vec2));

	auto vec3 = +vec2;
	CHECK(vec3.dimensions() == vec2.dimensions());
	CHECK(std::addressof(vec3) != std::addressof(vec2));
}

TEST_CASE("Negation") {
	auto const vec1 = comp6771::euclidean_vector{0.00231, 2.54, 4.54, 5.32, 7.23};
	auto vec2 = -vec1;
	auto res = vec1 + vec2;
	auto const zeros = comp6771::euclidean_vector(vec1.dimensions());

	REQUIRE(zeros == res);
	CHECK(std::addressof(vec1) != std::addressof(vec2));

	auto vec4 = -vec2;
	res = vec4 + vec2;
	REQUIRE(zeros == res);
	CHECK(std::addressof(vec4) != std::addressof(vec2));
}

TEST_CASE("Compound Addition") {
	auto const vec1 = comp6771::euclidean_vector{0.00231, 2.54, 4.54, 5.32, 7.23};
	auto vec2 = -vec1;
	auto vec3 = vec1;
	vec2 += vec1;
	auto zeros = comp6771::euclidean_vector(vec1.dimensions());
	REQUIRE(vec1 == vec3);
	REQUIRE(zeros == vec2);
	CHECK_THROWS_MATCHES(vec2 += comp6771::euclidean_vector(vec2.dimensions() + 1),
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Dimensions of LHS(5) and RHS(6) do not match"));
	vec3[1] = 0;
}

TEST_CASE("Compound Subtraction") {
	auto const vec1 = comp6771::euclidean_vector{0.00231, 2.54, 4.54, 5.32, 7.23};
	auto vec2 = comp6771::euclidean_vector(vec1.dimensions());
	auto vec3 = vec1;
	vec2 -= vec1;
	REQUIRE(vec1 == -vec2);
	REQUIRE(vec1 == vec3);
	CHECK_THROWS_MATCHES(vec2 += comp6771::euclidean_vector(vec2.dimensions() + 1),
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Dimensions of LHS(5) and RHS(6) do not match"));
	vec3[1] = 0;
}

TEST_CASE("Compound Multiplication") {
	auto const vec1 = comp6771::euclidean_vector(10, 3.1415926);
	auto vec2 = vec1;
	vec2 *= -1;
	CHECK(vec2 == -vec1);
	vec2 *= -1;
	CHECK(vec1 == vec2);
}

TEST_CASE("Compound Division") {
	auto const vec1 = comp6771::euclidean_vector(10, 3.1415926);
	auto vec2 = vec1;
	vec2 /= -1;
	CHECK(vec2 == -vec1);
	vec2 /= -1;
	CHECK(vec1 == vec2);
	CHECK_THROWS_MATCHES(vec2 /= 0,
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Invalid vector division by 0"));
}

TEST_CASE("Vector and List Type Conversion") {
	auto vec = std::vector<double>{1, 2, 3};
	auto const vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	auto const cast_vec = static_cast<std::vector<double>>(vec1);
	REQUIRE_THAT(vec, Catch::Matchers::Equals(cast_vec));

	auto const cast_list = static_cast<std::list<double>>(vec1);
	auto const lis = std::list<double>{1, 2, 3};
	CHECK(lis == cast_list);
}

TEST_CASE("Logic Equal and not Equal") {
	auto vec = std::vector<double>{7.12, 7.3435, 7.232, 7.232, 0.3237};
	auto const vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	auto const vec2 = comp6771::euclidean_vector(vec.begin(), vec.end());
	CHECK(vec1 == vec2);
	auto vec3 = vec2;
	CHECK(vec3 == vec1);
	vec3[2] += 0.323242;
	CHECK(vec3 != vec2);
	CHECK(vec3 != vec1);
}

TEST_CASE("Addition") {
	auto const vec = std::vector<double>{7.12, 7.3435, 7.232, 7.232, 0.3237};
	auto const vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	auto const vec2 = -vec1;
	auto vec3 = vec1 + vec2;
	auto zeros = comp6771::euclidean_vector(vec1.dimensions());
	CHECK(vec3 == zeros);
	vec3 = vec1 + zeros;
	CHECK(vec3 == vec1);
	auto const cast_vec = static_cast<std::vector<double>>(vec3);
	REQUIRE_THAT(vec, Catch::Matchers::Equals(cast_vec));
	CHECK_THROWS_MATCHES(vec1 + comp6771::euclidean_vector(vec1.dimensions() + 1),
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Dimensions of LHS(5) and RHS(6) do not match"));
}

TEST_CASE("Subtraction") {
	auto const vec = std::vector<double>{7.12, 7.3435, 7.232, 7.232, 0.3237};
	auto const vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	auto zeros = comp6771::euclidean_vector(vec1.dimensions());
	auto vec3 = zeros - vec1;
	CHECK(vec3 == -vec1);
	vec3 = zeros - vec3;
	CHECK(vec3 == vec1);
	auto const cast_vec = static_cast<std::vector<double>>(vec3);
	REQUIRE_THAT(vec, Catch::Matchers::Equals(cast_vec));
	CHECK_THROWS_MATCHES(vec1 - comp6771::euclidean_vector(vec1.dimensions() + 1),
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Dimensions of LHS(5) and RHS(6) do not match"));
}

TEST_CASE("Multiply") {
	auto const vec = std::vector<double>{7.12, 7.3435, 7.232, 7.232, 0.3237};
	auto const vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	auto vec3 = vec1 * (-1);
	CHECK(vec3 == -vec1);
	vec3 = (-1) * vec3;
	CHECK(vec3 == vec1);
	auto const cast_vec = static_cast<std::vector<double>>(vec3);
	REQUIRE_THAT(vec, Catch::Matchers::Equals(cast_vec));
	vec3 = vec1 * 0;
	CHECK(vec3 == comp6771::euclidean_vector(vec1.dimensions()));
}

TEST_CASE("Divide") {
	auto num = double{3.1415926};
	auto div = double{2.77};
	auto const vec1 = comp6771::euclidean_vector(20, num);
	auto const vec2 = vec1 / 1;
	CHECK(vec1 == vec2);
	auto const vec3 = vec1 / div;
	CHECK(vec3 == comp6771::euclidean_vector(20, num / div));
	CHECK_THROWS_MATCHES(vec3 / 0,
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Invalid vector division by 0"));
}

TEST_CASE("Output stream") {
	auto vec1 = comp6771::euclidean_vector();
	std::ostringstream oss1;
	oss1 << vec1;
	CHECK(oss1.str() == "[0]");

	auto const vec2 = std::move(vec1);
	std::ostringstream oss2;
	oss2 << vec2;
	CHECK(oss2.str() == "[0]");

	std::ostringstream oss3;
	oss3 << vec1;
	CHECK(oss3.str() == "[]");

	auto const num = double{6.3782034232};
	auto const size = int{66};
	auto vec = std::vector<double>(size, num);
	auto vec4 = comp6771::euclidean_vector(size, num);
	std::ostringstream oss4;
	oss4 << vec4;
	std::ostringstream oss5;
	oss5 << "[";
	for (auto iter = vec.begin(); iter != vec.end() - 1; ++iter) {
		oss5 << *iter << " ";
	}
	oss5 << num << "]";
	CHECK(oss4.str() == oss5.str());
}

TEST_CASE("Operation on 0-dim vectors") {
	auto vec1 = comp6771::euclidean_vector();
	auto vec2 = std::move(vec1);
	auto const vec3 = comp6771::euclidean_vector(std::move(vec2));
	auto res = vec1 + vec2;
	CHECK(res.dimensions() == 0);
	CHECK_THROWS_AS(res.at(0), comp6771::euclidean_vector_error);

	res = vec1 - vec2;
	CHECK(res.dimensions() == 0);
	CHECK_THROWS_AS(res.at(0), comp6771::euclidean_vector_error);

	res += vec1;
	CHECK(res.dimensions() == 0);
	CHECK_THROWS_AS(res.at(0), comp6771::euclidean_vector_error);

	res -= vec1;
	CHECK(res.dimensions() == 0);
	CHECK_THROWS_AS(res.at(0), comp6771::euclidean_vector_error);

	res *= double{0.6189923};
	CHECK(res.dimensions() == 0);
	CHECK_THROWS_AS(res.at(0), comp6771::euclidean_vector_error);

	res /= double{0.6189923};
	CHECK(res.dimensions() == 0);
	CHECK_THROWS_AS(res.at(0), comp6771::euclidean_vector_error);
}