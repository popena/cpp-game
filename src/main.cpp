#include "player.h"
#include "map.h"
#include "tileSprites.h"
#include "network.h"
#include "packet.h"

#include "fontManager.h"
#include "menuManager.h"

#include <iostream>
#include <vector>
#include <time.h>
#include <thread>
#include <string>


using namespace std;

bool gameRunning = true;
int lastUpdate = 0;
const int UPDATESPERSECOND = 1000 / 45;
inline void handleKeyboardEvent(SDL_Event &e, MenuManager *mm, Player *p);
void packetHandler();
Map *m;
Network net;

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Window *win = SDL_CreateWindow("testgame", 100, 100, WIDTH, HEIGHT, 0);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	tileSprites *sprites = new tileSprites(ren);

	FontManager fm;


	MenuManager mm(ren, sprites, &fm);


	m = new Map(ren, sprites);
	Player *p = new Player(m);
	srand(time(NULL));


	/* if (!net.initClient("127.0.0.1", 9001)) */
	/* 	fprintf(stderr, "Unable to initialize multiplayer!\n"); */


	while (gameRunning) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				gameRunning = false;
				break;
			} else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
                                handleKeyboardEvent(e, &mm, p);
                        }
		} 

                if (!mm.activeMenu) {
                        if(SDL_GetTicks() - lastUpdate >= UPDATESPERSECOND) {
                                int now = SDL_GetTicks();
                                int diff = now - lastUpdate - UPDATESPERSECOND;
                                do {
                                        diff = now - lastUpdate - UPDATESPERSECOND;
                                        p->update();
                                        m->update();
                                        now = SDL_GetTicks();
                                        lastUpdate = now - diff;
                                } while(diff >= UPDATESPERSECOND);
                        }
                        SDL_RenderClear(ren); 
                        m->draw();
                        p->draw();
                } else {
                        SDL_RenderClear(ren); 
                        mm.draw();
                }

		SDL_RenderPresent(ren);
	}
	delete m;
	delete sprites;
	delete p;
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	return 0;
}

inline void handleKeyboardEvent(SDL_Event &e, MenuManager *mm, Player *p)
{
	int key = e.key.keysym.scancode;
        static bool escDown;
        if (e.type == SDL_KEYDOWN) {
                if (!mm->activeMenu)
                        p->handleEvent(e, 0);
                else
                        mm->handleEvent(e, 0);
                if (key == SDL_SCANCODE_ESCAPE && !escDown) {
                        p->resetKeys();
			if (mm->activeMenu)
				mm->closeMenu();
			else
				mm->openMenu(pauseMenu);
                        escDown = true;
                }
        } else if (e.type == SDL_KEYUP) {
                if (!mm->activeMenu)
                        p->handleEvent(e, 1);
                else
                        mm->handleEvent(e, 1);
                if (key == SDL_SCANCODE_ESCAPE)
                        escDown = false;
        }
}
