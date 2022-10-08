#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h> /* Sqrt */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 1200
#define DELAY_MS 16

typedef struct {
	int x;
	int y;
	int mass; /* Reasonable values are between 20 and 200k */
	SDL_Texture *texture;
} star_t;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern int mouse_x;
extern int mouse_y;

extern star_t player;

#endif
