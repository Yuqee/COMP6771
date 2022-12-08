#include <vector>

template<typename T>
class stack {
public:
	stack();
	~stack();
	auto push(T&) -> void;
	auto pop() -> void;
	auto top() -> T&;
	auto top() const -> const T&;
	static int num_stacks_;

private:
	std::vector<T> stack_;
};

template<typename T>
int stack<T>::num_stacks_ = 0;

template<typename T>
stack<T>::stack() {
	num_stacks_++;
}

template<typename T>
stack<T>::~stack() {
	num_stacks_--;
}