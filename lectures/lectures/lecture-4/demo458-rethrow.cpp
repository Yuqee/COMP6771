#include <iostream>

class Cake {
public:
	Cake()
	: pieces_{8} {}
	int getPieces() {
		return pieces_;
	}
	Cake& operator--() {
		--pieces_;
		return *this;
	}

private:
	int pieces_;
};

int main() {
	try {
		try {
			try {
				throw Cake{};
			} catch (Cake& e1) {
				--e1;
				std::cout << "e1 Pieces: " << e1.getPieces() << " addr: " << &e1 << "\n";
				throw;
			}
		} catch (Cake e2) {
			--e2;
			std::cout << "e2 Pieces: " << e2.getPieces() << " addr: " << &e2 << "\n";
			throw;
		}
	} catch (Cake& e3) {
		--e3;
		std::cout << "e3 Pieces: " << e3.getPieces() << " addr: " << &e3 << "\n";
	}
}