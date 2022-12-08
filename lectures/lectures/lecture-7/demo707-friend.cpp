#include <iostream>
#include <string>

#include "./demo707-friend.h"

auto main() -> int {
	stack<std::string> ss;
	ss.push("Hello");
	std::cout << ss << "\n";
	stack<int> is;
	is.push(5);
	std::cout << is << "\n";
}