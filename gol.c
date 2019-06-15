#include <stdio.h>
#include <stdbool.h>
#include "gol.h"

static int count_neighbors(bool mundo[TAM_X][TAM_Y], bool *position);
static bool get_cell(bool mundo[TAM_X][TAM_Y], bool *position);

void gol_init(struct gol *gol)
{
	gol->current_world = 0;
	for (int x = 0; x < TAM_X; x++) {
		for (int y = 0; y < TAM_Y; y++) {
			gol->worlds[gol->current_world][x][y] = 0;
		}			
	}
	gol->worlds[gol->current_world][0][1] = 1;
	gol->worlds[gol->current_world][1][2] = 1;
	gol->worlds[gol->current_world][2][0] = 1;
	gol->worlds[gol->current_world][2][1] = 1;
	gol->worlds[gol->current_world][2][2] = 1;

}

void gol_print(const struct gol *gol)
{
	for (int x = 0; x < TAM_X; x++) {
		for (int y = 0; y < TAM_Y; y++) {
			printf("%c ", gol->worlds[gol->current_world][x][y]? '#' : '.');
		}
		printf("\n");
	}
}

void gol_step(struct gol *gol)
{
	int vecinas_vivas = 0;							
	for (int x = 0; x < TAM_X; x++) {
		for (int y = 0; y < TAM_Y; y++) {
			vecinas_vivas = count_neighbors(gol->worlds[gol->current_world], &gol->worlds[gol->current_world][x][y]);
			
			if (gol->worlds[gol->current_world][x][y]) {
				gol->worlds[!gol->current_world][x][y] = (vecinas_vivas == 3) || (vecinas_vivas == 2);
			} else {
				gol->worlds[!gol->current_world][x][y] = (vecinas_vivas == 3);
			}
			vecinas_vivas = 0;
		}
	}
	gol->current_world = !gol->current_world;
}

int count_neighbors(bool mundo[TAM_X][TAM_Y], bool *position)
{
	int vecinas_vivas = 0;
	vecinas_vivas += get_cell(mundo, (position-(TAM_Y-1)));	
	vecinas_vivas += get_cell(mundo, (position-TAM_Y));	
	vecinas_vivas += get_cell(mundo, (position-(TAM_Y+1)));
	vecinas_vivas += get_cell(mundo, (position+1));	
	vecinas_vivas += get_cell(mundo, (position-1));	
	vecinas_vivas += get_cell(mundo, (position+(TAM_Y-1)));	
	vecinas_vivas += get_cell(mundo, (position+TAM_Y));	
	vecinas_vivas += get_cell(mundo, (position+(TAM_Y+1)));

	return vecinas_vivas;
}

bool get_cell(bool mundo[TAM_X][TAM_Y], bool *position)
{
	bool status = *position;

	bool *start = &mundo[0][0];
	bool *end = &mundo[TAM_X - 1][TAM_Y - 1];
	if (position < start || position > end)
		status = 0;

	return status;
}

