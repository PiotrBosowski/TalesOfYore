#pragma once

struct Cords
{
	int y; //width
	int x; //height
};

enum sqType
{
	ground = 0,
	wall = 1,
	entrance = 2,
	egress = 3,
	NPC = 4,
	enemy = 5,
	hero = 6
};

enum cardinalDirection { N = 0, E = 1, S = 2, W = 3, c = 4 };
cardinalDirection oppositeDirection(cardinalDirection dirToSwitch);