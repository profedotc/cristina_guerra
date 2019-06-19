#include <stdio.h>
#include <stdbool.h>
#include "gol.h"

static int count_neighbors(struct gol *gol, int x, int y);
static bool get_cell(struct gol *gol, int x, int y);

bool gol_alloc(struct gol *gol, int size_x, int size_y) {
	for( int world = CURRENT; world <= NEXT; world++ ) {
		gol->worlds[world] = malloc(size_x * sizeof(bool(*)));
		if (!gol->worlds[world]) {
			printf("Error al reservar memoria dinamicamente");
			free(gol->worlds[world]);
			return false;
		}
		for (int x = 0; x < size_x; x++) {
			gol->worlds[world][x] = malloc(size_y * sizeof(bool));
			if (!gol->worlds[world][x]) {
				printf("Error al reservar memoria dinamicamente");
				free(gol->worlds[world][x]);
				return false;
			}
		}
	}
	gol->size_x = size_x;
	gol->size_y = size_y;
	return true;
}

void gol_free(struct gol *gol) {
	for( int world = CURRENT; world <= NEXT; world++ ) {
		for (int x = 0; x < gol->size_x; x++) {
			free(gol->worlds[world][x]);
		}
		free(gol->worlds[world]);		
	}
}

void gol_init(struct gol *gol)
{
	for (int x = 0; x < gol->size_x; x++) {
		for (int y = 0; y < gol->size_y; y++) {
			gol->worlds[CURRENT][x][y] = 0;
		}			
	}
	gol->worlds[CURRENT][0][1] = 1;
	gol->worlds[CURRENT][1][2] = 1;
	gol->worlds[CURRENT][2][0] = 1;
	gol->worlds[CURRENT][2][1] = 1;
	gol->worlds[CURRENT][2][2] = 1;

}

void gol_print(const struct gol *gol)
{
	for (int x = 0; x < gol->size_x; x++) {
		for (int y = 0; y < gol->size_y; y++) {
			printf("%c ", gol->worlds[CURRENT][x][y] ? '#' : '.');
		}
		printf("\n");
	}
}

void gol_step(struct gol *gol)
{
	int vecinas_vivas = 0;							
	for (int x = 0; x < gol->size_x; x++) {
		for (int y = 0; y < gol->size_y; y++) {
			vecinas_vivas = count_neighbors(gol, x, y);
			
			if (gol->worlds[CURRENT][x][y]) {
				gol->worlds[NEXT][x][y] = (vecinas_vivas == 3) || (vecinas_vivas == 2);
			} else {
				gol->worlds[NEXT][x][y] = (vecinas_vivas == 3);
			}
			vecinas_vivas = 0;
		}
	}
	bool **world_aux = gol->worlds[CURRENT];
	gol->worlds[CURRENT] = gol->worlds[NEXT];
	gol->worlds[NEXT] = world_aux;
}

int count_neighbors(struct gol *gol, int x, int y)
{
	int vecinas_vivas = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		for(int e = y - 1; e <= y + 1; e++) {
			if (e != y || i != x)
				vecinas_vivas += get_cell(gol, i, e);
		}
	}

	return vecinas_vivas;
}

bool get_cell(struct gol *gol,  int x, int y)
{
	bool status = 0;
	if ((x >= 0 && x < gol->size_x ) && (y >= 0 && y < gol->size_y)) {
		status = gol->worlds[CURRENT][x][y];
	}

	return status;
}

