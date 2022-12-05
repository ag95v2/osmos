#include "common.h"
#include "init.h"
#include "input.h"
#include "logic.h"
#include "draw.h"

SDL_Window *window;
SDL_Renderer *renderer;

int mouse_x;
int mouse_y;

int accelerate;

star_t player;
starlist_t *stars;

int current_star_id = 1;

int main(int argc, char **argv)
{
	int mass;
	int frame = 0;

	mass = 5000.0;
	if (argc > 1) {
		mass = atoi(argv[1]);
	}
	init_sdl();

	player.x = 300.0;
	player.y = 300.0;
	player.dx = 0.0;
	player.dy = 0.0;
	player.texture = loadTexture("player.png");
	player.mass = mass;
	player.id = 0;

	add_star(450,300,0,0,player.mass * 0.8);
	add_star(550,300,0,0,player.mass * 0.8);
	add_star(650,300,0,0,player.mass * 0.8);
	add_star(750,300,0,0,player.mass * 0.8);
	add_star(850,300,0,0,player.mass * 0.8);

	add_star(350,900,0,0,player.mass * 2);
	add_star(850,600,0,0,player.mass * 4);
	add_star(550,700,0,0,player.mass * 3);

	while (1) {
		SDL_SetRenderDrawColor(renderer, 20, 0, 20, 0);
		SDL_RenderClear(renderer); /* Clear screen with color */
		handle_events();
		if (accelerate) {
			accelerate_player();
			accelerate = 0;
		}
		move_all_stars();
		handle_collisions();
		delete_small_stars();
		show_all_stars();
		SDL_Delay(DELAY_MS);
		SDL_RenderPresent(renderer); /* Show all the stuff */
		frame++;
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
