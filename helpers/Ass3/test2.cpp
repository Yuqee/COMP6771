#include "gdwg/graph.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

TEST_CASE("Constructor: Default") {
    auto g = gdwg::graph<int, std::string>{};

    CHECK(g.empty());
}

TEST_CASE("Constructor: Initializer list") {
    SECTION("int") {
        auto g = gdwg::graph<int, std::string>{1, 5, 0, -9, -4};

        CHECK(g.is_node(1));
        CHECK(g.is_node(5));
        CHECK(g.is_node(0));
        CHECK(g.is_node(-9));
        CHECK(g.is_node(-4));
    }

    SECTION("string") {
        auto g = gdwg::graph<std::string, std::string>{"one", "two", "three"};

        CHECK(g.is_node("one"));
        CHECK(g.is_node("two"));
        CHECK(g.is_node("three"));
    }

    SECTION("std::vector") {
        auto v1 = std::vector<int>{1, 3, 5, 7};
        auto v2 = std::vector<int>{-2, -4, -6, -8};
        auto v3 = std::vector<int>{1, 3, 5, 7};
        auto g = gdwg::graph<std::vector<int>, std::string>{v1, v2, v3};

        CHECK(g.is_node(std::vector<int>(v1)));
        CHECK(g.is_node(std::vector<int>(v2)));
        CHECK(g.is_node(std::vector<int>(v3)));
    }
}

TEST_CASE("Constructor: InputIt") {
    SECTION("int vector") {
        auto v = std::vector<int>{-2, -4, -6, -8};
        auto g = gdwg::graph<int, std::string>(v.begin(), v.end());

        CHECK(g.is_node(-2));
        CHECK(g.is_node(-4));
        CHECK(g.is_node(-6));
        CHECK(g.is_node(-8));
    }

    SECTION("string set") {
        auto s = std::set<std::string>{"Taeyeon", "Yoona", "Mina"};
        auto g = gdwg::graph<std::string, int>(s.begin(), s.end());

        CHECK(g.is_node("Taeyeon"));
        CHECK(g.is_node("Yoona"));
        CHECK(g.is_node("Mina"));
    }
}

TEST_CASE("Copy Constructor") {
    SECTION("Just nodes") {
        auto const g = gdwg::graph<std::string, int>{"Taeyeon", "Yoona", "Mina"};
        auto g_copy = g;

        // Check that both graph has the exactly same nodes
        CHECK(g.is_node("Taeyeon"));
        CHECK(g.is_node("Yoona"));
        CHECK(g.is_node("Mina"));

        CHECK(g_copy.is_node("Taeyeon"));
        CHECK(g_copy.is_node("Yoona"));
        CHECK(g_copy.is_node("Mina"));

        // Check that modifying one will not affect the other
        // Assumes the correctness of replace_node
        CHECK(g_copy.replace_node("Mina", "Nayeon"));

        CHECK(g.is_node("Mina"));
        CHECK(g_copy.is_node("Nayeon"));

        CHECK_FALSE(g.is_node("Nayeon"));
        CHECK_FALSE(g_copy.is_node("Mina"));
    }

    // Assumes insert_edge(), begin() works
    SECTION("Edges") {
        auto g = gdwg::graph<std::string, int>{"Taeyeon", "Yoona", "Mina"};
        g.insert_edge("Taeyeon", "Yoona", 1314);
        g.insert_edge("Taeyeon", "Yoona", 520);

        auto g_copy = g;

        // Check edges by iterator
        auto g_copy_it = g_copy.begin();
        CHECK((*g_copy_it).from == "Taeyeon");
        CHECK((*g_copy_it).to == "Yoona");
        CHECK((*g_copy_it).weight == 520);

        ++g_copy_it;
        CHECK((*g_copy_it).from == "Taeyeon");
        CHECK((*g_copy_it).to == "Yoona");
        CHECK((*g_copy_it).weight == 1314);
    }
}

TEST_CASE("Copy Assignment") {
    SECTION("Just nodes") {
        auto const g = gdwg::graph<std::string, int>{"Taeyeon", "Yoona", "Mina"};
        auto g_copy = gdwg::graph<std::string, int>{"How", "Are", "You"};

        CHECK(g.is_node("Taeyeon"));
        CHECK(g.is_node("Yoona"));
        CHECK(g.is_node("Mina"));

        CHECK(g_copy.is_node("How"));
        CHECK(g_copy.is_node("Are"));
        CHECK(g_copy.is_node("You"));

        // Perform the copy assignment
        g_copy = g;

        CHECK(g.is_node("Taeyeon"));
        CHECK(g.is_node("Yoona"));
        CHECK(g.is_node("Mina"));

        CHECK(g_copy.is_node("Taeyeon"));
        CHECK(g_copy.is_node("Yoona"));
        CHECK(g_copy.is_node("Mina"));

        // Modify one and check if the other is changes
        // Assumes the correctness of replace_node
        CHECK(g_copy.replace_node("Mina", "Nayeon"));

        CHECK(g.is_node("Mina"));
        CHECK(g_copy.is_node("Nayeon"));

        CHECK_FALSE(g.is_node("Nayeon"));
        CHECK_FALSE(g_copy.is_node("Mina"));
    }

    // Assumes insert_edge(), begin() works
    SECTION("Edges") {
        auto g = gdwg::graph<std::string, int>{"Taeyeon", "Yoona", "Mina"};
        g.insert_edge("Taeyeon", "Yoona", 1314);
        g.insert_edge("Taeyeon", "Yoona", 520);

        auto g_copy = gdwg::graph<std::string, int>();
        g_copy = g;

        // Check edges by iterator
        auto g_copy_it = g_copy.begin();
        CHECK((*g_copy_it).from == "Taeyeon");
        CHECK((*g_copy_it).to == "Yoona");
        CHECK((*g_copy_it).weight == 520);

        ++g_copy_it;
        CHECK((*g_copy_it).from == "Taeyeon");
        CHECK((*g_copy_it).to == "Yoona");
        CHECK((*g_copy_it).weight == 1314);
    }
}

