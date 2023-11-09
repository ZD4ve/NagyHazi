#ifndef MENU_H
#define MENU_H


#include <stdlib.h>

#include "Graphics.h"
#include "File.h"
#include "gameWindow.h"
#include "debugmalloc.h"

#define max_saves 10

typedef struct Menu{
    Gwindow G;
    Fgame_file *saves;
    size_t save_cnt;
    gameWindow game_open;
} Menu;

Menu Minit();
void Mclose(Menu *menu);
void Mclose_game(Menu *menu);
void Msave_game(Menu *menu);
void Mclick(Menu *menu, int x, int y);

#endif