#include <iostream>
#include <memory>

int main() {
	auto up1 = std::unique_ptr<int>{new int{0}};
	*up1 = 5;
	std::cout << *up1 << "\n";
	auto op1 = up1.get();
	*op1 = 6;
	std::cout << *op1 << "\n";
	up1.reset();
	std::cout << *op1 << "\n";
}