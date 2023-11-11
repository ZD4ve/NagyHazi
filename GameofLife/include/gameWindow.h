#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <stdbool.h>
#include "Graphics.h"
#include "gameArea.h"
#include "File.h"

typedef struct gameWindow {
    gameArea A;
    Gwindow G;
    char *name;
    SDL_Texture *pre_rendered_cells;
    SDL_Texture *full_game;
    size_t texture_w;
    size_t texture_h;
    double zoom;
    ssize_t x_screen_offset;
    ssize_t y_screen_offset;
} gameWindow;

gameWindow Winit(gameArea A, char *name);
void Wclose(gameWindow *game);
void Wclick(gameWindow *game, int x, int y);
void Wdraw(gameWindow *game);
void Wzoom(gameWindow *game, double wheel, int x, int y);
void Wresetzoom(gameWindow *game);
void Wevent(gameWindow *game, SDL_Event e);
#endif