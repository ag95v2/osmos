#include <common.h>
#include <logic.h>

void blit(SDL_Texture *texture, int x, int y, int mass)
{
	SDL_Rect	dest;
	int texture_size;

	texture_size = get_texture_diam_by_mass(mass);
	dest.x = x - texture_size / 2;
	dest.y = y - texture_size / 2;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	dest.w = texture_size;
	dest.h = texture_size;
	printf("Width: %d height: %d mass: %d\n", dest.w, dest.h, mass);
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void show_star(star_t *s)
{
	blit(s->texture, (int)s->x,	(int)s->y, (int)s->mass);
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
