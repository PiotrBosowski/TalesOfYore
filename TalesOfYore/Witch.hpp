#pragma once
#include "Hero.hpp"
#include <string>
#include "World.hpp"
class Witch : public Hero
{
public:
	Witch(World * world);
	~Witch() override;

private:
	const std::string resourceName;
	double resource;
};
