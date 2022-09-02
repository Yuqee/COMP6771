#include "gdwg/graph.hpp"

#include <catch2/catch.hpp>
#include <stdexcept>
#include <vector>

/*This file tests the modifier of gdwg. Mostly done by check
if some value inside gdwg is euqal to the expected value or the
modified object behave as they expected to be.*/

/*Insert a vec of nodes into g, nodes in g should be the same as in vec and sorted.*/
TEST_CASE("inser_node") {
	auto const vec = std::vector<double>{3.1, 3.14, 3.141, 3.1415, 3.14159, 3.141592};
	auto g = gdwg::graph<double, std::string>{};

	CHECK(std::all_of(vec.begin(), vec.end(), [&g](auto const& v) { return g.insert_node(v); }));
	CHECK(std::all_of(vec.begin(), vec.end(), [&g](auto const& v) { return g.is_node(v); }));
	CHECK(std::none_of(vec.begin(), vec.end(), [&g](auto const& v) { return g.insert_node(v); }));
	CHECK(g.nodes() == vec);
}

/*Throws and false conditions checked*/
TEST_CASE("insert_edges") {
	// NOLINT <good reason why>
	auto g = gdwg::graph<int, int>{};
	CHECK_THROWS_MATCHES(g.insert_edge(1, 2, 3),
	                     std::runtime_error,
	                     Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::insert_edge when "
	                                              "either src or dst node does not exist"));
	g.insert_node(1);
	g.insert_node(7);
	g.insert_node(12);
	g.insert_node(14);
	g.insert_node(19);
	g.insert_node(21);
	CHECK(g.insert_edge(1, 7, 4));
	g.insert_edge(1, 7, 3);
	g.insert_edge(1, 7, 12);
	g.insert_edge(1, 12, 3);
	CHECK(g.insert_edge(1, 12, 3) == false);
	CHECK(std::vector<int>{3, 4, 12} == g.weights(1, 7));
}

/*TEST_CASE("replace_node1") test the fucntion and TEST_CASE("replace_node2") checks the
expception.*/
TEST_CASE("replace_node1") {
	auto g1 = gdwg::graph<char, int>{};
	g1.insert_node('A');
	g1.insert_node('B');
	g1.insert_node('C');
	g1.insert_node('D');
	g1.insert_edge('A', 'D', 3);
	g1.insert_edge('A', 'D', 1);
	g1.insert_edge('A', 'B', 2);
	auto const g2 = g1;
	auto const vec = g1.nodes();
	CHECK(std::none_of(vec.begin(), vec.end(), [&g1, &g2](auto const& v) {
		return g1.replace_node(v, 'A') || !(g1 == g2);
	}));
	auto const weis = g1.weights('A', 'D');
	g1.replace_node('A', 'E');
	CHECK(g1.is_node('A') == false);
	CHECK(g1.is_node('E') == true);
	CHECK(g1.weights('E', 'D') == weis);
}

TEST_CASE("replace_node2") {
	auto g1 = gdwg::graph<char, int>{};
	{
		g1.insert_node('A');
		g1.insert_node('B');
		g1.insert_node('C');
		g1.insert_node('D');
		g1.insert_edge('A', 'D', 3);
		g1.insert_edge('A', 'D', 1);
		g1.insert_edge('A', 'B', 2);
	}
	CHECK_THROWS_MATCHES(g1.replace_node('Z', 'D'),
	                     std::runtime_error,
	                     Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::replace_node on a "
	                                              "node that doesn't exist"));
}

/*example from spec*/
TEST_CASE("merge_replace_node1") {
	auto g1 = gdwg::graph<char, int>{};
	{
		g1.insert_node('A');
		g1.insert_node('B');
		g1.insert_node('C');
		g1.insert_node('D');
		g1.insert_edge('A', 'B', 3);
		g1.insert_edge('C', 'B', 2);
		g1.insert_edge('D', 'B', 4);
	}
	using graph = gdwg::graph<char, int>;
	auto const v = std::vector<graph::value_type>{{'A', 'A', 3}, {'C', 'A', 2}, {'D', 'A', 4}};

	auto g2 = graph{};
	for (const auto& [from, to, weight] : v) {
		g2.insert_node(from);
		g2.insert_node(to);
		g2.insert_edge(from, to, weight);
	}

	g1.merge_replace_node('B', 'A');

	CHECK(g1 == g2);
	CHECK_THROWS_MATCHES(g1.merge_replace_node('Z', 'D'),
	                     std::runtime_error,
	                     Catch::Matchers::Message("Cannot call gdwg::graph<N, "
	                                              "E>::merge_replace_node on old or new data if "
	                                              "they don't exist in the graph"));
	CHECK_THROWS_MATCHES(g1.merge_replace_node('A', 'Z'),
	                     std::runtime_error,
	                     Catch::Matchers::Message("Cannot call gdwg::graph<N, "
	                                              "E>::merge_replace_node on old or new data if "
	                                              "they don't exist in the graph"));
}

