#include <iostream>
#include <string>

#include "./demo705-classtemp.h"

int main() {
	stack<int> s1; // int: template argument
	s1.push(1);
	s1.push(2);
	stack<int> s2 = s1;
	std::cout << s1 << s2 << '\n';
	s1.pop();
	s1.push(3);
	std::cout << s1 << s2 << '\n';
	// s1.push("hello"); // Fails to compile.

	stack<std::string> string_stack;
	string_stack.push("hello");
	// string_stack.push(1); // Fails to compile.
}