#ifndef PLAYER_H
#define PLAYER_H
#include "utils.h"
#include "sprite.h"
#include "map.h"


class Player {
	public:
		Player(Map *);
		void draw();
		void update();
		void handleEvent(const SDL_Event &, int type);
		void move(int x, int y);
		void resetKeys();
	private:
		SDL_Rect pos;
		Sprite sprite;
		Map *m;
		int x;
		int y;
		char direction;
		bool wDown;
		bool dDown;
		bool sDown;
		bool aDown;
		int lastMoved;
		unsigned int speed;
		int currency;
};
#endif
