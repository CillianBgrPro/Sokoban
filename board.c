#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"

#define ROWS 10
#define COLS 10

static int win_position = -1;

char *create_board(void) {
    char *tab_values = malloc(ROWS * COLS * sizeof(char));
    if (!tab_values) {
        perror("Erreur d'allocation memoire");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ROWS * COLS; i++) {
        tab_values[i] = ' ';
    }

    return tab_values;
}

void display_board(char *tab_values) {
    char board[ROWS][COLS] = {
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#','#','#','#','#','#','#','#','#','#'}
    };

    if (win_position == -1) {
        for (int i = 0; i < ROWS * COLS; i++) {
            if (tab_values[i] == '.') {
                win_position = i;
                break;
            }
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int index = i * COLS + j;
            
            if (index == win_position && tab_values[index] != 'X' && tab_values[index] != 'o') {
                board[i][j] = '.';
            } else if (tab_values[index] != ' ') {
                board[i][j] = tab_values[index];
            }
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

bool is_valid_move(char *tab_values, char move) {
    int player_pos = -1;
    for (int i = 0; i < ROWS * COLS; i++) {
        if (tab_values[i] == 'o') {
            player_pos = i;
            break;
        }
    }

    if (player_pos == -1) return false;

    int next_pos = -1;
    int after_next_pos = -1;

    if (move == 'z') {
        next_pos = player_pos - COLS;
        after_next_pos = next_pos - COLS;
    } else if (move == 's') {
        next_pos = player_pos + COLS;
        after_next_pos = next_pos + COLS;
    } else if (move == 'q') {
        next_pos = player_pos - 1;
        after_next_pos = next_pos - 1;
    } else if (move == 'd') {
        next_pos = player_pos + 1;
        after_next_pos = next_pos + 1;
    } else {
        return false;
    }

    if (next_pos < 0 || next_pos >= ROWS * COLS) return false;

    int next_row = next_pos / COLS;
    int next_col = next_pos % COLS;
    
    if (next_row == 0 || next_row == ROWS - 1 || next_col == 0 || next_col == COLS - 1) {
        return false;
    }

    if (tab_values[next_pos] == '#') return false;

    if (tab_values[next_pos] == 'X') {
        if (after_next_pos < 0 || after_next_pos >= ROWS * COLS) return false;
        
        int after_row = after_next_pos / COLS;
        int after_col = after_next_pos % COLS;
        
        if (after_row == 0 || after_row == ROWS - 1 || after_col == 0 || after_col == COLS - 1) {
            return false;
        }
        
        if (tab_values[after_next_pos] == '#' || tab_values[after_next_pos] == 'X') return false;
    }

    return true;
}

void move_player(char *tab_values, char move) {
    int player_pos = -1;
    for (int i = 0; i < ROWS * COLS; i++) {
        if (tab_values[i] == 'o') {
            player_pos = i;
            break;
        }
    }

    if (player_pos == -1) return;

    int next_pos = -1;
    int after_next_pos = -1;

    if (move == 'z') {
        next_pos = player_pos - COLS;
        after_next_pos = next_pos - COLS;
    } else if (move == 's') {
        next_pos = player_pos + COLS;
        after_next_pos = next_pos + COLS;
    } else if (move == 'q') {
        next_pos = player_pos - 1;
        after_next_pos = next_pos - 1;
    } else if (move == 'd') {
        next_pos = player_pos + 1;
        after_next_pos = next_pos + 1;
    }

    if (tab_values[next_pos] == 'X') {

        tab_values[after_next_pos] = 'X';
        tab_values[next_pos] = 'o';
        tab_values[player_pos] = ' ';
    } else {

        tab_values[next_pos] = 'o';
        tab_values[player_pos] = ' ';
    }
}

bool check_win(char *tab_values) {

    if (win_position != -1 && tab_values[win_position] == 'X') {
        return true;
    }
    return false;
}

bool check_lose(char *tab_values) {

    int box_pos = -1;
    for (int i = 0; i < ROWS * COLS; i++) {
        if (tab_values[i] == 'X') {
            box_pos = i;
            break;
        }
    }

    if (box_pos == -1) return false;


    if (box_pos == win_position) {
        return false;
    }

    int row = box_pos / COLS;
    int col = box_pos % COLS;

    int up = box_pos - COLS;
    int down = box_pos + COLS;
    int left = box_pos - 1;
    int right = box_pos + 1;


    bool up_blocked = (row <= 1 || tab_values[up] == '#');
    bool down_blocked = (row >= ROWS - 2 || tab_values[down] == '#');
    bool left_blocked = (col <= 1 || tab_values[left] == '#');
    bool right_blocked = (col >= COLS - 2 || tab_values[right] == '#');


    if ((up_blocked && left_blocked) || (up_blocked && right_blocked) ||
        (down_blocked && left_blocked) || (down_blocked && right_blocked)) {
        return true;
    }

    return false;
}

void save_board(char *tab_values) {
    FILE *file = fopen("end.txt", "w");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int index = i * COLS + j;
            char c = tab_values[index];
            

            if (index == win_position && c == ' ') {
                fputc('.', file);
            } else if (c == ' ') {
                if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1) {
                    fputc('#', file);
                } else {
                    fputc(' ', file);
                }
            } else {
                fputc(c, file);
            }
        }
        fputc('\n', file);
    }

    fclose(file);
}

void free_board(char *tab_values) {
    free(tab_values);
    win_position = -1;
}