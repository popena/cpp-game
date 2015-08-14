#ifndef PARTICLE_H
#define PARTICLE_H
#include "sprite.h"
#include "utils.h"
#include <vector>


class Particle {
	public:
		float velx, vely;
		float accx, accy;
		float x, y;
		int time;
		int maxTime;
		Sprite *sprite;
		SDL_Rect pos;

		Particle(Sprite *sprite, float x, float y, float velx, float vely, float accx, float accy, int time);
		Particle(Sprite *sprite, float x, float y, int time);
		void draw(SDL_Renderer *);
		void update();
};

extern std::vector<Particle> particles;
#endif
