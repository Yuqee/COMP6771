// stack.h
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>

template<typename T>
class stack {
public:
	friend auto operator<<(std::ostream& os, const stack& s) -> std::ostream& {
		for (const auto& i : s.stack_)
			os << i << " ";
		return os;
	}
	auto push(T const& item) -> void;
	auto pop() -> void;
	auto top() -> T&;
	auto top() const -> const T&;
	auto empty() const -> bool;

private:
	std::vector<T> stack_;
};

#include "./demo705-classtemp.tpp"

#endif // STACK_H