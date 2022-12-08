// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <vector>

int main() {
	std::string s = "hello world";
	// std::for_each modifies each element
	std::for_each(s.begin(), s.end(), [](char& value) {
		value = static_cast<char>(std::toupper(static_cast<unsigned char>(value)));
	});
}
