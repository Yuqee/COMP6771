#include <iostream>

#include "./demo408-incdec.h"

auto main() -> int {
	auto const roadpos = 5;
	auto rp = roadposition(roadpos);
	std::cout << rp.km() << '\n';
	auto val1 = (rp++).km();
	std::cout << rp.km() << '\n';
	auto val2 = (++rp).km();
	std::cout << val1 << '\n';
	std::cout << val2 << '\n';
}