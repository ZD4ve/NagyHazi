#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

typedef struct Gwindow{
    SDL_Window *win;
    SDL_Renderer *ren;
} Gwindow;

void Ginit();

Gwindow Gnew(char title[],int width,int height);

#endif