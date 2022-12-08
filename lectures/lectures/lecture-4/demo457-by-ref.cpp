#include <iostream>

class Giraffe {
public:
	Giraffe() {
		std::cout << "Giraffe constructed" << '\n';
	}
	Giraffe(const Giraffe& g) {
		(void)g;
		std::cout << "Giraffe copy-constructed" << '\n';
	}
	~Giraffe() {
		std::cout << "Giraffe destructed" << '\n';
	}
};

void zebra() {
	throw Giraffe{};
}

void llama() {
	try {
		zebra();
	} catch (const Giraffe& g) {
		(void)g;
		std::cout << "caught in llama; rethrow" << '\n';
		throw;
	}
}

int main() {
	try {
		llama();
	} catch (const Giraffe& g) {
		(void)g;
		std::cout << "caught in main" << '\n';
	}
}