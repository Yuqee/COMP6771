#include <iostream>

int i = 1;
int main() {
	std::cout << i << "\n";
	if (i > 0) {
		int i = 2;
		std::cout << i << "\n";
		{
			int i = 3;
			std::cout << i << "\n";
		}
		std::cout << i << "\n";
	}
	std::cout << i << "\n";
}