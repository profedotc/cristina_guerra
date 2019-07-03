#include <stdio.h>
#include <stdbool.h>
#include "gol.h"

int main()
{
        int i = 0;
        struct gol gol1;

	bool success = gol_alloc(&gol1, 10, 20);
	if (!success) {
		EXIT_FAILURE;
	}
        gol_init(&gol1);

        do {
                printf("\033cIteration %d\n", i++);
                gol_print(&gol1);
                gol_step(&gol1);
        } while (getchar() != 'q');

        gol_free(&gol1);

        return EXIT_SUCCESS;
}

