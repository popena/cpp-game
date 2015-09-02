#include <cstdlib>
#include <time.h>
#include "map.h"
#include "tile.h"
#include "tileSprites.h"

Map::Map(tileSprites *sprites) 
{
	init(sprites);
}

Map::~Map()
{
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			delete tiles[x][y];
		}
	}
}

void Map::init(tileSprites *sprites)
{
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
                        Tile *t = new Tile(x, y, sprites, DIRTID, this);
                        tiles[x][y] = t;
		}
	}
        srand(time(NULL));
        for (int i = 0; i < 50; i++) {
                createBlob(rand() % WIDTH_TILES, rand() % HEIGHT_TILES, rand() % 10 + 3, STONEID);
        }
}

void Map::createBlob(int ox, int oy, int size, int type)
{
        if (size <= 0)
                return;
        int startx = ox - size / 2;
        int starty = oy - size / 2;
        int endx = ox + size / 2;
        int endy = oy + size / 2;

        for (int x = startx; x < endx; x++) {
                for (int y = starty; y < endy; y++) {
                        if (realTile(x, y)) {
                                float dist = (float)sqrt(pow(ox - x, 2) + pow(oy - y, 2));
                                if (dist <= 0)
                                        dist = 1;
                                int chance = (1 - (float)dist / (size / 2)) * 100;
                                if (nextTo(x, y, type, 2))
                                        chance *= 4;
                                if (rand() % 100 <= chance)
                                        tiles[x][y]->changeType(type);
                        }
                }
        }
}

/*
 * Check if there is specific tile near the position
 */
bool Map::nextTo(int ox, int oy, int tile, int range)
{
        int startx = ox - range / 2;
        int starty = oy - range / 2;
        int endx = ox + range / 2;
        int endy = oy + range / 2;
        for (int x = startx; x < endx; x++) {
                for (int y = starty; y < endy; y++) {
                        float dist = (float)sqrt(pow(ox - x, 2) + pow(oy - y, 2));
                        if (realTile(x, y) && dist <= range && tiles[x][y]->type == tile) {
                                return true;
                        }
                }
        }
        return false;
}

/*
 * Check if tile is inside the map
 * */
bool Map::realTile(int x, int y)
{
	return (x >= 0 && y >= 0 && x < mapWidth && y < mapHeight);
}

Tile* Map::getTile(int x, int y)
{
        if (realTile(x, y))
                return tiles[x][y];
        else
                return NULL;
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
	for (int x = 0; x < mapWidth; x++){
		for (int y = 0; y < mapHeight; y++) {
			tiles[x][y]->draw(ren);
		}
	}
}
