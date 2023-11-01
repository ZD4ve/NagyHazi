#ifndef FILE_H
#define FILE_H

#include "Error.h"
#include "game_Area.h"

GameArea Fopen(char *path);
void Fsave(char *path, GameArea gamearea);

#endif