#pragma once
#include <string>
#include "Equipment.h"
#include "Position.h"
class Hero
{
public:
	virtual std::string getClassName() = 0; //returns class name (not character name!) as a string
	bool isAlive(); //checks if character is alive
	double getHealth(); //returns number of health points character is left
	void loseHealth(double ammount); //decrease hp by <ammount> (it is being reduced by character's armor)
	void gainHealth(double ammount); //increase hp by <ammount> (its flat value, not reduced nor increased)
	virtual std::string getResourceName() = 0; //returns name of resource that character is using (every character-class has its own one)
	virtual double getResource() = 0; //returns value of character's resource left
	virtual void loseResource(double ammount) = 0; //decrease character's resource by flat <ammount>
	virtual void gainResource(double ammount) = 0; //decrease character's resource by flat <ammount>
	
	Hero(); //regular constructor
	virtual ~Hero(); //virtual destructor

protected:
	double health; //lose all and you die
	double armor; //how much dmg reduction u have, 100 = immortality
	double capacity; //how much weight you can bear
	Equipment equipment; //as the name says, items you both wear and carry
	Position position; //x and y cords
};