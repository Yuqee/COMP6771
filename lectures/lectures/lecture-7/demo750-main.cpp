#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>

#include "./demo750-intstack.h"

int main() {
	IntStack l;
	l.push(5);
	l.push(4);
	l.push(3);
	l.push(2);
	l.push(1);

	std::cout << std::boolalpha;
	std::cout << "Head is " << l.top() << '\n';
	l.pop();
	std::cout << "After popping, head is " << l.top() << '\n';

	std::cout << "Algorithms\n";
	std::copy(begin(l), end(l), std::ostream_iterator<int>{std::cout, "\n"});

	auto check_present = [&](int value) {
		std::cout << "Is " << value << " present: " << (std::find(begin(l), end(l), 5) != end(l))
		          << '\n';
	};
	check_present(5);
	check_present(99);
	(*begin(l)) = 99;
	check_present(99);

	// TODO(lecture): This should fail to compile
	(*cbegin(l)) = 100;

	std::cout << "Range-for\n";
	for (const auto& item : l) {
		std::cout << item << '\n';
	}
}