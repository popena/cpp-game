#ifndef MAP_H
#define MAP_H
#include "utils.h"
#include "tileSprites.h"
#include "tile.h"


class Tile;
class Map {
	public:
		static const int mapWidth = WIDTH_TILES;
		static const int mapHeight = HEIGHT_TILES;
		Tile *tiles[mapWidth][mapHeight];

		Map(tileSprites *ren);
		~Map();
		void init(tileSprites *);
		void draw(SDL_Renderer *);
		void update();
		bool realTile(int x, int y);
                Tile* getTile(int x, int y);
                void createBlob(int ox, int oy, int size, int type);
                bool nextTo(int ox, int oy, int tile, int range);
	private:
                
};
#endif
