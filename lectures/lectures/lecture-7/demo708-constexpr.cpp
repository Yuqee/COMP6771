#include <iostream>

// This can be called at compile time, or at runtime
constexpr int constexpr_factorial(int n) {
	return n <= 1 ? 1 : n * constexpr_factorial(n - 1);
}

// This may not be called at compile time
int factorial(int n) {
	return n <= 1 ? 1 : n * factorial(n - 1);
}

auto main() -> int {
	// Beats a #define any day.
	constexpr int max_n = 10;

	constexpr int tenfactorial = constexpr_factorial(10);

	// This will fail to compile
	int ninefactorial = factorial(9);

	std::cout << max_n << "\n";
	std::cout << tenfactorial << "\n";
	std::cout << ninefactorial << "\n";
}