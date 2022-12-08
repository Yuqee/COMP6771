#include <iostream>
#include <memory>

auto main() -> int {
	// 1 - Worst - you can accidentally own the resource multiple
	// times, or easily forget to own it.
	// auto* silly_string = new std::string{"Hi"};
	// auto up1 = std::unique_ptr<std::string>(silly_string);
	// auto up11 = std::unique_ptr<std::string>(silly_string);

	// 2 - Not good - requires actual thinking about whether there's a leak.
	auto up2 = std::unique_ptr<std::string>(new std::string("Hello"));

	// 3 - Good - no thinking required.
	auto up3 = std::make_unique<std::string>("Hello");

	std::cout << *up2 << "\n";
	std::cout << *up3 << "\n";
	// std::cout << *(up3.get()) << "\n";
	// std::cout << up3->size();
}