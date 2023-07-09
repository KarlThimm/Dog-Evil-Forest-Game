/*
 * Dog.hpp
 *
 *  Created on: Sep 8, 2022
 *      Author: karlthimm
 */

#ifndef DOG_HPP_
#define DOG_HPP_

#include <iostream>
#include <string.h>
using namespace std;

class Dog {
	friend class Board;
	string name;
	int strength;
	int x;
	int y;

public:
Dog(string dogg);
Dog();
bool Strength_Change(int number);
void die();
void printDog();
void won();
void reset();
};

#endif /* DOG_HPP_ */
