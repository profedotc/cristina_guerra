#include <stdio.h>
#include <stdbool.h>
#include "gol.h"

int main()
{
        int i = 0;
        struct gol gol1;

        gol_init(&gol1);

        do {
                printf("\033cIteration %d\n", i++);
                gol_print(&gol1);
                gol_step(&gol1);
        } while (getchar() != 'q');

        return EXIT_SUCCESS;
}

