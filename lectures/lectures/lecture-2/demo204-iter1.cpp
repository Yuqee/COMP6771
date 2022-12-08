// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <string>
#include <vector>

int main() {
	std::vector<std::string> names;
	for (auto iter = names.begin(); iter != names.end(); ++iter) {
		std::cout << *iter << "\n";
	}
	for (std::vector<std::string>::iterator iter = names.begin(); iter != names.end(); ++iter) {
		std::cout << *iter << "\n";
	}
}