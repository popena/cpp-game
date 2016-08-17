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

		Tile(int x, int y, int type, Map *);
		void draw();
		void update();
		bool isBomb();
		bool isDirt();
		bool isStone();
		bool takeDamage(int damage);
		int getMaxHealth();
		void changeType(int type);
		void resetHealth();
		void createDamageParticle();
		void explode(int bombSize);
		void drawCorners(Sprite &corner, Sprite &side, int id);
	private:
		void drawDamage(const SDL_Rect &rect, const float &mod);
		Map *m;
};
#endif
