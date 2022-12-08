#include <iostream>
#include <vector>

auto main() -> int {
	std::cout << "Enter -1 to quit\n";
	auto item = std::vector<int>{0, 0, 0, 0};
	std::cout << "Enter an index: ";
	for (int print_index; std::cin >> print_index;) {
		if (print_index == -1) {
			break;
		}
		std::cout << item.at(static_cast<std::vector<int>::size_type>(print_index)) << '\n';
		std::cout << "Enter an index: ";
	}
}