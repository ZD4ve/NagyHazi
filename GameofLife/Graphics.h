#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

#include "Error.h"

typedef struct Gwindow{
    SDL_Window *win;
    SDL_Renderer *ren;
    size_t w, h;
} Gwindow;

void Ginit();

Gwindow Gnew(char title[],int width,int height);

#endif