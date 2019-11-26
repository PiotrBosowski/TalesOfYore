#include "Defence.hpp"
using namespace std;

Defence::Defence()
{
}

double Defence::getHealth() const
{
	return health;
}

void Defence::loseHealth(const double loss)
{
	double effective_ammount = loss * ((100.0 - armor) / 100.0);
	health -= effective_ammount;
	if (health < health_min) health = 0;
}

void Defence::gainHealth(double ammount)
{
	health += ammount;
	if (health > health_max) health = health_max;
}

Defence::~Defence()
{
}