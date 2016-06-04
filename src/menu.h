#ifndef MENU_H
#define MENU_H

#include "utils.h"
#include "tileSprites.h"
#include "fontManager.h"
#include <vector>
#include <string>

typedef struct MenuItem {
	std::string menuText;
	SDL_Rect rect;
} MenuItem;

class Menu {
	private:
		std::vector<MenuItem> menuItems;
                SDL_Renderer *ren;
		tileSprites *sprites;
		FontManager *fm;

	public:
                bool visible;
		Menu(SDL_Renderer *ren, tileSprites *sprites, FontManager *fm);
		~Menu();
		void addMenuItem(MenuItem item);
		void addMenuItem(std::string menuText, int x, int y, int width, int height);
		void toggleMenu(void);
		void destroyMenu(void);
		void draw(void);
                void drawMenuItem(MenuItem* item);
                void handleEvent(SDL_Event &e, int type);
};

#endif /* end of include guard: MENU_H */
