#include <vector>

template<typename T, typename CONT = std::vector<T>>
class stack {
public:
	stack();
	~stack();
	auto push(T&) -> void;
	auto pop() -> void;
	auto top() -> T&;
	auto top() const -> T const&;
	static int num_stacks_;

private:
	CONT stack_;
};

template<typename T, typename CONT>
int stack<T, CONT>::num_stacks_ = 0;

template<typename T, typename CONT>
stack<T, CONT>::stack() {
	num_stacks_++;
}

template<typename T, typename CONT>
stack<T, CONT>::~stack() {
	num_stacks_--;
}