#include <iostream>
#include <vector>

auto main() -> int {
	std::cout << "Enter -1 to quit\n";
	std::vector<int> items{97, 84, 72, 65};
	std::cout << "Enter an index: ";
	for (int print_index; std::cin >> print_index;) {
		if (print_index == -1)
			break;
		try {
			std::cout << items.at(static_cast<unsigned int>(print_index)) << '\n';
			items.resize(items.size() + 10);
		} catch (const std::out_of_range& e) {
			std::cout << "Index out of bounds\n";
		} catch (...) {
			std::cout << "Something else happened";
		}
		std::cout << "Enter an index: ";
	}
}