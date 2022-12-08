// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef COMP6771_LECTURE2_CARDS_HPP
#define COMP6771_LECTURE2_CARDS_HPP

#include <compare>
#include <vector>

namespace comp6771 {
	enum class colour { red, green, blue, yellow };
	enum class value { number, draw_two, draw_four, reverse, skip };

	struct card {
		colour colour;
		value value;

		friend auto operator==(card, card) -> bool = default;
		friend auto operator<=>(card, card) = default;
	};

	inline constexpr auto red_number = card{colour::red, value::number};
	inline constexpr auto blue_number = card{colour::blue, value::number};
	inline constexpr auto green_draw_two = card{colour::green, value::draw_two};
	inline constexpr auto blue_skip = card{colour::blue, value::skip};
	inline constexpr auto yellow_draw_four = card{colour::yellow, value::draw_four};

	inline auto deal_hand() -> std::vector<card> {
		return std::vector<card>{
		   red_number,
		   blue_number,
		   green_draw_two,
		   blue_number,
		   blue_skip,
		   yellow_draw_four,
		   blue_number,
		   blue_number,
		   blue_skip,
		};
	}
} // namespace comp6771

#endif // COMP6771_LECTURE2_CARDS_HPP
