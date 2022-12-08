#include <iostream>

auto min(int a, int b) -> int {
	return a < b ? a : b;
}

auto min(double a, double b) -> double {
	return a < b ? a : b;
}

auto main() -> int {
	std::cout << min(1, 2) << "\n"; // calls line 1
	std::cout << min(1.0, 2.0) << "\n"; // calls line 4
}