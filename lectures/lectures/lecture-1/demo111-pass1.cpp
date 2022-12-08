// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>

auto swap(int x, int y) -> void {
	auto const tmp = x;
	x = y;
	y = tmp;
}

auto main() -> int {
	auto i = 1;
	auto j = 2;
	std::cout << i << ' ' << j << '\n'; // prints 1 2
	swap(i, j);
	std::cout << i << ' ' << j << '\n'; // prints 1 2... not swapped?
}