#include <stdio.h>
#include <stdbool.h>
#include "gol.h"

int main()
{
        int i = 0;
        struct gol gol1;

	bool success = gol_alloc(&gol1, 10, 10);
	if (!success) {
		EXIT_FAILURE;
	}
        gol_init(&gol1);

        do {
                i++;
                gol_step(&gol1);
        } while (i < 40);

        gol_free(&gol1);

        return EXIT_SUCCESS;
}
