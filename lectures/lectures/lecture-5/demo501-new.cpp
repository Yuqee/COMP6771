#include <iostream>
#include <vector>

int main() {
	int* a = new int{4};
	std::vector<int>* b = new std::vector<int>{1, 2, 3};
	std::cout << *a << "\n";
	std::cout << (*b)[0] << "\n";
	delete a;
	delete b;
	return 0;
}