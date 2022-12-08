#include <array>
#include <iostream>
#include <limits>

template<typename T, std::size_t size>
T findMax(const std::array<T, size>& arr) {
	T largest = std::numeric_limits<T>::min();
	for (auto const& i : arr) {
		if (i > largest)
			largest = i;
	}
	return largest;
}

auto main() -> int {
	auto i = std::array<int, 3>{-1, -2, -3};
	std::cout << findMax<int, 3>(i) << "\n";
	auto j = std::array<double, 3>{1.0, 1.1, 1.2};
	std::cout << findMax<double, 3>(j) << "\n";
}