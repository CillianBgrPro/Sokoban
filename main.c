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

        if (check_win(tab_values)) {
            printf("\nFelicitations ! Vous avez gagne !\n");
            save_board(tab_values);
            break;
        }

        if (check_lose(tab_values)) {
            printf("\nDommage ! Vous avez perdu. La boite est bloquee.\n");
            save_board(tab_values);
            break;
        }

        printf("\nChoisissez un mouvement : haut(z) bas(s) gauche(q) droite(d)\n");
        scanf(" %c", &move);

        if (!is_valid_move(tab_values, move)) {
            printf("Choix invalide, reessayez.\n");
            continue;
        }

        move_player(tab_values, move);
    }

    free_board(tab_values);
    return 0;
}