#include <iostream>
#include <string>

class user {
public:
	explicit user(std::string const& name)
	: name_{name} {}
	static auto valid_name(std::string const& name) -> bool {
		return name.length() < 20;
	}

private:
	std::string name_;

public:
	inline static int MAX_NAME_LENGTH_ = 20;
};

auto main() -> int {
	auto n = std::string{"Hayden Chris"};
	std::cout << user::MAX_NAME_LENGTH_ << "\n";
	std::cout << std::string::npos << "\n";
}