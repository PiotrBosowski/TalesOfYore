#pragma once
#include <string>
#include "Equipment.hpp"
#include "Position.hpp"
#include "Moving.hpp"
#include "Resource.hpp"
#include "World.hpp"
#include "Pathfinding.hpp"

class Hero
{
public:
	Hero(World * world_, std::string className_, heroClass classEnum_, std::string resourceName_, double resource_);
	bool isAlive(); //function returns true if character's live is more than 0, otherwise returns false
	virtual ~Hero();
	Equipment equipment; //working with gear you wear and items you carry
	Position position; //storing and changing characters position
	Resource resource; //object that represent characters resource, it can be mana, anger, arcane power etc.
	Moving move; //moving your hero
	Pathfinding pathfinding;
	const heroClass classType; //hero class enum
	const std::string className; //hero class name

public:
	double health; //lose all and you die
	double armor; //how much dmg reduction u have, 100 = immortality
	double capacity; //how much weight you can bear
};