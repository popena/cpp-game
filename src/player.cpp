#include "player.h"
#include "map.h"
#include "sprite.h"


Player::Player(SDL_Renderer *ren, Map *m)
{
	sprite.load(ren, "Images/player.png");
	this->m = m;
	x = 0;
	y = 0;
	pos.x = x * TILE_SIZE;
	pos.y = y * TILE_SIZE;
	pos.w = TILE_SIZE;
	pos.h = TILE_SIZE;
	wDown = false;
	dDown = false;
	sDown = false;
	aDown = false;
	speed = 250;
}

void Player::draw(SDL_Renderer *ren)
{
	pos.x = x * TILE_SIZE;
	pos.y = y * TILE_SIZE;
	sprite.draw(ren, &pos);
}

void Player::handleEvent(const SDL_Event &e, int type)
{
	int scancode = e.key.keysym.scancode;
	if (type == 0) { // keydown
		if (scancode == SDL_SCANCODE_W)
			wDown = true;
		else if (scancode == SDL_SCANCODE_D) 
			dDown = true;
		else if (scancode == SDL_SCANCODE_S) 
			sDown = true;
		else if (scancode == SDL_SCANCODE_A) 
			aDown = true;
		else if (scancode == SDL_SCANCODE_R) 
			m->tiles[x][y]->changeType(TNTID);
	} else if (type == 1) { // keyup
		if (scancode == SDL_SCANCODE_W)
			wDown = false;
		else if (scancode == SDL_SCANCODE_D)
			dDown = false;
		else if (scancode == SDL_SCANCODE_S)
			sDown = false;
		else if (scancode == SDL_SCANCODE_A)
			aDown = false;
	}
}

void Player::move(int rx, int ry)
{
	if (m->realTile(x+rx,y+ry)) {
		if (m->tiles[x+rx][y+ry]->type == AIRID) {
			if (SDL_GetTicks() - lastMoved > speed) {
				x += rx;
				y += ry;
				lastMoved = SDL_GetTicks();
			}
		} else {
			m->tiles[x+rx][y+ry]->takeDamage(1);
		}
	}
}

void Player::update()
{
	if(wDown) {
		move(0, -1);
	}
	if(dDown) { 
		move(1, 0);
	}
	if (sDown) {
		move(0, 1);
	}
	if (aDown) {
		move(-1, 0);
	}
}
