// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>

int main() {
	auto i = 1;
	std::cout << i << "\n";

	auto& j = i;
	j = 3;

	// prints "3 3"
	std::cout << i << " " << j << "\n";

	auto k = 1;
	auto const& ref = k;
	std::cout << ref << '\n';
	k++; // This is fine
	std::cout << ref << '\n';
	// ref++; // This is not OK

	auto const m = 1;
	auto const& mref = m; // this is allowed
	// auto& ref2 = m; // not allowed
	std::cout << mref << "\n";
}
