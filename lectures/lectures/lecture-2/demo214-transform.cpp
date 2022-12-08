// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <vector>

char to_upper(unsigned char value) {
	return static_cast<char>(std::toupper(static_cast<unsigned char>(value)));
}

int main() {
	std::string s = "hello world";
	// Algorithms like transform, which have output iterators,
	// use the other iterator as an output.
	auto upper = std::string(s.size(), '\0');
	std::transform(s.begin(), s.end(), upper.begin(), to_upper);
}
