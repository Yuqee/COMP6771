#include <functional>
#include <iostream>
#include <string>

#include "./animal.h"
#include "./cat.h"
#include "./dog.h"

int main() {
	auto animal = Animal(5);
	auto cat = Cat("kitty", 9);
	auto dog = Dog("doggo", 10);

	// Up-casting is always safe (derived to base).
	[[maybe_unused]] Animal& animal_cat = cat;
	[[maybe_unused]] Animal& animal_dog = dog;

	// Casting works the same with references and pointers.
	[[maybe_unused]] Animal* animal_cat_ptr = &cat;
	[[maybe_unused]] Animal* animal_dog_ptr = &dog;

	// The compiler won't allow you to down cast.
	// Down-casting may make sense.
	//  Cat& recast_cat = animal_cat;
	// But it may not.
	//  Cat& recast_dog = animal_dog;
}