TEST_CASE("merge_replace_node2") {
	using graph = gdwg::graph<char, int>;
	auto const v = std::vector<graph::value_type>{{'A', 'B', 1},
	                                              {'A', 'C', 2},
	                                              {'A', 'D', 3},
	                                              {'B', 'B', 1},
	                                              {'B', 'B', 2},
	                                              {'B', 'B', 3}};

	auto g1 = graph{};
	for (const auto& [from, to, weight] : v) {
		g1.insert_node(from);
		g1.insert_node(to);
		g1.insert_edge(from, to, weight);
	}
	g1.merge_replace_node('A', 'B');
	CHECK(g1.is_node('A') == false);
	CHECK(g1.weights('B', 'B') == std::vector<int>{1, 2, 3});
}

/*Erase B, result
A->C, 2
A->D, 3
*/
TEST_CASE("erase_node") {
	using graph = gdwg::graph<char, int>;
	auto const v1 = std::vector<graph::value_type>{{'A', 'B', 1},
	                                               {'A', 'C', 2},
	                                               {'A', 'D', 3},
	                                               {'B', 'B', 1},
	                                               {'B', 'B', 2},
	                                               {'B', 'B', 3}};

	auto g1 = graph{};
	for (const auto& [from, to, weight] : v1) {
		g1.insert_node(from);
		g1.insert_node(to);
		g1.insert_edge(from, to, weight);
	}
	CHECK(g1.weights('B', 'B') == std::vector<int>{1, 2, 3});
	g1.erase_node('B');
	CHECK(g1.is_node('B') == false);
	CHECK_THROWS_MATCHES(g1.weights('B', 'B'),
	                     std::runtime_error,
	                     Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::weights if src or "
	                                              "dst node don't exist in the graph"));
}

/*B->B, 1 is no longer in graph after erasing*/
TEST_CASE("erase_edge(src, dist, weight)") {
	using graph = gdwg::graph<char, int>;
	auto const v1 = std::vector<graph::value_type>{{'A', 'B', 1},
	                                               {'A', 'C', 2},
	                                               {'A', 'D', 3},
	                                               {'B', 'B', 1},
	                                               {'B', 'B', 2},
	                                               {'B', 'B', 3}};

	auto g1 = graph{};
	for (const auto& [from, to, weight] : v1) {
		g1.insert_node(from);
		g1.insert_node(to);
		g1.insert_edge(from, to, weight);
	}
	CHECK(g1.erase_edge('B', 'B', 1) == true);
	CHECK_THROWS_MATCHES(g1.erase_edge('Z', 'B', 1),
	                     std::runtime_error,
	                     Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::erase_edge on src "
	                                              "or dst if they don't exist in the graph"));
	CHECK(g1.find('B', 'B', 1) == g1.end());
}

TEST_CASE("erase_edge(iter)") {
	using graph = gdwg::graph<char, int>;
	auto const v1 =
	   std::vector<graph::value_type>{{'A', 'B', 1}, {'A', 'C', 2}, {'A', 'D', 3}, {'B', 'B', 1}};

	auto g1 = graph{};
	for (const auto& [from, to, weight] : v1) {
		g1.insert_node(from);
		g1.insert_node(to);
		g1.insert_edge(from, to, weight);
	}
	auto it = g1.erase_edge(g1.begin());
	it = g1.erase_edge(it);
	it = g1.erase_edge(it);
	it = g1.erase_edge(it);
	CHECK(it == g1.end());
}

TEST_CASE("erase_edge(iter, iter)") {
	using graph = gdwg::graph<char, int>;
	auto const v1 =
	   std::vector<graph::value_type>{{'A', 'B', 1}, {'A', 'C', 2}, {'A', 'D', 3}, {'B', 'B', 1}};

	auto g1 = graph{};
	for (const auto& [from, to, weight] : v1) {
		g1.insert_node(from);
		g1.insert_node(to);
		g1.insert_edge(from, to, weight);
	}
	auto it = g1.erase_edge(g1.begin(), g1.end());
	CHECK(it == g1.end());
}

TEST_CASE("clear") {
	auto g = gdwg::graph<int, int>{};
	g.insert_node(1);
	g.insert_node(7);
	g.insert_node(12);
	g.insert_node(14);
	g.insert_node(19);
	g.insert_node(21);
	g.insert_edge(1, 7, 4);
	g.insert_edge(1, 7, 3);
	g.insert_edge(1, 7, 12);
	g.insert_edge(1, 12, 3);
	g.clear();
	CHECK(g.empty() == true);
	CHECK(g.nodes().empty() == true);
}