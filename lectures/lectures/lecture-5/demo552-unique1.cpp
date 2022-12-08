#include <iostream>
#include <memory>

int main() {
	auto up1 = std::unique_ptr<int>{new int};
	// auto up2 = up1; // no copy constructor
	std::unique_ptr<int> up3;
	//	up3 = up2; // no copy assignment

	up3.reset(up1.release()); // OK
	auto up4 = std::move(up3); // OK
	std::cout << up4.get() << "\n";
	std::cout << *up4 << "\n";
	std::cout << *up1 << "\n";
}