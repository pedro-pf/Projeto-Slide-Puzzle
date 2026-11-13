#ifndef DRAW_H
#define DRAW_H

#include "raylib.h"
#include "board.h"
#include "game.c"
#include "game.h"
#include "board.c"

void draw_puzzle(
    Texture2D imagem,
    const Board *tabuleiro,
    Rectangle area
);

#endif