#include "raylib.h"
#include "board.h"
#include "game.h"
#include "draw.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Slide Puzzle");
    SetTargetFPS(60);

    Game *game = game_create(3);
    game_start(game);
    while (!WindowShouldClose()) {
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            draw_board(game_get_board(game));
            
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
} 