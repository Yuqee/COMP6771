#include "gdwg/graph.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <vector>

TEST_CASE("empty constructor test") {
    auto g = gdwg::graph<int, std::string>();
    CHECK(g.empty());

    CHECK(g.insert_node(23));
    CHECK(g.insert_node(31));

    CHECK(g.insert_edge(23, 31, "wubu"));

    CHECK(g.empty() == false);
    CHECK(g.is_node(23));
    CHECK(g.is_node(31));
    CHECK(g.is_connected(23, 31));
}

TEST_CASE("initializer list constructor test") {
    auto g = gdwg::graph<int, std::string>{23, 31};

    CHECK(g.empty() == false);
    CHECK(g.is_node(23));
    CHECK(g.is_node(31));
    CHECK(g.is_node(99) == false);
}

TEST_CASE("iterator constructor test") {
    auto v = std::vector<int>{23, 31};
    auto g = gdwg::graph<int, std::string>(v.begin(), v.end());

    CHECK(g.empty() == false);
    CHECK(g.is_node(23));
    CHECK(g.is_node(31));
    CHECK(g.is_node(99) == false);
}

TEST_CASE("move constructor test") {
    auto g1 = gdwg::graph<int, std::string>{23, 31};
    auto g2 = gdwg::graph(std::move(g1));

    CHECK(g1.empty());
    CHECK(g2.empty() == false);
    CHECK(g2.is_node(23));
    CHECK(g2.is_node(31));
    CHECK(g2.is_node(99) == false);
}

TEST_CASE("move assignment test") {
    auto g1 = gdwg::graph<int, std::string>{23, 31};
    auto g2 = gdwg::graph<int, std::string>();
    g2 = std::move(g1);

    CHECK(g1.empty());
    CHECK(g2.empty() == false);
    CHECK(g2.is_node(23));
    CHECK(g2.is_node(31));
    CHECK(g2.is_node(99) == false);
}

TEST_CASE("copy constructor test") {
    auto g1 = gdwg::graph<int, std::string>{23, 31};

    g1.insert_edge(23, 31, "wubu");

    auto g2 = gdwg::graph(g1);

    CHECK(g1 == g2);

    CHECK(g1.empty() == false);
    CHECK(g2.empty() == false);
    CHECK(g1.is_node(23));
    CHECK(g1.is_node(31));
    CHECK(g2.is_node(23));
    CHECK(g2.is_node(31));

    CHECK(g1.is_connected(23, 31));
    CHECK(g2.is_connected(23, 31));

    CHECK(g1.is_node(99) == false);
    CHECK(g1.is_node(99) == false);
}

TEST_CASE("copy assignment test") {
    auto g1 = gdwg::graph<int, std::string>{23, 31};
    auto g2 = gdwg::graph<int, std::string>();
    g2 = g1;

    CHECK(g1 == g2);

    CHECK(g1.empty() == false);
    CHECK(g2.empty() == false);
    CHECK(g1.is_node(23));
    CHECK(g1.is_node(31));
    CHECK(g2.is_node(23));
    CHECK(g2.is_node(31));

    CHECK(g1.is_node(99) == false);
    CHECK(g1.is_node(99) == false);
}

// TODO
TEST_CASE("insert_edge test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};
    CHECK(g1.insert_edge(31, 23, 7));
    CHECK(g1.insert_edge(31, 31, 7));

    CHECK(!g1.insert_edge(31, 31, 7));
    CHECK_THROWS(g1.insert_edge(31, 99, 7));
    CHECK_THROWS(g1.insert_edge(99, 23, 7));
}

TEST_CASE("insert_node test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    CHECK(!g1.insert_node(31));
    CHECK(!g1.insert_node(23));
    CHECK(!g1.insert_node(71));

    CHECK(g1.insert_node(89));
    CHECK(g1.insert_node(76));
}

TEST_CASE("clear test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    g1.insert_edge(31, 23, 7);
    g1.insert_edge(23, 31, 6);
    g1.insert_edge(23, 31, 5);
    g1.insert_edge(31, 23, 8);

    g1.clear();
    CHECK(g1.empty());
}

TEST_CASE("erase node test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    g1.insert_edge(31, 23, 7);
    g1.insert_edge(23, 31, 6);
    g1.insert_edge(23, 31, 5);
    g1.insert_edge(31, 23, 8);

    CHECK(g1.erase_node(23));
    CHECK(!g1.erase_node(283));

    CHECK(g1.nodes() == std::vector<int>{31, 71});
    CHECK(g1.connections(31).empty());
    CHECK(g1.connections(71).empty());
}

