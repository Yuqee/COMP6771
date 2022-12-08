// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <limits>
#include <vector>

int main() {
	auto i = 0; // i is an int
	auto j = 8.5; // j is a double
	// auto k; // this would not work as there is no RHS to infer from
	std::vector<int> f;
	auto k = f; // k is std::vector<int> (a copy of one)
	k.push_back(5);
	std::cout << k.size() << "\n";
	std::cout << i << " " << j << "\n";
}
