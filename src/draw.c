#include <stddef.h>
#include "raylib.h"
#include "draw.h"

void draw_background(Texture2D mesa, Color cor_fundo)
{
    ClearBackground(cor_fundo);

    if (mesa.id == 0)
        return;

    Rectangle origem = {
        0.0f,
        0.0f,
        (float)mesa.width,
        (float)mesa.height
    };

    Rectangle destino = {
        -230.0f,
        -135.0f,
        (float)GetRenderWidth() + 450.0f,
        (float)GetRenderHeight() + 300.0f
    };

    DrawTexturePro(
        mesa,
        origem,
        destino,
        (Vector2){0.0f, 0.0f},
        0.0f,
        WHITE
    );
}

void draw_puzzle(
    Texture2D imagem,
    const Board *tabuleiro,
    Rectangle area
)
{
    if (tabuleiro == NULL)
        return;

    if (tabuleiro->tabuleiro == NULL)
        return;

    if (tabuleiro->tamanho < 2)
        return;

    int lado = tabuleiro->tamanho;

    float largura_destino = area.width / lado;
    float altura_destino = area.height / lado;

    DrawRectangleRec(area, DARKGRAY);

    for (int linha = 0; linha < lado; linha++)
    {
        for (int coluna = 0; coluna < lado; coluna++)
        {
            int indice = linha * lado + coluna;
            int peca = tabuleiro->tabuleiro[indice];

            if (peca == 0)
                continue;

            Rectangle destino = {
                area.x + coluna * largura_destino,
                area.y + linha * altura_destino,
                largura_destino,
                altura_destino
            };

            if (imagem.id != 0)
            {
                float largura_origem =
                    (float)imagem.width / lado;

                float altura_origem =
                    (float)imagem.height / lado;

                int origem = peca - 1;

                int linha_origem =
                    origem / lado;

                int coluna_origem =
                    origem % lado;

                Rectangle recorte = {
                    coluna_origem * largura_origem,
                    linha_origem * altura_origem,
                    largura_origem,
                    altura_origem
                };

                DrawTexturePro(
                    imagem,
                    recorte,
                    destino,
                    (Vector2){0.0f, 0.0f},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                DrawRectangleRec(
                    destino,
                    PURPLE
                );

                float menor_lado;

                if (largura_destino < altura_destino)
                    menor_lado = largura_destino;
                else
                    menor_lado = altura_destino;

                int tamanho_fonte =
                    (int)(menor_lado * 0.35f);

                if (tamanho_fonte < 12)
                    tamanho_fonte = 12;

                const char *texto =
                    TextFormat("%d", peca);

                int largura_texto =
                    MeasureText(texto, tamanho_fonte);

                int texto_x =
                    (int)(
                        destino.x
                        + (destino.width - largura_texto) / 2
                    );

                int texto_y =
                    (int)(
                        destino.y
                        + (destino.height - tamanho_fonte) / 2
                    );

                DrawText(
                    texto,
                    texto_x,
                    texto_y,
                    tamanho_fonte,
                    WHITE
                );
            }

            DrawRectangleLinesEx(
                destino,
                2.0f,
                BLACK
            );
        }
    }

    DrawRectangleLinesEx(
        area,
        3.0f,
        BLACK
    );
}