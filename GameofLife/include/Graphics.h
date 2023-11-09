#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Error.h"
#include "Color.h"
#include "Dither.h"

#define CELL_SIZE 8

typedef struct Gwindow {
    SDL_Window *win;
    SDL_Renderer *ren;
    size_t w, h;
    TTF_Font *font_big;
    TTF_Font *font_reg;
    Color_theme colors; 
} Gwindow;

void Ginit();
void Gclose(Gwindow *window);
void Gquit();

Gwindow Gnew(char title[], int width, int height, bool resizable);
void Gset_color(Gwindow *window, SDL_Color col);
void Gfill_background(Gwindow *window);
void Gprint(Gwindow *window, char *text, SDL_Rect *location, Colortype col);
void Gprint_title(Gwindow *window);
SDL_Rect Grectwithborders(Gwindow *window,SDL_Rect location, size_t border_width, Colortype col);
SDL_Texture *Gpre_render_cells(Gwindow *window);
#endif