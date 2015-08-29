#ifndef MAP_H
#define MAP_H
#include "utils.h"
#include "tileSprites.h"
#include "tile.h"


class Tile;
class Map {
	public:
		static const int mapWidth = 50;
		static const int mapHeight = 35;
		Tile *tiles[mapWidth][mapHeight];

		Map(tileSprites *ren);
		~Map();
		void init(tileSprites *);
		void draw(SDL_Renderer *);
		void update();
		bool realTile(int x, int y);
                Tile* getTile(int x, int y);
	private:
};
#endif