TEST_CASE("erase_edge test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    g1.insert_edge(31, 23, 7);
    g1.insert_edge(23, 31, 6);
    g1.insert_edge(23, 31, 5);
    g1.insert_edge(31, 23, 8);

    CHECK(g1.erase_edge(31, 23, 8));
    CHECK(!g1.erase_edge(31, 23, 889));
}

TEST_CASE("erase_edge iterator test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    g1.insert_edge(31, 23, 7);
    g1.insert_edge(23, 31, 6);
    g1.insert_edge(23, 31, 5);
    g1.insert_edge(31, 23, 8);

    auto res = g1.erase_edge(g1.begin());
    CHECK((*res).from == 23);
    CHECK((*res).to == 31);
    CHECK((*res).weight == 6);

    res = g1.erase_edge(res);
    CHECK((*res).from == 31);
    CHECK((*res).to == 23);
    CHECK((*res).weight == 7);

    CHECK(g1.connections(23).empty());

    res = g1.erase_edge(res);
    CHECK((*res).from == 31);
    CHECK((*res).to == 23);
    CHECK((*res).weight == 8);

    CHECK(g1.weights(31, 23) == std::vector<int>{8});

    res = g1.erase_edge(res);
    CHECK(res == g1.end());
}

TEST_CASE("erase_edge two iterator test") {
    SECTION("erase edge use begin and end") {
        auto g1 = gdwg::graph<int, int>{23, 31, 71};

        g1.insert_edge(31, 23, 7);
        g1.insert_edge(23, 31, 6);
        g1.insert_edge(23, 31, 5);
        g1.insert_edge(31, 23, 8);

        auto res = g1.erase_edge(g1.begin(), g1.end());
        CHECK(res == g1.end());

        CHECK(g1.connections(23).empty());
        CHECK(g1.connections(31).empty());
    }

    SECTION("erase edge use begin and ++") {
        auto g2 = gdwg::graph<int, int>{23, 31, 71};
        g2.insert_edge(31, 23, 7);
        g2.insert_edge(23, 31, 6);
        g2.insert_edge(23, 31, 5);
        g2.insert_edge(31, 23, 8);

        auto it = g2.begin();
        it++;
        it++;

        g2.erase_edge(g2.begin(), it);

        CHECK(g2.connections(23).empty());
        CHECK(g2.weights(31, 23) == std::vector<int>{7, 8});
    }
}

TEST_CASE("replace_node test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    g1.insert_edge(31, 23, 7);
    g1.insert_edge(23, 31, 6);
    g1.insert_edge(23, 31, 5);
    g1.insert_edge(31, 23, 8);
    g1.insert_edge(23, 23, 9);

    CHECK_THROWS(g1.replace_node(99, 99));

    CHECK(g1.replace_node(23, 99));

    CHECK(g1.weights(99, 31) == std::vector<int>{5, 6});
    CHECK(g1.weights(31, 99) == std::vector<int>{7, 8});
    CHECK(g1.weights(99, 99) == std::vector<int>{9});
}

TEST_CASE("merge_replace_node test") {
    SECTION("merge_replace_node without reflexive edge") {
        auto g1 = gdwg::graph<int, int>{23, 31, 71};

        g1.insert_edge(31, 23, 7);
        g1.insert_edge(23, 31, 6);
        g1.insert_edge(23, 31, 5);
        g1.insert_edge(31, 23, 8);

        CHECK_THROWS(g1.merge_replace_node(31, 99));
        CHECK_THROWS(g1.merge_replace_node(99, 23));

        g1.merge_replace_node(23, 31);

        CHECK(g1.weights(31, 31) == std::vector<int>{5, 6, 7, 8});

        g1.merge_replace_node(31, 71);

        CHECK(g1.weights(71, 71) == std::vector<int>{5, 6, 7, 8});
    }

    SECTION("merge_replace_node with reflexive edge") {
        auto g2 = gdwg::graph<int, int>{23, 31, 71};
        g2.insert_edge(23, 23, 7);
        g2.insert_edge(31, 31, 7);

        g2.merge_replace_node(23, 31);

        CHECK(g2.weights(31, 31) == std::vector<int>{7});
    }

    SECTION("merge_replace_node with string and int") {
        auto g3 = gdwg::graph<std::string, int>{"a", "b", "c", "d"};
        g3.insert_edge("a", "b", 1);
        g3.insert_edge("a", "c", 2);
        g3.insert_edge("a", "d", 3);
        g3.insert_edge("b", "b", 1);

        g3.merge_replace_node("a", "b");

        CHECK(g3.weights("b", "b") == std::vector<int>{1});
        CHECK(g3.weights("b", "c") == std::vector<int>{2});
        CHECK(g3.weights("b", "d") == std::vector<int>{3});
    }
}

