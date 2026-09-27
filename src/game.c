#include "board.h"
#include <stdlib.h>
#include "game.h"

#define EMBARALHAMENTO_PADRAO 100

Game *game_create(int tamanho)
{
    Game *game = malloc(sizeof(Game));

    if (game == NULL)
        return NULL;

    game->board = board_create(tamanho);

    if (game->board == NULL) {
        free(game);
        return NULL;
    }

    game->tamanho = tamanho;
    game->movimentos = 0;
    game->venceu = 0;
    game->iniciado = 0;

    board_initialize(game->board);

    return game;
}

void game_destroy(Game *game)
{
    if (game == NULL)
        return;

    board_destroy(game->board);
    free(game);
}

void game_start(Game *game)
{
    if (game == NULL)
        return;

    board_initialize(game->board);
    board_shuffle(game->board, EMBARALHAMENTO_PADRAO);

    game->movimentos = 0;
    game->venceu = 0;
    game->iniciado = 1;
}

void game_restart(Game *game)
{
    game_start(game);
}

int game_move(Game *game, int linha, int coluna)
{
    if (game == NULL || game->iniciado == 0 || game->venceu == 1)
        return 0;

    int moveu = board_move(game->board, linha, coluna);

    if (moveu) {
        game->movimentos++;

        if (board_is_solved(game->board))
            game->venceu = 1;
    }

    return moveu;
}

static int game_find_empty(Game *game)
{
    int quantidade_celulas = game->board->tamanho * game->board->tamanho;

    for (int i = 0; i < quantidade_celulas; i++) {
        if (game->board->tabuleiro[i] == 0)
            return i;
    }

    return -1;
}

int game_move_direction(Game *game, int direcao)
{
    if (game == NULL || game->iniciado == 0 || game->venceu == 1)
        return 0;

    int tamanho = game->board->tamanho;
    int indice_vazio = game_find_empty(game);

    if (indice_vazio == -1)
        return 0;

    int linha_vazio = indice_vazio / tamanho;
    int coluna_vazio = indice_vazio % tamanho;

    int linha_peca = linha_vazio;
    int coluna_peca = coluna_vazio;

    /* Mesma convenção usada no embaralhamento do board.c */
    switch (direcao) {
        case 0: // cima
            linha_peca--;
            break;

        case 1: // baixo
            linha_peca++;
            break;

        case 2: // esquerda
            coluna_peca--;
            break;

        case 3: // direita
            coluna_peca++;
            break;

        default:
            return 0;
    }

    return game_move(game, linha_peca, coluna_peca);
}

int game_is_won(Game *game)
{
    if (game == NULL)
        return 0;

    return game->venceu;
}

int game_is_started(Game *game)
{
    if (game == NULL)
        return 0;

    return game->iniciado;
}

int game_get_moves(Game *game)
{
    if (game == NULL)
        return 0;

    return game->movimentos;
}

int game_get_size(Game *game)
{
    if (game == NULL)
        return 0;

    return game->tamanho;
}

int game_set_size(Game *game, int tamanho)
{
    if (game == NULL || tamanho < 2)
        return 0;

    board_destroy(game->board);

    game->board = board_create(tamanho);

    if (game->board == NULL)
        return 0;

    game->tamanho = tamanho;
    board_initialize(game->board);

    game->movimentos = 0;
    game->venceu = 0;
    game->iniciado = 0;

    return 1;
}

Board *game_get_board(Game *game)
{
    if (game == NULL)
        return NULL;

    return game->board;
}