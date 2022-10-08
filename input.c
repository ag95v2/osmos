#include "common.h"

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
