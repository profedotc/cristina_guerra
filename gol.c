#include <stdio.h>
#include <stdbool.h>
#include "gol.h"

int main()
{
	int i = 0;
	bool mundo[2][TAM_X][TAM_Y];
	int index = 0;
	
	gol_init(mundo[index]);

	do {
		printf("\033cIteration %d\n", i++);
		gol_print(mundo[index]);
		int new_index = index ? 0 : 1;
		gol_step(mundo[index], mundo[new_index]);
		index = new_index;
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void gol_init(bool mundo[TAM_X][TAM_Y])
{
	for (int x = 0; x < TAM_X; x++) {
		for (int y = 0; y < TAM_Y; y++) {
			mundo[x][y] = 0;
		}			
	}
	mundo[0][1] = 1;
	mundo[1][2] = 1;
	mundo[2][0] = 1;
	mundo[2][1] = 1;
	mundo[2][2] = 1;

}

void gol_print(bool mundo[TAM_X][TAM_Y])
{
	for (int x = 0; x < TAM_X; x++) {
		for (int y = 0; y < TAM_Y; y++) {
			printf("%c ", mundo[x][y]? '#' : '.');
		}
		printf("\n");
	}
}

void gol_step(bool mundo0[TAM_X][TAM_Y], bool mundo1[TAM_X][TAM_Y])
{
	int vecinas_vivas = 0;							
	for (int x = 0; x < TAM_X; x++) {
		for (int y = 0; y < TAM_Y; y++) {
			vecinas_vivas = gol_count_neighbors(mundo0, &mundo0[x][y]);
			
			if (mundo0[x][y]) {
				mundo1[x][y] = (vecinas_vivas == 3) || (vecinas_vivas == 2);
			} else {
				mundo1[x][y] = (vecinas_vivas == 3);
			}
			vecinas_vivas = 0;
		}
	}
}

int gol_count_neighbors(bool mundo[TAM_X][TAM_Y], bool *position)
{
	int vecinas_vivas = 0;
	vecinas_vivas += gol_get_cell(mundo, (position-(TAM_Y-1)));	
	vecinas_vivas += gol_get_cell(mundo, (position-TAM_Y));	
	vecinas_vivas += gol_get_cell(mundo, (position-(TAM_Y+1)));
	vecinas_vivas += gol_get_cell(mundo, (position+1));	
	vecinas_vivas += gol_get_cell(mundo, (position-1));	
	vecinas_vivas += gol_get_cell(mundo, (position+(TAM_Y-1)));	
	vecinas_vivas += gol_get_cell(mundo, (position+TAM_Y));	
	vecinas_vivas += gol_get_cell(mundo, (position+(TAM_Y+1)));

	return vecinas_vivas;
}

bool gol_get_cell(bool mundo[TAM_X][TAM_Y], bool *position)
{
	bool status = *position;

	bool *start = &mundo[0][0];
	bool *end = &mundo[TAM_X - 1][TAM_Y - 1];
	if (position < start || position > end)
		status = 0;

	return status;
}
