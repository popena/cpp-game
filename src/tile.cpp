#include "tile.h"
#include "tileSprites.h"
#include "map.h"
#include "particle.h"
#include "packetTypes.h"
#include "network.h"
#include <iostream>
#include <algorithm>


Tile::Tile(int x, int y, int type, Map *m)
{
	this->type = type;
	this->m = m;
	this->x = x;
	this->y = y;
	resetHealth();
}

void Tile::update()
{
	if (isBomb())
		this->takeDamage(10);
}

bool Tile::isBomb()
{
	return (type == TNTID);
}

bool Tile::isDirt()
{
	return (type == DIRTID);
}

bool Tile::isStone()
{
	return (type == STONEID || type == STONE_GOLDID);
}

int Tile::getMaxHealth()
{
	int hp = 1;
	switch (type) {
		case AIRID:
			hp = 1;
			break;

		case STONEID:
		case STONE_GOLDID:
			hp = 1000;
			break;

		case DIRTID:
			hp = 250;
			break;

		case TNTID:
			hp = 5000;
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
    Sprite *s = &m->sprites->STONE_PARTICLE;
    if (this->type == DIRTID)
	s = &m->sprites->DIRT_PARTICLE;
    Particle p(s, (float)x * TILE_SIZE + TILE_SIZE / 2, (float)y * TILE_SIZE + TILE_SIZE / 2, rand() % 250 + 25);
    m->particles.push_back(p);
}

bool Tile::takeDamage(int dmg)
{
	if (dmg <= 0)
		return false;
	if (!isBomb() && this->type != AIRID) {
		if (rand() % (250 / dmg + 1) == 0) {
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
		if (m->net->connected) {
			PACKET_TILECHANGE p = {x, y, 0};
			m->net->sendData(m->net->TILECHANGE, &p, sizeof(p));
		}
		return true;
	}
	return false;
}

void Tile::explode(int bombSize)
{
    for (int y = 0; y < bombSize; y++) {
	for (int x = 0; x < bombSize; x++) {
	    int totalx = x + this->x - bombSize / 2;
	    int totaly = y + this->y - bombSize / 2;
	    if ((totalx != this->x || totaly != this->y) && m->insideBounds(totalx, totaly)) {
		float dist = (float)sqrt(pow(totalx - this->x, 2) + pow(totaly - this->y, 2));
		float dmg = (float)bombSize / (float)dist;
		dmg = std::min(pow(dmg / 2, 6), 1000.0) * 10;
		this->changeType(AIRID);
		m->tiles[totalx][totaly]->takeDamage((int)dmg);
	    }
	}
    }
}

void Tile::drawDamage(const SDL_Rect &rect, const float &mod)
{
	if (mod <= 0.3)
		m->sprites->DAMAGE_3.draw(m->ren, &rect);
	else if (mod <= 0.6)
		m->sprites->DAMAGE_2.draw(m->ren, &rect);
	else if (mod <= 0.9)
		m->sprites->DAMAGE_1.draw(m->ren, &rect);
}

void Tile::drawCorners(Sprite &corner, Sprite &side, int id)
{
	SDL_Rect rect;
	rect.x = x * TILE_SIZE;
	rect.y = y * TILE_SIZE;
	rect.w = TILE_SIZE;
	rect.h = TILE_SIZE;
	bool airDown = (y > 0 && m->getTile(this->x, this->y - 1)->type == id);
	bool airTop = (y < HEIGHT_TILES - 1 && m->getTile(this->x, this->y + 1)->type == id);
	bool airRight = (x > 0 && m->getTile(this->x - 1, this->y)->type == id);
	bool airLeft = (x < WIDTH_TILES - 1 && m->getTile(this->x + 1, this->y)->type == id);
	if (airDown) {
		side.draw(m->ren, &rect, 0.0);
		if (airRight) 
			corner.draw(m->ren, &rect, 0.0);
	}
	if (airTop) {
		side.draw(m->ren, &rect, 180.0);
		if (airLeft) 
			corner.draw(m->ren, &rect, 180.0);
	}
	if (airRight) {
		side.draw(m->ren, &rect, 270.0);
		if (airTop) 
			corner.draw(m->ren, &rect, 270.0);
	}
	if (airLeft) {
		side.draw(m->ren, &rect, 90.0);
		if (airDown) 
			corner.draw(m->ren, &rect, 90.0);
	}
}

void Tile::draw()
{
	SDL_Rect rect;
	rect.x = x * TILE_SIZE;
	rect.y = y * TILE_SIZE;
	rect.w = TILE_SIZE;
	rect.h = TILE_SIZE;
	Sprite *sprite = m->sprites->getSprite(this->type);
	float mod = health / (float)getMaxHealth();
	if (mod != 1) {
		if (isBomb()) {
			sprite->draw(m->ren, &rect, 255, 255 * mod, 255 * mod);
		} else {
			sprite->draw(m->ren, &rect);
			drawDamage(rect, mod);
		}
	} else {
		sprite->draw(m->ren, &rect);
	}
	if (this->type != AIRID && !isBomb()) {
		drawCorners(m->sprites->CORNER, m->sprites->SIDE, AIRID);
		if (!isStone()) {
			drawCorners(m->sprites->CORNER_STONE, m->sprites->SIDE_STONE, STONEID);
			drawCorners(m->sprites->CORNER_STONE, m->sprites->SIDE_STONE, STONE_GOLDID);
		}
	}
}
