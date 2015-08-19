#include "tileSprites.h"
#include "sprite.h"


tileSprites::tileSprites(SDL_Renderer *ren)
{
	this->STONE.load(ren, "Images/stone.png");
	this->DIRT.load(ren, "Images/dirt.png");
	this->AIR.load(ren, "Images/air.png");
	this->TNT.load(ren, "Images/tnt.png");
	this->STONE_PARTICLE.load(ren, "Images/stone_particle.png");
	this->DIRT_PARTICLE.load(ren, "Images/dirt_particle.png");
}

Sprite *tileSprites::getSprite(int id)
{
	switch (id) {
	case STONEID:
		return &this->STONE;
		break;

	case DIRTID:
		return &this->DIRT;
		break;

	case AIRID:
		return &this->AIR;
		break;

	case TNTID:
		return &this->TNT;
		break;

	case STONE_PARTICLEID:
		return &this->STONE_PARTICLE;
		break;

	case DIRT_PARTICLEID:
		return &this->DIRT_PARTICLE;
		break;
	}
	return NULL;
}
