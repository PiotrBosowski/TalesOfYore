#pragma once
#include "Hero.h"
#include <string>
class Witch : public Hero
{
public:
	std::string getClassName() override;
	std::string getResourceName() override;
	double getResource() override;
	void loseResource(double ammount) override;
	void gainResource(double ammount) override;
	
	Witch();
	~Witch() override;

private:
	const std::string className;
	const std::string resourceName;
	double mana;
};
