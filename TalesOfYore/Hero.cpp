#include "Hero.h"
#include <iostream>
#include <string>
#include "Position.h"
using namespace std;

Hero::Hero()
{
	position.setAbsolute(Cords{ 0, 0 });
}

bool Hero::isAlive()
{
	return (health > 0) ? true : false;
}

double Hero::getHealth()
{
	return health;
}

void Hero::loseHealth(double ammount)
{
	double effective_ammount = ammount * ((100.0 - armor) / 100.0);
	if(effective_ammount < health) health -= effective_ammount;
	else health = 0;
	cout << "Nice, you lost " << effective_ammount << " health points,  " << health << " to go." << endl;
}

void Hero::gainHealth(double ammount)
{
	health += ammount;
	cout << "Shame, you healed for " << ammount << " HP, now it's " << health << " left." << endl;
}

Hero::~Hero() {}