#include <array>

auto findmin(const std::array<int, 3> a) -> int {
	int min = a[0];
	for (std::size_t i = 1; i < 3; ++i) {
		if (a[i] < min)
			min = a[i];
	}
	return min;
}

auto findmin(const std::array<double, 4> a) -> double {
	double min = a[0];
	for (std::size_t i = 1; i < 4; ++i) {
		if (a[i] < min)
			min = a[i];
	}
	return min;
}

int main() {}