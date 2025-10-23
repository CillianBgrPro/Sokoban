#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "init.h"

#define ROWS 10
#define COLS 10

char *init_objects(void) {
    srand(time(NULL));

    char box = 'X';
    char player = 'o';
    char win = '.';

    char *tab_values = malloc(ROWS * COLS * sizeof(char));
    if (!tab_values) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ROWS * COLS; i++) {
        tab_values[i] = ' ';
    }

    int player_position = -1;
    while (player_position == -1) {
        int index = rand() % (ROWS * COLS);
        int row = index / COLS;
        int col = index % COLS;

        if (row > 0 && row < ROWS - 1 && col > 0 && col < COLS - 1) {
            tab_values[index] = player;
            player_position = index;
        }
    }

    int box_position = -1;
    while (box_position == -1) {
        int index = rand() % (ROWS * COLS);
        if (tab_values[index] == ' ' && index != player_position) {
            tab_values[index] = box;
            box_position = index;
        }
    }

    int win_position = -1;
    while (win_position == -1) {
        int index = rand() % (ROWS * COLS);
        if (tab_values[index] == ' ' && index != player_position && index != box_position) {
            tab_values[index] = win;
            win_position = index;
        }
    }

    return tab_values;
}
