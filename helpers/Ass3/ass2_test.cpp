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