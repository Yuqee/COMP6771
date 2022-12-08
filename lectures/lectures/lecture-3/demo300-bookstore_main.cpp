#include <iostream>

#include "demo300-bookstore.h"

// TODO: set this to 1 when there is an implementation
#define implementation_exists 0

int main() {
#if implementation_exists
	BookSale cur_book;
	if (read(std::cin, cur_book)) {
		BookSale new_book;
		while (read(std::cin, new_book)) {
			if (cur_book.getBookName() == new_book.getBookName()) {
				cur_book.combine(new_book);
			}
			else {
				print(std::cout, cur_book) << '\n';
				cur_book = new_book;
			}
		}
		print(std::cout, cur_book) << '\n';
	}
	else {
		std::cerr << "No data?!\n";
	}
#endif
}
