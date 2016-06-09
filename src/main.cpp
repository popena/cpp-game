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

#include <SDL/SDL_net.h>


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
        SDLNet_Init();
	TTF_Init();
	SDL_Window *win = SDL_CreateWindow("testgame", 100, 100, WIDTH, HEIGHT, 0);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	tileSprites *sprites = new tileSprites(ren);

	FontManager fm;


	MenuManager mm(ren, sprites, &fm);


	m = new Map(ren, sprites);
	Player *p = new Player(m);
	srand(time(NULL));




        if (net.connect("127.0.0.1", 9001)) {
                net.sendMsg("test");
                thread network(packetHandler);
                network.detach();
        }

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


void packetHandler()
{
        char *msg = NULL;
        while (1) {
                if (net.recvMsg(msg) != -1) {
                        string sMsg = string(msg);
                        cout << sMsg << endl;
                        string *buff = new string[4];
                        splitPacket(buff, sMsg);
                        /* string test = "123,2,3,4"; */
                        /* string buff[4]; */
                        /* parsePacket2(test, buff, 4); */
                        /* cout << buff[0] << endl; */
                        /* int type = atoi(parsePacket(sMsg, 0).c_str()); */
                        /* int x = atoi(parsePacket(sMsg, 1).c_str()); */
                        /* int y = atoi(parsePacket(sMsg, 2).c_str()); */
                        /* int tileType = atoi(parsePacket(sMsg, 2).c_str()); */
                        /* m->tiles[x][y]->changeType(tileType); */
                        delete [] buff;
                } else {
                        cout << "Connection lost" << endl;
                        break;
                }
        }
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
