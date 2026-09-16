#include <stdlib.h>
#include <time.h>
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

static int board_find_empty(Board *board)
{
    int quantidade_celulas = board->tamanho * board->tamanho;

    for (int i = 0; i < quantidade_celulas; i++) {
        if (board->tabuleiro[i] == 0)
            return i;
    }

    return -1;
}

int board_move(Board *board, int linha, int coluna)
{
    int tamanho = board->tamanho;

    if (linha < 0 || linha >= tamanho ||
        coluna < 0 || coluna >= tamanho)
        return 0;

    int indice_peca = linha * tamanho + coluna;
    int indice_vazio = board_find_empty(board);

    if (indice_vazio == -1)
        return 0;

    int linha_vazio = indice_vazio / tamanho;
    int coluna_vazio = indice_vazio % tamanho;

    int distancia_linha = linha - linha_vazio;
    int distancia_coluna = coluna - coluna_vazio;

    if ((distancia_linha == 0 && (distancia_coluna == 1 || distancia_coluna == -1)) ||
        (distancia_coluna == 0 && (distancia_linha == 1 || distancia_linha == -1))) {

        int temporario = board->tabuleiro[indice_peca];
        board->tabuleiro[indice_peca] = board->tabuleiro[indice_vazio];
        board->tabuleiro[indice_vazio] = temporario;

        return 1;
    }

    return 0;
}

static int board_move_random(Board *board, int direcao)
{
    int indice_vazio = board_find_empty(board);

    if (indice_vazio == -1)
        return 0;

    int tamanho = board->tamanho;

    int linha_vazio = indice_vazio / tamanho;
    int coluna_vazio = indice_vazio % tamanho;

    int linha_peca = linha_vazio;
    int coluna_peca = coluna_vazio;

    switch (direcao) {
        case 0:
            linha_peca--;
            break;

        case 1:
            linha_peca++;
            break;

        case 2:
            coluna_peca--;
            break;

        case 3:
            coluna_peca++;
            break;
    }

    return board_move(board, linha_peca, coluna_peca);
}

void board_shuffle(Board *board, int movimentos)
{
    for (int i = 0; i < movimentos; i++) {
        int direcao;

        do {
            direcao = rand() % 4;
        } while (!board_move_random(board, direcao));
    }
}