#ifndef SPRITE_H
#define SPRITE_H
#include "utils.h"


class Sprite {
	public:
		Sprite();
		Sprite(SDL_Renderer *, const char*);
		~Sprite();

		void load(SDL_Renderer *, const char* imgPath);
		void draw(SDL_Renderer *, const SDL_Rect *rect);
		void draw(SDL_Renderer *, const SDL_Rect *rect, char r, char g, char b);
	private:
		SDL_Texture *spriteTex;
};
#endif
