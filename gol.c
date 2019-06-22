#include <stdio.h>
#include <stdbool.h>
#include "gol.h"

static int count_neighbors(struct gol *gol, int x, int y);
static bool fix_coords(struct gol *gol, int x, int y);

bool gol_alloc(struct gol *gol, int size_x, int size_y) {
	for( int world = CURRENT; world <= NEXT; world++ ) {
		gol->worlds[world] = malloc(size_x * size_y * sizeof(bool));
		if (!gol->worlds[world]) {
			printf("Error al reservar memoria dinamicamente");
			free(gol->worlds[world]);
			return false;
		}
	}
	gol->size_x = size_x;
	gol->size_y = size_y;
	return true;
}

void gol_free(struct gol *gol) {
	for( int world = CURRENT; world <= NEXT; world++ ) {
		free(gol->worlds[world]);		
	}
}

void gol_init(struct gol *gol)
{
	for (int x = 0; x < gol->size_x; x++) {
		for (int y = 0; y < gol->size_y; y++) {
			set_cell(gol, CURRENT, x, y, 0);
		}			
	}
	set_cell(gol, CURRENT, 0, 1, 1);
	set_cell(gol, CURRENT, 1, 2, 1);
	set_cell(gol, CURRENT, 2, 0, 1);
	set_cell(gol, CURRENT, 2, 1, 1);
	set_cell(gol, CURRENT, 2, 2, 1);
}

void gol_print(const struct gol *gol)
{
	for (int x = 0; x < gol->size_x; x++) {
		for (int y = 0; y < gol->size_y; y++) {
			printf("%c ", *(gol->worlds[CURRENT] + x * gol->size_y + y) ? '#' : '.');
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
			
			if (get_cell(gol, CURRENT, x, y)) {
				bool value = (vecinas_vivas == 3) || (vecinas_vivas == 2);
				set_cell(gol, NEXT, x, y, value);
			} else {
				bool value = (vecinas_vivas == 3);
				set_cell(gol, NEXT, x, y, value);
			}
			vecinas_vivas = 0;
		}
	}							
	bool *world_aux = gol->worlds[CURRENT];
	gol->worlds[CURRENT] = gol->worlds[NEXT];
	gol->worlds[NEXT] = world_aux;
}

int count_neighbors(struct gol *gol, int x, int y)
{
	int vecinas_vivas = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		for(int e = y - 1; e <= y + 1; e++) {
			if (e != y || i != x)
				vecinas_vivas += get_cell(gol, CURRENT, i, e);
		}
	}

	return vecinas_vivas;
}

bool get_cell(struct gol *gol, enum current_world world, int x, int y)
{
	bool status = 0;
	if (fix_coords(gol, x, y))
		status = *(gol->worlds[world] + x * gol->size_y + y);

	return status;
}

void set_cell(struct gol *gol, enum current_world world, int x, int y, bool value) {
	if (fix_coords(gol, x, y)) {
		*(gol->worlds[world] + x * gol->size_y + y) = value;
	}
}

static bool fix_coords(struct gol *gol, int x, int y) {

	bool status = 0;
	if ((x >= 0 && x < gol->size_x ) && (y >= 0 && y < gol->size_y)) {
		status = 1;
	}

	return status;
}

