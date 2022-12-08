#include "./demo705-classtemp.h"

template<typename T>
auto stack<T>::push(T const& item) -> void {
	stack_.push_back(item);
}

template<typename T>
auto stack<T>::pop() -> void {
	stack_.pop_back();
}

template<typename T>
auto stack<T>::top() -> T& {
	return stack_.back();
}

template<typename T>
auto stack<T>::top() const -> T const& {
	return stack_.back();
}

template<typename T>
auto stack<T>::empty() const -> bool {
	return stack_.empty();
}