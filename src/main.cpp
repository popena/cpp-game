#include "player.h"
#include "map.h"
#include "particle.h"
#include "tileSprites.h"
#include "menu.h"
#include <iostream>
#include <vector>
#include <time.h>


using namespace std;

bool gameRunning = true;
vector<Particle> particles;
int lastUpdate = 0;
const int UPDATESPERSECOND = 1000/45;
void handleEvent(SDL_Event &e);

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *win = SDL_CreateWindow("testgame", 100, 100, WIDTH, HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	tileSprites *sprites = new tileSprites(renderer);
	Menu menu(renderer);
	Map *m = new Map(sprites);
	Player *p = new Player(renderer, m);
	srand(time(NULL));

	while (gameRunning) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				gameRunning = false;
				break;
			} else if (e.type == SDL_KEYDOWN) {
				p->handleEvent(e, 0);
			} else if (e.type == SDL_KEYUP) {
				p->handleEvent(e, 1);
			} else if (e.type == SDLK_ESCAPE) {
				menu.showMenu();
			}
		} 

                if(SDL_GetTicks() - lastUpdate >= UPDATESPERSECOND) {
                        int now = SDL_GetTicks();
                        int diff = now - lastUpdate - UPDATESPERSECOND;
                        do {
                                diff = now - lastUpdate - UPDATESPERSECOND;
                                p->update();
                                m->update();
                                for (unsigned int i = 0; i < particles.size(); i++) {
                                        particles[i].update();
                                        if (particles[i].time <= 0) {
                                                particles.erase(particles.begin() + i);
                                        }
                                }
                                now = SDL_GetTicks();
                                lastUpdate = now - diff;
                        } while(diff >= UPDATESPERSECOND);
                }
		SDL_RenderClear(renderer); 
		m->draw(renderer);
		p->draw(renderer);
		for (unsigned int i = 0; i < particles.size(); i++) {
			particles[i].draw(renderer);
		}

		/*SDL_Color White = {255, 255, 255};
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(NULL, "Currency:", White); 
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect Message_rect;
		Message_rect.x = 0;
		Message_rect.y = 0;
		Message_rect.w = 100;
		Message_rect.h = 100;*/

		SDL_RenderPresent(renderer);
	}
	delete m;
	delete sprites;
	delete p;

	return 0;
}
