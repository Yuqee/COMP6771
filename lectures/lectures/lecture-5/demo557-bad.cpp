#include <exception>

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

class unsafe_class {
public:
	unsafe_class(int a, int b)
	: a_{new my_int{a}}
	, b_{new my_int{b}} {}

	~unsafe_class() {
		delete a_;
		delete b_;
	}

private:
	my_int* a_;
	my_int* b_;
};

int main() {
	auto a = unsafe_class(1, 2);
}