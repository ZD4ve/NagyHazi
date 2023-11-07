#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "Graphics.h"
#include "gameArea.h"

typedef struct gameWindow
{
    gameArea A;
    Gwindow G;
    SDL_Texture *pre_rendered_cells;
    SDL_Texture *full_game;
} gameWindow;

gameWindow Winit(gameArea *A);
void Wclose(gameWindow *W);
void WdrawCells(gameWindow *game);

#endif