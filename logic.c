#include "common.h"

void move_star(star_t *s)
{
	s->x += s->dx;
	s->y += s->dy;
}
