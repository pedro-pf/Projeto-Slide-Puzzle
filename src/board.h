#ifndef BOARD_H
#define BOARD_H

typedef struct {
    int tamanho;
    int *tabuleiro;
} Board;

Board *board_create(int tamanho);
void board_destroy(Board *board);
void board_initialize(Board *board);
int board_move(Board *board, int linha, int coluna);
void board_shuffle(Board *board, int movimentos);
int board_is_solved(Board *board);

#endif