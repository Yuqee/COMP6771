// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <limits>

int main() {
	std::cout << std::numeric_limits<int>::max() << "\n";
	std::cout << std::numeric_limits<int>::min() << "\n";
	std::cout << std::numeric_limits<double>::max() << "\n";
	std::cout << std::numeric_limits<double>::min() << "\n";
}
