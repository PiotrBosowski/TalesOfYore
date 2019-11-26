#include "Minimap.hpp"
#include "Position.hpp"
#include "World.hpp"
#include <algorithm>
using namespace std;

Minimap::Minimap(const World * const world_, const Position * position_) : world{ world_ }, position{ position_ }
{
	size = 1;
	MINIMAP_HEIGHT_PIXELS = 180;
	MINIMAP_WIDTH_PIXELS = 240;
}

void Minimap::zoomIn()
{
	if (size < 2) size++;
}

void Minimap::zoomOut()
{
	if (size > 1) size--;
}

void Minimap::draw()
{
	al_draw_filled_rectangle(WINDOW_WIDTH_PIXELS - MINIMAP_WIDTH_PIXELS, WINDOW_HEIGHT_PIXELS - MINIMAP_HEIGHT_PIXELS, WINDOW_WIDTH_PIXELS, WINDOW_HEIGHT_PIXELS, al_map_rgb(40,40,40));
	auto worldMapRef = world->getWorldMap();
	int currentRoomTopleftX, currentRoomTopleftY, currentRoomDownrightX, currentRoomDownrightY;
	int topleftX,            topleftY,            downrightX,            downrightY;
	for (Room * room : worldMapRef)
	{
		if (room->getTopLeftCords().x <= position->get().x + (MINIMAP_WIDTH_PIXELS / size)/2 && //optimalization - not drawing rooms that arent visible on the screen
			room->getDownRightCords().x >= position->get().x - (MINIMAP_WIDTH_PIXELS / size)/2 &&
			room->getTopLeftCords().y <= position->get().y + (MINIMAP_HEIGHT_PIXELS / size)/2 &&
			room->getDownRightCords().y >= position->get().y - (MINIMAP_HEIGHT_PIXELS / size)/2)
		{
			topleftX = max((size*(room->getTopLeftCords().x - position->get().x) + (WINDOW_WIDTH_PIXELS - MINIMAP_WIDTH_PIXELS / 2)), WINDOW_WIDTH_PIXELS - MINIMAP_WIDTH_PIXELS);
			topleftY = max((size*(room->getTopLeftCords().y - position->get().y) + (WINDOW_HEIGHT_PIXELS - MINIMAP_HEIGHT_PIXELS / 2)), WINDOW_HEIGHT_PIXELS - MINIMAP_HEIGHT_PIXELS);
			downrightX = min((size*(room->getDownRightCords().x - position->get().x) + (WINDOW_WIDTH_PIXELS - MINIMAP_WIDTH_PIXELS / 2)) + size, WINDOW_WIDTH_PIXELS);
			downrightY = min((size*(room->getDownRightCords().y - position->get().y) + (WINDOW_HEIGHT_PIXELS - MINIMAP_HEIGHT_PIXELS / 2)) + size, WINDOW_HEIGHT_PIXELS);
			
			if (room->getRoomNumber() == position->get().level)
			{
				currentRoomTopleftX = max((size*(room->getTopLeftCords().x - position->get().x) + (WINDOW_WIDTH_PIXELS - MINIMAP_WIDTH_PIXELS / 2)), WINDOW_WIDTH_PIXELS - MINIMAP_WIDTH_PIXELS);
				currentRoomTopleftY = max((size*(room->getTopLeftCords().y - position->get().y) + (WINDOW_HEIGHT_PIXELS - MINIMAP_HEIGHT_PIXELS / 2)), WINDOW_HEIGHT_PIXELS - MINIMAP_HEIGHT_PIXELS);
				currentRoomDownrightX = min((size*(room->getDownRightCords().x - position->get().x) + (WINDOW_WIDTH_PIXELS - MINIMAP_WIDTH_PIXELS / 2)) + size, WINDOW_WIDTH_PIXELS);
				currentRoomDownrightY = min((size*(room->getDownRightCords().y - position->get().y) + (WINDOW_HEIGHT_PIXELS - MINIMAP_HEIGHT_PIXELS / 2)) + size, WINDOW_HEIGHT_PIXELS);
				continue;
			}
			else
			{
				al_draw_filled_rectangle(topleftX, topleftY, downrightX, downrightY, al_map_rgb(56, 78, 112));
			}
		}
	}
	al_draw_filled_rectangle(currentRoomTopleftX, currentRoomTopleftY, currentRoomDownrightX, currentRoomDownrightY, al_map_rgb(139, 0, 139));
}

Minimap::~Minimap()
{
}
