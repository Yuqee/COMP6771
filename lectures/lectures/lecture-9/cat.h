#ifndef LECTURES_WEEK9_CAT_H_
#define LECTURES_WEEK9_CAT_H_

#include <iostream>
#include <string>
#include <utility>

#include "./animal.h"

class Cat : public Animal {
public:
	// This is very similar to delegating constructors. Each subclass constructor must always make
	// sure a constructor is called for the base class subobject.
	Cat(std::string name, int age)
	: Animal(age)
	, name_(std::move(name)) {
		// print_details("is being born");
	}

	void print_details(const std::string& suffix) const final {
		std::cout << "Cat " << name_ << " of age " << get_age() << ' ' << suffix << '\n';
	}

	using Animal::get_age;

private:
	std::string name_;
};

#endif