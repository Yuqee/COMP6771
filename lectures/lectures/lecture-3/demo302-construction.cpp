#include <vector>

auto main() -> int {
	// Always use auto on the left for this course, but you may see this elsewhere.
	std::vector<int> v11; // Calls 0-argument constructor. Creates empty vector.

	// There's no difference between these:
	// T variable = T{arg1, arg2, ...}
	// T variable{arg1, arg2, ...}
	auto v12 = std::vector<int>{}; // No different to first
	auto v13 = std::vector<int>(); // No different to the first

	{
		auto v2 = std::vector<int>{v11.begin(), v11.end()}; // A copy of v11.
		auto v3 = std::vector<int>{v2}; // A copy of v2.
	} // v2 and v3 destructors are called here

	auto v41 = std::vector<int>{5, 2}; // Initialiser-list constructor {5, 2}
	auto v42 = std::vector<int>(5, 2); // Count + value constructor (5 * 2 => {2, 2, 2, 2, 2})
} // v11, v12, v13, v41, v42 destructors called here