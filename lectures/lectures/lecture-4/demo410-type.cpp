#include "./demo410-type.h"

#include <iostream>
#include <vector>
int main() {
	auto const p = point(1, 2);
	auto vec = std::vector<int>(p); // explicit
	std::cout << vec.at(0) << '\n';
	std::cout << vec.at(1) << '\n';
}