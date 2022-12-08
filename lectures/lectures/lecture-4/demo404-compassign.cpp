#include "./demo404-compassign.h"

point& point::operator+=(point const& p) {
	x_ += p.x_;
	y_ += p.y_;
	return *this;
}

point& point::operator-=(point const& p) {
	x_ -= p.x_;
	y_ -= p.y_;
	return *this;
}

point& point::operator*=(int i) {
	x_ *= i;
	y_ *= i;
	return *this;
}

// point& operator+=(point const& p) { /* what do we put here? */
// }
// point& operator-=(point const& p) { /* what do we put here? */
//}
// point& operator*=(point const& p) { /* what do we put here? */
// }
// point& operator/=(point const& p) { /* what do we put here? */
// }
// point& operator*=(int i) { /* what do we put here? */
// }

auto main() -> int {
	auto p1 = point{1, 2};
	auto p2 = point{2, 3};
	p1 += p2;
	p1 -= p2;
	p1 *= 100;
	auto p3 = p1 * 100;
	std::cout << p1;
}