// Move constructor: Iterator of other are not invalidated
TEST_CASE("Move Constructor") {
    SECTION("Just nodes") {
        auto moved_from = gdwg::graph<std::string, int>{"Taeyeon", "Yoona", "Mina"};

        SECTION("Check moved to contents && if the moved from is emtpy") {
            auto moved_to = gdwg::graph<std::string, int>(std::move(moved_from));

            // Check that both graph has the exactly same nodes
            CHECK(moved_to.is_node("Taeyeon"));
            CHECK(moved_to.is_node("Yoona"));
            CHECK(moved_to.is_node("Mina"));

            CHECK(moved_from.empty());
        }

        // Assumes insert_edge(), begin() works
        SECTION("Check that moved_from iterator works and edge is correctly moved") {
            moved_from.insert_edge("Taeyeon", "Yoona", 1314);
            auto moved_from_it = moved_from.begin();

            auto moved_to = gdwg::graph<std::string, int>(std::move(moved_from));
            CHECK((*moved_from_it).from == "Taeyeon");
            CHECK((*moved_from_it).to == "Yoona");
            CHECK((*moved_from_it).weight == 1314);
        }
    }
}

TEST_CASE("Move Assignment") {
    SECTION("Just nodes") {
        auto moved_from = gdwg::graph<std::string, int>{"Taeyeon", "Yoona", "Mina"};
        auto moved_to = gdwg::graph<std::string, int>();

        SECTION("Check moved to contents && if the moved from is emtpy") {
            moved_to = std::move(moved_from);

            // Check that both graph has the exactly same nodes
            CHECK(moved_to.is_node("Taeyeon"));
            CHECK(moved_to.is_node("Yoona"));
            CHECK(moved_to.is_node("Mina"));

            CHECK(moved_from.empty());
        }

        // Assumes insert_edge(), begin() works
        SECTION("Check that moved_from iterator works and edge is correctly moved") {
            moved_from.insert_edge("Taeyeon", "Yoona", 1314);
            auto moved_from_it = moved_from.begin();

            moved_to = std::move(moved_from);
            CHECK((*moved_from_it).from == "Taeyeon");
            CHECK((*moved_from_it).to == "Yoona");
            CHECK((*moved_from_it).weight == 1314);
        }
    }
}

TEST_CASE("Check if resources are owned") {
    SECTION("Test 1: Node") {
        auto g = gdwg::graph<std::string, int>();
        {
            auto s = std::string("Test");
            g.insert_node(s);
        }

        CHECK(g.is_node("Test"));
    }

    SECTION("Test 2: Node and Edge") {
        auto g = gdwg::graph<std::vector<int>, std::string>();
        {
            auto s = std::string("Test");
            auto v1 = std::vector<int>{1, 3, 5};
            auto v2 = std::vector<int>{2, 4, 6};

            g.insert_node(v1);
            g.insert_node(v2);
            g.insert_edge(v1, v2, s);
        }

        CHECK(g.is_node(std::vector<int>{1, 3, 5}));
        CHECK(g.is_node(std::vector<int>{2, 4, 6}));
        CHECK((*(g.begin())).weight == "Test");
    }
}

TEST_CASE("Insert node") {
    auto g = gdwg::graph<int, std::string>{1};
    CHECK(g.insert_node(7));
    CHECK(g.insert_node(-1));

    CHECK(g.is_node(1));
    CHECK(g.is_node(-1));
    CHECK(g.is_node(7));

    SECTION("Insert existing node") {
        CHECK_FALSE(g.insert_node(7));
        CHECK_FALSE(g.insert_node(1));
    }
}

TEST_CASE("Insert edge") {
    auto g = gdwg::graph<std::string, int>{"Yoona", "Taeyeon", "Tzuyu"};

    SECTION("Insert legal edges") {
        CHECK(g.insert_edge("Yoona", "Tzuyu", 530));
        CHECK(g.insert_edge("Yoona", "Yoona", 530)); // Reflexive edge

        CHECK(g.find("Yoona", "Tzuyu", 530) != g.end());
        CHECK(g.find("Yoona", "Yoona", 530) != g.end());

        // Edge with the same src and dst but different weight
        CHECK(g.insert_edge("Yoona", "Tzuyu", 1314));
        CHECK(g.insert_edge("Yoona", "Yoona", 1314)); // Reflexive edge

        CHECK(g.find("Yoona", "Tzuyu", 1314) != g.end());
        CHECK(g.find("Yoona", "Yoona", 1314) != g.end());
    }

    SECTION("Insert existing node") {
        CHECK(g.insert_edge("Yoona", "Tzuyu", 530));
        CHECK(g.insert_edge("Yoona", "Yoona", 530)); // Reflexive edge

        CHECK_FALSE(g.insert_edge("Yoona", "Tzuyu", 530));
        CHECK_FALSE(g.insert_edge("Yoona", "Yoona", 530)); // Reflexive edge
    }

    SECTION("Exception: Either src or dst not exist") {
        // dst not exist
        CHECK_THROWS_MATCHES(g.insert_edge("Yoona", "Mina", 1314),
                             std::runtime_error,
                             Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::insert_edge "
                                                      "when "
                                                      "either src or dst node does not exist"));

        // src not exist
        CHECK_THROWS_MATCHES(g.insert_edge("Nayeon", "Taeyeon", 520),
                             std::runtime_error,
                             Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::insert_edge "
                                                      "when "
                                                      "either src or dst node does not exist"));

        // both not exist
        CHECK_THROWS_MATCHES(g.insert_edge("Nayeon", "Mina", 520),
                             std::runtime_error,
                             Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::insert_edge "
                                                      "when "
                                                      "either src or dst node does not exist"));
    }
}

