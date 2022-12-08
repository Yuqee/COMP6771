#include <istream>
#include <ostream>

class point {
public:
	point(int x, int y)
	: x_{x}
	, y_{y} {};
	friend std::ostream& operator<<(std::ostream& os, const point& type);
	friend std::istream& operator>>(std::istream& is, point& type);

private:
	int x_;
	int y_;
};
