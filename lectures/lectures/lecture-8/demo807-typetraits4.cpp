#include <iostream>
#include <type_traits>

template<typename T>
auto testIfNumberType(T i) -> void {
	if (std::is_integral<T>::value || std::is_floating_point<T>::value) {
		std::cout << i << " is a number"
		          << "\n";
	}
	else {
		std::cout << i << " is not a number"
		          << "\n";
	}
}

auto main() -> int {
	auto i = int{6};
	auto l = long{7};
	auto d = double{3.14};
	testIfNumberType(i);
	testIfNumberType(l);
	testIfNumberType(d);
	testIfNumberType(123);
	testIfNumberType("Hello");
	auto s = "World";
	testIfNumberType(s);
}