TEST_CASE("Replace Node") {
    auto g = gdwg::graph<std::string, int>{"Yoona", "Taeyeon", "Tzuyu"};

    SECTION("Simple case: If node are replaced") {
        CHECK(g.replace_node("Yoona", "Rose"));

        CHECK(g.is_node("Rose"));
        CHECK_FALSE(g.is_node("Yoona"));
    }

    SECTION("Hard case: If edges are also replaced") {
        CHECK(g.insert_edge("Yoona", "Taeyeon", 818));
        CHECK(g.insert_edge("Taeyeon", "Yoona", 1314));
        CHECK(g.insert_edge("Yoona", "Yoona", 530));
        CHECK(g.insert_edge("Yoona", "Yoona", 1314));

        CHECK(g.replace_node("Yoona", "Rose"));

        // Check that the edges no longer exist
        CHECK(g.find("Yoona", "Taeyeon", 818) == g.end());
        CHECK(g.find("Taeyeon", "Yoona", 1314) == g.end());
        CHECK(g.find("Yoona", "Yoona", 530) == g.end());
        CHECK(g.find("Yoona", "Yoona", 1314) == g.end());

        // Check that the old node doesn't exist, and new node exist
        CHECK(g.is_node("Rose"));
        CHECK_FALSE(g.is_node("Yoona"));

        // Check we have these edges
        CHECK(g.find("Rose", "Taeyeon", 818) != g.end());
        CHECK(g.find("Taeyeon", "Rose", 1314) != g.end());
        CHECK(g.find("Rose", "Rose", 530) != g.end());
        CHECK(g.find("Rose", "Rose", 1314) != g.end());
    }

    SECTION("new_data already exist") {
        CHECK_FALSE(g.replace_node("Yoona", "Taeyeon"));

        CHECK(g.is_node("Yoona"));
        CHECK(g.is_node("Taeyeon"));
    }

    SECTION("Exception: is_node(old_data) == false") {
        // src, dst not exist
        CHECK_THROWS_MATCHES(g.replace_node("Yeonwoo", "Mina"),
                             std::runtime_error,
                             Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::replace_node "
                                                      "on a node that doesn't exist"));

        // src not exist, dst exist
        CHECK_THROWS_MATCHES(g.replace_node("Yeonwoo", "Taeyeon"),
                             std::runtime_error,
                             Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::replace_node "
                                                      "on a node that doesn't exist"));
    }
}

TEST_CASE("Merge and replace node") {
    auto g = gdwg::graph<std::string, int>{"Yoona", "Taeyeon", "Tzuyu"};

    SECTION("Simple case: No duplicate edge after replacement") {
        g.insert_edge("Yoona", "Taeyeon", 309);
        g.insert_edge("Yoona", "Yoona", 530);

        g.merge_replace_node("Yoona", "Tzuyu");

        // Check old edge are removed
        CHECK(g.find("Yoona", "Taeyeon", 309) == g.end());
        CHECK(g.find("Yoona", "Yoona", 530) == g.end());

        // Check the existence of the new edges
        CHECK(g.find("Tzuyu", "Tzuyu", 530) != g.end());
        CHECK(g.find("Tzuyu", "Taeyeon", 309) != g.end());

        // Check that the old node is remove
        CHECK_FALSE(g.is_node("Yoona"));
    }

    SECTION("Hard case: Edges need to be merged") {
        g.insert_edge("Yoona", "Tzuyu", 309);
        g.insert_edge("Tzuyu", "Tzuyu", 309);
        g.insert_edge("Yoona", "Taeyeon", 520);
        g.insert_edge("Tzuyu", "Taeyeon", 520);

        g.merge_replace_node("Yoona", "Tzuyu");

        // Check that the old node is remove
        CHECK_FALSE(g.is_node("Yoona"));

        // Check that edges have been merged, by checking the printed graph
        auto oss = std::ostringstream();
        oss << g;
        auto const expected_oss = std::string_view(R"(Taeyeon (
)
Tzuyu (
  Taeyeon | 520
  Tzuyu | 309
)
)");
        CHECK(oss.str() == expected_oss);
    }

    SECTION("Exception: either is_node(old_data) or is_node(new_data) are false") {
        // src not exist, dst exist
        CHECK_THROWS_MATCHES(g.merge_replace_node("Yeonwoo", "Taeyeon"),
                             std::runtime_error,
                             Catch::Matchers::Message("Cannot call gdwg::graph<N, "
                                                      "E>::merge_replace_node on old or new data if "
                                                      "they don't exist in the graph"));

        // dst not exist, src exist
        CHECK_THROWS_MATCHES(g.merge_replace_node("Taeyeon", "Yeonwoo"),
                             std::runtime_error,
                             Catch::Matchers::Message("Cannot call gdwg::graph<N, "
                                                      "E>::merge_replace_node on old or new data if "
                                                      "they don't exist in the graph"));

        // Both not exist
        CHECK_THROWS_MATCHES(g.merge_replace_node("Yeonwoo", "Mina"),
                             std::runtime_error,
                             Catch::Matchers::Message("Cannot call gdwg::graph<N, "
                                                      "E>::merge_replace_node on old or new data if "
                                                      "they don't exist in the graph"));
    }
}

