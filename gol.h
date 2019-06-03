#ifndef _PERSON_H_
#define _PERSON_H_
#include <stdlib.h>
#include <stdbool.h>

#define TAM_X 10
#define TAM_Y 10

struct gol {
	bool worlds[2][TAM_X][TAM_Y];
	int current_world;
};

void gol_init(struct gol *gol);
void gol_print(const struct gol *gol);
void gol_step(struct gol *gol);
int gol_count_neighbors(bool mundo[TAM_X][TAM_Y], bool *position);
bool gol_get_cell(bool mundo[TAM_X][TAM_Y], bool *position);
#endif
