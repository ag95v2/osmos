#include "common.h"

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
			SDL_LOG_PRIORITY_INFO,
			"Loading %s", filename);
	texture = IMG_LoadTexture(renderer, filename);
	return texture;
}

void init_sdl()
{
	int window_flags;
	int renderer_flags;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window_flags = 0;
	window = SDL_CreateWindow("Osmos",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT, window_flags);

	renderer_flags = SDL_RENDERER_ACCELERATED;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}