TEST_CASE("is_node test") {
    auto g = gdwg::graph<int, std::string>{46, 47, 48, 0};

    CHECK(g.is_node(46));
    CHECK(!g.is_node(465));
}

TEST_CASE("empty test") {
    auto g = gdwg::graph<int, std::string>();
    auto g1 = gdwg::graph<int, std::string>{46, 47, 48, 0};

    CHECK(g.empty());
    CHECK(!g1.empty());
}

TEST_CASE("is_connected test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    g1.insert_edge(31, 23, 7);
    g1.insert_edge(23, 31, 6);
    g1.insert_edge(23, 31, 5);
    g1.insert_edge(31, 23, 8);

    CHECK(g1.is_connected(23, 31));
    CHECK(!g1.is_connected(23, 23));

    CHECK_THROWS(g1.is_connected(46546, 31));
    CHECK_THROWS(g1.is_connected(23, 846465));
}

TEST_CASE("nodes function test") {
    SECTION("nodes function test use list constructor and compare to vector") {
        auto v = std::vector<int>{0, 46, 47, 48};
        auto g = gdwg::graph<int, std::string>{46, 47, 48, 0};
        CHECK(v == g.nodes());
        CHECK(g.nodes() == g.nodes());
    }

    SECTION("nodes function test use vector constructor and compare to that vector") {
        auto v1 = std::vector<int>{0, 46, 47, 48, 78798};
        auto g1 = gdwg::graph<int, std::string>(v1.begin(), v1.end());
        CHECK(g1.nodes() == v1);
    }
}

TEST_CASE("weights function test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    g1.insert_edge(31, 23, 7);
    g1.insert_edge(23, 31, 6);
    g1.insert_edge(23, 31, 5);
    g1.insert_edge(31, 23, 8);

    g1.insert_edge(31, 31, 9);
    g1.insert_edge(31, 31, 10);

    CHECK(g1.weights(23, 31) == std::vector<int>{5, 6});
    CHECK(g1.weights(31, 23) == std::vector<int>{7, 8});
    CHECK(g1.weights(31, 31) == std::vector<int>{9, 10});
}

TEST_CASE("find function test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    g1.insert_edge(31, 23, 7);
    g1.insert_edge(23, 31, 6);
    g1.insert_edge(23, 31, 5);
    g1.insert_edge(31, 23, 8);

    CHECK(g1.find(23, 31, 5) == g1.begin());
    CHECK(g1.find(99, 99, 99) == g1.end());
}

TEST_CASE("connections function test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    g1.insert_edge(31, 23, 7);
    g1.insert_edge(23, 31, 6);
    g1.insert_edge(23, 31, 5);
    g1.insert_edge(31, 23, 8);

    g1.insert_edge(31, 31, 9);
    g1.insert_edge(31, 31, 10);

    CHECK(g1.connections(31) == std::vector<int>{23, 31});
    CHECK(g1.connections(23) == std::vector<int>{31});

    CHECK_THROWS(g1.connections(99));
}

TEST_CASE("iterator constructor test1") {
    SECTION("iterator constructor with list constructor") {
        auto g1 = gdwg::graph<int, int>{23, 31, 71};

        g1.insert_edge(23, 31, 6);
        g1.insert_edge(23, 31, 5);
        g1.insert_edge(31, 23, 7);
        g1.insert_edge(31, 23, 8);

        auto a = g1.begin();
        a = g1.end();
    }

    SECTION("iterator constructor with default graph Constructors ") {
        auto g2 = gdwg::graph<int, int>();
        auto a = g2.begin();
        a = g2.end();
    }
}

TEST_CASE("iterator increment test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    g1.insert_edge(31, 23, 7);
    g1.insert_edge(23, 31, 6);
    g1.insert_edge(23, 31, 5);
    g1.insert_edge(31, 23, 8);
    g1.insert_edge(31, 31, 9);

    int count = 0;
    for (auto i = g1.begin(); i != g1.end(); i++) {
        switch (count) {
        case 0:
            CHECK((*i).from == 23);
            CHECK((*i).to == 31);
            CHECK((*i).weight == 5);
            break;
        case 1:
            CHECK((*i).from == 23);
            CHECK((*i).to == 31);
            CHECK((*i).weight == 6);
            break;
        case 2:
            CHECK((*i).from == 31);
            CHECK((*i).to == 23);
            CHECK((*i).weight == 7);
            break;
        case 3:
            CHECK((*i).from == 31);
            CHECK((*i).to == 23);
            CHECK((*i).weight == 8);
            break;
        case 4:
            CHECK((*i).from == 31);
            CHECK((*i).to == 31);
            CHECK((*i).weight == 9);
            break;
        }
        count++;
    }

    CHECK(count == 5);
}