TEST_CASE("Erase node") {
    auto g = gdwg::graph<std::string, int>{"Yoona", "Taeyeon", "Tzuyu"};

    SECTION("Erase not exist node") {
        CHECK_FALSE(g.erase_node("Twice"));
    }

    SECTION("No edge situtation") {
        CHECK(g.erase_node("Yoona"));

        CHECK(g.is_node("Yoona") == false);
    }

    SECTION("With edge: Relevant edges should be removed") {
        g.insert_edge("Yoona", "Yoona", 530);
        g.insert_edge("Yoona", "Yoona", 520);
        g.insert_edge("Yoona", "Tzuyu", 309);
        g.insert_edge("Taeyeon", "Tzuyu", 309);

        CHECK(g.erase_node("Yoona"));

        // Non-relevant is not removed
        CHECK(g.find("Taeyeon", "Tzuyu", 309) != g.end());

        // Relevant ones are removed
        CHECK(g.find("Yoona", "Yoona", 530) == g.end());
        CHECK(g.find("Yoona", "Yoona", 520) == g.end());
        CHECK(g.find("Yoona", "Tzuyu", 309) == g.end());
    }
}

TEST_CASE("Erase edge: (src, dst, weight)") {
    auto g = gdwg::graph<std::string, int>{"Yoona", "Taeyeon", "Tzuyu"};

    SECTION("Remove not exist edge") {
        CHECK_FALSE(g.erase_edge("Yoona", "Taeyeon", 520));
    }

    SECTION("Remove an edge successfully") {
        g.insert_edge("Tzuyu", "Taeyeon", 2);
        g.insert_edge("Tzuyu", "Taeyeon", 4);
        g.insert_edge("Yoona", "Taeyeon", 666);

        CHECK(g.erase_edge("Tzuyu", "Taeyeon", 4));

        // Check the remaining edges are correct
        CHECK(g.find("Tzuyu", "Taeyeon", 4) == g.end());

        CHECK(g.find("Tzuyu", "Taeyeon", 2) != g.end());
        CHECK(g.find("Yoona", "Taeyeon", 666) != g.end());
    }

    SECTION("Exception: either is_node(src) or is_node(dst) is false.") {
        // dst not exist
        CHECK_THROWS_MATCHES(g.erase_edge("Taeyeon", "Mina", 1314),
                             std::runtime_error,
                             Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::erase_edge on "
                                                      "src or dst if they don't exist in the graph"));

        // // src not exist
        CHECK_THROWS_MATCHES(g.erase_edge("Yeonwoo", "Taeyeon", 530),
                             std::runtime_error,
                             Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::erase_edge on "
                                                      "src or dst if they don't exist in the graph"));

        // // Both not exist
        CHECK_THROWS_MATCHES(g.erase_edge("Yeonwoo", "Mina", 520),
                             std::runtime_error,
                             Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::erase_edge on "
                                                      "src or dst if they don't exist in the graph"));
    }
}

TEST_CASE("Erase edge: (iterator i)") {
    auto g = gdwg::graph<std::string, int>{"Yoona", "Taeyeon", "Tzuyu"};

    SECTION("Remove not exist edge") {
        CHECK(g.erase_edge(g.begin()) == g.end());
        CHECK(g.erase_edge(g.end()) == g.end());
        // CHECK(g.erase_edge(gdwg::graph<std::string, int>::iterator()) == g.end());
    }

    SECTION("Remove from a graph with single edge") {
        g.insert_edge("Tzuyu", "Taeyeon", 2);

        CHECK(g.erase_edge(g.begin()) == g.end());
        CHECK(g.find("Tzuyu", "Taeyeon", 2) == g.end());
    }

    SECTION("Remove from a graph with multiple edges") {
        g.insert_edge("Tzuyu", "Taeyeon", 2);
        g.insert_edge("Yoona", "Taeyeon", 666);
        g.insert_edge("Tzuyu", "Taeyeon", 4);

        SECTION("Test 1") {
            CHECK(g.erase_edge(g.find("Tzuyu", "Taeyeon", 2)) == g.find("Tzuyu", "Taeyeon", 4));

            // Only the particular edge is removed
            CHECK(g.find("Tzuyu", "Taeyeon", 2) == g.end());
            CHECK(g.find("Yoona", "Taeyeon", 666) != g.end());
            CHECK(g.find("Tzuyu", "Taeyeon", 4) != g.end());
        }

        SECTION("Test 2") {
            CHECK(g.erase_edge(g.find("Yoona", "Taeyeon", 666)) == g.end());
        }

        SECTION("Test 3") {
            CHECK(g.erase_edge(g.find("Tzuyu", "Taeyeon", 4)) == g.find("Yoona", "Taeyeon", 666));
        }

        SECTION("Test 4") {
            CHECK(g.erase_edge(g.find("Tzuyu", "Taeyeon", 4)) == g.find("Yoona", "Taeyeon", 666));
            CHECK(g.erase_edge(g.find("Tzuyu", "Taeyeon", 2)) == g.find("Yoona", "Taeyeon", 666));
            CHECK(g.erase_edge(g.find("Yoona", "Taeyeon", 666)) == g.end());
        }
    }
}

