#include <queue>
#include <unordered_map>
#include <iostream>
#include <algorithm>

auto count_diffrence(std::string const& word1, std::string const& word2) -> int {
    auto count_diff = 0;
    auto word1_iter = word1.begin();
    for (auto word2_iter = word2.begin(); word2_iter != word2.end(); ++word2_iter) {
        if ((*word1_iter) != (*word2_iter))
            count_diff += 1;
        ++word1_iter;
    }
    return count_diff;
}

auto hop_lexicon(std::string const& word, std::unordered_set<std::string> lexicon,
                 int hop = 1) -> std::vector<std::string> {
    auto count_diff = 0;
    std::vector<std::string> hopped_lexicon;
    for (auto iter = lexicon.begin(); iter != lexicon.end(); ++iter) {
        if (count_diffrence(word, *iter) == hop) {
            hopped_lexicon.push_back(*iter);
        }
    }

    return hopped_lexicon;
}

auto same_len_lexicon(std::string const from, std::unordered_set<std::string> lexicon)
   -> std::unordered_set<std::string> {
    std::unordered_set<std::string> return_lex;
    for (auto& word : lexicon) {
        if (word.size() == from.size())
            return_lex.insert(word);
    }
    return return_lex;
}

auto lexicon_graph(std::string const from, std::unordered_set<std::string> lexicon)
   -> std::unordered_map<std::string, std::vector<std::string>> {
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::queue<std::string> nodes;
    std::vector<std::string> explored;

    nodes.push(from);
    lexicon.erase(from);

    while (!nodes.empty()) {
        auto const level = nodes.size();
        auto count = 0;
        while (count < level) {
            auto cur_node = nodes.front();
            nodes.pop();

            auto adjecent_nodes = hop_lexicon(cur_node, lexicon);
            for (auto& new_node : adjecent_nodes) {
                auto isfound = std::find(explored.begin(), explored.end(), new_node);
                if (isfound == explored.end()) {
                    explored.push_back(new_node);
                    nodes.push(new_node);
                }
                graph[cur_node].push_back(new_node);
            }
            count += 1;
        }

        for (auto& n : explored) {
            lexicon.erase(n);
        }
        explored.clear();
    }
    return graph;
}


namespace word_ladder {

    [[nodiscard]] auto generate(std::string const& from,
                                std::string const& to,
                                std::unordered_set<std::string> const& lexicon)
       -> std::vector<std::vector<std::string>> {

        std::vector<std::vector<std::string>> ladders;
        std::queue<std::vector<std::string>> pontential_ladders;
        std::vector<std::string> cur_ladder;

        auto graph = lexicon_graph(from, same_len_lexicon(from, lexicon));

        // std::cout << "T is ready!!!\n";
        // std::cout << graph.size() << '\n';

        cur_ladder.push_back(from);
        pontential_ladders.push(cur_ladder);
        cur_ladder.clear();

        auto ladder_size = 0;
        while(!pontential_ladders.empty()) {
            cur_ladder = pontential_ladders.front();
            pontential_ladders.pop();
            auto cur_word = (*cur_ladder.rbegin());
            if (cur_word == to) {
                if ((ladder_size == 0) && (ladders.size()==0)){
                    ladders.push_back(cur_ladder);
                    ladder_size = cur_ladder.size();
                } else if (cur_ladder.size()==ladder_size)
                    ladders.push_back(cur_ladder);
            } else if (((ladder_size == 0) && (ladders.size()==0)) || (cur_ladder.size() < ladder_size)){
                if (graph.find(cur_word) != graph.end()) {
                    for (auto iter = graph[cur_word].begin(); iter != graph[cur_word].end(); ++iter) {
                        auto new_ladder = cur_ladder;
                        new_ladder.push_back(*iter);
                        pontential_ladders.push(new_ladder);
                    }
                }
            }
        }
        std::sort(ladders.begin(), ladders.end());
        return ladders;
    }

} // namespace word_ladder