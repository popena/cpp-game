#include "tile.h"
#include "tileSprites.h"
#include "map.h"
#include "particle.h"
#include <iostream>
#include <algorithm>


Tile::Tile(int x, int y, tileSprites *sprites, int type, Map *m)
{
	this->type = type;
	this->m = m;
	this->x = x;
	this->y = y;
	resetHealth();
	this->sprites = sprites;
}

void Tile::update()
{
	if (isBomb())
		this->takeDamage(1);
}

bool Tile::isBomb()
{
	if (type == TNTID)
		return true;
	return false;
}

int Tile::getMaxHealth()
{
	int hp = 1;
	switch (type) {
		case AIRID:
			hp = 1;
			break;

		case STONEID:
			hp = 100;
			break;

		case DIRTID:
			hp = 25;
			break;

		case TNTID:
			hp = 500;
			break;
	}
	return hp;
}

void Tile::changeType(int type)
{
	this->type = type;
	this->resetHealth();
}

void Tile::resetHealth()
{
	this->health = getMaxHealth();
}

void Tile::createDamageParticle()
{
    Sprite *s = &sprites->STONE_PARTICLE;
    if (this->type == DIRTID)
        s = &sprites->DIRT_PARTICLE;
    Particle p(s, (float)x * TILE_SIZE + TILE_SIZE / 2, (float)y * TILE_SIZE + TILE_SIZE / 2, rand() % 250 + 25);
    particles.push_back(p);
}

void Tile::takeDamage(int dmg)
{
	if (dmg <= 0)
        return;
	if (!isBomb() && this->type != AIRID) {
        if (rand() % (25 / dmg + 1) == 0) {
            createDamageParticle();
        }
	}
	if (this->type != AIRID)
		this->health -= dmg;
	if (this->health < 0) {
		if (isBomb()) {
            explode(16);
		}
		this->changeType(AIRID);
	}
}

void Tile::explode(int bombSize)
{
    for (int y = 0; y < bombSize; y++) {
        for (int x = 0; x < bombSize; x++) {
            int totalx = x + this->x - bombSize / 2;
            int totaly = y + this->y - bombSize / 2;
            if ((totalx != this->x || totaly != this->y)&&m->realTile(totalx, totaly)) {
                float dist = (float)sqrt(pow(totalx - this->x, 2) + pow(totaly - this->y, 2));
                float dmg = (float)bombSize / (float)dist;
                dmg = std::min(pow(dmg / 2, 6), 1000.0);
                this->changeType(AIRID);
                m->tiles[totalx][totaly]->takeDamage((int)dmg);
            }
        }
    }
}

void Tile::draw(SDL_Renderer *ren)
{
	SDL_Rect rect;
	rect.x = x * TILE_SIZE;
	rect.y = y * TILE_SIZE;
	rect.w = TILE_SIZE;
	rect.h = TILE_SIZE;
	Sprite *sprite = sprites->getSprite(this->type);
	float mod = health / (float)getMaxHealth();
	if (mod != 1) {
		if (isBomb())
			sprite->draw(ren, &rect, 255, 255 * mod, 255 * mod);
		else
			sprite->draw(ren, &rect, 255 * mod, 255 * mod, 255 * mod);
	} else {
		sprite->draw(ren, &rect);
	}
}
