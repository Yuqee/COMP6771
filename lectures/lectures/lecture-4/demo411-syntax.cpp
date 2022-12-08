#include <iostream>
class stringptr {
public:
	explicit stringptr(std::string const& s)
	: ptr_{new std::string(s)} {}
	~stringptr() {
		delete ptr_;
	}
	auto operator->() const -> std::string* {
		return ptr_;
	}
	auto operator*() const -> std::string& {
		return *ptr_;
	}

private:
	std::string* ptr_;
};

auto main() -> int {
	auto p = stringptr("smart pointer");
	std::cout << *p << '\n';
	std::cout << p->size() << '\n';
}