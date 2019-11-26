#include "GUI.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "World.hpp"
#include "Room.hpp"
#include "Hero.hpp"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro.h"
#include "allegro5/bitmap.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
using namespace std;

GUI::GUI(World * worldToServe, Hero * heroToObserve) : world{ worldToServe }, hero{ heroToObserve }, position{&(heroToObserve->position)}
{
	if(!al_init()) cout << "al init error" << endl;
	if(!al_init_image_addon()) cout << "al init image error" << endl;
	if(!(display = al_create_display(WINDOW_WIDTH_PIXELS, WINDOW_HEIGHT_PIXELS))) cout << "display init error" << endl;
	if(!(al_install_mouse())) cout << "error installing mouse" << endl;
	if(!(al_install_keyboard())) cout << "error installing keyboard" << endl;
	if (!(al_init_primitives_addon())) cout << "error installing primitives" << endl;
	if (!(al_init_font_addon())) cout << "error installing font" << endl;
	if (!(al_init_ttf_addon())) cout << "error installing font" << endl;
	storage = new GUIstorage;
}

void GUI::draw(Hero * heroToDraw)
{
	al_draw_scaled_bitmap(storage->getTexture(hero->classType), 0, 0, TEXTURES_SIZE, TEXTURES_SIZE, SQUARE_SIZE * (WINDOW_WIDTH/2), SQUARE_SIZE * (WINDOW_HEIGHT/2), SQUARE_SIZE, SQUARE_SIZE, 0);
}

void GUI::drawHUD()
{
	#define HUD_DIMENSIONS 250, 116
	#define FRAME_COLOR 80, 7, 86
	#define FRAME_COLOR2 100, 47, 104
	#define TEXT_COLOR 182, 100, 55
	al_draw_filled_rectangle(0, 0, HUD_DIMENSIONS, al_map_rgb(FRAME_COLOR2));
	al_draw_filled_rectangle(126, 0, 131, 116, al_map_rgb(FRAME_COLOR));
	al_draw_text(storage->getFont(), al_map_rgb(TEXT_COLOR), 120, 8, ALLEGRO_ALIGN_RIGHT, hero->className.c_str());
	al_draw_text(storage->getFont(), al_map_rgb(TEXT_COLOR), 120, 35, ALLEGRO_ALIGN_RIGHT, "Health");
	al_draw_text(storage->getFont(), al_map_rgb(TEXT_COLOR), 120, 62, ALLEGRO_ALIGN_RIGHT, hero->resource.getName().c_str());
	al_draw_text(storage->getFont(), al_map_rgb(TEXT_COLOR), 120, 89, ALLEGRO_ALIGN_RIGHT, "Position");
	
	string positionText = to_string(hero->position.get().x) + "," + to_string(hero->position.get().y) + "," + to_string(hero->position.get().level);
	al_draw_filled_rectangle(248 - 115 * (hero->health / 100), 35, 248, 53, al_map_rgb(230 - 170 * (1 - (hero->health / 100)), 60, 60));
	al_draw_filled_rectangle(248 - 115 * (hero->resource.get() / 100), 62, 248, 81, al_map_rgb(60, 60, 230));
	al_draw_text(storage->getFont(), al_map_rgb(TEXT_COLOR), 135, 89, ALLEGRO_ALIGN_LEFT, positionText.c_str());
}

void GUI::drawMinimap()
{
	minimap.draw();
}

#define BLACK 0,0,0
#define DARK_GREY 30,30,30
#define WHITE 255,255,255
void GUI::drawFrame()
{
	al_clear_to_color(al_map_rgb(BLACK));
	draw(world);
	draw(hero);
	drawHUD();
	drawMinimap();
	al_flip_display();
}

ALLEGRO_DISPLAY * GUI::getDisplay()
{
	return display;
}
#define QUICKER_VANISHING 0 //change to zero to make rooms vanish properly (outside the screen)
void GUI::draw(World * worldToDraw)
{
	int i = 0;
	for (Room * room : worldToDraw->worldMap)
	{
		if (room->getTopLeftCords().x <= position->get().x + WINDOW_WIDTH/2 - QUICKER_VANISHING && //optimalization - not drawing rooms that arent visible on the screen
			room->getDownRightCords().x >= position->get().x - WINDOW_WIDTH / 2 + QUICKER_VANISHING &&
			room->getTopLeftCords().y <= position->get().y + WINDOW_HEIGHT/2 - QUICKER_VANISHING &&
			room->getDownRightCords().y >= position->get().y - WINDOW_HEIGHT / 2 + QUICKER_VANISHING)
			if(i != hero->position.get().level)
				draw(room);
		i++;
	}
	draw(worldToDraw->worldMap[hero->position.get().level]);
}

