#pragma once
#include <iostream>
#include "Position.hpp"
#include "Structures.hpp"

class Node;

class Square
{
public:
	Square();
	Square(const Square & squareToCopy);
	virtual sqType getType() const = 0;
	virtual bool isStepable() const = 0;
	Square & operator=(const Square & squareToCopy);
	Position position;
	virtual ~Square();
};

class Door : public Square
{
public:
	Door(sqType type_) { type = type_; };
	sqType getType() const override { return type; };
	bool isStepable() const override { return true; };
	sqType type;
};

class Wall : public Square
{
public:
	sqType getType() const override { return wall; };
	bool isStepable() const override { return false; };
};

class Ground : public Square
{
public:
	sqType getType() const override { return ground; };
	bool isStepable() const override { return true; };
};