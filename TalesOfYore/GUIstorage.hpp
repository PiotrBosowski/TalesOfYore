#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_font.h"
#include "Structures.hpp"

class GUIstorage
{
public:
	GUIstorage();
	ALLEGRO_BITMAP * getTexture(int type);
	ALLEGRO_BITMAP * getTexture(heroClass heroClassName);
	ALLEGRO_FONT * getFont();
	~GUIstorage();
private:
	ALLEGRO_BITMAP * squareTexture[7];
	ALLEGRO_BITMAP * witchTexture;
	ALLEGRO_FONT * font;
};

