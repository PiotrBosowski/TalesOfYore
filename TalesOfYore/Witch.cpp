#include "Witch.h"
#include <iostream>
#include <string>
using namespace std;

string Witch::getClassName()
{
	return className;
}
string Witch::getResourceName()
{
	return resourceName;
}



Witch::Witch() : className{ "Witch" }, resourceName{ "Mana" }, mana{ 25 }
{
	health = 100;
	armor = 12;
	cout << "stworzyles postac klasy " << className << endl;
}

double Witch::getResource()
{
	return mana;
}

void Witch::loseResource(double ammount)
{
	mana -= ammount;
}
void Witch::gainResource(double ammount)
{
	mana += ammount;
}

Witch::~Witch()
{
	cout << "zabiles postac klasy " << className << endl;
}


