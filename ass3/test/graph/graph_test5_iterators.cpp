#include "gdwg/graph.hpp"

#include <algorithm>
#include <catch2/catch.hpp>

/*This file tests the iterator class in gdwg. Mostly done by check
if some value inside gdwg is euqal to the expected value or the
modified object behave as they expected to be.*/

/*pointing to the first element of gdwg*/
TEST_CASE("begin()") {
	auto g = gdwg::graph<double, std::string>{1, 2, 3, 4};
	g.insert_edge(1, 1, "winner");
	g.insert_edge(1, 2, "2nd place");
	auto const it = g.begin();
	auto const val = *it;
	CHECK(val.from == 1);
	CHECK(val.to == 1);
	CHECK(val.weight == "winner");
}

/*pointing to one step after the last element of gdwg, and
test [begin(), end()) is iterable*/
TEST_CASE("end()") {
	auto g = gdwg::graph<double, std::string>{1, 2, 3, 4};
	g.insert_edge(1, 1, "winner");
	g.insert_edge(1, 2, "2nd place");
	auto const it = --g.end();
	auto const val = *it;
	CHECK(val.from == 1);
	CHECK(val.to == 2);
	CHECK(val.weight == "2nd place");
	CHECK(std::all_of(g.begin(), g.end(), [](auto const& it) { return it.from == 1; }));
}

TEST_CASE("opertor*") {
	auto g = gdwg::graph<double, std::string>{1, 2, 3, 4};
	g.insert_edge(1, 1, "winner");
	g.insert_edge(1, 2, "2nd place");
	g.insert_edge(1, 3, "3nd place");
	g.insert_edge(1, 4, "loser");
	auto const dists = g.connections(1);
	auto iter = g.begin();
	CHECK(std::all_of(dists.begin(), dists.end(), [&iter](auto const& dist) {
		auto const val = *iter;
		++iter;
		return val.from == 1 && val.to == dist;
	}));
}

TEST_CASE("opertor++1") {
	using graph = gdwg::graph<int, int>;
	auto const v = std::vector<graph::value_type>{{1, 7, 4},
	                                              {1, 12, 3},
	                                              {1, 21, 13},
	                                              {7, 21, 13},
	                                              {12, 19, 16},
	                                              {14, 14, 0},
	                                              {19, 1, 3},
	                                              {19, 21, 2},
	                                              {21, 14, 23},
	                                              {21, 31, 14}};

	auto g = gdwg::graph<int, int>{1, 7, 12, 14, 19, 21, 31, 67};
	g.insert_edge(1, 7, 4);
	g.insert_edge(1, 12, 3);
	g.insert_edge(1, 21, 13);
	g.insert_edge(7, 21, 13);
	g.insert_edge(12, 19, 16);
	g.insert_edge(14, 14, 0);
	g.insert_edge(19, 1, 3);
	g.insert_edge(19, 21, 2);
	g.insert_edge(21, 14, 23);
	g.insert_edge(21, 31, 14);
	auto iter2 = v.begin();
	for (auto iter1 = g.begin(); iter1 != g.end(); ++iter1) {
		CHECK((*iter1).from == iter2->from);
		CHECK((*iter1).to == iter2->to);
		CHECK((*iter1).weight == iter2->weight);
		++iter2;
	}
}

TEST_CASE("opertor++2") {
	using graph = gdwg::graph<int, int>;
	auto const v = std::vector<graph::value_type>{{1, 7, 4},
	                                              {1, 12, 3},
	                                              {1, 21, 13},
	                                              {7, 21, 13},
	                                              {12, 19, 16},
	                                              {14, 14, 0},
	                                              {19, 1, 3},
	                                              {19, 21, 2},
	                                              {21, 14, 23},
	                                              {21, 31, 14}};

	auto g = gdwg::graph<int, int>{1, 7, 12, 14, 19, 21, 31, 67};
	g.insert_edge(1, 7, 4);
	g.insert_edge(1, 12, 3);
	g.insert_edge(1, 21, 13);
	g.insert_edge(7, 21, 13);
	g.insert_edge(12, 19, 16);
	g.insert_edge(14, 14, 0);
	g.insert_edge(19, 1, 3);
	g.insert_edge(19, 21, 2);
	g.insert_edge(21, 14, 23);
	g.insert_edge(21, 31, 14);
	auto iter2 = v.begin();
	for (auto iter1 = g.begin(); iter1 != g.end(); iter1++) {
		CHECK((*iter1).from == iter2->from);
		CHECK((*iter1).to == iter2->to);
		CHECK((*iter1).weight == iter2->weight);
		iter2++;
	}
}

