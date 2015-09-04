#ifndef TILE_H
#define TILE_H
#include "utils.h"
#include "tileSprites.h"
#include "map.h"


class Map;

class Tile {
	public:
		int type;
		int health;
		int x, y;

		Tile(int x, int y, tileSprites *sprites, int type, Map *);
		void draw(SDL_Renderer *);
		void update();
		bool isBomb();
		bool isDirt();
		bool isStone();
		void takeDamage(int damage);
		int getMaxHealth();
		void changeType(int type);
		void resetHealth();
		void createDamageParticle();
		void explode(int bombSize);
                void drawCorners(SDL_Renderer *ren, Sprite &corner, Sprite &side, int id);
	private:
                void drawDamage(SDL_Renderer *ren, const SDL_Rect &rect, const float &mod);
		tileSprites *sprites;
		Map *m;
};
#endif
