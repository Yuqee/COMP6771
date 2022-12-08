#include <iostream>
#include <memory>
#include <vector>

class BaseClass {
public:
	BaseClass(int member)
	: int_member_(member) {}

	~BaseClass() {
		std::cout << "Destructing base with member " << int_member_ << '\n';
	}

	int get_member() {
		return int_member_;
	}

	std::string get_class_name() {
		return "BaseClass";
	}

private:
	int int_member_;
};

class DerivedClass : public BaseClass {
public:
	DerivedClass([[maybe_unused]] int member, std::unique_ptr<int> ptr)
	: BaseClass(member)
	, ptr_member_(std::move(ptr)) {}

	~DerivedClass() {
		std::cout << "Destructing DerivedClass with member " << *ptr_member_ << '\n';
	}

	std::string GetClassName() {
		return "DerivedClass";
	}

	int GetMember() {
		return *ptr_member_;
	}

private:
	std::unique_ptr<int> ptr_member_;
};

void print_stuff(BaseClass& base) {
	std::cout << "Size is " << sizeof(base) << ", class name is " << base.get_class_name()
	          << ", member is " << base.get_member() << '\n';
}

auto main() -> int {
	{
		auto base = BaseClass(1);
		auto derived = DerivedClass(9001, std::make_unique<int>(9002));
		std::cout << "Size of base is " << sizeof(base) << '\n';
		std::cout << "Size of derived is " << sizeof(derived) << '\n';
		// print_stuff(base);
		// print_stuff(derived);
	}

	// {
	// 	std::cout << "Vector section\n";
	// 	auto vec = std::vector<BaseClass>();
	// 	vec.push_back(BaseClass(3));
	// 	vec.push_back(DerivedClass(9003, std::make_unique<int>(9004)));
	// 	print_stuff(vec[0]);
	// 	print_stuff(vec[1]);
	// 	std::cout << "Destructing vector\n";
	// }

	// {
	// 	std::cout << "Static and dynamic types.";
	// 	auto base = BaseClass(1);
	// 	auto derived = DerivedClass(2, std::make_unique<int>(3));
	// 	// Which of these lines will actually compile?
	// 	// The following could all be replaced with pointers
	// 	// and have the same effect.
	// 	[[maybe_unused]] BaseClass const& base_to_base{base};
	// 	[[maybe_unused]] BaseClass const& base_to_derived{derived};
	// 	[[maybe_unused]] DerivedClass const& derived_to_base{base};
	// 	[[maybe_unused]] DerivedClass const& derived_to_derived{derived};
	// 	[[maybe_unused]] DerivedClass const& derived_to_base_to_derived{base_to_derived};
	// 	auto copy = base_to_derived;
	// }
}
