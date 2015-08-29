#ifndef PLAYER_H
#define PLAYER_H
#include "utils.h"
#include "sprite.h"
#include "map.h"


class Player {
	public:
		Player(SDL_Renderer *ren, Map *);
		void draw(SDL_Renderer *ren);
		void update();
		void handleEvent(const SDL_Event &, int type);
		void move(int x, int y);

		SDL_Rect pos;
		int x;
		int y;
		char direction;
		bool wDown;
		bool dDown;
		bool sDown;
		bool aDown;
		int lastMoved;
		unsigned int speed;
	private:
		Sprite sprite;
		Map *m;
};
#endif
