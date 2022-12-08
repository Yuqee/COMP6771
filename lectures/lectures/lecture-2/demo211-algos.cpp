// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <numeric>
#include <vector>

int main() {
	std::vector<int> v{1, 2, 3, 4, 5};
	int sum = std::accumulate(v.begin(), v.end(), 0);

	// What is the type of std::multiplies<int>()
	int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());

	auto midpoint = v.begin() + (v.size() / 2);
	// This looks a lot harder to read. Why might it be better?
	// auto midpoint2 = std::next(v.begin(), std::distance(v.begin(), v.end()) / 2);

	int sum2 = std::accumulate(v.begin(), midpoint, 0);

	std::cout << product << "\n";
	std::cout << sum << "\n";
	std::cout << sum2 << "\n";
}
