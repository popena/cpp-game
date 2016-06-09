#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "utils.h"
#include "tileSprites.h"
#include "fontManager.h"
#include "menu.h"
#include <vector>
#include <string>

enum menuType {
	pauseMenu,
	testMenu
};

class MenuManager {
	private:
		std::vector<Menu> menus;
                SDL_Renderer *ren;
		tileSprites *sprites;
		FontManager *fm;
	public:
		Menu *activeMenu;

		MenuManager(SDL_Renderer *ren, tileSprites *sprites, FontManager *fm);
		void openMenu(int id);
		void closeMenu();
		void init();
		void addMenu(Menu menu);
		void draw();
                void handleEvent(SDL_Event &e, int type);
};

#endif
