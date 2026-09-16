#include <stdlib.h>
#include "board.h"

Board *board_create(int tamanho)
{
    Board *board = malloc(sizeof(Board));

    if (board == NULL)
        return NULL;

    board->tamanho = tamanho;

    board->tabuleiro = malloc(tamanho * tamanho * sizeof(int));

    if (board->tabuleiro == NULL) {
        free(board);
        return NULL;
    }

    return board;
}

void board_destroy(Board *board)
{
    if (board == NULL)
        return;

    free(board->tabuleiro);
    free(board);
}

void board_initialize(Board *board)
{
    int quantidade_celulas = board->tamanho * board->tamanho;

    for (int i = 0; i < quantidade_celulas; i++) {
        board->tabuleiro[i] = i + 1;

        if (i == quantidade_celulas - 1)
            board->tabuleiro[i] = 0;
    }
}