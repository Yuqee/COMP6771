#include <exception>
#include <memory>

class my_int {
public:
	my_int(int const i)
	: i_{i} {
		if (i == 2) {
			throw std::exception();
		}
	}

private:
	int i_;
};

class safe_class {
public:
	safe_class(int a, int b)
	: a_(std::make_unique<my_int>(a))
	, b_(std::make_unique<my_int>(b)) {}

private:
	std::unique_ptr<my_int> a_;
	std::unique_ptr<my_int> b_;
};

int main() {
	auto a = safe_class(1, 2);
}