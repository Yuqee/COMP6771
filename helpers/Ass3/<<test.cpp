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
    you?  | 1
)
you? (
)
)");
 CHECK(str.str() == expected_output);
}