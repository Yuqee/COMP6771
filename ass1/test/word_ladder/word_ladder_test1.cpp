//
//  Copyright UNSW Sydney School of Computer Science and Engineering
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include <comp6771/word_ladder.hpp>

#include <string>
#include <vector>

#include <catch2/catch.hpp>

TEST_CASE("at -> it") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");
	auto const ladders = word_ladder::generate("at", "it", english_lexicon);

	REQUIRE(std::size(ladders) == 1);
	CHECK(std::is_sorted(ladders.begin(), ladders.end()));

	CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"at", "it"}) == 1);
}

// Derived from the spec of ass1, test forward, test backward.
TEST_CASE("cat -> dog") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");
	auto const ladders = word_ladder::generate("cat", "dog", english_lexicon);

	REQUIRE(std::size(ladders) == 2);
	REQUIRE(std::is_sorted(ladders.begin(), ladders.end()));

	CHECK(
	   std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"cat", "cot", "cog", "dog"})
	   == 1);
	CHECK(
	   std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"cat", "cot", "dot", "dog"})
	   == 1);
}

TEST_CASE("dog -> cat") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");
	auto const ladders = word_ladder::generate("dog", "cat", english_lexicon);

	REQUIRE(std::size(ladders) == 2);
	REQUIRE(std::is_sorted(ladders.begin(), ladders.end()));

	CHECK(
	   std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"dog", "cog", "cot", "cat"})
	   == 1);
	CHECK(
	   std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"dog", "dot", "cot", "cat"})
	   == 1);
}

// Derived from the spec of ass1.
TEST_CASE("code -> data") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");
	auto const ladders = word_ladder::generate("code", "data", english_lexicon);

	REQUIRE(std::size(ladders) == 3);
	for (auto& l : ladders)
		REQUIRE(std::size(l) == 5);
	REQUIRE(std::is_sorted(ladders.begin(), ladders.end()));

	std::vector<std::string> l1 = {"code", "cade", "cate", "date", "data"};
	std::vector<std::string> l2 = {"code", "cote", "cate", "date", "data"};
	std::vector<std::string> l3 = {"code", "cote", "dote", "date", "data"};
	CHECK(std::count(ladders.begin(), ladders.end(), l1) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l2) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l3) == 1);
}

// Derived from the spec of ass1.
TEST_CASE("work -> play") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");
	auto const ladders = word_ladder::generate("work", "play", english_lexicon);

	REQUIRE(std::size(ladders) == 12);
	for (auto& l : ladders)
		REQUIRE(std::size(l) == 7);
	REQUIRE(std::is_sorted(ladders.begin(), ladders.end()));

	std::vector<std::string> l1 = {"work", "fork", "form", "foam", "flam", "flay", "play"};
	std::vector<std::string> l2 = {"work", "pork", "perk", "peak", "pean", "plan", "play"};
	std::vector<std::string> l3 = {"work", "pork", "perk", "peak", "peat", "plat", "play"};
	std::vector<std::string> l4 = {"work", "pork", "perk", "pert", "peat", "plat", "play"};
	std::vector<std::string> l5 = {"work", "pork", "porn", "pirn", "pian", "plan", "play"};
	std::vector<std::string> l6 = {"work", "pork", "port", "pert", "peat", "plat", "play"};
	std::vector<std::string> l7 = {"work", "word", "wood", "pood", "plod", "ploy", "play"};
	std::vector<std::string> l8 = {"work", "worm", "form", "foam", "flam", "flay", "play"};
	std::vector<std::string> l9 = {"work", "worn", "porn", "pirn", "pian", "plan", "play"};
	std::vector<std::string> l10 = {"work", "wort", "bort", "boat", "blat", "plat", "play"};
	std::vector<std::string> l11 = {"work", "wort", "port", "pert", "peat", "plat", "play"};
	std::vector<std::string> l12 = {"work", "wort", "wert", "pert", "peat", "plat", "play"};
	CHECK(std::count(ladders.begin(), ladders.end(), l1) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l2) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l3) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l4) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l5) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l6) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l7) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l8) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l9) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l10) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l11) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l12) == 1);
}

// Derived from the spec of ass1.
TEST_CASE("awake -> sleep") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");
	auto const ladders = word_ladder::generate("awake", "sleep", english_lexicon);

	REQUIRE(std::size(ladders) == 2);
	for (auto& l : ladders)
		REQUIRE(std::size(l) == 10);
	REQUIRE(std::is_sorted(ladders.begin(), ladders.end()));

	std::vector<std::string> l1 =
	   {"awake", "aware", "sware", "share", "sharn", "shawn", "shewn", "sheen", "sheep", "sleep"};
	std::vector<std::string> l2 =
	   {"awake", "aware", "sware", "share", "shire", "shirr", "shier", "sheer", "sheep", "sleep"};
	CHECK(std::count(ladders.begin(), ladders.end(), l1) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l2) == 1);
}

TEST_CASE("airplane -> tricycle") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");
	auto const ladders = word_ladder::generate("airplane", "tricycle", english_lexicon);

	REQUIRE(std::size(ladders) == 0);
}

TEST_CASE("charge -> comedo") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");
	auto const ladders = word_ladder::generate("charge", "comedo", english_lexicon);

	REQUIRE(std::size(ladders) == 4);
	for (auto& l : ladders)
		REQUIRE(std::size(l) == 23);

	std::vector<std::string> l1 = {"charge", "change", "changs", "chants", "chints", "chines",
	                               "chined", "coined", "coiner", "conner", "conger", "conges",
	                               "conies", "conins", "coning", "coming", "homing", "hominy",
	                               "homily", "homely", "comely", "comedy", "comedo"};
	std::vector<std::string> l2 = {"charge", "change", "changs", "chants", "chints", "chines",
	                               "chined", "coined", "coiner", "conner", "conger", "conges",
	                               "conies", "conins", "coning", "honing", "homing", "hominy",
	                               "homily", "homely", "comely", "comedy", "comedo"};
	std::vector<std::string> l3 = {"charge", "change", "changs", "chants", "chints", "chines",
	                               "chined", "coined", "conned", "conner", "conger", "conges",
	                               "conies", "conins", "coning", "coming", "homing", "hominy",
	                               "homily", "homely", "comely", "comedy", "comedo"};
	std::vector<std::string> l4 = {"charge", "change", "changs", "chants", "chints", "chines",
	                               "chined", "coined", "conned", "conner", "conger", "conges",
	                               "conies", "conins", "coning", "honing", "homing", "hominy",
	                               "homily", "homely", "comely", "comedy", "comedo"};
	CHECK(std::count(ladders.begin(), ladders.end(), l1) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l2) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l3) == 1);
	CHECK(std::count(ladders.begin(), ladders.end(), l4) == 1);
}

// Derived from the spec of ass1 and ed
TEST_CASE("atlases -> cabaret") {
	auto const english_lexicon = ::word_ladder::read_lexicon("english.txt");
	auto const ladders = ::word_ladder::generate("atlases", "cabaret", english_lexicon);

	REQUIRE(std::size(ladders) == 840);
	for (auto& l : ladders)
		REQUIRE(std::size(l) == 58);
}