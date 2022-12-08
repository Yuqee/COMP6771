// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <vector>

int main() {
	std::vector<int> nums{1, 2, 3, 4, 5};

	auto sum = 0;
	for (auto it = nums.begin(); it != nums.end(); ++it) {
		sum += *it;
	}
	std::cout << sum << "\n";
}