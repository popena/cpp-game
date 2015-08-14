#ifndef UTILS_H
#define UTILS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


const int TILE_SIZE = 16;
const int WIDTH = TILE_SIZE * 50;
const int HEIGHT = TILE_SIZE * 35;
enum tiles {
	AIRID,
	STONEID,
	DIRTID,
	TNTID,
	STONE_PARTICLEID,
	DIRT_PARTICLEID
};
#endif
