#include <iostream>
#include <memory>

auto main() -> int {
	auto x = std::make_shared<int>(1);

	auto wp = std::weak_ptr<int>(x); // x owns the memory

	auto y = wp.lock();
	if (y != nullptr) { // x and y own the memory
		// Do something with y
		std::cout << "Attempt 1: " << *y << '\n';
	}
}