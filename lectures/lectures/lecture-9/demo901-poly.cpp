#include <iostream>
#include <string>

class BaseClass {
public:
	int get_member() {
		return member_;
	}
	std::string get_class_name() {
		return "BaseClass";
	};

private:
	int member_;
};

class SubClass : public BaseClass {
public:
	std::string get_class_name() {
		(void)subclass_data_;
		return "SubClass";
	}

private:
	int subclass_data_;
};

void print_class_name(BaseClass base) {
	std::cout << base.get_class_name() << ' ' << base.get_member() << '\n';
}

int main() {
	BaseClass base_class;
	SubClass subclass;
	print_class_name(base_class);
	print_class_name(subclass);
}