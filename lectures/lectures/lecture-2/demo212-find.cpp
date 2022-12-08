// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
	std::vector<int> nums{1, 2, 3, 4, 5};

	auto it = std::find(nums.begin(), nums.end(), 4);

	if (it != nums.end()) {
		std::cout << "Found it!"
		          << "\n";
	}
}
