#include <iostream>
#include <memory>
#include <string>

class BaseClass {
public:
	virtual std::string get_class_name() {
		return "BaseClass";
	};

	~BaseClass() {
		std::cout << "Destructing base class\n";
	}
};

class SubClass : public BaseClass {
public:
	std::string get_class_name() override {
		return "SubClass";
	}

	~SubClass() {
		std::cout << "Destructing subclass\n";
	}
};

void print_stuff(BaseClass& base_class) {
	std::cout << base_class.get_class_name() << '\n';
}

int main() {
	auto subclass = static_cast<std::unique_ptr<BaseClass>>(std::make_unique<SubClass>());
	std::cout << subclass->get_class_name();
}