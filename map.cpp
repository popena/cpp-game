#include "map.h"
#include "tile.h"
#include "tileSprites.h"


Map::Map(tileSprites *sprites) 
{
	init(sprites);
}

Map::~Map()
{
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			delete tiles[x][y];
		}
	}
}

void Map::init(tileSprites *sprites)
{
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			if (x + y > mapHeight / 1.2) {
				Tile *t = new Tile(x, y, sprites, STONEID, this);
				tiles[x][y] = t;
			} else {
				Tile *t = new Tile(x, y, sprites, DIRTID, this);
				tiles[x][y] = t;
			}
		}
	}
}

/*
 * Check if tile is inside the map
 * */
bool Map::realTile(int x, int y)
{
	return (x >= 0 && y >= 0 && x < mapWidth && y < mapHeight);
}

void Map::update()
{
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			tiles[x][y]->update();
		}
	}
}

void Map::draw(SDL_Renderer *ren)
{
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++){
			tiles[x][y]->draw(ren);
		}
	}
}
