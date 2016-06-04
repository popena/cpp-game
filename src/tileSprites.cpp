#include "tileSprites.h"
#include "sprite.h"


tileSprites::tileSprites(SDL_Renderer *ren)
{
	this->DAMAGE_1.load(ren, "Images/damage_1.png");
	this->DAMAGE_2.load(ren, "Images/damage_2.png");
	this->DAMAGE_3.load(ren, "Images/damage_3.png");

	this->SIDE.load(ren, "Images/side2.png");
	this->SIDE_STONE.load(ren, "Images/side_stone.png");

	this->CORNER.load(ren, "Images/corner.png");
	this->CORNER_STONE.load(ren, "Images/corner_stone.png");

	this->STONE_GOLD.load(ren, "Images/stone_gold.png");


	this->STONE.load(ren, "Images/stone.png");
	this->DIRT.load(ren, "Images/dirt.png");
	this->AIR.load(ren, "Images/air.png");
	this->TNT.load(ren, "Images/tnt.png");
	this->STONE_PARTICLE.load(ren, "Images/stone_particle.png");
	this->DIRT_PARTICLE.load(ren, "Images/dirt_particle.png");

	this->DEFAULT_BUTTON.load(ren, "Images/default_button.png");
}

Sprite *tileSprites::getSprite(int id)
{
	switch (id) {
	case STONEID:
		return &this->STONE;
		break;

	case STONE_GOLDID:
		return &this->STONE_GOLD;
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
