#include <comp6771/word_ladder.hpp>
#include <queue>
#include <algorithm>
#include <iostream>

auto same_len_lexicon (std::string const& from,
                       std::unordered_set<std::string> const& lexicon)
-> std::unordered_set<std::string>;

namespace word_ladder {

    [[nodiscard]] auto generate(std::string const& from,
                                std::string const& to,
                                std::unordered_set<std::string> const& lexicon)
       -> std::vector<std::vector<std::string>> {
        std::queue<std::vector<std::string>> potential_ladders;
        std::vector<std::vector<std::string>> ladders;

        auto small_lexicon = same_len_lexicon(from, lexicon);

        std::vector<std::string> cur_ladder;
        cur_ladder.push_back(from);
        potential_ladders.push(cur_ladder);
        cur_ladder.clear();
        auto ladder_size = 0;
        auto cur_level = 1;
        std::unordered_set<std::string> added_words;
        added_words.insert(from);
        for (auto& w : added_words) {
            small_lexicon.erase(w);
        }
        added_words.clear();

        while (!potential_ladders.empty()) {
            cur_ladder = potential_ladders.front();
            potential_ladders.pop();

            // std::cout << "queue size: " << potential_ladders.size() << '\n';
            // if (cur_ladder.size()==6) {
            //     std::cout << "\n------------\ncur_ladder: ";
            //     for (auto& w : cur_ladder)
            //         std::cout << w << " ";
            // }
            // std::cout << "\n------------\ncur_ladder: ";
            // for (auto& w : cur_ladder)
            //     std::cout << w << " ";
            // std::cout << "\nlexicon: ";
            // for (auto& w : small_lexicon)
            //     std::cout << w << " ";
            // std::cout << "\ncur_ladder size: " << cur_ladder.size();
            // std::cout << "\ncur_level: " << cur_level;

            auto const cur_word = *cur_ladder.rbegin();

            if (cur_ladder.size() > cur_level) {
                // std::cout << "\nCase1";
                for (auto& w : added_words) {
                    small_lexicon.erase(w);
                }
                added_words.clear();
                cur_level += 1;
            }

            if (cur_word == to) {
                // std::cout << "\nCase2";
                if (ladders.size() == 0 && ladder_size == 0) {
                    ladder_size = cur_ladder.size();
                    ladders.push_back(cur_ladder);
                }
                else if (cur_ladder.size() == ladder_size) {
                    ladders.push_back(cur_ladder);
                }
            } else if (((cur_ladder.size()<ladder_size)||(ladder_size == 0))&&(cur_level==cur_ladder.size())) {
                // std::cout << "\nCase3";
                std::vector<std::string> new_words;
                auto new_word = cur_word;
                for (auto& letter : new_word) {
                    new_word = cur_word;
                    for (auto ch = 'a'; ch <= 'z'; ++ch) {
                        letter = ch;
                        auto isadded = (added_words.find(new_word) != added_words.end());
                        if (new_word == to)
                            isadded = false;
                        auto isduplicte = (std::find(cur_ladder.begin(), cur_ladder.end(), new_word) != cur_ladder.end());
                        auto isvalid = (small_lexicon.find(new_word) != small_lexicon.end());

                        // if (new_word == "peat") {
                        //     std::cout << "\n~~~~~~~~~~~~~\n\tisadded\tisduplicte\tisvalid";
                        //     std::cout << "\n\t" << isadded << "\t" << isduplicte << "\t" << isvalid;
                        // }

                        if (!isduplicte && isvalid) {
                            new_words.push_back(new_word);
                            if (!isadded)
                                added_words.insert(new_word);
                            new_word = cur_word;
                        }
                    }
                }
                // std::cout<<"\nnew_words: ";
                for (auto& w : new_words) {
                    // std::cout << w << " ";
                    auto new_ladder = cur_ladder;
                    new_ladder.push_back(w);
                    potential_ladders.push(new_ladder);
                }
            }
        }
        std::sort(ladders.begin(), ladders.end());
        return ladders;
    }

} // namespace word_ladder

auto same_len_lexicon (std::string const& from,
                       std::unordered_set<std::string> const& lexicon)
-> std::unordered_set<std::string> {
    std::unordered_set<std::string> small_lexicon;
    for (auto& word : lexicon) {
        if (word.size() == from.size())
            small_lexicon.insert(word);
    }
    return small_lexicon;
}