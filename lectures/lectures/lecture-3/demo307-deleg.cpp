#include <string>

class dummy {
public:
	dummy(int const& i)
	: s_{"Hello world"}
	, val_{i} {}

	dummy()
	: dummy(5) {}
	std::string const& get_s() {
		return s_;
	}
	int get_val() {
		return val_;
	}

private:
	std::string s_;
	const int val_;
};

auto main() -> int {
	dummy d1(5);
	dummy d2{};
}