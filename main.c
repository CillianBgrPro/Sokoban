#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "init.h"

int main() {
    char *tab_values = create_board();
    char *objects = init_objects();
    char move;

    for (int i = 0; i < 100; i++) {
        tab_values[i] = objects[i];
    }

    free(objects);

    while (true) {
        display_board(tab_values);

        printf("Choisissez un mouvement : haut(z) bas(s) gauche(q) droite(d)\n");
        scanf(" %c", &move);

        if (!is_valid_move(tab_values, move)) {
            printf("Choix invalide, réessayez.\n");
            continue;
        }

    }

    free(tab_values);
    return 0;
}
