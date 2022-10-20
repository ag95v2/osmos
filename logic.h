#ifndef LOGIC_H
#define LOGIC_H

int get_texture_diam_by_mass(int mass);
void add_star(float x, float y,	float dx, float dy, float mass);
void move_star(star_t *star);
void move_all_stars(void);
void accelerate_player(void);

#endif
