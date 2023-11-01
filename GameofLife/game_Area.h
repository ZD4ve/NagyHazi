#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <SDL2/SDL.h>
#include <stdlib.h>  //DEBUGMALLOC!!

#include "Error.h"

/**
 * @brief Játéktér és tulajdonságai
 * @details Létrehozni csak fügvénnyel szabad,
 * törlése kötelező az Afree fügvénnyel
 */
typedef struct GameArea {
    size_t w;      // A játéktér szélessége
    size_t h;      // A játéktér magassága
    uint8_t **area;  // A játéktér tömbje
} GameArea;

GameArea Anew(size_t width, size_t height);
void Aclear(GameArea gamearea);
void Afree(GameArea *gamearea);

#endif