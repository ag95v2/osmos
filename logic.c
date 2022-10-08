#include "common.h"

int get_texture_diam_by_mass(int mass)
{
	double r;

	r = sqrt(mass/3.14);
	return (int)(r * 2);
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