TEST_CASE("opertor--1") {
	using graph = gdwg::graph<int, int>;
	auto const v = std::vector<graph::value_type>{{1, 7, 4},
	                                              {1, 12, 3},
	                                              {1, 21, 13},
	                                              {7, 21, 13},
	                                              {12, 19, 16},
	                                              {14, 14, 0},
	                                              {19, 1, 3},
	                                              {19, 21, 2},
	                                              {21, 14, 23},
	                                              {21, 31, 14}};

	auto g = gdwg::graph<int, int>{1, 7, 12, 14, 19, 21, 31, 67};
	g.insert_edge(1, 7, 4);
	g.insert_edge(1, 12, 3);
	g.insert_edge(1, 21, 13);
	g.insert_edge(7, 21, 13);
	g.insert_edge(12, 19, 16);
	g.insert_edge(14, 14, 0);
	g.insert_edge(19, 1, 3);
	g.insert_edge(19, 21, 2);
	g.insert_edge(21, 14, 23);
	g.insert_edge(21, 31, 14);
	auto iter2 = --v.end();
	for (auto iter1 = --g.end(); iter1 != g.begin(); --iter1) {
		CHECK((*iter1).from == iter2->from);
		CHECK((*iter1).to == iter2->to);
		CHECK((*iter1).weight == iter2->weight);
		--iter2;
	}
}

TEST_CASE("opertor--2") {
	using graph = gdwg::graph<int, int>;
	auto const v = std::vector<graph::value_type>{{1, 7, 4},
	                                              {1, 12, 3},
	                                              {1, 21, 13},
	                                              {7, 21, 13},
	                                              {12, 19, 16},
	                                              {14, 14, 0},
	                                              {19, 1, 3},
	                                              {19, 21, 2},
	                                              {21, 14, 23},
	                                              {21, 31, 14}};

	auto g = gdwg::graph<int, int>{1, 7, 12, 14, 19, 21, 31, 67};
	g.insert_edge(1, 7, 4);
	g.insert_edge(1, 12, 3);
	g.insert_edge(1, 21, 13);
	g.insert_edge(7, 21, 13);
	g.insert_edge(12, 19, 16);
	g.insert_edge(14, 14, 0);
	g.insert_edge(19, 1, 3);
	g.insert_edge(19, 21, 2);
	g.insert_edge(21, 14, 23);
	g.insert_edge(21, 31, 14);
	auto iter2 = --v.end();
	for (auto iter1 = --g.end(); iter1 != g.begin(); iter1--) {
		CHECK((*iter1).from == iter2->from);
		CHECK((*iter1).to == iter2->to);
		CHECK((*iter1).weight == iter2->weight);
		iter2--;
	}
}

TEST_CASE("iter1 == iter2") {
	auto g = gdwg::graph<int, int>{1, 7, 12, 14, 19, 21, 31, 67};
	g.insert_edge(1, 7, 4);
	g.insert_edge(1, 12, 3);
	g.insert_edge(1, 21, 13);
	auto const g2 = g;
	CHECK(g.begin() != g2.begin());
	CHECK(g.begin() == g.find(1, 7, 4));
	g.erase_edge(g.find(1, 7, 4));
	CHECK(g.begin() == g.find(1, 12, 3));
	g.erase_edge(g.find(1, 12, 3));
	CHECK(g.begin() == g.find(1, 21, 13));
	g.erase_edge(g.find(1, 21, 13));
	CHECK(g.begin() == g.end());
}