#include "menu.h"


Menu::Menu(SDL_Renderer *ren)
{
        visible = false;
        this->ren = ren;
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
        tmp.left = left;
        tmp.right = right;
        tmp.top = top;
        tmp.bottom = bottom;
        tmp.width = width;
        tmp.height = height;
        addMenuItem(tmp);
}

void Menu::toggleMenu(void)
{
        visible = !visible;
}

void Menu::draw()
{
        SDL_Rect rect;
        rect.w = WIDTH;
        rect.h = HEIGHT;
        rect.x = 0;
        rect.y = 0;
        SDL_RenderDrawRect(ren, &rect);
        for(std::vector<MenuItem>::iterator i = menuItems.begin(); i != menuItems.end(); ++i) {
                drawMenuItem(&(*i));
        }
}

void Menu::handleEvent(SDL_Event &e, int type)
{
}

void Menu::drawMenuItem(MenuItem* item)
{
}

void Menu::destroyMenu(void)
{
	//
}
