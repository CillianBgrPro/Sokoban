#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"

#define ROWS 10
#define COLS 10

static int win_position = -1;

//j'alloue la mémoire nécessaire afin de stocker le tableau de 10 x 10, soit la taille de Rows qui correspond aux lignes et Cols qui correspond aux colonnes 

char *create_board(void) {
    char *tab_values = malloc(ROWS * COLS * sizeof(char));
    if (!tab_values) { //si la mémoire allouée n'est pas suffisante le message d'erreur si dessous s'affiche, j'ai trouvé le perror sur https://koor.fr/C/cstdio/perror.wp
        perror("Erreur d'allocation memoire");
        exit(0); //je mets fin au programme
    }

    for (int i = 0; i < ROWS * COLS; i++) { //je créer un boucle for dans laquelle je déclare une variable i qui a pour valeur 0, tant que i est inférieur au nombre de case du tableau soit 10 x 10 donc 100, on attribue ' ' à chaque case d'indice i
        tab_values[i] = ' ';
    }

    return tab_values;
}

void display_board(char *tab_values) { //je créé mon tableau qui s'affichera en console lors de l'execution du programme, # représente les murs et ' ' les cases dans lesquelles le personnage pourra se déplacer 
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

    //cette condition permet de chercher ou se situe la win_position, tant que win_position = -1 ce qui signifie qu'elle n'est pas encore trouvé, une boucle for s'execute et check les case une par une jusqu'à trouver le '.'
    if (win_position == -1) {
        for (int i = 0; i < ROWS * COLS; i++) {
            if (tab_values[i] == '.') {
                win_position = i;
                break;
            }
        }
    }


    int player_pos = -1;
    int box_pos = -1;
    
    //permet de trouver l'index de player_pos 
    for (int i = 0; i < ROWS * COLS; i++) {
        if (tab_values[i] == 'o') {
            player_pos = i;
        }
        //permet de trouver l'index de box_pos
        if (tab_values[i] == 'X') {
            box_pos = i;
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
    
//On affiche les indices de chaque éléments en sortant l'indice de Cols et de Row sous le format boite : x y 
    printf("\n--- Indices ---\n");
    
    if (player_pos != -1) {
        int player_row = player_pos / COLS;
        int player_col = player_pos % COLS;
        printf("Joueur : %d %d\n", player_row, player_col);
    }
    
    if (box_pos != -1) {
        int box_row = box_pos / COLS;
        int box_col = box_pos % COLS;
        printf("Boite  : %d %d\n", box_row, box_col);
    }
    
    if (win_position != -1) {
        int win_row = win_position / COLS;
        int win_col = win_position % COLS;
        printf("Emplacement : %d %d\n", win_row, win_col);
    }
    printf("---------------\n");
}

//fonction booleen qui permet de verifier si le movement spécifier par le joueur est valide, 
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

//fonction qui permet au joueur de se déplacer
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

    //mise en place de toutes les conditions qui permet de determiner le déplacement du joueur en fonction de la lettre entré en console 
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

//je check si X est sur la win position et dans ce cas la partie est remportée 
bool check_win(char *tab_values) {

    if (win_position != -1 && tab_values[win_position] == 'X') {
        return true;
    }
    return false;
}


//je check toutes les possibilités pour savoir si la caisse est bloquée, et dans ce cas je renvoie dans mon main le message perdu
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

//enregistrement de la position des éléments dans un fichier end.txt, je me suis aidé de ChatGpt pour réaliser ceci, je lui est demander comment débuter car j'étais bloqué 
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