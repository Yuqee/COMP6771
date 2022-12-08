// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <vector>

char to_upper(char value) {
	return static_cast<char>(std::toupper(static_cast<unsigned char>(value)));
}

int main() {
	std::string s = "hello world";
	// std::for_each modifies each element
	std::for_each(s.begin(), s.end(), toupper);

	std::string upper;
	// std::transform adds to third iterator.
	std::transform(s.begin(), s.end(), std::back_inserter(upper), to_upper);
}
