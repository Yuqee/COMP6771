#include <iostream>

class myclass {
public:
	myclass(int i) {
		i_ = i;
	}
	int getval() {
		return i_;
	}

private:
	int i_;
};

int main() {
	auto mc = myclass{1};
	std::cout << mc.getval() << "\n";
}