TEST_CASE("iterator decrement test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    g1.insert_edge(31, 23, 7);
    g1.insert_edge(23, 31, 6);
    g1.insert_edge(23, 31, 5);
    g1.insert_edge(31, 23, 8);

    int count = 0;
    for (auto i = g1.end(); i != g1.begin();) {
        --i;
        switch (count) {
        case 0:
            CHECK((*i).from == 31);
            CHECK((*i).to == 23);
            CHECK((*i).weight == 8);
            break;
        case 1:
            CHECK((*i).from == 31);
            CHECK((*i).to == 23);
            CHECK((*i).weight == 7);
            break;
        case 2:
            CHECK((*i).from == 23);
            CHECK((*i).to == 31);
            CHECK((*i).weight == 6);
            break;
        case 3:
            CHECK((*i).from == 23);
            CHECK((*i).to == 31);
            CHECK((*i).weight == 5);
            break;
        }
        count++;
    }

    CHECK(count == 4);
}

TEST_CASE("iterator general test") {
    auto g1 = gdwg::graph<int, int>{23, 31, 71};

    g1.insert_edge(31, 23, 7);
    g1.insert_edge(23, 31, 6);
    g1.insert_edge(23, 31, 5);
    g1.insert_edge(31, 23, 8);

    int count = 0;
    for (auto i = g1.end(); i != g1.begin();) {
        --i;
        switch (count) {
        case 0:
            CHECK((*i).from == 31);
            CHECK((*i).to == 23);
            CHECK((*i).weight == 8);
            break;
        case 1:
            CHECK((*i).from == 31);
            CHECK((*i).to == 23);
            CHECK((*i).weight == 7);
            break;
        case 2:
            CHECK((*i).from == 23);
            CHECK((*i).to == 31);
            CHECK((*i).weight == 6);
            break;
        case 3:
            CHECK((*i).from == 23);
            CHECK((*i).to == 31);
            CHECK((*i).weight == 5);
            break;
        }
        count++;
    }

    CHECK(count == 4);
    count = 0;
    for (auto i = g1.begin(); i != g1.end(); i++) {
        switch (count) {
        case 0:
            CHECK((*i).from == 23);
            CHECK((*i).to == 31);
            CHECK((*i).weight == 5);
            break;
        case 1:
            CHECK((*i).from == 23);
            CHECK((*i).to == 31);
            CHECK((*i).weight == 6);
            break;
        case 2:
            CHECK((*i).from == 31);
            CHECK((*i).to == 23);
            CHECK((*i).weight == 7);
            break;
        case 3:
            CHECK((*i).from == 31);
            CHECK((*i).to == 23);
            CHECK((*i).weight == 8);
            break;
        }
        count++;
    }

    CHECK(count == 4);
}

TEST_CASE("iterator equal test") {
    auto g1 = gdwg::graph<int, std::string>{23, 31};
    auto g2 = gdwg::graph<int, std::string>();

    CHECK(g1.begin() == g1.begin());
    CHECK(g1.begin() == g1.end());

    CHECK(g2.begin() == g2.end());
}

TEST_CASE("Extractor  test") {
    using graph = gdwg::graph<int, double>;
    auto const v = std::vector<graph::value_type>{
       {1, 1, 1.2},
       {1, 1, 2.3},
       {1, 1, 3.4},
       {1, 2, 5.6},
       {2, 1, 5.6},
       {2, 2, 8.888},
       {2, 3, -5.0},
       {2, 7, -9787},
    };

    auto g = graph{};
    for (const auto& [from, to, weight] : v) {
        g.insert_node(from);
        g.insert_node(to);
        g.insert_edge(from, to, weight);
    }

    auto out = std::ostringstream{};
    out << g;
    auto const expected_output = std::string_view(R"(1 (
  1 | 1.2
  1 | 2.3
  1 | 3.4
  2 | 5.6
)
2 (
  1 | 5.6
  2 | 8.888
  3 | -5
  7 | -9787
)
3 (
)
7 (
)
)");
    CHECK(out.str() == expected_output);
}

TEST_CASE("Comparisons  test") {
    auto g1 = gdwg::graph<int, std::string>{};
    auto g2 = gdwg::graph<int, std::string>{46, 47, 48, 0};
    auto g3 = gdwg::graph<int, std::string>{46, 47, 48, 0};

    CHECK(g1 == g1);
    CHECK(g2 == g2);
    CHECK(g3 == g3);

    CHECK(g2 == g3);

    g2.insert_edge(46, 0, "wubu");
    CHECK(g2 != g3);

    g3.insert_edge(46, 0, "wubu");
    CHECK(g2 == g3);
}