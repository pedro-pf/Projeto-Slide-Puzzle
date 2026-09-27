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

    /*
        O Game cria o Board internamente.
        Portanto, NÃO criamos outro Board aqui.
    */
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

    /*
        Pegamos exatamente o Board que pertence ao Game.
    */
    Board *tab = game_get_board(game);

    // Tamanho inicial do tabuleiro
    int tr = 350;
    int lr = 350;

    while (!WindowShouldClose())
    {
        /*
            Movimentação
            0 = cima
            1 = baixo
            2 = esquerda
            3 = direita
        */
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

        /*
            Mesa
        */
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

        /*
            Mantém o tabuleiro no centro da tela
        */
        int x = (largura_tela - tr) / 2;
        int y = (altura_tela - lr) / 2;

        /*
            O tamanho é 3 porque o Board é 3x3.
            NÃO usamos sqrt aqui.
        */
        int tamanho_lado = tab->tamanho;

        int trr = tr / tamanho_lado;
        int lrr = lr / tamanho_lado;

        int num = 0;

        BeginDrawing();

        ClearBackground(cor);

        /*
            Mesa ocupa toda a tela
        */
        DrawTexturePro(
            mesa,
            Sf,
            Df,
            (Vector2){0.0f, 0.0f},
            0.0f,
            WHITE
        );

        /*
            Fundo do tabuleiro
        */
        DrawRectangle(
            x,
            y,
            tr,
            lr,
            YELLOW
        );

        /*
            Peças
        */
        for (int j = 0; j < tamanho_lado; j++)
        {
            int xr = x;

            for (int i = 0; i < tamanho_lado; i++)
            {
                /*
                    Pegamos o VALOR que está nessa posição.

                    Exemplo:
                    tabuleiro =

                    1 2 3
                    4 5 6
                    7 0 8

                    Na última posição teremos valor 8,
                    então desenhamos maca8.
                */
                int valor = tab->tabuleiro[num];

                /*
                    0 é o espaço vazio.
                    Portanto, não desenhamos nenhuma maçã.
                */
                if (valor != 0)
                {
                    /*
                        Os valores vão de 1 até 9,
                        enquanto os índices da matriz img vão
                        de 0 até 8.

                        Por isso fazemos valor - 1.
                    */
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

                    /*
                        Fundo roxo da peça
                    */
                    DrawRectangle(
                        xr + 1,
                        y + j * lrr + 1,
                        trr - 2,
                        lrr - 2,
                        PURPLE
                    );

                    /*
                        Desenha a maçã dentro da casa.
                    */
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

    /*
        O Board pertence ao Game.
        Portanto, NÃO fazemos board_destroy(tab).
        game_destroy() já destrói o Board.
    */
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