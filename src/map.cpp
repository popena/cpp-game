#include <cstdlib>
#include <time.h>
#include "map.h"
#include "tile.h"
#include "tileSprites.h"

Map::Map(SDL_Renderer *ren, tileSprites *sprites) 
{
	init(ren, sprites);
}

Map::~Map()
{
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			delete tiles[x][y];
		}
	}
}

void Map::init(SDL_Renderer *ren, tileSprites *sprites)
{
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
                        Tile *t = new Tile(x, y, DIRTID, this);
                        tiles[x][y] = t;
		}
	}
        srand(time(NULL));
        for (int i = 0; i < 50; i++) {
                createBlob(rand() % WIDTH_TILES, rand() % HEIGHT_TILES, rand() % 10 + 3, STONEID, DIRTID);
        }
        for (int i = 0; i < 50; i++) {
                createBlob(rand() % WIDTH_TILES, rand() % HEIGHT_TILES, rand() % 2 + 1, STONE_GOLDID, STONEID);
        }
	this->ren = ren;
	this->sprites = sprites;
}

void Map::createBlob(int ox, int oy, int size, int type, int topOf)
{
        if (size <= 0)
                return;
        if (size == 1 && insideBounds(ox, oy) && tiles[ox][oy]->type == topOf) {
                tiles[ox][oy]->changeType(type);
                return;
        }
        int startx = ox - size / 2;
        int starty = oy - size / 2;
        int endx = ox + size / 2;
        int endy = oy + size / 2;

        for (int x = startx; x < endx; x++) {
                for (int y = starty; y < endy; y++) {
                        if (insideBounds(x, y) && tiles[x][y]->type == topOf) {
                                float dist = (float)sqrt(pow(ox - x, 2) + pow(oy - y, 2));
                                int chance = (1 - (float)dist / (size / 2 + 1)) * 100;
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
                        if (insideBounds(x, y) && dist <= range && tiles[x][y]->type == tile) {
                                return true;
                        }
                }
        }
        return false;
}

/*
 * Check if tile is inside the map
 * */
bool Map::insideBounds(int x, int y)
{
	return (x >= 0 && y >= 0 && x < mapWidth && y < mapHeight);
}

Tile* Map::getTile(int x, int y)
{
        if (insideBounds(x, y))
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
	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i].update();
		if (particles[i].time <= 0) {
			particles.erase(particles.begin() + i);
		}
	}
}

void Map::draw()
{
	for (int x = 0; x < mapWidth; x++){
		for (int y = 0; y < mapHeight; y++) {
			tiles[x][y]->draw();
		}
	}
	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i].draw(ren);
	}
}
