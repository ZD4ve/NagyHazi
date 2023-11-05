#ifndef MENU_H
#define MENU_H


#include <SDL2/SDL.h>

#include "../include/Graphics.h"
#include "../include/File.h"

#define max_saves 10

typedef struct Menu{
    Gwindow G;
    Fgame_file *saves;
    size_t save_cnt;
} Menu;

Menu Minit();
void Mclose(Menu menu);
void Mclick(Menu menu, int x, int y);

#endif