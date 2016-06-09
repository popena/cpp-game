#include "menuManager.h"
#include "menu.h"
#include <vector>
#include <stdio.h>

MenuManager::MenuManager(SDL_Renderer *ren, tileSprites *sprites, FontManager *fm)
{
	this->ren = ren;
	this->sprites = sprites;
	this->fm = fm;
	activeMenu = NULL;
	init();
}

void MenuManager::init()
{
	Menu menu(ren, sprites, fm);
	MenuItem test = {"Paused", {WIDTH / 2 - 100, 25, 200, 70}, false, false};
	menu.addMenuItem(test);
	MenuItem button = {"Button", {WIDTH / 2 - 50, 150, 100, 35}, true, true};
	menu.addMenuItem(button);
	MenuItem button2 = {"Button2", {WIDTH / 2 - 50, 200, 100, 35}, true, false};
	menu.addMenuItem(button2);
	addMenu(menu);
}

void MenuManager::addMenu(Menu menu)
{
	menus.push_back(menu);
}

void MenuManager::openMenu(int id)
{
	activeMenu = &menus[id];
}

void MenuManager::closeMenu()
{
	activeMenu = NULL;
}

void MenuManager::draw()
{
	if (activeMenu)
		activeMenu->draw();
}

void MenuManager::handleEvent(SDL_Event &e, int type)
{
	activeMenu->handleEvent(e, type);
}
