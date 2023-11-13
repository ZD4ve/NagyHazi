#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "Color.h"
#include "Dither.h"
#include "Error.h"

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
void Gprint_title(Gwindow *window);
SDL_Rect Gprint(Gwindow *window, char *text, SDL_Rect *location, Colortype col);
void Gtextbox(Gwindow *window, char *text, SDL_Rect *location, Colortype col, size_t border_width);
SDL_Texture *Gpre_render_cells(Gwindow *window);
void Ginput_text(Gwindow *window, char *dest, size_t hossz, SDL_Rect teglalap, bool is_file_name);
#endif