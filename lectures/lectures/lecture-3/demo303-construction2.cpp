#include <iostream>

double f() {
	return 1.1;
}

int main() {
	// One of the reasons we do auto is to avoid ununitialized values.
	// int n; // Not initialized (memory contains previous value)

	int n21{}; // Default constructor (memory contains 0)
	auto n22 = int{}; // Default constructor (memory contains 0)
	auto n3{5};

	// Not obvious you know that f() is not an int, but the compiler lets it through.
	// int n43 = f();

	// Not obvious you know that f() is not an int, and the compiler won't let you (narrowing
	// conversion)
	// auto n41 = int{f()};

	// Good code. Clear you understand what you're doing.
	auto n42 = static_cast<int>(f());

	// std::cout << n << "\n";
	std::cout << n21 << "\n";
	std::cout << n22 << "\n";
	std::cout << n3 << "\n";
	std::cout << n42 << "\n";
}