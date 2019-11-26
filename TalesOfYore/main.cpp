#include <iostream>
#include "World.h"
using namespace std;

int main()
{
	Gui gui;

	World fujisoma;

	fujisoma.createLevel();

	fujisoma.printMap();
}


//WARNING: memory is soaking through the cellar door