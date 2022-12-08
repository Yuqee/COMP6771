#include <iostream>

template<typename T>
auto min(T a, T b) -> T {
	return a < b ? a : b;
}

auto main() -> int {
	std::cout << min(1, 2) << "\n"; // calls int min(int, int)
	std::cout << min(1.0, 2.0) << "\n"; // calls double min(double, double)
}