#include "menu.h"
#include "tileSprites.h"


Menu::Menu(SDL_Renderer *ren, tileSprites *sprites, FontManager *fm)
{
        visible = false;
        this->ren = ren;
	this->sprites = sprites;
	this->fm = fm;
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

void Menu::addMenuItem(std::string menuText, int x, int y, int width, int height)
{
	MenuItem tmp;
	tmp.menuText = menuText;
	tmp.rect.x = x;
	tmp.rect.y = y;
        tmp.rect.w = width;
        tmp.rect.h = height;
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

void Menu::drawMenuItem(MenuItem *item)
{
	sprites->DEFAULT_BUTTON.draw(this->ren, &item->rect);
	this->fm->showText(this->ren, item->menuText.c_str(), &item->rect);
}

void Menu::destroyMenu(void)
{
	//
}
