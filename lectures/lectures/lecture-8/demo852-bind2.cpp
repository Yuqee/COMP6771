#include <iostream>

template<typename T>
auto print(T&& a) -> void {
	std::cout << a << "\n";
}

auto goo() -> std::string const {
	return "Test";
}

auto main() -> int {
	auto j = int{1};
	auto const& k = 1;

	print(1); // rvalue,       foo(int&&)
	print(goo()); // rvalue        foo(const int&&)
	print(j); // lvalue        foo(int&)
	print(k); // const lvalue  foo(const int&)
}