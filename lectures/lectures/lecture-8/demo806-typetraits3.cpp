#include <iostream>

template<typename T>
struct is_pointer {
	static const bool val = false;
};

template<typename T>
struct is_pointer<T*> {
	static const bool val = true;
};

auto main() -> int {
	std::cout << is_pointer<int*>::val << "\n";
	std::cout << is_pointer<int>::val << "\n";
}