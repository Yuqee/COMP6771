#include <iostream>
#include <typeinfo>

template<typename T>
auto print(const T& msg) -> void {
	std::cout << msg << " ";
}

template<typename A, typename... B>
auto print(A head, B... tail) -> void {
	print(head);
	print(tail...);
}

auto main() -> int {
	print(1, 2.0f);
	std::cout << "\n";
	print(1, 2.0f, "Hello");
	std::cout << "\n";
}