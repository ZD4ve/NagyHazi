#ifndef MENU_H
#define MENU_H


#include <SDL2/SDL.h>

#include "../include/Graphics.h"
#include "../include/File.h"

Gwindow Minit();
void Mfree_files(Fgame_file saves[], size_t cnt);


#endif