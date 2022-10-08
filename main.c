#include "common.h"
#include "init.h"
#include "input.h"

SDL_Window *window;
SDL_Renderer *renderer;

int mouse_x;
int mouse_y;

star_t player;

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
	SDL_RenderCopy(renderer, texture, NULL, &dest);
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
