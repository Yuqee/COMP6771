#include <iostream>
#include <string>

class BaseClass {
public:
	virtual ~BaseClass() {}
	int get_member() {
		return member_;
	}
	virtual std::string get_class_name() {
		return "BaseClass";
	};

private:
	int member_;
};

class SubClass : public BaseClass {
public:
	std::string get_class_name() override {
		(void)subclass_data_;
		return "SubClass";
	}

private:
	int subclass_data_;
};

void print_class_name(BaseClass& base) {
	std::cout << base.get_class_name() << ' ' << base.get_member() << '\n';
}

int main() {
	BaseClass base_class;
	SubClass subclass;
	print_class_name(base_class);
	print_class_name(subclass);
}