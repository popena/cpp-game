#include "player.h"
#include "map.h"
#include "particle.h"
#include "tileSprites.h"
#include <iostream>
#include <vector>
#include <time.h>


using namespace std;

bool gameRunning = true;
vector<Particle> particles;
void handleEvent(SDL_Event &e);

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *win = SDL_CreateWindow("testgame", 100, 100, WIDTH, HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	tileSprites *sprites = new tileSprites(renderer);
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
			}
		} 

		p->update();
		m->update();
		for (unsigned int i = 0; i < particles.size(); i++) {
			particles[i].update();
			if (particles[i].time <= 0) {
				particles.erase(particles.begin() + i);
			}
		}
        //TODO: better fps system
		SDL_RenderClear(renderer); 
		m->draw(renderer);
		p->draw(renderer);
		for (unsigned int i = 0; i < particles.size(); i++) {
			particles[i].draw(renderer);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(25);
	}
	delete m;
	delete sprites;
	delete p;

	return 0;
}
