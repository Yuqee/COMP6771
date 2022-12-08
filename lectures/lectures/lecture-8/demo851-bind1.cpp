#include <iostream>

auto print(std::string const& a) -> void {
	std::cout << a << "\n";
}

auto goo() -> std::string const {
	return "C++";
}

auto main() -> int {
	auto j = std::string{"C++"};
	auto const& k = "C++";
	print("C++"); // rvalue
	print(goo()); // rvalue
	print(j); // lvalue
	print(k); // const lvalue
}