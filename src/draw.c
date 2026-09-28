#include "raylib.h"
#include <stdio.h>
#include "game.h"
#include "game.c"
#include "board.h"
#include "board.c"

int main(void)
{
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

    Texture2D img[3][3] = {
        { maca1, maca2, maca3 },
        { maca4, maca5, maca6 },
        { maca7, maca8, maca9 }
    };

    Color cor = BLUE;

    Game *game = game_create(3);

    if (game == NULL)
    {
        UnloadTexture(mesa);

        UnloadTexture(maca1);
        UnloadTexture(maca2);
        UnloadTexture(maca3);
        UnloadTexture(maca4);
        UnloadTexture(maca5);
        UnloadTexture(maca6);
        UnloadTexture(maca7);
        UnloadTexture(maca8);
        UnloadTexture(maca9);

        CloseWindow();
        return 1;
    }

    game_start(game);

    Board *tab = game_get_board(game);

    // Tamanho inicial do tabuleiro
    int tr = 350;
    int lr = 350;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_UP))
            game_move_direction(game, 0);

        if (IsKeyPressed(KEY_DOWN))
            game_move_direction(game, 1);

        if (IsKeyPressed(KEY_LEFT))
            game_move_direction(game, 2);

        if (IsKeyPressed(KEY_RIGHT))
            game_move_direction(game, 3);

        // Tela cheia
        if (IsKeyPressed(KEY_F11))
            ToggleFullscreen();

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

        int x = (largura_tela - tr) / 2;
        int y = (altura_tela - lr) / 2;

        int tamanho_lado = tab->tamanho;

        int trr = tr / tamanho_lado;
        int lrr = lr / tamanho_lado;

        int num = 0;

        BeginDrawing();

        ClearBackground(cor);

        DrawTexturePro(
            mesa,
            Sf,
            Df,
            (Vector2){0.0f, 0.0f},
            0.0f,
            WHITE
        );

        DrawRectangle(
            x,
            y,
            tr,
            lr,
            YELLOW
        );

        for (int j = 0; j < tamanho_lado; j++)
        {
            int xr = x;

            for (int i = 0; i < tamanho_lado; i++)
            {
   
                int valor = tab->tabuleiro[num];

             
                if (valor != 0)
                {
                  
                    int indice = valor - 1;

                    int img_linha = indice / 3;
                    int img_coluna = indice % 3;

                    Texture2D maca = img[img_linha][img_coluna];

                    Rectangle source = {
                        0.0f,
                        0.0f,
                        (float)maca.width,
                        (float)maca.height
                    };

                    Rectangle dest = {
                        (float)(xr + 1),
                        (float)(y + j * lrr + 1),
                        (float)(trr - 2),
                        (float)(lrr - 2)
                    };

                 
                    DrawRectangle(
                        xr + 1,
                        y + j * lrr + 1,
                        trr - 2,
                        lrr - 2,
                        PURPLE
                    );

                   
                    DrawTexturePro(
                        maca,
                        source,
                        dest,
                        (Vector2){0.0f, 0.0f},
                        0.0f,
                        WHITE
                    );
                }

                xr += trr;
                num++;
            }
        }

        EndDrawing();
    }

    game_destroy(game);

    UnloadTexture(mesa);

    UnloadTexture(maca1);
    UnloadTexture(maca2);
    UnloadTexture(maca3);
    UnloadTexture(maca4);
    UnloadTexture(maca5);
    UnloadTexture(maca6);
    UnloadTexture(maca7);
    UnloadTexture(maca8);
    UnloadTexture(maca9);

    CloseWindow();

    return 0;
}