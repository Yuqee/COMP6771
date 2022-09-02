#include "gdwg/graph.hpp"

#include <algorithm>
#include <catch2/catch.hpp>
#include <initializer_list>
#include <vector>

/*This file test all the constructors of gdwg. Mostly done by check
if some value inside gdwg is euqal to the expected value.*/

/*Empty graph is empty and its iterators should be both end()*/
TEST_CASE("Default constructor") {
	auto g = gdwg::graph<int, std::string>{};
	CHECK(g.empty());
	CHECK(g.begin() == g.end());
}

/*As mentioned in spec, graph(il.begin(), li.end())
has the same effect, check every nodes and const-correctness.
const g1 and non-const should have the same result,
check if every nodes has been sorted.*/
TEST_CASE("Initializer list constructor") {
	auto li = std::initializer_list<std::string>{"6771", "is", "a", "great", "crouse"};
	auto const g1 = gdwg::graph<std::string, std::string>(li);
	auto g2 = gdwg::graph<std::string, std::string>(li.begin(), li.end());
	CHECK(g1 == g2);
	CHECK(g1.nodes() == g2.nodes());
	auto vec1 = g1.nodes();
	std::sort(vec1.begin(), vec1.end());
	CHECK(g1.nodes() == vec1);
}

/*Similar as TEST_CASE("Initializer list constructor")*/
TEST_CASE("Input iterator constructor") {
	auto li = std::vector<std::string>{"c++", "is", "a", "great", "progamming language"};
	auto const g1 = gdwg::graph<std::string, std::string>(li.begin(), li.end());
	auto g2 = gdwg::graph<std::string, std::string>(li.begin(), li.end());
	CHECK(g1 == g2);
	CHECK(g1.nodes() == g2.nodes());
	auto vec1 = g1.nodes();
	std::sort(vec1.begin(), vec1.end());
	CHECK(g1.nodes() == vec1);
}

/*Last loop checks iterators pointing to *this*/
TEST_CASE("Move constructor") {
	auto li = std::vector<std::string>{"c++", "is", "a", "great", "progamming language"};
	auto g1 = gdwg::graph<std::string, std::string>(li.begin(), li.end());
	g1.insert_edge("c++", "a", "good");
	g1.insert_edge("c++", "is", "nice");
	auto vec1 = g1.nodes();
	auto g2 = gdwg::graph<std::string, std::string>(std::move(g1));
	CHECK(g2.nodes() == vec1);
	std::sort(vec1.begin(), vec1.end());
	CHECK(g2.nodes() == vec1);
	CHECK(g1.empty());
	CHECK(std::all_of(g1.begin(), g1.end(), [&g1](auto const& val) {
		auto [from, to, weight] = val;
		return g1.find(from, to, weight) != g1.end();
	}));
	CHECK(std::all_of(g2.begin(), g2.end(), [&g2](auto const& val) {
		auto [from, to, weight] = val;
		return g2.find(from, to, weight) != g2.end();
	}));
}

/*Similar as TEST_CASE("Move constructor")*/
TEST_CASE("Move assignment") {
	auto li = std::vector<std::string>{"c++", "is", "a", "great", "progamming language"};
	auto g1 = gdwg::graph<std::string, std::string>(li.begin(), li.end());
	g1.insert_edge("c++", "a", "good");
	g1.insert_edge("c++", "is", "nice");
	auto vec1 = g1.nodes();
	auto g2 = std::move(g1);
	CHECK(g2.nodes() == vec1);
	std::sort(vec1.begin(), vec1.end());
	CHECK(g2.nodes() == vec1);
	CHECK(g1.empty());
	CHECK(std::all_of(g1.begin(), g1.end(), [&g1](auto const& val) {
		auto [from, to, weight] = val;
		return g1.find(from, to, weight) != g1.end();
	}));
}

/*Match accessors*/
TEST_CASE("Copy constructor") {
	auto li = std::vector<std::string>{"c++", "is", "a", "great", "progamming language"};
	auto g1 = gdwg::graph<std::string, std::string>(li.begin(), li.end());
	g1.insert_edge("c++", "a", "good");
	g1.insert_edge("c++", "is", "nice");

	auto const g2 = gdwg::graph<std::string, std::string>(g1);
	CHECK(g2.nodes() == g1.nodes());

	CHECK(std::all_of(g1.begin(), g1.end(), [&g1, &g2](auto const& val) {
		auto [from, to, weight] = val;
		return g1.weights(from, to) == g2.weights(from, to);
	}));

	CHECK(std::all_of(g2.begin(), g2.end(), [&g1, &g2](auto const& val) {
		auto [from, to, weight] = val;
		return g1.weights(from, to) == g2.weights(from, to);
	}));
	CHECK(g1 == g2);
}

/*Similar as TEST_CASE("Copy constructor")*/
TEST_CASE("Copy assignment") {
	auto li = std::vector<std::string>{"c++", "is", "a", "great", "progamming language"};
	auto g1 = gdwg::graph<std::string, std::string>(li.begin(), li.end());
	g1.insert_edge("c++", "a", "good");
	g1.insert_edge("c++", "is", "nice");

	auto const g2 = g1;
	CHECK(g2.nodes() == g1.nodes());

	CHECK(std::all_of(g1.begin(), g1.end(), [&g1, &g2](auto const& val) {
		auto [from, to, weight] = val;
		return g1.weights(from, to) == g2.weights(from, to);
	}));

	CHECK(std::all_of(g2.begin(), g2.end(), [&g1, &g2](auto const& val) {
		auto [from, to, weight] = val;
		return g1.weights(from, to) == g2.weights(from, to);
	}));

	CHECK(g1 == g2);
}