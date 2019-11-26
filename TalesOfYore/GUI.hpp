#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "GUIstorage.hpp"
#include "Position.hpp"
#include "Minimap.hpp"
class World; //?//#include "World.h" why is it incorrect?
class Room; //?//#include "Room.h" why is it incorrect?
class Square; //?//#include "Square.h" why is it incorrect?
class Hero;
constexpr int TEXTURES_SIZE = 16; //size of texures used
constexpr int SQUARE_SIZE = 32; //size of a square
constexpr int WINDOW_HEIGHT = 23; //height of the window (in squares), should be odd
constexpr int WINDOW_WIDTH = 33;  //width of the window (in squares), should be odd
constexpr int WINDOW_HEIGHT_PIXELS = WINDOW_HEIGHT * SQUARE_SIZE;
constexpr int WINDOW_WIDTH_PIXELS = WINDOW_WIDTH * SQUARE_SIZE;
constexpr int FPS = 60;

class GUI
{
private:
	ALLEGRO_DISPLAY * display;
	World * world; //world to serve
	Hero * hero; //hero to observe
	GUIstorage * storage; //stores all textures and graphics, its methods gives you pointers to accurate one
	
	const Position * const position; //pointer to characters position, this is camera position

public:
	GUI(World * worldToServe, Hero * heroToObserve_);
	Minimap minimap{world, position};
	ALLEGRO_DISPLAY * getDisplay();
	void drawFrame();
	void draw(World * worldToDraw);
	void draw(Room * roomToDraw);
	void draw(Square * squareToDraw);
	void draw(Hero * heroToDraw);
	void drawHUD();
	void drawMinimap();
	~GUI();
};