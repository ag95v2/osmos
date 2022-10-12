#include "common.h"
#include "init.h"
#include "input.h"
#include "logic.h"
#include "draw.h"

SDL_Window *window;
SDL_Renderer *renderer;

int mouse_x;
int mouse_y;

star_t player;
starlist_t *stars;

int main(int argc, char **argv)
{
	int mass;
	int frame = 0;

	mass = 300;
	if (argc > 1) {
		mass = atoi(argv[1]);
	}
	init_sdl();

	player.x = 1;
	player.y = 1;
	player.dx = 5;
	player.dy = 5;
	player.texture = loadTexture("player.png");
	player.mass = mass;

	add_star(300, 300, -3, 0, 700);
	add_star(500, 300, -3, 2, 300);
	while (1) {
		SDL_SetRenderDrawColor(renderer, 20, 0, 20, 0);
		SDL_RenderClear(renderer); /* Clear screen with color */
		handle_events();
		move_all_stars();
		show_all_stars();
		SDL_Delay(DELAY_MS);
		SDL_RenderPresent(renderer); /* Show all the stuff */
		frame++;
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
