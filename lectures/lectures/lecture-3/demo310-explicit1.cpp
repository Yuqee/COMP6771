class age {
public:
	age(int age)
	: age_{age} {}

private:
	int age_;
};

auto main() -> int {
	// Explicitly calling the constructor
	age a1{20};

	// Explicitly calling the constructor
	auto a2 = age{20};

	// Attempts to use an integer
	// where an age is expected.
	// Implicit conversion done.
	// This seems reasonable.
	age a3 = 20;
}
