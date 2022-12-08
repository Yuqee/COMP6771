#include <cassert>

class point {
public:
	point(int x, int y)
	: x_{x}
	, y_{y} {};
	int& operator[](int i) {
		assert(i == 0 or i == 1);
		return i == 0 ? x_ : y_;
	}
	int operator[](int i) const {
		assert(i == 0 or i == 1);
		return i == 0 ? x_ : y_;
	}

private:
	int x_;
	int y_;
};