#define CZARNA_OBWODKA 0 //change to zero to get rid of the black edging
void GUI::draw(Room * roomToDraw)
{
	if (roomToDraw->getRoomNumber() != hero->position.get().level)
	{
		int topleftX = SQUARE_SIZE * (roomToDraw->getTopLeftCords().x - hero->position.get().x + WINDOW_WIDTH / 2);
		int topleftY = SQUARE_SIZE * (roomToDraw->getTopLeftCords().y - hero->position.get().y + WINDOW_HEIGHT / 2);
		int downrightX = SQUARE_SIZE * (roomToDraw->getDownRightCords().x - hero->position.get().x + WINDOW_WIDTH / 2) + SQUARE_SIZE;
		int downrightY = SQUARE_SIZE * (roomToDraw->getDownRightCords().y - hero->position.get().y + WINDOW_HEIGHT / 2) + SQUARE_SIZE;
		al_draw_filled_rectangle(topleftX, topleftY, downrightX, downrightY, al_map_rgb(DARK_GREY));
	}
	else
	{
		for (vector<Square*> row : roomToDraw->getRoomMap())
			for (Square * square : row)
			{
				if ((square->position.get().x <= position->get().x + WINDOW_WIDTH / 2 - CZARNA_OBWODKA) && //optimalization - nor drawing squares that arent visible on the screen
					(square->position.get().x >= position->get().x - WINDOW_WIDTH / 2 + CZARNA_OBWODKA) &&
					(square->position.get().y <= position->get().y + WINDOW_HEIGHT / 2 - CZARNA_OBWODKA) &&
					(square->position.get().y >= position->get().y - WINDOW_HEIGHT / 2 + CZARNA_OBWODKA))
				{
					draw(square);
				}
			}
		auto & nodesVector = roomToDraw->pathsetting.getNodesVector();
		for (size_t j = 0, jmax = nodesVector.size(); j < jmax; j++)
		{
			if (nodesVector[j] != nullptr)
			{
				double SQS = (double)SQUARE_SIZE;
				int topleftX = SQUARE_SIZE * (nodesVector[j]->getPosition().x - hero->position.get().x + WINDOW_WIDTH / 2);
				int topleftY = SQUARE_SIZE * (nodesVector[j]->getPosition().y - hero->position.get().y + WINDOW_HEIGHT / 2);
				al_draw_filled_rectangle(topleftX + SQS * 0.3, topleftY + SQS * 0.3, topleftX + SQS * 0.7, topleftY + SQS * 0.7, al_map_rgb(255, 220, 180));
				if(nodesVector[j]->type[N]) al_draw_filled_rectangle(topleftX + 0.4 * SQS, topleftY + SQS * 0.1, topleftX + 0.6 * SQS, topleftY + SQS * 0.3, al_map_rgb(255, 220, 180));
				if(nodesVector[j]->type[E]) al_draw_filled_rectangle(topleftX + 0.7 * SQS, topleftY + SQS * 0.4, topleftX + 0.9 * SQS, topleftY + SQS * 0.6, al_map_rgb(255, 220, 180));
				if(nodesVector[j]->type[S]) al_draw_filled_rectangle(topleftX + 0.4 * SQS, topleftY + SQS * 0.7, topleftX + 0.6 * SQS, topleftY + SQS * 0.9, al_map_rgb(255, 220, 180));
				if(nodesVector[j]->type[W]) al_draw_filled_rectangle(topleftX + 0.1 * SQS, topleftY + SQS * 0.4, topleftX + 0.3 * SQS, topleftY + SQS * 0.6, al_map_rgb(255, 220, 180));
				if(nodesVector[j]->type[NE]) al_draw_filled_rectangle(topleftX + 0.7 * SQS, topleftY + SQS * 0.1, topleftX +  0.9 * SQS, topleftY + SQS * 0.3, al_map_rgb(255, 220, 180));
				if(nodesVector[j]->type[SE]) al_draw_filled_rectangle(topleftX + 0.7 * SQS, topleftY + 0.7 * SQS, topleftX + 0.9 * SQS, topleftY + 0.9 * SQS, al_map_rgb(255, 220, 180));
				if(nodesVector[j]->type[SW]) al_draw_filled_rectangle(topleftX + 0.1 * SQS, topleftY + 0.7 * SQS, topleftX + 0.3 * SQS, topleftY + 0.9 * SQS, al_map_rgb(255, 220, 180));
				if(nodesVector[j]->type[NW]) al_draw_filled_rectangle(topleftX + 0.1 * SQS, topleftY + 0.1 * SQS, topleftX + 0.3 * SQS, topleftY + 0.3 * SQS, al_map_rgb(255, 220, 180));
			}
		}
		int licznikrysowanych = 0;
		for (size_t j = 0, jmax = nodesVector.size(); j < jmax; j++)
		{
			for (Connection con : nodesVector[j]->getConnectionSet())
			{
				licznikrysowanych++;
				//al_draw_line((nodesVector[j]->getPosition().x - hero->position.get().x + WINDOW_WIDTH / 2)*SQUARE_SIZE + SQUARE_SIZE/2, (nodesVector[j]->getPosition().y - hero->position.get().y + WINDOW_HEIGHT / 2) * SQUARE_SIZE + SQUARE_SIZE/2, (con.getNode()->getPosition().x - hero->position.get().x + WINDOW_WIDTH / 2) * SQUARE_SIZE + SQUARE_SIZE/2, (con.getNode()->getPosition().y - hero->position.get().y + WINDOW_HEIGHT / 2) * SQUARE_SIZE + SQUARE_SIZE/2, al_map_rgb(255, 220, 180), 1);
			}
		}
	//	cout << licznikrysowanych << "narysowanych" << endl;

	}
}

void GUI::draw(Square * squareToDraw)
{
	al_draw_scaled_bitmap(storage->getTexture(squareToDraw->getType()), 0, 0, TEXTURES_SIZE, TEXTURES_SIZE, SQUARE_SIZE * (squareToDraw->position.get().x - hero->position.get().x + WINDOW_WIDTH/2), SQUARE_SIZE * (squareToDraw->position.get().y - hero->position.get().y + WINDOW_HEIGHT/2), SQUARE_SIZE, SQUARE_SIZE, 0); //15 is on-screen heros position
}

GUI::~GUI()
{
	al_destroy_display(display);
	delete storage;
}