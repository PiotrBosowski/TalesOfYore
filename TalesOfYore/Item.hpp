#pragma once
#include <string>
#include <iostream>

enum statisticType
{
	dexterity, strength, intelligence 
};

struct statistic
{
	double value;
	statisticType type;
	std::string name;
};

class Item
{
public:
	Item();
	virtual ~Item();

	double getArmor();
	double getWeight();
	std::string getName();
	statistic getStat();
	friend std::ostream& operator<<(std::ostream& s, Item* item);

protected:
	statistic stat;
	double weight;
	double armor;
	std::string itemClassName;
	std::string itemName;
};

Item * randomItem();  //returns an adress of fully random item (made by 'new' operator - needs to be deleted later on)
void randomize(statistic & stat, int min = 0, int max = 100);  //initializes a dex-int-str statistic with random type and value
void randomize(double & value, int min = 0, int max = 100); //initializes any double variable with random value

//warning: enemy can attack you with the weapon he drops off when he dies