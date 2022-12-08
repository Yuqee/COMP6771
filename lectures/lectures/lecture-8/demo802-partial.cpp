#include "./demo802-partial.h"

auto main() -> int {
	auto i1 = 6771;
	auto i2 = 1917;

	auto s1 = stack<int>{};
	s1.push(i1);
	s1.push(i2);
	std::cout << s1.size() << " ";
	std::cout << s1.top() << " ";
	std::cout << s1.sum() << "\n";

	auto s2 = stack<int*>{};
	s2.push(&i1);
	s2.push(&i2);
	std::cout << s2.size() << " ";
	std::cout << *(s2.top()) << " ";
	std::cout << s2.sum() << "\n";
}
