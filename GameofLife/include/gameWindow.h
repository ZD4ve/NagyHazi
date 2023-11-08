#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <stdbool.h>
#include "Graphics.h"
#include "gameArea.h"

typedef struct gameWindow {
    gameArea A;
    Gwindow G;
    char *name;
    SDL_Texture *pre_rendered_cells;
    SDL_Texture *full_game;
    size_t texture_w;
    size_t texture_h;
    double zoom;
    double center_x;
    double center_y;
} gameWindow;

gameWindow Winit(gameArea *A, char *name);
void Wclose(gameWindow *game);
void Wclick(gameWindow *game, int x, int y);
void Wdraw(gameWindow *game, bool valtozott_adat);
#endif