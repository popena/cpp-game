#include "utils.h"
#include "fontManager.h"
#include <stdio.h>

FontManager::FontManager()
{
	big = TTF_OpenFont("Fonts/FreeMono.ttf", 70);
	if (!big)
		printf("TTF_OpenFont: %s\n", TTF_GetError());
}

void FontManager::showText(SDL_Renderer *ren, const char *text, SDL_Rect *rec)
{
	SDL_Color color = {255, 50, 50};

	SDL_Surface* surfMessage = TTF_RenderText_Solid(this->big, text, color);
	SDL_Texture* texMessage = SDL_CreateTextureFromSurface(ren, surfMessage);
	SDL_RenderCopy(ren, texMessage, NULL, rec);
	SDL_FreeSurface(surfMessage);
	SDL_DestroyTexture(texMessage);
}
