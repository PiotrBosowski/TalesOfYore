#pragma once
class Defence
{
public:
	Defence();
	double getHealth() const; //returns number of health points character is left
	void loseHealth(double ammount); //decrease hp by <ammount> (it is being reduced by character's armor)
	void gainHealth(double ammount); //increase hp by <ammount> (its flat value, not reduced nor increased)
	~Defence();

private:
	double health, health_min = 0, health_max = 100;
	double armor;
};




