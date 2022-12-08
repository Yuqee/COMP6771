#include <vector>

class intvec {
public:
	// This one allows the implicit conversion
	// intvec(std::vector<int>::size_type length)
	// : vec_(length, 0);

	// This one disallows it.
	explicit intvec(std::vector<int>::size_type length)
	: vec_(length, 0) {}

private:
	std::vector<int> vec_;
};

auto main() -> int {
	int const size = 20;
	// Explictly calling the constructor.
	intvec container1{size}; // Construction
	intvec container2 = intvec{size}; // Assignment

	// Implicit conversion.
	// Probably not what we want.
	// intvec container3 = size;
}
