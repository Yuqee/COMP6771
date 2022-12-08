#include <iostream>

class point {
public:
	point(int x, int y)
	: x_{x}
	, y_{y} {};
	friend point& operator++(point& other) {
		other.x_ += 1;
		other.y_ += 1;
		return other;
	}
	point operator+(point const& lhs) {
		return point(lhs.x_ + this->x_, lhs.y_ + this->y_);
	};
	friend std::ostream& operator<<(std::ostream& os, point const& p) {
		os << "(" << p.x_ << "," << p.y_ << ")";
		return os;
	}
	int operator[](int index) const {
		std::cout << "I am const :)"
		          << "\n";
		return index == 0 ? x_ : y_;
	}

private:
	int x_;
	int y_;
};

auto main() -> int {
	point p1{1, 2};
	point const p2{2, 3};
	std::cout << ++p1 << "\n";
	// p1[0] = 100;
	std::cout << "Printing p1[0]" << p1[0] << "\n";
	std::cout << "Printing p2[0]" << p2[0] << "\n";
	// std::cout << "p1[0] == " << p1[0] << "\n";
	// std::cout << "p1[1] == " << p1[1] << "\n";
	// std::cout << "p2[0] == " << p2[0] << "\n";
	// std::cout << "p2[1] == " << p2[1] << "\n";
}