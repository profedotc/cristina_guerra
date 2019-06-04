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

