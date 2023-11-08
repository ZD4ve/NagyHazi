#ifndef FILE_H
#define FILE_H

#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "Error.h"
#include "gameArea.h"
#include "debugmalloc.h"


typedef struct Fgame_file{
    char *path;
    SDL_Rect location;
} Fgame_file;

gameArea Fopen(char *path);
void Fsave(char *path, gameArea *gamearea);
size_t Flist(Fgame_file games[], size_t max_count);

#endif