TEST_CASE("Erase edge: (iterator i, iterator s)") {
    auto g = gdwg::graph<std::string, int>{"Yoona", "Taeyeon", "Tzuyu"};

    SECTION("Remove from a graph with single edge") {
        g.insert_edge("Tzuyu", "Taeyeon", 2);

        CHECK(g.erase_edge(g.begin(), g.end()) == g.end());
        CHECK(g.find("Tzuyu", "Taeyeon", 2) == g.end());
    }

    SECTION("Remove from a graph with multiple edges") {
        g.insert_edge("Tzuyu", "Taeyeon", 2);
        g.insert_edge("Yoona", "Taeyeon", 666);
        g.insert_edge("Tzuyu", "Taeyeon", 4);

        SECTION("Test 1") {
            CHECK(g.erase_edge(g.find("Tzuyu", "Taeyeon", 2), g.find("Tzuyu", "Taeyeon", 4))
                  == g.find("Tzuyu", "Taeyeon", 4));

            // Only the particular edge is removed
            CHECK(g.find("Tzuyu", "Taeyeon", 2) == g.end());
            CHECK(g.find("Yoona", "Taeyeon", 666) != g.end());
            CHECK(g.find("Tzuyu", "Taeyeon", 4) != g.end());
        }

        SECTION("Test 2") {
            CHECK(g.erase_edge(g.find("Tzuyu", "Taeyeon", 4), g.end()) == g.end());

            CHECK(g.find("Tzuyu", "Taeyeon", 2) != g.end());
        }
    }
}

TEST_CASE("Clear") {
    SECTION("Default constructed emtpy graph") {
        auto g = gdwg::graph<std::string, int>{};
        g.clear();
        CHECK(g.empty());
    }

    SECTION("Graph with nodes") {
        auto g = gdwg::graph<std::string, int>{"one", "two"};
        g.clear();
        CHECK(g.empty());
    }

    SECTION("Graph with nodes and edges") {
        auto g = gdwg::graph<std::string, int>{"one", "two"};
        g.insert_edge("one", "two", 2);
        g.clear();
        CHECK(g.empty());
    }
}

