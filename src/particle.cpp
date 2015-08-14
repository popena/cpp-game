#include "utils.h"
#include "particle.h"
#include "sprite.h"
#include "tileSprites.h"
#include <time.h>


Particle::Particle(Sprite *sprite, float x, float y, float velx, float vely, float accx, float accy, int time)
{
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	this->velx = velx;
	this->vely = vely;
	this->accx = accx;
	this->accy = accy;
	this->time = time;
}

Particle::Particle(Sprite *sprite, float x, float y, int time)
{
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	this->velx = (float)(rand() % 20 - 10) / 10;
	this->vely = (float)(rand() % 20 - 10) / 10;
	this->accx = 0;
	this->accy = 0;
	this->time = time;
	this->maxTime = time;
}

void Particle::draw(SDL_Renderer *ren)
{
	pos.x = x;
	pos.y = y;
	pos.w = 5;
	pos.h = 5;
	this->sprite->draw(ren, &pos);
}

void Particle::update()
{
	velx += accx;
	vely += accy;
	x += velx;
	y += vely;
	velx *= 0.90;
	vely *= 0.90;
	accx *= 0.95;
	accy *= 0.95;
	time--;
}
