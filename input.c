#include "common.h"

static void handle_keypress(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_Q) {
			exit(0);
		}
	}
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
					accelerate = 1;
					printf("Mouse click\n");
				}
			case SDL_KEYDOWN:
				handle_keypress(&event.key);
				break;
			default:
				break;
		}
	}
}
