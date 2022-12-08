#include <iostream>
#include <string>

class myclass {
public:
	myclass(int i)
	: i_{i} {}
	int getval() {
		return i_;
	}

private:
	int i_;
};

int main() {
	auto mc = myclass{5};
	std::cout << mc.getval() << "\n";
}