#ifndef MENU_H
#define MENU_H

#include "utils.h"
#include <vector>
#include <string>

typedef struct MenuItem {
	std::string menuText;
	float x, y;
	float left, right, top, bottom;
	float width, height;
} MenuItem;

class Menu {
	private:
		std::vector<MenuItem> menuItems;
                SDL_Renderer *ren;

	public:
                bool visible;
		Menu(SDL_Renderer *ren);
		~Menu();
		void addMenuItem(MenuItem item);
		void addMenuItem(std::string menuText, float x, float y, float left,
				float right, float top, float bottom, float width, float height);
		void toggleMenu(void);
		void destroyMenu(void);
		void draw(void);
                void drawMenuItem(MenuItem* item);
                void handleEvent(SDL_Event &e, int type);
};

#endif /* end of include guard: MENU_H */
