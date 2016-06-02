#include "player.h"
#include "map.h"
#include "tileSprites.h"
#include "menu.h"
#include "network.h"
#include "packet.h"
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
inline void handleKeyboardEvent(SDL_Event &e, Menu *menu, Player *p);
void packetHandler();
Map *m;
Network net;

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
        SDLNet_Init();
	SDL_Window *win = SDL_CreateWindow("testgame", 100, 100, WIDTH, HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	tileSprites *sprites = new tileSprites(renderer);
	Menu menu(renderer);
	m = new Map(sprites);
	Player *p = new Player(renderer, m);
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
                                handleKeyboardEvent(e, &menu, p);
                        }
		} 

                if (!menu.visible) {
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
                        SDL_RenderClear(renderer); 
                        m->draw(renderer);
                        p->draw(renderer);
                } else {
                        SDL_RenderClear(renderer); 
                        menu.draw();
                }

		SDL_RenderPresent(renderer);
	}
	delete m;
	delete sprites;
	delete p;

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

inline void handleKeyboardEvent(SDL_Event &e, Menu *menu, Player *p)
{
	int key = e.key.keysym.scancode;
        static bool escDown;
        if (e.type == SDL_KEYDOWN) {
                if (!menu->visible)
                        p->handleEvent(e, 0);
                else
                        menu->handleEvent(e, 0);
                if (key == SDL_SCANCODE_ESCAPE && !escDown) {
                        p->resetKeys();
                        menu->toggleMenu();
                        escDown = true;
                }
        } else if (e.type == SDL_KEYUP) {
                if (!menu->visible)
                        p->handleEvent(e, 1);
                else
                        menu->handleEvent(e, 1);
                if (key == SDL_SCANCODE_ESCAPE)
                        escDown = false;
        }
}
