#include "gdwg/graph.hpp"

#include <catch2/catch.hpp>
#include <sstream>

/*This file tests the comparisons and extractor of gdwg. Mostly done by check
if some value inside gdwg is euqal to the expected value or the
modified object behave as they expected to be.*/

TEST_CASE("g1 == g2") {
	auto const g1 = gdwg::graph<std::string, std::string>{};
	auto g2 = gdwg::graph<std::string, std::string>{};
	CHECK(g1 == g2);
	auto g3 = gdwg::graph<std::string, std::string>{"people", "love", "dragons"};
	CHECK(g2 != g3);
	g2.insert_node("love");
	g2.insert_node("people");
	g2.insert_node("dragons");
	CHECK(g2 == g3);
	g2.insert_edge("people", "love", "hard to achive");
	g3.insert_edge("people", "love", "hard to achive");
	g2.insert_edge("love", "people", "magic");
	g3.insert_edge("love", "people", "magic");
	CHECK(g2 == g3);
	g2.erase_node("dragons");
	CHECK(g2 != g3);
	g2.clear();
	g3.clear();
	CHECK(g2 == g3);
}

TEST_CASE("extractor1") {
	using graph = gdwg::graph<int, int>;
	auto const v = std::vector<graph::value_type>{
	   {4, 1, -4},
	   {3, 2, 2},
	   {2, 4, 2},
	   {2, 1, 1},
	   {6, 2, 5},
	   {6, 3, 10},
	   {1, 5, -1},
	   {3, 6, -8},
	   {4, 5, 3},
	   {5, 2, 7},
	};

	auto g = graph{};
	for (const auto& [from, to, weight] : v) {
		g.insert_node(from);
		g.insert_node(to);
		g.insert_edge(from, to, weight);
	}

	g.insert_node(64);
	auto out = std::ostringstream{};
	out << g;
	auto const expected_output = std::string_view(R"(1 (
  5 | -1
)
2 (
  1 | 1
  4 | 2
)
3 (
  2 | 2
  6 | -8
)
4 (
  1 | -4
  5 | 3
)
5 (
  2 | 7
)
6 (
  2 | 5
  3 | 10
)
64 (
)
)");
	CHECK(out.str() == expected_output);
}

TEST_CASE("extractor2") {
	auto g = gdwg::graph<std::string, int>{};
	g.insert_node("hello");
	g.insert_node("how");
	g.insert_node("are");
	g.insert_node("you?");

	g.insert_edge("hello", "how", 5);
	g.insert_edge("hello", "are", 8);
	g.insert_edge("hello", "are", 2);

	g.insert_edge("how", "you?", 1);
	g.insert_edge("how", "hello", 4);

	g.insert_edge("are", "you?", 3);

	std::ostringstream str;
	str << g;
	auto const expected_output = std::string_view(R"(are (
  you? | 3
)
hello (
  are | 2
  are | 8
  how | 5
)
how (
  hello | 4
  you? | 1
)
you? (
)
)");
	CHECK(str.str() == expected_output);
}

TEST_CASE("extractor3") {
	auto g = gdwg::graph<std::string, int>{};

	std::ostringstream str;
	str << g;
	auto const expected_output = std::string_view(R"()");
	CHECK(str.str() == expected_output);
}