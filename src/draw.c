#include "raylib.h"
#include "draw.h"
#include <stdio.h>
#include "src/board.h"
#include "src/game.h"
#include <math.h>

int main(void) {

    InitWindow(900, 500, "Jogo");

    Texture2D mesa = LoadTexture("Assets/mesa.png");

        Texture2D maca1 = LoadTexture("Assets/maca1.png");
        Texture2D maca2 = LoadTexture("Assets/maca2.png");
        Texture2D maca3 = LoadTexture("Assets/maca3.png");
        Texture2D maca4 = LoadTexture("Assets/maca4.png");
        Texture2D maca5 = LoadTexture("Assets/maca5.png");
        Texture2D maca6 = LoadTexture("Assets/maca6.png");
        Texture2D maca7 = LoadTexture("Assets/maca7.png");
        Texture2D maca8 = LoadTexture("Assets/maca8.png");
        Texture2D maca9 = LoadTexture("Assets/maca9.png");
    Texture2D img[3][3] = { maca1, maca2, maca3, maca4, maca5, maca6, maca7, maca8, maca9,
    };
    Color cor = BLUE;
    bool c = true;

    Board *tab = board_create(9);
    board_initialize(tab);
    Game *game = game_create(3);
    game_start(game);

    // Tamanho inicial do tabuleiro
    int tr = 350;
    int lr = 350;

    while (!WindowShouldClose()) {
        
        // Lê as setas do teclado e move a peça se o jogador apertar
        if (IsKeyPressed(KEY_UP))    game_move_direction(game, 0); // Ajuste o número da direção conforme sua lógica
        if (IsKeyPressed(KEY_DOWN))  game_move_direction(game, 1);
        if (IsKeyPressed(KEY_LEFT))  game_move_direction(game, 2);
        if (IsKeyPressed(KEY_RIGHT)) game_move_direction(game, 3);

        // Tela cheia
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        int largura_tela = GetRenderWidth();
        int altura_tela = GetRenderHeight();

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

        for ( int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
            img[i][j].width = lrr;
            img[i][j].height = trr;
            }
        }
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

                    DrawTexture(
                        img[j][i],
                        xr + 1,
                        yr + 1,
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
