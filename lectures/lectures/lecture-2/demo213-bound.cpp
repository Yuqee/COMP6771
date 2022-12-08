// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

int main() {
	// Lower bound does a binary search, and returns the first value >= the argument.
	std::vector<int> sortedVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::lower_bound(sortedVec.begin(), sortedVec.end(), 5);

	std::list<int> sortedLinkedList{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::lower_bound(sortedLinkedList.begin(), sortedLinkedList.end(), 5);
}
