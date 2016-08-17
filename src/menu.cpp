#include "menu.h"
#include "tileSprites.h"
#include <stdio.h>


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

unsigned int Menu::getFocusedElement()
{
	for (unsigned int i = 0; i < menuItems.size(); i++) {
		if (menuItems[i].focus)
			return i;
	}
	return -1;
}

void Menu::handleEvent(SDL_Event &e, int type)
{
	int key = e.key.keysym.scancode;
	if (type == 0) {
		switch (key) {
		case SDL_SCANCODE_W:
			moveMenuFocus(-1);
			break;
		case SDL_SCANCODE_S:
			moveMenuFocus(1);
			break;
		case SDL_SCANCODE_RETURN:
			puts(menuItems[getFocusedElement()].menuText.c_str());
			break;
		} 
	}
}

void Menu::moveMenuFocus(int change)
{
	unsigned int curFocus = getFocusedElement();
	if (change == 0 || curFocus + change < 0 || curFocus + change > menuItems.size())
		return;
	if (!menuItems[curFocus + change].canFocus) {
		if (change > 0)
			moveMenuFocus(change + 1);
		else 
			moveMenuFocus(change - 1);
	} else {
		menuItems[curFocus].focus = false;
		menuItems[curFocus + change].focus = true;
	}
}

void Menu::drawMenuItem(MenuItem *item)
{
	if (item->focus)
		sprites->ACTIVE_BUTTON.draw(this->ren, &item->rect);
	else
		sprites->DEFAULT_BUTTON.draw(this->ren, &item->rect);
	this->fm->showText(this->ren, item->menuText.c_str(), &item->rect);
}

void Menu::destroyMenu(void)
{
	//
}
