#ifndef GAME_H
#define GAME_H

#include "board.h"

typedef struct {
    Board *board;
    int tamanho;
    int movimentos;
    int venceu;
    int iniciado;
} Game;

Game *game_create(int tamanho);
void game_destroy(Game *game);

void game_start(Game *game);
void game_restart(Game *game);

int game_move(Game *game, int linha, int coluna);
int game_move_direction(Game *game, int direcao);

int game_is_won(Game *game);
int game_is_started(Game *game);

int game_get_moves(Game *game);
int game_get_size(Game *game);
int game_set_size(Game *game, int tamanho);

Board *game_get_board(Game *game);

#endif