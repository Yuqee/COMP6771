#include <functional>
#include <iostream>
#include <string>

#include "./animal.h"
#include "./cat.h"
#include "./dog.h"

void do_things(Animal& animal) {
	std::cout << "animal has size " << sizeof(animal) << '\n';
	animal.print_details(" is doing things");
}

int main() {
	// TODO(lecture): Does it make sense to be able to create animals on their own?
	// Fix after explaining the following two sections.
	auto animal = Animal(5);
	auto cat = Cat("kitty", 9);
	auto dog = Dog("doggo", 10);
	std::cout << '\n';

	// TODO(lecture): What do we expect the answers here are?
	std::cout << "animal: size = " << sizeof(animal) << ", ptr = " << sizeof(&animal)
	          << ", ref = " << sizeof(std::ref(animal)) << '\n';
	std::cout << "kitty: size = " << sizeof(cat) << ", ptr = " << sizeof(&cat)
	          << ", ref = " << sizeof(std::ref(cat)) << '\n';
	std::cout << "doggo: size = " << sizeof(dog) << ", ptr = " << sizeof(&dog)
	          << ", ref = " << sizeof(std::ref(dog)) << '\n';
	std::cout << '\n';

	std::cout << "kitty age = " << cat.get_age() << '\n';
	// std::cout << "doggo age = " < dog.get_age() << '\n';
	std::cout << '\n';

	// TODO(lecture): What do we expect to happen when we uncomment this?
	// do_things(animal);
	// do_things(cat);
	// do_things(dog);
	std::cout << '\n';
}

// Dog d;