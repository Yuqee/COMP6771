#include <iostream>

class Base {
public:
	virtual ~Base() = default;
	virtual void print_num(int i = 1) {
		std::cout << "Base " << i << '\n';
	}
};

class Derived : public Base {
public:
	void print_num(int i = 2) override {
		std::cout << "Derived " << i << '\n';
	}
};

int main() {
	Derived derived;
	Base* base = &derived;
	derived.print_num(); // Prints "Derived 2"
	base->print_num(); // Prints "Derived 1"
}