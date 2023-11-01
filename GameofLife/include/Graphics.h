#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../include/Error.h"

typedef struct Gwindow {
    SDL_Window *win;
    SDL_Renderer *ren;
    size_t w, h;
} Gwindow;

void Ginit();
void Gquit();

Gwindow Gnew(char title[], int width, int height);
void Gprint(Gwindow window, char *text, SDL_Rect location, SDL_Color color);
void Gprint_title(Gwindow window, SDL_Color color);

#endif