#ifndef LOGIC_H
#define LOGIC_H

int get_texture_diam_by_mass(int mass);
void add_star(int x, int y,	int dx,	int dy,	int mass);
void move_star(star_t *star);
void move_all_stars(void);

#endif
