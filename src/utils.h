#ifndef UTILS_H
#define UTILS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TILE_SIZE 16
#define WIDTH_TILES 50
#define HEIGHT_TILES 35
#define WIDTH TILE_SIZE * WIDTH_TILES
#define HEIGHT TILE_SIZE * HEIGHT_TILES

enum tiles {
	AIRID,
	STONEID,
	DIRTID,
	TNTID,
	STONE_PARTICLEID,
	DIRT_PARTICLEID,
        STONE_GOLDID
};
#endif
