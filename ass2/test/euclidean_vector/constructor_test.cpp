#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

auto const EPSILON = 0.0001;

// This file tests all the constructors.
// Used some operators for checking.
TEST_CASE("Default Constructor") {
	auto const vec1 = comp6771::euclidean_vector{};

	CHECK(vec1.dimensions() == 1);
	CHECK(abs(vec1[0] - 0.0) < EPSILON);
	CHECK(abs(vec1.at(0) - 0.0) < EPSILON);

	auto vec2 = comp6771::euclidean_vector();
	CHECK(vec1.dimensions() == vec2.dimensions());
	CHECK(abs(vec1[0] - vec2[0]) < EPSILON);
	CHECK(abs(vec1.at(0) - vec2.at(0)) < EPSILON);
}

TEST_CASE("Single-argument Constructor") {
	auto const size = int{5};
	auto const vec1 = comp6771::euclidean_vector(size);
	CHECK(vec1.dimensions() == size);
	std::ostringstream oss1;
	oss1 << vec1;
	std::string vec1_string = oss1.str();
	CHECK(vec1_string == "[0 0 0 0 0]");

	auto vec2 = comp6771::euclidean_vector(size);
	CHECK(vec1.dimensions() == vec2.dimensions());
	std::ostringstream oss2;
	oss2 << vec2;
	std::string vec2_string = oss2.str();
	CHECK(vec1_string == vec2_string);
}

TEST_CASE("Double-argument Constructor") {
	auto const size = int{5};
	auto const val = double{5.7};
	auto const vec1 = comp6771::euclidean_vector(size, val);
	CHECK(vec1.dimensions() == size);
	std::ostringstream oss1;
	oss1 << vec1;
	std::string vec1_string = oss1.str();
	CHECK(vec1_string == "[5.7 5.7 5.7 5.7 5.7]");

	auto vec2 = comp6771::euclidean_vector(size, val);
	CHECK(vec1.dimensions() == vec2.dimensions());
	std::ostringstream oss2;
	oss2 << vec2;
	std::string vec2_string = oss2.str();
	CHECK(vec1_string == vec2_string);
}

TEST_CASE("Iterator Constructor") {
	auto const vec = std::vector<double>{5, 7, 8};
	auto const vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	CHECK(vec1.dimensions() == static_cast<int>(vec.size()));
	std::ostringstream oss1;
	oss1 << vec1;
	std::string vec1_string = oss1.str();
	CHECK(vec1_string == "[5 7 8]");

	auto vec2 = comp6771::euclidean_vector(vec.begin(), vec.end());
	CHECK(vec1.dimensions() == vec2.dimensions());
	std::ostringstream oss2;
	oss2 << vec2;
	std::string vec2_string = oss2.str();
	CHECK(vec1_string == vec2_string);
}

TEST_CASE("Initializer_list Constructor") {
	auto const init_list = std::initializer_list<double>{6, 1, 7};
	auto const vec1 = comp6771::euclidean_vector(init_list);
	CHECK(vec1.dimensions() == static_cast<int>(init_list.size()));
	std::ostringstream oss1;
	oss1 << vec1;
	std::string vec1_string = oss1.str();
	CHECK(vec1_string == "[6 1 7]");

	auto vec2 = comp6771::euclidean_vector(init_list);
	CHECK(vec1.dimensions() == vec2.dimensions());
	std::ostringstream oss2;
	oss2 << vec2;
	std::string vec2_string = oss2.str();
	CHECK(vec1_string == vec2_string);
}

TEST_CASE("Copy Constructor") {
	auto const vec = std::vector<double>{1, 3, 1, 4};
	auto const vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	auto const vec2 = comp6771::euclidean_vector(vec1);
	std::ostringstream oss1;
	oss1 << vec1;
	std::string vec1_string = oss1.str();
	std::ostringstream oss2;
	oss2 << vec2;
	std::string vec2_string = oss2.str();

	CHECK(vec1.dimensions() == static_cast<int>(vec.size()));
	CHECK(vec1_string == "[1 3 1 4]");
	CHECK(vec1.dimensions() == vec2.dimensions());
	CHECK(vec1_string == vec2_string);
}

TEST_CASE("Move Constructor") {
	auto const vec = std::vector<double>{1, 3, 1, 4};
	auto vec1 = comp6771::euclidean_vector(vec.begin(), vec.end());
	CHECK(vec1.dimensions() == static_cast<int>(vec.size()));

	auto vec1_move = comp6771::euclidean_vector(std::move(vec1));
	std::ostringstream oss1;
	oss1 << vec1_move;
	std::string vec1_move_string = oss1.str();
	CHECK(vec1.dimensions() == 0);
	CHECK(vec1_move.dimensions() == static_cast<int>(vec.size()));
	CHECK(vec1_move_string == "[1 3 1 4]");
}

TEST_CASE("Move Constructor more") {
	auto vec2 = comp6771::euclidean_vector(2, 1.2);
	auto const vec2_move = comp6771::euclidean_vector(std::move(vec2));
	std::ostringstream oss2;
	oss2 << vec2_move;
	std::string vec2_move_string = oss2.str();
	CHECK(vec2.dimensions() == 0);
	CHECK(vec2_move.dimensions() == 2);
	CHECK(vec2_move_string == "[1.2 1.2]");
}