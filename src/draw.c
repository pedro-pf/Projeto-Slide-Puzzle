#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "board.h"
#include "game.c"
#include "game.h"
#include "board.c"

// Desenha o puzzle a partir de uma imagem inteira.
// O tamanho é obtido automaticamente do tabuleiro.
void draw_puzzle(
    Texture2D imagem,
    const Board *tabuleiro,
    Rectangle area
);

#endif

void draw_puzzle(
    Texture2D imagem,
    const Board *tabuleiro,
    Rectangle area
) {
    if (tabuleiro == NULL ||
        tabuleiro->tabuleiro == NULL ||
        tabuleiro->tamanho < 2 ||
        imagem.id == 0) {
        return;
    }

    int lado = tabuleiro->tamanho;

    // Dimensões de cada recorte na imagem original.
    float largura_origem = (float)imagem.width / lado;
    float altura_origem = (float)imagem.height / lado;

    // Dimensões de cada peça na tela.
    float largura_destino = area.width / lado;
    float altura_destino = area.height / lado;

    // Fundo que aparecerá no espaço vazio.
    DrawRectangleRec(area, DARKGRAY);

    for (int linha = 0; linha < lado; linha++) {
        for (int coluna = 0; coluna < lado; coluna++) {

            int indice = linha * lado + coluna;
            int peca = tabuleiro->tabuleiro[indice];

            // O zero representa o espaço vazio.
            if (peca == 0) {
                continue;
            }

            // Descobre a posição original da peça.
            int origem = peca - 1;

            int linha_origem = origem / lado;
            int coluna_origem = origem % lado;

            // Região da imagem que pertence à peça.
            Rectangle recorte = {
                coluna_origem * largura_origem,
                linha_origem * altura_origem,
                largura_origem,
                altura_origem
            };

            // Posição atual da peça no tabuleiro.
            Rectangle destino = {
                area.x + coluna * largura_destino,
                area.y + linha * altura_destino,
                largura_destino,
                altura_destino
            };

            DrawTexturePro(
                imagem,
                recorte,
                destino,
                (Vector2){0, 0},
                0.0f,
                WHITE
            );

            // Borda para distinguir as peças.
            DrawRectangleLinesEx(destino, 1.5f, BLACK);
        }
    }

    DrawRectangleLinesEx(area, 2.0f, BLACK);
}

int main(void)
{
    InitWindow(900, 500, "Slide Puzzle");
    SetTargetFPS(60);

    Texture2D mesa = LoadTexture("Assets/mesa.png");
    Texture2D imagem = LoadTexture("Assets/maca.png");

    Game *game = game_create(3); 

    if (imagem.id == 0) {
        if (mesa.id != 0) UnloadTexture(mesa);
        CloseWindow();
        return 1;
    }

    game_start(game);
    

    // O argumento é o número de linhas e colunas.
    Board *tab = game_get_board(game);


    if (tab == NULL) {
        UnloadTexture(imagem);
        if (mesa.id != 0) UnloadTexture(mesa);
        CloseWindow();
        return 1;
    }

    board_initialize(tab);
    board_shuffle(tab,50);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_UP))
            game_move_direction(game, 0);

        if (IsKeyPressed(KEY_DOWN))
            game_move_direction(game, 1);

        if (IsKeyPressed(KEY_LEFT))
            game_move_direction(game, 2);

        if (IsKeyPressed(KEY_RIGHT))
            game_move_direction(game, 3);

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        float largura = (float)GetRenderWidth();
        float altura = (float)GetRenderHeight();

        Rectangle area_tabuleiro = {
            (largura - 350.0f) / 2.0f,
            (altura - 350.0f) / 2.0f,
            350.0f,
            350.0f
        };

        BeginDrawing();
        ClearBackground(BLUE);

        if (mesa.id != 0) {
            Rectangle origem_mesa = {
                0, 0,
                (float)mesa.width,
                (float)mesa.height
            };

            Rectangle destino_mesa = {
                -230, -135,
                largura + 450,
                altura + 300
            };

            DrawTexturePro(
                mesa,
                origem_mesa,
                destino_mesa,
                (Vector2){0, 0},
                0,
                WHITE
            );
        }

        draw_puzzle(imagem, tab, area_tabuleiro);

        EndDrawing();
    }

    board_destroy(tab);
    UnloadTexture(imagem);

    if (mesa.id != 0) {
        UnloadTexture(mesa);
    }

    CloseWindow();
    return 0;
}