#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

char *create_board(void);
void display_board(char *tab_values);
bool is_valid_move(char *tab_values, char move);
void move_player(char *tab_values, char move);
bool check_win(char *tab_values);
bool check_lose(char *tab_values);
void save_board(char *tab_values);
void free_board(char *tab_values);

#endif