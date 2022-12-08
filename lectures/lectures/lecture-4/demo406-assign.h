#include <istream>

class point {
public:
	point(int x, int y)
	: x_{x}
	, y_{y} {};
	point& operator=(point const& p);

private:
	int x_;
	int y_;
};

point& point::operator=(point const& p) {
	x_ = p.x_;
	y_ = p.y_;
	return *this;
}
