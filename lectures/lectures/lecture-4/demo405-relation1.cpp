#include <iostream>

class point {
public:
	point(int x, int y)
	: x_{x}
	, y_{y} {}
	// hidden friend - preferred
	friend bool operator==(point const& p1, point const& p2) {
		return p1.x_ == p2.x_ and p1.y_ == p2.y_;
		// return std::tie(p1.x_, p1.y_) == std::tie(p2.x_, p2.y_);
	}
	friend bool operator!=(point const& p1, point const& p2) {
		return !(p1 == p2);
	}
	friend bool operator<(point const& p1, point const& p2) {
		return p1.x_ < p2.x_ and p1.y_ < p2.y_;
	}
	friend bool operator<=(point const& p1, point const& p2) {
		return !(p2 < p1);
	}
	friend bool operator>(point const& p1, point const& p2) {
		return p2 < p1;
	}
	friend bool operator>=(point const& p1, point const& p2) {
		return !(p1 < p2);
	}

private:
	int x_;
	int y_;
};

auto main() -> int {
	auto const p2 = point{1, 2};
	auto const p1 = point{1, 2};
	std::cout << "p1 == p2 " << (p1 == p2) << "\n";
	std::cout << "p1 != p2 " << (p1 != p2) << "\n";
	std::cout << "p1 < p2 " << (p1 < p2) << "\n";
	std::cout << "p1 > p2 " << (p1 > p2) << "\n";
	std::cout << "p1 <= p2 " << (p1 <= p2) << "\n";
	std::cout << "p1 >= p2 " << (p1 >= p2) << "\n";
}