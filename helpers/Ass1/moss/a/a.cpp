#include <queue>
#include <algorithm>
#include <iostream>
#include <unordered_map>

auto same_len_lexicon (int const f_size, std::unordered_set<std::string> const& lexicon)
-> std::unordered_set<std::string>;

auto ladder_exist (std::string const& from, std::string const& to,
                   std::unordered_set<std::string> lexicon) -> int;

auto lexicon_graph (std::string const& from, std::string const& to,
                    std::unordered_set<std::string> lexicon)
-> std::unordered_map<std::string, std::unordered_set<std::string>>;

auto bfs_ladders (std::string const& from, std::string const& to, int const l_size,
                  std::unordered_map<std::string, std::unordered_set<std::string>> graph)
-> std::vector<std::vector<std::string>>;

namespace word_ladder {

    [[nodiscard]] auto generate(std::string const& from,
                                std::string const& to,
                                std::unordered_set<std::string> const& lexicon)
       -> std::vector<std::vector<std::string>> {
        std::queue<std::vector<std::string>> potential_ladders;
        std::vector<std::vector<std::string>> ladders;

        auto small_lexicon = same_len_lexicon(from.size(), lexicon);
        auto const ladder_size = ladder_exist(from, to, small_lexicon);

        if (ladder_size == 0){
            return ladders;
        } else {
            return bfs_ladders(from, to, ladder_size, lexicon_graph(from, to, small_lexicon));
        }
    }

} // namespace word_ladder

auto same_len_lexicon (int f_size, std::unordered_set<std::string> const& lexicon)
-> std::unordered_set<std::string> {
    std::unordered_set<std::string> small_lexicon;
    for (auto& word : lexicon) {
        if (word.size() == f_size)
            small_lexicon.insert(word);
    }
    return small_lexicon;
}

auto ladder_exist (std::string const& from, std::string const& to,
                   std::unordered_set<std::string> lexicon)-> int {
    std::queue<std::vector<std::string>> potential_ladders;

    std::vector<std::string> cur_ladder;
    cur_ladder.push_back(from);
    potential_ladders.push(cur_ladder);
    cur_ladder.clear();
    auto cur_level = 1;
    std::unordered_set<std::string> added_words;
    added_words.insert(from);
    for (auto& w : added_words) {
        lexicon.erase(w);
    }
    added_words.clear();

    while (!potential_ladders.empty()) {
        cur_ladder = potential_ladders.front();
        potential_ladders.pop();

        auto const cur_word = *cur_ladder.rbegin();

        if (cur_ladder.size() > cur_level) {
            for (auto& w : added_words) {
                lexicon.erase(w);
            }
            added_words.clear();
            cur_level += 1;
        }

        if (cur_word == to) {
            return cur_ladder.size();
        } else if (cur_level == cur_ladder.size()) {
            std::vector<std::string> new_words;
            auto new_word = cur_word;
            for (auto& letter : new_word) {
                new_word = cur_word;
                for (auto ch = 'a'; ch <= 'z'; ++ch) {
                    letter = ch;
                    auto isadded = (added_words.find(new_word) != added_words.end());
                    auto isduplicte = (std::find(cur_ladder.begin(), cur_ladder.end(), new_word) != cur_ladder.end());
                    auto isvalid = (lexicon.find(new_word) != lexicon.end());
                    if (!isduplicte && isvalid && !isadded) {
                        new_words.push_back(new_word);
                        added_words.insert(new_word);
                        new_word = cur_word;
                    }
                }
            }

            for (auto& w : new_words) {
                auto new_ladder = cur_ladder;
                new_ladder.push_back(w);
                potential_ladders.push(new_ladder);
            }
        }
    }
    return cur_ladder.size();
}

auto lexicon_graph (std::string const& from, std::string const& to,
                    std::unordered_set<std::string> lexicon)
-> std::unordered_map<std::string, std::unordered_set<std::string>> {
    std::unordered_set<std::string> added_words;
    std::queue<std::string> wqueue;
    std::unordered_map<std::string, std::unordered_set<std::string>> graph;

    wqueue.push(from);
    added_words.insert(from);

    while (!wqueue.empty()) {
        auto const level = wqueue.size();
        auto count = 0;

        for (auto& w : added_words)
            lexicon.erase(w);
        added_words.clear();

        while (count < level) {
            auto cur_word = wqueue.front();
            wqueue.pop();

            auto new_word = cur_word;
            for (auto& letter : new_word) {
                new_word = cur_word;
                for (auto ch = 'a'; ch <= 'z'; ++ch) {
                    letter = ch;
                    auto isadded = (added_words.find(new_word) != added_words.end());
                    if (new_word == to)
                        isadded = false;
                    auto isvalid = (lexicon.find(new_word) != lexicon.end());

                    if (isvalid) {
                        graph[cur_word].insert(new_word);
                        if (!isadded) {
                            added_words.insert(new_word);
                            wqueue.push(new_word);
                        }
                        new_word = cur_word;
                    }
                }
            }
            count += 1;
        }
    }
    return graph;
}

auto bfs_ladders (std::string const& from, std::string const& to, int const l_size,
                  std::unordered_map<std::string, std::unordered_set<std::string>> graph)
-> std::vector<std::vector<std::string>> {
    std::vector<std::vector<std::string>> ladders;
    std::queue<std::vector<std::string>> ladders_queue;
    std::vector<std::string> cur_ladder;

    cur_ladder.push_back(from);
    ladders_queue.push(cur_ladder);
    cur_ladder.clear();

    while (!ladders_queue.empty()) {
        cur_ladder = ladders_queue.front();
        ladders_queue.pop();
        auto cur_word = (*cur_ladder.rbegin());
        if (cur_word == to) {
            ladders.push_back(cur_ladder);
        }
        else if (cur_ladder.size() < l_size)
        {
            if (graph.find(cur_word) != graph.end()) {
                for (auto iter = graph[cur_word].begin(); iter != graph[cur_word].end(); ++iter) {
                    auto new_ladder = cur_ladder;
                    new_ladder.push_back(*iter);
                    if ((new_ladder.size() < l_size) || ((new_ladder.size() == l_size) && ((*iter) == to)))
                        ladders_queue.push(new_ladder);
                }
            }
        }
    }
    std::sort(ladders.begin(), ladders.end());
    return ladders;
}