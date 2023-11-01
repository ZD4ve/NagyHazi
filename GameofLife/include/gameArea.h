#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <SDL2/SDL.h>
#include <stdlib.h>  //DEBUGMALLOC!!

#include "../include/Error.h"

/**
 * @brief Játéktér és tulajdonságai
 * @details Létrehozni csak fügvénnyel szabad,
 * törlése kötelező az Afree fügvénnyel
 */
typedef struct gameArea {
    size_t w;      // A játéktér szélessége
    size_t h;      // A játéktér magassága
    uint8_t **area;  // A játéktér tömbje
} gameArea;

gameArea Anew(size_t width, size_t height);
void Aclear(gameArea gamearea);
void Afree(gameArea *gamearea);

#endif