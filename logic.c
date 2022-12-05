#include "common.h"

double circle_intersection_area(circle_t p1, circle_t p2) {
	double d;
	double a;
	double b;
	double x;
	double y;
	double z;

	d = hypot(p2.x - p1.x, p2.y - p1.y);

	if (d < p1.r + p2.r) {

		a = p1.r * p1.r;
		b = p2.r * p2.r;

		x = (a - b + d * d) / (2 * d);
		z = x * x;
		y = sqrt(a - z);

		if (d <= abs(p2.r - p1.r)) {
			return (M_PI * MIN(a, b));
		}
		return (a * asin(y / p1.r) + b * asin(y / p2.r)
				- y * (x + sqrt(z + b - a)));
	}
	return (0);
}

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

void add_star(double x, double y, double dx, double dy,	double mass)
{
	starlist_t *new;

	new = malloc(sizeof(starlist_t));
	new->star.x = x;
	new->star.y = y;
	new->star.dx = dx;
	new->star.dy = dy;
	new->star.mass = mass;
	new->star.texture = player.texture;
	new->star.id = current_star_id;
	current_star_id++;
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
	if (s->x <= texture_side / 2 ||
			s->x + texture_side / 2 >= MAX_X_POSITION) {
		s->dx = s->dx * (-1);
		s->x = (s->x <= texture_side / 2) ?
			texture_side / 2 : MAX_X_POSITION - texture_side / 2;
	}
	if (s->y <= texture_side / 2 ||
			s->y + texture_side / 2 >= MAX_Y_POSITION) {
		s->dy = s->dy * (-1);
		s->y = (s->y <= texture_side / 2) ?
			texture_side / 2 : MAX_Y_POSITION - texture_side / 2;
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
	double alpha;
	double new_star_mass;
	double new_star_diam;
	double new_star_x;
	double new_star_y;

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
	player.dx -= ACCELERAION_MASS_SPEED * cosf(alpha) *
		ACCELERAION_DROP_MASS_RATE * ACCELERAION_MAGIC_CONSTANT;
	player.dy -= ACCELERAION_MASS_SPEED * sinf(alpha) *
		ACCELERAION_DROP_MASS_RATE * ACCELERAION_MAGIC_CONSTANT;
}

void handle_collision(star_t *a, star_t *b)
{
	circle_t c1;
	circle_t c2;
	double area;

	/* Avoid double handling */
	if (a->id >= b->id) {
		return ;
	}
	c1.x = a->x;
	c1.y = a->y;
	c2.x = b->x;
	c2.y = b->y;
	c1.r = a->radius;
	c2.r = b->radius;
	
	area = circle_intersection_area(c1, c2);
	if (area > 0) {
		printf("Stars intersect: x1=%.2f y1=%.2f r1=%.2f x2=%.2f y2=%.2f r2=%.2f area=%.2f\n", 
				a->x, a->y, a->radius,
				b->x, b->y, b->radius,
				area
				);
		if (a->radius >= b->radius) {
			a->dx = (a->dx * a->mass + b->dx * area) / (a->mass + area);
			a->dy = (a->dy * a->mass + b->dy * area) / (a->mass + area);
			a->mass += area;
			b->mass -= area;
		}
		else {
			b->dx = (b->dx * b->mass + a->dx * area) / (b->mass + area);
			b->dy = (b->dy * b->mass + a->dy * area) / (b->mass + area);
			a->mass -= area;
			b->mass += area;
		}
	}
}

void handle_collisions_of_star(star_t *s)
{
	starlist_t *current;

	current = stars;
	while (current) {
		handle_collision(s, &(current->star));
		current = current->next;
	}
}

void handle_collisions(void)
{
	starlist_t *current;

	handle_collisions_of_star(&player);
	current = stars;
	while (current) {
		handle_collisions_of_star(&(current->star));
		current = current->next;
	}
}

void delete_small_stars(void)
{
	starlist_t *current;
	starlist_t *prev;
	starlist_t *tmp;
	
	current = stars;
	prev = NULL;
	while (current) {
		if (current->star.mass < MIN_DISPLAYABLE_MASS) {
			if (prev) {
				prev->next = current->next;
			}
			else {
				stars = current->next;
			}
			tmp = current;
			free(current);
			current = tmp->next;
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}
