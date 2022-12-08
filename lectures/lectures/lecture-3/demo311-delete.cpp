#include <vector>

class intvec {
public:
	// intvec() = default;

	// This one allows the implicit conversion
	explicit intvec(std::vector<int>::size_type length)
	: vec_(length, 0) {}

	// intvec(intvec const& v) = delete;

private:
	std::vector<int> vec_;
};

auto main() -> int {
	auto a = std::vector<int>{4};
	// auto a = intvec{};
	auto b = intvec{a.size()};
	// intvec b{a}; // Will this work?
}