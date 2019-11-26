#pragma once
class World;
class Position;

class Minimap
{
public:
	Minimap(const World * const world_, const Position * const position_);
	void zoomIn();
	void zoomOut();
	void draw();
	~Minimap();

private:
	int size; //both height and width of a minimap Square representation
	int MINIMAP_HEIGHT_PIXELS;
	int MINIMAP_WIDTH_PIXELS;
	const World * const world;
	const Position * const position;
};

