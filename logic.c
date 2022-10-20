#include "common.h"

int get_texture_diam_by_mass(int mass)
{
	double r;

	r = sqrt(mass/3.14);
	return (int)(r * 2);
}

void calculate_star_data(star_t *s)
{
	int diam;

	diam = get_texture_diam_by_mass(s->mass);
	s->radius = diam / 2;
}

void add_star(float x, float y,	float dx, float dy,	float mass)
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

	texture_side = get_texture_diam_by_mass((int)s->mass);
	/* Wall collisions */
	if (s->x <= texture_side / 2 || s->x + texture_side / 2 >= MAX_X_POSITION) {
		s->dx = s->dx * (-1);
		s->x = (s->x <= texture_side / 2) ? texture_side / 2 : MAX_X_POSITION - texture_side / 2;
	}
	if (s->y <= texture_side / 2 || s->y + texture_side / 2 >= MAX_Y_POSITION) {
		s->dy = s->dy * (-1);
		s->y = (s->y <= texture_side / 2) ? texture_side / 2 : MAX_Y_POSITION - texture_side / 2;
	}
	calculate_star_data(s);
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

void accelerate_player(void)
{
	float alpha;
	float new_star_mass;
	float new_star_diam;
	float new_star_x;
	float new_star_y;

	new_star_mass = player.mass * ACCELERAION_DROP_MASS_RATE;
	player.mass -= new_star_mass;
	new_star_diam = get_texture_diam_by_mass(new_star_mass);
	alpha = atanf((mouse_y - player.y) / (mouse_x - player.x));
	
	/* 
	** alpha is in range [-pi/2 : pi/2] so we need adjustment
	*/
	if ((mouse_y - player.y >= 0) && (mouse_x - player.x <= 0)) {
		alpha -= M_PI;
	}
	if ((mouse_y - player.y <= 0) && (mouse_x - player.x <= 0)) {
		alpha -= M_PI;
	}

	new_star_x = (player.radius + new_star_diam / 2) * cosf(alpha) + player.x;
	new_star_y = (player.radius + new_star_diam / 2) * sinf(alpha) + player.y;

	add_star(new_star_x, new_star_y,
			ACCELERAION_MASS_SPEED * cosf(alpha),
			ACCELERAION_MASS_SPEED * sinf(alpha), new_star_mass);
	player.dx -= ACCELERAION_MASS_SPEED * cosf(alpha) * ACCELERAION_DROP_MASS_RATE * ACCELERAION_MAGIC_CONSTANT;
	player.dy -= ACCELERAION_MASS_SPEED * sinf(alpha) * ACCELERAION_DROP_MASS_RATE * ACCELERAION_MAGIC_CONSTANT;
}
