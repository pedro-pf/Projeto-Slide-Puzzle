#ifndef BOARD_H
#define BOARD_H

typedef struct {
    int tamanho;
    int *tabuleiro;
} Board;

Board *board_create(int tamanho);
void board_destroy(Board *board);
void board_initialize(Board *board);

#endif