#include <iostream>

class point {
public:
	point(int x, int y)
	: x_{x}
	, y_{y} {};
	point& operator+=(point const& p);
	point& operator-=(point const& p);
	// point& operator*=(point const& p);
	// point& operator/=(point const& p);
	point& operator*=(int i);
	friend std::ostream& operator<<(std::ostream& os, point const& p) {
		os << "(" << p.x_ << "," << p.y_ << ")";
		return os;
	}
	friend point operator*(point const& lhs, int i) {
		return point(lhs.x_ * i, lhs.y_ * i);
	}
	friend point operator*(int i, point const& lhs) {
		return lhs * i;
	}

private:
	int x_;
	int y_;
};
