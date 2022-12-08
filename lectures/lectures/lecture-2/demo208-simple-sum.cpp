// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <vector>

int main() {
	std::vector<int> nums{1, 2, 3, 4, 5};

	int sum = 0;

	// Internally, this uses begin and end,
	// but it abstracts it away.
	for (const auto& i : nums) {
		sum += i;
	}

	std::cout << sum << "\n";
}