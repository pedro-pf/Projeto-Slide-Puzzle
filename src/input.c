#include <stddef.h>
#include "raylib.h"
#include "input.h"

void input_update(Game *game)
{
    if (game == NULL)
        return;

    if (IsKeyPressed(KEY_UP))
        game_move_direction(game, 0);

    if (IsKeyPressed(KEY_DOWN))
        game_move_direction(game, 1);

    if (IsKeyPressed(KEY_LEFT))
        game_move_direction(game, 2);

    if (IsKeyPressed(KEY_RIGHT))
        game_move_direction(game, 3);

    if (IsKeyPressed(KEY_R))
        game_restart(game);

    if (IsKeyPressed(KEY_F11))
        ToggleFullscreen();
}