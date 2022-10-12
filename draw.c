#include <common.h>
#include <logic.h>

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

void show_star(star_t *s)
{
	blit(s->texture, s->x, s->y, s->mass);
}

void show_all_stars(void)
{
	starlist_t *current;

	show_star(&player);
	current = stars;
	while (current) {
		show_star(&(current->star));
		current = current->next;
	}
}
