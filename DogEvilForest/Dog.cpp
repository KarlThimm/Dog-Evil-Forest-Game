/*
 * Dog.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: karlthimm
 */

#include <iostream>
#include "Dog.hpp"
using namespace std;
#ifndef DOG_CPP_
#define DOG_CPP_

Dog::Dog(string dogg){
	strength=50;
	name=dogg;
	x=0;
	y=0;
}

Dog::Dog(){
	name='Cody';
	strength=50;
	x=0;
	y=0;
}

bool Dog::Strength_Change(int number){
	strength=number+strength;
	printDog();
	if(strength<1){
		strength = 0;
		die();
		return false;
	}
	else{
		return true;
	}
}

void Dog::die(){
	cout<<"Cody did not make it through the forest"<<endl;
}
void Dog::printDog(){
	cout<<"Cody has "<<strength<< " strength"<<endl;
}
void Dog::won(){
	cout<<"Cody has made it through the forest"<<endl;
}
void Dog::reset(){ //Resets the dog at the beginning of the game (or end)
	strength=50;
	x=0;
	y=0;
}

#endif












