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
#define MAX_X_POSITION SCREEN_WIDTH - 100
#define MAX_Y_POSITION SCREEN_HEIGHT - 100

typedef struct {
	int x;
	int y;
	int dx;
	int dy;
	int mass; /* Reasonable values are between 20 and 200k */
	SDL_Texture *texture;
} star_t;

typedef struct starlist_s {
	star_t star;
	struct starlist_s *next;
} starlist_t;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern int mouse_x;
extern int mouse_y;

extern star_t player;
extern starlist_t *stars;

#endif
