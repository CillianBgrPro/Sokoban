#ifndef BOARD_H
#define BOARD_H


char *create_board(void);
void display_board(char *tab_values);
bool is_valid_move(char *tab_values, char move);
void free_board(char *tab_values);

#endif
