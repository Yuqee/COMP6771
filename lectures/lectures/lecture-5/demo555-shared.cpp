#include <iostream>
#include <memory>

auto main() -> int {
	auto x = std::make_shared<int>(5);
	auto y = x;
	std::cout << "use count: " << x.use_count() << "\n";
	std::cout << "value: " << *x << "\n";
	x.reset(); // Memory still exists, due to y.
	std::cout << "use count: " << y.use_count() << "\n";
	std::cout << "value: " << *y << "\n";
	y.reset(); // Deletes the memory, since
	// no one else owns the memory
	std::cout << "use count: " << x.use_count() << "\n";
	std::cout << "value: " << *y << "\n";
}