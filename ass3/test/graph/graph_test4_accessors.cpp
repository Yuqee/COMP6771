#include "gdwg/graph.hpp"

#include <algorithm>
#include <catch2/catch.hpp>
#include <stdexcept>
#include <vector>

/*This file tests the accessors of gdwg. Mostly done by check
if some value inside gdwg is euqal to the expected value or certain
object equal to expected ones.*/

/*Apply std::algorithm if each node is there*/
TEST_CASE("is_node") {
	auto const vec1 = std::vector<std::string>{"writing", "test", "is", "the", "last", "part"};
	auto const g = gdwg::graph<std::string, char>(vec1.begin(), vec1.end());
	CHECK(std::all_of(vec1.begin(), vec1.end(), [&g](auto const& v) { return g.is_node(v); }));
	auto const vec2 = std::vector<std::string>{"this", "break", "will", "be", "fun"};
	CHECK(std::none_of(vec2.begin(), vec2.end(), [&g](auto const& v) { return g.is_node(v); }));
}

TEST_CASE("empty") {
	auto g = gdwg::graph<std::string, char>{};
	CHECK(g.empty());
	auto const vec1 = std::vector<std::string>{"writing", "test", "is", "the", "last", "part"};
	g = gdwg::graph<std::string, char>(vec1.begin(), vec1.end());
	CHECK(!g.empty());
	g.clear();
	CHECK(g.empty());
}

TEST_CASE("is_connected1") {
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
	CHECK(g1.is_connected('B', 'B'));
	CHECK(g1.is_connected('C', 'B') == false);
	CHECK(g1.is_connected('A', 'B'));
	CHECK(g1.is_connected('A', 'C'));
	CHECK(g1.is_connected('A', 'D'));
}

/*Test exceptions*/
TEST_CASE("is_connected2") {
	using graph = gdwg::graph<char, int>;
	auto const v1 =
	   std::vector<graph::value_type>{{'A', 'B', 1}, {'A', 'C', 2}, {'A', 'D', 3}, {'B', 'B', 1}};

	auto g1 = graph{};
	for (const auto& [from, to, weight] : v1) {
		g1.insert_node(from);
		g1.insert_node(to);
		g1.insert_edge(from, to, weight);
	}

	CHECK_THROWS_MATCHES(g1.is_connected('A', 'Z'),
	                     std::runtime_error,
	                     Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::is_connected if "
	                                              "src or dst node don't exist in the graph"));
	CHECK_THROWS_MATCHES(g1.is_connected('Z', 'Z'),
	                     std::runtime_error,
	                     Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::is_connected if "
	                                              "src or dst node don't exist in the graph"));
}

TEST_CASE("nodes") {
	auto vec1 = std::vector<std::string>{"writing", "test", "is", "the", "last", "part"};
	auto const g = gdwg::graph<std::string, char>(vec1.begin(), vec1.end());
	CHECK(vec1 != g.nodes());
	std::sort(vec1.begin(), vec1.end());
	CHECK(vec1 == g.nodes());
	auto const vec = g.nodes();
	CHECK(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("weights") {
	auto const vec1 = std::vector<gdwg::graph<char, int>::value_type>{{'A', 'B', 1},
	                                                                  {'A', 'C', 2},
	                                                                  {'A', 'D', 3},
	                                                                  {'B', 'B', 1},
	                                                                  {'B', 'B', 2},
	                                                                  {'B', 'B', 3}};

	auto g1 = gdwg::graph<char, int>{};
	for (const auto& [from, to, weight] : vec1) {
		g1.insert_node(from);
		g1.insert_node(to);
		g1.insert_edge(from, to, weight);
	}
	auto weights_vec = std::vector<int>{1, 2, 3};
	CHECK(g1.weights('B', 'B') == weights_vec);
	g1.insert_edge('B', 'B', 0);
	weights_vec.emplace(weights_vec.end(), 0);
	std::sort(weights_vec.begin(), weights_vec.end());
	CHECK(g1.weights('B', 'B') == weights_vec);
	g1.erase_node('B');
	CHECK_THROWS_MATCHES(g1.weights('B', 'B'),
	                     std::runtime_error,
	                     Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::weights if src or "
	                                              "dst node don't exist in the graph"));
}

TEST_CASE("find") {
	auto target = gdwg::graph<double, double>::value_type{1, 2, 1.314};
	auto g = gdwg::graph<double, double>{};
	g.insert_node(1);
	g.insert_node(2);
	g.insert_edge(1, 2, 1.314);
	auto const it = g.find(target.from, target.to, target.weight);
	CHECK(it != g.end());
	CHECK((*it).from == target.from);
	CHECK((*it).to == target.to);
	CHECK((*it).weight == target.weight);
	target = gdwg::graph<double, double>::value_type{1, 2, 1};
	CHECK(g.find(target.from, target.to, target.weight) == g.end());
}

TEST_CASE("connections1") {
	auto g = gdwg::graph<double, double>{};
	g.insert_node(7);
	g.insert_node(8);
	g.insert_node(1);
	g.insert_node(4);
	g.insert_edge(1, 7, 1.314);
	g.insert_edge(1, 4, 1.314);
	g.insert_edge(1, 8, 1.314);
	g.insert_edge(1, 7, 1.314);
	g.insert_edge(1, 4, 1.314);
	g.insert_edge(1, 8, 1.314);
	auto vec = std::vector<double>{7, 4, 8};
	std::sort(vec.begin(), vec.end());
	CHECK(g.connections(1) == vec);
	vec.erase(std::find(vec.begin(), vec.end(), 7));
	g.erase_edge(1, 7, 1.314);
	CHECK(g.connections(1) == vec);
	vec.pop_back();
	g.erase_edge(1, 8, 1.314);
	CHECK(g.connections(1) == vec);
	vec.pop_back();
	g.erase_edge(1, 4, 1.314);
	CHECK(g.connections(1) == vec);
	auto const nodes = g.nodes();
	CHECK(std::all_of(nodes.begin(), nodes.end(), [&g, &vec](auto const& n) {
		return g.connections(n) == vec;
	}));
}

/*test exceptions*/
TEST_CASE("connections2") {
	auto g = gdwg::graph<double, double>{};
	g.insert_node(7);
	g.insert_node(8);
	g.insert_node(1);
	g.insert_node(4);
	g.insert_edge(1, 7, 1.314);
	g.insert_edge(1, 4, 1.314);
	g.insert_edge(1, 8, 1.314);
	g.insert_edge(1, 7, 1.314);
	g.insert_edge(1, 4, 1.314);
	g.insert_edge(1, 8, 1.314);

	CHECK_THROWS_MATCHES(g.connections('B'),
	                     std::runtime_error,
	                     Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::connections if "
	                                              "src doesn't exist in the graph"));
	CHECK_THROWS_MATCHES(g.connections(12),
	                     std::runtime_error,
	                     Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::connections if "
	                                              "src doesn't exist in the graph"));
}