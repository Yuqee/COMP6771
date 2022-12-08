#include <iostream>
#include <string>

void fn(std::string const& param) {
	std::cout << "Called lvalue overload from parameter " << param << '\n';
}

void fn(std::string&& param) {
	std::cout << "Called rvalue overload from parameter " << param << '\n';
}

template<typename T>
void wrapper(T value) {
	fn(value);
}

void variadic() {}

template<typename T, typename... Args>
void variadic(T head, Args... args) {
	wrapper(head);
	variadic(args...);
}

auto main() -> int {
	auto lvalue = std::string("lvalue");
	wrapper(lvalue);
	wrapper(std::string("rvalue"));
	variadic(lvalue, std::string("rvalue"));
}