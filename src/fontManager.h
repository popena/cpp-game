#ifndef FONTMANAGER_H
#define FONTMANAGER_H
#include "utils.h"
#include <SDL2/SDL_ttf.h>
class FontManager {
	private:
		TTF_Font *big;

	public:
		FontManager();
		~FontManager();
		void showText(SDL_Renderer *ren, const char *text, SDL_Rect *rec);
};
#endif