TEST_CASE("Test for a bunch of accessor functions") {
    auto g = gdwg::graph<std::string, int>{"Yoona", "Taeyeon", "Tzuyu"};
    g.insert_edge("Yoona", "Taeyeon", 818);
    g.insert_edge("Yoona", "Yoona", 530);
    g.insert_edge("Tzuyu", "Taeyeon", 1314);

    auto const g_copy_const = g;

    SECTION("Non-const is_node()") {
        CHECK(g.is_node("Yoona"));
        CHECK(g.is_node("Taeyeon"));
        CHECK(g.is_node("Tzuyu"));

        CHECK_FALSE(g.is_node("Yeonwoo"));
    }

    SECTION("Const is_node()") {
        CHECK(g_copy_const.is_node("Yoona"));
        CHECK(g_copy_const.is_node("Taeyeon"));
        CHECK(g_copy_const.is_node("Tzuyu"));

        CHECK_FALSE(g_copy_const.is_node("Yeonwoo"));
    }

    SECTION("empty()") {
        CHECK(gdwg::graph<std::string, int>{}.empty());
        CHECK_FALSE(g.empty());
        CHECK_FALSE(g_copy_const.empty());
    }

    SECTION("is_connected()") {
        SECTION("Non-const: Test has connection and no connection") {
            CHECK(g.is_connected("Yoona", "Taeyeon"));
            CHECK(g.is_connected("Yoona", "Yoona"));
            CHECK(g.is_connected("Tzuyu", "Taeyeon"));

            CHECK_FALSE(g.is_connected("Taeyeon", "Taeyeon"));
            CHECK_FALSE(g.is_connected("Taeyeon", "Tzuyu"));
        }

        SECTION("Const: Test has connection and no connection") {
            CHECK(g_copy_const.is_connected("Yoona", "Taeyeon"));
            CHECK(g_copy_const.is_connected("Yoona", "Yoona"));
            CHECK(g_copy_const.is_connected("Tzuyu", "Taeyeon"));

            CHECK_FALSE(g_copy_const.is_connected("Taeyeon", "Taeyeon"));
            CHECK_FALSE(g_copy_const.is_connected("Taeyeon", "Tzuyu"));
        }

        SECTION("Non-const Exception: either of is_node(src) or is_node(dst) are false") {
            // src not exist
            CHECK_THROWS_MATCHES(g.is_connected("Yeonwoo", "Tzuyu"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, "
                                                          "E>::is_connected if src or dst node don't "
                                                          "exist in the graph"));

            // dst not exist
            CHECK_THROWS_MATCHES(g.is_connected("Taeyeon", "Mina"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, "
                                                          "E>::is_connected if src or dst node don't "
                                                          "exist in the graph"));

            // src, dst not exist
            CHECK_THROWS_MATCHES(g.is_connected("Yeonwoo", "Mina"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, "
                                                          "E>::is_connected if src or dst node don't "
                                                          "exist in the graph"));
        }

        SECTION("Const Exception: either of is_node(src) or is_node(dst) are false") {
            // src not exist
            CHECK_THROWS_MATCHES(g_copy_const.is_connected("Yeonwoo", "Tzuyu"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, "
                                                          "E>::is_connected if src or dst node don't "
                                                          "exist in the graph"));

            // dst not exist
            CHECK_THROWS_MATCHES(g_copy_const.is_connected("Taeyeon", "Mina"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, "
                                                          "E>::is_connected if src or dst node don't "
                                                          "exist in the graph"));

            // src, dst not exist
            CHECK_THROWS_MATCHES(g_copy_const.is_connected("Yeonwoo", "Mina"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, "
                                                          "E>::is_connected if src or dst node don't "
                                                          "exist in the graph"));
        }
    }

    SECTION("nodes") {
        CHECK(gdwg::graph<std::string, int>{}.nodes().empty());
        CHECK(g.nodes() == std::vector<std::string>{"Taeyeon", "Tzuyu", "Yoona"});
        CHECK(g_copy_const.nodes() == std::vector<std::string>{"Taeyeon", "Tzuyu", "Yoona"});
    }

    SECTION("weights") {
        SECTION("Check nodes with no connection") {
            CHECK(g.weights("Taeyeon", "Tzuyu").empty());
            CHECK(g.weights("Taeyeon", "Yoona").empty());

            CHECK(g_copy_const.weights("Taeyeon", "Tzuyu").empty());
            CHECK(g_copy_const.weights("Taeyeon", "Yoona").empty());
        }

        SECTION("Check if the weights are in the right order") {
            g.insert_edge("Yoona", "Yoona", 250);
            g.insert_edge("Yoona", "Taeyeon", 1000);
            g.insert_edge("Yoona", "Taeyeon", 530);

            CHECK(g.weights("Yoona", "Yoona") == std::vector<int>{250, 530});
            CHECK(g.weights("Yoona", "Taeyeon") == std::vector<int>{530, 818, 1000});

            // Check const
            auto const g_const = g;

            CHECK(g_const.weights("Yoona", "Yoona") == std::vector<int>{250, 530});
            CHECK(g_const.weights("Yoona", "Taeyeon") == std::vector<int>{530, 818, 1000});
        }

        SECTION("Non-const Exception: either of is_node(src) or is_node(dst) are false") {
            // src not exist
            CHECK_THROWS_MATCHES(g.weights("Yeonwoo", "Tzuyu"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::weights if "
                                                          "src or dst node don't exist in the graph"));

            // dst not exist
            CHECK_THROWS_MATCHES(g.weights("Taeyeon", "Mina"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::weights if "
                                                          "src or dst node don't exist in the graph"));

            // src, dst not exist
            CHECK_THROWS_MATCHES(g.weights("Yeonwoo", "Mina"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::weights if "
                                                          "src or dst node don't exist in the graph"));
        }

        SECTION("Const Exception: either of is_node(src) or is_node(dst) are false") {
            // src not exist
            CHECK_THROWS_MATCHES(g_copy_const.weights("Yeonwoo", "Tzuyu"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::weights if "
                                                          "src or dst node don't exist in the graph"));

            // dst not exist
            CHECK_THROWS_MATCHES(g_copy_const.weights("Taeyeon", "Mina"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::weights if "
                                                          "src or dst node don't exist in the graph"));

            // src, dst not exist
            CHECK_THROWS_MATCHES(g_copy_const.weights("Yeonwoo", "Mina"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::weights if "
                                                          "src or dst node don't exist in the graph"));
        }
    }

    SECTION("find()") {
        SECTION("Non-const: Edge not exist") {
            CHECK(g.find("Yoona", "Tzuyu", 100) == g.end());
            CHECK(g.find("Yoona", "Yoona", 520) == g.end());
            CHECK(g.find("Yeonwoo", "Tzuyu", 100) == g.end());
            CHECK(g.find("Yeonwoo", "Mina", 100) == g.end());
        }

        SECTION("Const: Edge not exist") {
            CHECK(g_copy_const.find("Yoona", "Tzuyu", 100) == g_copy_const.end());
            CHECK(g_copy_const.find("Yoona", "Yoona", 520) == g_copy_const.end());
            CHECK(g_copy_const.find("Yeonwoo", "Tzuyu", 100) == g_copy_const.end());
            CHECK(g_copy_const.find("Yeonwoo", "Mina", 100) == g_copy_const.end());
        }

        SECTION("Non-const: Return correct iterator") {
            auto it = g.find("Yoona", "Taeyeon", 818);

            CHECK((*it).from == "Yoona");
            CHECK((*it).to == "Taeyeon");
            CHECK((*it).weight == 818);

            it = g.find("Yoona", "Yoona", 530);

            CHECK((*it).from == "Yoona");
            CHECK((*it).to == "Yoona");
            CHECK((*it).weight == 530);
        }

        SECTION("Const: Return correct iterator") {
            auto it = g_copy_const.find("Yoona", "Taeyeon", 818);

            CHECK((*it).from == "Yoona");
            CHECK((*it).to == "Taeyeon");
            CHECK((*it).weight == 818);

            it = g_copy_const.find("Yoona", "Yoona", 530);

            CHECK((*it).from == "Yoona");
            CHECK((*it).to == "Yoona");
            CHECK((*it).weight == 530);
        }
    }

    SECTION("connections()") {
        SECTION("Empty connections") {
            CHECK(g.connections("Taeyeon").empty());
            CHECK(g_copy_const.connections("Taeyeon").empty());
        }

        SECTION("Non-const: Check if nodes return are in order and complete") {
            g.insert_edge("Yoona", "Tzuyu", 818);
            g.insert_edge("Yoona", "Yoona", 425);
            g.insert_edge("Yoona", "Taeyeon", 309);

            CHECK(g.connections("Yoona")
                  == std::vector<std::string>{"Taeyeon", "Taeyeon", "Tzuyu", "Yoona", "Yoona"});
        }

        SECTION("Const: Check if nodes return are in order and complete") {
            g.insert_edge("Yoona", "Tzuyu", 818);
            g.insert_edge("Yoona", "Yoona", 425);
            g.insert_edge("Yoona", "Taeyeon", 309);

            auto const g_const = g;

            CHECK(g_const.connections("Yoona")
                  == std::vector<std::string>{"Taeyeon", "Taeyeon", "Tzuyu", "Yoona", "Yoona"});
        }

        SECTION("Non-const Exception: if is_node(src) is false") {
            // src not exist
            CHECK_THROWS_MATCHES(g.connections("Yeonwoo"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::connections "
                                                          "if src doesn't exist in the graph"));
        }

        SECTION("Const Exception: if is_node(src) is false") {
            // src not exist
            CHECK_THROWS_MATCHES(g_copy_const.connections("Yeonwoo"),
                                 std::runtime_error,
                                 Catch::Matchers::Message("Cannot call gdwg::graph<N, E>::connections "
                                                          "if src doesn't exist in the graph"));
        }
    }
}

