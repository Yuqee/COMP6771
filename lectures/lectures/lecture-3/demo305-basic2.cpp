#include <iostream>
#include <string>

class person {
public:
	person()
	: name_{"hayden"}
	, age_{99} {}
	auto get_name() -> std::string const&;
	auto get_age() -> int const&;

private:
	std::string name_;
	int const age_;
};

auto person::get_name() -> std::string const& {
	return name_;
}

auto person::get_age() -> int const& {
	return age_;
}

auto main() -> int {
	auto p = person();
	std::cout << p.get_name() << "\n";
}