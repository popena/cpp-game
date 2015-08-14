#ifndef TILESPRITES_H
#define TILESPRITES_H
#include "sprite.h"
#include "utils.h"


class tileSprites {
	public:
		Sprite STONE;
		Sprite DIRT;
		Sprite AIR;
		Sprite TNT;
		Sprite STONE_PARTICLE;
		Sprite DIRT_PARTICLE;

		tileSprites(SDL_Renderer *ren);
		Sprite* getSprite(int id);
};
#endif
