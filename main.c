#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <math.h> /* Sqrt */

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 1200
#define DELAY_MS 16

typedef struct {
	int x;
	int y;
	int mass; /* Reasonable values are between 20 and 200k */
	SDL_Texture *texture;
} star_t;

SDL_Window *window;
SDL_Renderer *renderer;

int mouse_x;
int mouse_y;

star_t player;

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
	window = SDL_CreateWindow("Agario",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT, window_flags);

	renderer_flags = SDL_RENDERER_ACCELERATED;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void handle_events(void)
{
	SDL_Event event;
	int event_cnt;

	event_cnt = 0;
	/* Any events in queue */
	while (SDL_PollEvent(&event))
	{
		event_cnt++;
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouse_x, &mouse_y);
				printf("Event number %d. Mouse state: %d %d\n", event_cnt, mouse_x, mouse_y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_RIGHT){
					;
				}
				if(event.button.button == SDL_BUTTON_MIDDLE){
					;
				}
				if(event.button.button==SDL_BUTTON_LEFT){
					printf("Mouse click\n");
				}
			default:
				break;
		}
	}
}

int get_texture_diam_by_mass(int mass)
{
	double r;

	r = sqrt(mass/3.14);
	return (int)(r * 2);
}

void blit(SDL_Texture *texture, int x, int y, int mass)
{
	SDL_Rect	dest;
	int texture_size;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	texture_size = get_texture_diam_by_mass(mass);
	dest.w = texture_size;
	dest.h = texture_size;
	printf("Width: %d height: %d\n", dest.w, dest.h);
	SDL_RenderCopy(renderer, texture, NULL, &dest); //NULL - copy the entire texture
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
	texture = IMG_LoadTexture(renderer, filename);
	return texture;
}


int main(int argc, char **argv)
{
	int mass;

	mass = atoi(argv[1]);
	init_sdl();

	player.x = 1;
	player.y = 1;
	player.texture = loadTexture("player.png");

	while (1) {
		SDL_SetRenderDrawColor(renderer, 20, 0, 20, 0);
		SDL_RenderClear(renderer); /* Clear screen with color */
		handle_events();
		blit(player.texture, player.x, player.y, mass);
		SDL_Delay(DELAY_MS);
		SDL_RenderPresent(renderer); /* Show all the stuff */
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
