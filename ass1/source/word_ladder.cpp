#include <comp6771/word_ladder.hpp>
#include <unordered_map>
#include <algorithm>
#include <queue>

auto same_len_lexicon(int const f_size, std::unordered_set<std::string> const& lexicon)
   -> std::unordered_set<std::string>;

auto is_one_hop(std::string w1, std::string w2) -> bool;

auto ladder_len(std::string const& from,
                std::string const& to,
                std::unordered_set<std::string> lexicon) -> int;

auto lexicon_graph(std::string const& from,
                   std::string const& to,
                   std::unordered_set<std::string> lexicon)
   -> std::unordered_map<std::string, std::unordered_set<std::string>>;

auto bfs_ladders(std::string const& from,
                 std::string const& to,
                 int const l_size,
                 std::unordered_set<std::string> small_lexicon,
                 std::unordered_map<std::string, std::unordered_set<std::string>> graph)
   -> std::vector<std::vector<std::string>>;

namespace word_ladder {

	[[nodiscard]] auto generate(std::string const& from,
	                            std::string const& to,
	                            std::unordered_set<std::string> const& lexicon)
	   -> std::vector<std::vector<std::string>> {
		auto small_lexicon = same_len_lexicon(from.size(), lexicon);
		auto const ladder_size = ladder_len(from, to, small_lexicon);

		if (ladder_size == 1) {
			return std::vector<std::vector<std::string>>{};
		}
		else {
			return bfs_ladders(from,
			                   to,
			                   ladder_size,
			                   small_lexicon,
			                   lexicon_graph(from, to, small_lexicon));
		}
	}

} // namespace word_ladder

auto same_len_lexicon(int f_size, std::unordered_set<std::string> const& lexicon)
   -> std::unordered_set<std::string> {
    // filter the lexicon.
	std::unordered_set<std::string> small_lexicon;
	for (auto& word : lexicon) {
		if (word.size() == f_size)
			small_lexicon.insert(word);
	}
	return small_lexicon;
}

auto is_one_hop(std::string w1, std::string w2) -> bool {
	// return ture if 2 words have one letter difference.
	auto count = 0;
	auto iter1 = w1.begin();
	for (auto iter2 = w2.begin(); iter2 != w2.end(); ++iter2) {
		if ((*iter1) != (*iter2))
			count += 1;
		++iter1;
	}
	return (count == 1);
}

auto ladder_len(std::string const& from,
                std::string const& to,
                std::unordered_set<std::string> lexicon) -> int {
    // quickly figure out one ladder by erease words from lexicon quickly.
	std::queue<std::vector<std::string>> potential_ladders;
	std::vector<std::string> cur_ladder;
	std::unordered_set<std::string> added_words;
	auto cur_level = 1;

	cur_ladder.push_back(from);
	potential_ladders.push(cur_ladder);
	cur_ladder.clear();
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
		}
		else if (cur_level == cur_ladder.size()) {
			std::vector<std::string> new_words;
			auto new_word = cur_word;
			for (auto& letter : new_word) {
				new_word = cur_word;
				for (auto ch = 'a'; ch <= 'z'; ++ch) {
					letter = ch;
					auto isadded = (added_words.find(new_word) != added_words.end());
					auto isduplicte =
					   (std::find(cur_ladder.begin(), cur_ladder.end(), new_word) != cur_ladder.end());
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

auto lexicon_graph(std::string const& from,
                   std::string const& to,
                   std::unordered_set<std::string> lexicon)
   -> std::unordered_map<std::string, std::unordered_set<std::string>> {
    // connecting lexi_nodes naively.
	std::unordered_map<std::string, std::unordered_set<std::string>> graph;

	for (auto& w1 : lexicon) {
		for (auto& w2 : lexicon) {
			if (is_one_hop(w1, w2))
				graph[w1].insert(w2);
		}
	}
	return graph;
}

auto bfs_ladders(std::string const& from,
                 std::string const& to,
                 int const l_size,
                 std::unordered_set<std::string> small_lexicon,
                 std::unordered_map<std::string, std::unordered_set<std::string>> graph)
   -> std::vector<std::vector<std::string>> {
    // bfs method to find shortest path and delete used words per level.
	std::queue<std::vector<std::string>> potential_ladders;
	std::vector<std::vector<std::string>> ladders;
	std::vector<std::string> cur_ladder;
	std::unordered_set<std::string> added_words;
	auto cur_level = 1;

	cur_ladder.push_back(from);
	potential_ladders.push(cur_ladder);
	cur_ladder.clear();
	added_words.insert(from);
	for (auto& w : added_words) {
		small_lexicon.erase(w);
	}
	added_words.clear();

	while (!potential_ladders.empty()) {
		cur_ladder = potential_ladders.front();
		potential_ladders.pop();

		auto const cur_word = *cur_ladder.rbegin();

		if (cur_ladder.size() > cur_level) {
			for (auto& w : added_words) {
				small_lexicon.erase(w);
			}
			added_words.clear();
			cur_level += 1;
		}

		if (cur_word == to) {
			if (cur_ladder.size() == l_size) {
				ladders.push_back(cur_ladder);
			}
		}
		else if ((cur_ladder.size() < l_size) && (cur_level == cur_ladder.size())) {
			std::vector<std::string> new_words;
			if (graph.find(cur_word) != graph.end()) {
				for (auto& new_word : graph[cur_word]) {
					auto isadded = (added_words.find(new_word) != added_words.end());
					if (new_word == to)
						isadded = false;
					auto isduplicte =
					   (std::find(cur_ladder.begin(), cur_ladder.end(), new_word) != cur_ladder.end());
					auto isvalid = (small_lexicon.find(new_word) != small_lexicon.end());

					if (!isduplicte && isvalid) {
						new_words.push_back(new_word);
						if (!isadded)
							added_words.insert(new_word);
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
	std::sort(ladders.begin(), ladders.end());
	return ladders;
}