#pragma once
#include "Position.hpp"

class Hero;
class World;

class Pathfinding
{
public:
	Pathfinding(Hero * const hero_, World * const world_);
	void findBestPath(const Cords & relativeCords);
	~Pathfinding();
private:
	Hero * const hero; //pointer to hero
	World * const world; //ptr to world ofc
};

