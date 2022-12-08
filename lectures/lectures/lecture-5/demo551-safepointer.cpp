#include <iostream>

class my_int_pointer {
public:
	// This is the constructor
	explicit my_int_pointer(int* value);

	// This is the destructor
	~my_int_pointer();

	int* value();

private:
	int* value_;
};

my_int_pointer::my_int_pointer(int* value)
: value_(value) {}

int* my_int_pointer::value() {
	return value_;
}

my_int_pointer::~my_int_pointer() {
	// Similar to C's free function.
	delete value_; // free(value_);
}

auto main() -> int {
	// Similar to C's malloc
	int* j = new int{5};
	auto p = my_int_pointer(j);

	std::cout << *(p.value()) << "\n";
	// Copy the pointer;
	// auto q = my_int_pointer(p.value());
	// p and q are both now destructed.
	// What happens?
}