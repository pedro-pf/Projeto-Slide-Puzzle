#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#include "game.h"
#include "draw.h"
#include "input.h"

static Texture2D carregar_textura_opcional(
    const char *caminho1,
    const char *caminho2
)
{
    Texture2D textura = {0};

    if (FileExists(caminho1))
    {
        textura = LoadTexture(caminho1);
        return textura;
    }

    if (FileExists(caminho2))
    {
        textura = LoadTexture(caminho2);
        return textura;
    }

    return textura;
}

int main(void)
{
    const int largura_inicial = 900;
    const int altura_inicial = 500;

    InitWindow(
        largura_inicial,
        altura_inicial,
        "Slide Puzzle"
    );

    SetTargetFPS(60);

    srand((unsigned int)time(NULL));

    Game *game = game_create(3);

    if (game == NULL)
    {
        CloseWindow();
        return 1;
    }

    game_start(game);

    Texture2D mesa =
        carregar_textura_opcional(
            "assets/mesa.png",
            "Assets/mesa.png"
        );

    Texture2D imagem =
        carregar_textura_opcional(
            "assets/maca.png",
            "Assets/maca.png"
        );

    while (!WindowShouldClose())
    {
        input_update(game);

        float largura_tela =
            (float)GetRenderWidth();

        float altura_tela =
            (float)GetRenderHeight();

        const float tamanho_tabuleiro = 350.0f;

        Rectangle area_tabuleiro = {
            (largura_tela - tamanho_tabuleiro) / 2.0f,
            (altura_tela - tamanho_tabuleiro) / 2.0f,
            tamanho_tabuleiro,
            tamanho_tabuleiro
        };

        BeginDrawing();

        draw_background(
            mesa,
            BLUE
        );

        draw_puzzle(
            imagem,
            game_get_board(game),
            area_tabuleiro
        );

        DrawRectangle(
            10,
            10,
            310,
            65,
            Fade(RAYWHITE, 0.85f)
        );

        DrawText(
            TextFormat(
                "Movimentos: %d",
                game_get_moves(game)
            ),
            20,
            18,
            20,
            BLACK
        );

        DrawText(
            "Setas: mover | R: reiniciar | F11: tela cheia",
            20,
            48,
            12,
            DARKGRAY
        );

        if (game_is_won(game))
        {
            const char *mensagem =
                "PUZZLE COMPLETO!";

            int tamanho_fonte = 30;

            int largura_texto =
                MeasureText(
                    mensagem,
                    tamanho_fonte
                );

            DrawRectangle(
                (int)(
                    largura_tela / 2
                    - largura_texto / 2
                    - 20
                ),
                (int)(
                    area_tabuleiro.y
                    + area_tabuleiro.height
                    + 15
                ),
                largura_texto + 40,
                50,
                Fade(RAYWHITE, 0.90f)
            );

            DrawText(
                mensagem,
                (int)(
                    largura_tela / 2
                    - largura_texto / 2
                ),
                (int)(
                    area_tabuleiro.y
                    + area_tabuleiro.height
                    + 25
                ),
                tamanho_fonte,
                DARKGREEN
            );
        }

        EndDrawing();
    }

    game_destroy(game);

    if (imagem.id != 0)
        UnloadTexture(imagem);

    if (mesa.id != 0)
        UnloadTexture(mesa);

    CloseWindow();

    return 0;
}