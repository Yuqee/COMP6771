#include <iostream>
#include <memory>
#include <vector>

template<typename T, template<typename...> typename CONT>
class stack {
public:
	auto push(T t) -> void {
		stack_.push_back(t);
	}
	auto pop() -> void {
		stack_.pop_back();
	}
	auto top() -> T& {
		return stack_.back();
	}
	auto empty() const -> bool {
		return stack_.empty();
	}

private:
	CONT<T> stack_;
};

#include <iostream>
#include <vector>

auto main(void) -> int {
	auto s1 = stack<int, std::vector>{};
	s1.push(1);
	s1.push(2);
}