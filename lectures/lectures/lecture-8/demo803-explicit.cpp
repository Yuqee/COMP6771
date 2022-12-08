#include <iostream>

template<typename T>
struct is_void {
	static bool const val = false;
};

template<>
struct is_void<void> {
	static bool const val = true;
};

auto main() -> int {
	std::cout << is_void<int>::val << "\n";
	std::cout << is_void<void>::val << "\n";
}