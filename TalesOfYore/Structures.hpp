#pragma once

enum sqType
{
	ground = 0,
	wall = 1,
	entrance = 2,
	egress = 3,
	NPC = 4,
	enemy = 5,
	hero = 6,
	door
};

enum heroClass
{
	classWitch,
	classRouge,
	classThief
};

enum movingCases
{
	move_squareBeyondMap, //hero goes to the next (unexplored) egress
	move_egress, //hero goes to egress, hero's room counter increases
	move_entrance, //hero goes to entrance, hero's room decreases
	move_ground,
	move_wall, //hero does nothing
	move_otherRoom, //hero goes to egress of actual room
	move_error,
};

enum cardinalDirection
{
	N = 0, NE = 1, E = 2, SE = 3, S = 4, SW = 5, W = 6, NW = 7, c = 8
};
cardinalDirection oppositeDirection(cardinalDirection dirToSwitch);

struct Cords
{
	int x;
	int y;
	unsigned int level = 0;
};

class Type
{
public:
	Type();
	void set(int newType);
	int get();
	~Type();
private:
	int type;
};