#ifndef FILE_H
#define FILE_H

#include "../include/Error.h"
#include "../include/gameArea.h"

gameArea Fopen(char *path);
void Fsave(char *path, gameArea gamearea);

#endif