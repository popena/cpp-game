#include "menu.h"


Menu::Menu(SDL_Renderer *ren)
{
	//
}

Menu::~Menu(void)
{
	//
}

void Menu::addMenuItem(MenuItem item)
{
	this->menuItems.push_back(item);
}

void Menu::addMenuItem(std::string menuText, float x, float y, float left, float right,
					   float top, float bottom, float width, float height)
{
	MenuItem tmp;

	tmp.menuText = menuText;
	tmp.x = x;
	tmp.y = y;
}

void Menu::showMenu(void)
{
	//
}

void Menu::destroyMenu(void)
{
	//
}
