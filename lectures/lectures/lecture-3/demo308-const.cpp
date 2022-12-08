#include <iostream>
#include <string>

class person {
public:
	explicit person(std::string const& name)
	: name_{name} {}
	auto set_name(std::string const& name) -> void {
		name_ = name;
	}
	[[nodiscard]] auto get_name() const -> std::string const& {
		return name_;
	}

private:
	std::string name_;
};

auto main() -> int {
	auto const p1 = person{"Hayden"};
	std::cout << p1.get_name() << "\n";
}