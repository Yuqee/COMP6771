#include <iostream>
#include <vector>

int* newInt(int i) {
	int* a = new int{i};
	return a;
}

int main() {
	int* myInt = newInt();
	std::cout << *a << "\n"; // a was defined in a scope that
	                         // no longer exists
	delete a;
	return 0;
}