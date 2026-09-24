#include "raylib.h"
#include "draw.h"
#include <stdio.h>
#include "board.c"
#include <math.h>

int main(void) {

    InitWindow(900, 500, "Jogo");

    Texture2D mesa = LoadTexture("Assets/mesa.png");

    Color cor = BLUE;
    bool c = true;

    Board *tab = board_create(9);
    board_initialize(tab);

    // Tamanho inicial do tabuleiro
    int tr = 350;
    int lr = 350;

    while (!WindowShouldClose()) {

        // Tela cheia
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        // =====================================================
        // TAMANHO ATUAL DA ÁREA DE RENDERIZAÇÃO
        // =====================================================

        int largura_tela = GetRenderWidth();
        int altura_tela = GetRenderHeight();


        // =====================================================
        // MESA
        // =====================================================

        Rectangle Sf = {
            0.0f,
            0.0f,
            (float)mesa.width,
            (float)mesa.height
        };

       Rectangle Df = {
            -230.0f,
            -135.0f,
            (float)GetRenderWidth() + 450,
            (float)GetRenderHeight() + 300
        };


        // Mantém o tabuleiro no centro da tela
        int x = (largura_tela - tr) / 2;
        int y = (altura_tela - lr) / 2;

        int xr = x;
        int yr = y;

        int tamanho_lado = sqrt(tab->tamanho);

        int trr = tr / tamanho_lado;
        int lrr = lr / tamanho_lado;

        int ctp = trr / 2;
        int clp = lrr / 2;

        int num = 0;


        BeginDrawing();

        ClearBackground(cor);

        // Mesa ocupa toda a tela
        DrawTexturePro(
            mesa,
            Sf,
            Df,
            (Vector2){0.0f, 0.0f},
            0.0f,
            WHITE
        );


        // Tabuleiro
        DrawRectangle(
            x,
            y,
            tr,
            lr,
            YELLOW
        );


        // Peças
        for (int j = 0; j < tamanho_lado; j++) {

            xr = x;

            for (int i = 0; i < tamanho_lado; i++) {

                if (num != 0) {

                    DrawRectangle(
                        xr + 1,
                        yr + 1,
                        trr - 1,
                        lrr - 1,
                        PURPLE
                    );

                    DrawText(
                        TextFormat("%d", tab->tabuleiro[num]),
                        xr + ctp,
                        yr + clp,
                        2,
                        WHITE
                    );
                }

                xr += trr;
                num++;
            }

            yr += lrr;
        }

        EndDrawing();
    }

    UnloadTexture(mesa);
    CloseWindow();

    return 0;
}