#include <iostream>
#include <vector>

template<typename T>
class stack {
public:
	auto push(T const&) -> void;
	auto pop() -> void;

	friend auto operator<<(std::ostream& os, stack<T> const& s) -> std::ostream& {
		return os << "My top item is " << s.stack_.back() << "\n";
	}

private:
	std::vector<T> stack_;
};

template<typename T>
auto stack<T>::push(T const& t) -> void {
	stack_.push_back(t);
}