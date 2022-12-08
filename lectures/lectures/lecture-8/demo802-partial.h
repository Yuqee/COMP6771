#include <iostream>
#include <numeric>
#include <vector>

template<typename T>
class stack {
public:
	auto push(T t) -> void {
		stack_.push_back(t);
	}
	auto top() -> T& {
		return stack_.back();
	}
	auto pop() -> void {
		stack_.pop_back();
	}
	auto size() const -> std::size_t {
		return stack_.size();
	};
	auto sum() -> int {
		return std::accumulate(stack_.begin(), stack_.end(), 0);
	}

private:
	std::vector<T> stack_;
};

template<typename T>
class stack<T*> {
public:
	auto push(T* t) -> void {
		stack_.push_back(t);
	}
	auto top() -> T* {
		return stack_.back();
	}
	auto pop() -> void {
		stack_.pop_back();
	}
	auto size() const -> std::size_t {
		return stack_.size();
	};
	auto sum() -> int {
		return std::accumulate(stack_.begin(), stack_.end(), 0, [](int a, T* b) { return a + *b; });
	}

private:
	std::vector<T*> stack_;
};
