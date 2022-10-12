#include "common.h"

int get_texture_diam_by_mass(int mass)
{
	double r;

	r = sqrt(mass/3.14);
	return (int)(r * 2);
}

void add_star(int x, int y,	int dx,	int dy,	int mass)
{
	starlist_t *new;

	new = malloc(sizeof(starlist_t));
	new->star.x = x;
	new->star.y = y;
	new->star.dx = dx;
	new->star.dy = dy;
	new->star.mass = mass;
	new->star.texture = player.texture;
	new->next = stars;
	stars = new;
}

void move_star(star_t *s)
{
	int texture_side;

	s->x += s->dx;
	s->y += s->dy;

	texture_side = get_texture_diam_by_mass(s->mass);
	/* Wall collisions */
	if (s->x <= 0 || s->x + texture_side >= MAX_X_POSITION) {
		s->dx = s->dx * (-1);
	}
	if (s->y <= 0 || s->y + texture_side >= MAX_Y_POSITION) {
		s->dy = s->dy * (-1);
	}
}

void move_all_stars(void)
{
	starlist_t *current;

	move_star(&player);
	current = stars;
	while (current) {
		move_star(&(current->star));
		current = current->next;
	}
}
