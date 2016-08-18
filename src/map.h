#ifndef MAP_H
#define MAP_H
#include "utils.h"
#include "tileSprites.h"
#include "particle.h"
#include "tile.h"
#include "network.h"
#include <vector>


class Tile;
class Network;
class Map {
	public:
		std::vector<Particle> particles;
		static const int mapWidth = WIDTH_TILES;
		static const int mapHeight = HEIGHT_TILES;
		Tile *tiles[mapWidth][mapHeight];

		Map(SDL_Renderer *ren, tileSprites *sprites, Network *net);
		~Map();
		void init(SDL_Renderer *ren, tileSprites *sprites, Network *net);
		void draw();
		void update();
		bool insideBounds(int x, int y);
		Tile* getTile(int x, int y);
		void createBlob(int ox, int oy, int size, int type, int topOf);
		bool nextTo(int ox, int oy, int tile, int range);

		SDL_Renderer *ren;
		tileSprites *sprites;
		Network *net;
	private:
		
};
#endif
