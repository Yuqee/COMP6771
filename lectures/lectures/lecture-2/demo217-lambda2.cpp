// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <vector>

void add_n(std::vector<int>& v, int n) {
	std::for_each(v.begin(), v.end(), [n](int& val) { val = val + n; });
}

int main() {
	std::vector<int> v{1, 2, 3};
	add_n(v, 3);
}
