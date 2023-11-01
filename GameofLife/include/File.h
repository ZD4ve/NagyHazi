#ifndef FILE_H
#define FILE_H

#include "Error.h"
#include "gameArea.h"

gameArea Fopen(char *path);
void Fsave(char *path, gameArea gamearea);

#endif