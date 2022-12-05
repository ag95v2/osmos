#ifndef LOGIC_H
#define LOGIC_H

int get_texture_diam_by_mass(int mass);
void add_star(double x, double y,	double dx, double dy, double mass);
void move_star(star_t *star);
void move_all_stars(void);
void accelerate_player(void);
void handle_collisions(void);
void delete_small_stars(void);

#endif
