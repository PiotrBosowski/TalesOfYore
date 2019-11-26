#include "GUIstorage.hpp"
#include <iostream>
using namespace std;

GUIstorage::GUIstorage()
{
	if (!(squareTexture[0] = al_load_bitmap("graphics/ground.png"))) cout << "error reading ground.png" << endl;
	if (!(squareTexture[1] = al_load_bitmap("graphics/wall.png"))) cout << "error reading wall.png" << endl;
	if (!(squareTexture[2] = al_load_bitmap("graphics/entrance.png"))) cout << "error reading entrance.png" << endl;
	if (!(squareTexture[3] = al_load_bitmap("graphics/egress.png"))) cout << "error reading egress.png" << endl;
	if (!(squareTexture[4] = al_load_bitmap("graphics/NPC.png"))) cout << "error reading NPC.png" << endl;
	if (!(squareTexture[5] = al_load_bitmap("graphics/enemy.png"))) cout << "error reading enemy.png" << endl;
	if (!(squareTexture[6] = al_load_bitmap("graphics/hero.png"))) cout << "error reading hero.png" << endl;
	if (!(witchTexture = al_load_bitmap("graphics/witchTexture.png"))) cout << "error reading witchTexture.png" << endl;
	if (!(font = al_load_ttf_font("fonts/lucida.ttf", 20, 0))) cout << "error loading fonasdsadt" << endl;
}

ALLEGRO_BITMAP * GUIstorage::getTexture(int type)
{
	switch (type)
	{
	case 0: return squareTexture[0];
	case 1: return squareTexture[1];
	case 2: return squareTexture[2];
	case 3: return squareTexture[3];
	case 4: return squareTexture[4];
	case 5: return squareTexture[5];
	case 6: return squareTexture[6];
	default: return squareTexture[0];
	}
}

ALLEGRO_BITMAP * GUIstorage::getTexture(heroClass heroClass)
{
	switch (heroClass)
	{
	case classWitch: return witchTexture; break;
	default: return witchTexture;
	}
}

ALLEGRO_FONT * GUIstorage::getFont()
{
	return font;
}

GUIstorage::~GUIstorage()
{
	for(ALLEGRO_BITMAP * bitmap : squareTexture)
		al_destroy_bitmap(bitmap);
}