TEST_CASE("Iterator") {
    SECTION("Empty Graph") {
        auto const g_empty = gdwg::graph<std::string, int>{};
        CHECK(g_empty.begin() == g_empty.end());
    }

    auto g = gdwg::graph<std::string, int>{"Yoona", "Taeyeon", "Tzuyu"};
    g.insert_edge("Yoona", "Taeyeon", 818);
    g.insert_edge("Yoona", "Yoona", 530);
    g.insert_edge("Tzuyu", "Taeyeon", 1314);

    auto const g_const = g;

    SECTION("Begin and dereference *") {
        auto const it = g_const.begin();

        CHECK((*it).from == "Tzuyu");
        CHECK((*it).to == "Taeyeon");
        CHECK((*it).weight == 1314);
    }

    SECTION("Traveral ++()") {
        // Expected output
        auto const exp = std::vector<gdwg::graph<std::string, int>::value_type>{
           {"Tzuyu", "Taeyeon", 1314},
           {"Yoona", "Taeyeon", 818},
           {"Yoona", "Yoona", 530},
        };

        // Iterate through the graph
        auto count = std::size_t{0};
        for (auto it = g_const.begin(); it != g_const.end(); ++it, ++count) {
            CHECK((*it).from == exp[count].from);
            CHECK((*it).to == exp[count].to);
            CHECK((*it).weight == exp[count].weight);
        }
    }

    SECTION("Traveral ++(int)") {
        auto it = g_const.begin();

        // Post increment and check if the iterator returned is correct
        auto prev_it = it++;
        CHECK((*prev_it).from == "Tzuyu");
        CHECK((*prev_it).to == "Taeyeon");
        CHECK((*prev_it).weight == 1314);

        // Check if increment is success
        CHECK((*it).from == "Yoona");
        CHECK((*it).to == "Taeyeon");
        CHECK((*it).weight == 818);
    }

    SECTION("Traveral --()") {
        // Expected output
        auto const exp = std::vector<gdwg::graph<std::string, int>::value_type>{
           {"Tzuyu", "Taeyeon", 1314},
           {"Yoona", "Taeyeon", 818},
           {"Yoona", "Yoona", 530},
        };

        // Increment to point the last element
        auto last_element_it = g_const.begin();
        ++last_element_it;
        ++last_element_it;

        // Iterate the graph backwardly
        auto count = std::size_t{2};
        auto it = last_element_it;
        for (; it != g_const.begin(); --it, --count) {
            CHECK((*it).from == exp[count].from);
            CHECK((*it).to == exp[count].to);
            CHECK((*it).weight == exp[count].weight);
        }

        CHECK((*it).from == exp[count].from);
        CHECK((*it).to == exp[count].to);
        CHECK((*it).weight == exp[count].weight);
    }

    SECTION("Traveral --(int)") {
        // Let the iterator points to the last element
        auto it = g_const.begin();
        ++it;
        ++it;

        // Post decrement and check if the iterator returned is correct
        auto last_element_it = it--;
        CHECK((*last_element_it).from == "Yoona");
        CHECK((*last_element_it).to == "Yoona");
        CHECK((*last_element_it).weight == 530);

        // Check if decrement is success
        CHECK((*it).from == "Yoona");
        CHECK((*it).to == "Taeyeon");
        CHECK((*it).weight == 818);
    }

    SECTION("Comparision") {
        // SECTION("Value constructed iterator are equal") {
        //  CHECK(gdwg::graph<std::string, int>::iterator() == gdwg::graph<std::string,
        // int>::iterator());
        // }

        SECTION("Test if true on equal iterator") {
            auto it = g_const.begin();
            CHECK(g_const.begin() == g_const.find("Tzuyu", "Taeyeon", 1314));

            ++it;
            CHECK(it == g_const.find("Yoona", "Taeyeon", 818));

            ++it;
            CHECK(it == g_const.find("Yoona", "Yoona", 530));

            ++it;
            CHECK(it == g_const.end());
        }

        SECTION("Test if false on not equal iterator") {
            auto it = g_const.begin();
            CHECK_FALSE(it == g_const.end());
            CHECK_FALSE(++it == g_const.end());
            CHECK_FALSE(++it == g_const.end());
            CHECK_FALSE(--it == g_const.end());
            CHECK_FALSE(--it == g_const.end());
        }
    }
}

