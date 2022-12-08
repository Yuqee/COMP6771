#ifndef LECTURES_WEEK9_DOG_H_
#define LECTURES_WEEK9_DOG_H_

#include <iostream>
#include <string>
#include <utility>

#include "./animal.h"

class Dog : public Animal {
public:
	// This is very similar to delegating constructors. Each subclass constructor must always make
	// sure a constructor is called for the base class subobject.
	Dog(std::string name, int age)
	: Animal(age)
	, name_(std::move(name)) {
		// print_details("Is being born");
	}

	void print_details(const std::string& suffix) const override {
		std::cout << "Dog " << name_ << " of age " << get_age() << ' ' << suffix << '\n';
	}

	~Dog() {
		std::cout << "Dog is dying\n";
	}

private:
	std::string name_;
};

#endif // LECTURES_WEEK9_DOG_H_
