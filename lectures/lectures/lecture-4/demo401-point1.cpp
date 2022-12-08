#include <iostream>

class point {
public:
	point(int x, int y)
	: x_{x}
	, y_{y} {};
	[[nodiscard]] int x() const {
		return this->x_;
	}
	[[nodiscard]] int y() const {
		return this->y_;
	}
	// operator+(T, T) ... operator+(T, T)
	friend point operator+(point const& lhs, point const& rhs) {
		return point(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
	}
	friend point operator+(point const& lhs) {
		return lhs;
	}
	friend std::ostream& operator<<(std::ostream& os, point const& p) {
		os << "(" << p.x_ << "," << p.y_ << ")";
		return os;
	}

private:
	int x_;
	int y_;
};

auto main() -> int {
	auto p1 = point{1, 2};
	auto p2 = point{2, 3};
	std::cout << p1 + +p2 << "\n";
}