TEST_CASE("Comparison ==") {
    SECTION("Empty Graph") {
        CHECK(gdwg::graph<std::string, int>{} == gdwg::graph<std::string, int>({}));
    }

    SECTION("Just nodes") {
        // Construct two new graph, one const, one non-const
        auto const g_const = gdwg::graph<std::string, int>{"Yoona", "Mina", "Taeyeon"};
        auto g = gdwg::graph<std::string, int>{};

        CHECK_FALSE(g == g_const);

        g.insert_node("Yoona");
        g.insert_node("Mina");
        g.insert_node("Taeyeon");

        CHECK(g == g_const);
    }

    SECTION("Nodes and edges") {
        auto g = gdwg::graph<std::string, int>{"Yoona", "Tzuyu", "Taeyeon"};
        g.insert_edge("Yoona", "Taeyeon", 818);
        g.insert_edge("Yoona", "Yoona", 530);
        g.insert_edge("Tzuyu", "Taeyeon", 1314);

        auto v = std::vector<std::string>{"Taeyeon", "Tzuyu", "Yoona"};
        auto g_same = gdwg::graph<std::string, int>{v.begin(), v.end()};

        g_same.insert_edge("Yoona", "Taeyeon", 818);
        g_same.insert_edge("Yoona", "Yoona", 530);
        g_same.insert_edge("Tzuyu", "Taeyeon", 1314);

        SECTION("Check comparison with const") {
            auto const g_const = g_same;
            (void)g_const;

            CHECK(g_const == g_same);
            CHECK(g == g);
        }

        CHECK(g == g_same);

        g.erase_edge("Yoona", "Yoona", 530);
        CHECK_FALSE(g == g_same);

        g_same.erase_edge("Yoona", "Yoona", 530);
        CHECK(g == g_same);
    }
}

TEST_CASE("Comparison !=") {
    SECTION("Empty Graph") {
        CHECK_FALSE(gdwg::graph<std::string, int>{} != gdwg::graph<std::string, int>({}));
    }

    SECTION("Just nodes") {
        // Construct two new graph, one const, one non-const
        auto const g_const = gdwg::graph<std::string, int>{"Yoona", "Mina", "Taeyeon"};
        auto g = gdwg::graph<std::string, int>{};

        CHECK(g_const != g);
        CHECK(g != g_const);

        g.insert_node("Yoona");
        g.insert_node("Mina");
        g.insert_node("Taeyeon");

        CHECK_FALSE(g_const != g);
        CHECK_FALSE(g != g_const);
    }

    SECTION("Nodes and edges") {
        auto g = gdwg::graph<std::string, int>{"Yoona", "Tzuyu", "Taeyeon"};
        g.insert_edge("Yoona", "Taeyeon", 818);
        g.insert_edge("Yoona", "Yoona", 530);
        g.insert_edge("Tzuyu", "Taeyeon", 1314);

        auto v = std::vector<std::string>{"Taeyeon", "Tzuyu", "Yoona"};
        auto g_same = gdwg::graph<std::string, int>{v.begin(), v.end()};

        g_same.insert_edge("Yoona", "Taeyeon", 818);
        g_same.insert_edge("Yoona", "Yoona", 530);
        g_same.insert_edge("Tzuyu", "Taeyeon", 1314);

        SECTION("Check comparison with const") {
            auto const g_const = g_same;
            (void)g_const;

            CHECK_FALSE(g_const != g_same);
            CHECK_FALSE(g != g);
        }

        CHECK_FALSE(g != g_same);

        g.erase_edge("Yoona", "Yoona", 530);
        CHECK(g != g_same);

        g_same.erase_edge("Yoona", "Yoona", 530);
        CHECK_FALSE(g != g_same);
    }
}

TEST_CASE("Extractor <<") {
    SECTION("Empty graph") {
        auto const g = gdwg::graph<int, int>{};

        auto out = std::ostringstream{};
        out << g;
        CHECK(out.str().empty());
    }

    SECTION("Just nodes") {
        auto g = gdwg::graph<std::string, int>{"Yoona", "Tzuyu", "Taeyeon"};

        auto out = std::ostringstream{};
        out << g;
        auto const expected_output = std::string_view(R"(Taeyeon (
)
Tzuyu (
)
Yoona (
)
)");

        CHECK(out.str() == expected_output);

        auto const g_const = g;
        (void)g_const;
        out.str("");
        out << g_const;
        CHECK(out.str() == expected_output);
    }

    SECTION("Sample test with edge insertion order changed") {
        auto const v = std::vector<gdwg::graph<int, int>::value_type>{
           {4, 1, -4},
           {3, 6, -8},
           {3, 2, 2},
           {2, 4, 2},
           {2, 1, 1},
           {6, 3, 10},
           {6, 2, 5},
           {1, 5, -1},
           {4, 5, 3},
           {5, 2, 7},
        };

        auto g = gdwg::graph<int, int>{1, 2, 3, 4, 5, 6, 64};
        for (const auto& x : v) {
            g.insert_edge(x.from, x.to, x.weight);
        };

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

        // Also check for const
        auto const g_const = g;
        out.str("");
        out << g_const;
        CHECK(out.str() == expected_output);
    }
}