#include "sprite.h"


Sprite::Sprite()
{
}

Sprite::Sprite(SDL_Renderer *ren, const char* imgPath) {
	SDL_Surface* surface = NULL;
	surface = IMG_Load(imgPath);
	spriteTex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(spriteTex);
}

void Sprite::load(SDL_Renderer *ren, const char* imgPath)
{
	SDL_Surface* surface = NULL;
	surface = IMG_Load(imgPath);
	spriteTex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
}

void Sprite::draw(SDL_Renderer *ren, const SDL_Rect *pos)
{
	SDL_RenderCopy(ren, spriteTex, NULL, pos);
}

void Sprite::draw(SDL_Renderer *ren, const SDL_Rect *pos, char r, char g, char b)
{
	SDL_SetTextureColorMod(spriteTex, r, g, b);
	SDL_RenderCopy(ren, spriteTex, NULL, pos);
	SDL_SetTextureColorMod(spriteTex, 255, 255, 255);
}
