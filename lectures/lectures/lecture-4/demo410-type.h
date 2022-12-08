#include <vector>

class point {
public:
	point(int x, int y)
	: x_(x)
	, y_(y) {}
	explicit operator std::vector<int>() const {
		return std::vector<int>{x_, y_};
	}

private:
	int x_;
	int y_;
};