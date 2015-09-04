#ifndef TILESPRITES_H
#define TILESPRITES_H
#include "sprite.h"
#include "utils.h"


class tileSprites {
	public:
		Sprite DAMAGE_1;
		Sprite DAMAGE_2;
		Sprite DAMAGE_3;

		Sprite SIDE;
                Sprite SIDE_STONE;

		Sprite CORNER;
		Sprite CORNER_STONE;
                
		Sprite STONE;
		Sprite DIRT;
		Sprite AIR;
		Sprite TNT;
		Sprite STONE_PARTICLE;
		Sprite DIRT_PARTICLE;

		tileSprites(SDL_Renderer *ren);
		Sprite *getSprite(int id);
};
#endif
