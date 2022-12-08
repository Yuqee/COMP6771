#ifndef LECTURES_WEEK9_ANIMAL_H_
#define LECTURES_WEEK9_ANIMAL_H_

#include <iostream>
#include <string>

class Animal {
public:
	explicit Animal(int age)
	: age_(age) {
		print_details("is being born");
	}

protected:
	int get_age() const {
		return age_;
	}

public:
	virtual ~Animal() {
		std::cout << "animal is dying\n";
	}

	virtual void print_details(const std::string& suffix) const {
		std::cout << "Unknown animal of age " << age_ << ' ' << suffix << '\n';
	}

private:
	int age_;
};

#endif // LECTURES_WEEK9_ANIMAL_H_
