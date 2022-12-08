#include <iostream>
#include <type_traits>

template<typename T1, typename T2>
auto print_is_same() -> void {
	std::cout << std::is_same<T1, T2>() << "\n";
}

auto main() -> int {
	std::cout << std::boolalpha;
	print_is_same<int, int>();
	// true
	print_is_same<int, int&>(); // false
	print_is_same<int, int&&>(); // false
	print_is_same<int, std::remove_reference<int>::type>();
	// true
	print_is_same<int, std::remove_reference<int&>::type>(); // true
	print_is_same<int, std::remove_reference<int&&>::type>(); // true
	print_is_same<const int, std::remove_reference<const int&&>::type>(); // true
}