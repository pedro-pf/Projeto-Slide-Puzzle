#include "raylib.h"
#include "draw.h"
#include <stdio.h>
#include "board.c"
#include <math.h>


int main(void) {
    InitWindow(900, 500, "Jogo");
    Board *tab = board_create(9);
    board_initialize(tab);

     Color cor = BLUE;
     bool c = true;
     
     //Tamanho do tabuleiro;
     int tr = 350;
     int lr = 350;

     //Posição do tabuleiro;
     int x = (GetRenderWidth() - tr) /2; 
     int y = (GetRenderHeight() - lr) /2;

     

    while(!WindowShouldClose()) {

    //Tela cheia (faltam configurações);
    if (IsKeyPressed(KEY_F11)) {
        ToggleFullscreen();
    }


    BeginDrawing();


    ClearBackground(cor);

    //Desenhar tabuleiro
    DrawRectangle(x, y, tr, lr, YELLOW);

    
    //Posição das peças;
     int xr = x;
     int yr = y;

     //Tamanho das peças;
     int trr = tr/(sqrt(tab->tamanho));
     int lrr = lr/(sqrt(tab->tamanho));

     //Centro das peças;
     int ctp = trr/2;
     int clp = lrr/2;

     //Contador das peças;
     int num = 0;
     
     //Desenhar cada peça do tabuleiro
    for (int j = 0; j < sqrt(tab->tamanho); j++) {
        xr = x;
        for (int i = 0; i < sqrt(tab->tamanho); i++) {
            if (num != 0) {
            DrawRectangle(xr + 1, yr + 1, trr - 1, lrr - 1, PURPLE);
            DrawText(TextFormat("%d", tab->tabuleiro[num]), xr + ctp, yr + clp, 2, WHITE);
            }
            xr += trr;
            num++;
    }
        yr += lrr;
}
    EndDrawing();
    }
}