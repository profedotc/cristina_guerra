#ifndef _PERSON_H_
#define _PERSON_H_
#include <stdlib.h>
#include <stdbool.h>

#define TAM_X 10
#define TAM_Y 10

void gol_init(bool mundo[TAM_X][TAM_Y]);
void gol_print(bool mundo[TAM_X][TAM_Y]);
void gol_step(bool mundo0[TAM_X][TAM_Y], bool mundo1[TAM_X][TAM_Y]);
int gol_count_neighbors(bool mundo[TAM_X][TAM_Y], bool *position);
bool gol_get_cell(bool mundo[TAM_X][TAM_Y], bool *position);
#endif
