#ifndef DRAW_H
#define DRAW_H

#include "raylib.h"
#include "board.h"

void draw_background(Texture2D mesa, Color cor_fundo);

void draw_puzzle(
    Texture2D imagem,
    const Board *tabuleiro,
    Rectangle area
);

#endif