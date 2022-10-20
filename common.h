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

#define ACCELERAION_DROP_MASS_RATE 0.05
#define ACCELERAION_MASS_SPEED 10.0
#define ACCELERAION_MAGIC_CONSTANT 1.0

#ifndef M_PI
# define M_PI 3.141593
#endif

typedef struct {
	float x; /* Center */
	float y;
	float dx;
	float dy;
	float mass; /* Reasonable values are between 20 and 200k */
	float radius;
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

extern int accelerate;

extern star_t player;
extern starlist_t *stars;

#endif
