#ifndef MENU_H
#define MENU_H


#include <stdlib.h>

#include "Graphics.h"
#include "File.h"
#include "gameWindow.h"
#include "debugmalloc.h"

#define MAX_SAVES 10
#define INPUT_MAX_LENGHT 15

typedef struct uj_jatek_input{
    char name[INPUT_MAX_LENGHT+4];
    SDL_Rect name_rct;
    char width[INPUT_MAX_LENGHT];
    SDL_Rect width_rct;
    char height[INPUT_MAX_LENGHT];
    SDL_Rect height_rct;
    SDL_Rect button;
} uj_jatek_input;

typedef struct Menu{
    Gwindow G;
    Fgame_file *saves;
    size_t save_cnt;
    gameWindow game_open;
    uj_jatek_input text_input;
} Menu;

Menu Minit();
void Mclose(Menu *menu);
void Mclick(Menu *menu, int x, int y);
void Mevent(Menu *menu, SDL_Event e);

#endif